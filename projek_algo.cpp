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

Node *awal, *akhir, *bantu, *list, *NB; // node untuk berbagai macam operasi linked list

void registerAdmin()
{
    admin newAdmin;
    cout << "Masukkan nama admin: "; // nama admin yang baru
    getline(cin, newAdmin.nama);
    cout << "Masukkan PIN (angka): "; // pin yang baru
    cin >> newAdmin.pin;
    cin.ignore();

    FILE *file = fopen("admin.dat", "ab");
    if (!file)
    {
        cout << "File admin tidak ditemukan\n";
        return;
    }

    fprintf(file, "%s|%d\n", newAdmin.nama.c_str(), newAdmin.pin); // masukkan info admin ke file admin.dat
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

    while (fscanf(file, " %99[^|]|%d\n", nama, &pin) == 2) // mengambil data admin
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

void listBaru() // fungsi membuat list baru
{
    list = NULL;
    awal = list;
    akhir = list;
}

int listKosong() // fungsi cek list kosong
{
    return (awal == NULL);
}

bool namaSudahAda(string namaCek)
{
    Node *temp = awal;
    while (temp != NULL)
    {
        if (temp->info.nama == namaCek)
        {
            return true; // nama ditemukan
        }
        temp = temp->next;
    }
    return false; // nama belum ada
}

void tambahKontak(string namaBaru, string noTelBaru) // fungsi menambah kontak
{
    NB = new Node;              // deklarasi node baru
    NB->info.nama = namaBaru;   // nama baru disimpan dalam node
    NB->info.noTel = noTelBaru; // no tel baru disimpan dalam node
    NB->next = NULL;
    NB->prev = NULL;

    if (listKosong()) // jika list tidak ada atau kosong
    {
        awal = akhir = NB; // node baru akan menjadi list baru
    }
    else if (awal->info.nama >= namaBaru) // jika nilai node baru kurang dari node pertama
    {
        NB->next = awal;
        awal->prev = NB;
        awal = NB; // sisipkan node baru ke node pertama
    }
    else
    {
        bantu = awal;                                                    // node awal disimpan dalam node bantu
        while (bantu->next != NULL && bantu->next->info.nama < namaBaru) // selama nilai node belum kosong (null) dan info nama node yang selanjutnya masih lebih kecil nilainya dari nama yang baru diinput
        {
            bantu = bantu->next; // menulusuri semua node dari awal hingga akhir
        }
        NB->next = bantu->next;
        if (bantu->next != NULL)    // jika selama ditelusuri, node tidak bernilai kosong
            bantu->next->prev = NB; // bikin node baru
        NB->prev = bantu;           // menyisipkan node diantara bantu dan bantu->next
        bantu->next = NB;           // memastikan node bantu terhubung dengan NB
        if (NB->next == NULL)       // jika akhir node bernilai kosong
            akhir = NB;             // NB menjadi node akhir
    }
}

void tampilkanKontak()
{
    if (listKosong()) // memastikan list tidak kosong
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
        } // selama list belum bernilai kosong, lakukan print semua info node
        cout << "==============================================\n";
    }
}

void cariData(string cariNama) // fungsi cari nama
{
    bool ketemu = false;
    bantu = awal;

    if (listKosong()) // memastikan list agar tidak kosong
    {
        cout << "Tidak ada kontak yang tersimpan!" << endl;
    }
    else
    {
        while (bantu != NULL) // selama node belum bernilai kosong
        {
            if (bantu->info.nama == cariNama) // bandingkan satu-satu semua node dengan nama yang dicari
            {
                ketemu = true;
                cout << "Nama Kontak : " << bantu->info.nama << endl;
                cout << "No Telepon  : " << bantu->info.noTel << endl;
                break;
            }
            bantu = bantu->next;
        }
        if (!ketemu) // jika tidak ketemu
        {
            cout << "Data tidak ditemukan\n";
        }
    }
}

