/*********************************************************************************
*                               Author: Pendragon                                *
*                      Creation Date: June 5, 2025 11:14 AM                      *
*                      Last Updated: June 5, 2025 11:15 AM                       *
*                              Source Language: cpp                              *
*                                                                                *
*                            --- Code Description ---                            *
*                           Implementation of FdCollector class                           *
*********************************************************************************/

#include<FdCollector.hpp>

FdCollector::FdCollector() : fd()
{};
FdCollector::~FdCollector()
{
	for (std::list<int>::iterator it = fd.begin(); it != fd.end(); it++)
	{
		if (*it != -1)
			close(*it);
	}
};

void	FdCollector::collect(int newFd)
{
	if ( newFd != -1 )
		fd.push_back(newFd);
}

void	FdCollector::remove(int newFd)
{
	if ( newFd != -1 )
	{
		close(newFd);
		fd.remove(newFd);
	}
}

void	FdCollector::clear()
{
	int tmp;

	for (std::list<int>::iterator it = fd.begin(); it != fd.end(); it++)
	{
		tmp = *it;
		if (tmp != -1)
		{
			close(tmp);
			*it = -1;
		}
	}
}
