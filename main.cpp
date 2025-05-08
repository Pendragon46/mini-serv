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

	if ( MiniServ::Init(servSocket, &addrServ) == false)
		return (1);
	while ( true )
	{
		std::cout << "Waiting connection on port " << PORT << " ..." << std::endl;
		struct addrinfo addrClient;
		int	clientSocket = accept(servSocket, addrClient.ai_addr, &addrClient.ai_addrlen);

		std::cout << "Client connected " << std::endl;
		std::string data("Congrats your client app work !");

		if (send(clientSocket, data.c_str(), data.length(), 0) < 0)
		{
			std::cerr << "Send : " << strerror(errno) << std::endl;
			return (1);
		}
		close(clientSocket);
	}
	return 0;
}