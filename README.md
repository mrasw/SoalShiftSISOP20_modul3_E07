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
selanjutnya ketika palyer memasukkan perintah "find" (mencari lawan), maka server akan mencarikan lawan dengan melakukan pengelompokkan pada player player yang memasukkan perintah "find" kedalam fungsi "send_message"
```c
void send_message(int sock_player,int start)
{
    int cek_id = 0;
    int player[5];
    int player_id = 0;
    char message[1024];
    int valread;
    pid_t child;
```
mendeklarasikan variabel
```c
    while(1)
    {
        if(sock_player == client[cek_id])
        {   
            if((child = fork()) == 0)
            {
             
                while(1)
                {
                    valread = read(sock_player, status, 1024);
                    if(strcmp("find",status) == 0);
                    {
                        player[player_id] = sock_player;
                        player_id++;
                        status[0] = '\0';
                    }
```
operasi diatas melakukan pengelompokkan untuk setiap player yang memasukkan perintah "find" dan memberikan id pada player tersebut kemudian disimpan pada array "player[]" (yang dideklarasikan sebelumnya)
```c
                    if(((player_id) % 2) == 0 && start == 1)
                    {
                        send(sock_player, found, strlen(found), 0);
```
kemudian untuk jumlah player yang memasukkan perintah "find" genap dan tidak sama dengan 0, maka game akan dimulai dengan mengirimkan pesan kepada player bahwa game akan dimulai kemudian
```c
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
    }
}
```
kemudian server akan melayani pengiriman serangan dari player1 ke player2 berdasarkan sock dari tiap player

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
### Screen 2

deklarasivariabel untuk screen2
```c
        char input[25];
        int daftar = 1;
        int login = 1;
        int cek;
```

#### ★ Pada screen 2 anda dapat menginputkan “logout” setelah logout anda akan kembali ke screen 1
```c
        scanf("%s",input);

        if(strcmp("logout",input) == 0)
        {
            send(sock, input, strlen(input), 0);
            screen1();
        }
```
#### ★ Pada screen 2 anda dapat menginputkan “find”, setelah itu akan menampilkan pesan “Waiting for player ...” print terus sampai menemukan lawan

#### ★ Jika menemukan lawan maka akan menampilkan pesan “Game dimulai silahkan ​ tap ​ ​ tap ​ secepat mungkin !!”
```c
        else if(strcmp("find",input) == 0)
        {
            cek = send(sock, input, strlen(input), 0);
            printf("dah mau kirim ke server\n");
            printf("%d %s\n",cek,input);
            find();
        }
```
menuju fungsi find()
```c
void find()
{
    while(1)
    {
        printf("waiting for player....\n");

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
```
#### ★ Jika health anda <= 0 maka akan menampilkan pesan “Game berakhir kamu kalah”, apabila lawan anda healthnya <= 0 maka akan menampilkan pesan ”Game berakhir kamu menang”
```c
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
```

## Soal 4

4a
Pertama, dideklarasikan variabel yang digunakan untuk menyimpan matriks yang akan dikalikan serta matriks hasilnya. Selanjutnya, fungsi perkalian dibuat untuk mengalikan matriks. Matriks hasil merupakan hasil matriks3 sebelumnya ditambah hasil perkalian matriks1 dengan matriks 2. Pada fungsi main, dibuat perulangan untuk mengisi matriks 1 dan 2 dengan ngka random. Kemudian matriks 1 dan 2 ditampilkan isinya ke layar. Selanjutnya, dilakukan perulangan dengan thread yang memanggil fungsi perkalian sebanyak empat kali sesuai dengan baris matriks. Lalu, dibuat join thread agar masing - masing thread dapat menyelesaikan tugasnya sampai selesai terlebih dahulu. Selanjutnya, matriks hasil perkalian ditampilkan ke layar.

4c
Pertama, variabel fds untuk pipe dideklarasikan. Selanjutnya, jika pipe(fds) mengembalikan -1 artinya pipe fail. Lalu, dilakukan fork. Saat pid mengembalikan nol, maka proses anak berhasil dibuat. Kemudian standar output file deskriptor dari child ditutup. Input dituliskan ke pipe. Input ini berasal dari output perintah execlp. Lalu, pipe ditutup. Perintah ls execlp kemudian berjalan. Saat pid mengembalikan bukan nol artinya proses berada pada parent. Pertama, standar input file deskriptor ditutup. Selanjutnya dilakukan reading output dari pipe yang selanjutnya menjadi input execlp. Kemudian, pipe yang digunakan untuk write ditutup. Selanjutnya, command wc execlp berjalan menghitung file dan folder di direktori.
