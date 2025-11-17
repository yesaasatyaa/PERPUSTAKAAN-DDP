#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> 

#define MAX_BUKU 100

struct Buku {
    char judul[100];
    char penulis[100];
    int tahun;
};

struct Buku perpustakaan[MAX_BUKU];
int jumlahBuku = 0;

void loading() {
    printf("Memuat sistem");
    for (int i = 0; i < 5; i++) {
        printf(".");
        fflush(stdout);
        sleep(1); // jeda 1 detik
    }
    printf("\nSelesai!\n\n");
}

int login() {
    char username[50], password[50];
    const char user[] = "admin";
    const char pass[] = "123";

    printf("=== LOGIN PERPUSTAKAAN ===\n");
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    if (strcmp(username, user) == 0 && strcmp(password, pass) == 0) {
        printf("Login berhasil!\n");
        loading();
        return 1;
    } else {
        printf("Login gagal. Username atau password salah.\n");
        return 0;
    }
}

void tambahBuku() {
    if (jumlahBuku >= MAX_BUKU) {
        printf("Perpustakaan penuh!\n");
        return;
    }

    printf("Masukkan judul buku: ");
    getchar();
    fgets(perpustakaan[jumlahBuku].judul, sizeof(perpustakaan[jumlahBuku].judul), stdin);
    perpustakaan[jumlahBuku].judul[strcspn(perpustakaan[jumlahBuku].judul, "\n")] = 0;

    printf("Masukkan nama penulis: ");
    fgets(perpustakaan[jumlahBuku].penulis, sizeof(perpustakaan[jumlahBuku].penulis), stdin);
    perpustakaan[jumlahBuku].penulis[strcspn(perpustakaan[jumlahBuku].penulis, "\n")] = 0;

    printf("Masukkan tahun terbit: ");
    scanf("%d", &perpustakaan[jumlahBuku].tahun);

    jumlahBuku++;
    printf("Buku berhasil ditambahkan!\n");
}

void tampilkanBuku() {
    if (jumlahBuku == 0) {
        printf("Belum ada buku di perpustakaan.\n");
        return;
    }

    printf("\nDaftar Buku:\n");
    for (int i = 0; i < jumlahBuku; i++) {
        printf("%d. %s oleh %s (%d)\n", i + 1,
               perpustakaan[i].judul,
               perpustakaan[i].penulis,
               perpustakaan[i].tahun);
    }
}

void cariBuku() {
    char keyword[100];
    int ditemukan = 0;

    printf("Masukkan judul buku yang dicari: ");
    getchar();
    fgets(keyword, sizeof(keyword), stdin);
    keyword[strcspn(keyword, "\n")] = 0;

    for (int i = 0; i < jumlahBuku; i++) {
        if (strstr(perpustakaan[i].judul, keyword)) {
            printf("Ditemukan: %s oleh %s (%d)\n",
                   perpustakaan[i].judul,
                   perpustakaan[i].penulis,
                   perpustakaan[i].tahun);
            ditemukan = 1;
        }
    }

    if (!ditemukan) {
        printf("Buku tidak ditemukan.\n");
    }
}

int main() {
    int pilihan;

    if (!login()) {
        return 0;
    }

    do {
        printf("\n=== Menu Utama Perpustakaan ===\n");
        printf("1. Tambah Buku\n");
        printf("2. Tampilkan Buku\n");
        printf("3. Cari Buku\n");
        printf("0. Keluar\n");
        printf("Pilihan: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1: tambahBuku(); break;
            case 2: tampilkanBuku(); break;
            case 3: cariBuku(); break;
            case 0: printf("Keluar dari program.\n"); break;
            default: printf("Pilihan tidak valid.\n");
        }
    } while (pilihan != 0);

    return 0;
}