void hapusKontak(string namaHapus, bool silent = false) // fungsi untuk menghapus kontak berdasarkan nama yang diberikan
{
    if (listKosong()) // cek apakah linked list kosong (tidak ada kontak sama sekali)
    {
        if (!silent) // jika mode tidak silent, tampilkan pesan
            cout << "Tidak ada kontak yang tersimpan!" << endl;
        return; // keluar fungsi karena tidak ada kontak yang bisa dihapus
    }

    bantu = awal; // mulai pencarian dari node awal linked list
    // telusuri linked list selama belum sampai akhir dan nama pada node tidak sama dengan nama yang ingin dihapus
    while (bantu != NULL && bantu->info.nama != namaHapus)
    {
        bantu = bantu->next;
    }

    if (bantu == NULL) // jika sampai akhir linked list tapi kontak tidak ditemukan
    {
        if (!silent)
            cout << "Kontak tidak ditemukan!" << endl; // tampilkan pesan jika tidak dalam mode silent
        return;                                        // keluar fungsi karena kontak tidak ada
    }

    // jika kontak ditemukan, lakukan penghapusan dengan memperhatikan posisi node:
    if (bantu == awal && bantu == akhir) // jika hanya ada satu node di list (awal dan akhir sama)
    {
        awal = akhir = NULL; // set list menjadi kosong
    }
    else if (bantu == awal) // jika node yang dihapus adalah node pertama
    {
        awal = bantu->next; // geser pointer awal ke node berikutnya
        if (awal)
            awal->prev = NULL; // node baru awal tidak punya prev (null)
    }
    else if (bantu == akhir) // jika node yang dihapus adalah node terakhir
    {
        akhir = bantu->prev; // geser pointer akhir ke node sebelumnya
        if (akhir)
            akhir->next = NULL; // node baru akhir tidak punya next (null)
    }
    else // jika node berada di tengah list
    {
        bantu->prev->next = bantu->next; // hubungkan node sebelumnya ke node setelahnya
        bantu->next->prev = bantu->prev; // hubungkan node setelahnya ke node sebelumnya
    }

    delete bantu; // hapus node dari memori

    if (!silent) // jika mode tidak silent, tampilkan pesan sukses
    {
        cout << "Kontak berhasil dihapus!" << endl;
    }
}

void editKontak(string namaCari, string namaBaru, string noTelBaru) // fungsi edit kontak
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

void simpanKeFile() // fungsi simpan data dari linked list ke file
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

void tambahKeFile() // fungsi tambah data dari linked list ke file
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

void muatDariFile() // fungsi membaca data dari file ke linked list
{
    FILE *file = fopen("kontak.txt", "r");
    if (!file)
        return;

    char nama[100], noTel[13];
    while (fscanf(file, " %99[^|] | %12[^\n]\n", nama, noTel) == 2)
    {
        string namaStr(nama);   // konversi array char nama ke string C++
        string noTelStr(noTel); // konversi array char noTel ke string C++
        tambahKontak(namaStr, noTelStr);
    }

    fclose(file);
}

void urutkanAscending() // fungsi mengurutkan data secara ascending
{
    if (listKosong())
        return;

    Node *i, *j;
    for (i = awal; i != NULL; i = i->next)
    {
        for (j = i->next; j != NULL; j = j->next)
        {
            if (i->info.nama > j->info.nama) // data dibandingkan dengan nama
            {
                swap(i->info, j->info); // tukar data jika lebih besar
            }
        }
    }
    cout << "Kontak telah diurutkan secara ascending.\n";
}

void urutkanDescending() // fungsi mengurutkan data secara descending
{
    if (listKosong())
        return;

    Node *i, *j;
    for (i = awal; i != NULL; i = i->next)
    {
        for (j = i->next; j != NULL; j = j->next)
        {
            if (i->info.nama < j->info.nama) // data dibandingkan dengan nama
            {
                swap(i->info, j->info); // tukar data jika lebih kecil
            }
        }
    }
    cout << "Kontak telah diurutkan secara descending.\n";
}

