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
int jumlah_buku = 0;

