#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>

void gotoxy(int x,int y)
{
  printf("%c[%d;%df",0x1B,y,x); // what does 0x1B mean ?
}


int main(){
  int clientSock;
  //char buffer[1024];
  struct sockaddr_in serverAddr;
  socklen_t addr_size;
  int bytesRecv;
  char fname[1024];
  char recvBuff[1024];
  memset(recvBuff, '0', sizeof(recvBuff));
  FILE *fp;
  int bytesReceived;

  /*---- Create the socket. The three arguments are: ----*/
  /* 1) Internet domain 2) Stream socket 3) Default protocol (TCP in this case) */
  clientSock = socket(PF_INET, SOCK_STREAM, 0);

  /*---- Configure settings of the server address struct ----*/
  /* Address family = Internet */
  serverAddr.sin_family = AF_INET;
  /* Set port number, using htons function to use proper byte order */
  serverAddr.sin_port = htons(7891);
  /* Set IP address to localhost */
  serverAddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
  /* Set all bits of the padding field to 0 */
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

  /*---- Connect the socket to the server using the address struct ----*/
  addr_size = sizeof serverAddr;
  connect(clientSock, (struct sockaddr *) &serverAddr, addr_size);  // should have checked the value of the function call.

  char buffer[1024];
  printf("Server has asked to choose a file from the following list: \n");
  while((bytesRecv = read(clientSock, buffer, 5)) > 0){             // how to use read() function.
    if(strcmp(buffer, "over") == 0) break;
    //printf("Data received: %d\n",bytesRecv);
    printf("Data received: %s\n",buffer);
  }

  scanf("%s", fname);
  int bytes_sent = write(clientSock, fname, strlen(fname));         // how to use write() ?
  //printf("sent c : %d", bytes_sent);


  printf("got here\n" );
  fp = fopen(fname, "w");                                           // open file for writing.
  if(NULL == fp)
    {
      printf("Error opening file");
      return 1;
    }

    long double sz=1;
    /* Receive data in chunks of 256 bytes */
    while((bytesReceived = read(clientSock, recvBuff, 1024)) > 0)
    {
        sz++;
        printf("bytesReceived: %d\n", bytesReceived);
        fflush(stdout);
        // recvBuff[n] = 0;
        fprintf(fp,"%s",recvBuff);
        //fwrite(recvBuff, 1,bytesReceived,fp);
        printf("%s \n", recvBuff);
    }

    if(bytesReceived < 0)
    {
        printf("\n Read Error \n");
    }

    printf("\nFile OK....Completed\n");

  return 0;
}
