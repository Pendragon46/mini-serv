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
	
	sock = wrap_socket(addr.sin_family, SOCK_STREAM, 0);
	wrap_bind(sock, reinterpret_cast<sockaddr *>(&addr), sizeof(addr));
	wrap_listen(sock, LISTENQ);
	
	fd.collect(sock);
	bzero(&fds, sizeof(fds));
	fds[0].fd = sock;
	fds[0].events = POLL_IN;
	for (int i = 1; i < OPEN_MAX; i++)
		fds[i].fd = -1;
}
MiniServ::~MiniServ()
{
	fd.remove(sock);
}


/********************************/
/*		  HTTP/1.1 Function		*/
/********************************/

void	MiniServ::ft_accept( )
{
	Client	newClient;

	newClient = wrap_accept(sock, (sockaddr *)(&newClient.addr), &newClient.size);
	collect(newClient);
}

bool	MiniServ::getRequest(int fdKey)
{
	std::string	res;
	char		tmp[DATALEN + 1];
	int			status = DATALEN;
	Client		&clt = client[fdKey];

	while (status == DATALEN)
	{
		memset(tmp, 0, sizeof(char) * DATALEN);
		status = recv(clt.sock, tmp, DATALEN, 0);
		if (status == -1)
		{
			std::cerr << "Recv : " << strerror(errno) << std::endl;
			return (false);
		}
		tmp[DATALEN] = '\0';
		res += tmp;
	}
	std::cout	<<"Request =\n"
				<<"-------------------------------------------------\n"
				<< res
				<<"-------------------------------------------------"
				<< std::endl;
	clt.pollstruct->events = POLLOUT;
	clt.request = res;
	//  process response
	clt.response = "Congrats your client app work !";
	return (true);
}

bool	MiniServ::sendResponse(int fdKey)
{
	Client		&clt = client[fdKey];

	if (send(clt.sock, clt.response.c_str(), clt.response.length(), 0) < 0)
	{
		std::cerr << "Send : " << strerror(errno) << std::endl;
		return (false);
	}
	remove(clt);
	return (true);
}


/********************************/
/*			FD Collector		*/
/********************************/

void	MiniServ::collect(Client &newClient)
{
	int i = 1;

	fd.collect(newClient.sock);
	for (; i < OPEN_MAX && fds[i].fd != -1; i++);
	fds[i].fd = newClient.sock;
	fds[i].events = POLL_IN;
	newClient.pollstruct = &fds[i];
	client[newClient.sock] = newClient;
	client[newClient.sock].sock = newClient.sock;
}

void	MiniServ::remove(Client &clt)
{
	clt.pollstruct->fd = -1;
	clt.pollstruct->events = -1;
	client.erase(clt.sock);
	fd.remove(clt.sock);
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

