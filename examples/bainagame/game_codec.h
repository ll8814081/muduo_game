#ifndef MUDUO_EXAMPLES_ASIO_CHAT_CODEC_H
#define MUDUO_EXAMPLES_ASIO_CHAT_CODEC_H
#include "net_packet.h"
#include <muduo/base/Logging.h>
#include <muduo/net/Buffer.h>
#include <muduo/net/Endian.h>
#include <muduo/net/TcpConnection.h>
#include <boost/function.hpp>
#include <boost/noncopyable.hpp>

class BainaCodec : boost::noncopyable
{
 public:
  typedef boost::function<void (const muduo::net::TcpConnectionPtr&,
								INetPacket* packet,
                                muduo::Timestamp)> StringMessageCallback;

  explicit BainaCodec(const StringMessageCallback& cb)
    : messageCallback_(cb)
  {
  }

  void onMessage(const muduo::net::TcpConnectionPtr& conn,
                 muduo::net::Buffer* buf,
                 muduo::Timestamp receiveTime)
  {
    while (buf->readableBytes() >= kHeaderLen) // kHeaderLen == 4
    {
      const void* data = buf->peek();
      uint16_t be16 = *static_cast<const uint16_t*>(data); // SIGBUS
      const uint16_t len = be16;
      if ( len == 0)
      {
        LOG_ERROR << "Invalid length " << len;
        conn->shutdown();  
        break;
      }
      else if (buf->readableBytes() >= len)
      {
        buf->retrieve(kSizeLen);
		uint16_t packet_size = static_cast<uint16_t>(len-kSizeLen);
		INetPacket* packet = makePacket(buf,packet_size);
        messageCallback_(conn, packet, receiveTime);
		if (packet!=NULL)
		{
			delete packet;
			packet =NULL;
		}
        buf->retrieve(len-kHeaderLen);
      }
      else
      {
        break;
      }
    }
  }
  
  INetPacket* makePacket(muduo::net::Buffer* buf,uint16_t len)
  {
	const void* data = buf->peek();
	uint16_t be16 = *static_cast<const uint16_t*>(data); 
	const uint16_t op_code = be16;
	uint32_t buff_size = static_cast<uint32_t>(len-kOpcodeLen);
	INetPacket* packet = NEW_NETPACKET(buff_size, op_code);
	buf->retrieve(kOpcodeLen);
 	return packet; 
  }

  void send(muduo::net::TcpConnection* conn,
	  const INetPacket& packet)
  {
	  muduo::net::Buffer buf;
	  uint16_t size = static_cast<uint16_t>(packet.Size()+BainaCodec::kHeaderLen);
	  uint16_t op_code = packet.GetOpcode();
	  void* ptr_size =&size;
	  void* ptr_opcode =&op_code;
	  void* ptr_content = static_cast<void*>(packet.GetReadBuffer());
	  buf.append(ptr_size,sizeof(uint16_t));
	  buf.append(ptr_opcode,sizeof(uint16_t));
	  buf.append(ptr_content, packet.GetRemainSize());
	  conn->send(&buf);
  }


 private:
  StringMessageCallback messageCallback_;

public:
  const static size_t kHeaderLen = sizeof(uint16_t)+sizeof(uint16_t);
  const static size_t kOpcodeLen =sizeof(uint16_t);
  const static size_t kSizeLen = sizeof(uint16_t);
};

#endif  // MUDUO_EXAMPLES_ASIO_CHAT_CODEC_H
