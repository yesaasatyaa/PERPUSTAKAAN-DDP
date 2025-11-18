#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <conio.h>

struct Buku {
    char judul[100];
    char penulis[100];
    int tahun;

    int dipinjam;
    char peminjam[50];
    int telat;
    char alasan[100];
};

struct User{
    char username[30];
    char password[30];
};

struct Buku daftarBuku[100];
int jumlahBuku = 0;

struct User admin = {"admin", "admin123"};

void inputPassword(char *pass){
    char ch;
    int i = 0;

    while(1){
        ch = getch();

        if(ch == 13){
            pass[i] = '\0';
            printf("\n");
            break;
        }else if(ch == 8 && i > 0){
            i--;
            printf("\b \b");
        }else{
            pass[i++] = ch;
            printf("*");
        }
    }
}

void login(){
    char user[20], pass[20];

    while(1){
        printf("\n====== LOGIN PERPUSTAKAAN ======\n");
        printf("Username : ");
        scanf("%s", user);
        printf("Password : ");
        scanf("%s", pass);

        if(strcmp(user, "admin") == 0 && strcmp(pass, "admin123") == 0){
            printf("\nLogin Berhasil!\n");
            break;
        } else {
            printf("\nLogin gagal! Coba lagi.\n");
        }
    }
}

void menuUtama(){
    int pilihan;

    do{
        printf("\n===== SELAMAT DATANG DI MENU UTAMA PERPUSTAKAAN ======\n");
        printf("1. Tambah buku\n");
        printf("2. Lihat list buku\n");
        printf("3. Edit buku\n");
        printf("4. Hapus buku\n");
        printf("5. Rumah pola\n");
        printf("6. Bendera Negara\n");
        printf("7. Pinjam buku\n");
        printf("8. Pengembalian buku + denda\n");
        printf("9. Exit\n");
        printf("Pilih Menu : ");
        scanf("%d", &pilihan);

        switch(pilihan){
            case 1:
                tambahBuku();
                break;
            case 2:
                lihatBuku();
                break;
            case 3:
                editBuku();
                break;
            case 4:
                hapusBuku();
                break;
            case 5:
                rumahPola();
                break;
            case 6:
                benderaNegara();
                break;
            case 7:
                pinjamBuku();
                break;
            case 8:
                pengembalianBuku();
                break;
            case 9:
                printf("\nTerimakasih!.\n");
                break;
            default :
                printf("Pilihan tidak valid!\n");
        }
    } while(pilihan != 7);
}

int main(){
    login();
    menuUtama();
    return 0;
}