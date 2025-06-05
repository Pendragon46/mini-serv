/*********************************************************************************
*                               Author: Pendragon                                *
*                      Creation Date: June 5, 2025 11:10 AM                      *
*                      Last Updated: June 5, 2025 11:20 AM                       *
*                              Source Language: cpp                              *
*                                                                                *
*                            --- Code Description ---                            *
*                           Class for manipulating fd                            *
*********************************************************************************/

#ifndef FDCOLLECTOR_HPP
# define FDCOLLECTOR_HPP

# include <list>
# include <unistd.h>

class FdCollector
{
	private:
		std::list<int> fd;
		
	public:
		FdCollector();
		~FdCollector();
		void	collect(int fd);
		void	remove(int fd);
		void	clear();
};

#endif