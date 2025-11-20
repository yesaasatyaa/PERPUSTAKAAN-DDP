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

void tambahBuku() {
    struct Buku b;

    printf("\n=== Tambah Buku ===\n");
    fflush(stdin); 
    printf("Judul Buku : ");
    fgets(b.judul, sizeof(b.judul), stdin);
    b.judul[strcspn(b.judul, "\n")] = '\0'; 

    printf("Penulis Buku : ");
    fgets(b.penulis, sizeof(b.penulis), stdin);
    b.penulis[strcspn(b.penulis, "\n")] = '\0';

    printf("Tahun Terbit : ");
    scanf("%d", &b.tahun);

    b.dipinjam = 0; 
    strcpy(b.peminjam, "-");
    b.telat = 0;
    strcpy(b.alasan, "-");

    daftarBuku[jumlahBuku++] = b;

    printf("\nBuku berhasil ditambahkan!\n");
}

void lihatBuku() {
    printf("\n=== List Buku ===\n");
    if(jumlahBuku == 0){
        printf("Belum ada buku yang terdaftar.\n");
        return;
    }

    for(int i = 0; i < jumlahBuku; i++){
        printf("\nBuku ke-%d\n", i+1);
        printf("Judul     : %s\n", daftarBuku[i].judul);
        printf("Penulis   : %s\n", daftarBuku[i].penulis);
        printf("Tahun     : %d\n", daftarBuku[i].tahun);
        printf("Status    : %s\n", daftarBuku[i].dipinjam ? "Dipinjam" : "Tersedia");
        if(daftarBuku[i].dipinjam){
            printf("Peminjam  : %s\n", daftarBuku[i].peminjam);
            printf("Telat     : %d hari\n", daftarBuku[i].telat);
            printf("Alasan    : %s\n", daftarBuku[i].alasan);
        }
    }
}

void rumahPola(){
    system("cls");

    int tinggiAtap = 4;
    int lebar = 11;

    for(int i = 0; i < tinggiAtap; i++) {
        for (int s = 0; s < tinggiAtap - i; s++) {
            putchar(' ');
        }

        putchar('/');

        for (int t = 0; t < i *2; t++) {
             if (i == tinggiAtap -1)
                putchar('_'); 
             else
             putchar(' ');
        }   
    
        putchar('\\');
        putchar('\n');
    }

    for (int i = 0; i <3; i++) {
        putchar(' ');
        putchar(' ');
        putchar(' ');
        putchar(' ');
        putchar('|');

        if(i == 1)
            printf("  []  ");
        else
            printf("      ");


        putchar('|');
        putchar('\n');
    }  
    
    for (int i = 0; i < 4; i++) {
        printf("   |");

        if (i == 0)
            printf("  __  ");
        else if (i == 1 || i == 2)
            printf(" |  | ");
        else
            printf(" |__| ");

        printf("|\n");
    }
    
    for (int i = 0; i < 4; i++) {
        printf("   |");

        if (i == 0)
            printf("  __  ");
        else if (i == 1 || i == 2)
            printf(" |  | ");
        else
            printf(" |__| ");

        printf("|\n");
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