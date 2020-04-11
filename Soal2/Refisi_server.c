#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#define PORT 8080

pthread_t tid[2];

    char status[1024] = {0};
	char *found = "Found";
    int client[5];
	int id_client = 0;

void send_message(int, int);

// void* playgame(void *arg)
// {
//     pthread_t id = pthread_self();

//     if()
// }

int main(int *argc, char const *argv[])
{
    int server_fd;
    struct sockaddr_in address;

    int sock_player;
    struct sockaddr_in newAddr;

    socklen_t addr_size;
    pid_t childpid;
    pid_t childgame;

    int valread;
    // int client[5];
    int client_tot = 0;
    int opt = 1;
    int check = 0;
    int addrlen;
    char username[1024];//untuk nyimpan username dari akun.txt
    char password[1024];//untuk nyimpan password dari akun.txt
    char S_username[1024];//untuk nerima username
    char S_password[1024];//untuk nerima password
    int start = 0;
    char *auth1 = "Auth Success";
    char *auth0 = "Auth Failed";
    char *login1 = "Login Success";
    char *login0 = "Login Failed";
	int last_client = 0;
	// int id_client = 0;

    int test1,test2;

    //membuat master socket
    if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socked failed");
        exit(EXIT_FAILURE);
    }

    //set master socket to allow multiple connection
    //this is just a good habit, it still work without this
    if((setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    //accept the incoming connections
    memset(&address,'\0',sizeof(address));
    // addrlen = sizeof(address);
    // puts("waiting for connections...");

    //type of socket created
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
    // printf("%d",address.sin_addr.s_addr);

    //bind the socket to localhost port 8080
    if(bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    //maksimal ada 3 koneksi yangditunda untuk master socket
    if(listen(server_fd,3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    while(1)
    {
        // sock_player = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        sock_player = accept(server_fd, (struct sockaddr *)&newAddr, &addr_size);
        
        if( sock_player < 0)
        {
            perror("accept");
            exit(EXIT_FAILURE);
        }
                        // printf("%d\n",sock_player);

     	if(sock_player != 0)
		{
			if(last_client == 0)
			{
				last_client = sock_player;
				printf("The first client's socket is: %d\n",last_client);
			}

			if(sock_player != last_client || last_client != 0)
			{
                printf("%d\n",id_client);
				client[id_client] = sock_player;

				last_client = sock_player;
				printf("Client's id %d of the socket number %d\n",id_client,sock_player);
				
				if( (id_client)%2 == 0)
				{
					// send(client[last_client], found, strlen(found), 0);
					// send(client[last_client - 1], found, strlen(found), 0);
                    start = 1;
				}

				id_client++;
                printf("%d\n",id_client);
			}
		}

        if((childpid = fork()) == 0)
        {
            close(server_fd);
            while(1)
            {
                valread = read( sock_player, status, 1024);
                // printf("%d",valread);
                // printf("%s\n",status);

                if( strcmp("register",status)==0 )
                {
                    char c;
                    FILE *fp,*fp2,*fp3;
                    fp = fopen("akun.txt","a");
                    read( sock_player, S_username, 1024);
                    read( sock_player, S_password, 1024);

                    printf("%s\n",S_username);
                    printf("%s\n",S_password);

                    fprintf(fp,"%s",S_username);
                    fputs(" ",fp);
                    fprintf(fp,"%s",S_password);
                    // fputc('\0',fp);
                    fputs("\n",fp);
                    fclose(fp);

                    fp2 = fopen("akun.txt","r");
                    while((c = getc(fp2)) != EOF)
                    {
                        printf("%c",c);
                    }
                    fclose(fp2);

                    fp3 = fopen("akun.txt","r");
                    while((c = getc(fp3)) != EOF)
                    {
                        // printf("%s\n",S_username);
                        // printf("%s\n",S_password);
                        fscanf(fp3,"%s",username);
                        fscanf(fp3,"%s",password);
                        test1 = strcmp(S_username,username);
                        test2 = strcmp(S_password,password);

                        // printf("%d %d\n",test1,test2);
                        if(test1==0 && test2==0)
                        {
                            break; 
                        }
                    }
                    fclose(fp3);
                    if(test1==0 && test2==0)
                    {
                        send(sock_player, auth1, strlen(auth1), 0);
                    }
                    else
                    {
                        send(sock_player, auth0, strlen(auth0), 0);
                    }

                    bzero(status, sizeof(status));

                }

                else if( strcmp("login",status)==0 )
                {
                    char c;
                    int test1,test2;
                    FILE *fp4;
                    fp4 = fopen("akun.txt","r");
                    read( sock_player, S_username, 1024);
                    read( sock_player, S_password, 1024);

                    while((c = getc(fp4)) != EOF)
                    {
                        // printf("%s\n",S_username);
                        // printf("%s\n",S_password);
                        fscanf(fp4,"%s",username);
                        fscanf(fp4,"%s",password);
                        test1 = strcmp(S_username,username);
                        test2 = strcmp(S_password,password);

                        // printf("%d %d\n",test1,test2);
                        if(test1==0 && test2==0)
                        {
                            break;
                        }
                    }

                    // printf("%d %d\n",test1,test2);
                    if(test1==0 && test2==0)
                    {
                        printf("%s\n",auth1);
                        send(sock_player, login1, strlen(login1), 0);
                        
                        // read(sock_player, status, 1024);
                        if((childgame = fork()) == 0)
                        {
                            // printf("sudah menemukan musuh");
                            // fflush(stdout);
                            // send(sock_player, found, strlen(found), 0);
                            // playgame(sock_player);
                            send_message(sock_player, start);
                        }
                    }
                    else
                    {
                        printf("%s\n",auth0);
                        send(sock_player, login0, strlen(login0), 0);
                    }
                    bzero(status, sizeof(status));

                }
            }
        }
    }
    close(sock_player);

    return 0;
}

// void playgame(int sock_player)
// {
//     // printf("masuk kedalam fungsi playgame");
//     read(sock_player, status, 1024);
//     if(strcmp("find",status) == 0 );
//     {
//         // printf("sudah menemukan musuh");
//         send(sock_player, found, strlen(found), 0);
//     }
// }

void send_message(int sock_player,int start)
{
    int cek_id = 0;
    int player[5];
    int player_id = 0;
    char message[1024];
    int valread;
    pid_t child;

    while(1)
    {
        if(sock_player == client[cek_id])
        {
            printf("%d\t",sock_player);
            printf("%d\n",client[cek_id]);
            // send(client[cek_id], found, strlen(found), 0);
            // break;
            
            if((child = fork()) == 0)
            {
                while(1)
                {
                    printf("lagi masuk kirim pesan\n");
                    // valread = read(sock_player, status, 1024);
                    // send(sock_player, found, strlen(found), 0);
                    printf("%d %s\n",valread,status);
                    if(strcmp("find",status) == 0);
                    {
                        printf("lagi nunggu musuh\n");
                        // send(sock_player, found, strlen(found), 0);
                        player[player_id] = sock_player;
                        player_id++;
                    }

                    if((player_id % 2) == 0 && start == 1)
                    {
                        printf("dah masuk ke war\n");
                        send(sock_player, found, strlen(found), 0);
                        read(sock_player, message, 1024);
                        if(sock_player == player[0])
                        {
                            send(sock_player, message, strlen(message), 0);
                        }
                        if(sock_player == player[1])
                        {
                            send(sock_player, message, strlen(message), 0);
                        }
                    }
                }
            }
        }
        cek_id++;
                // send(sock_player, found, strlen(found), 0);
    }
}
