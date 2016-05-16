#ifndef MUDUO_EXAMPLES_BAINAGAME_NET_PACKET_H
#define MUDUO_EXAMPLES_BAINAGAME_NET_PACKET_H

#include <string.h>
#include <stdint.h>
#include "buffer.h"
#include <muduo/base/Atomic.h>

#ifndef MAX
#define MAX(a, b)						((a) > (b) ? (a) : (b))
#endif

#ifndef MIN
#define MIN(a, b)						((a) < (b) ? (a) : (b))
#endif


#pragma pack(push, 4)

#define ENABLE_HEAD_CHECK 1

#if ENABLE_HEAD_CHECK
struct NetPacketHeaderChecker
{
	const static uint32 FLAG = _BITSWAP32(0x12345678);
	NetPacketHeaderChecker() : HEADER_FLAG(FLAG) {};
	bool Check()
	{
		return (HEADER_FLAG == FLAG);
	};

	uint32 HEADER_FLAG;
};
#define PACKET_HEADER_CHECHER_SIZE sizeof(NetPacketHeaderChecker)

#endif

struct NetPacketHeader
{
	uint16 size;
	uint16 cmd;
};

#define PACKET_HEADER_SIZE sizeof(NetPacketHeader)

#pragma pack(pop)


#define PACKET_NEW new
#define PACKET_DELETE delete
#ifndef SAFE_DELETE
#define SAFE_DELETE(p)			if (p) { delete p; p = NULL; }
#endif
class LocationVector;
class INetPacket;

void InitNetPackPools();
void ClearNetPackPools();

#if 0
#define NEW_NETPACKET(size, opcode) (new NetPacket(opcode))
#else
inline INetPacket* NEW_NETPACKET(uint32 size, uint16 opcode);
#endif

class INetPacket : public IStreamBuffer
{
public:
	INetPacket() :_opcode(0) 
	{
		s_total_cnt.increment();
	};
	INetPacket(uint16 opcode) :_opcode(opcode) 
	{
		s_total_cnt.increment();
	};
	//NetPacket(const NetPacket& pck) : CBuffer<PAK_SIZE>(pck), _opcode(pck._opcode) {};
	virtual ~INetPacket() 
	{
		s_total_cnt.decrement();
	};

public:
	uint16 GetOpcode() const		
	{ 
		return _opcode; 
	};
	void SetOpcode(uint16 opcode)
	{
		_opcode = opcode;
	};
	//TODO:need optimize
	void WritePacket(const INetPacket& r);
	INetPacket * ReadPacket(INetPacket* r = NULL);
	INetPacket * UnPackPacket();
	void ReadPacket(INetPacket& r)
	{
		ReadPacket(&r);
	};
	INetPacket * CopyNew() const;

	static void Free(INetPacket *& pck) {PACKET_DELETE pck;};
public:
	muduo::AtomicInt64 s_total_cnt;
private:
	uint16 _opcode;
	//uint16 _reserve;
};


template <uint32 default_size>
class CNetPacket : public INetPacket
{
#ifdef MONKEY
	#define MAX_POOL_MEM 0
	#define MAX_POOL_COUNT 0
#elif defined _SERVER_
	#define MAX_POOL_MEM (8*1024*1024) //8M
	#define MAX_POOL_COUNT 4096
#else
	//#define MAX_POOL_MEM (2*1024) //2K
	#define MAX_POOL_MEM (0) //2K
	#define MAX_POOL_COUNT 16
#endif

#if (MAX_POOL_MEM > 0)
public:
	static void * operator new(size_t size, int block = 0, const char * file_name = NULL, int line = 0)
	{
		void * p = s_packet_pool.Get();// NULL;
		if (p == NULL)
		{
			p = ::operator new(size);
			if (AtomicIncrement(&s_cur_cnt) > s_max_cnt)
			{
				s_max_cnt = s_cur_cnt;
			}
		}
		return p;
	};

	static void operator delete(void * p)
	{
		if (p != NULL)
		{
			if (s_packet_pool.Put((CNetPacket *)p))
			{
			}
			else
			{
				::operator delete(p);
				AtomicDecrement(&s_cur_cnt);
			}
		}
	};

	static void operator delete(void * p, int block, const char * file_name, int line)
	{
		CNetPacket::operator delete(p);
	};
private:
	friend void InitNetPackPools();
	friend void ClearNetPackPools();
	static const unsigned int s_max_pool_cnt = MAX(MIN((uint32)(MAX_POOL_MEM/default_size), (uint32)MAX_POOL_COUNT), 1);
	static ThreadSafePool<CNetPacket<default_size>, CNetPacket<default_size>::s_max_pool_cnt> s_packet_pool;
	static void InitPool()
	{
	};
	static void ClearPool()
	{
		void * p = NULL;
		while(!s_packet_pool.IsEmpty())
		{
			p = s_packet_pool.Get();
			::operator delete(p);
			p = NULL;
		}
	};

	static volatile long s_max_cnt, s_cur_cnt;
#endif

public:
	CNetPacket() {};
	CNetPacket(uint16 opcode) :INetPacket(opcode) {};
	virtual ~CNetPacket() { _Clear(); };

public:
	virtual void Clear()				
	{ 
		_Clear();
		IStreamBuffer::Clear();
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
		}
	};
private:
	uint8 _buff_internal[default_size];
};

#if (MAX_POOL_MEM > 0)
template <uint32 default_size> 
	ThreadSafePool<CNetPacket<default_size>, CNetPacket<default_size>::s_max_pool_cnt> CNetPacket<default_size>::s_packet_pool;

template <uint32 default_size> 
	volatile long CNetPacket<default_size>::s_max_cnt;

template <uint32 default_size> 
	volatile long CNetPacket<default_size>::s_cur_cnt;
#endif

typedef CNetPacket<256> NetPacket;

#ifndef NEW_NETPACKET
inline INetPacket* NEW_NETPACKET(uint32 size, uint16 opcode)
{
	if (size <= 1024)
	{
		if (size <= 32) 
			return PACKET_NEW CNetPacket<32>(opcode);
		if (size <= 64) 
			return PACKET_NEW CNetPacket<64>(opcode);
		if (size <= 128) 
			return PACKET_NEW CNetPacket<128>(opcode);
		if (size <= 256) 
			return PACKET_NEW CNetPacket<256>(opcode);
		if (size <= 512) 
			return PACKET_NEW CNetPacket<512>(opcode);
		return PACKET_NEW CNetPacket<1024>(opcode);
	}
	if (size <= 4096) 
		return PACKET_NEW CNetPacket<4096>(opcode);
	if (size <= 8192) 
		return PACKET_NEW CNetPacket<8192>(opcode);
	if (size <= 32768) 
		return PACKET_NEW CNetPacket<32768>(opcode);

	return PACKET_NEW CNetPacket<65536>(opcode);
};
#endif
//class NetPacket : public CNetPacket<256>
//{
//public:
//	NetPacket() {};
//	NetPacket(uint16 opcode) :CNetPacket<256>(opcode) {};
//	virtual ~NetPacket() {};
//};

#undef MAX
#undef MIN

#endif //MUDUO_EXAMPLES_BAINAGAME_NET_PACKET_H