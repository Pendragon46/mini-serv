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
/*		Cannonical Function		*/
/********************************/

MiniServ::MiniServ(){}
MiniServ::~MiniServ(){}
MiniServ::MiniServ( const MiniServ &toCopy ){ static_cast<void>(toCopy); }
MiniServ &MiniServ::operator=( const MiniServ &toCopy)
{
	static_cast<void>(toCopy);
	return (*this);
}

/********************************/
/*		  Static Function		*/
/********************************/

bool	MiniServ::Init(int &socketfd, struct addrinfo **addr)
{
	struct addrinfo hint;
	
	memset(&hint, 0, sizeof(hint));
	hint.ai_family = AF_INET;
	hint.ai_socktype = SOCK_STREAM;
	hint.ai_flags = AI_PASSIVE;
	if ( getaddrinfo(NULL, PORT , &hint, addr) != 0 )
	{
		std::cerr << gai_strerror(errno) << std::endl;
		return (false);
	}
	for (struct addrinfo *tmp = *addr; tmp != NULL; tmp = tmp->ai_next)
	{
		socketfd = socket(tmp->ai_family, tmp->ai_socktype, tmp->ai_protocol);
		if ( socketfd < 0 )
		{
			std::cerr << "CreateSocket : " << strerror(errno) << std::endl;
			return (false);
		}
		if (bind(socketfd, tmp->ai_addr, tmp->ai_addrlen) == 0)
			break;
		close(socketfd);
	}
	if (listen(socketfd, 1) < 0)
	{
		std::cerr << "Listen : " << strerror(errno) << std::endl;
		return (false);
	}
	return (true);
}