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
	Client		client;
	int			events;

	serv.signalHandler();
	std::cout << "Waiting connection on port " << PORT << "..." << std::endl;
	while ( !MiniServ::sig )
	{
		events = poll(serv.fds, OPEN_MAX, -1);
		if (events > 0)
		{
			if (serv.fds[0].revents == POLLIN)
			{
				serv.ft_accept();
				events--;
			}
			for (int i = 1; i < OPEN_MAX && events > 0; i++)
			{
				if (serv.fds[i].revents == POLLIN)
				{
					serv.getRequest(serv.fds[i].fd);
					events--;
				}
				else if (serv.fds[i].revents == POLLOUT)
				{
					serv.sendResponse(serv.fds[i].fd);
					events--;
				}
			}
		}
		else if ( events == -1 && !MiniServ::sig )
		{
			std::cerr << "Poll : " << strerror(errno) << std::endl;
			return ( 1 );
		}
	}
	std::cout << "\nServer shut down gracefully." << std::endl;
	return 0;
}