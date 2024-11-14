#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<io.h>

    struct pengguna{
        char username[10];
        char pass[10];
        int score;
    };
    const char *folder_name = "database";

    void sistemregistrasi(){
        struct pengguna penggunabaru;
        char konfirpassword[10];
    
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

        printf("konfirmasi password : ");
        fgets(konfirpassword, sizeof(konfirpassword), stdin);
        konfirpassword[strcspn(konfirpassword, "\n")] = '0';

        if (strcmp(konfirpassword, penggunabaru.pass) == 0)
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
    if ( _access(folder_name, 0) == 0) 
     printf("Folder %s sudah ada. Ga perlu buat lagi.\n", folder_name);
    else 
    if (_mkdir(folder_name) == 0) 
     printf("Folder '%s' berhasil dibuat.\n", folder_name);
    else 
     perror("Error ges");
    }


    int main(int argc, char *argv[]){
        if(argc < 2){
            printf("Selamat datang di game paling gacor, silahkan ikuti petunjuk command line di bawah untuk lanjut :3, coba:\n-> ./main register\n-> ./main login (username) (password)\n");
        }
        else if(strcmp(argv[1], "register")==0 && argc == 2) {
            buatfolder(folder_name);
            sistemregistrasi();
            
        } else if(strcmp(argv[1], "login")==0 && argc==4) {

            struct pengguna user[10];
            char binfile[100];
            FILE *file = fopen("database/login.bin", "rb");
            int i=0;
            while(fgets(binfile, sizeof(binfile), file) && i < 10){
                sscanf(binfile, "%[^#]#%[^=]=%d\n", user[i].username, user[i].pass, &user[i].score);
                i++;
            }
            fclose(file);

            int isCorrect=0;
            struct pengguna player;
            for(i=0; i<10; i++) {
                if(strcmp(argv[2], user[i].username)==0) {
                    isCorrect++;
                    if(strcmp(argv[3], user[i].pass)==0) { 
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
            if(isCorrect==1) {
                printf("selamat datang %s\nScore saat ini: %d\n", player.username, player.score);
            } else {
                printf("username tidak ditemukan\n");
                exit(1);
            }
            printf("SOAL PERTAMA");
        }
        else {
            printf(" Format CLA tidak sesuai, coba:\n-> ./main register\n-> ./main login (username) (password)\n");
        }
    return 0;
}
