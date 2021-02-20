#include<iostream>
#include <boost/asio.hpp>
#include <thread>
#include "smncpp/socket_mtd.h"
#include "smncpp/base_asio_socket.h"
#include "smncpp/asio_server.h"
#include "ric_code/pb/rip_rpc_itf.pb.h"
#include "ric_code/pb/smn_base.pb.h"
#include "ric_code/pb/smn_dict.pb.h"
#include "ric_code/rpc_itf.Login.h"
#include "ric_code/rpc_itf.svr.Login.h"
#include "ric_code/rpc_itf.clt.Login.h"
#include "smncpp/ticker.h"

using namespace std;
using namespace boost::asio;

class Login: public rpc_itf::Login{
public:
	rip_rpc_itf::Login_DoLogin_Ret DoLogin(const std::string& user, const std::string& pswd, int64_t code)override  {
		cout << "Hello " << user << " whose pswd = " << pswd<<endl;
		return rip_rpc_itf::Login_DoLogin_Ret();
	}

	std::vector<int64_t> Test1(const std::vector<std::string>& a, const std::vector<int64_t>& b, const std::vector<uint64_t>& c, const std::vector<uint64_t>& d, const std::vector<int32_t>& e) override {
		throw std::runtime_error("a runtime error");
	} 

	bool Test2(const std::string& key, std::shared_ptr<smnet::Conn>  c) override{
		if (key == "hello"){
			smnet::writeString(c, "hahahahahaha");
		}else{
			smnet::writeString(c, "hehehehe");
		}
		return true;
	}
};


shared_ptr<svr_rpc_rpc_itf::Login> NewLoginServer(ip::tcp::socket sock){
	return make_shared<svr_rpc_rpc_itf::Login>(std::move(sock), make_shared<Login>());
}

void run_server(){
	io_service ioc;
	smnet::Server s(ioc, 1000, NewLoginServer);
	s.start();
	ioc.run();
}

void run_client(){
	io_service ioc;
	ip::tcp::socket sock(ioc);
	ip::tcp::endpoint ep(ip::address::from_string("127.0.0.1"), 1000);
	sock.connect(ep);
	
	clt_rpc_rpc_itf::Login client(make_shared<smnet::SMConn>(std::move(sock)));
	client.Test2("helo", [](std::shared_ptr<smnet::Conn> c){
			std::string str;
			smnet::readString(c, str);

			cout << str <<endl;
			return 0;
			});
	client.Test2("hello", [](std::shared_ptr<smnet::Conn> c){
			std::string str;
			smnet::readString(c, str);
			cout << str <<endl;
			return 0;
			});
	ioc.run();

}

int main(){
	thread t(run_server);
	smnet::sleep(1000);
	run_client();
	t.detach();
}
