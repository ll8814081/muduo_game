#ifndef MUDUO_EXAMPLES_BAINAGAME_BUFFER_H
#define MUDUO_EXAMPLES_BAINAGAME_BUFFER_H

#include <string.h>
#include <stdint.h>
#include <map>
#include <vector>
#include <assert.h>
#include <string>

#ifndef _BIG_ENDIAN_
#define _LITTLE_ENDIAN_ 1
#endif

#if !_LITTLE_ENDIAN_
#define _BITSWAP16(x) (((x << 8) & 0xff00) | ((x >> 8) & 0x00ff))

#define _BITSWAP32(x) (((x << 24) & 0xff000000) | ((x <<  8) & 0x00ff0000) | \
	((x >>  8) & 0x0000ff00) | ((x >> 24) & 0x000000ff))

#define _BITSWAP64(x) (((x << 56) & 0xff00000000000000ULL) | ((x << 40) & 0x00ff000000000000ULL) | \
	((x << 24) & 0x0000ff0000000000ULL) | ((x <<  8) & 0x000000ff00000000ULL) | \
	((x >>  8) & 0x00000000ff000000ULL) | ((x >> 24) & 0x0000000000ff0000ULL) | \
	((x >> 40) & 0x000000000000ff00ULL) | ((x >> 56) & 0x00000000000000ffULL))
#else
#define _BITSWAP16(x) (x)
#define _BITSWAP32(x) (x)
#define _BITSWAP64(x) (x)
#endif


#define uint32 uint32_t
#define uint16 uint16_t
#define int16 int16_t
#define int32 int32_t
#define uint64 uint64_t
#define int64 int64_t
#define int8 int8_t
#define uint8 uint8_t

class BufferException
{
public:
	BufferException() {}
	virtual ~BufferException() throw() {}
};

enum IStreamBufferMode {
	IStreamBufferRead = 1 << 0,
	IStreamBufferWrite = 1 << 1,
	IStreamBufferReadAndWrite = IStreamBufferRead | IStreamBufferWrite,
};

class IStreamBuffer
{
	friend class BufferException;
	friend class CBitMask;

public:
	IStreamBuffer():_buff_size(0), _buff(NULL), _validate_size(0), _rpos(0), _wpos(0), _mode(IStreamBufferReadAndWrite)
	{
		//Clear(); 
		//_Resize(sizeof(_buff_internal)); 
	}
	virtual ~IStreamBuffer()
	{

		_Clear();
	};

	IStreamBuffer& operator= (const IStreamBuffer& r)
	{
		if (this != &r)
		{
			Clear();
			Resize(r._validate_size);
			_rpos = r._rpos;
			_wpos = r._wpos;
			memcpy(_buff, r._buff, r._validate_size);
		}
		return *this;
	};

public:
	virtual void Clear()				
	{ 
		_Clear();
	};
protected:
	virtual void _Resize(size_t newsize) = 0;
private:
	void _Clear()				
	{ 
		_validate_size = _rpos = _wpos = 0; 
		_buff = NULL;
		_buff_size = 0;
	};
public:
	uint8* Content() const		{ return _buff; }
	uint8* GetWriteBuffer(size_t size)
	{ 
		size_t pos = _wpos;
		_wpos += size;
		Resize(_wpos);
		return _buff + pos;
	}
	uint8* GetReadBuffer() const
	{ 
		//size_t pos = _rpos;
		//_rpos += size;
		return _buff + _rpos;
	};
	size_t GetRemainSize() const { return _validate_size - _rpos; }
	size_t Size() const			 { return _validate_size; }
	size_t BufferSize() const	 { return _buff_size; }
	
	void SkipRead(size_t size)   { _rpos += size; };
	void ResetPosRead()			 { _rpos = 0; }; //ATTENTION: please use this carefully, MS use the rpos to improve performance, any question please contact zhuj
	void SkipToEnd()			 { _rpos = _validate_size; };
	size_t PosRead() const		 { return _rpos; }

	void Append(const char *src, uint16 size) {const  void* tmp = src; Append(static_cast<const uint8 *>(tmp), size); }
	void Append(const uint8 *src, uint16 size) { if (size > 0) _Write(src, size); }

	size_t PosWrite() const		 { return _wpos; }
	bool CanRead() const		 { return _validate_size - _rpos > 0; }

	IStreamBuffer& operator<<(char value)	{ _Write<char>(value); return *this; }
	IStreamBuffer& operator>>(char &value) 	{ _Read<char>(value); return *this; }

