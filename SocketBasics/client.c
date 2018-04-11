// taken from - https://www.youtube.com/watch?v=LtXEMwSG5-8

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
  // create a socket

/*
	SYNOPSIS
       #include <sys/types.h>
       #include <sys/socket.h>

       int socket(int domain, int type, int protocol);

	RETURN VALUE
       On  success,  a  file  descriptor  for  the new socket is 	returned.  On
       error, -1 is returned, and errno is set appropriately.


*/

	int network_socket;
	network_socket = socket(AF_INET,SOCK_STREAM,0);

/*
AF_INET             IPv4 Internet protocols 

SOCK_STREAM     Provides sequenced, reliable, two-way, connection-based
                       byte  streams.  An out-of-band data transmission mecha‐
                       nism may be supported.

0 		indicates that the caller does not want to specify the protocol and will leave it up to the service provider.
*/

// specify an address for socket.
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9002);
	server_address.sin_addr.s_addr = INADDR_ANY;

/*
SYNOPSIS
       #include <sys/types.h>
       #include <sys/socket.h>

       int connect(int sockfd, const struct sockaddr *addr,
                   socklen_t addrlen);

RETURN VALUE
       If  the connection or binding succeeds, zero is returned.  On error, -1
       is returned, and errno is set appropriately.

*/

	int connection_status = connect(network_socket,(struct sockaddr*)&server_address,sizeof(server_address));

// check for error in the connection.

	if(connection_status==-1){
		printf("there was an error making connection to the remote socket.\n");
	}

// receive data from server.

	char server_response[256];

/*
SYNOPSIS
       #include <sys/types.h>
       #include <sys/socket.h>

       ssize_t recv(int sockfd, void *buf, size_t len, int flags);

       ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags,
                        struct sockaddr *src_addr, socklen_t *addrlen);

       ssize_t recvmsg(int sockfd, struct msghdr *msg, int flags);

RETURN VALUE
       These calls return the number of bytes received,  or  -1  if  an  error
       occurred.   In  the  event  of  an  error, errno is set to indicate the
       error.

       When a stream socket peer has performed an orderly shutdown, the return
       value will be 0 (the traditional "end-of-file" return).

       Datagram  sockets  in  various  domains  (e.g.,  the  UNIX and Internet
       domains)  permit  zero-length  datagrams.   When  such  a  datagram  is
       received, the return value is 0.

       The  value  0  may also be returned if the requested number of bytes to
       receive from a stream socket was 0.

*/

	recv(network_socket,&server_response,sizeof(server_response),0);

// print the server's response.

	printf("the server sent the data: %s\n",server_response);

	// then close the socket.
	close(network_socket);		
	return 0;
}
