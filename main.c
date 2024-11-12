#include<stdio.h>
#include<stdlib.h>
#include<string.h>

    struct pengguna{
        char username[10];
        char pass[10];
    };

    void registrationSystem(){
        struct pengguna penggunabaru;
        FILE *regis = fopen("database/login.bin", "ab");
        char buffer[255];
            
        printf("Selamat datang di game paling gacor maxwinn777\n");
        printf("Silahkan buat akun dulu\n");
        
        printf("Masukkan username : ");
        fgets(penggunabaru.username, sizeof(penggunabaru.username), stdin);
        penggunabaru.username[strcspn(penggunabaru.username, "\n")] = '\0';
            
        printf("Masukkan password : ");
        fgets(penggunabaru.pass, sizeof(penggunabaru.pass), stdin);
        if(regis == NULL){
                perror("Error ges");
                exit(1);
        }
        snprintf(buffer, 255, "%s#%s\n", penggunabaru.username, penggunabaru.pass);
        fwrite(buffer, 1, strlen(buffer), regis);
        fclose(regis);
    }

    int main(int argc, char *argv[]){
        if(strcmp(argv[1], "register")==0 && argc == 2) {
            registrationSystem();
            
        } else if(strcmp(argv[1], "login")==0 && argc==4) {
            FILE *file = fopen("database/login.bin", "rb");
        }
        else {
            printf("Format CLA tidak sesuai, coba:\n-> ./main register\n-> ./main login (username) (password)\n");
        }
    return 0;
}
