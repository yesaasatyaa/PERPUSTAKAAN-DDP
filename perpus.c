#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <conio.h>

struct Buku {
    int id;               
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

int cariIndexByJudul(char judul[]){
    for(int i = 0; i < jumlahBuku; i++){
        if(strcmp(daftarBuku[i].judul, judul) == 0){
            return i;
        }
    }
    return -1;
}

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

    b.id = jumlahBuku + 1;  

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
    printf("\n=== DAFTAR BUKU ===\n");

    if (jumlahBuku == 0) {
        printf("Belum ada buku.\n");
        return;
    }

    printf("+----+------------------------------+-------------------------+-------+-------------+\n");
    printf("| ID | Judul                        | Penulis                 | Tahun | Status      |\n");
    printf("+----+------------------------------+-------------------------+-------+-------------+\n");

    for (int i = 0; i < jumlahBuku; i++) {
        printf("| %-2d | %-28s | %-23s | %-5d | %-11s |\n",
            daftarBuku[i].id,
            daftarBuku[i].judul,
            daftarBuku[i].penulis,
            daftarBuku[i].tahun,
            daftarBuku[i].dipinjam ? "Dipinjam" : "Tersedia"
        );
    }

    printf("+----+------------------------------+-------------------------+-------+-------------+\n");
}


void editBuku(){
    char judulCari[100];
    char tmp[100];

    fflush(stdin);
    printf("\nMasukkan judul buku yang akan diedit : ");
    fgets(judulCari, sizeof(judulCari), stdin);
    judulCari[strcspn(judulCari, "\n")] = '\0';

    int idx = cariIndexByJudul(judulCari);

    if(idx == -1){
        printf("\nBuku tidak ditemukan!\n");
        return;
    }

    printf("\n=== Data Buku Saat Ini ===\n");
    printf("Judul     : %s\n", daftarBuku[idx].judul);
    printf("Penulis   : %s\n", daftarBuku[idx].penulis);
    printf("Tahun     : %s\n", daftarBuku[idx].tahun);
    printf("Status    : %s\n", daftarBuku[idx].dipinjam ? "Dipinjam" : "Tersedia");

    printf("\n=== Edit Buku (Kosongkan untuk tidak mengubah) ===\n");

    printf("Judul baru : ");
    fgets(tmp, sizeof(tmp), stdin);
    tmp[strcspn(tmp, "\n")] = '\0';
    if(strlen(tmp) > 0)
    strcpy(daftarBuku[idx].judul, tmp);

    printf("Penulis baru : ");
    fgets(tmp, sizeof(tmp), stdin);
    tmp[strcspn(tmp, "\n")] = '\0';
    if(strlen(tmp) > 0)
    strcpy(daftarBuku[idx].penulis, tmp);

    printf("Tahun baru : ");
    fgets(tmp, sizeof(tmp), stdin);
    tmp[strcspn(tmp, "\n")] = '\0';
    if(strlen(tmp) > 0){
    int tahunBaru = atoi(tmp);
    if(tahunBaru > 0)
        daftarBuku[idx].tahun = tahunBaru;
}

    printf("\nBuku berhasil diperbarui!\n");
}

void hapusBuku(){
    char judulCari[100];

    fflush(stdin);
    printf("\nMasukkan judul buku yang akan dihapus : ");
    fgets(judulCari, sizeof(judulCari), stdin);
    judulCari[strcspn(judulCari, "\n")] = '\0';

    int idx = cariIndexByJudul(judulCari);

    if(idx == 1){
        printf("\nBuku tidak ditemukan!\n");
        return;
    }

    for(int i = idx; i < jumlahBuku - 1; i++){
        daftarBuku[i] = daftarBuku[i+1];
    }

    jumlahBuku--;

    printf("\nBuku berhasil dihapus!\n");
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

void benderaNegara(){
    system ("cls");

    int flagWidth = 30;
    int flagHeight = 10;
    int poleExtra = 6;
    int groundWidth = 5;

    printf("\n=== BENDERA INDONESIA ===\n\n");

    for(int i = 0; i < flagHeight / 2; i++) {
        printf("| ");
        for(int j = 0; j < flagWidth; j++) printf("#");
        printf("\n");
    } 

    for(int i = 0; i < flagHeight / 2; i++) {
        printf("| ");
        for(int j = 0; j < flagWidth; j++) printf(".");
        printf("\n");
    }

    for(int i = 0; i < poleExtra; i++)
        printf("| \n");

    for(int i = 0; i < groundWidth; i++)
        printf("=");

     printf("\n\nTekan enter untuk kembali...");
    getch();
}

}

