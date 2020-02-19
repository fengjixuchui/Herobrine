// Copyright 2019 SMS
// License(Apache-2.0)
//

#include "Server.h"
#include "Session.h"
#include "print.h"
#include <thread>
#include <boost/bind.hpp>

using std::thread;
using namespace boost;



Server::Server(ushort port)
		: acceptor(ios, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port))
{
}


// ��ʼ�첽ͨ��
void Server::run()
{
	Accept();

	print::info("��ʼ����: " + acceptor.local_endpoint().address().to_string() + ":" + to_string(acceptor.local_endpoint().port()));
}


// �����ӽ���ʱ�ص�
void Server::OnAccept(const system::error_code& err, socket_ptr sock)
{
	if(err)
		return;

	print::good("�ͻ��˽���: " + sock->remote_endpoint().address().to_string() + ":" + to_string(sock->remote_endpoint().port()));

	// ����¿ͻ���
	Session_ session(ios);

	Accept();
}


// �첽����
void Server::Accept()
{
	socket_ptr sock(new asio::ip::tcp::socket(ios));
	acceptor.async_accept(*sock, boost::bind(&Server::OnAccept, this, asio::placeholders::error, sock));
}