bool validNoTel(string noTel) // fungsi memvalidasi no tel agar tidak lebih dari 12 karakter
{
    if (noTel.length() > 12) // jika no tel melebihi 12 digit maka false
        return false;

    // Perulangan untuk memeriksa setiap karakter dalam string noTel
    for (int i = 0; i < (int)noTel.length(); i++)
    {
        char c = noTel[i];           // ambil karakter ke-i dari string
        if (!(c >= '0' && c <= '9')) // jika karakter bukan angka (bukan antara '0' sampai '9')
        {
            return false; // maka kembalikan false karena tidak valid
        }
    }

    return true; // jika semua karakter adalah angka dan panjangnya valid, kembalikan true
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
    case 1:                                                 // login
        for (int percobaan = 3; percobaan > 0; percobaan--) // login memiliki 3 percobaan
        {
            cout << "Masukkan PIN anda (angka): ";
            cin >> adminInput;
            cin.ignore();

            namaAdminLogin = login(adminInput); // membandingkan nama admin yang ada dengan nama yang diinput
            if (namaAdminLogin == "")
            {
                cout << "PIN Salah\n";
                cout << "Kesempatan tersisa: " << percobaan - 1 << "\n";
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

    case 2:                                                 // registrasi
        registerAdmin();                                    // registrasi akun admin
        for (int percobaan = 3; percobaan > 0; percobaan--) // login kembali setelah register
        {
            cout << "Masukkan PIN anda (angka): ";
            cin >> adminInput;
            cin.ignore();

            namaAdminLogin = login(adminInput);
            if (namaAdminLogin == "")
            {
                cout << "PIN Salah\n";
                cout << "Kesempatan tersisa: " << percobaan - 1 << "\n";
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

    case 3: // keluar program
        cout << "Keluar dari program.\n";
        return 0;

    default:
        cout << "Pilihan tidak valid.\n";
        return 0;
    }

    listBaru();     // membuat list baru
    muatDariFile(); // mengambil data kontak dari file

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
        cout << " 7. Logout\n";
        cout << " 8. Keluar Program\n";
        cout << "===========================\n";
        cout << " Pilih menu: ";
        cin >> pilihMenu;
        cin.ignore();
        system("cls");

        switch (pilihMenu)
        {
        case 1: // input kontak
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

                if (namaSudahAda(nama))
                {
                    cout << "Nama kontak \"" << nama << "\" sudah ada, silakan gunakan nama yang berbeda.\n";
                    i--; // ulangi input untuk kontak ini
                }
                else
                {
                    tambahKontak(nama, noTel);
                    cout << "Kontak berhasil ditambahkan!";
                    tambahKeFile();
                }
                cout << endl;
            }
            break;

        case 2: // menampilkan kontak yang tersimpan
            tampilkanKontak();
            break;

        case 3: // mencari kontak
            cout << "Masukkan nama kontak yang akan dicari: ";
            getline(cin, cariKontak);
            cariData(cariKontak);
            break;

        case 4: // mengedit data kontak
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

        case 5: // menghapus data kontak
            cout << "Masukkan nama kontak yang ingin dihapus: ";
            getline(cin, nama);
            hapusKontak(nama);
            simpanKeFile();
            break;

        case 6: // sorting kontak
            int pilihSort;
            cout << "===========================\n";
            cout << "     Metode Pengurutan\n";
            cout << "===========================\n";
            cout << " 1. Ascending\n";
            cout << " 2. Descending\n";
            cout << "===========================\n";
            cout << "Pilih: ";
            cin >> pilihSort;
            cin.ignore();

            system("cls");

            if (pilihSort == 1) // sorting ascending
            {
                urutkanAscending();
            }
            else if (pilihSort == 2) // sorting descending
            {
                urutkanDescending();
            }
            else
            {
                cout << "Pilihan tidak valid\n";
                break;
            }
            tampilkanKontak();
            break;

        case 7: // logout
            main();
            return 0;

        case 8: // keluar program
            simpanKeFile();
            cout << "Terima kasih telah menggunakan program ini!\n";
            return 0;

        default: // error handling jika input tidak sesuai dari 1 - 7
            cout << "Menu tidak valid\n";
            break;
        }
        system("pause");
    }
}