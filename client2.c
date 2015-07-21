#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>


int main()
{
	const time_t timer = time(NULL);
	int  listener;
	char message[]="Hello World! ";
	char buf[sizeof(message)];
	int sock;
	struct sockaddr_in addr;
	char name[40];
	char name2[40];
	int bytes_read;
	char stop_word[]="/exit";
	char sp[]=": ";
    
	listener = socket (AF_INET, SOCK_STREAM,0);

	sock=socket(AF_INET,SOCK_STREAM,0);
	if (sock<0){
		perror("socket");
		return 1;
	}

	addr.sin_family = AF_INET;
	addr.sin_port=htons(3425);
	addr.sin_addr.s_addr=htonl(INADDR_LOOPBACK);
	if(connect(sock,(struct sockaddr*)&addr,sizeof(addr))<0){
		perror("Couldn't connect to server");
		return 1;
	}
	
	else
	{
		printf("Welcome, You have successfully connected to the server!\n");
		printf("Type '/exit' to quit the chat\n\n");
		printf("Enter your name: ");
 		scanf("%s",&name);
 		strcat(name,sp);
 		
	}
	
	while(1)
	{
		
		printf("%s ",name);
 		scanf("%s",&message);
		strcpy(name2,name);
  		strcat(name2,message);
 		strcat(name2,"\n");
 		printf("%s",name2);
 	 	if (strcmp(message,stop_word)==0)
 	 		break;
 	 	else	
 			send (sock,name2,sizeof(name2),0);
					
	}
		
	close(sock);
	printf("You have quited the chat\n");
	return 0;
	}
