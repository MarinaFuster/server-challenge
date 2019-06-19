#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "challenges.h"

#define CHALLENGE_QTY 11

extern void shoot_challenges(int client_socket);
extern void clrscr();

int main(){

    // create a server socket 
    int socket_desc;
     
    // AF_INET -> type of addresses my socket can communicate with (Internet Protocol v4 addresses this case)  
    // SOCK_STREAM -> indicates type of socket, TCP socket
    // 0 -> protocol value for Internet Protocol
    socket_desc = socket(AF_INET,SOCK_STREAM,0);
    if(socket_desc == 0){
        perror("Socket creation failed\n");
        exit(EXIT_FAILURE);
    }

    // define the server address
    struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(9003);

    // binds our IP and port
    bind(socket_desc , (struct sockaddr *)&server , sizeof(server));

    // listen allows us to listen for connections 
    // number of connections that can be waiting to connect -> 1, we do not have to deal with traffic
    listen(socket_desc, 1);

    // accept client socket
    int client_socket;
    // we are at a local machine so the address at which the client is connected is not useful for us
    client_socket = accept(socket_desc, NULL, NULL);

    puts(INITIAL_MESSAGE);

    char client_answer[256]={0};

    do{
        recv(client_socket, &client_answer, sizeof(client_answer), 0);
    }while(strcmp(client_answer, "entendido\n")!=0);
    clrscr();
    shoot_challenges(client_socket);

    puts(FINAL_MESSAGE);
    
    // close socket once we are done
    close(socket_desc);

    return 0;
}