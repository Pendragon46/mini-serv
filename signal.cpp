/*********************************************************************************
*                               Author: Pendragon                                *
*                      Creation Date: June 5, 2025 03:23 PM                      *
*                      Last Updated: June 5, 2025 03:23 PM                       *
*                              Source Language: cpp                              *
*                                                                                *
*                            --- Code Description ---                            *
*                              Signal Handling file                              *
*********************************************************************************/

#include <MiniServ.hpp>

void sighandler(int sig)
{
	if (sig == SIGINT)
	{
		MiniServ::fd.clear();
		MiniServ::sig = 1;
	}
}
void	MiniServ::signalHandler()
{
	signal(SIGINT, sighandler);
}