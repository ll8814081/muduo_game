#include "game_codec.h"
#include "packet_dispatch.h"

#include <muduo/base/Logging.h>
#include <muduo/base/Mutex.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/TcpServer.h>

#include <boost/bind.hpp>

#include <set>
#include <stdio.h>


using namespace muduo;
using namespace muduo::net;

class GameServer : boost::noncopyable
{
 public:
  GameServer(EventLoop* loop,
             const InetAddress& listenAddr)
  : server_(loop, listenAddr, "GameServer"),
    codec_(boost::bind(&GameServer::onStringMessage, this, _1, _2, _3))
  {
    server_.setConnectionCallback(
        boost::bind(&GameServer::onConnection, this, _1));
    server_.setMessageCallback(
        boost::bind(&BainaCodec::onMessage, &codec_, _1, _2, _3));
	packet_handle_.setSendCallBack(
		boost::bind(&BainaCodec::send, &codec_, _1, _2));
  }

  void start()
  {
	packet_handle_.init();
    server_.start();
  }

 private:
  void onConnection(const TcpConnectionPtr& conn)
  {
    LOG_INFO << conn->localAddress().toIpPort() << " -> "
             << conn->peerAddress().toIpPort() << " is "
             << (conn->connected() ? "UP" : "DOWN");

    if (conn->connected())
    {
      connections_.insert(conn);
    }
    else
    {
      connections_.erase(conn);
    }
  }

  void onStringMessage(const TcpConnectionPtr& ptr,
								INetPacket* packet,
                       Timestamp)
  {
	handlePacket(ptr,packet);
  }

  void handlePacket(const TcpConnectionPtr& ptr,const INetPacket* packet)
  {
	if(packet->GetOpcode()!=3){
LOG_INFO<<"[GameServer::handlePacket]   "<<packet->GetOpcode()<<" get  and handle";
}
	  packet_handle_.HandlePacket(ptr,packet);

  }
  
  typedef std::set<TcpConnectionPtr> ConnectionList;
  TcpServer server_;
  BainaCodec codec_;
  PacketDispatch packet_handle_;
  ConnectionList connections_;
};

int main(int argc, char* argv[])
{
  LOG_INFO << "pid = " << getpid();
  if (argc > 1)
  {
    EventLoop loop;
    uint16_t port = static_cast<uint16_t>(atoi(argv[1]));
    InetAddress serverAddr(port);
    GameServer server(&loop, serverAddr);
    server.start();
    loop.loop();
  }
  else
  {
    printf("Usage: %s port\n", argv[0]);
  }
}

