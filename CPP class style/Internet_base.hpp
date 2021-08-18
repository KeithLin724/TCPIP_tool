#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS 1  

#ifndef INTERNET_BASE_HPP
#define INTERNET_BASE_HPP

#pragma comment(lib,"ws2_32.lib")
#include <WS2tcpip.h>
#include <string>
#define This (*this)

namespace _internet_base {
	enum Internet_msg {
		//
		_SUCCESS_ = 0,
		//
		_START_WINSOCK_ERROR_ = -1,
		_OPEN_WINSOCK_ERROR_ = -2,
		_SET_ASYNCHRONIZED_MODE_ERROR_ = -3,
		_OPEN_SOCKET_LISTENER_ERROR_ = -4,
		_OPEN_SOCKET_CONNECTER_ERROR = -5,
		_OPEN_SOCKET_BIND_ERROR_ = -6
	};

	class Internet_base {
	protected:
		WSADATA  wsadata;
		sockaddr_in tcp_udp;
		struct Internet_mode {
			const long TCP = (FD_CONNECT | FD_WRITE | FD_READ | FD_CLOSE);
			const long UDP = (FD_READ);
		} Mode;
		int err;

	protected:
		std::string API_ErrMsg;
		void WSA_Get_ErrTxt(std::string S1) {}

		//for son constructor
		Internet_base(WSADATA& wasdata); 
		Internet_base(WSADATA& wasdata, int err);
		Internet_base(WSADATA& wasdata, sockaddr_in& tcp_udp);

		//internet function 
		int start_Winsock();

	public:
		Internet_base();
		//set 
		void set_wsadata(WSADATA& wsadata);
		void set_tcp_udp(sockaddr_in& tcp_udp);

		//smart_set 
		void smart_set(WSADATA& wsadata);
		void smart_set(sockaddr_in& tcp_udp);

		// get
		WSADATA& get_wsadata();
		int get_err();
		sockaddr_in& get_tcp_udp();
	};

	Internet_base::Internet_base() { // init 
		This.wsadata = {};
		This.err = 0;
		This.tcp_udp = {};
	}

	Internet_base::Internet_base(WSADATA& wasdata) {
		This.wsadata = wasdata; 
		This.err = 0;
		This.tcp_udp = {};
	}
	Internet_base::Internet_base(WSADATA& wasdata, int err) {
		This.wsadata = wasdata;
		This.err = err;
		This.tcp_udp = {};
	}
	Internet_base::Internet_base(WSADATA& wasdata, sockaddr_in& tcp_udp) {
		This.wsadata = wasdata;
		This.err = 0;
		This.tcp_udp = tcp_udp;
	}

	int Internet_base::start_Winsock() {
		if ((This.err = WSAStartup(0x202, &This.wsadata)) != 0) {
			This.WSA_Get_ErrTxt(This.API_ErrMsg);
			return _START_WINSOCK_ERROR_;
		}
		return _SUCCESS_;
	}

	//set
	void Internet_base::set_wsadata(WSADATA& wsadata) {
		This.wsadata = wsadata;
	}
	void Internet_base::set_tcp_udp(sockaddr_in& tcp_udp) {
		This.tcp_udp = tcp_udp;
	}

	//smart set 

	void Internet_base::smart_set(WSADATA& wsadata) {
		This.set_wsadata(wsadata); 
	}
	void Internet_base::smart_set(sockaddr_in& tcp_udp) {
		This.set_tcp_udp(tcp_udp); 
	}

	// get
	WSADATA& Internet_base::get_wsadata() {
		return This.wsadata;
	}
	int Internet_base::get_err() {
		return This.err;
	}
	sockaddr_in& Internet_base::get_tcp_udp() {
		return This.tcp_udp;
	}

	class Internet_base_plug : public Internet_base {
	private:
		SOCKET psockfd;
		WORD Port;
		DWORD EVENT;
		HWND Hwnd;
	protected:
		int open_Winsock();
		int Set_Asynchronized_Mode(long l_Mode);
		void set_Socket_nameing(u_long S_addr);
		void set_Socket_nameing(std::string IP);

		int open_socket_bind();
		int open_socket_listener();
		int open_socket_connecter();

	public:
		Internet_base_plug();
		Internet_base_plug(SOCKET& psockfd, WORD& Port, DWORD& EVENT, HWND& Hwnd);
		~Internet_base_plug();

		// set 
		void set_all(SOCKET& psockfd , WORD& Port , DWORD& EVENT, HWND& Hwnd);
		void set_socket(SOCKET& psockfd);
		void set_port(WORD& Port);
		void set_event(DWORD& EVENT);
		void set_Hwnd(HWND& Hwnd);

		// get 
		SOCKET& get_socket();
		WORD& get_port();
		DWORD& get_Event();
		HWND& get_Hwnd();


