#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <wait.h>
#define PORT 8080

// pthread_t tid_scrn[3];

    int sock , valread;
    char regist[1024];
    char start[1024];
    char usrname[50];
    char passwrd[50];

void screen1(int);
void screen2(int);
void find(int);

void login(char input[25])
{
    char recv[25];

    strcpy(recv,input);

    send(sock, recv, strlen(recv), 0);
    printf("[[[==========-> LOGIN <-==========]]]\n");
    printf("Username:\t");
    scanf("%s",usrname);
    send(sock, usrname, strlen(usrname), 0);
    printf("Password:\t");
    scanf("%s",passwrd);
    send(sock, passwrd, strlen(passwrd), 0);
}

void screen1(int sock)
{
    char *argv[] = {"clear",NULL};
    pid_t child;

    char input[25];
    int daftar = 1;
    int masuk = 1;

    child  = fork();

    wait(NULL);
    if(child == 0)
    {
        execv("/usr/bin/clear", argv);
    }

    else
    {            
        printf("[[[=========->> WELCOME <<-=========]]]\n");
        printf("1.Login\n");
        printf("2.Register\n");
        printf("Choice:\t"); 
    }

            scanf("%s",input);

            if(strcmp("login",input) == 0)
            {
                login(input);
            }

            else if(strcmp("register",input) == 0)
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
            if((daftar = strcmp("Auth Success",regist)) == 0)
            {
                printf("Register Success\n");
                    login("login");
            }
            else if(strcmp("Auth Failed",regist) == 0)
            {
                printf("Register Failed\n");
            }
            else if((masuk = strcmp("Login Success",regist)) == 0)
            {
                printf("%s\n",regist);
                    screen2(sock);  
            }
            else if(strcmp("Login Failed",regist) == 0)
            {
                printf("%s\n",regist);
            }

}

void screen2(int sock)
{
                // printf("%d",id_client);
    char *argv[] = {"clear",NULL};
    pid_t child1;

    char input[25];
    int daftar = 1;
    int login = 1;
    int cek;

    child1 = fork();

    wait(NULL);
    if(child1 == 0)
    {
        execv("/usr/bin/clear", argv);
    }

    else
    {            
        printf("[[[=========->> WELCOME <<-=========]]]\n");
        printf("1.Find Match\n");
        printf("2.Logout\n");
        printf("Choice:\t");
    }

            scanf("%s",input);

            if(strcmp("logout",input) == 0)
            {
                send(sock, input, strlen(input), 0);
                screen1(sock);
            }

            else if(strcmp("find",input) == 0)
            {
                cek = send(sock, input, strlen(input), 0);
                printf("dah mau kirim ke server\n");
                printf("%d %s\n",cek,input);
                find(sock);
                printf("baru keluar dari fungsi find\n");
            }

}

void find(int sock)
{
    int HP = 100;
    char enemys_attck[1024];
    printf("dah masuk ke fungsi find\n");
    // read(sock, start, 1024);
    // printf("%s",start);
    while(1)
    {
        // if(valread == 0)
        // {
            printf("waiting for player....\n");
        // }

        valread = read(sock, start, 1024);

        if(strcmp ("Found", start) == 0)
        {
            printf("Game dimulai silahkan tap tap secepat mungkin!!\n");

            while (1)
            {
                read(sock, enemys_attck, 1024);
                if(strcmp(" ",enemys_attck) == 0)
                {
                    HP=HP-10;
                    printf("%d",HP);
                }

                if(HP <= 0)
                {
                    printf("Game berakhir, kamu kalah");
                    break;
                }
            }
        }
        sleep(1);
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

    screen1(sock);

}
