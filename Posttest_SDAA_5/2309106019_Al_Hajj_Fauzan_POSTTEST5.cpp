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
int pilih1;


struct Barang {
    string nama_barang;
    double harga_barang;
    long stok_barang;
};

struct Node{
    Barang stuff;
    Node *next;
    Node *prev;
};

Node*head=NULL;
Node*tail=NULL;

int total_stok(){
    int jumlah = 0;
    Node *temp = head;
    while (temp != nullptr){
        jumlah += temp->stuff.stok_barang;
        temp = temp->next;
    }
    cout<<hijau << "total stok:"<< jumlah <<putih <<endl;
    return jumlah;
}
void clearscreen() {
    cout << "\033[2J\033[1;1H";
}

Node* merge_sort_ascending(Node* left, Node* right) {
    if (!left) return right;
    if (!right) return left;

    if (left->stuff.nama_barang <= right->stuff.nama_barang) {
        left->next = merge_sort_ascending(left->next, right);
        left->next->prev = left;
        return left;
    } else {
        right->next = merge_sort_ascending(left, right->next);
        right->next->prev = right;
        return right;
    }
}
Node* mergsort_ascending(Node* head) {
    if (!head || !head->next) return head;
    Node* mid = head;
    Node* fast = head->next;
    while (fast && fast->next) {
        mid = mid->next;
        fast = fast->next->next;
    }
    Node* right = mid->next;
    mid->next = nullptr;
    if (right) right->prev = nullptr;
    return merge_sort_ascending(mergsort_ascending(head), mergsort_ascending(right));
}
void shellsort_descending(Node** head) {
    int n = 0;
    Node* temp = *head;
    while (temp) {
        n++;
        temp = temp->next;
    }
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            Node* temp1 = *head;
            Node* temp2 = *head;
            for (int j = 0; j < i; j++) temp1 = temp1->next;
            for (int j = 0; j < i - gap; j++) temp2 = temp2->next;
            if (temp1->stuff.nama_barang > temp2->stuff.nama_barang) {
                swap(temp1->stuff, temp2->stuff);
            }
        }
    }
}

