#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS 1  

#ifndef TCPIP_HPP
#define TCPIP_HPP

#include "Internet_base.hpp"

#ifdef INTERNET_BASE_HPP 

#define _Internet_msg _internet_base::Internet_msg
#define _Internet_base_plug _internet_base::Internet_base_plug

namespace Internet {

	class TCP_Server :public _Internet_base_plug {
	private:
		const std::string name = "TCP_Server";

	protected:
		std::string get_class_name();
		
	public:
		TCP_Server(); 
		TCP_Server(SOCKET& psockfd, WORD& Port, DWORD& EVENT, HWND& Hwnd);
		~TCP_Server();
		int start();
	};
	TCP_Server::TCP_Server() :Internet_base_plug(){

	}
	TCP_Server::TCP_Server(SOCKET &psockfd , 
		WORD &Port,
		DWORD& EVENT , 
		HWND& Hwnd) 
		:Internet_base_plug(psockfd , Port , EVENT , Hwnd){
		
	}

	std::string TCP_Server::get_class_name() {
		return This.name;
	}

	int TCP_Server::start() {
		if (This.start_Winsock() == _Internet_msg::_START_WINSOCK_ERROR_) {
			return _Internet_msg::_START_WINSOCK_ERROR_;
		}
		if (This.open_Winsock() == _Internet_msg::_OPEN_WINSOCK_ERROR_) {
			return _Internet_msg::_OPEN_WINSOCK_ERROR_;
		}
		if (This.Set_Asynchronized_Mode(This.Mode.TCP) == _Internet_msg::_SET_ASYNCHRONIZED_MODE_ERROR_) {
			return _Internet_msg::_SET_ASYNCHRONIZED_MODE_ERROR_;
		}
		This.set_Socket_nameing(htonl(INADDR_ANY));
		if (This.open_socket_bind() == _Internet_msg::_OPEN_SOCKET_BIND_ERROR_) {
			return _Internet_msg::_OPEN_SOCKET_BIND_ERROR_;
		}
		if (This.open_socket_listener() == _Internet_msg::_OPEN_SOCKET_LISTENER_ERROR_) {
			return _Internet_msg::_OPEN_SOCKET_LISTENER_ERROR_;
		}
		return _Internet_msg::_SUCCESS_;
	}

	TCP_Server::~TCP_Server() {
	}


	class TCP_Client :public _Internet_base_plug {
	private:
		const std::string name = "TCP_Client";
		std::string IP;

	protected:

		std::string get_class_name();
		
	public:
		TCP_Client(); 
		TCP_Client(std::string IP); 
		TCP_Client(SOCKET& psockfd, WORD& R_Port, std::string& IP, DWORD& EVENT, HWND& Hwnd);
		~TCP_Client();
		int start();

		void set_all(SOCKET& psockfd, WORD& R_Port, std::string& IP, DWORD& EVENT, HWND& Hwnd);
		void set_IP(std::string IP);
		
		std::string get_IP();
	};

	TCP_Client::TCP_Client():Internet_base_plug(){

	}

	TCP_Client::TCP_Client(std::string IP):Internet_base_plug() {
		This.IP = IP;
	}

	TCP_Client::TCP_Client(SOCKET& psockfd, 
		WORD& R_Port, 
		std::string& IP, 
		DWORD& EVENT,
		HWND& Hwnd) 
		:Internet_base_plug(psockfd, R_Port, EVENT, Hwnd) {
		This.IP = IP; 
	}

	TCP_Client::~TCP_Client() {

	}
	std::string TCP_Client::get_class_name() {
		return This.name; 
	}

	//set
	void TCP_Client::set_all(SOCKET& psockfd, WORD& R_Port, std::string& IP, DWORD& EVENT, HWND& Hwnd) {
		This.set_socket(psockfd); 
		This.set_port(R_Port);
		This.set_IP(IP); 
		This.set_event(EVENT); 
		This.set_Hwnd(Hwnd); 
	}

	void TCP_Client::set_IP(std::string IP) {
		This.IP = IP; 
	}

	//get 
	std::string TCP_Client::get_IP() {
		return This.IP; 
	}

	int TCP_Client::start() {
		if (This.start_Winsock() == _Internet_msg::_START_WINSOCK_ERROR_) {
			return _Internet_msg::_START_WINSOCK_ERROR_;
		}
		if (This.open_Winsock() == _Internet_msg::_OPEN_WINSOCK_ERROR_) {
			return _Internet_msg::_OPEN_WINSOCK_ERROR_;
		}
		if (This.Set_Asynchronized_Mode(This.Mode.TCP) == _Internet_msg::_SET_ASYNCHRONIZED_MODE_ERROR_) {
			return _Internet_msg::_SET_ASYNCHRONIZED_MODE_ERROR_;
		}
		This.set_Socket_nameing(This.IP); 
		if (This.open_socket_connecter() == _Internet_msg::_OPEN_SOCKET_CONNECTER_ERROR) {
			return _Internet_msg::_OPEN_SOCKET_CONNECTER_ERROR;
		}
		return _Internet_msg::_SUCCESS_;
	}


