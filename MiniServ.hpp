/*********************************************************************************
*                               Author: Pendragon                                *
*                      Creation Date: May 8, 2025 10:50 AM                       *
*                       Last Updated: May 8, 2025 10:51 AM                       *
*                              Source Language: cpp                              *
*                                                                                *
*                            --- Code Description ---                            *
*                           Header for class miniserv                            *
*********************************************************************************/

#ifndef MINI_SERV_HPP
# define MINI_SERV_HPP

#include <unistd.h>
#include <errno.h>
#include <string>
#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

#define	PORT "5050"
class MiniServ
{
	private:
		MiniServ();
		MiniServ( const MiniServ &toCopy );
		~MiniServ();
		MiniServ &operator=( const MiniServ &toCopy );

	public:
		static bool Init( int &socket, struct addrinfo **res);
};

#endif