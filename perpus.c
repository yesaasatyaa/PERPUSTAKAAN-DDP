#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <conio.h>

//ini ANSI  buat ngatur warna di terminal ya adik adik
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define MAGENTA "\033[35m"
#define BLUE    "\033[34m"
#define YELLOW  "\033[33m"

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

struct User {
    char username[30];
    char password[30];
};

struct Buku daftarBuku[100];
int jumlahBuku = 0;

struct User admin = {"admin", "admin123"};

void setPurpleNeon() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
}

char inputYaTidak() {
    char c;
    while (1) {
        fflush(stdin);
        scanf(" %c", &c);
        if (c == 'y' || c == 'Y' || c == 'n' || c == 'N') {
            return c;
        }
        printf("Input tidak valid! Masukkan hanya (y/n): ");
    }
}

void inputPassword(char *pass) {
    char ch;
    int i = 0;
    while (1) {
        ch = getch();
        if (ch == 13) {
            pass[i] = '\0';
            printf("\n");
            break;
        } else if (ch == 8 && i > 0) {
            i--;
            printf("\b \b");
        } else {
            pass[i++] = ch;
            printf("*");
        }
    }
}

void loadingAwal() {
    system("cls");
    printf("\n\n\n\t\t\t\t  ==============================\n");
    printf("\t\t\t\t       SYSTEM PERPUSTAKAAN\n");
    printf("\t\t\t\t  ==============================\n\n");
    printf("\t\t\t              Loading, please wait...\n\n");
    printf("\t\t        [");

    for (int i = 0; i < 50; i++) {
        printf("#");
        Sleep(30);
    }

    printf("]\n");
    printf("\n\t\t\t\t          100%% Loaded!\n");
    printf("\n\t\t\t\t     Press ENTER to continue...");
    
    getch();
    system("cls");
    setPurpleNeon();
}

void login() {
    char user[50], pass[50];
    int gagal = 0;

    while (1) {
        printf("\n\t\t===== LOGIN SYSTEM =====\n\n");
        printf("\t\tUsername : ");
        scanf("%s", user);
        printf("\t\tPassword : ");
        inputPassword(pass);

        if (strcmp(user, "admin") == 0 && strcmp(pass, "admin123") == 0) {
            system("cls");
            printf("\n\t\tLogin berhasil!\n");
            break;
        } else {
            gagal++;
            printf("\n\t\tLogin gagal! Percobaan ke-%d\n", gagal);

            if (gagal >= 3) {
                printf("\n\t\tAnda sudah gagal 3 kali. Program berhenti...\n\n");
                exit(0);
            }

            printf("\t\tTekan ENTER untuk mencoba lagi...");
            getch();
            system("cls");

        }
    }

    system("cls");
	setPurpleNeon();
}


void tambahBuku() {
    system("cls");
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

    printf("\nApakah Anda yakin ingin menambah buku ini? (y/n): ");
    char konfirmasi = inputYaTidak();

    if (konfirmasi == 'y' || konfirmasi == 'Y') {
        daftarBuku[jumlahBuku++] = b;
        printf("\nBuku berhasil ditambahkan!\n");
    } else {
        printf("\nPenambahan buku dibatalkan.\n");
    }
    printf("Tekan enter untuk kembali ke menu...");
    getch();
}

