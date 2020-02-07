#include <SFML\Audio.hpp>

#ifndef FSTREAM_H
#define FSTREAM_H

using namespace sf;

//Point of this Subclass is, to get a stream of one file from a package/container
//See PackageBuilder.h to see how a package is built
class FileSeekStream : public InputStream, NonCopyable {
private:
	Int64 maxPos = 0;
	Int64 length = 0;
	Int64 offset = 0;
	Int64 result = 0;
	FileInputStream innerStream;

public:
	FileSeekStream();
	FileSeekStream(const char* path, Int64 offset, Int64 length);
	Int64 read(void* data, Int64 size);
	Int64 seek(Int64 position);
	Int64 tell();
	Int64 getSize();
	bool setData(const char* path, Int64 offset, Int64 length);
};
#endif