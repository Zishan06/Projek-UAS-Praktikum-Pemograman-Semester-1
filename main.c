#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#ifdef _WIN32
    #include <Windows.h>
    #include <io.h>
    #include <direct.h>
    #include <conio.h>
#else
    #include "getch.h"
    #include <unistd.h>
    #include <sys/stat.h>
#endif

    struct pengguna{
        char username[14];
        char pass[21];
        double score;
    };
    const char *folder_name = "database";

    void clear() {
        #ifdef _WIN32
        system("cls");
        #else
        system("clear");
        #endif
    }

    void sistemregistrasi(){
        struct pengguna penggunabaru;
        char konfirpassword[14];
        clear();
        printf("╔══════════════════════════════════════════════════════╗\n");
        printf("║ Selamat datang di game TWK (Tes Wawasan Kematian)!   ║\n║ Ketik Username dan password untuk mendaftar.         ║\n");
        printf("╚══════════════════════════════════════════════════════╝\n\n");
        
        printf("-> Masukkan username     : ");
        fgets(penggunabaru.username, sizeof(penggunabaru.username), stdin);
        penggunabaru.username[strcspn(penggunabaru.username, "\n")] = '\0';

        FILE *checkfile = fopen("database/login.bin", "rb");
        if (checkfile != NULL) {
            char baris[50];
            while (fgets(baris, sizeof(baris), checkfile)) {
                char *fileUsername = strtok(baris, "#");
                if (strcmp(fileUsername, penggunabaru.username) == 0) {
                printf("Username sudah digunakan. Silakan pilih username lain.\n");
                fclose(checkfile);
                return;
                }
            }
            fclose(checkfile);
        }
            
        printf("-> Masukkan password     : ");
        fgets(penggunabaru.pass, sizeof(penggunabaru.pass), stdin);
        penggunabaru.pass[strcspn(penggunabaru.pass, "\n")] = '\0';
        
        for (int i = 0; penggunabaru.pass[i] != '\0'; i++) {
            if (!isalnum(penggunabaru.pass[i])) {
            printf("Password tidak boleh mengandung karakter special.\n");
            return;
            }
        }

        printf("-> Konfirmasi password  : ");
        fgets(konfirpassword, sizeof(konfirpassword), stdin);
        konfirpassword[strcspn(konfirpassword, "\n")] = '\0';

        if (strcmp(konfirpassword, penggunabaru.pass) != 0) {
            printf("Password yang anda masukkan tidak sama dengan yang sebelumnya.\n");
            return;
        }
         
        FILE *regis = fopen("database/login.bin", "ab");
        if (regis == NULL)
        {
            perror("Error ges");
            exit(1);
        }
        fprintf(regis, "%s#%s=0.00\n", penggunabaru.username, penggunabaru.pass);
        fclose(regis);
        printf("\n╔══════════════════════════════════════════════════════╗\n");
        printf("║----------------------- Halo! ------------------------║\n");
        printf("╚══════════════════════════════════════════════════════╝\n");
    }
   
    void buatfolder(const char *folder_name) {
    #ifdef _WIN32  //ni kalau di windows
        if (_access(folder_name, 0) == 0) 
            printf("Folder %s sudah ada. Ga perlu buat lagi.\n", folder_name);
        else {
            if (_mkdir(folder_name) == 0) 
                printf("Folder '%s' berhasil dibuat.\n", folder_name);
            else 
                perror("Error ges");
        }
    #else //ni kalau di linux
        if (access(folder_name, F_OK) == 0) 
            printf("Folder %s sudah ada. Ga perlu buat lagi.\n", folder_name);
        else {
            if (mkdir(folder_name, 0777) == 0) 
                printf("Folder '%s' berhasil dibuat.\n", folder_name);
            else 
                perror("Error ges");
        }
    #endif
    }

    void soalQuiz(double *skor, int mode){
        
        const char *soal[] = {
            "Apa nama lautan terbesar di dunia?",
            "Planet terdekat dengan matahari adalah?",
            "Siapa presiden pertama amerika serikat?",
            "Berapakah jumlah warna untuk pelangi?",
            "Siapa pelukis dari lukisan 'mona lisa'?",
            "Apa nama sungai terpanjang di dunia?",
            "Apa mata uang resmi jepang?",
            "Negara apa yang disebut dengan 'Negari Tirai Bambu'?",
            "Apa bahasa resmi di brazil?",
            "Berapa warna yang ada pada bendera italia?",
            "Satelit alami terbesar di tata surya adalah?",
            "Pelukis terkenal dengan karya the presistence of memory adalah?",
            "Dalam teori ekonomi, istilah invisible hand dikemukakan oleh?",
            "Gunung apa yang dikenal sebagai gunung berapi tertinggi di dunia?",
            "Siapa tokoh yang dikenal sebagai bapak ekonomi modern?",
            "Pada tahun berapakah perang dunia II berakhir?",
            "Indeks harga saham di jepang dikenal sebagai?",
            "Unsur kimia apa yang memiliki hg?",
            "Siapa pendiri microsoft?",
            "Siapa penulis novel 1984?"};

        const char *pilihan[][4] = {
            {"Samudra Atlantik", "Samudra Arktik", "Samudra Pasifik", "Samudra Hindia"},
            {"Venus", "Merkurius", "Mars", "Uranus"},
            {"George Washington", "Abraham Lincoln", "John Adams", "Thomas Jefferson"},
            {"5", "6", "7", "8"},
            {"Pablo Picasso", "Michelangelo", "Vincent van Gogh", "Leonardo da Vinci"},
            {"Amazon", "Nile", "Yangtze", "Mississippi"},
            {"Yuan", "Won", "Yen", "Dong"},
            {"Jepang", "China", "Korea Selatan", "Vietnam"},
            {"Portugis", "Spanyol", "Inggris", "Prancis"},
            {"3", "2", "4", "5"},
            {"Ganymede", "Titan", "Europa", "Callisto"},
            {"Pablo Picasso", "Claude Monet", "Salvador Dali", "Vincent Van Gogh"},
            {"Thomas Malthus", "Adam Smith", "Friedrich Hayek", "David Ricardo"},
            {"Mount Etna", "Kilimanjaro", "Mauna Kea", "Ojos Del Salado"},
            {"Adam Smith", "Karl Max", "John Maynard Keynes", "Milton Friedman"},
            {"1947", "1944", "1945", "1946"},
            {"Nikkei", "Dow Jones", "FTSE", "Hang Seng"},
            {"magnesium", "hidrogen", "helium", "merkuri" },
            {"Bill Gates", "Larry Page", "Mark Zuckerberg", "Steve Jobs"},
            {"Franz Kafka", "George Orwell","Aldous Huxley", "Fyodor Dostoevsky"}};

       
        const int jawabanBenar[] = {2, 1, 0, 2, 3, 1, 2, 1, 0, 0, 0, 2, 1, 3, 0, 2, 0, 3, 0, 1};
        const int sulittidak[] = {1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0};


        int jumlahSoal = sizeof(soal) / sizeof(soal[0]);
        int soalTampil[jumlahSoal];
        int soalPake;
        int sulit=0, biasa=0, maxSulit, maxBiasa;
        double poinMaks = 100.0;
        double nilaiSoal[jumlahSoal];
        memset(soalTampil, 0, sizeof(soalTampil));

        switch (mode) {
            case 0:
                maxSulit = 0;
                maxBiasa = 10;
                break;
            case 1:
                maxSulit = 3;
                maxBiasa = 4;
                break;
            case 2:
                maxSulit = 7;
                maxBiasa = 0;
                break;
        }
        soalPake = maxBiasa + maxSulit;
        int j=0;
        soal:
        while(j < soalPake){
            clear();
            int indeks;
            printf("══════════════════════════════════════════════════════\n");
            printf("Soal %d :\n", j+1);
            
            do
            {
                acakulang:
                indeks = rand() % jumlahSoal;
                if(sulittidak[indeks]==1 && sulit==maxSulit) 
                    goto acakulang;
                if(sulittidak[indeks]==0 && biasa==maxBiasa)
                    goto acakulang;
                
            } while (soalTampil[indeks] == 1);

            soalTampil[indeks] = 1;
            (sulittidak[indeks]==1) ? sulit++ : biasa++;

            int pilihanx=0;
            printf("%s\n", soal[indeks]);
            char pilih;

            for (int i = 0; i < 4; i++) {
                printf("%c. %s\n\033[0m", i+97, pilihan[indeks][i]);
            }
            printf("══════════════════════════════════════════════════════");
            printf("\nMasukkan a-b: ");
            ulang:
            pilih = getch();
            printf("\n");
            switch(pilih) {
                case 'a':
                    pilihanx = 0;
                    break;
                case 'b':
                    pilihanx = 1;
                    break;
                case 'c':
                    pilihanx = 2;
                    break;
                case 'd':
                    pilihanx = 3;
                    break;
                default:
                    printf("'%c' tidak ada dalam pilihan. ", pilih);
                    goto ulang;
            }

            if (pilihanx == jawabanBenar[indeks]) {
                clear();
                printf("\e[33mJawaban Benar!\e[0m\n\n");
                if(j<soalPake-1) {
                    for(int i=3; i>=0; i--) {
                        if(i==0)
                            break;
                        printf("\e[FSoal selanjutnya akan dimulai dalam %ds\n", i);
                        #ifdef _WIN32
                            Sleep(1000);
                        #else
                            sleep(1);
                        #endif
                    } 
                } else {
                        printf("Selamat! Anda berhasil menjawab semua soal dengan benar");
                }
                printf("\n");
                *skor += (sulittidak[indeks]==1) ? 20.00 : 10.00;
                j++;
                
            }
            else {
                    clear();
                    printf("\033[31mJawaban Salah!\nANDA TERELIMINASI!!\n\033[0m\nJawaban yang benar adalah \033[32m%s\033[0m\n", pilihan[indeks][jawabanBenar[indeks]]);
                    return;
            }
        }    
    }
    short int batas;
    void endingrahasia(){
        char keinginan[30];
        char jalur[50];
        
        
    #ifdef _WIN32
        system("cls");  
    #else
        system("clear");  
    #endif
        printf("\033[0;31mSelamat!!! kamu adalah orang yang kami cari!!\033[0m \n");
    #ifdef _WIN32 
        Sleep(3000); 
    #else 
        sleep(3); 
    #endif
        printf("Tampaknya kamu adalah orang yang sangat pintar bahkan melebihi kepintaran Albert Einstein!!\n");
        printf("Sebagai hadiah, silahkan masukkan keinginanmu, nanti akan admin belikan :3 = ");
        fgets(keinginan, sizeof(keinginan), stdin);
        keinginan[strcspn(keinginan, "\n")] = '\0';
    printf("\nAdmin yang ganteng dan cantik serta rajin menabung ini akan kasih kamu \033[1m%s\033[0m :3\nsilahkan tunggu 5 detik...", keinginan);
    #ifdef _WIN32 
        Sleep(5000); 
        system("start https://www.youtube.com/watch?v=uHgt8giw1LY");
    #else 
        sleep(5); 
        system("xdg-open https://www.youtube.com/watch?v=uHgt8giw1LY");
    #endif

    #ifdef _WIN32
        system("cls");  
    #else
        system("clear");  
    #endif
    printf("Sike!!!! YOU JUST GOT RICKROLLED\n");
    printf("Belajar lagi dek! Jangan satu soalpun gak bisa kau jawab\n");
    batas++;
    }



    int main(int argc, char *argv[]){
        if(argc < 2){
            clear();
            printf("╔════════════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
            printf("║ Selamat datang di game paling gacor, silahkan ikuti petunjuk command line di bawah untuk lanjut :3, coba:  ║\n║ -> ./main register                                                                                         ║\n║ -> ./main login (username) (password)                                                                      ║\n");
            printf("╚════════════════════════════════════════════════════════════════════════════════════════════════════════════╝\n");
        }
        else if(strcmp(argv[1], "register")==0 && argc == 2) {
            buatfolder(folder_name);
            sistemregistrasi();
            
        } else if(strcmp(argv[1], "login")==0 && argc==4) {

            struct pengguna user[14];
            char binfile[100];
            FILE *file = fopen("database/login.bin", "rb");
            if (file == NULL) {
                perror("Error ges");
                exit(1);
            }
            int i=0;
            while(fgets(binfile, sizeof(binfile), file) && i < 14){
                sscanf(binfile, "%[^#]#%[^=]=%lf\n", user[i].username, user[i].pass, &user[i].score);
                i++;
            }
            fclose(file);

            int isCorrect=0;
            int indexPengguna;
            
            for(i=0; i<14; i++) {
                if(strcmp(argv[2], user[i].username)==0) {
                    isCorrect++;
                    if(strcmp(argv[3], user[i].pass)==0) { 
                        isCorrect++;
                        indexPengguna = i;
                        break;
                    } else {
                        printf("Password anda salah\n");
                        break;
                    }
                }
            }
            int pilihan;
            if(isCorrect==2) {
                srand(time(NULL));
                menu:
                clear();
                printf("╔═════════════════════════════════╗\n");
                printf("    \e[1m۞ Selamat datang %s ۞     \n\e[0m╠═════════════════════════════════╣\n      Score saat ini: %.2lf\n╚═════════════════════════════════╝\n", user[indexPengguna].username, user[indexPengguna].score);
                
                char pilih;
                int pilihan;
                int pilihmode;
                char *menu[4] = {"MULAI\033[0m", "TENTANG\033[0m", "EXIT\033[0m", "LEADERBOARD\033[0m"};
                pilihan = 0;
                reset:
                while(1) {
                    printf("\n");
                    for(int i=0; i<4; i++) {
                        if(i == pilihan)
                            printf("\033[33m\e[1m");
                        printf("%s\n", menu[i]);
                    }
                    pilih:
                    pilih = getch();
                    if(pilih=='A' || pilih=='w') {
                        if(pilihan!=0) 
                            pilihan--;
                    } else if(pilih=='B' || pilih=='s') {
                        if(pilihan!=3) 
                            pilihan++;
                    } else if(pilih==' ' || pilih == '\n') {
                            switch(pilihan) {
                                case 0:
                                user[indexPengguna].score = 0.00;
                                char *mode[3] = {"Easy", "Normal", "Hard"};
                                int indexMode=0;
                                char pilihMode;
                                clear();
                                printf("\e[1mPilih Mode\n\e[0m\n");
                                while(1) {
                                    
                                    for(int i=0; i<3; i++) {
                                        if (indexMode==i)
                                            printf("\033[33m\e[1m");
                                        printf("%s\033[0m\n", mode[i]);
                                    }
                                    pilihmode:
                                    pilihMode = getch();
                                    if((pilihMode=='A') || pilihMode=='w') {
                                        if(indexMode!=0)
                                            indexMode--;
                                    } else if((pilihMode=='B') || pilihMode=='s') {
                                        if(indexMode!=2)
                                            indexMode++;
                                    } else if(pilihMode=='\n' || pilihMode==' ') {
                                        soalQuiz(&user[indexPengguna].score, indexMode);
                                        break;
                                    } else if(pilihMode==127 || pilih == '\b') {
                                        goto menu;
                                        
                                    } else {
                                        goto pilihmode;
                                    }
                                    printf("\e[F\e[F\e[F");
                                }

                                lanjut:
                                printf("Skor akhir anda : %.2lf\n", user[indexPengguna].score);

                                if (user[indexPengguna].score <= 100 && user[indexPengguna].score >= 80)
                                    printf("Kelaz king!\n\nTerimakasih telah bermain!\n");
                                else if (user[indexPengguna].score <= 79 && user[indexPengguna].score >= 60)
                                    printf("Okela.\n\nTerimakasih telah bermain!\n");
                                else if (user[indexPengguna].score <= 59 && user[indexPengguna].score >= 40)
                                    printf("Belajar lagi dek.\n\nMohon dicoba lagi nanti!\n");
                                else if (user[indexPengguna].score <= 39 && user[indexPengguna].score > 0)
                                    printf("Bodo kali la!\n\nTidur aja sana!\n");
                                else if (user[indexPengguna].score <= 0)
                                    if(batas == 0)
                                     endingrahasia();
                                    else 
                                     printf("Tolong jangan sama sekali ga bisa dijawab :( \n");
                                FILE *updateFile = fopen("database/login.bin", "rb+");
                                if (updateFile == NULL) {
                                    perror("Error ges");
                                    exit(1);
                                }

                                char baris[50];
                                int k = 0;

                                while (fgets(baris, sizeof(baris), updateFile))
                                {
                                    if(k == indexPengguna) {
                                        fseek(updateFile, -strlen(baris), SEEK_CUR);
                                        fprintf(updateFile, "%s#%s=%.2lf\n", user[k].username, user[k].pass, user[indexPengguna].score);
                                        break;
                                    }
                                    k++;
                                }
                                fclose(updateFile);
                                printf("Tekan BACKSPACE untuk kembali");
                                while(1) {
                                    pilih = getch();
                                    if(pilih==127 || pilih == '\b')
                                    goto menu;
                                }
                                goto menu;

                                case 1:
                                clear();
                                printf("\nTWK (Tes Wawasan Kematian) merupakan sebuah project yang dibangun oleh 5 mahasiswa informatika dalam rangka penilaian UAS, TWK merupakan sebuah game yang dimainkan perorangan dengan cara register, and play,setiap score yang didapatkan oleh player akan disimpan lalu dapat ditampilkan, dengan bantuan dan arahan dari bang ganang dan kak tasya Alhamdulillah TWK Berjalan dengan baik.\n\n");
                                printf("Tekan BACKSPACE untuk kembali");
                                while(1) {
                                    pilih = getch();
                                    if(pilih==127 || pilih=='\b')
                                        goto menu;
                                }

                                case 2:
                                batas = 0;
                                exit(1);

                                case 3:
                                clear();
                                printf("\n\e[1mLEADERBOARD\n\e[0m\nNAMA\t\t\tSCORE\n\n");
                                int indexRank[14] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
                                for (int i = 1; i < 14; i++) {
                                    int key = indexRank[i];
                                    int j = i - 1;
                                    while (j >= 0 && user[indexRank[j]].score < user[key].score) {
                                        indexRank[j + 1] = indexRank[j];
                                        j = j - 1;
                                    }
                                    indexRank[j + 1] = key;
                                }
                                for (i = 0; i < 10; i++) {
                                    if (user[indexRank[i]].score > 1.00) {
                                        if (indexPengguna == indexRank[i]) {
                                            printf("\033[33m");
                                        }
                                        printf("%d. %s\t\t%.2lf\n", i + 1, user[indexRank[i]].username, user[indexRank[i]].score);
                                        printf("\033[0m");
                                    } else {
                                        break;
                                    }
                                }
                                printf("\nTekan BACKSPACE untuk kembali");
                                while(1) {
                                    pilih = getch();
                                    if(pilih==127 || pilih == '\b')
                                        goto menu;
                                }
                            }
                            break;
                    } else  
                        goto pilih;
                    printf("\033[F\033[F\033[F\033[F\033[F");
                    

                    
                }
            } else if (isCorrect == 0) {
                printf("username tidak ditemukan\n");
                exit(1);
            }
        }
        else {
            printf("╔══════════════════════════════════════════════════════╗\n");
            printf("║ Format CLA tidak sesuai, coba:                       ║\n║ -> ./main register                                   ║\n║ -> ./main login (username) (password)                ║\n");
            printf("╚══════════════════════════════════════════════════════╝\n");
        }
    return 0;
    }
