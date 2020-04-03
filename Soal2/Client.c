#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#define PORT 8080

pthread_t tid[3];
pid_t child;

    int sock = 0, valread;
    char regist[1024];
    char usrname[50];
    char passwrd[50];

void* screen1(void *arg)
{
    char *argv[] = {"clear",NULL};
    pthread_t id = pthread_self();

    if(pthread_equal(id,tid[0]))
    {
        child = fork();
        if(child == 0)
        {
            execv("/usr/bin/clear",argv);
        }
    }
    else if(pthread_equal(id,tid[1]))
    {
        char input[25];
        scanf("%s",input);

        if(strcmp("login",input)==0)
        {
            send(sock, input, strlen(input), 0);
            printf("[[[==========-> LOGIN <-==========]]]\n");
            printf("Username:\t");
            scanf("%s",usrname);
            send(sock, usrname, strlen(usrname), 0);
            printf("Password:\t");
            scanf("%s",passwrd);
            send(sock, passwrd, strlen(passwrd), 0);
        }

        else if(strcmp("register",input)==0)
        {
            send(sock, input, strlen(input), 0);
            printf("[[[==========-> REGISTRATION <-==========]]]\n");
            printf("Username:\t");
            scanf("%s",usrname);
            send(sock, usrname, strlen(usrname), 0);
            printf("Password:\t");
            scanf("%s",passwrd);
            send(sock, passwrd, strlen(passwrd), 0);
        }

        read(sock, regist, 1024);
        if(strcmp("Auth Success",regist) == 0)
        {
            printf("Register Success\n");
        }
        else if(strcmp("Auth Failed",regist) == 0)
        {
            printf("Register Failed\n");
        }
        else if(strcmp("Login Success",regist) == 0)
        {
            printf("%s\n",regist);
        }
        else if(strcmp("Login Failed",regist) == 0)
        {
            printf("%s\n",regist);
        }

    }
}

int main(int argc, char const *argv[])
{
    struct sockaddr_in addres;
    struct sockaddr_in serv_address;
    // int sock = 0, valread;
    // char regist[1024];
    // char usrname[50];
    // char passwrd[50];

    if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\nsocket cration failed\n");
        return -1;
    }

    memset(&serv_address, '0', sizeof(serv_address));

    serv_address.sin_family = AF_INET;
    serv_address.sin_port = htons(PORT);

    if(inet_pton(AF_INET, "127.0.0.1", &serv_address.sin_addr) <= 0)
    {
        printf("\n Invalid address / address not supported\n");
        return -1;
    }

    if(connect(sock, (struct sockaddr *)&serv_address, sizeof(serv_address)) < 0)
    {
        printf("\nConnection failed\n");
        return -1;
    }

    pthread_create(&(tid[0]),NULL,&screen1,NULL);
    pthread_create(&(tid[1]),NULL,&screen1,NULL);

    pthread_join(tid[0],NULL);
	pthread_join(tid[1],NULL);
}
