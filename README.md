# SoalShiftSISOP20_modul3_E07

## Soal 2

### SERVER SIDE

#### varibel yang terdapat pada server

```c
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
```

#### ★ Pada saat program pertama kali dijalankan maka program akan membuat file akun.txt jika file tersebut tidak ada. File tersebut digunakan untuk menyimpan username dan password.

```c
FILE *fp,*fp2,*fp3;
fp = fopen("akun.txt","a");
```

#### ★ Pada saat user berhasil login maka akan menampilkan pesan “Auth success” jika gagal “Auth Failed”.

```c
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
                    fscanf(fp4,"%s",username);
                    fscanf(fp4,"%s",password);
                    test1 = strcmp(S_username,username);
                    test2 = strcmp(S_password,password);

                    if(test1==0 && test2==0)
                    {
                        break;
                    }
                }

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
```

untuk login, akan menerima username serta password yang akan di validasi dengan menggunakan
```c

                read( new_socket, S_username, 1024);
                read( new_socket, S_password, 1024);
```
kemudian username serta password tersebut akan di cek apakah telah terdaftar didalam akun.txt dengan menggunakan
```c
                while((c = getc(fp4)) != EOF)
                {
                    fscanf(fp4,"%s",username);
                    fscanf(fp4,"%s",password);
                    test1 = strcmp(S_username,username);
                    test2 = strcmp(S_password,password);

                    if(test1==0 && test2==0)
                    {
                        break;
                    }
                }
```

#### ★ Pada saat user sukses meregister maka akan menampilkan List account yang terdaftar (username dan password harus terlihat)

```c
valread = read( new_socket, status, 1024);

            if( strcmp("register",status)==0 )
            {
                char c;
                FILE *fp,*fp2,*fp3;
                fp = fopen("akun.txt","a");
                read( new_socket, S_username, 1024);
                read( new_socket, S_password, 1024);

                fprintf(fp,"%s",S_username);
                fputs(" ",fp);
                fprintf(fp,"%s",S_password);
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
```
untuk register, code akan menerima username serta password yang akan didaftarkan dengan menggunakan
```c

                read( new_socket, S_username, 1024);
                read( new_socket, S_password, 1024);
```
jika telah terdaftar akan mengirimkan pesan pada client "Auth Success" jika tidak akan mengirimkan pesan pada client "Auth Failed" 
```c
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
```
dalam code diatas menunjukkan bahwa, ketika client melakukan register usename serta password akan di simpan pada akun.txt
dengan menggunakan
```c
fprintf(fp,"%s",S_username);
fputs(" ",fp);
fprintf(fp,"%s",S_password);
fputs("\n",fp);
```
kemudian akan dilakukan validasi apakah username serta password benar benar tersimpan dalam file akun.txt sekaligus mengirimkan pesan pada client bahwa akun telah terdaftar
```c
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
```
kemudian menampilkan list akun-akun yang telah terdaftar pada server dengan
```c
                fp2 = fopen("akun.txt","r");
                while((c = getc(fp2)) != EOF)
                {
                    printf("%c",c);
                }
                fclose(fp2);
```
### Client Side
