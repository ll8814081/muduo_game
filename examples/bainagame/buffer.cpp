#include "buffer.h"

#ifndef MIN
#define MIN(a, b)						((a) < (b) ? (a) : (b))
#endif
/*
void FileBuffer::SetBufferSize(int bufferSize)
{
	if (bufferSize > _buff_size)
	{
		Resize(bufferSize);
	}
}

int FileBuffer::GetBufferSize() const
{
	return (int)_buff_size;
}

FileBuffer::FileBuffer( const char * szPath, const char * mode )
: _path(szPath)
, _mode(mode)
, _file(fopen(szPath, mode))
, _rfilepos(0)
, _wfilepos(0)
{
	Resize(4096);
}

FileBuffer::~FileBuffer()
{
	Close();
}

bool FileBuffer::IsOpened() const
{
	return _file != NULL;
}

void FileBuffer::Close()
{
	if (_file != NULL)
	{
		Flush();
		fclose(_file);
		_file = NULL;
	}
}


inline void FileBuffer::_Write(const uint8 *src, size_t size)
{
	//assert((0 <= size) && (_wpos + size <= MAXSIZE));
	size_t bytesToCopy = size;
	size_t bytesCopied = 0;
	while(bytesToCopy > 0)
	{
		size_t copy_size = MIN(_buff_size - _wpos, bytesToCopy);
		memcpy(&_buff[_wpos], src + bytesCopied, copy_size);
		bytesCopied += copy_size;
		bytesToCopy -= copy_size;
		_wpos += copy_size;
		_wfilepos += copy_size;
		if (_wpos == _buff_size)
		{
			fwrite(_buff, sizeof(uint8), _wpos,  _file);
			_wpos = 0;
		}
	}

}

inline void FileBuffer::_Read(uint8 *dest, size_t size)
{
	//assert((0 <= size) && (_rpos + size <= _validate_size));
	size_t bytesToRaed = size;
	size_t bytesRead = 0;
	while (bytesToRaed > 0)
	{
		if (_rfilepos == ftell(_file))
		{
			_validate_size = fread(_buff, sizeof(uint8), _buff_size, _file);
			if (0 == _validate_size)
			{
				THROW_EXCEPTION(BufferException());
			}
			_rpos = 0;
		}
		size_t copy_size = MIN(_validate_size - _rpos, bytesToRaed);
		memcpy(dest + bytesRead, &_buff[_rpos],  copy_size);
		_rpos += copy_size;
		_rfilepos += copy_size;
		bytesRead += copy_size;
		bytesToRaed -= copy_size;
	}
}

inline void FileBuffer::_Put(size_t pos, const uint8* src, size_t size)
{
	//assert((0 <= size) && (pos + size <= MAXSIZE));
	Flush();
	fseek(_file, pos, SEEK_SET);
	_wfilepos = (int)pos;
	_wpos = 0;
	_Write(src, size);
}

void FileBuffer::Flush()
{
	if (_file != NULL && _wpos != 0)
	{
		fwrite(_buff, sizeof(uint8), _wpos,  _file);
		fflush(_file);
		_wpos = 0;
	}
}
*/
#undef MIN
