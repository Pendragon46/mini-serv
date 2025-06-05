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
#include <exception>
#include <errno.h>
#include <string>
#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <list>
#include <FdCollector.hpp>
#include <Client.hpp>
#include <signal.h>
#include <stdlib.h>


#define	PORT	4646
#define	LISTENQ 46
#define DATALEN 1080
class MiniServ
{
	private:
		MiniServ( const MiniServ &toCopy );
		MiniServ &operator=( const MiniServ &toCopy );
		
	public:
		int					sock;
		struct sockaddr_in	addr;
		
		MiniServ();
		~MiniServ();
		void	collect(int fd);
		void	remove(Client &client);
		void	ft_accept(Client &client);
		bool	getRequest(Client &client);
		bool	sendResponse(Client &client);

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
