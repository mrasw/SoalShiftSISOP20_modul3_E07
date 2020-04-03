#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#define PORT 8080

int main(int *argc, char const *argv[])
{
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char username[1024];
    char password[1024];
    char S_username[1024];
    char S_password[1024];
    char status[1024] = {0};
    char *auth1 = "Auth Success";
    char *auth0 = "Auth Failed";
    char *login1 = "Login Success";
    char *login0 = "Login Failed";

    int test1,test2,comp;

    // FILE *fp;
    // fp = fopen("akun.txt","a");
    // char *username = "mrasw";
    // char *password = "be_humble";

    if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socked failed");
        exit(EXIT_FAILURE);
    }

    if((setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );

    if(bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if(listen(server_fd,3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    if((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }

        // while(1)
        // {
            valread = read( new_socket, status, 1024);
            // printf("%d",valread);
            // printf("%s\n",status);

            if( strcmp("register",status)==0 )
            {
                char c;
                FILE *fp,*fp2,*fp3;
                fp = fopen("akun.txt","a");
                read( new_socket, S_username, 1024);
                read( new_socket, S_password, 1024);

                // printf("%s",S_username);
                // printf("%s",S_password);

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
                        comp=1;
                        if(comp==1)
                        {
                            send(new_socket, auth1, strlen(auth1), 0);
                        }
                        else
                        {
                            send(new_socket, auth0, strlen(auth0), 0);
                        }
                        break;
                        
                    }
                }
                fclose(fp3);

            }

            else if( strcmp("login",status)==0 )
            {
                char c;
                int test1,test2;
                FILE *fp4;
                fp4 = fopen("akun.txt","r");
                read( new_socket, S_username, 1024);
                read( new_socket, S_password, 1024);

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
                    send(new_socket, login1, strlen(login1), 0);
                }
                else
                {
                    printf("%s\n",auth0);
                    send(new_socket, login0, strlen(login0), 0);
                }

            }
        // }
}