void tampilkan_barang_dalam_vending_machine() {
    clearscreen();
    cout << kuning << "Pilih tampilan yang diinginkan:\n";
    cout << "1. Ascending\n";
    cout << "2. Descending\n";
    cout << "3. Tampilan Biasa\n";
    cout << ": " << putih << endl;
    cin >> pilih1;
    if (head == nullptr) {
        cout << "Tidak ada barang dalam Vending Machine." << endl;
        return;
    }
    Node* originalHead = nullptr;
    Node* tempOriginal = head;
    while (tempOriginal != nullptr) {
        Node* newNode = new Node();
        newNode->stuff = tempOriginal->stuff;
        newNode->next = originalHead;
        if (originalHead != nullptr) originalHead->prev = newNode;
        originalHead = newNode;
        tempOriginal = tempOriginal->next;
    }
    if (pilih1 == 1) { 
        head = mergsort_ascending(head);  
    } else if (pilih1 == 2) { 
        shellsort_descending(&head);     
    }
    if (pilih1 == 1 || pilih1 == 2) {
        cout << hijau << "Barang dalam Vending Machine (Setelah Sorting):" << putih << endl;
        Node* temp = head;
        while (temp != nullptr) {
            cout << kuning << "Nama: " << temp->stuff.nama_barang
                 << ", Harga: RP" << temp->stuff.harga_barang
                 << ", Stok: " << temp->stuff.stok_barang << putih << endl;
            temp = temp->next;
        }
        head = originalHead;
    } 
    if (pilih1 == 3) {
        cout << hijau << "Barang dalam Vending Machine (Tampilan Biasa):" << putih << endl;
        Node* temp = head;
        while (temp != nullptr) {
            cout << kuning << "Nama: " << temp->stuff.nama_barang
                 << ", Harga: RP" << temp->stuff.harga_barang
                 << ", Stok: " << temp->stuff.stok_barang << putih << endl;
            temp = temp->next;
        }
    }
    if (pilih1 > 3 || pilih1 < 1) {
        cout << merah << "Pilihan tidak sesuai." << putih << endl;
        return;
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

void tambah_barang_depan() {
    Node* newNode = new Node;
    cout << "Masukkan nama barang: ";
    cin.ignore();
    getline(cin, newNode->stuff.nama_barang);  
    cout << "Masukkan harga barang: ";
    cin >> newNode->stuff.harga_barang;
    cout << "Masukkan stok barang: ";
    cin >> newNode->stuff.stok_barang;

    newNode->next = head;
    newNode->prev = nullptr;
    if (head != nullptr) {
        head->prev = newNode;
    }
    head = newNode;
    if (tail == nullptr) {
        tail = newNode;
    }
    clearscreen();
            cout << kuning << "Barang berhasil ditambahkan." << putih << endl;
}
void hapus_dari_depan() {
    if (head == nullptr) {
        cout << merah << "Barang kosong!" << putih << endl;
        return;
    }

    Node* temp = head;
    head = head->next;   

    delete temp;          
    cout << kuning << "Barang berhasil dihapus." << putih << endl;
}

void tambah_barang_belakang() { 
    Node* newNode = new Node;
     cin.ignore(1000, '\n');
    do {
        cout << "Masukkan nama barang: ";
        getline(cin, newNode->stuff.nama_barang);
    } while (newNode->stuff.nama_barang.empty());

    do {
        cout << "Masukkan harga baru: ";
        if (!(cin >>newNode->stuff.harga_barang)) {
            cout << merah << "Inputan tidak valid, harus menggunakan angka!" << putih << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }
        break;
    } while (true);

    do {
        cout << "Masukkan stok baru: ";
        if (!(cin >> newNode->stuff.stok_barang)) {
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
            newNode->prev = tail;     

            if (tail == nullptr) {     
                head = newNode;
                tail = newNode;
            } else {
                tail->next = newNode; 
                tail = newNode;        
            }

}


void hapus_barang_belakang() { 
    if (head == nullptr) {  
        cout << "Tidak ada barang dalam Vending Machine" << endl;
        return;
    }

    Node* temp = head;
    clearscreen();
    cout << "Barang berhasil dihapus  " << temp->stuff.nama_barang << endl;

    head = head->next;    

    if (head == nullptr) {
        tail = nullptr;
    } else {
        head->prev = nullptr; 
    }

    delete temp;  
}


void perbarui_barang() {
    clearscreen();
    if (head == nullptr) {
        cout << merah << "Barang kosong" << putih << endl;
        return;
    }

    cin.ignore(1000, '\n');  
    string nama_barang;
    Node *temp = head;


    cout << "Masukkan nama barang yang ingin diperbarui: ";
    getline(cin, nama_barang);

    while (temp != nullptr && temp->stuff.nama_barang != nama_barang) {
        temp = temp->next;
    }

    if (temp == nullptr) {
        cout << merah << "Barang tidak ditemukan" << putih << endl;
        return;
    }
    do {
        cout << "Masukkan harga baru: ";
        if (!(cin >> temp->stuff.harga_barang)) {  
            cout << merah << "Input tidak valid, harus angka!" << putih << endl;
            cin.clear();  
            cin.ignore(1000, '\n');  
            continue;
        }
        break;  
    } while (true);
    do {
        cout << "Masukkan stok baru: ";
        if (!(cin >> temp->stuff.stok_barang)) {  
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


void hapus_barang_depan() {
    clearscreen();
    Node* temp =head;
    if (head == nullptr) {
        cout << "Barang kosong"<< endl;
        return ;
    }
    tampilkan_barang_dalam_vending_machine();
    cin.ignore(1000, '\n');
    head = head->next;
     if (head != nullptr) {
        head->prev = nullptr;  
    } else {
        tail = nullptr;  
    }

    delete temp;  
    clearscreen();
    cout << kuning << "Barang berhasil dihapus." << putih << endl;
    }


int main() {
    clearscreen();
    Node *head = nullptr;
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
                    tambah_barang_depan();
                    break;
                case 2:
                    clearscreen();
                    tambah_barang_belakang();
                    break;
                case 3:
                    clearscreen();
                    tampilkan_barang_dalam_vending_machine(); 
                    total_stok(); 
                    break;
                case 4:
                    clearscreen();
                    tampilkan_barang_dalam_vending_machine();
                    perbarui_barang();
                    break;
                case 5:
                    clearscreen();
                    hapus_barang_depan();
                    break;
                case 6:
                    clearscreen();
                    hapus_barang_belakang();
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
