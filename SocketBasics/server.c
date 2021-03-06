// taken from - https://www.youtube.com/watch?v=LtXEMwSG5-8

#include<stdio.h>
#include<stdlib.h>

#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include <unistd.h>

int main(){
	char server_message[256] = "you recieved this from server";

	//create the server socket
	int server_socket;
	server_socket = socket(AF_INET,SOCK_STREAM,0);

	//define the server address
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9002);
	server_address.sin_addr.s_addr = INADDR_ANY;

	/*
	SYNOPSIS
       #include <sys/types.h>
       #include <sys/socket.h>

       int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
       
       RETURN VALUE
       On  success,  zero is returned.  On error, -1 is returned, and errno is
       set appropriately.

	*/
	// bind the socket to the specified id and port.
	bind(server_socket,(struct sockaddr*)&server_address,sizeof(server_address));
	
	/*
	SYNOPSIS
       #include <sys/types.h>
       #include <sys/socket.h>

       int listen(int sockfd, int backlog);
       
       RETURN VALUE
       On  success,  zero is returned.  On error, -1 is returned, and errno is
       set appropriately.

	*/

	listen(server_socket,5);

	int client_socket;
	// after listening accept.
	client_socket = accept(server_socket,NULL,NULL);
	
	/*
	SYNOPSIS
       #include <sys/types.h>
       #include <sys/socket.h>

       ssize_t send(int sockfd, const void *buf, size_t len, int flags);

       ssize_t sendto(int sockfd, const void *buf, size_t len, int flags,
                      const struct sockaddr *dest_addr, socklen_t addrlen);

       ssize_t sendmsg(int sockfd, const struct msghdr *msg, int flags);
       
       RETURN VALUE
       On success, these calls return the number of bytes sent.  On error,  -1
       is returned, and errno is set appropriately.
       
	*/

	send(client_socket,server_message,sizeof(server_message),0);

	//close the socket
	close(server_socket);
	return 0;
}