	IStreamBuffer& operator<<(bool value)	{ _Write<bool>(value); return *this; }
	IStreamBuffer& operator>>(bool &value) 	{ _Read<bool>(value); return *this; }

	IStreamBuffer& operator<<(int8 value)	{ _Write<int8>(value); return *this; }
	IStreamBuffer& operator>>(int8 &value) 	{ _Read<int8>(value); return *this; }
	IStreamBuffer& operator<<(uint8 value) 	{ _Write<uint8>(value); return *this; }
	IStreamBuffer& operator>>(uint8 &value) { _Read<uint8>(value); return *this; }

	IStreamBuffer& operator<<(int16 value)	{ _Write<int16>(_BITSWAP16(value)); return *this; }
	IStreamBuffer& operator>>(int16 &value)	{ _Read<int16>(value); value = _BITSWAP16(value); return *this; }
	IStreamBuffer& operator<<(uint16 value)	{ _Write<uint16>(_BITSWAP16(value)); return *this; }
	IStreamBuffer& operator>>(uint16 &value){ _Read<uint16>(value); value = _BITSWAP16(value); return *this; }

	IStreamBuffer& operator<<(int32 value)	{ _Write<int32>(_BITSWAP32(value)); return *this; }
	IStreamBuffer& operator>>(int32 &value)	{ _Read<int32>(value); value = _BITSWAP32(value); return *this; }
	IStreamBuffer& operator<<(uint32 value)	{ _Write<uint32>(_BITSWAP32(value)); return *this; }
	IStreamBuffer& operator>>(uint32 &value){ _Read<uint32>(value); value = _BITSWAP32(value); return *this; }

	IStreamBuffer& operator<<(int64 value)	{ _Write<int64>(_BITSWAP64(value)); return *this; }
	IStreamBuffer& operator>>(int64 &value)	{ _Read<int64>(value); value = _BITSWAP64(value); return *this; }
	IStreamBuffer& operator<<(uint64 value)	{ _Write<uint64>(_BITSWAP64(value)); return *this; }
	IStreamBuffer& operator>>(uint64 &value){ _Read<uint64>(value); value = _BITSWAP64(value); return *this; }

    
	IStreamBuffer& operator<<(const char *value);
	IStreamBuffer& operator<<(const std::string &value);
	IStreamBuffer& operator>>(std::string &value);

	IStreamBuffer& operator<<(const IStreamBuffer& value) 
	{
		size_t size = value.Size();
		uint16 size_little_endian = static_cast<uint16>(_BITSWAP16(size));
		_Write<uint16>(size_little_endian);
		if( size > 0 )
		{
			_Write(value._buff, size);
		}
		return *this;
	};
	IStreamBuffer& operator>>(IStreamBuffer& value)
	{	
		uint16 size_little_endian = 0;
		_Read<uint16>(size_little_endian);
		uint16 size = _BITSWAP16(size_little_endian);
		if( size > 0 )
		{
			value.Resize(size + value._wpos);
			_Read(&value._buff[value._wpos], size);
			value._wpos += size;
		}
		return *this;
	};


    template<typename key_type, typename value_type> 
    IStreamBuffer& operator << (const std::map<key_type, value_type>& data)
    {
        this->operator << (data.size());
        for(typename std::map<key_type, value_type>::const_iterator it = data.begin(); 
            it != data.end(); ++ it)
        {
            this->operator << (it->first);
            this->operator << (it->second);
        }
        return *this;
    };
    template<typename key_type, typename value_type>
    IStreamBuffer& operator >> (std::map<key_type, value_type>& data)
    {
        data.clear();
        uint32 data_size;
        this->operator >> (data_size);
        for (uint32 idx = 0; idx < data_size; ++idx)
        {
            key_type key_data;
            value_type value_data;
            this->operator >> (key_data);
            this->operator >> (value_data);
            data.insert(std::make_pair(key_data, value_data));
        }
        return *this;
    };

	IStreamBuffer& operator<<(const float& value);
	IStreamBuffer& operator>>(float &value);

	//void PushUint32Array(const uint32* pArray, uint32 nCount);
	void Put(size_t pos, const uint8 *src, size_t cnt) { _Put(pos, src, cnt); };

