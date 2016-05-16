
#ifndef MUDUO_EXAMPLES_BAINAGAME_PACKET_DISPATCH_H
#define MUDUO_EXAMPLES_BAINAGAME_PACKET_DISPATCH_H


#include "net_packet.h"
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <muduo/net/TcpConnection.h>

using namespace muduo;
using namespace muduo::net;

typedef boost::function<void (const TcpConnectionPtr&,const INetPacket*)> PacketHandleCallback;

typedef boost::function<void (muduo::net::TcpConnection* conn,
							  const INetPacket& packet)> SendCallback;
class PacketDispatch{


public:
	void init();
	void register_handle(uint8_t opcode,PacketHandleCallback call_back);
	void HandlePacket(const TcpConnectionPtr& ptr,const INetPacket* packet);
	void setSendCallBack(const SendCallback& cb){
		send_call_back_ = cb;
	}
public:
	void HandleGetServerConfig(const TcpConnectionPtr& ptr,const INetPacket* packet);




private:
	//void send(TcpConnection* conn,const INetPacket& packet);
private:
	std::map<uint16_t,PacketHandleCallback>  packet_handle_call_back_;	
	SendCallback send_call_back_;
	
};

#endif  //MUDUO_EXAMPLES_BAINAGAME_PACKET_DISPATCH_H
