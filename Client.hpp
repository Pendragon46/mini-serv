/*********************************************************************************
*                               Author: Pendragon                                *
*                      Creation Date: June 5, 2025 02:09 PM                      *
*                      Last Updated: June 5, 2025 02:09 PM                       *
*                              Source Language: cpp                              *
*                                                                                *
*                            --- Code Description ---                            *
*                                   TCP client                                   *
*********************************************************************************/

#ifndef CLIENT_HPP
# define CLIENT_HPP
# include <arpa/inet.h>
# include <string>
#include <poll.h>

class Client
{
	public:
		int					sock;
		socklen_t			size;
		struct	sockaddr_in addr;

		std::string			request;
		std::string			response;
		struct	pollfd		*pollstruct;

		Client(/* args */);
		~Client();
};

#endif