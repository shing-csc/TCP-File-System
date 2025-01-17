#include <iostream>
#include <fstream>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>
#include <memory>

#include <string>
#include <cstring>

#include "../include/client_upload.h"

using namespace std;
const int PORT = 8080;
const int BUFFER_SIZE = 1024;


int main(){
    
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    string command = "UNDEFINED";

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");


    // Clientsocket establish connection to the server
    if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1){
        cerr << "Unable to connect to server" << endl;
        close(clientSocket);
        return -1;
    }


    while(true){
        cout << "command { UPLOAD (U) | DOWNLOAD (D) | REMOVAL (R) | EXIT (E)}: " << endl;
        cin >> command;

        if (command == "U"){
            send(clientSocket, "U", strlen("U"), 0);
            handleUpload(clientSocket, BUFFER_SIZE);
        }
        else if (command == "D"){
            send(clientSocket, "D", strlen("D"), 0);
        }
        else if (command == "R"){
            send(clientSocket, "R", strlen("R"), 0);
        }
        else if (command == "E"){
            send(clientSocket, "E", strlen("E"), 0);
            break;
        }
        else{
            send(clientSocket, "U", strlen("U"), 0);
        }
    }
    
    
    close(clientSocket);
    return 0;
}