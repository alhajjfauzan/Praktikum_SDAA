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


string nama_barang;
double harga_barang;
long stok_barang;
int pilihan;


struct Barang {
    string nama_barang;
    double harga_barang;
    long stok_barang;
    Barang *next;
};
int total_stok(Barang *head){
    int jumlah = 0;
    Barang *temp = head;
    while (temp != nullptr){
        jumlah += temp->stok_barang;
        temp = temp->next;
    }
    cout << "total stok:"<< jumlah <<endl;
}
void clearscreen() {
    cout << "\033[2J\033[1;1H";
}


void tampilkan_barang_dalam_vending_machine(Barang *head) {
    clearscreen();
    Barang *temp = head;
    if (temp == nullptr) {
        cout << "Barang belum tersedia"<< endl;
        return ;
    }
    while (temp != nullptr) {
        cout << "Barang dalam vending machine:"<< endl;
        cout << "Nama: " << temp->nama_barang <<endl;
        cout << "Harga: RP" << temp->harga_barang << endl;
        cout << "Stok: "<<temp->stok_barang<<endl;
        cout << endl;
        temp = temp->next;
    }
}
void menu_CRUD() {
    cout << tebalCyan << "[>>>>--------> Menu CRUD Vending Machine <--------<<<<]" << putih << endl;
    cout << biru << "|1. Menambahkan barang di rak depan Vending Machine   |" << endl;
    cout << "|2. Menambahkan barang di rak belakang Vending Machine|" << endl;
    cout << "|3. Tampilkan barang pada Vending Machine             |" << endl;
    cout << "|4. Perbarui harga dan stok dalam Vending Machine     |" << endl;
    cout << "|5. Hapus barang di rak depan Vending Machine         |" << endl;
    cout << "|6. Hapus barang di rak belakang Vending Machine      |" << endl;
    cout << "|7. Keluar                                            |" << putih << endl;
    cout << tebalCyan << "[xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx]\n" << putih << endl;
}
void tambah_barang_depan(Barang*& head) {
    clearscreen();
    Barang *newNode = new Barang;
    cin.ignore(1000, '\n');
    do {
        cout << "Masukkan nama barang: ";
        getline(cin,newNode->nama_barang);
    } while (newNode->nama_barang.empty());
    do {
        cout << "Masukkan harga baru: ";
        if (!(cin >> newNode->harga_barang)) {
            cout << merah << "Inputan tidak valid, harus menggunakan angka!" << putih << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }
        break;
    } while (true);

    do {
        cout << "Masukkan stok baru: ";
        if (!(cin >> newNode->stok_barang)) {
            cout << merah << "Inputan tidak valid, harus menggunakan angka!" << putih << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }
        break;
    } while (true);
        clearscreen();
            cout << kuning << "Barang berhasil ditambahkan." << putih << endl;

    newNode->next = nullptr;
    if (head == nullptr) {
        newNode->next = nullptr;
        head = newNode;
        return;
    }
    newNode->next = head;
    head = newNode;
}

void tambah_barang_belakang(Barang*& head) {
    clearscreen();
    Barang *newNode = new Barang;
    cin.ignore(1000, '\n');
    do {
        cout << "Masukkan nama barang: ";
        getline(cin, newNode->nama_barang);
    } while (newNode->nama_barang.empty());

    do {
        cout << "Masukkan harga baru: ";
        if (!(cin >>newNode->harga_barang)) {
            cout << merah << "Inputan tidak valid, harus menggunakan angka!" << putih << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }
        break;
    } while (true);

    do {
        cout << "Masukkan stok baru: ";
        if (!(cin >> newNode->stok_barang)) {
            cout << merah << "Inputan tidak valid, harus menggunakan angka!" << putih << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }
        break;
    } while (true);
        clearscreen();
            cout << kuning << "Barang berhasil ditambahkan." << putih << endl;

    if (head == nullptr) {
        head = newNode;
        return;
    }
    Barang *temp = head;
    while (temp->next != nullptr) {
        temp = temp->next;
    }

    newNode->next = nullptr;
    temp->next = newNode;
}

void perbarui_barang(Barang *&head) {
    clearscreen();
    cin.ignore(1000, '\n');  
    Barang *temp = head;
    do {
        cout << "Masukkan nama barang yang ingin diperbarui: ";
        getline(cin, nama_barang);
        if (head == nullptr) {
            cout << merah << "Barang tidak ditemukan! Silakan coba lagi." << putih << endl;
            return;
        }
        while ( temp->nama_barang != nama_barang) {
            temp = temp->next;
        }
    } while (temp == nullptr || nama_barang.empty()); 

 
    do {
        cout << "Masukkan harga baru: " << endl;
        if (!(cin >> temp->harga_barang)) {  
            cout << merah << "Input tidak valid, harus angka!" << putih << endl;
            cin.clear();  
            cin.ignore(1000, '\n');  
            continue;
        }
        break;  
    } while (true);

  
    do {
        cout << "Masukkan stok baru: " << endl;
        if (!(cin >> temp->stok_barang)) {  
            cout << merah << "Input tidak valid, harus angka!" << putih << endl;
            cin.clear(); 
            cin.ignore(1000, '\n'); 
            continue;
        }
        break;  
    } while (true);
    clearscreen();
    cout << kuning << "Barang berhasil diperbarui." << putih << endl;
}


void hapus_barang_depan(Barang *&head ) {
    clearscreen();
    Barang* temp =head;
    if (head == nullptr) {
        cout << "Barang belum tersedia"<< endl;
        return ;
    }
    tampilkan_barang_dalam_vending_machine(head);
    cin.ignore(1000, '\n');
    head = head->next;
    delete temp;
    cout << kuning << "Barang berhasil dihapus." << putih << endl;
    }

void hapus_barang_belakang(Barang *&head) {
    clearscreen();
    Barang* temp =head;
    if (head == nullptr) {
        cout << "Barang belum tersedia"<< endl;
        return ;
    }
    if (head->next == nullptr){
        delete head;
        head = nullptr;
        cout << kuning << "Barang berhasil dihapus." << putih << endl;
        return;
    }
    tampilkan_barang_dalam_vending_machine(head);
    cin.ignore(1000, '\n'); 
    while (temp->next->next != nullptr) {
        temp = temp->next;
    }
    delete temp->next;
    temp->next = nullptr;
    cout << kuning << "Barang berhasil dihapus." << putih << endl;
    }


int main() {
    clearscreen();
    Barang *head = nullptr;
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
                    tambah_barang_depan(head);
                    break;
                case 2:
                    clearscreen();
                    tambah_barang_belakang(head);
                    break;
                case 3:
                    clearscreen();
                    tampilkan_barang_dalam_vending_machine(head); 
                    total_stok(head); 
                    break;
                case 4:
                    clearscreen();
                    tampilkan_barang_dalam_vending_machine(head);
                    perbarui_barang(head);
                    break;
                case 5:
                    clearscreen();
                    hapus_barang_depan(head);
                    break;
                case 6:
                    clearscreen();
                    hapus_barang_belakang(head);
                    break;
                case 7:
                    cout << "Keluar dari program." << endl;
                    break;
                default:
                    clearscreen();
                    cout << merah << "Inputan salah, silahkan dicoba ulang." << putih << endl;
                    break;
            }
        }
    } while (pilihan != 7);
    return 0;
}
