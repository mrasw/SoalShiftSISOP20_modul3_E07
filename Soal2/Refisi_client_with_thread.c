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

pthread_t tid_scrn[3];

    int sock , valread;
    char regist[1024];
    char start[1024];
    char usrname[50];
    char passwrd[50];

void screen2();
void screen1();
void find();

void* th_screen(void *arg)
{
    pthread_t id_scrn = pthread_self();

    if(pthread_equal(id_scrn,tid_scrn[0]))
    {
        char input[25];
        int daftar = 1;
        int login = 1;
        scanf("%s",input);

        if(strcmp("login",input) == 0)
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
        }
        else if(strcmp("Auth Failed",regist) == 0)
        {
            printf("Register Failed\n");
        }
        else if((login = strcmp("Login Success",regist)) == 0)
        {
            printf("%s\n",regist);
        }
        else if(strcmp("Login Failed",regist) == 0)
        {
            printf("%s\n",regist);
        }

        if(daftar == 0 || login == 0)
        {
            screen2();        
        }
    }

    else if(pthread_equal(id_scrn,tid_scrn[1]))
    {
        char input[25];
        int daftar = 1;
        int login = 1;
        int cek;
        scanf("%s",input);

        if(strcmp("logout",input) == 0)
        {
            send(sock, input, strlen(input), 0);
            screen1();
        }

        else if(strcmp("find",input) == 0)
        {
            cek = send(sock, input, strlen(input), 0);
            printf("dah mau kirim ke server\n");
            printf("%d %s\n",cek,input);
            find();
            printf("baru keluar dari fungsi find\n");
        }
    }

    else if(pthread_equal(id_scrn,tid_scrn[2]))
    {
        
    }

    else if(pthread_equal(id_scrn,tid_scrn[3]))
    {
        int HP = 100;
        char enemys_attck[1024];

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
}


void screen1()
{
    char *argv[] = {"clear",NULL};
    pid_t child;

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

    pthread_create(&(tid_scrn[0]),NULL,&th_screen,NULL);

    pthread_join(tid_scrn[0],NULL);

}

void screen2()
{
                // printf("%d",id_client);
    char *argv[] = {"clear",NULL};
    pthread_t ID = pthread_self();
    pid_t child1;

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

    pthread_create(&(tid_scrn[1]),NULL,&th_screen,NULL);

    pthread_join(tid_scrn[1],NULL);

}

void find()
{
    // printf("dah masuk ke fungsi find\n");
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

            sleep(1);

            pthread_create(&(tid_scrn[2]),NULL,&th_screen,NULL);
            pthread_create(&(tid_scrn[3]),NULL,&th_screen,NULL);
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

    screen1();

}






        // if(ntohs(newAddr.sin_port)!=0)
		// {
		// 	check = check + 1;

		// 	if(check == 2)
		// 	{
		// 		printf("Lets the battle begin.....\n");
		// 	}
		// }
