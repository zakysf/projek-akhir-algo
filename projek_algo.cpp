#include <iostream>
#include <stdio.h>
#include <iomanip>
using namespace std;

struct admin
{
    string nama;
    int pin;
};

struct Kontak
{
    string nama;
    string noTel;
};

struct Node
{
    admin infoAdmin;
    Kontak info;
    Node *prev, *next;
};

Node *awal, *akhir, *bantu, *list, *NB;

void registerAdmin()
{
    admin newAdmin;
    cout << "Masukkan nama admin: ";
    getline(cin, newAdmin.nama);
    cout << "Masukkan PIN (angka): ";
    cin >> newAdmin.pin;
    cin.ignore();

    FILE *file = fopen("admin.dat", "ab");
    if (!file)
    {
        cout << "File admin tidak ditemukan\n";
        return;
    }

    fprintf(file, "%s|%d\n", newAdmin.nama.c_str(), newAdmin.pin);
    fclose(file);
    cout << "Admin berhasil diregistrasi!\n";
}

string login(int adminInput)
{
    FILE *file = fopen("admin.dat", "r");
    if (!file)
    {
        cout << "File admin tidak ditemukan.\n";
        return "";
    }

    char nama[100];
    int pin;

    while (fscanf(file, " %99[^|]|%d\n", nama, &pin) == 2)
    {
        if (adminInput == pin)
        {
            fclose(file);
            return string(nama); // return nama admin
        }
    }

    fclose(file);
    return "";
}

void listBaru()
{
    list = NULL;
    awal = list;
    akhir = list;
}

int listKosong()
{
    return (awal == NULL);
}

void tambahKontak(string namaBaru, string noTelBaru)
{
    NB = new Node;
    NB->info.nama = namaBaru;
    NB->info.noTel = noTelBaru;
    NB->next = NULL;
    NB->prev = NULL;

    if (listKosong())
    {
        awal = akhir = NB;
    }
    else if (awal->info.nama >= namaBaru)
    {
        NB->next = awal;
        awal->prev = NB;
        awal = NB;
    }
    else
    {
        bantu = awal;
        while (bantu->next != NULL && bantu->next->info.nama < namaBaru)
        {
            bantu = bantu->next;
        }
        NB->next = bantu->next;
        if (bantu->next != NULL)
            bantu->next->prev = NB;
        NB->prev = bantu;
        bantu->next = NB;
        if (NB->next == NULL)
            akhir = NB;
    }
}

void tampilkanKontak()
{
    if (listKosong())
    {
        cout << "Tidak ada kontak yang tersimpan!" << endl;
    }
    else
    {
        cout << "==============================================\n";
        cout << "               Daftar Kontak                   \n";
        cout << "==============================================\n";
        cout << left << setw(30) << "Nama" << " | " << setw(15) << "No. Telepon" << endl;
        cout << "----------------------------------------------\n";

        bantu = awal;
        while (bantu != NULL)
        {
            cout << left << setw(30) << bantu->info.nama << " | " << setw(15) << bantu->info.noTel << endl;
            bantu = bantu->next;
        }
        cout << "==============================================\n";
    }
}

void cariData(string cariNama)
{
    bool ketemu = false;
    bantu = awal;

    if (listKosong())
    {
        cout << "Tidak ada kontak yang tersimpan!" << endl;
    }
    else
    {
        while (bantu != NULL)
        {
            if (bantu->info.nama == cariNama)
            {
                ketemu = true;
                cout << "Nama Kontak : " << bantu->info.nama << endl;
                cout << "No Telepon  : " << bantu->info.noTel << endl;
                break;
            }
            bantu = bantu->next;
        }
        if (!ketemu)
        {
            cout << "Data tidak ditemukan\n";
        }
    }
}