	void Put(size_t pos, const int8& value)  {	_Put<int8>(pos,value ); }
	void Put(size_t pos, const int16& value) {	_Put<int16>(pos,_BITSWAP16(value) ); }
	void Put(size_t pos, const int32& value) {	_Put<int32>(pos,_BITSWAP32(value) ); }
	void Put(size_t pos, const int64& value) {	_Put<int64>(pos,_BITSWAP64(value) ); }
	void Put(size_t pos, const uint8& value)  {	_Put<uint8>(pos,value ); }
	void Put(size_t pos, const uint16& value) {	_Put<uint16>(pos,_BITSWAP16(value) ); }
	void Put(size_t pos, const uint32& value) {	_Put<uint32>(pos,_BITSWAP32(value) ); }
	void Put(size_t pos, const uint64& value) {	_Put<uint64>(pos,_BITSWAP64(value) ); }


protected:
	void Resize(size_t newsize) 
	{ 
		if (newsize > _buff_size)
		{
			_Resize(newsize); 
		}
		if (newsize > _validate_size) 
		{
			_validate_size = newsize; 
		}
	};
	virtual void _Write(const uint8 *src, size_t size);
	virtual void _Read(uint8 *dest, size_t size);
	virtual void _Put(size_t pos,const uint8* src, size_t size);
	void _DestroyBuff();

	template <typename T> void _Write(const T& value) 	{const void* ptr = &value;_Write(static_cast<const uint8*>(ptr), sizeof(T)); }
	template <typename T> void _Read(T &value)	{ void * ptr = &value; _Read(static_cast<uint8*>(ptr), sizeof(T)); }
	template <typename T> void _Put(size_t pos,const T &value)   { const void * ptr = &value;_Put(pos,static_cast<const uint8*>(ptr),sizeof(T) ); }

public:
	//static const size_t MAXSIZE = 0xffffffff;//0xffff; 
	void SetBufferMode(IStreamBufferMode mode) {
		_mode = mode;
	}

	IStreamBufferMode GetBufferMode() {
		return _mode;
	}

protected:
	size_t _buff_size;
	uint8 *_buff;

//private:
	size_t _validate_size;
	size_t _rpos;
	size_t _wpos;
	IStreamBufferMode _mode;
};


inline void IStreamBuffer::_Write(const uint8 *src, size_t size)
{
	//assert((0 <= size) && (_wpos + size <= MAXSIZE));
	if ((_mode & IStreamBufferWrite) == 0) {
		assert(_mode & IStreamBufferWrite);
		return;
	}

	Resize(_wpos + size);
	memcpy(&_buff[_wpos], src, size);
	_wpos += size;
}

inline void IStreamBuffer::_Read(uint8 *dest, size_t size)
{
	//assert((0 <= size) && (_rpos + size <= _validate_size));
	if ((_mode & IStreamBufferRead) == 0) {
		assert(_mode & IStreamBufferRead);
		return;
	}

	if (_rpos + size <= _validate_size)
	{
		memcpy(dest, &_buff[_rpos],  size);
		_rpos += size;
	}
	else
	{
		// Note: Only can an INetPacket be read once
		// Call ResetPosRead if you really need read more than once
		//THROW_EXCEPTION(BufferException());
	}
}

inline void IStreamBuffer::_Put(size_t pos, const uint8* src, size_t size)
{
	//assert((0 <= size) && (pos + size <= MAXSIZE));

	Resize(pos + size);
	memcpy(&_buff[pos], src, size);
}
//我们的windows的服务器上，汉字常量都是ansi，打包需要转换为utf8，网络上跑的是utf8
inline IStreamBuffer& IStreamBuffer::operator<<(const char *value)
{
#ifdef _SERVER_
	std::string utf8Value = AnsiToUTF8(value);
	value = utf8Value.c_str();
#endif
	size_t size = strlen(value);
	if(size > 1024*10)
	{
		assert(0);
		size = 1024*10;
	}
	uint16 size_little_endian = static_cast<uint16>(_BITSWAP16(size));
	_Write<uint16>(size_little_endian);	
	if ( size > 0)
	{
		const void *tmp = value;
		_Write(static_cast<const uint8*>(tmp), size);
	}
	return *this;
}


//我们的windows的服务器上，汉字常量都是ansi，打包需要转换为utf8，网络上跑的是utf8
inline IStreamBuffer& IStreamBuffer::operator<<(const std::string &value)
{
#ifdef _SERVER_
	std::string utf8Value = AnsiToUTF8(value);
#else
    std::string utf8Value = value;
#endif
	uint16 size = static_cast<uint16>(utf8Value.size());
	uint16 size_little_endian = _BITSWAP16(size); 
	_Write<uint16>(size_little_endian);
	if ( size > 0)
	{
		const void * tmp = utf8Value.data();	
		_Write(static_cast<const uint8*>(tmp), size);
		//		_Write((const uint8*)value.c_str(), size);
	}

	return *this;
}

