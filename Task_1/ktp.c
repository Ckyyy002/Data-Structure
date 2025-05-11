#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int tanggal;
    int bulan;
    int tahun;
} Tanggal;

typedef struct {
    char nik[17];
    char nama[50];
    Tanggal tanggal_lahir;
    char jenis_kelamin[2];
    char golongan_darah[3];
    char alamat[100];
    char agama[10];
    char kewarganegaraan[4];
    int aktif;
} ID;

ID ktp[50];
int amt = 0;

void print_ktp(ID ktp) {
    printf("NIK: %s\n", ktp.nik);
    printf("Nama: %s\n", ktp.nama);
    printf("Tanggal Lahir: %d/%d/%d\n", 
           ktp.tanggal_lahir.tanggal, 
           ktp.tanggal_lahir.bulan, 
           ktp.tanggal_lahir.tahun);
    printf("Jenis Kelamin: %s\n", ktp.jenis_kelamin);
    printf("Golongan Darah: %s\n", ktp.golongan_darah);
    printf("Alamat: %s\n", ktp.alamat);
    printf("Agama: %s\n", ktp.agama);
    printf("Kewarganegaraan: %s\n", ktp.kewarganegaraan);
}

int cek_nik(char nik[]) {
    for (int i = 0; i < amt; i++) {
        if (ktp[i].aktif && strcmp(ktp[i].nik, nik) == 0) {
            return i;
        }
    }
    return -1;
}

void Delete() {
    char hapus[17];
    
    printf("Masukkan NIK yang ingin dihapus: ");
    scanf("%s", hapus);
    getchar(); 
    
    int index = cek_nik(hapus);
    
    if (index != -1) {
        ktp[index].aktif = 0;
        printf("KTP dengan NIK %s sudah terhapus.\n", hapus);
    } 
    else {
        printf("KTP dengan NIK %s tidak ditemukan.\n", hapus);
    }
}

void show() {
    if (amt == 0) {
        printf("Tidak ada data KTP di database.\n");
        return;
    }
    
    printf("\n==== Data KTP ====\n");
    
    int count = 0;
    for (int i = 0; i < amt; i++) {
        if (ktp[i].aktif) {
            printf("\nKTP #%d:\n", ++count);
            print_ktp(ktp[i]);
        }
    }
    
    if (count == 0) {
        printf("Tidak ada data KTP aktif di database.\n");
    }
}

void find() {
    char cari[17];
    
    printf("Masukkan NIK yang ingin dicari: ");
    scanf("%s", cari);
    getchar(); 
    
    int index = cek_nik(cari);
    
    if (index != -1) {
        printf("\nKTP ditemukan:\n");
        print_ktp(ktp[index]);
    } 
    else {
        printf("NIK %s tidak ditemukan.\n", cari);
    }
}

void add() {
    if (amt >= 50) {
        printf("Data sudah penuh\n");
        return;
    }
    
    ID nw;
    nw.aktif = 1;
    
    printf("Masukkan NIK: ");
    scanf("%s", nw.nik);
    getchar(); 
    
    if (cek_nik(nw.nik) != -1) {
        printf("NIK %s sudah terdata.\n", nw.nik);
        return;
    }
    
    printf("Masukkan nama: ");
    fgets(nw.nama, 50, stdin);
    nw.nama[strcspn(nw.nama, "\n")] = 0; 
    
    printf("Masukkan tanggal lahir:\n");
    printf("Tanggal (1-31): ");
    scanf("%d", &nw.tanggal_lahir.tanggal);
    getchar();
    
    printf("Bulan (1-12): ");
    scanf("%d", &nw.tanggal_lahir.bulan);
    getchar();
    
    printf("Tahun (contoh: 1990): ");
    scanf("%d", &nw.tanggal_lahir.tahun);
    getchar();
    
    printf("Masukkan jenis kelamin (L/P): ");
    scanf("%s", nw.jenis_kelamin);
    getchar();
    
    printf("Masukkan golongan darah (O/A/B/AB): ");
    scanf("%s", nw.golongan_darah);
    getchar();
    
    printf("Masukkan alamat: ");
    fgets(nw.alamat, 100, stdin);
    nw.alamat[strcspn(nw.alamat, "\n")] = 0;
    
    printf("Masukkan agama: ");
    scanf("%s", nw.agama);
    getchar();
    
    printf("Masukkan kewarganegaraan: ");
    scanf("%s", nw.kewarganegaraan);
    getchar();
    
    ktp[amt] = nw;
    amt++;
    
    printf("KTP berhasil diinput\n");
}

void Menu() {
    system("clear"); 
    printf("==== Sistem Manajemen KTP ====\n");
    printf("1. Tambah KTP\n");
    printf("2. Cari KTP\n");
    printf("3. Tampilkan Semua KTP\n");
    printf("4. Hapus KTP\n");
    printf("0. Keluar\n");
    printf("Masukkan pilihanmu: ");
}

int main() {
    int pilihan;
    
    for (int i = 0; i < 50; i++) {
        ktp[i].aktif = 0;
    }
    
    while (1) {
        Menu();
        scanf("%d", &pilihan);
        getchar();
        
        switch (pilihan) {
            case 1:
                add();
                break;
            case 2:
                find();
                break;
            case 3:
                show();
                break;
            case 4:
                Delete();
                break;
            case 0:
                printf("Selamat Tinggal!\n");
                return 0;
            default:
                printf("Silahkan coba lagi!\n");
        }
        
        printf("\nKetik enter untuk melanjutkan\n");
        getchar();
    }
    
    return 0;
}
