#include <iostream>
#include <cstdlib>
#include <limits> 

using namespace std;

#define oren "\033[38;5;208m"
#define tebalCyan "\033[1m\033[36m"
#define merah "\033[31m"
#define cyan "\033[36m"
#define kuning "\033[33m"
#define putih "\033[0m"
#define hijau "\033[32m"
#define tebalhijau "\033[1;32m"
#define biru "\033[1;34m"

string nama;
double harga;
int stok; 
int pilihan;
int total_stok = 0;

struct Barang {
    string nama_barang;
    double harga_barang;
    int stok_barang;
};

Barang barang[2][3];

void clearscreen() {
    cout << "\033[2J\033[1;1H";
}
int hitung_total_stok(Barang (*barang)[3], int &total_stok) {
    total_stok = 0;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 3; ++j) {
            total_stok += barang[i][j].stok_barang;
        }
    }
    return total_stok;
}


void tampilkan_barang_dalam_vending_machine(Barang (*barang)[3]) {
    clearscreen();
    int total_stok = 0;
    cout << kuning << "Barang dalam vending machine:" << endl;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 3; ++j) {
        if (!barang[i][j].nama_barang.empty()) {
            cout << "Nama: " << barang[i][j].nama_barang << ", Harga: RP" << barang[i][j].harga_barang << ", Stok: " << barang[i][j].stok_barang << endl;
            total_stok += barang[i][j].stok_barang;
        }
    }
    cout << "Total stok di vending machine: " << total_stok << endl;
}}

void menu_CRUD() {
    cout << tebalCyan << "[>>>>--------> Menu CRUD Vending Machine <--------<<<<]" << putih << endl;
    cout << biru << "|1. Menambahkan barang ke Vending Machine             |" << endl;
    cout << "|2. Tampilkan barang pada Vending Machine             |" << endl;
    cout << "|3. Perbarui harga dan stok dalam Vending Machine     |" << endl;
    cout << "|4. Hapus barang dari Vending Machine                 |" << endl;
    cout << "|5. Keluar                                            |" << putih << endl;
    cout << tebalCyan << "[xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx]\n" << putih << endl;
}

void tambah_barang(Barang (*barang)[3], int& total_stok) {
    clearscreen();
    string nama_barang;
    int stok_barang;
    double harga_barang;
    cin.ignore(1000, '\n');
    do {
        cout << "Masukkan nama barang: ";
        getline(cin, nama);
    } while (nama.empty() || nama.find_first_not_of(' ') == string::npos);

    do {
        cout << "Masukkan harga baru: ";
        if (!(cin >> harga)) {
            cout << merah << "Inputan tidak valid, harus menggunakan angka!" << putih << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }
        break;
    } while (true);

    do {
        cout << "Masukkan stok baru: ";
        if (!(cin >> stok)) {
            cout << merah << "Inputan tidak valid, harus menggunakan angka!" << putih << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }
        break;
    } while (true);
        clearscreen();
            cout << kuning << "Barang berhasil ditambahkan." << putih << endl;
             int baris = total_stok
             / 3;
             int kolom = total_stok
             % 3;
             barang[baris][kolom].nama_barang = nama;
             barang[baris][kolom].harga_barang = harga;
             barang[baris][kolom].stok_barang = stok;
             total_stok
            ++;
}

void perbarui_barang() {
    clearscreen();
    cin.ignore(1000, '\n'); 
    do 
    {
        cout << "Masukkan nama barang yang ingin diperbarui: ";
        getline(cin, nama);
    } while (nama.empty() || nama.find_first_not_of(' ') == string::npos);
    do 
    {
        cout << "Masukkan harga baru: ";
        if (!(cin >> harga)) { 
            cout << merah << "Inputan tidak valid, harus menggunakan angka!" << putih << endl;
            cin.clear(); 
            cin.ignore(1000, '\n'); 
            continue; 
        }
        break; 
    } while (true);
    do {
        cout << "Masukkan stok baru: ";
        if (!(cin >> stok)) { 
            cout << merah << "Inputan tidak valid, harus menggunakan angka!" << putih << endl;
            cin.clear(); 
            cin.ignore(1000, '\n'); 
            continue; 
        }
        break; 
    } 
    while (true);
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (barang[i][j].nama_barang == nama) {
                barang[i][j].harga_barang = harga;
                barang[i][j].stok_barang = stok;
                clearscreen();
                cout << kuning << "Barang berhasil diperbarui." << putih << endl;
                return;
            }
        }
    }
    cout << merah << "Barang tidak ditemukan." << putih << endl;
}

void hapus_barang(int &total_stok) {
    clearscreen();
    cin.ignore(1000, '\n'); 
    do {
        cout << "Masukkan nama barang yang ingin dihapus: ";
        getline(cin, nama);
    } while (nama.empty() || nama.find_first_not_of(' ') == string::npos);
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (barang[i][j].nama_barang == nama) {
                barang[i][j].nama_barang.clear();
                barang[i][j].harga_barang = 0;
                barang[i][j].stok_barang = 0;
                clearscreen();
                cout << kuning << "Barang berhasil dihapus." << putih << endl;
                total_stok = hitung_total_stok(barang, total_stok); 
                return;
            }
        }
    }
    cout << merah << "Barang tidak ditemukan." << putih << endl;
}



int main() {
    clearscreen();
    do {
        menu_CRUD();
        cout << "Pilih menu yang diinginkan: ";
        if (!(cin >> pilihan)) {
            cin.clear();
            cin.ignore(1000, '\n');
            clearscreen();
            cout << merah << "Inputan harus berupa angka!" << putih << endl;
        } 
        else {
            switch (pilihan) {
                case 1:
                    clearscreen();
                    tambah_barang(barang, total_stok
                );
                    break;
                case 2:
                    clearscreen();
                    tampilkan_barang_dalam_vending_machine(barang
                );

                    
                    break;
                case 3:
                    clearscreen();
                    tampilkan_barang_dalam_vending_machine(barang);
                    perbarui_barang();
                    break;
                case 4:
                    clearscreen();
                    tampilkan_barang_dalam_vending_machine(barang);
                    hapus_barang(total_stok);
                    break;
                case 5:
                    cout << "Keluar dari program." << endl;
                    break;
                default:
                    clearscreen();
                    cout << merah << "Inputan salah, silahkan dicoba ulang." << putih << endl;
                    break;
            }
        }
    } while (pilihan != 5);
    return 0;
}
