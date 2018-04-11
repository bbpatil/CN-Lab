// server code.
// written by Kudo_1729

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>



int main(){
  int udpSocket, nBytes;
  //char buffer[1024];
  struct sockaddr_in serverAddr, clientAddr;
  struct sockaddr_storage serverStorage;
  socklen_t addr_size, client_addr_size;
  int *result = (int *)malloc(sizeof(int));

  udpSocket = socket(PF_INET, SOCK_DGRAM, 0);               // server_socket = socket(AF_INET,SOCK_STREAM,0);

  printf("Socket establishment done for local host\n");

  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(7891);
  serverAddr.sin_addr.s_addr = htonl( INADDR_LOOPBACK );        // server_address.sin_addr.s_addr = INADDR_ANY;
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

  								/*Bind socket with address struct*/
  bind(udpSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
  printf("Binding done at port number 7891 \nWaiting for the input from the client\n");

  addr_size = sizeof serverStorage;
    char *buffer=(char*)malloc(sizeof(int)*100);
nBytes = recvfrom(udpSocket,buffer,1024,0,(struct sockaddr *)&serverStorage, &addr_size);   //we are listening .
                                                                                            // listen(server_socket,5)
    int i ,j=0,k=0,l=0;                                                                     // client_socket = accept(server_socket,NULL,NULL);
    char a[100],b[100],c;
    int x,y;
    for(i=0;i<strlen(buffer);i++)
    {
        if(j==0)
        {
            if(buffer[i]>=48 && buffer[i]<=59)
            {
                a[k]=buffer[i];
                k++;

            }
            else
            {
                c=buffer[i];
                j=1;

            }

        }
        if(j==1)
        {
            if(buffer[i]>=48 && buffer[i]<=59)
            {
                b[l]=buffer[i];
                l++;

            }
            if(buffer[i]=='\0')
            j=2;

        }


    }




      printf("Here\n");
            x=atoi(a);
		printf("%d\n",x);
            y=atoi(b);
		printf("%d\n",y);
		printf("operation = %d\n",c);
            if(c=='+')
            {
                *result=x+y;
                printf("%d\n", *result);
                sendto(udpSocket,(void *)result,nBytes,0,(struct sockaddr *)&serverStorage,addr_size);


            }
              else if(c=='-')
            {
                *result=x-y;
                sendto(udpSocket,(void *)result,nBytes,0,(struct sockaddr *)&serverStorage,addr_size);


            }
             else if(c=='*')
            {
                *result=x*y;
                sendto(udpSocket,(void *)result,nBytes,0,(struct sockaddr *)&serverStorage,addr_size);


            }
             else if(c=='/')
            {
                *result=x/y;

                sendto(udpSocket,(void *)result,nBytes,0,(struct sockaddr *)&serverStorage,addr_size);


            }


  return 0;
}
