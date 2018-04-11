// client code written first.
// Written By Kudo_1729

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
  int clientSocket, portNum, nBytes;
  char buffer[1024];
  int *a = (int *)malloc(sizeof(int));
  int *b = (int *)malloc(sizeof(int));
  int *result = (int *)malloc(sizeof(int));

  							//setbuf(stdout, NULL);
  struct sockaddr_in serverAddr;
  socklen_t addr_size;


  clientSocket = socket(PF_INET, SOCK_DGRAM, 0);        // network_socket=socket(AF_INET,SOCK_STREAM,0);


  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(7891);
  serverAddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);  // server_address.sin_addr.s_addr = INADDR_ANY;
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

  addr_size = sizeof serverAddr;

    char s[100];
    printf("enter the application to perform\n");
    scanf("%s",s);
    sendto(clientSocket,s,strlen(s),0,(struct sockaddr *)&serverAddr,addr_size);    // sending request.
    nBytes = recvfrom(clientSocket,result,1024,0,NULL, NULL);                       // recieve()

    printf("%d\n", *result);    // print the result returned.

    close(clientSocket);	// close socket.

/*
	How to completely destroy a socket connection in C ?

	

The close call only marks the TCP socket closed. It is not usable by process anymore. But kernel may still hold some resources for a period (TIME_WAIT, 2MLS etc stuff).

Setting of SO_REUSEADDR should remove binding problems.

So be sure that value of true is really non-zero when calling setsockopt (overflow bug may overwrite it):

true = 1;
setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&true,sizeof(int))

There is pid variable is your code. If you use fork (for starting connection handling processs), then you should close sock also in the process which does not need it.

*/
  return 0;
}
