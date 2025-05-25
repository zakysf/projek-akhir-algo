#include <iostream>
#include <stdio.h>
using namespace std;

// menu
// 1. input kontak
// 2. output kontak
// 3. cari kontak
// 4. hapus kontak
// 5. edit kontak
// 6. keluar

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
    if (awal == NULL){
        return true;
    } else{
        return false;
    }
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
    } else if(awal->info.nama >= namaBaru){ //sorting langsung berdasarkan nama
        NB->next = awal;
        awal->prev = NB;
        awal = NB;
    } else{
        bantu = awal;
        while (bantu->next != NULL && bantu->next->info.nama < namaBaru){
            bantu = bantu->next;
        }
        NB->next = bantu->next; // Sisip tengah atau belakang
        if (bantu->next != NULL)
        {
            bantu->next->prev = NB;
        }
        NB->prev = bantu;
        bantu->next = NB;
        if (namaBaru > akhir->info.nama)
        {
            akhir = NB;
        }
    }
}

void tampilkanKontak(){
    if (listKosong()){
        cout << "Tidak ada kontak yang tersimpan!" << endl;
    } else{
        cout << "===========================\n";
        cout << "   Daftar Kontak\n";
        cout << "===========================\n";
        bantu = awal;
        int no = 1;
        while (bantu != NULL){
            cout << "Nama: " << bantu->info.nama << endl;
            cout << "No. Telepon: " << bantu->info.noTel << endl;
            bantu = bantu->next;
            no++;
        }
        cout << "===========================\n";
    }
}

void cariData(string cariNama){
    bool ketemu = false;
    bantu = awal;
    if (listKosong()){
        cout << "Tidak ada kontak yang tersimpan!" << endl;
    } else{
        while (bantu != NULL)
        {
            if (bantu->info.nama == cariNama){
                ketemu = true;
                cout << "Nama Kontak: " << bantu->info.nama << endl;
                cout << "No Telepon: " << bantu->info.noTel << endl;
            }
            bantu = bantu->next;
        }
        if (!ketemu){
            cout << "Data tidak ditemukan\n";
        }
    }
}

void editKontak(string& namaCari, string& namaBaru, string& noTelBaru){
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
            bantu->info.nama = namaBaru;
            bantu->info.noTel = noTelBaru;
            cout << "Kontak berhasil diedit" << endl;
        }
    }
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

        switch (pilihMenu)
        {
        case 1:
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
            }
            break;

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
            break;

        case 6:
            cout << "Terima kasih" << endl;
            return 0;
        
        default:
            cout << "Menu tidak valid" << endl;
            break;
        }
    }
       
    return 0;
}