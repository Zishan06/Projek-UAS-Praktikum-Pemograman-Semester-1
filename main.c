#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<time.h>
#ifdef _WIN32
    #include<Windows.h>
    #include <io.h>
    #include<direct.h>
#else
    #include <unistd.h>
    #include <sys/stat.h>
#endif

    struct pengguna{
        char username[14];
        char pass[14];
        double score;
    };
    const char *folder_name = "database";

    void sistemregistrasi(){
        struct pengguna penggunabaru;
        char konfirpassword[14];
    
        printf("===============================================================\n");
        printf("|| Selamat datang di game TWK (Tes Wawasan Kematian)!            ||\n|| Ketik Username dan password untuk mendaftar.               ||\n");
        printf("===============================================================\n\n");
        
        printf("-> Masukkan username     : ");
        fgets(penggunabaru.username, sizeof(penggunabaru.username), stdin);
        penggunabaru.username[strcspn(penggunabaru.username, "\n")] = '\0';

        if(strlen(penggunabaru.username) < 8 || strlen(penggunabaru.username) > 12){
            printf("Username harus minimal 8 karakter dan maksimal 12 karakter.\n");
            return;
        }

        FILE *checkfile = fopen("database/login.bin", "rb");
        if (checkfile != NULL)
        {
            char baris[50];
            while (fgets(baris, sizeof(baris), checkfile))
            {
                char *fileUsername = strtok(baris, "#");
                if (strcmp(fileUsername, penggunabaru.username) == 0)
                {
                printf("Username sudah digunakan. Silakan pilih username lain.\n");
                fclose(checkfile);
                return;
                }
            }
            fclose(checkfile);
        }
            
        printf("->Masukkan password     : ");
        fgets(penggunabaru.pass, sizeof(penggunabaru.pass), stdin);
        penggunabaru.pass[strcspn(penggunabaru.pass, "\n")] = '\0';

        if(strlen(penggunabaru.pass) < 8 || strlen(penggunabaru.pass) > 12){
            printf("Password harus minimal 8 karakter dan maksimal 12 karakter.\n");
            return;
        }

        for (int i = 0; penggunabaru.pass[i] != '\0'; i++)
        {
            if (!isalnum(penggunabaru.pass[i]))
            {
            printf("Password tidak boleh mengandung karakter special.\n");
            return;
            }
        }

        printf("-> konfirmasi password  : ");
        fgets(konfirpassword, sizeof(konfirpassword), stdin);
        konfirpassword[strcspn(konfirpassword, "\n")] = '\0';

        if (strcmp(konfirpassword, penggunabaru.pass) != 0)
        {
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
        printf("\n=================================================================\n");
        printf("|| ----------------------------Halo!-------------------------- ||\n");
        printf("=================================================================\n");
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
            "apabila nun mati atau tanwin bertemu dengan huruf fa maka hukumnya?",
            "di bawah ini yang termasuk sifat mustahil nabi adalah?",
            "ada berapa sifat wajib Allah?",
            "siapa nama dosen kece kelas b?",
            "syifa ngecrushin doi selama 2 tahun, ternyata doi udah punya pacar, tapi ga dipost aja. tebak berapa hts syifa sekarang?",
            "7 ekor buaya dikali 3, berapa total buaya sekarang?",
            "5 x 4 + 3 : 100 + kamu sama yang lain = ?",
            "berapa banyak rukun shalat?",
            "di tahan sakit, di keluarin malu, apakah gerangan?",
            "berapa banyak rukun islam?"};

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
            {"ikhfa", "iqlab", "mad asli", "saktah"},
            {"sidik", "amanah", "kadzib", "tablig"},
            {"15", "20", "1", "10"},
            {"pak mahyus", "pak taufiq", "s14p4 y4ch?", "pak alim<3"},
            {"0 lah bjir stay halal!!", "keknya si 4 yah", "1 fakultas sie", "otw cari tuh"},
            {"21", "4", "10", "15"},
            {"aku yo ngoding lah ;p", "10+ hts", "23", "aku ma siapa? </3 :("},
            {"10", "11", "9", "13" },
            {"kentut anjay", "rasa cintaku padanya", "jawab nomor 2", "kentut tapi ga bunyi"},
            {"6", "5","2", "3"}};

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
            case 1:
                maxSulit = 0;
                maxBiasa = 10;
                break;
            case 2:
                maxSulit = 3;
                maxBiasa = 4;
                break;
            case 3:
                maxSulit = 7;
                maxBiasa = 0;
                break;
        }
        soalPake = maxBiasa + maxSulit;

        for(int j = 0; j < soalPake; j++){
            int indeks;
            printf("\nSoal %d :\n", j+1);
            
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

            printf("%s\n", soal[indeks]);
            for (int i = 0; i < 4; i++)
            {
                printf("%d. %s\n", i + 1, pilihan[indeks][i]);
        
            }

            int jawabanPengguna;
            printf("Pilihlah jawaban dari (1 - 4) : ");
            scanf("%d", &jawabanPengguna);

            if (jawabanPengguna - 1 == jawabanBenar[indeks])
            {
                printf("\033[33mJawaban Benar!\033[0m");
                *skor += (sulittidak[indeks]==1) ? 20.00 : 10.00;
            }
            else
            {
                printf("\033[31mJawaban Salah!\nANDA TERELIMINASI!!\n\033[0m\nJawaban yang benar adalah \033[32m%s\n\033[0m", pilihan[indeks][jawabanBenar[indeks]]);
                break;
            }
            printf("\n");
        }    
    }


    int main(int argc, char *argv[]){
        if(argc < 2){
            printf("===============================================================================================================\n");
            printf("|| Selamat datang di game paling gacor, silahkan ikuti petunjuk command line di bawah untuk lanjut :3, coba: ||\n\n|| -> ./main register                                                                                        ||\n|| -> ./main login (username) (password)                                                                     ||\n");
            printf("===============================================================================================================\n");
        }
        else if(strcmp(argv[1], "register")==0 && argc == 2) {
            buatfolder(folder_name);
            sistemregistrasi();
            
        } else if(strcmp(argv[1], "login")==0 && argc==4) {

            struct pengguna user[14];
            char binfile[100];
            FILE *file = fopen("database/login.bin", "rb");
            if (file == NULL)
            {
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
                printf("\nSelamat datang %s\nScore saat ini: %.2lf\n\n", user[indexPengguna].username, user[indexPengguna].score);
                reset:
                while(1){
                    printf("1. Mulai\n2. Credit\n3. Exit\n4. Daftar Score\n\nPilih (1 - 4) : ");
                    if(scanf("%d", &pilihan) != 1){
                        while(getchar() != '\n');
                        printf("\nInput tidak valid. Pilih (1 - 4) :\n ");
                        goto reset;
                    }
                    if(pilihan < 1 || pilihan > 4){
                        printf("\nPilihan tidak valid. Pilih (1 - 4) :\n ");
                        goto reset;
                    }
                    break;
                }
                int pilihmode;         
                switch(pilihan) {
                    case 1:
                   user[indexPengguna].score = 0.00;
                    printf("1.easy \n2.normal \n3.hard\n");
                    printf("pilih mode : ");
                    scanf("%d", &pilihmode);
                    soalQuiz(&user[indexPengguna].score, pilihmode);
    
                    printf("\nSkor akhir anda : %.2lf\n", user[indexPengguna].score);

                    if (user[indexPengguna].score <= 100 && user[indexPengguna].score >= 80)
                    {
                        printf("Kelaz king!\n\nTerimakasih telah bermain!\n");
                    }
                    else if (user[indexPengguna].score <= 79 && user[indexPengguna].score >= 60)
                    {
                        printf("Okela.\n\nTerimakasih telah bermain!\n");
                    }
                    else if (user[indexPengguna].score <= 59 && user[indexPengguna].score >= 40)
                    {
                        printf("Belajar lagi dek.\n\nMohon dicoba lagi nanti!\n");
                    }
                    else if (user[indexPengguna].score <= 39 && user[indexPengguna].score >= 0)
                    {
                        printf("Bodo kali la!\n\nTidur aja sana!\n");
                    }

                    FILE *updateFile = fopen("database/login.bin", "rb+");
                    if (updateFile == NULL)
                    {
                        perror("Error ges");
                        exit(1);
                    }

                    char baris[50];
                    int k = 0;

                    while (fgets(baris, sizeof(baris), updateFile))
                    {
                        if(k == indexPengguna)
                        {
                            fseek(updateFile, -strlen(baris), SEEK_CUR);
                            fprintf(updateFile, "%s#%s=%.2lf\n", user[k].username, user[k].pass, user[indexPengguna].score);
                            break;
                        }
                        k++;
                    }
                    fclose(updateFile);
                    break;

                    case 2:
                    printf("\nGame ini adalah projek dari bang Ganang SETYO HADI APALAH NYUSAHIN ORANG AJAHHHH:(\n");
                    #ifdef _WIN32 
                        Sleep(5); 
                    #else 
                        usleep(5000000); 
                    #endif
                    goto menu;

                    case 3:
                    exit(1);

                    case 4:
                    printf("\nLEADERBOARD\nNAMA\t\t\tSCORE\n\n");
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
                    for(i=0; i<10; i++) {
            
                        if(strlen(user[indexRank[i]].username) <= 0) 
                            break;
                        for(i = 0; i < 10; i++){
                            if (strlen(user[indexRank[i]].username) >= 8){
                                if(indexPengguna==indexRank[i]) {
                                    printf("\033[33m");
                                }
                                printf("%d. %s\t\t%.2lf\n", i+1, user[indexRank[i]].username, user[indexRank[i]].score);
                                printf("\033[0m");
                            }
                        }
                    }
                    #ifdef _WIN32 
                    Sleep(3); 
                    #else 
                    sleep(3); 
                    #endif
                    goto menu;

                }
            
            } else if (isCorrect == 0) {
                printf("username tidak ditemukan\n");
                exit(1);
            }
        }
        else {
            printf("=========================================================\n");
            printf("|| Format CLA tidak sesuai, coba:                      ||\n\n|| -> ./main register                                  ||\n|| -> ./main login (username) (password)               ||\n");
            printf("=========================================================");
        }
    return 0;
    } 
    
