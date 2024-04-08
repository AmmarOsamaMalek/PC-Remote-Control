
//#include "Socket.hpp"



void Get_Command(Socket *s);

bool Execute_Command(void);

void Commands_list(Socket *ss);

bool Add_Command(const std::string cmd,const std::string shortcut);

void Remove_Command(std::string shortcut,Socket *ss);

