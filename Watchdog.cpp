#include "Watchdog.h"

//Collecting the Players here
std::vector<Observer*> observers;

bool (*playingSate) (); //For Muting.. Assigned externally!
void registerPlayingState(void* fktPtr) {
    playingSate = (bool(*)())fktPtr;
}

void registerObserver(Observer* observer) {
    observers.push_back(observer);
}

//Notifying the players of changes. Needing to reduce redundance later!
void notifyObservers() {
    for (Observer* observer : observers) {
        observer->update();
    }
}

//Needing to find the DOSBox Handler to get into its memory.
//Stole the code from Stackoverflow. Any questions ask the stackoverflow people.
HWND hWnd;

DWORD GetProcessID(const wchar_t* FileName) {
    PROCESSENTRY32 entry;
    entry.dwSize = sizeof(PROCESSENTRY32);

    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

    if (Process32First(snapshot, &entry)) {
        while (Process32Next(snapshot, &entry)) {
            if (!wcscmp(entry.szExeFile, FileName)) {
                return entry.th32ProcessID;
            }
        }
    }

    return -1;
}

BOOL CALLBACK EnumDosboxProc(HWND hwnd, LPARAM lParam)
{
    char buffer[128];
    int written = GetWindowTextA(hwnd, buffer, 32);
    if (written && strstr(buffer, "DOSBox") != NULL) {
        *(HWND*)lParam = hwnd;
        return FALSE;
    }
    return TRUE;
}

HWND GetDOSBoxHwnd()
{
    hWnd = NULL;
    EnumWindows(EnumDosboxProc, (LPARAM)&hWnd);

    return hWnd;
}

DWORD_PTR GetProcessBaseAddress(DWORD processID)
{
    DWORD_PTR   baseAddress = 0;
    HANDLE      processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processID);
    HMODULE* moduleArray;
    LPBYTE      moduleArrayBytes;
    DWORD       bytesRequired;

    if (processHandle)
    {
        if (EnumProcessModules(processHandle, NULL, 0, &bytesRequired))
        {
            if (bytesRequired)
            {
                moduleArrayBytes = (LPBYTE)LocalAlloc(LPTR, bytesRequired);

                if (moduleArrayBytes)
                {
                    unsigned int moduleCount;

                    moduleCount = bytesRequired / sizeof(HMODULE);
                    moduleArray = (HMODULE*)moduleArrayBytes;

                    if (EnumProcessModules(processHandle, moduleArray, bytesRequired, &bytesRequired))
                    {
                        baseAddress = (DWORD_PTR)moduleArray[0];
                    }
                    LocalFree(moduleArrayBytes);
                }
            }
        }
        CloseHandle(processHandle);
    }
    return baseAddress;
}

BOOL IsProcessStillRunning()
{
    if (GetDOSBoxHwnd())
        return TRUE;
    else
        return FALSE;
}

//Checking if RAY is in the string by going step by step from the char pointer
bool RayCheck(const char* buffer) {
    for (int i = 0; i < sizeof(buffer) - 3; i++) {
        if (buffer[i] == 'R' && buffer[i + 1] == 'A' && buffer[i + 2] == 'Y') {
            return true;
        }
    }
    return false;
}

__int64 worldBase = 1; //This will be the pointer to the WorldBase. Giving it a 1 to sattisfy my compiler
HANDLE phandle; //The handle for DOSBox's process
GameData* data;
Offsets* loffsets;
DWORD_PTR baseaddr = 0;

//Cause a glitch in Rayman to prevent the next CDDA Track to be played. Useful for the Boss Event
bool GlitchMusic(bool enable) {
    if (worldBase == 1)
        return false;

    return WriteProcessMemory(phandle, (LPVOID)(worldBase + loffsets->Music), &enable, sizeof(enable), 0);
}

//Quickly mute the CDDA channel from DOSBox. Requires static address
bool MuteCDDA(bool enable) {
    if (baseaddr == 0)
        return false;
    
    return WriteProcessMemory(phandle, (LPVOID)(baseaddr + loffsets->CDDA), &enable, sizeof(enable), 0);
}

