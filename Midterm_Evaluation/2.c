#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Timestamp {
    int hour, minute, second;
} Timestamp;

typedef struct laporan {
    int id, priority;
    char nama[31];
    Timestamp timestamp;
    struct laporan *next;
} laporan;

laporan *head = NULL;
int id = 1;

void push() {
    laporan *laporan_baru = (laporan*)malloc(sizeof(laporan));
    laporan_baru->id = id++;
    printf("Masukkan nama pelapor: ");
    getchar();
    fgets(laporan_baru->nama, 31, stdin);
    printf("Masukkan kode prioritas (1-5, 1 paling kritis): ");
    scanf("%d", &laporan_baru->priority);
    printf("Masukkan waktu laporan (jam menit detik): ");
    scanf("%d %d %d", &laporan_baru->timestamp.hour, &laporan_baru->timestamp.minute, &laporan_baru->timestamp.second);
    laporan_baru->next = NULL;

    if (head == NULL) {
        head = laporan_baru;
    } 
    else {
        laporan *current = head;
        laporan *prev = NULL;
        int new_time = (laporan_baru->timestamp.hour * 3600) + (laporan_baru->timestamp.minute * 60) + laporan_baru->timestamp.second;
        
        while (current != NULL) {
            int current_time = (current->timestamp.hour * 3600) + (current->timestamp.minute * 60) +  current->timestamp.second;
            if (laporan_baru->priority < current->priority || (laporan_baru->priority == current->priority && new_time < current_time)) {
                break;
            }
            prev = current;
            current = current->next;
        }

        if (prev == NULL) {
            laporan_baru->next = head;
            head = laporan_baru;
        } 
        else {
            laporan_baru->next = current;
            prev->next = laporan_baru;
        }
    }
}

void pop() {
    if (head == NULL) {
        printf("Tidak ada laporan dalam antrean.\n");
        return;
    }

    laporan *diproses = head;
    head = head->next;

    printf("Laporan yang diproses:\n");
    printf("ID: %d\n", diproses->id);
    printf("Nama Pelapor: %s\n", diproses->nama);
    printf("Prioritas: %d\n", diproses->priority);
    printf("Waktu laporan: %02d:%02d:%02d\n", diproses->timestamp.hour, diproses->timestamp.minute, diproses->timestamp.second);

    free(diproses);
}

void show() {
    if (head == NULL) {
        printf("Tidak ada laporan dalam antrean.\n");
        return;
    }

    laporan *current = head;
    while (current != NULL) {
        printf("ID: %d\n", current->id);
        printf("Nama Pelapor: %s", current->nama);
        printf("Prioritas: %d\n", current->priority);
        printf("Waktu laporan: %02d:%02d:%02d\n", current->timestamp.hour, current->timestamp.minute, current->timestamp.second);
        current = current->next;
    }
}

int main() {
    int choice;
    
    while (1) {
        printf("1. Tambah laporan baru\n");
        printf("2. Proses laporan\n");
        printf("3. Tampilkan semua laporan dalam antrean\n");
        printf("4. Keluar dari program\n");
        printf("Pilihan Anda: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                push();
                break;
            case 2:
                pop();
                break;
            case 3:
                show();
                break;
            default:
                printf("Keluar dari program.\n");
                while (head != NULL) {
                    laporan *temp = head;
                    head = head->next;
                    free(temp);
                }
                return 0;
        }
    }
}
