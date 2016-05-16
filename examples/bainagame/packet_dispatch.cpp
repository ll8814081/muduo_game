#include "packet_dispatch.h"
#include "op_code.h"
#include "game_codec.h"
#include "net_packet.h"

#include <boost/bind.hpp>

using namespace muduo;
using namespace muduo::net;
using namespace muduo::net::sockets;

void PacketDispatch::init(){
	register_handle(CMSG_SERVER_CONFIG,boost::bind(&PacketDispatch::HandleGetServerConfig, this, _1, _2));
}

void PacketDispatch::register_handle(uint8_t opcode,PacketHandleCallback call_back){
	packet_handle_call_back_.insert(std::make_pair<uint16_t,PacketHandleCallback>(opcode,call_back));
}

void PacketDispatch::HandlePacket(const TcpConnectionPtr& conn,const INetPacket* packet){
	std::map<uint16_t,PacketHandleCallback>::iterator it =packet_handle_call_back_.find(packet->GetOpcode());
	if (it != packet_handle_call_back_.end()){
		it->second(conn,packet);
	}else{
		LOG_ERROR << "[PacketDispatch::HandlePacket]  opcode ["<<packet->GetOpcode()<<"]   has not handle function";
	}
	
}

void PacketDispatch::HandleGetServerConfig(const TcpConnectionPtr& conn,const INetPacket* packet){
	NetPacket p(SMSG_SERVER_CONFIG_RESP);
	p<<uint32_t(0);
	p << "172.18.254.254" ;
	p<<uint32_t(7011);
	p<<uint32_t(3);
	send_call_back_(get_pointer(conn),p);	
}