void FetchData() {
    //Needing to read a 0x17635 or 95797 bytes big chunk starting from the worldbase.
    //This is where my pBuffer comes in play.
    char* pBuffer = new char[27];
    pBuffer[0] = 1;

    //This is prolly the only loop in need in the final
    while (IsProcessStillRunning())
    {
        //Reading world
        ReadProcessMemory(phandle, (LPVOID)worldBase, pBuffer, 8, 0);
        data->World.assign(pBuffer, 8);

        //Reading level
        ReadProcessMemory(phandle, (LPVOID)(worldBase + loffsets->Level), pBuffer+9, 9, 0); //Will have offsets injected later
        data->Level.assign(pBuffer + 9, 8);

        //Bugfix: Previous loop having 9 iterations caused the level string to have a bigger size than
        //characters due to a null being added extra
        if (pBuffer[17])
            data->Level += pBuffer[17];

        //Reading InLevel
        ReadProcessMemory(phandle, (LPVOID)(worldBase + loffsets->InLevel), pBuffer+18, 1, 0);
        data->InLevel = pBuffer[18];

        //Reading Music
        ReadProcessMemory(phandle, (LPVOID)(worldBase + loffsets->Music), pBuffer + 19, 1, 0);
        data->Music = pBuffer[19];

        //Reading OptionsOn
        ReadProcessMemory(phandle, (LPVOID)(worldBase + loffsets->OptionsOn), pBuffer + 20, 1, 0);
        data->OptionsOn = pBuffer[20];

        //Reading OptionsOff
        ReadProcessMemory(phandle, (LPVOID)(worldBase + loffsets->OptionsOff), pBuffer + 21, 1, 0);
        data->OptionsOff = pBuffer[21];

        //Reading BossEvent
        ReadProcessMemory(phandle, (LPVOID)(worldBase + loffsets->BossEvent), pBuffer + 22, 1, 0);
        data->BossEvent = pBuffer[22];

        //Reading XAxis
        ReadProcessMemory(phandle, (LPVOID)(worldBase + loffsets->XAxis), pBuffer + 23, 2, 0);
        data->XAxis = ((uint16_t)pBuffer[24] << 8) | (uint8_t)pBuffer[23];

        //Reading YAxis
        ReadProcessMemory(phandle, (LPVOID)(worldBase + loffsets->YAxis), pBuffer + 25, 2, 0);
        data->YAxis = ((uint16_t)pBuffer[26] << 8) | (uint8_t)pBuffer[25];

        notifyObservers();

        //Immediatly mute CDDA if TPLS is playing!
        if (playingSate())
            MuteCDDA(false); //note: false means muting

        Sleep(10);
    }
}

bool Watch(Offsets* offsets, GameData* pdata)
{
    __int64 worldOffset = offsets->WorldBase; //Hardcoding the v1.12 Worldbase address. Will change later, not so hard boi anymore :(
    __int64 value = 0; //Need a result variable when reading the pointer to DOSBox's virtual memory 
    __int64 memoryTest = offsets->MemoryTest; //Excepting a 320 for v1.12 when reading from DOSBox's virtual memory to this offset
    int memoryTestRes = 0;
    DWORD pid;
    hWnd;
    DWORD_PTR pMem = offsets->Pointer;
    DWORD_PTR address;
    data = pdata;
    
    hWnd = GetDOSBoxHwnd();
    if (!hWnd)
    {
        std::cout << "Window not found!\n";
        return false;
    }
    GetWindowThreadProcessId(hWnd, &pid);
    DWORD pidTest = GetProcessID(L"dosbox-x.exe");
    phandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
    if (!phandle)
    {
        std::cout << "Could not get handle!\n";
        return false;
    }
    baseaddr = GetProcessBaseAddress(pid);
    address = baseaddr; //Getting Base Address, not every dosbox uses a fixed base address!
    std::cout << "Got base address: " << address << std::endl;
    address += pMem; //Address here should go to the global pointer, which points towards the virtual memory I'm looking for 
    std::cout << "Pointer: " << address << std::endl;
    

    while (IsProcessStillRunning() && worldBase == 1)
    { //Now Loop while DOSBox's is still running and apparently the compatible Rayman version hasnt't been started yet..
        ReadProcessMemory(phandle, (LPCVOID)address, &value, 8, 0); //Getting the pointer to the virtual memory and storing it to "value"
        if (value == 0) {
            std::cout << "No pointer found yet..." << std::endl;
        }
        else {
            std::cout << "Pointer found! At: " << value << std::endl;
            worldBase = value + worldOffset; 
            //Do a quick test if I got the correct address. If not should just stop.
            ReadProcessMemory(phandle, (LPVOID)(value + memoryTest), &memoryTestRes, 2, 0);
            if (memoryTestRes == 320) {
                std::cout << "Game found at: " << worldBase << std::endl;
                break;
            }
        }
        worldBase = 1;
        std::cout << "No Worldbase found yet!" << std::endl;
        Sleep(1000);
    }

    loffsets = offsets;
    FetchData();

    return true;
}