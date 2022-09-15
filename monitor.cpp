
//cite TCP socket code from https://www.geeksforgeeks.org/socket-programming-cc/
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include <vector>
#include <sstream>

#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fstream>
#include <algorithm>
#include <errno.h>
#include <netdb.h>
#include <sys/wait.h>
#define PORTMU    24270
#define PORTMC    25270
#define PORTMM    26270
#define PORTA     21270
#define PORTB     22270
#define PORTC     23270
#define MAXLINE 1024
#define MSG_CONFIRM 0
 
using namespace std;

vector<string> split2 (const string &s, char delim) {
    vector<string> result;
    stringstream ss (s);
    string item;
    while (getline (ss, item, delim)) {
        result.push_back (item);
    }
    return result;
}







int main(int argc, char const* argv[])
{
    int sock = 0, valread, client_fd;
    struct sockaddr_in serv_addr, newaddr;
    char* hello = "Hello from client C";
    char buffer[1024] = { 0 };
    char bufferin[1024] = {0};
    //char bufferr[1024] = { 0 };
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }
 
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORTMC);
    
    newaddr.sin_family = AF_INET;
    newaddr.sin_port = htons(PORTMC);
    newaddr.sin_addr.s_addr = INADDR_ANY;
    
    
    // form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)
        <= 0) {
        printf(
            "\nInvalid address/ Address not supported \n");
        return -1;
    }
 
    if ((client_fd
         = connect(sock, (struct sockaddr*)&serv_addr,
                   sizeof(serv_addr)))
        < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }
    
    cout<<"The monitor is up and running."<<endl;
    vector<string> args( argv, argv + argc );
    //printf("args ha %s\n", args[1].c_str());
    string ss = args[1];
    
    send(sock, ss.c_str(), strlen(hello), 0);
    cout<<"Monitor sent a sorted list request to the main server."<<endl;
    
    valread = read(sock, bufferin, 1024);
    printf("%s\n", bufferin);
 
    // closing the connected socket
   
    close(client_fd);
    
    return 0;
}
