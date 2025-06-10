/*********************************************************************************
*                               Author: Pendragon                                *
*                     Creation Date: June 10, 2025 02:40 PM                      *
*                      Last Updated: June 10, 2025 02:40 PM                      *
*                              Source Language: cpp                              *
*                                                                                *
*                            --- Code Description ---                            *
*                                 WrapperHeader                                  *
*********************************************************************************/

#ifndef WRAPPERFUNCTION_HPP
# define WRAPPERFUNCTION_HPP

#include <MiniServ.hpp>
#include <Client.hpp>


int	wrap_socket(int domain, int type, int protocol);
void wrap_bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
void wrap_listen(int sockfd, int backlog);
Client wrap_accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

#endif