inline IStreamBuffer& IStreamBuffer::operator>>(std::string &value)
{
	uint16 size_little_endian = 0;
	_Read<uint16>(size_little_endian);
	uint16 size = _BITSWAP16(size_little_endian);
	value.clear();
	if ( size > 0 && size <= GetRemainSize() )
	{
		value.clear();
		uint8* tmpBuf = new uint8[size];
		_Read(tmpBuf, size);
		void * buf = tmpBuf;
		value.append( static_cast<char*>(buf), size );
		delete [] tmpBuf;
		//value.resize(size);
		//_Read((uint8*)&value[0], size);
	}
    //对于windows的server，解包后是utf8，需要转换为ansi
#ifdef _SERVER_
    std::string ansiValue = UTF8ToAnsi(value);
    value = ansiValue;
#endif

	return *this;
}

#ifdef WIN32
#define IS_NAN(x) (_isnan(x) != 0)
#else
#define IS_NAN(x) (isnan(x) != 0)
#endif

inline IStreamBuffer& IStreamBuffer::operator<<(const float& value) 
{
	//if (IS_NAN(value))
	{
		//THROW_EXCEPTION(BufferException());
	}
#if _LITTLE_ENDIAN_
	_Write<float>(value);
#else
	uint32 tmp;
	tmp = *((uint32*)&value);
	//memcpy(&tmp, &value, 4);
	_Write<uint32>(_BITSWAP32(tmp));
#endif
	return *this;
}

inline IStreamBuffer& IStreamBuffer::operator>>(float& value) 
{
#if _LITTLE_ENDIAN_
	_Read<float>(value);
#else
	uint32 tmp = 0;
	_Read<uint32>(tmp); 
	tmp = _BITSWAP32(tmp);
	//value = *((float*)&tmp);
	memcpy(&value, &tmp, 4);
#endif
	//if (IS_NAN(value))
	{
		//THROW_EXCEPTION(BufferException());
	}
	return *this; 
}

//////////////////////////////////////////////////////////////////////////

template <uint32 default_size>
class CBuffer : public IStreamBuffer
{
public:
	CBuffer(){};
	virtual ~CBuffer(){ _Clear(); };
public:
	virtual void Clear()				
	{ 
		_Clear();
		IStreamBuffer::Clear();
	};

	CBuffer(const CBuffer& r)
	{
		Clear();
		IStreamBuffer::operator =(r);
	};

	CBuffer& operator= (const CBuffer& r)
	{
		if (this != &r)
		{
			Clear();
			IStreamBuffer::operator =(r);
		}
		return *this;
	};
protected:
	virtual void _Resize(size_t newsize)
	{
		if (_buff_size == 0)
		{
			_buff = &_buff_internal[0];
			_buff_size = sizeof(_buff_internal);
		}
		if (newsize > _buff_size)
		{
			newsize = (newsize > _buff_size * 2) ? newsize : (_buff_size * 2);
			uint8* new_buff = new uint8[newsize];
			if (_buff && Size() > 0)
			{
				memcpy(new_buff, _buff, Size());
			}
			if (_buff && _buff != &_buff_internal[0])
				delete [] _buff;
			_buff = new_buff;
			_buff_size = newsize;
		}
	};
private:
	void _Clear()				
	{ 
		if (_buff && _buff != &_buff_internal[0]) 
		{
			delete [] _buff; 
			_buff = NULL;
			_buff_size = 0;
		}
	};
protected:
	uint8 _buff_internal[default_size];
};

typedef CBuffer<256> Buffer;
/*
class FileBuffer :
	public CBuffer<4096>
{
public:
	FileBuffer(const char * szPath, const char * mode);
	~FileBuffer();

	void Flush();
	bool IsOpened() const;
	void Close();
	void SetBufferSize(int bufferSize);
	int GetBufferSize() const;
protected:
	virtual void _Write(const uint8 *src, size_t size);
	virtual void _Read(uint8 *dest, size_t size);
	virtual void _Put(size_t pos,const uint8* src, size_t size);

private:
	int				_rfilepos;
	int				_wfilepos;
	FILE *			_file;
	std::string		_mode;
	std::string		_path;
};
*/

#endif  // MUDUO_EXAMPLES_BAINAGAME_BUFFER_H
