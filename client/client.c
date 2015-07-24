#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <linux/unistd.h>
#include <unistd.h>
#include <fcntl.h>
#include "client_module.h"

struct data    
{                  
    char name[20];       
    char pass[20];        
    };

void filework()
{
	char buf[999];
	FILE *f, *q;
	system("clear");
	f=fopen("history.txt","r");
	
	while (fgets(buf,10,f)!=NULL)
	 {              
                printf(buf);
     }        
                fclose(f);
}


void * thread_func(void *arg)
{ int i;
int loc_id = * (int *) arg;
for (; ; ) 
{
	filework();
	sleep(1);
}
}
	


void chat(char *nam)
{
	int  listener;
	int sock;
	struct sockaddr_in addr;
	int bytes_read;
	char stop_word[]="/exit";
	char sp[]=": ";
	char message[100],name[20],name2[20];
	const time_t timer = time(NULL);
	int id1, id2, result;
	pthread_t thread1, thread2;
	id1 = 1;
	result = pthread_create(&thread1, NULL, thread_func, &id1);
	if (result != 0) {
	perror("Error with creating the thread");
	return -2;
	}
	listener = socket (AF_INET, SOCK_STREAM,0);
	sock=socket(AF_INET,SOCK_STREAM,0);
	if (sock<0){
		perror("Error with socket");
		return 1;
	}
	addr.sin_family = AF_INET;
	addr.sin_port=htons(3425);
	addr.sin_addr.s_addr=htonl(INADDR_LOOPBACK);
	if(connect(sock,(struct sockaddr*)&addr,sizeof(addr))<0){
		perror("Couldn't connect to server");
		return 1;
	}
	strcpy(name,nam);
 		strcat(name,sp);
	while(1)
	{
		scanf("%s",&message);
		strcpy(name2,name);
  		strcat(name2,message);
 		strcat(name2,"\n");
 	 	if (strcmp(message,stop_word)==0)
 	 		break;
 	 	else	
 			send (sock,name2,sizeof(name2),0);
 					
 				
	}
	close(sock);
	printf("You have quited the chat\n");	
}
int main()
{
	int bytes_read,i;	
	char name[20],pass[20];
	printf("Choose the action you want:\n");
	printf("1 - login to server, 2 -register new account on server\n");
	scanf("%d",&i);
	if (i==1)
	{
		printf("Enter your login:\n");
		scanf("%s",name);
		printf("Enter your password:\n");
		scanf("%s",pass);
		if (login(name,pass)==1)
			{
		chat(name);
		}
		else
		{
			puts(" You have failed login to the server!");
		}
				
		}
		
	if (i==2)
	{
		reg();
		system("clear");
		printf("Enter your login:\n");
		scanf("%s",name);
		printf("Enter your password:\n");
		scanf("%s",pass);
		if (login(name,pass)==1)
			
			chat(name);		
		else
		puts(" You have failed login to the server!");	
		}
		else
	puts("You have entered wrong number!");	
	return 0;
	}