	class UDP_Server :public _Internet_base_plug {
	private:
		const std::string name = "UDP_Server";

	protected:
		std::string get_class_name();

	public:
		UDP_Server(); 
		UDP_Server(SOCKET& psockfd, WORD& Port, DWORD& EVENT, HWND& Hwnd);
		~UDP_Server();

		int start();
	};
	UDP_Server::UDP_Server() :Internet_base_plug() {

	}
	UDP_Server::UDP_Server(SOCKET& psockfd, 
		WORD& Port, 
		DWORD& EVENT, 
		HWND& Hwnd)
		:Internet_base_plug(psockfd, Port,EVENT , Hwnd) {
	}

	UDP_Server::~UDP_Server() {
	}

	std::string UDP_Server::get_class_name() {
		return This.name;
	}

	int UDP_Server::start() {
		if (This.start_Winsock() == _Internet_msg::_START_WINSOCK_ERROR_) {
			return _Internet_msg::_START_WINSOCK_ERROR_;
		}
		if (This.open_Winsock() == _Internet_msg::_OPEN_WINSOCK_ERROR_) {
			return _Internet_msg::_OPEN_WINSOCK_ERROR_;
		}
		if (This.Set_Asynchronized_Mode(This.Mode.UDP) == _Internet_msg::_SET_ASYNCHRONIZED_MODE_ERROR_) {
			return _Internet_msg::_SET_ASYNCHRONIZED_MODE_ERROR_;
		}

		This.set_Socket_nameing(htonl(INADDR_ANY));

		if (This.open_socket_bind() == _Internet_msg::_OPEN_SOCKET_BIND_ERROR_) {
			return _Internet_msg::_OPEN_SOCKET_BIND_ERROR_;
		}
		return _Internet_msg::_SUCCESS_;
	}

	
	class UDP_Client : public _Internet_base_plug {
	private:
		const std::string name = "UDP_Client";
		std::string IP; 

	protected:
		std::string get_class_name(); 
		
	public:
		UDP_Client(); 
		UDP_Client(std::string IP);
		UDP_Client(SOCKET& psockfd,
				   sockaddr_in& udpclient,
			       WORD& R_Port,
			       std::string& IP,
			       DWORD& EVENT,
			       HWND& Hwnd);
		
		
		~UDP_Client();
		std::string get_IP();
		void set_all(SOCKET& psockfd, WORD& R_Port, std::string& IP, DWORD& EVENT, HWND& Hwnd);
		void set_IP(std::string IP);

		int start(); 
	};

	UDP_Client::UDP_Client():Internet_base_plug() {

	}

	UDP_Client::UDP_Client(std::string IP) : Internet_base_plug() {
		This.IP = IP; 
	}

	UDP_Client::UDP_Client(SOCKET& psockfd, 
		sockaddr_in& udpclient, 
		WORD& R_Port, 
		std::string& IP, 
		DWORD& EVENT, 
		HWND& Hwnd) :Internet_base_plug(psockfd , R_Port , EVENT , Hwnd){

		This.tcp_udp = udpclient; 
		This.IP = IP; 

	}

	std::string UDP_Client::get_class_name() {
		return This.name; 
	}

	std::string UDP_Client::get_IP() {
		return This.IP; 
	}

	void UDP_Client::set_all(SOCKET& psockfd, WORD& R_Port, std::string& IP, DWORD& EVENT, HWND& Hwnd) {
		This.set_socket(psockfd);
		This.set_port(R_Port);
		This.set_IP(IP);
		This.set_event(EVENT);
		This.set_Hwnd(Hwnd);
	}

	void UDP_Client::set_IP(std::string IP) {
		This.IP = IP;
	}

	UDP_Client::~UDP_Client() {
	
	}

	int UDP_Client::start() {
		if (This.start_Winsock() == _Internet_msg::_START_WINSOCK_ERROR_) {
			return _Internet_msg::_START_WINSOCK_ERROR_;
		}
		if (This.open_Winsock() == _Internet_msg::_OPEN_WINSOCK_ERROR_) {
			return _Internet_msg::_OPEN_WINSOCK_ERROR_;
		}
		if (This.Set_Asynchronized_Mode(This.Mode.TCP) == _Internet_msg::_SET_ASYNCHRONIZED_MODE_ERROR_) {
			return _Internet_msg::_SET_ASYNCHRONIZED_MODE_ERROR_;
		}
		This.set_Socket_nameing(This.IP);
		return _Internet_msg::_SUCCESS_;
	}
}
#endif // check INTERNET_BASE_HPP

#endif // !TCPIP_HPP
