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
#include <map>
#include <string_view>
#include "Server.hpp"
#include "Commands.hpp"

char command_msg[4096];

std::map<std::string,std::string>commands{
    {"calculator", "gnome-calculator"},
    {"firefox", "firefox"},
    {"calendar", "gnome-calendar"},
    {"settings", "gnome-control-center"},
    };


void Get_Command(Socket *ss)
{
     ss->Socket :: Recieve(command_msg);
    for (char *iter = command_msg; *iter != '\0'; ++iter)
   {
       *iter = std::tolower(*iter);
       ++iter;
   }
}

bool Execute_Command()
{
    bool check = 0;
    std::string cmd(command_msg);
    auto itr = commands.begin();
    while(itr != commands.end())
  {
     if(cmd == itr->first)
     {
        system(itr->second.c_str());
        check = 1;
        break;
     }    
    itr++;
  }
  if(check == 0)
  {
   return 0;
  }
  else
  return 1;
}

bool Add_Command( std::string cmd, std::string shortcut)
{
   auto check = commands.insert(std::pair<std::string, std::string>(shortcut, cmd));
   if(check.second)
    return 1;
   else
    return 0;
}

void Remove_Command(std::string shortcut,Socket *ss)
{
        auto it = commands.find(shortcut);
        if (it != commands.end()) {
        commands.erase(it);
        ss->Socket :: Send("'Command' ",11);
        ss->Socket :: Send(shortcut.c_str(),shortcut.length());
        ss->Socket :: Send(" removed.\n",11);
        }
        else {
        ss->Socket :: Send("'Command' ",11);
        ss->Socket :: Send(shortcut.c_str(),shortcut.length());
        ss->Socket :: Send(" not found.\n",13);
        }
}

void Commands_list(Socket *ss)
{
for (const auto& pair : commands) {
        ss->Socket :: Send("\nshortcut: ",11);
        ss->Socket :: Send(pair.first.c_str(),pair.first.length());
        ss->Socket :: Send(",",2);
        ss->Socket :: Send("command: ",10);
        ss->Socket :: Send(pair.second.c_str(),pair.second.length());
        ss->Socket :: Send("\n",2);
    }

}

