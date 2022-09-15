//cite UDP socket code from https://www.geeksforgeeks.org/udp-server-client-implementation-c/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
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
//get code from https://stackoverflow.com/questions/41717167/erase-empty-lines-from-a-text-file-in-c
void DeleteEmptyLines(const std::string &FilePath)
{
    std::ifstream in(FilePath);
    std::string line, text;
    while (std::getline(in, line))
        if (!(line.empty() || line.find_first_not_of(' ') == std::string::npos))
            text += line + "\n";
    in.close();
    std::ofstream out(FilePath);
    out << text;
}

//get parsing code from https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c reply 102
vector<string> split2 (const string &s, char delim) {
    vector<string> result;
    stringstream ss (s);
    string item;
    while (getline (ss, item, delim)) {
        result.push_back (item);
    }
    return result;
}
//get read text code from tutorial https://shengyu7697.github.io/cpp-read-text-file/ last 2 image
string getData(string file1){
    
    ifstream ifs1(file1);
    string buffer1;
    string temp;
        while (getline(ifs1,buffer1)) {
            if(!buffer1.empty()){
                temp+=buffer1;
                temp+='\n';
            }
        }
        //cout<<temp<<endl;
        ifs1.close();
    
    return temp;
}



// Driver code
int main() {
    int sockfd;
    char buffer[MAXLINE];
    char *hello = "Hello from server C";
    struct sockaddr_in servaddr, cliaddr;
        
    // Creating socket file descriptor
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
    
    
    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));
        
    // Filling server information
    servaddr.sin_family    = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORTC);
        
    // Bind the socket with the server address
    if ( ::bind(sockfd, (const struct sockaddr *)&servaddr,
            sizeof(servaddr)) < 0 )
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
        
    int n;
    socklen_t len;
    string save;
    cout<<"The ServerC is up and running using UDP on port 23270."<<endl;
    
    len = sizeof(cliaddr);  //len is value/result
    
    n = recvfrom(sockfd, (char *)buffer, MAXLINE,
                MSG_WAITALL, ( struct sockaddr *) &cliaddr,
                 &len);
    save = buffer;
    cout<<"The ServerC received a request from the Main Server."<<endl;
    while(n){
        buffer[n] = '\0';
        //printf("Client : %s\n", buffer);
        string rep = getData("block3.txt");
        if(strcmp(buffer, "nloo") == 0){
            sendto(sockfd, (char *)buffer, strlen(buffer),
                   MSG_CONFIRM, (const struct sockaddr *) &cliaddr,
                   len);
        }
        else{
            sendto(sockfd, rep.c_str(), strlen(rep.c_str()),
                   MSG_CONFIRM, (const struct sockaddr *) &cliaddr,
                   len);
        }
        cout<<"The ServerC finished sending the response to the Main Server."<<endl;
    //printf("Hello message sent.\n");
        getData("block3.txt");
        if(strcmp(buffer, "nloo") == 0){
            break;
        }
        memset(buffer, 0, 1024);
        n = recvfrom(sockfd, (char *)buffer, MAXLINE,
                    MSG_WAITALL, ( struct sockaddr *) &cliaddr,
                     &len);
        vector<string> vec = split2(buffer,' ');
        if(vec[0] == "1"){
            DeleteEmptyLines("block3.txt");
            //chenge text
            //get write code from https://stackoverflow.com/questions/6932409/writing-a-string-to-the-end-of-a-file-c
            ofstream out;
            out.open("block3.txt", std::ios::app);
            string save1 = vec[1]+ " " + save;
            out << save1;
            out.close();
            memset(buffer, 0, 1024);
            n = recvfrom(sockfd, (char *)buffer, MAXLINE,
                        MSG_WAITALL, ( struct sockaddr *) &cliaddr,
                         &len);
        }
        save = buffer;
        cout<<"The ServerC received a request from the Main Server."<<endl;
        //printf("JUST TESTING : %s\n", buffer);
    }
    
    
    //return 0;
}