void hapusKontak(string namaHapus, bool silent = false)
{
    if (listKosong())
    {
        if (!silent)
            cout << "Tidak ada kontak yang tersimpan!" << endl;
        return;
    }

    bantu = awal;
    while (bantu != NULL && bantu->info.nama != namaHapus)
    {
        bantu = bantu->next;
    }

    if (bantu == NULL)
    {
        if (!silent)
            cout << "Kontak tidak ditemukan!" << endl;
        return;
    }

    if (bantu == awal && bantu == akhir)
    {
        awal = akhir = NULL;
    }
    else if (bantu == awal)
    {
        awal = bantu->next;
        if (awal)
            awal->prev = NULL;
    }
    else if (bantu == akhir)
    {
        akhir = bantu->prev;
        if (akhir)
            akhir->next = NULL;
    }
    else
    {
        bantu->prev->next = bantu->next;
        bantu->next->prev = bantu->prev;
    }

    delete bantu;
    if (!silent)
    {
        cout << "Kontak berhasil dihapus!" << endl;
    }
}

void editKontak(string namaCari, string namaBaru, string noTelBaru)
{
    system("cls");
    if (listKosong())
    {
        cout << "Tidak ada kontak yang tersimpan" << endl;
    }
    else
    {
        bantu = awal;
        while (bantu != NULL && bantu->info.nama != namaCari)
        {
            bantu = bantu->next;
        }
        if (bantu == NULL)
        {
            cout << "Kontak tidak ditemukan" << endl;
        }
        else
        {
            hapusKontak(namaCari, true);
            tambahKontak(namaBaru, noTelBaru);
            cout << "Kontak berhasil diedit" << endl;
        }
    }
}

void simpanKeFile()
{
    FILE *file = fopen("kontak.txt", "w");
    if (!file)
    {
        cout << "Gagal menyimpan ke file\n";
        return;
    }

    bantu = awal;
    while (bantu != NULL)
    {
        fprintf(file, "%s | %s\n", bantu->info.nama.c_str(), bantu->info.noTel.c_str());
        bantu = bantu->next;
    }

    fclose(file);
}

void tambahKeFile()
{
    FILE *file = fopen("kontak.txt", "a");
    if (!file)
    {
        cout << "Gagal menyimpan ke file\n";
        return;
    }

    bantu = awal;
    while (bantu != NULL)
    {
        fprintf(file, "%s | %s\n", bantu->info.nama.c_str(), bantu->info.noTel.c_str());
        bantu = bantu->next;
    }

    fclose(file);
}

void muatDariFile()
{
    FILE *file = fopen("kontak.txt", "r");
    if (!file)
        return;

    char nama[100], noTel[13];
    while (fscanf(file, " %99[^|] | %12[^\n]\n", nama, noTel) == 2)
    {
        string namaStr(nama);
        string noTelStr(noTel);
        tambahKontak(namaStr, noTelStr);
    }

    fclose(file);
}

void urutkanAscending()
{
    if (listKosong())
        return;

    Node *i, *j;
    for (i = awal; i != NULL; i = i->next)
    {
        for (j = i->next; j != NULL; j = j->next)
        {
            if (i->info.nama > j->info.nama)
            {
                swap(i->info, j->info);
            }
        }
    }
    cout << "Kontak telah diurutkan secara ascending.\n";
}

void urutkanDescending()
{
    if (listKosong())
        return;

    Node *i, *j;
    for (i = awal; i != NULL; i = i->next)
    {
        for (j = i->next; j != NULL; j = j->next)
        {
            if (i->info.nama < j->info.nama)
            {
                swap(i->info, j->info);
            }
        }
    }
    cout << "Kontak telah diurutkan secara descending.\n";
}

bool validNoTel(string noTel)
{
    if (noTel.length() > 12)
        return false;

    for (int i = 0; i < (int)noTel.length(); i++)
    {
        char c = noTel[i];
        if (!(c >= '0' && c <= '9'))
        {
            return false;
        }
    }
    return true;
}

