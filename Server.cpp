#include <cstdlib>
#include <functional>
#include <iostream>
#include <netinet/in.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include "Server.hpp"
#include <map>

char Socket::Create_Socket()
{
SOcketfd = socket(AF_INET, SOCK_STREAM, 0);
if(SOcketfd == -1)
{
    return -1;
}
else 
{
return 1;
}
}

char Socket::Bind(uint16_t port)
{
SockAddr.sin_family = AF_INET;
SockAddr.sin_port = htons(port);  // is a function used to convert a port number from host byte order to network byte order (big-endian). It stands for "host to network short".
inet_pton(AF_INET, "0.0.0.0", &SockAddr.sin_addr); // After the function call, &SockAddr.sin_addr will contain the binary representation of the IPv4 address 0.0.0.0.
if(bind(SOcketfd,(struct sockaddr *)&SockAddr,sizeof(SockAddr)) == -1)
{
    return -1;
}
else
{
     return 1;
}
}

char Socket::Listen()
{
    if(listen(SOcketfd, SOMAXCONN) == -1) // SOMAXCONN : t represents the maximum number of connection requests that can be queued up by the operating system while waiting for the server to accept them
{
     return -1;
}
else 
{
 return 1;
}
}


char Socket::Accept()
{
socklen_t ClientSize = sizeof(client);
Clientfd = accept(SOcketfd,(struct sockaddr *)&client , &ClientSize);
if(Clientfd == -1)
{
    return -1;
}
else 
{
    return 1;
}
}
void Socket::Recieve( char * msgbuffer)
{
    int k=0;
    memset(msgbuffer, 0, 4096);
        // Wait for client to send data
        ssize_t bytesReceived = recv(Clientfd, msgbuffer, 4096, 0);
        if (bytesReceived == -1)
        {
            send(Clientfd,"Error in recv(). Quitting",26,0);
            exit(1);
        }
 
        if (bytesReceived == 0)
        {
             send(Clientfd,"Client disconnected ",21,0);
            exit(1);
        }

        for(int i = 0;i<bytesReceived-2;i++) 
        {
            if(msgbuffer[i] != '\n')
            msgbuffer[k++] = msgbuffer[i];
        }
        msgbuffer[k] = '\0';
        for(int i = 0;msgbuffer[i]!='\0';i++) 
        {
            if(msgbuffer[i]!='\n')
            std::cout<<msgbuffer[i]<<std::endl;
        }
        
}


void Socket::Send(const char* msg,size_t len)
{
   send(Clientfd,msg,len,0);    

}

void Socket::Close()
{
     close(SOcketfd); 
     close(Clientfd);
}
char Socket::Socket_INIT(uint16_t port)
{
    
    if(Socket::Create_Socket() == -1)
    {
        std::cout<<"Can't open a socket!!"<<std::endl;
        return -1;
    }
    else
    {
        std::cout<<"Socket Opened Successfully"<<std::endl;
    }
    if(Socket::Bind(port) == -1)
    {
        std::cout<<"Can not bind to port"<<std::endl;
        return -1;
    }
    else
    {
         std::cout<<"Bind Successfully"<<std::endl;
    }
    if(Socket::Listen() == -1)
    {
        std::cout<<"Can not Listen!!"<<std::endl;
        return -1;
    }
    else
    {
        std::cout<<"Listening...."<<std::endl;
    }
    if(Socket::Accept() == -1)
    {
        std::cout<<"Client Connecting Failed"<<std::endl;
        return -1;
    }
    else
    {
        send(Clientfd,"Connected Successfully",23,0);
        return 1;
    }
}