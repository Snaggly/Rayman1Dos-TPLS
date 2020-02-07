#include <SFML\Audio.hpp>
#include "FileSeekStream.h"

using namespace sf;

FileSeekStream::FileSeekStream() { }

//When initialized, innerStream is opened and moved to the offset where the file to be streamed from lies.
FileSeekStream::FileSeekStream(const char* path, Int64 offset, Int64 length) {
	this->length = length;
	this->offset = offset;
	this->maxPos = offset + length;
	innerStream.open(path);
	innerStream.seek(offset);
}

Int64 FileSeekStream::read(void* data, Int64 size) {
	return innerStream.read(data, size);
}

Int64 FileSeekStream::seek(Int64 position) {
	result = innerStream.seek(offset + position);
	if (result > maxPos)
		return -1;
	return result - offset;
}

//Mocks the position of the stream
Int64 FileSeekStream::tell() {
	result = innerStream.tell() - offset;
	if (result < 0 || result > length)
		return -1;
	return result;
}

Int64 FileSeekStream::getSize() {
	return length;
}

//Alternative to a constructor
bool FileSeekStream::setData(const char* path, Int64 offset, Int64 length)
{
	this->offset = offset;
	this->length = length;
	this->maxPos = offset + length;
	if (!innerStream.open(path))
		return false;
	innerStream.seek(offset);
	return true;
}
