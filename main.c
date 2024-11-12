#include<stdio.h>
#include<stdlib.h>
#include<string.h>

    struct pengguna{
        char username[10];
        char pass[10];
    };

    void IniUntukBuatFileBinYagesya(const char *namafile, struct pengguna user){
        FILE *file = fopen(namafile, "ab");
        if(file == NULL){
            perror("Error pulak bah");
            exit(1);
        }
        fwrite(&user, sizeof(struct pengguna), 1, file);

        fclose(file);
        printf("sername sudah disimpan, have fun!\nKetik dengan format\n-> ./main (username) (password)\n");
    }

    int main(int argc, char *argv[]){
        if(strcmp(argv[1], "register")==0 && argc == 2) {
            struct pengguna penggunabaru;
            printf("Selamat datang di game paling gacor maxwinn777\n");
            printf("Silahkan buat akun dulu\n");
        
            printf("Masukkan username : ");
            fgets(penggunabaru.username, sizeof(penggunabaru.username), stdin);
            penggunabaru.username[strcspn(penggunabaru.username, "\n")] = '#';

            printf("Masukkan password : ");
            fgets(penggunabaru.pass, sizeof(penggunabaru.pass), stdin);
            penggunabaru.pass[strcspn(penggunabaru.pass, "\n")] = '@';

            IniUntukBuatFileBinYagesya("database/login.bin", penggunabaru);
        } else if(strcmp(argv[1], "login")==0 && argc==4) {
            FILE *file = fopen("database/login.bin", "rb");
        }
        else {
            printf("Format CLA tidak sesuai, coba:\n-> ./main register\n-> ./main login (username) (password)\n");
        }
    return 0;
}