void lihatBuku(int prompt) {
    system("cls");
    printf("\n=== DAFTAR BUKU ===\n");

    if (jumlahBuku == 0) {
        printf("Belum ada buku.\n");
    } else {
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

    if (prompt) {
        printf("\nTekan enter untuk kembali ke menu...");
        getch();
    }
}

void editBuku() {
    system("cls");
    lihatBuku(0);

    if (jumlahBuku == 0) {
        printf("\nTekan enter untuk kembali ke menu...");
        getch();
        return;
    }

    int id;
    printf("\nMasukkan ID buku yang akan diedit : ");
    scanf("%d", &id);

    int idx = id - 1;
    if (idx < 0 || idx >= jumlahBuku) {
        printf("\nID tidak valid!\nTekan enter untuk kembali...");
        getch();
        return;
    }

    char tmp[100];
    printf("\n=== Edit Buku (Kosongkan untuk tidak mengubah) ===\n");
    fflush(stdin);

    printf("Judul baru : ");
    fgets(tmp, sizeof(tmp), stdin);
    tmp[strcspn(tmp, "\n")] = '\0';
    if (strlen(tmp) > 0) strcpy(daftarBuku[idx].judul, tmp);

    printf("Penulis baru : ");
    fgets(tmp, sizeof(tmp), stdin);
    tmp[strcspn(tmp, "\n")] = '\0';
    if (strlen(tmp) > 0) strcpy(daftarBuku[idx].penulis, tmp);

    printf("Tahun baru : ");
    fgets(tmp, sizeof(tmp), stdin);
    tmp[strcspn(tmp, "\n")] = '\0';
    if (strlen(tmp) > 0) daftarBuku[idx].tahun = atoi(tmp);

    printf("\nApakah Anda yakin ingin mengedit buku ini? (y/n): ");
    char konfirmasi = inputYaTidak();

    if (konfirmasi == 'y' || konfirmasi == 'Y') {
        printf("\nBuku berhasil diperbarui!\n");
    } else {
        printf("\nPengeditan dibatalkan.\n");
    }

    printf("Tekan enter untuk kembali...");
    getch();
}

void hapusBuku() {
    system("cls");
    lihatBuku(0);

    if (jumlahBuku == 0) {
        printf("\nTekan enter untuk kembali...");
        getch();
        return;
    }

    int id;
    printf("\nMasukkan ID buku yang akan dihapus : ");
    scanf("%d", &id);

    int idx = id - 1;
    if (idx < 0 || idx >= jumlahBuku) {
        printf("\nID tidak valid!\nTekan enter...");
        getch();
        return;
    }

    printf("Apakah Anda yakin ingin menghapus buku ini? (y/n): ");
    char konfirmasi = inputYaTidak();

    if (konfirmasi == 'y' || konfirmasi == 'Y') {
        for (int i = idx; i < jumlahBuku - 1; i++) {
            daftarBuku[i] = daftarBuku[i + 1];
        }
        jumlahBuku--;
        printf("\nBuku berhasil dihapus!\n");
    } else {
        printf("\nPenghapusan dibatalkan.\n");
    }

    printf("Tekan enter...");
    getch();
}

void rumahPola() {
    char ulang;
    do {
        system("cls");
        int roof_height, body_height, i, j, k;
        char symbol;

        printf("Masukkan tinggi atap (ANGKA): ");
        scanf("%d", &roof_height);
        printf("Masukkan tinggi body (ANGKA): ");
        scanf("%d", &body_height);
        printf("Masukkan karakter pola: ");
        scanf(" %c", &symbol);

        system("cls");
        printf("\n=====================================\n");
        printf("=         RUMAH SUDAH JADI            =\n");
        printf("=====================================\n");
        for (i = 1; i <= roof_height; i++) {
            for (j = 1; j <= 15 - i; j++) printf(" ");
            for (k = 1; k <= i * 2 + 9; k++) {
                if (k <= 11) printf(RED "%c", symbol);
                else printf(MAGENTA "%c", symbol);
            }
            printf(RESET "\n");
            Sleep(500);
        }

        int cols = roof_height * 2 + 9;
        int body_spaces = 15 - roof_height;

        for (i = 1; i <= body_height; i++) {
            for (j = 1; j <= body_spaces; j++) printf(" ");
            for (j = 1; j <= cols; j++) {
                if (j <= 11) printf(BLUE "%c", symbol);
                else printf(YELLOW "%c", symbol);
            }
            printf(RESET "\n");
            Sleep(500);
        }
        setPurpleNeon();

        printf("\nUlang membuat rumah? (y/n): ");
        ulang = inputYaTidak();

    } while (ulang == 'y' || ulang == 'Y');
    setPurpleNeon();
}

void setColorBendera(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void benderaNegara() {
    char ulang;
    do {
        system("cls");
        int tinggi;

        printf("Masukkan tinggi bendera (ANGKA): ");
        scanf("%d", &tinggi);

        int lebar = tinggi * 8;

        printf("\n=====================================\n");
        printf("=         BENDERA SUDAH JADI        =\n");
        printf("=====================================\n");

        for (int i = 0; i < tinggi; i++) {
            setColorBendera(4);
            for (int j = 0; j < lebar; j++) printf("%c", 219);
            printf("\n");
            Sleep(20);
        }

        for (int i = 0; i < tinggi; i++) {
            setColorBendera(15);
            for (int j = 0; j < lebar; j++) printf("%c", 219);
            printf("\n");
            Sleep(20);
        }

        setColorBendera(7);
        
		setPurpleNeon();
        printf("Apakah anda mau mengulang? (y/n): ");
        ulang = inputYaTidak();

    } while (ulang == 'y' || ulang == 'Y');
    setPurpleNeon();
}

void pinjamBuku() {
    system("cls");
    lihatBuku(0);

    if (jumlahBuku == 0) {
        printf("\nTekan enter...");
        getch();
        return;
    }

    int id;
    printf("\nMasukkan ID buku yang ingin dipinjam: ");
    scanf("%d", &id);

    int idx = id - 1;
    if (idx < 0 || idx >= jumlahBuku) {
        printf("\nID tidak valid!\nTekan enter...");
        getch();
        return;
    }

    if (daftarBuku[idx].dipinjam) {
        printf("Buku sedang dipinjam oleh %s\n", daftarBuku[idx].peminjam);
        getch();
        return;
    }

    fflush(stdin);
    char nama[50];
    printf("Masukkan nama peminjam : ");
    fgets(nama, sizeof(nama), stdin);
    nama[strcspn(nama, "\n")] = '\0';

    printf("\nYakin ingin meminjam buku ini? (y/n): ");
    char konfirmasi = inputYaTidak();

    if (konfirmasi == 'y' || konfirmasi == 'Y') {
        daftarBuku[idx].dipinjam = 1;
        strcpy(daftarBuku[idx].peminjam, nama);
        printf("\nBuku berhasil dipinjam!\n");
    } else {
        printf("\nPeminjaman dibatalkan.\n");
    }

    printf("\nTekan enter...");
    getch();
}

void pengembalianBuku() {
    system("cls");
    lihatBuku(0);

    if (jumlahBuku == 0) {
        printf("\nTidak ada buku.\n");
        printf("Tekan enter untuk kembali ke menu...");
        getch();
        return;
    }

    int id;
    printf("\nMasukkan ID buku yang ingin dikembalikan : ");
    scanf("%d", &id);

    int idx = id - 1;
    if (idx < 0 || idx >= jumlahBuku) {
        printf("\nID tidak valid!\n");
        printf("Tekan enter untuk kembali ke menu...");
        getch();
        return;
    }

    if (!daftarBuku[idx].dipinjam) {
        printf("\nBuku ini tidak sedang dipinjam.\n");
        printf("Tekan enter untuk kembali ke menu...");
        getch();
        return;
    }

    printf("Buku dipinjam oleh : %s\n", daftarBuku[idx].peminjam);

    int telat;
    printf("Masukkan jumlah hari keterlambatan (0 jika tidak telat): ");
    scanf("%d", &telat);

    int denda = telat * 1000;
    printf("Total denda : Rp %d\n", denda);

    int bayar, metode;

    if (denda > 0) {
        printf("\n== Metode Pembayaran ==\n1. Cash\n2. QRIS\nPilih metode: ");
        scanf("%d", &metode);

        if (metode == 1) {
            printf("Masukkan jumlah uang cash : ");
            scanf("%d", &bayar);

            if (bayar < denda) {
                printf("Uang tidak cukup! Transaksi dibatalkan.\n");
                printf("Tekan enter untuk kembali ke menu...");
                getch();
                return;
            }

            printf("\n=== STRUK PEMBAYARAN CASH ===\n");
            printf("Uang Bayar : Rp %d\n", bayar);
            printf("Denda      : Rp %d\n", denda);
            printf("Kembalian  : Rp %d\n", bayar - denda);

        } else if (metode == 2) {
            printf("Masukkan nominal QRIS : ");
            scanf("%d", &bayar);

            if (bayar != denda) {
                printf("Nominal harus pas!\n");
                printf("Tekan enter untuk kembali ke menu...");
                getch();
                return;
            }

            printf("\n=== STRUK PEMBAYARAN QRIS ===\n");
            printf("Bayar : Rp %d\n", bayar);

        } else {
            printf("Metode tidak valid!\n");
            printf("Tekan enter untuk kembali ke menu...");
            getch();
            return;
        }
    } else {
        printf("\n=== STRUK PEMBAYARAN ===\nDenda : Rp 0\nStatus: Lunas\n");
    }

    daftarBuku[idx].dipinjam = 0;
    strcpy(daftarBuku[idx].peminjam, "-");
    daftarBuku[idx].telat = telat;

    printf("\nBuku berhasil dikembalikan!\nTekan enter untuk kembali ke menu...");
    getch();
}

void menuUtama() {
    int pilihan;
    do {
        system("cls");
        printf("\n===== MENU UTAMA PERPUSTAKAAN ======\n");
        printf("1. Tambah buku\n");
        printf("2. Lihat list buku\n");
        printf("3. Edit buku\n");
        printf("4. Hapus buku\n");
        printf("5. Rumah pola (semoga ga kena badai)\n");
        printf("6. Bendera Negara(pelis jangan error)\n");
        printf("7. Pinjam buku\n");
        printf("8. Pengembalian buku\n");
        printf("9. Exit\n");
        printf("Pilih Menu : ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1: tambahBuku(); break;
            case 2: lihatBuku(1); break;
            case 3: editBuku(); break;
            case 4: hapusBuku(); break;
            case 5: rumahPola(); break;
            case 6: benderaNegara(); break;
            case 7: pinjamBuku(); break;
            case 8: pengembalianBuku(); break;
            case 9: printf("\nTerima kasih!\n"); break;
            default: 
                printf("\nPilihan tidak valid!\n");
                printf("Tekan enter untuk memilih lagi . . .");
                getch();
                break;
        }
    } while (pilihan != 9);
}

int main() {
    setPurpleNeon();
    loadingAwal();
    login();
    menuUtama();
    return 0;
}
