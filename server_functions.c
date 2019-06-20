#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
 #include <unistd.h>

#include "challenges.h"

char client_answer[256]={0};

/*
** AUXILIAR FUNCTIONS
*/

// function from https://stackoverflow.com/questions/2347770/how-do-you-clear-the-console-screen-in-c
void clrscr(){
    system("@cls||clear");
}

void clean_buffer(char * buffer){
    for(int i=0;i<256;i++)
        buffer[i]='\0';
}

/*
** CHALLENGES
*/

//Challenges are listed in reverse order (12th --> 1st)

void execute_challenge(char * challenge, char * question, char * answer, int client_socket){
    printf("%s",CHALLENGE_TXT);
    printf("%s\n\n",challenge);
    printf("%s",QUESTION_TXT);
    printf("%s",question);
    do{
        clean_buffer(client_answer);
        recv(client_socket, &client_answer, sizeof(client_answer), 0);
    }while(strcmp(client_answer, answer)!=0);
    printf("Respuesta correcta\n");
    clrscr();
}

void libc(int client_socket){
    char * challenge="/lib/x86_64-linux-gnu/libc-2.19.so ?";
    char * answer="/lib/x86_64-linux-gnu/ld-2.19.so\n";
    execute_challenge(challenge, TWELVETH_Q, answer, client_socket);
    puts(FINAL_MESSAGE);
}

// DONE ? NO
void gdbme(int client_socket){
    char * challenge="b gdbme y encontrá el valor mágico\ntry again";
    char * answer="gdb rules\n";
    execute_challenge(challenge, ELEVENTH_Q, answer, client_socket);
    libc(client_socket);
}

// DONE ? NO, I cannot seem to catch the exit error for gcc compilation terminated
void quine(int client_socket){
    
    int exit_status;
    exit_status=system("gcc -o ./quine.o ./quine.c; ./quine.o");
    
    if(exit_status==EXIT_SUCCESS){    
        char * challenge="La respuesta a este desafio es cachiporra";
        char * answer="cachiporra\n";
        execute_challenge(challenge, TENTH_Q, answer, client_socket);
        gdbme(client_socket);
    }
    else{
        printf("There is something wrong!!!\n");
    }
}

void many_words(int client_socket){
    char * challenge="Tango Hotel India Sierra India Sierra Alfa Whiskey Echo Sierra Oscar Mike Echo";
    char * answer="this is awesome\n";
    execute_challenge(challenge, NINTH_Q, answer, client_socket);
    quine(client_socket);
}

// DONE ? NO
void mixed_fds(int client_socket){
    char * challenge="TODO: function that encodes the answer here";
    char * answer="indeterminado\n";
    execute_challenge(challenge, EIGHTH_Q, answer, client_socket);
    many_words(client_socket);
}

// DONE ? NO
void sections(int client_socket){
    char * challenge=".data .bss .comment ? .shstrtab .symtab .strtab";
    char * answer=".runme\n";
    execute_challenge(challenge, SEVENTH_Q, answer, client_socket);
    mixed_fds(client_socket);
}

// DONE ? NO
void pumpkin(int client_socket){
    char * challenge="respuesta = strings[224]";
    char * answer="easter_egg\n";
    execute_challenge(challenge, SIXTH_Q, answer, client_socket);
    sections(client_socket);
}

// DONE ? NO
void ebadf(int client_socket){
    char * challenge="EBADF... abrilo y verás";
    char * answer="cabeza de calabaza\n";
    execute_challenge(challenge, FIFTH_Q, answer, client_socket);
    pumpkin(client_socket);
}

void vocaroo(int client_socket){
    char * challenge="https://vocaroo.com/i/s19015zmR4t8";
    char * answer="nokia\n";
    execute_challenge(challenge, FOURTH_Q, answer, client_socket);
    ebadf(client_socket);
}

void shoot_challenges(int client_socket){
    char * challenge="# \\033[D \\033[A \\033[A \\033[D \\033[B \\033[C \\033[B \\033[D *";
    char * answer="#0854780*\n";
    execute_challenge(challenge, THIRD_Q, answer, client_socket);
    vocaroo(client_socket);
}