		//smart_set() 
		/*void smart_set(SOCKET& psockfd, WORD& Port, DWORD& EVENT, HWND& Hwnd);
		void smart_set(SOCKET& psockfd);
		void smart_set(WORD& Port);
		void smart_set(DWORD& EVENT);
		void smart_set(HWND& Hwnd);*/

	};

	Internet_base_plug::Internet_base_plug() {
		This.psockfd = {};
		This.Port = {};
		This.EVENT = {};
		This.Hwnd = {};
	}

	Internet_base_plug::Internet_base_plug(SOCKET& psockfd, WORD& Port, DWORD& EVENT, HWND& Hwnd) {
		This.psockfd = psockfd;
		This.Port = Port;
		This.EVENT = EVENT;
		This.Hwnd = Hwnd;
	}


	Internet_base_plug::~Internet_base_plug() {

	}

	int Internet_base_plug::open_Winsock() {
		if ((This.psockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
			This.WSA_Get_ErrTxt(This.API_ErrMsg);
			return _OPEN_WINSOCK_ERROR_;
		}
		return _SUCCESS_;
	}

	int Internet_base_plug::Set_Asynchronized_Mode(long l_Mode) {
		if ((This.err = WSAAsyncSelect(This.psockfd, This.Hwnd, This.EVENT, l_Mode)) < 0) {
			This.WSA_Get_ErrTxt(This.API_ErrMsg);
			return _SET_ASYNCHRONIZED_MODE_ERROR_;
		}
		return _SUCCESS_;
	}

	void Internet_base_plug::set_Socket_nameing(u_long S_addr) {
		This.tcp_udp.sin_family = AF_INET;
		This.tcp_udp.sin_port = htons(This.Port);
		This.tcp_udp.sin_addr.s_addr = S_addr;
	}
	void Internet_base_plug::set_Socket_nameing(std::string IP) {
		This.tcp_udp.sin_family = AF_INET;
		This.tcp_udp.sin_port = htons(This.Port);
		inet_pton(AF_INET, IP.c_str(), &This.tcp_udp.sin_addr.s_addr);
		//InetPton(AF_INET, IP.c_str(), &This.tcp_udp.sin_addr.s_addr);
	}

	int Internet_base_plug::open_socket_bind() {
		if (bind(This.psockfd, (sockaddr*)&This.tcp_udp, sizeof(This.tcp_udp)) < 0) {
			This.WSA_Get_ErrTxt(This.API_ErrMsg);
			return _OPEN_SOCKET_BIND_ERROR_;
		}
		return _SUCCESS_;
	}
	int Internet_base_plug::open_socket_listener() {
		if ((This.err = listen(This.psockfd, SOMAXCONN)) < 0) {
			This.WSA_Get_ErrTxt(This.API_ErrMsg);
			return _OPEN_SOCKET_LISTENER_ERROR_;
		}
		return _SUCCESS_;
	}
	int Internet_base_plug::open_socket_connecter() {
		if (This.err = connect(This.psockfd, (sockaddr*)&This.tcp_udp, sizeof(This.tcp_udp)) < 0) {
			This.WSA_Get_ErrTxt(This.API_ErrMsg);
			return _OPEN_SOCKET_CONNECTER_ERROR;
		}
		return _SUCCESS_;
	}
	//set
	void Internet_base_plug::set_all(SOCKET& psockfd, WORD& Port, DWORD& EVENT, HWND& Hwnd) {
		This.psockfd = psockfd; 
		This.Port = Port; 
		This.EVENT = EVENT;
		This.Hwnd = Hwnd; 
	}

	void Internet_base_plug::set_socket(SOCKET& psockfd) {
		This.psockfd = psockfd;
	}
	void Internet_base_plug::set_port(WORD& Port) {
		This.Port = Port;
	}
	void Internet_base_plug::set_event(DWORD& EVENT) {
		This.EVENT = EVENT;
	}
	void Internet_base_plug::set_Hwnd(HWND& Hwnd) {
		This.Hwnd = Hwnd;
	}

	/*void Internet_base_plug::smart_set(SOCKET& psockfd, WORD& Port, DWORD& EVENT, HWND& Hwnd) {
		This.set_all(psockfd, Port, EVENT, Hwnd); 
	}
	void Internet_base_plug::smart_set(SOCKET& psockfd) {
		This.set_socket(psockfd); 
	}
	void Internet_base_plug::smart_set(WORD& Port) {
		This.set_port(Port); 
	}
	void Internet_base_plug::smart_set(DWORD& EVENT) {
		This.set_event(EVENT); 
	}
	void Internet_base_plug::smart_set(HWND& Hwnd) {
		This.set_Hwnd(Hwnd); 
	}*/

	// get 
	SOCKET& Internet_base_plug::get_socket() {
		return This.psockfd;
	}
	WORD& Internet_base_plug::get_port() {
		return This.Port;
	}
	DWORD& Internet_base_plug::get_Event() {
		return This.EVENT;
	}
	HWND& Internet_base_plug::get_Hwnd() {
		return This.Hwnd;
	}
}


#endif // !INTERNET_BASE_HPP
