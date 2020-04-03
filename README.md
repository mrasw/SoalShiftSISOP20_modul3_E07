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

#### Variabel yang terdapat pada client
```c
    int sock = 0, valread;
    char regist[1024];
    char usrname[50];
    char passwrd[50];
```
```c
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
```
#### Screen 1

##### ★ Pada screen 1 kalian dapat menginputkan “login”, setelah menekan enter anda diminta untuk menginputkan username dan password seperti berikut Username : { ex : qiqi } Password : { ex : aku nggak marah!! }

##### ★ Jika login berhasil maka akan menampilkan pesan “login success”, jika gagal akan menampilkan pesan “login failed” (pengecekan login hanya mengecek username dan password, maka dapat multi autentikasi dengan username dan password yang sama)

pertama, ketika user memasukkan pilihan login, maka client akan diminta memasukkan username serta password 

```c
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
```
setelah user memasukkan username serta password, client akan mengirimkan username serta password kepada server untuk dicek apakah valid atau tidak.

client akan menerima pesan dari server apakah username dan password benar atau salah

```c
        read(sock, regist, 1024);
```

jika username dan password benar, maka akan menampilkan "Login Success" jika tidak akan menampilkan "Login Failed" pada layar client
```c
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
```
##### ★ Pada screen 1 kalian juga dapat menginputkan “register”, setelah menekan enter anda diminta untuk menginputkan username dan password sama halnya seperti login

##### ★ Pada register tidak ada pengecekan unique username, maka setelah register akan langsung menampilkan pesan “register success” dan dapat terjadi double account

ketika user memasukkan pilihan register user akan diminta memasukkan username serta password
```c
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
```
lalu username dan password akan di kirimkan ke server untuk didaftarkan dengan menggunkan
```c
            send(sock, usrname, strlen(usrname), 0);
            send(sock, passwrd, strlen(passwrd), 0);
```
setelah itu, client akan menerima pesan dari server apakah username berhasil didaftarkan atau tidak dengan menggunakan
```c
        read(sock, regist, 1024);
```

ketika username serta password berhasil didaftarkan, akan menampilkan "Register Success" ketika gagal didaftarkan akan menampilkan "Register Failed" pada layar client
```c
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
```
