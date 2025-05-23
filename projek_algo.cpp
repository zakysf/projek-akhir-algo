#include <iostream>
#include <stdio.h>
using namespace std;

struct Kontak
{
    string nama;
    string noTel;
};

struct Node
{
    Kontak info;
    Node *prev, *next;
};
Node *awal, *akhir, *bantu, *hapus, *list, *NB;

void listBaru(){
    list = NULL;
    awal = list;
    akhir = list;
}

int listKosong(){
    return (awal == NULL);
}

void tambahKontak(string& namaBaru, string& noTelBaru){
    NB = new Node;
    NB->info.nama = namaBaru;
    NB->info.noTel = noTelBaru;
    NB->next = NULL;
    NB->prev = NULL;
    if (listKosong()){
        awal = NB;
        akhir = NB;
    } else if(awal->info.nama >= namaBaru){
        NB->next = awal;
        awal->prev = NB;
        awal = NB;
    } else{
        bantu = awal;
        while (bantu->next != NULL && bantu->next->info.nama < namaBaru){
            bantu = bantu->next;
        }
        NB->next = bantu->next;
        if (bantu->next != NULL)
            bantu->next->prev = NB;
        NB->prev = bantu;
        bantu->next = NB;
        if (namaBaru > akhir->info.nama){
            akhir = NB;
        }
    }
}

void tampilkanKontak(){
    system("cls");
    if (listKosong()){
        cout << "Tidak ada kontak yang tersimpan!" << endl;
    } else{
        cout << "===========================\n";
        cout << "       Daftar Kontak       \n";
        cout << "===========================\n";
        bantu = awal;
        int no = 1;
        while (bantu != NULL){
            cout << no << ".\n";
            cout << "Nama     : " << bantu->info.nama << endl;
            cout << "No. Telp : " << bantu->info.noTel << endl;
            cout << "---------------------------\n";
            bantu = bantu->next;
            no++;
        }
        cout << "===========================\n";
    }
    cout << "Tekan ENTER untuk kembali ke menu...";
    cin.ignore();
    cin.get();
    system("cls");
}

void cariData(string cariNama){
    system("cls");
    bool ketemu = false;
    bantu = awal;
    if (listKosong()){
        cout << "Tidak ada kontak yang tersimpan!" << endl;
    } else{
        while (bantu != NULL){
            if (bantu->info.nama == cariNama){
                ketemu = true;
                cout << "Nama Kontak: " << bantu->info.nama << endl;
                cout << "No Telepon: " << bantu->info.noTel << endl;
                break;
            }
            bantu = bantu->next;
        }
        if (!ketemu){
            cout << "Data tidak ditemukan\n";
        }
    }
    cout << "Tekan ENTER untuk kembali ke menu...";
    cin.ignore();
    cin.get();
    system("cls");
}

void hapusKontak(string namaHapus, bool silent = false) {
    if (listKosong()) {
        if (!silent) cout << "Tidak ada kontak yang tersimpan!" << endl;
        return;
    }

    bantu = awal;
    while (bantu != NULL && bantu->info.nama != namaHapus) {
        bantu = bantu->next;
    }

    if (bantu == NULL) {
        if (!silent) cout << "Kontak tidak ditemukan!" << endl;
        return;
    }

    if (bantu == awal && bantu == akhir) {
        awal = NULL;
        akhir = NULL;
    } else if (bantu == awal) {
        awal = bantu->next;
        awal->prev = NULL;
    } else if (bantu == akhir) {
        akhir = bantu->prev;
        akhir->next = NULL;
    } else {
        bantu->prev->next = bantu->next;
        bantu->next->prev = bantu->prev;
    }

    delete bantu;
    if (!silent) {
        cout << "Kontak berhasil dihapus!" << endl;
        cout << "Tekan ENTER untuk kembali ke menu...";
        cin.ignore();
        cin.get();
        system("cls");
    }
}

void editKontak(string& namaCari, string& namaBaru, string& noTelBaru){
    system("cls");
    if (listKosong()){
        cout << "Tidak ada kontak yang tersimpan" << endl;
    } else{
        bantu = awal;
        while (bantu != NULL && bantu->info.nama != namaCari){
            bantu = bantu->next;
        }
        if (bantu == NULL){
            cout << "Kontak tidak ditemukan" << endl;
        } else{
            hapusKontak(namaCari, true);
            tambahKontak(namaBaru, noTelBaru);
            cout << "Kontak berhasil diedit" << endl;
        }
    }
    cout << "Tekan ENTER untuk kembali ke menu...";
    cin.ignore();
    cin.get();
    system("cls");
}

int main(){
    int pilihMenu;
    string nama, noTel;
    string cariKontak;
    string namaCari, namaBaru, noTelBaru;

    listBaru();
    while (true){
        cout << "===========================\n";
        cout << "   Menu Manajemen Kontak\n";
        cout << "===========================\n";
        cout << " 1. Tambah kontak\n";
        cout << " 2. Tampilkan semua kontak\n";
        cout << " 3. Cari kontak\n";
        cout << " 4. Edit kontak\n";
        cout << " 5. Hapus kontak\n";
        cout << " 6. Keluar\n";
        cout << "===========================\n";
        cout << " Pilih menu: ";
        cin >> pilihMenu;
        cin.ignore();
        system("cls");

        switch (pilihMenu){
            case 1: {
                int jmlInput;
                cout << "Masukkan jumlah kontak yang ingin ditambahkan: ";
                cin >> jmlInput;
                cin.ignore();
                for (int i = 0; i < jmlInput; i++) {
                    cout << "Masukkan nama kontak ke-" << (i+1) << ": ";
                    getline(cin, nama);
                    cout << "Masukkan nomor kontak ke-" << (i+1) << ": ";
                    getline(cin, noTel);
                    tambahKontak(nama, noTel);
                    system("cls");
                }
                cout << "Kontak berhasil ditambahkan!\n";
                cout << "Tekan ENTER untuk kembali ke menu...";
                cin.get();
                system("cls");
                break;
            }
            case 2:
                tampilkanKontak();
                break;

            case 3:
                cout << "Masukkan nama kontak yang akan dicari: ";
                getline(cin, cariKontak);
                cariData(cariKontak);
                break;

            case 4:
                cout << "Masukkan nama kontak yang ingin diedit: ";
                getline(cin, namaCari);
                cout << "Masukkan nama baru: ";
                getline(cin, namaBaru);
                cout << "Masukkan nomor baru: ";
                getline(cin, noTelBaru);
                editKontak(namaCari, namaBaru, noTelBaru);
                break;

            case 5:
                cout << "Masukkan nama kontak yang ingin dihapus: ";
                getline(cin, nama);
                hapusKontak(nama);
                break;

            case 6:
                cout << "Terima kasih telah menggunakan program ini!\n";
                return 0;

            default:
                cout << "Menu tidak valid\n";
                cout << "Tekan ENTER untuk kembali ke menu...";
                cin.get();
                system("cls");
                break;
        }
    }

    return 0;
}