int main()
{
    int pilihMenu, adminInput, pilihMenuAwal;
    string namaAdminLogin;
    string nama, noTel;
    string cariKontak;
    string namaCari, namaBaru, noTelBaru;
    bool berhasilLogin = false;

    cout << "===========================================\n";
    cout << "  Selamat Datang di Menu Manajemen Kontak\n";
    cout << "===========================================\n";
    cout << " 1. Login\n";
    cout << " 2. Register\n";
    cout << " 3. Keluar\n";
    cout << "===========================================\n";
    cout << " Pilihan anda: ";
    cin >> pilihMenuAwal;
    cin.ignore();

    switch (pilihMenuAwal)
    {
    case 1:
        for (int i = 0; i < 3; i++)
        {
            cout << "Masukkan PIN anda (angka): ";
            cin >> adminInput;
            cin.ignore();

            namaAdminLogin = login(adminInput);
            if (namaAdminLogin == "")
            {
                cout << "PIN Salah\n";
            }
            else
            {
                berhasilLogin = true;
                break;
            }
        }
        if (!berhasilLogin)
        {
            cout << "Login gagal\n";
            return 0;
        } else{
            break;
        }
        break;

    case 2:
        registerAdmin();
        for (int i = 0; i < 3; i++)
        {
            cout << "Masukkan PIN anda (angka): ";
            cin >> adminInput;
            cin.ignore();

            namaAdminLogin = login(adminInput);
            if (namaAdminLogin == "")
            {
                cout << "PIN Salah\n";
            }
            else
            {
                berhasilLogin = true;
                break;
            }
        }

        if (!berhasilLogin)
        {
            cout << "Login gagal\n";
            return 0;
        }
        else
        {
            break;
        }
        break;

    case 3:
        cout << "Keluar dari program.\n";
        return 0;

    default:
        cout << "Pilihan tidak valid.\n";
        return 0;
    }

    listBaru();
    muatDariFile();

    while (true)
    {
        system("cls");
        cout << "===========================\n";
        cout << "   Menu Manajemen Kontak\n";
        cout << "   Admin: " << namaAdminLogin << endl;
        cout << "===========================\n";
        cout << " 1. Tambah kontak\n";
        cout << " 2. Tampilkan semua kontak\n";
        cout << " 3. Cari kontak\n";
        cout << " 4. Edit kontak\n";
        cout << " 5. Hapus kontak\n";
        cout << " 6. Urutkan kontak\n";
        cout << " 7. Keluar\n";
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
            for (int i = 0; i < jmlInput; i++)
            {
                cout << "\nMasukkan nama kontak ke-" << (i + 1) << ": ";
                getline(cin, nama);

                do
                {
                    cout << "Masukkan nomor kontak ke-" << (i + 1) << " (max 12 digit): ";
                    getline(cin, noTel);
                    if (!validNoTel(noTel))
                    {
                        cout << "Nomor telepon tidak valid, coba lagi.\n";
                    }
                } while (!validNoTel(noTel));

                tambahKontak(nama, noTel);
                cout << "Kontak berhasil ditambahkan!";
                tambahKeFile();
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
            cout << "\nMasukkan nama baru: ";
            getline(cin, namaBaru);
            cout << "Masukkan nomor baru (max 12 digit): ";
            do
            {
                getline(cin, noTelBaru);
                if (!validNoTel(noTelBaru))
                {
                    cout << "Nomor telepon tidak valid, coba lagi.\n";
                }
            } while (!validNoTel(noTelBaru));
            editKontak(namaCari, namaBaru, noTelBaru);
            simpanKeFile();
            break;

        case 5:
            cout << "Masukkan nama kontak yang ingin dihapus: ";
            getline(cin, nama);
            hapusKontak(nama);
            simpanKeFile();
            break;

        case 6:
            int pilihSort;
            cout << "===========================\n";
            cout << "     Metode Pengurutan\n";
            cout << "===========================\n";
            cout << "1. Ascending\n";
            cout << "2. Descending\n";
            cout << "Pilih: ";
            cin >> pilihSort;
            cin.ignore();

            system("cls");

            if (pilihSort == 1)
            {
                urutkanAscending();
            }
            else if (pilihSort == 2)
            {
                urutkanDescending();
            }
            else
            {
                cout << "Pilihan tidak valid\n";
                break;
            }
            tampilkanKontak();
            simpanKeFile();
            break;

        case 7:
            simpanKeFile();
            cout << "Terima kasih telah menggunakan program ini!\n";
            return 0;

        default:
            cout << "Menu tidak valid\n";
            break;
        }

        system("pause");
    }
}