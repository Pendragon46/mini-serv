/*********************************************************************************
*                               Author: Pendragon                                *
*                     Creation Date: June 10, 2025 02:38 PM                      *
*                      Last Updated: June 10, 2025 02:39 PM                      *
*                              Source Language: cpp                              *
*                                                                                *
*                            --- Code Description ---                            *
*                         Wrapper function for property                          *
*********************************************************************************/

#include <WrapperFunction.hpp>


int	wrap_socket(int domain, int type, int protocol)
{
	int sock;

	sock = socket(domain, type, protocol);
	if (sock < 0)
	{
		std::cerr << "Socket : " << strerror(errno) << std::endl;
		throw MiniServ::BadConstructException();
	}
	return (sock);
}

void wrap_bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
{
	int activate = 1;

	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &activate, sizeof(activate)) < 0)
	{
		std::cerr << "setsockopt : " << strerror(errno) << std::endl;
		throw MiniServ::BadConstructException();
	}
	if (bind(sockfd, addr, addrlen) < 0)
	{
		std::cerr << "Bind : " << strerror(errno) << std::endl;
		throw MiniServ::BadConstructException();
	}
}

void wrap_listen(int sockfd, int backlog)
{
	if (listen(sockfd, backlog) < 0)
	{
		std::cerr << "Listen : " << strerror(errno) << std::endl;
		throw MiniServ::BadConstructException();
	}
}

Client wrap_accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen)
{
	Client	newClient;

	newClient.sock = accept(sockfd, addr, addrlen);
	if (newClient.sock  == -1 )
	{
		std::cerr << "Accept : " << strerror(errno) << std::endl;
		throw MiniServ::BadConstructException();
	}
	std::cout	<< "\n\nClient ( "
				<< inet_ntoa(newClient.addr.sin_addr)
				<< " ) connected." << std::endl;
	return (newClient);
}

std::s  wrap_recv(int fd, DATALEN)
{

}