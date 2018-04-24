#include <stdio.h>
#include <sys/socket.h>
#include <dirent.h>
#include <netinet/in.h>
#include <string.h>
#include <pthread.h>
#include<string.h>

char fname[1024];


int main(){
  int sockfd, clientSocket, bytes_sent;
  char buffer[1024];
  struct sockaddr_in serverAddr;
  struct sockaddr_storage serverStorage;
  socklen_t addr_size;
  sockfd = socket(PF_INET, SOCK_STREAM, 0);
  pthread_t tid;
  char fileName[1024];

  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(7891);
  serverAddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

  bind(sockfd, (struct sockaddr *) &serverAddr, sizeof(serverAddr));		// using bind ?

  if(listen(sockfd,1)==0)
    printf("Listening on the port fmor the client\n");
  else
    printf("Listening error\n");

  addr_size = sizeof serverStorage;
  clientSocket = accept(sockfd, (struct sockaddr *) &serverStorage, &addr_size);	// using accept ?
  printf("Connection accepted......\n");
  printf("Sending the file names to the client.....\n");
	DIR *d;
	struct dirent *dir;
  	d = opendir("/Users/bhavin/Desktop/serverFolder/ServerFiles");			// oh boy !???
  	if (d) {
    		while ((dir = readdir(d)) != NULL) {
      		if (dir->d_type == DT_REG)
  		    {
            memset(buffer ,0 , strlen(buffer));
            strcpy(buffer, dir->d_name);
            printf("%s\n", buffer);
            bytes_sent = write(clientSocket, buffer, strlen(buffer));
            printf("%d\n", bytes_sent);
          }
        }
    }

  strcpy(buffer, "over");
  write(clientSocket,buffer,13);

  printf("File names sent, waiting for the response......\n");
  memset(buffer ,0 , strlen(buffer));

  int bytesRecv = read(clientSocket, fname, 1024);
  printf("name recieved %s\n", fname);

  strcpy(fileName, fname);

  printf("%s\n", fileName);
  char dest[200];
  strcpy(dest, "/Users/bhavin/Desktop/serverFolder/ServerFiles/");
  //printf("%s\n", dest);
        strcat(dest, fileName);
        printf("%s\n", dest);
        FILE *fp = fopen(dest,"r");
        if(fp==NULL)
        {
            printf("File opern error");
            return 1;
        }

        /* Read data from file and send it */
        printf("File opend yoho!!!!!!!!\n");
        while(1)
        {
            /* First read file in chunks of 256 bytes */
            unsigned char buff[1024]={0};
            int nread = fread(buff,1,1024,fp);
            printf("Bytes read %d \n", nread);
            printf("%s\n", buff);

            /* If read was success, send data. */
            if(nread > 0)
            {
                write(clientSocket, buff, nread);
            }
            if (nread < 1024)
            {
                if (feof(fp))
                {
                    printf("End of file\n");
                }
                if (ferror(fp))
                    printf("Error reading\n");
                break;
            }
        }
close(clientSocket);
shutdown(clientSocket,SHUT_WR);
fclose(fp);

  return 0;
}
