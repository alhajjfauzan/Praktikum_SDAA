#include <iostream>
using namespace std;

void algoritma_hanoi(int n, string asal, string sementara, string tujuan) {
    if(n == 1) {
        cout << "piringan "<<n <<" dari"<<" "<< asal << " pindah ke " << tujuan << endl;
        cout<<"====================================================="<<endl;
    } else {
        algoritma_hanoi(n-1, asal, tujuan, sementara);
        cout << "piringan " <<n<< " dari"<<" "<< asal << " pindah ke " << tujuan << endl;
        algoritma_hanoi(n-1, sementara, asal, tujuan);
    } 
    
}

int main() {
    int n = 3;
    string awal = "asal";
    string tengah = "sementara";
    string akhir = "tujuan";
    cout<<"Algoritma Menara Hanoi"<<endl;
    algoritma_hanoi(n, awal, tengah, akhir);
}
