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
#include <limits.h>
#include <stdlib.h>
#include <signal.h>
#include <poll.h>
#include <errno.h>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

#include <exception>
#include <iostream>
#include <string>
#include <cstring>
#include <list>
#include <map>

#include <WrapperFunction.hpp>
#include <FdCollector.hpp>
#include <Client.hpp>

#define	PORT	4646
#define	LISTENQ 46
#define DATALEN 1080
#define OPEN_MAX 1024

class MiniServ
{
	private:
		MiniServ( const MiniServ &toCopy );
		MiniServ &operator=( const MiniServ &toCopy );
		
	public:
		int						sock;
		struct pollfd			fds[OPEN_MAX];
		std::map<int, Client>	client;
		struct sockaddr_in		addr;
		
		MiniServ();
		~MiniServ();
		void	collect(Client &client);
		void	ft_accept();
		void	remove(Client &client);
		bool	getRequest(int fdKey);
		bool	sendResponse(int fdKey);

		static FdCollector	fd;
		static sig_atomic_t	sig;
		static void	signalHandler();

		class BadConstructException : public std::exception
		{
			public:
				const char* what() const throw();
		};
		class ConnexionException : public std::exception
		{
			public:
				const char* what() const throw();
		};
};

#endif
