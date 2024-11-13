#include<stdio.h>
#include<stdlib.h>
#include<string.h>

    struct pengguna{
        char username[10];
        char pass[10];
        int score;
    };
    const char *folder_name = "database";

    void registrationSystem(){
        struct pengguna penggunabaru;
        char confirmPassword[10];
    
        printf("Selamat datang di game paling gacor maxwinn777\nKetik Username dan password untuk mendaftar\n");
        
        printf("Masukkan username : ");
        fgets(penggunabaru.username, sizeof(penggunabaru.username), stdin);
        penggunabaru.username[strcspn(penggunabaru.username, "\n")] = '\0';

        FILE *checkFile = fopen("database/login.bin", "rb");
        if (checkFile != NULL)
        {
            char line[50];
            while (fgets(line, sizeof(line), checkFile))
            {
                char *fileUsername = strtok(line, "#");
                if (strcmp(fileUsername, penggunabaru.username) == 0)
                {
                printf("Username sudah digunakan. Silakan pilih username lain.\n");
                fclose(checkFile);
                return;
                }
            }
            fclose(checkFile);
        }
            
        printf("Masukkan password : ");
        fgets(penggunabaru.pass, sizeof(penggunabaru.pass), stdin);
        penggunabaru.username[strcspn(penggunabaru.username, "\n")] = '\0';

        FILE *regis = fopen("database/login.bin", "ab"); 
        if(regis == NULL){
                perror("Error ges");
                exit(1);
        }
        fprintf(regis, "%s#%s=0\n", penggunabaru.username, penggunabaru.pass);
        fclose(regis);
    }
   
    void createFolder(const char *folder_name) { 
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
            createFolder(folder_name);
            registrationSystem();
            
        } else if(strcmp(argv[1], "login")==0 && argc==4) {
            struct pengguna users[10];
            char binFile[100];
            FILE *file = fopen("database/login.bin", "rb");
            fgets(binFile, sizeof(binFile), file);
            
        }
        else {
            printf(" Format CLA tidak sesuai, coba:\n-> ./main register\n-> ./main login (username) (password)\n");
        }
    return 0;
}
