/*********************************************************************************
*                               Author: Pendragon                                *
*                      Creation Date: May 8, 2025 10:57 AM                       *
*                       Last Updated: May 8, 2025 10:57 AM                       *
*                              Source Language: cpp                              *
*********************************************************************************/

#include <MiniServ.hpp>

int main ( void )
{
	int				servSocket;
	struct addrinfo *addrServ;

	if ( MiniServ::Init(servSocket, &addrServ) == false )
		return (1);
	while ( true )
	{
		std::cout << "Waiting connection on port " << PORT << " ..." << std::endl;
		// struct addrinfo addrClient;
		struct sockaddr_in addrClient;
		socklen_t size ;
		int	clientSocket = accept(servSocket, (sockaddr *)(&addrClient), &size);
		if (clientSocket  == -1)
		{
			std::cerr << "Accept : " << strerror(errno) << std::endl;
			return (1);
		}
		std::cout << "Client connected " << std::endl;
		std::string data("Congrats your client app work !");

		if (send(clientSocket, data.c_str(), data.length(), 0) < 0)
		{
			std::cerr << "Send : " << strerror(errno) << std::endl;
			return (1);
		}
		close(clientSocket);
	}
	close(servSocket);
	return 0;
}