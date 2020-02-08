#include "Watchdog.h"
#include "BGMPlayer.h"
#include "MidiPlayer.h"
#include "PosPlayer.h"

//Collecting the Players here
std::vector<Observer*> observers;
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

void Watch(uint64_t pDOSBox)
{
    __int64 worldOffset = 0x1AD804; //Hardcoding the v1.12 Worldbase address. Yeah I'm a really bad boi >:D
    __int64 value = 0; //Need a result variable when reading the pointer to DOSBox's virtual memory 
    __int64 memoryTest = 0x1AD7BC; //Excepting a 320 for v1.12 when reading from DOSBox's virtual memory to this offset
    int memoryTestRes = 0;
    DWORD pid;
    hWnd;
    DWORD_PTR pMem = pDOSBox;
    DWORD_PTR address;

    while (1)
    {
        Sleep(1000); //The while loop will be gone soon. This should not be running if DOSBox's hasn't been started up before!
        hWnd = GetDOSBoxHwnd();
        if (!hWnd)
        {
            std::cout << "Window not found!\n";
            continue;
        }
        GetWindowThreadProcessId(hWnd, &pid);
        DWORD pidTest = GetProcessID(L"dosbox-x.exe");
        phandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
        if (!phandle)
        {
            std::cout << "Could not get handle!\n";
            continue;
        }
        address = GetProcessBaseAddress(pid); //Getting Base Address, not every dosbox uses a fixed base address!
        std::cout << "Got base address: " << address << std::endl;
        address += pMem; //Address here should go to the global pointer, which points towards the virtual memory I'm looking for 
        std::cout << "Pointer: " << address << std::endl;
        break;
    }

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

    //Creating new GameData struct and Players
    //I should move this out later
    GameData* data = new GameData;
    BGMPlayer player(data);
    MidiPlayer midi(data);
    PosPlayer pos(data);
    registerObserver(&midi);
    registerObserver(&pos);
    registerObserver(&player);

    //Having local data here to check if something changed.
    //Should also be moved out if I want all data passed to the listeners as one
    bool InLevel = false;
    bool Music = false;
    bool OptionsOff = false;
    bool OptionsOn = false;
    bool BossEvent = false;
    char b0 = 0;
    char b1 = 1;
    //Needing to read a 0x17635 or 95797 bytes big chunk starting from the worldbase.
    //This is where my pBuffer comes in play.
    char* pBuffer = new char[0x17635];
    pBuffer[0] = 1;

    //This is prolly the only loop in need in the final
    while (IsProcessStillRunning())
    {
        ReadProcessMemory(phandle, (LPVOID)worldBase, pBuffer, 0x17635, 0);
        
        //Assigning the current World and Level into the GameData struct
        data->World.assign(pBuffer, 8);
        data->Level.assign(pBuffer+0x0001C, 8);

        //Bugfix: Previous loop having 9 iterations caused the level string to have a bigger size than
        //characters due to a null being added extra
        if (pBuffer[8 + 0x0001C])
            data->Level += pBuffer[8 + 0x0001C];
        
        //Storing all the datas from each offset 
        data->InLevel = pBuffer[0x02278];
        data->Music = pBuffer[0x02232];
        data->OptionsOn = pBuffer[0x174E7];
        data->OptionsOff = pBuffer[0x174E9];
        data->BossEvent = pBuffer[0x02256];
        data->XAxis = ((uint16_t)pBuffer[0x000E55] << 8) | (uint8_t)pBuffer[0x000E54];
        data->YAxis = ((uint16_t)pBuffer[0x000E59] << 8) | (uint8_t)pBuffer[0x000E58];

        notifyObservers();

        Sleep(100);
    }
}

//Cause a glitch in Rayman to prevent the next CDDA Track to be played. Useful for the Boss Event
bool GlitchMusic(bool enable) {
    if (worldBase == 1)
        return false;

    char b;
    if (enable) {
        b = 0;
        return WriteProcessMemory(phandle, (LPVOID)(worldBase + 0x02232), &b, sizeof(b), 0);
    }
    else {
        b = 1;
        return WriteProcessMemory(phandle, (LPVOID)(worldBase + 0x02232), &b, sizeof(b), 0);
    }
}