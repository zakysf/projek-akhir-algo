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

bool login(int adminInput){
    FILE* pin = fopen("admin.dat", "rb");
    if (!pin)
    {
        cout << "File admin tidak ditemukan";
        return false;
    }
    
    int adminAsli;
    fscanf(pin, "%d", &adminAsli);
    fclose(pin);

    if (adminAsli == adminInput) {
        return true;
    } else{
        return false;
    }
    
}

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
    if (listKosong()){
        cout << "Tidak ada kontak yang tersimpan!" << endl;
    } else{
        cout << "===========================\n";
        cout << "       Daftar Kontak       \n";
        cout << "===========================\n";
        bantu = awal;
        while (bantu != NULL){
            cout << "Nama     : " << bantu->info.nama << endl;
            cout << "No. Telp : " << bantu->info.noTel << endl;
            cout << "---------------------------\n";
            bantu = bantu->next;
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
}

int main(){
    int pilihMenu, adminInput;
    string nama, noTel;
    string cariKontak;
    string namaCari, namaBaru, noTelBaru;
    FILE* pin = fopen("admin.dat", "w");
    int pinBaru = 124240071;
    fprintf(pin, "%d\n", pinBaru);
    fclose(pin);

    cout << "===========================================\n";
    cout << "  Selamat Datang di Menu Manajemen Kontak\n";
    cout << "===========================================\n";
    
    bool berhasilLogin = false;
    for (int i = 0; i < 3; i++)
    {
        cout << "Masukkan PIN anda (angka): ";
        cin >> adminInput;
        cin.ignore();
        login(adminInput);
        
        if (!login(adminInput))
        {
            cout << "PIN Salah\n";
        } else{
            berhasilLogin = true;
            break;
        }
    }

    if (!berhasilLogin)
    {
        cout << "Login gagal\n";
        return 0;
    }
    
    listBaru();
    while (true){
        system("cls");
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
                    cout << endl;
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
                cout << "Masukkan nama kontak yang ingin dihapus: ";
                getline(cin, nama);
                hapusKontak(nama);
                break;
                
            case 6:
                cout << "Terima kasih telah menggunakan program ini!\n";
                return 0;
                
            default:
                cout << "Menu tidak valid\n";
                break;
        }
        system("pause");
    }
}