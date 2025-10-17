#include <iostream>
#include <cstdlib>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>
constexpr int MAX = 1000;
constexpr int PORT = 8080;
using SA = struct sockaddr;

using namespace std;
void func(int sockfd)
{
    char buff[MAX];
    int n;
    while (true)
    {
        memset(buff, 0, sizeof(buff));
        cout << "Enter the string : " << endl;
        n = 0;
        char ch;
        while (cin.get(ch) && ch != '\n')
        {
            buff[n++] = ch;
        }
        write(sockfd, buff, sizeof(buff));
        memset(buff, 0, sizeof(buff));
        read(sockfd, buff, sizeof(buff));
        cout << "From Server : " << buff << endl;
        if ((strncmp(buff, "exit", 4)) == 0)
        {
            cout << "Client Exit..." << endl;
            break;
        }
    }
}
int main()
{
    int sockfd, connfd;
    sockaddr_in servaddr{}, cli{};
    // socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        cout << "socket creation failed..." << endl;
        exit(0);
    }
    else
        cout << "Socket successfully created.." << endl;
    memset(&servaddr, 0, sizeof(servaddr));
    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);
    // connect the client socket to server socket
    if (connect(sockfd, (SA *)&servaddr, sizeof(servaddr)) != 0)
    {
        cout << "connection with the server failed..." << endl;
        exit(0);
    }
    else
        cout << "connected to the server.." << endl;

    // function for chat
    func(sockfd);

    // close the socket
    close(sockfd);
}