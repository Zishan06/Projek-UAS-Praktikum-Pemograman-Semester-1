#include<stdio.h>
#include<stdlib.h>
#include<string.h>

    struct pengguna{
        char username[10];
        char pass[10];
        int score;
    };

    void registrationSystem(){
        struct pengguna penggunabaru;
        char confirmPassword[10];
    
        printf("Selamat datang di game paling gacor maxwinn777\nKetik Username dan password untuk mendaftar\n");
        
        printf("Masukkan username : ");
        fgets(penggunabaru.username, sizeof(penggunabaru.username), stdin);
        penggunabaru.username[strcspn(penggunabaru.username, "\n")] = '\0';
            
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

    int main(int argc, char *argv[]){
        if(argc < 2){
            printf(" Format CLA tidak sesuai, coba:\n-> ./main register\n-> ./main login (username) (password)\n");
        }
        else if(strcmp(argv[1], "register")==0 && argc == 2) {
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
