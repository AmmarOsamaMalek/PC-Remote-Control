
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
#include "Commands.hpp"
#define PORT  8080



int main()
{
    
Socket sk;

size_t len = 0;
char op[4];
bool check;
char shortcut[MAXBYTES] ;
char cmd[MAXBYTES] ;


const char* client_msg = "                          \n[1]- List all commands\n\
                          [2]- Add command\n\
                          [3]- Remove command\n\
                          [4]- Write command\n\
                          [5]- Close connection\n\
                          Note: Press c to return to the main page";
                          
len = strlen(client_msg) + 1;

if(sk.Socket_INIT(PORT))
{

sk.Send(client_msg,len);

while(true)
{
    sk.Send("\nEnter Your Choice : ",22);
    sk.Recieve(op);
    if(*op == '1')
    {
        Commands_list(&sk);
    }
    else if(*op == '2')
    {
        sk.Send("Enter shortcut: ",17); 
        sk.Recieve(shortcut);
        sk.Send("Enter command: ",16);
        sk.Recieve(cmd);
        check = Add_Command(cmd,shortcut);
        if(check == 1)
        {
            sk.Send("successfully added\n",20);
        }
        else
        {
            sk.Send("Failed",7);
        }
        Commands_list(&sk);
    }
    else if(*op == '3')
    {
        sk.Send("Enter shortcut to remove: ",27);
        sk.Recieve(shortcut);
        Remove_Command(shortcut,&sk);
        Commands_list(&sk);
    }
    else if(*op == '4')
    {
            sk.Send("Enter Shortcut: ",17);
            Get_Command(&sk);
            check = Execute_Command();
            if(check == 0)
            {
                sk.Send("Wrong Command",14);
            }
    }
    else if(*op == '5')
    {
        sk.Close();
    }
    else if(*op == 'c')
    {
        sk.Send(client_msg,len);
    }
    else
    {
        sk.Send("Wrong Choice...Try Again\n",26);
        sk.Send(client_msg,len);
    }
}
}
    
return 0;
}