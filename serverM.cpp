//cite TCP socket code from https://www.geeksforgeeks.org/socket-programming-cc/
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <errno.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <ctype.h>

#define PORTMU    24270
#define PORTMC    25270
#define PORTMM    26270
#define PORTA     21270
#define PORTB     22270
#define PORTC     23270
#define MAXLINE 1024
#define MSG_CONFIRM 0

using namespace std;
int glob = 0;
//get parsing code from https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c reply 102
vector< vector <string> > split (const string &s, char delim1, char delim2) {
    vector< vector < string > > result;
    stringstream ss (s);
    string item;
    string item2;
    
    while (getline (ss, item, delim1)) {
        
        result.push_back (vector<string>());
        stringstream sstream(item);
        while((getline (sstream, item2, delim2))){
            result.back().push_back(item2);
        }
    }
    
    return result;
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
//get sort code from https://www.geeksforgeeks.org/sorting-2d-vector-in-c-set-1-by-row-and-column/
bool sortcol(const vector<string>& v1, const vector<string>& v2)
{
    return stoi(v1[0]) < stoi(v2[0]);
}

//cite modified from https://stackoverflow.com/questions/12557135/converting-simple-c-encryption-to-c
void encrypt(int offset, char *str) {

int i,l;

l=strlen(str);

printf("\nUnencrypted str = \n%s\n", str);

    for(i=0;i<l;i++){
        if (str[i]!=32){
            str[i] = str[i]+ offset;
        
            if(!isalpha(str[i])){
                str[i] -= 26;
            }
        }
    }
printf("\nEncrypted str = \n%s \nlength = %d\n", str, l);
}

void decrypt(int offset, char *str) {

int i,l;

l=strlen(str);

    for(i=0;i<l;i++){
        if (str[i]!=32){
            str[i] = str[i]- offset;
            //if(!((str[i]>64&&str[i]<91)||(str[i]>96&&str[i]<123))){
            if(!isalpha(str[i])){
                str[i] += 26;
            }
        }
    }
}


int coin(vector<vector < string > > in, string name){
    int res = 1000;
    //char *name1 = &name[0];
    //encrypt(3, name1);
    int flag = 0;
    for (int i = 0; i<in.size(); i++){
        if(strcmp(in[i][1].c_str(), name.c_str()) == 0){
            res -= stoi(in[i][3]);
            flag+=1;
        }
        if(strcmp(in[i][2].c_str(), name.c_str()) == 0){
            res += stoi(in[i][3]);
            flag+=1;
        }
    }
    if(flag>0){
        return res;
    }
    else{
        return -99;
    }
    
}

int checkTrans(vector<vector < string > > in, string name1, string name2, int money){
    char *n1 = &name1[0];
    char *n2 = &name2[0];
    encrypt(3, n1);
    encrypt(3, n2);
    int flag1 = 0;
    int flag2 = 0;
    for (int i = 0; i<in.size(); i++){
        if(strcmp(in[i][1].c_str(), n1) == 0){
            flag1+=1;
        }
        if(strcmp(in[i][2].c_str(), n1) == 0){
            flag1+=1;
        }
        if(strcmp(in[i][1].c_str(), n2) == 0){
            flag2+=1;
        }
        if(strcmp(in[i][2].c_str(), n2) == 0){
            flag2+=1;
        }
    }
    
    if(flag1>0&&flag2>0){
        int sq = coin(in,name1);
        
        if(sq>=money){
            
            return 1;
        }
        else{
            return 2;
        }
    }
    else if(flag2>0){
        return 7;
    }
    else if(flag1>0){
        return 3;
    }
    else{
        return 4;
    }
    
}



int main(int argc, char const* argv[])
{
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = { 0 };
    char* hello = "Hello from M TCP";
 
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0))
        == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
 
    
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR , &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORTMC);
 
    // Forcefully attaching socket to the port 8080
    if (::bind(server_fd, (struct sockaddr*)&address,
             sizeof(address))
        < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    
    cout<<"The main server is up and running."<<endl;
    while ((new_socket
         = accept(server_fd, (struct sockaddr*)&address,
                  (socklen_t*)&addrlen))
        > 0) {
    
    //READ from client
    valread = read(new_socket, buffer, 1024);
    //printf("%s\n", buffer);
    
        
        
        vector<string> client = split2(buffer,' ');
        vector<string> enclient = split2(buffer,' ');
        char *test1 = &enclient[0][0];
        encrypt(3, test1);
        if(enclient.size()>1){
            char *test2 = &enclient[1][0];
            encrypt(3, test2);
        }
        
        encrypt(3, buffer);
        

        if(client.size()==1){
            if(strcmp(client[0].c_str(), "TXLIST")==0){
                cout<<"The main server received a sorted list request from the monitor using TCP over port "<<PORTMC<<"."<<endl;
            }
            else{
                cout<<"The main server received input=\""<<client[0]<<"\" from the client using TCP over port "<<PORTMC<<"."<<endl;
            }
        }
        else{
            cout<<"The main server received from "<<client[0]<<" to transfer "<<client[2]<<" coins to "<<client[1]<<" using TCP over port <port number>."<<endl;
        
        }
    
    
    //cite UDP socket code from https://www.geeksforgeeks.org/udp-server-client-implementation-c/
    
    int sockfd;
    char buffer2[MAXLINE];
        char bufferin[MAXLINE];
        char bufferin2[MAXLINE];
        char bufferin3[MAXLINE];
    char *hello2 = "Hello from M UDP";
    struct sockaddr_in     servaddr, newaddr,servaddr2,servaddr3;
    
    // Creating socket file descriptor
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
    
    memset(&servaddr, 0, sizeof(servaddr));
        
    // Filling server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORTA);
    servaddr.sin_addr.s_addr = INADDR_ANY;
        servaddr2.sin_family = AF_INET;
        servaddr2.sin_port = htons(PORTB);
        servaddr2.sin_addr.s_addr = INADDR_ANY;
        servaddr3.sin_family = AF_INET;
        servaddr3.sin_port = htons(PORTC);
        servaddr3.sin_addr.s_addr = INADDR_ANY;
        
    int n;
    socklen_t len;
    
    //send to back serverA
        //encrypt(3,buffer);
        
        char* con = "1";
        string con2 = enclient[0];
        if(enclient.size()>1){
            con2 = con2 + " " + enclient[1] + " " + enclient[2];
        }
    
    sendto(sockfd, (char *)con2.c_str(), strlen((char *)buffer),
        MSG_CONFIRM, (const struct sockaddr *) &servaddr,
            sizeof(servaddr));
        cout<<"The main server sent a request to server A."<<endl;
    
        
    //recieve from back end
    n = recvfrom(sockfd, (char *)bufferin, MAXLINE,
                MSG_WAITALL, (struct sockaddr *) &newaddr,
                &len);
        cout<<"The main server received transactions from Server A using UDP over port "<<PORTMU<<"."<<endl;
        bufferin[n] = '\0';
    
        
        
        //send to back serverB
        sendto(sockfd, (char *)con2.c_str(), strlen((char *)buffer),
            MSG_CONFIRM, (const struct sockaddr *) &servaddr2,
                sizeof(servaddr2));
            cout<<"The main server sent a request to server B."<<endl;
        
            
        //recieve from back end
        n = recvfrom(sockfd, (char *)bufferin2, MAXLINE,
                    MSG_WAITALL, (struct sockaddr *) &newaddr,
                    &len);
            cout<<"The main server received transactions from Server B using UDP over port "<<PORTMU<<"."<<endl;
            bufferin2[n] = '\0';
        
        
        
        
        //send to back serverC
        sendto(sockfd, (char *)con2.c_str(), strlen((char *)buffer),
            MSG_CONFIRM, (const struct sockaddr *) &servaddr3,
                sizeof(servaddr3));
            cout<<"The main server sent a request to server C."<<endl;
        
            
        //recieve from back end
        n = recvfrom(sockfd, (char *)bufferin3, MAXLINE,
                    MSG_WAITALL, (struct sockaddr *) &newaddr,
                    &len);
            cout<<"The main server received transactions from Server C using UDP over port "<<PORTMU<<"."<<endl;
            bufferin3[n] = '\0';
        
        
        
        
        
    //send to client
    
        
        if(strcmp(bufferin, "nloo") == 0){
            send(new_socket, (char *)bufferin, strlen(bufferin), 0);
        }
        else if(client.size()==1){
            
            if(strcmp(client[0].c_str(), "TXLIST")==0){
                vector<vector < string > > res = split(bufferin,'\n',' ');
                vector<vector < string > > res2 = split(bufferin2,'\n',' ');
                vector<vector < string > > res3 = split(bufferin3,'\n',' ');
                res.insert(res.end(),res2.begin(),res2.end());
                res.insert(res.end(),res3.begin(),res3.end());
                glob = res.size();
                sort(res.begin(), res.end(), sortcol);
                string out = "";
                int m = res.size();
                int n = res[0].size();
                for (int i = 0; i < m; i++) {
                    for (int j = 0; j < n; j++){
                        if(j==1 or j==2){
                            char *temp1 = &res[i][j][0];
                            decrypt(3, temp1);
                            out = out + temp1 + " ";
                        }
                        else{
                            out = out + res[i][j] + " ";
                        }
                    }
                    out += "\n";
                }
                ofstream MyFile("txchain.txt");
                MyFile << out;
                MyFile.close();
                string tosend = "Successfully received a sorted list of transactions from the main server.";
                send(new_socket, (char *)tosend.c_str(), strlen(tosend.c_str()), 0);
            }
            else{
                vector<vector < string > > res = split(bufferin,'\n',' ');
                vector<vector < string > > res2 = split(bufferin2,'\n',' ');
                vector<vector < string > > res3 = split(bufferin3,'\n',' ');
                res.insert(res.end(),res2.begin(),res2.end());
                res.insert(res.end(),res3.begin(),res3.end());
                glob = res.size();
                char *temp1 = &enclient[0][0];
                //encrypt(3, temp1);
                int ret = coin(res,temp1);
                string ret2 = to_string(ret);
                if(ret >0 ){
                    ret2 = "The current balance of \""+client[0]+"\" is : "+ret2+" txcoins.";
                }
                else{
                    ret2 = client[0]+" is not part of the network";
                }
                char const *ret3 = ret2.c_str();
                //cout<<"hey "<<ret<<endl;
                send(new_socket, (char *)ret3, strlen(ret3), 0);
                cout<<"The main server sent the current balance to the client."<<endl;
            
            }
        }
        else{
            vector<vector < string > > res = split(bufferin,'\n',' ');
            vector<vector < string > > res2 = split(bufferin2,'\n',' ');
            vector<vector < string > > res3 = split(bufferin3,'\n',' ');
            res.insert(res.end(),res2.begin(),res2.end());
            res.insert(res.end(),res3.begin(),res3.end());
            glob = res.size();
            int trans = checkTrans(res,client[0],client[1],stoi(client[2]));
            string trans2 = to_string(trans);
            string tosend = "";
            if(trans == 1){
                char *temp1 = &enclient[0][0];
                //encrypt(3, temp1);
                int t = coin(res,temp1);
                t -= stoi(client[2]);
                trans2 = trans2 + " " + to_string(t);
                
                //make trans update
                string co(con);
                co = co + " " + to_string(glob+1);
                if(glob%3 == 0){
                    sendto(sockfd, (char *)co.c_str(), strlen((char *)co.c_str()),
                           MSG_CONFIRM, (const struct sockaddr *) &servaddr,
                           sizeof(servaddr));
                }
                else if(glob%3 == 1){
                    sendto(sockfd, (char *)co.c_str(), strlen((char *)co.c_str()),
                           MSG_CONFIRM, (const struct sockaddr *) &servaddr2,
                           sizeof(servaddr2));
                }
                else{
                    sendto(sockfd, (char *)co.c_str(), strlen((char *)co.c_str()),
                           MSG_CONFIRM, (const struct sockaddr *) &servaddr3,
                           sizeof(servaddr3));
                }
                tosend = client[0]+" successfully transferred "+client[2]+" txcoins to "+client[1]+".The current balance of "+client[0]+" is : "+to_string(t)+" txcoins.";
                
            }
            if(trans == 2){
                char *temp1 = &enclient[0][0];
                //encrypt(3, temp1);
                int t = coin(res,temp1);
                trans2 = trans2 + " " + to_string(t);
                tosend = client[0]+" was unable to transfer "+client[2]+" txcoins to "+client[1]+" because of insufficient balance.The current balance of "+client[0]+" is : "+to_string(t)+" txcoins";
            }
            if(trans == 3){
                tosend = "Unable to proceed with the transaction as "+client[1]+" is not part of the network.";
            }
            if(trans == 4){
                tosend = "Unable to proceed with the transaction as "+client[0]+" and "+client[1]+" are not part of the network.";
            }
            if(trans == 7){
                tosend = "Unable to proceed with the transaction as "+client[0]+" is not part of the network.";
            }
            char const *trans3 = trans2.c_str();
            send(new_socket, (char *)tosend.c_str(), strlen(tosend.c_str()), 0);
            cout<<"The main server sent the result of the transaction to the client."<<endl;
        }
        if(strcmp(buffer, "nloo")==0){
            break;
        }
    }
  // closing the connected socket
        
        close(new_socket);
  // closing the listening socket
        shutdown(server_fd, SHUT_RDWR);
        return 0;
    
}
    
