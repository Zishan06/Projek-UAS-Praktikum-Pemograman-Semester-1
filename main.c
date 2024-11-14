#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<time.h>
#ifdef _WIN32
    #include <io.h>
    #include<direct.h>
#else
    #include <unistd.h>
    #include <sys/stat.h>
#endif

    struct pengguna{
        char username[14];
        char pass[14];
        int score;
    };
    const char *folder_name = "database";

    void sistemregistrasi(){
        struct pengguna penggunabaru;
        char konfirpassword[14];
    
        printf("Selamat datang di game paling gacor maxwinn777\nKetik Username dan password untuk mendaftar\n");
        
        printf("Masukkan username : ");
        fgets(penggunabaru.username, sizeof(penggunabaru.username), stdin);
        penggunabaru.username[strcspn(penggunabaru.username, "\n")] = '\0';

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
            
        printf("Masukkan password : ");
        fgets(penggunabaru.pass, sizeof(penggunabaru.pass), stdin);
        penggunabaru.pass[strcspn(penggunabaru.pass, "\n")] = '\0';

        if(strlen(penggunabaru.pass) < 8 || strlen(penggunabaru.pass) > 12){
            printf("Password harus minimal 8 dan maksimal 12.\n");
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

        printf("konfirmasi password : ");
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
        fprintf(regis, "%s#%s=0\n", penggunabaru.username, penggunabaru.pass);
        fclose(regis);
        printf("Halo!\n");
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

    void soalQuiz(int *skor){
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
            "Berapa warna yang ada pada bendera italia?"};

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
            {"3", "2", "4", "5"}};

        const int jawabanBenar[] = {2, 1, 0, 2, 3, 1, 2, 1, 0, 0};

        int jumlahSoal = sizeof(soal) / sizeof(soal[0]);
        int soalTampil[jumlahSoal];
        memset(soalTampil, 0, sizeof(soalTampil));

        for(int j = 0; j < 5; j++){
            int indeks;
            printf("Soal %d :\n", j+1);
            do
            {
                indeks = rand() % jumlahSoal;
            } while (soalTampil[indeks] == 1);

            soalTampil[indeks] = 1;

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
                printf("Jawaban Benar!\n");
                *skor = *skor + 20;
            }
            else
            {
                printf("Jawaban Salah!\nJawaban yang benar adalah %s\n", pilihan[indeks][jawabanBenar[indeks]]);
            }
            printf("\n");
        }    
    }


    int main(int argc, char *argv[]){
        if(argc < 2){
            printf("Selamat datang di game paling gacor, silahkan ikuti petunjuk command line di bawah untuk lanjut :3, coba:\n-> ./main register\n-> ./main login (username) (password)\n");
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
                sscanf(binfile, "%[^#]#%[^=]=%d\n", user[i].username, user[i].pass, &user[i].score);
                i++;
            }
            fclose(file);

            int isCorrect=0;
            struct pengguna player;
            for(i=0; i<14; i++) {
                if(strcmp(argv[2], user[i].username)==0) {
                    isCorrect++;
                    if(strcmp(argv[3], user[i].pass)==0) { 
                        isCorrect++;
                        strcpy(player.username, user[i].username);
                        strcpy(player.pass, user[i].pass);
                        player.score = user[i].score;
                        break;
                    } else {
                        printf("Password anda salah\n");
                        break;
                    }
                }
            }
            if(isCorrect==2) {
                srand(time(NULL));
                printf("selamat datang %s\nScore saat ini: %d\n", player.username, player.score);
                player.score = 0;

                soalQuiz(&player.score);

                printf("\nTerimakasih telah bermain!\nSkor akhir anda : %d\n", player.score);

                FILE *updateFile = fopen("database/login.bin", "rb+");
                if (updateFile == NULL)
                {
                    perror("Error ges");
                    exit(1);
                }

                char baris[50];
                int adaOrangnya = 0;
                int k = 0;

                while (fgets(baris, sizeof(baris), updateFile))
                {
                    sscanf(baris, "%[^#]#%[^=]=%d\n", user[k].username, user[k].pass, &user[k].score);

                    if (strcmp(player.username, user[k].username) == 0)
                    {
                        adaOrangnya = 1;
                        user[k].score = player.score;
                        fseek(updateFile, -strlen(baris), SEEK_CUR);
                        fprintf(updateFile, "%s#%s=%d\n", user[k].username, user[k].pass, user[k].score);
                        break;
                    }
                    k++;
                }
                fclose(updateFile);
            } else if (isCorrect == 0) {
                printf("username tidak ditemukan\n");
                exit(1);
            }
        }
        else {
            printf(" Format CLA tidak sesuai, coba:\n-> ./main register\n-> ./main login (username) (password)\n");
        }
    return 0;
}
