/*********************************************************************************
*                               Author: Pendragon                                *
*                      Creation Date: May 8, 2025 10:52 AM                       *
*                       Last Updated: May 8, 2025 10:53 AM                       *
*                              Source Language: cpp                              *
*                                                                                *
*                            --- Code Description ---                            *
*                        Implementation of class MiniServ                        *
*********************************************************************************/

#include <MiniServ.hpp>

/********************************/
/*		Construct && Desct		*/
/********************************/
FdCollector		MiniServ::fd;
sig_atomic_t	MiniServ::sig = 0;
MiniServ::MiniServ( const MiniServ &toCopy ){ static_cast<void>(toCopy); }
MiniServ &MiniServ::operator=( const MiniServ &toCopy)
{
	static_cast<void>(toCopy);
	return (*this);
}

MiniServ::MiniServ() : sock(-1)
{
	bzero(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	sock = socket(addr.sin_family, SOCK_STREAM, 0);
	if (sock < 0)
	{
		std::cerr << "Socket : " << strerror(errno) << std::endl;
		throw BadConstructException();
	}
	if (bind(sock, (sockaddr *)&addr, sizeof(addr)) < 0)
	{
		std::cerr << "Bind : " << strerror(errno) << std::endl;
		throw BadConstructException();
	}
	if (listen(sock, LISTENQ) < 0)
	{
		std::cerr << "Listen : " << strerror(errno) << std::endl;
		throw BadConstructException();
	}
	fd.collect(sock);
}
MiniServ::~MiniServ()
{
	fd.remove(sock);
}


/********************************/
/*		  HTTP/1.1 Function		*/
/********************************/

void	MiniServ::ft_accept(Client &client)
{
	client.sock = accept(sock, (sockaddr *)(&client.addr), &client.size);
	if (sig)
		return;
	if (client.sock  == -1 )
	{
		std::cerr << "Accept : " << strerror(errno) << std::endl;
		throw BadConstructException();
	}
	std::cout << "Client connected " << std::endl;
	fd.collect(client.sock);
}

bool	MiniServ::getRequest(Client &client)
{
	std::string	res;
	char		tmp[DATALEN + 1];
	int			status = DATALEN;

	while (status == DATALEN)
	{
		memset(tmp, 0, sizeof(char) * DATALEN);
		status = recv(client.sock, tmp, DATALEN, 0);
		if (sig)
			return(true);
		if (status == -1)
		{
			std::cerr << "Recv : " << strerror(errno) << std::endl;
			return (false);
		}
		tmp[DATALEN] = '\0';
		res += tmp;
	}
	std::cout	<<"-------------------------------------------------"
				<< "Request =\n" << res
				<<"-------------------------------------------------"
				<< std::endl;
	return (true);
}

bool	MiniServ::sendResponse(Client &client)
{
	std::string data("Congrats your client app work !");
	if (send(client.sock, data.c_str(), data.length(), 0) < 0)
	{
		if (sig)
			return(true);
		std::cerr << "Send : " << strerror(errno) << std::endl;
		return (false);
	}
	return (true);
}


/********************************/
/*			FD Collector		*/
/********************************/

void	MiniServ::collect(int newFd)
{
	fd.collect(newFd);
}

void	MiniServ::remove(Client &client)
{
	fd.remove(client.sock);
}

/********************************/
/*		  	Exception			*/
/********************************/

const char*	MiniServ::BadConstructException::what() const throw()
{
	return ("");
}

const char*	MiniServ::ConnexionException::what() const throw()
{
	return ("");
}

