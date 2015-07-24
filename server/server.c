#include <stdio.h>
#include <stddef.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>

//#define PAS "base.txt"
//#define HIST "history.txt"

int main()
{

    int listener;
    struct sockaddr_in addr;
    char buf[1024];
    int bytes_read;
    int sock[3];
//
        FILE *f, *q;


//
    puts("History stored in file history.txt");
    puts("User's accounts stored in file base.dat");
    puts("Server started");
    puts("Press Ctrl+C to shutdown server");

    listener = socket(AF_INET, SOCK_STREAM, 0);
    if(listener < 0)
    {
        perror("socket");
        exit(1);
    }
    
    addr.sin_family = AF_INET;
    addr.sin_port = htons(3425);
    addr.sin_addr.s_addr = INADDR_ANY;
    if(bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("bind");
        exit(2);
    }

    listen(listener, 1);
    
    while(1)
    {
        sock[0] = accept(listener, NULL, NULL);
        if(sock[0] < 0)
        {
            perror("Error with accepting");
            exit(3);
        }
        
        switch(fork())
        {
        case -1:
            perror("Error with forking");
            break;
            
        case 0:
            close(listener);
            
            while(1)
            {
                bytes_read = recv(sock[0], buf, 1024, 0);
                if(bytes_read <= 0) 
                	break;
                

                f=fopen("/home/rt/hat/history.txt","a");
                fprintf(f,buf);
                
                fclose(f);
               //printf(buf);
               //send(sock[0], buf, sizeof(buf), 0);
                //send (sock[0],name2,,0);
            }

            close(sock[0]);
            _exit(0);
            
        default:
            close(sock[0]);
        }
    }
    
    close(listener);

    return 0;
}