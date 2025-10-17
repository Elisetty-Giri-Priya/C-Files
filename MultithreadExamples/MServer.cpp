#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <cstdlib>
#include <thread>
#include <vector>
using namespace std;
constexpr int MAX = 80;
constexpr int PORT = 8080;
using SA = struct sockaddr;
void func(int connfd)
{
    char buff[MAX];
    int n;
    while (true)
    {
        memset(buff, 0, MAX);
        // read the message from client and copy it in buffer
        read(connfd, buff, sizeof(buff));
        // print buffer which contains the client contents
        cout << "From client: " << buff << "To client : " << buff << endl;
        // memset(buff, 0, MAX);
        // n = 0;
        // // copy server message in the buffer
        // char ch;
        // while (cin.get(ch) && ch != '\n')
        // {
        //     buff[n++] = ch;
        // }
        // and send that buffer to client
        write(connfd, buff, sizeof(buff));
        // if msg contains "Exit" then server exit and chat ended.
        if (strncmp("exit", buff, 4) == 0)
        {
            cout << "Server Exit... " << endl;
            break;
        }
    }
}
// Driver fuction
int main()
{
    int sockfd, connfd;
    socklen_t len;
    sockaddr_in servaddr{}, cli{};
    vector<thread*> thread_ptrs;
    // socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        cout << "Socket creation failed.. " << endl;
        exit(0);
    }
    else
    {
        cout << "Socket Successfully created .." << endl;
    }
    memset(&servaddr, 0, sizeof(servaddr));
    // Assign IP, Port
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);
    // Binding newly created socket to given IP and verification
    if ((bind(sockfd, reinterpret_cast<SA *>(&servaddr), sizeof(servaddr))) != 0)
    {
        cout << " Socket bind failed.. " << endl;
        exit(0);
    }
    else
    {
        cout << "Socket successfully binded.." << endl;
    }
    // Now server is ready to listen and verification
    if ((listen(sockfd, 5)) != 0)
    {
        cout << "Listen failed.." << endl;
        exit(0);
    }
    else
    {
        cout << "Server Listening.. " << endl;
    }
    // len = sizeof(cli);
    len = sizeof(cli);
    // Accept the data packet from client and verification
    int i =0;
    while (i<2)
    {
        connfd = accept(sockfd, reinterpret_cast<SA *>(&cli), &len);
        if (connfd < 0)
        {
            cout << "<server accept failed..." << endl;
            exit(0);
        }
        else
        {
            cout << "server accept the client..." << endl;
        }

        // Function for chatting between client and server
        thread* t = new thread(func, connfd);
        thread_ptrs.push_back(t);
        i++;
    }

    for(thread* thread_ptr: thread_ptrs) {
        thread_ptr->join();
    }

    // After chatting close the socket
    close(sockfd);
}