void pinjamBuku() {
    printf("\n=== DAFTAR BUKU ===\n");
    lihatBuku();

    if (jumlahBuku == 0) {
        printf("\nTekan enter untuk kembali ke menu...");
        getch();
        return;
    }

    int id;
    printf("\nMasukkan ID buku yang ingin dipinjam: ");
    scanf("%d", &id);

    int idx = id - 1;

    if (idx < 0 || idx >= jumlahBuku) {
        printf("ID tidak valid!\n");

        printf("\nTekan enter untuk kembali ke menu...");
        getch();
        return;
    }

    if (daftarBuku[idx].dipinjam) {
        printf("Buku sedang dipinjam oleh %s\n", daftarBuku[idx].peminjam);

        printf("\nTekan enter untuk kembali ke menu...");
        getch();
        return;
    }

    fflush(stdin);
    char nama[50];
    printf("Masukkan nama peminjam : ");
    fgets(nama, sizeof(nama), stdin);
    nama[strcspn(nama, "\n")] = '\0';

    daftarBuku[idx].dipinjam = 1;
    strcpy(daftarBuku[idx].peminjam, nama);

    printf("\nBuku berhasil dipinjam!\n");

    printf("\nTekan enter untuk kembali ke menu...");
    getch();
}



void pengembalianBuku() {

    printf("\n=== DAFTAR BUKU ===\n");
    lihatBuku(); 

    if (jumlahBuku == 0) {
        printf("\nTidak ada buku.\n");
        return;
    }

    int id;
    printf("\nMasukkan ID buku yang ingin dikembalikan : ");
    scanf("%d", &id);

    int idx = id - 1;

    if (idx < 0 || idx >= jumlahBuku) {
        printf("ID tidak valid!\n");
        return;
    }

    if (!daftarBuku[idx].dipinjam) {
        printf("Buku ini tidak sedang dipinjam.\n");
        return;
    }

    printf("Buku dipinjam oleh : %s\n", daftarBuku[idx].peminjam);

    int telat;
    printf("Masukkan jumlah hari keterlambatan (0 jika tidak telat): ");
    scanf("%d", &telat);

    int denda = telat * 1000;
    printf("Total denda : Rp %d\n", denda);

    printf("\n=== Metode Pembayaran ===\n");
    printf("1. Cash\n");
    printf("2. QRIS (harus pas, tidak ada kembalian)\n");
    printf("Pilih metode : ");

    int metode;
    scanf("%d", &metode);

    int bayar;

    if (metode == 1) {  
        printf("Masukkan jumlah uang cash : ");
        scanf("%d", &bayar);

        if (bayar < denda) {
            printf("Uang tidak cukup! Transaksi dibatalkan.\n");
            return;
        }

        int kembalian = bayar - denda;

        printf("\n=== STRUK PEMBAYARAN CASH ===\n");
        printf("Metode     : Cash\n");
        printf("Uang Bayar : Rp %d\n", bayar);
        printf("Denda      : Rp %d\n", denda);
        printf("Kembalian  : Rp %d\n", kembalian);
        printf("===============================\n");

    } else if (metode == 2) {  
        printf("Masukkan nominal QRIS : ");
        scanf("%d", &bayar);

        if (bayar != denda) {
            printf("QRIS harus pas! Transaksi dibatalkan.\n");
            return;
        }

        printf("\n=== STRUK PEMBAYARAN QRIS ===\n");
        printf("Metode : QRIS\n");
        printf("Bayar  : Rp %d\n", bayar);
        printf("Denda  : Rp %d\n", denda);
        printf("Status : BERHASIL\n");
        printf("==============================\n");

    } else {
        printf("Metode tidak valid!\n");
        return;
    }

    daftarBuku[idx].dipinjam = 0;
    strcpy(daftarBuku[idx].peminjam, "-");
    daftarBuku[idx].telat = telat;

    printf("\nBuku berhasil dikembalikan!\n");
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
    } while(pilihan != 9);
}

int main(){
    login();
    menuUtama();
    return 0;
}