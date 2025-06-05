/*********************************************************************************
*                               Author: Pendragon                                *
*                      Creation Date: May 8, 2025 10:57 AM                       *
*                       Last Updated: May 8, 2025 10:57 AM                       *
*                              Source Language: cpp                              *
*********************************************************************************/

#include <MiniServ.hpp>

int main ( void )
{
	MiniServ	serv;

	serv.signalHandler();
	while ( !MiniServ::sig )
	{
		Client		client;

		std::cout << "Waiting connection on port " << PORT << "..." << std::endl;
		serv.ft_accept(client);
		serv.getRequest(client);
		serv.sendResponse(client);
		serv.remove(client);
	}
	std::cout << "\nServer shut down gracefully." << std::endl;
	return 0;
}