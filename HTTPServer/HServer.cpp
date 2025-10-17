#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <cstdlib>
#include <sstream>
#include <vector>
#include "json.hpp"
using json = nlohmann::json;
using namespace std;
constexpr int MAX = 1000;
constexpr int PORT = 8080;
using SA = struct sockaddr;
struct User
{
    string name;
    int age;
};
struct Bus
{
    string name;
    int num;
};
void func(int connfd)
{
    char buff[MAX];
    int n;
    vector<User> users;
    vector<Bus> buses;
    while (true)
    {
        memset(buff, 0, MAX);
        // read the message from client and copy it in buffer
        read(connfd, buff, sizeof(buff));
        // if msg contains "Exit" then server exit and chat ended.
        if (strncmp("exit", buff, 4) == 0)
        {
            cout << "Server Exit... " << endl;
            break;
        }
        // print buffer which contains the client contents
        istringstream Buff(buff); // String flow
        string word;
        vector<string> Buffer;
        while (getline(Buff, word, '|'))
        {
            Buffer.push_back(word);
        }
        // cout.flush();
        if (Buffer[0] == "POST")
        {
            cout << "From client: " << 200 << " To client : " << 200 << endl;
            // convert the string into json object
            json obj = json::parse(Buffer[2]);
            // json object is pushing to Users
            if (Buffer[1] == "user")
            {
                users.push_back({obj["name"].get<string>(), obj["age"].get<int>()});
            }
            else if (Buffer[1] == "bus")
            {
                buses.push_back({obj["name"].get<string>(), obj["num"].get<int>()});
            }
            string jsonstring = obj.dump();
            write(connfd, jsonstring.c_str(), jsonstring.size());
        }
        else if (Buffer[0] == "GET")
        {
            if (Buffer[1] == "user")
            {
                cout << "From client: " << 200 << " To client : " << 200 << endl;
                vector<json> vec;
                int j = 0;
                while (j < users.size())
                {
                    User u = users[j];
                    // string jsonstring=u.name+u.age;
                    json js;
                    js["name"] = u.name;
                    js["age"] = u.age;
                    vec.push_back(js);
                    j++;
                }
                json J = vec;
                string jsonstring = J.dump();
                write(connfd, jsonstring.c_str(), jsonstring.size());
            }
            else if (Buffer[1] == "bus")
            {
                cout << "From client: " << 200 << " To client : " << 200 << endl;
                vector<json> vec;
                int j = 0;
                while (j < buses.size())
                {
                    Bus b = buses[j];
                    // string jsonstring=u.name+u.age;
                    json js;
                    js["name"] = b.name;
                    js["num"] = b.num;
                    vec.push_back(js);
                    j++;
                }
                json J = vec;
                string jsonstring = J.dump();
                write(connfd, jsonstring.c_str(), jsonstring.size());
            }
            else
            {
                cout << "From client: " << 400 << " To client : " << 400 << endl;
            }
        }
        else
        {
            cout << "From client: " << 400 << " To client : " << 400 << endl;
        }
        memset(buff, 0, MAX);
    }
}
// Driver fuction
int main()
{
    int sockfd, connfd;
    socklen_t len;
    sockaddr_in servaddr{}, cli{};
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
    func(connfd);

    // After chatting close the socket
    close(sockfd);
}
