
#include <arpa/inet.h>

#define MAXBYTES 4096

class Socket
{
private:
int SOcketfd;
sockaddr_in SockAddr;
int Clientfd;
sockaddr_in client;
char massage[MAXBYTES];

public:
char Create_Socket(void);
char Bind(uint16_t Port);
char Listen(void);
char Accept(void);
void Recieve(char * msgbuffer);
void Send(const char* msg,size_t len);
void Close(void);
char Socket_INIT(uint16_t Port);
};