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
	struct addrinfo *res;
	
	memset(&hint, 0, sizeof(hint));
	hint.ai_family = AF_INET;
	hint.ai_socktype = SOCK_STREAM;
	hint.ai_flags = AI_PASSIVE;
	socketfd = socket(hint.ai_family, hint.ai_socktype, hint.ai_protocol);
	if ( socketfd < 0 )
	{
		std::cerr << "CreateSocket : " << strerror(errno) << std::endl;
		return (false);
	}
	if ( getaddrinfo(NULL, PORT , &hint, addr) != 0 )
	{
		std::cerr << gai_strerror(errno) << std::endl;
		return (false);
	}
	res = *addr;
	for (struct addrinfo *tmp = res; tmp != NULL; tmp = res->ai_next)
	{
		if (bind(socketfd, res->ai_addr, res->ai_addrlen) == 0)
			break;
	}
	freeaddrinfo(res);
	if (listen(socketfd, 1) < 0)
	{
		std::cerr << "Listen : " << strerror(errno) << std::endl;
		return (false);
	}
	return (true);
}