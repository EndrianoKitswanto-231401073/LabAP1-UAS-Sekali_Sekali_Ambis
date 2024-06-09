#include <iostream>
#include <limits>
#include <iomanip>
#include <vector>
#include <ctime>
using namespace std;

vector<time_t> waktuArray; // untuk menyimpan waktu parkir

class PenjagaParkir {
public:
    string nama, id;

    // constructor
    PenjagaParkir(string nama,string id) {
        this->nama = nama;
        this->id = id;
    }

    void displayInfo() { // menampilkan informasi petugas
        system("cls");
        cout << " ===================================================================================" << endl;
        cout << " Nama Petugas : " << nama << endl;
        cout << " ID Petugas   : " << id << endl;
        cout << endl;
        cout << "                           TERIMA KASIH ATAS KERJASAMANYA !                         " << endl;
        cout << " -------------------------- S E L A M A T  B E R T U G A S -------------------------" << endl;
        cout << " ===================================================================================" << endl;
        cout << endl;
        cout << endl;
    }
};

class Mobil {
public:
    string plat, merk, warna;
    time_t waktuMasuk;

    // constructor
    Mobil(string plat, string merk, string warna) {
        this->plat = plat;
        this->merk = merk;
        this->warna = warna;
        waktuMasuk = time(0);
    }

    void display() {
        cout << " Plat mobil   : " << this->plat << endl;
        cout << " Merk mobil   : " << this->merk << endl;
        cout << " Warna mobil  : " << this->warna << endl;
        displaytimer();
    }

    void displaytimer() { // menghitung durasi parkir 
        time_t sekarang = time(0);
        time_t selisihDetik = difftime(sekarang, waktuMasuk);
        int hours = selisihDetik / 3600;
        int minutes = (selisihDetik % 3600) / 60;
        int seconds = selisihDetik % 60;

        cout << " Waktu parkir : " << hours << " jam " << minutes << " menit " << seconds << " detik\n";
        cout << endl;
    }
};

int indexAwal = 0;
void InputMobil(vector<Mobil>& kendaraan) { // menerima inputan jumlah mobil yang akan masuk
    int jumlahMobil,i;
    cout << " Masukan jumlah mobil yang akan di parkirkan : "; cin >> jumlahMobil;
    if (jumlahMobil > 20) {
        cout << " Maaf, parkiran hanya dapat memuat 20 mobil. \n";
        cout << endl;
        return;
    }
    string plat, merk, warna; 
    cin.ignore();
    if (indexAwal == 0) { // meminta user menginput data mobil
        for (i = 0; i < jumlahMobil; i++){
            cout << " Mobil ke " << i + 1 << endl;
            cout << " Masukkan plat mobil  : ";
            getline(cin, plat);

            cout << " Masukkan merk mobil  : ";
            getline(cin, merk);

            cout << " Masukkan warna mobil : ";
            getline(cin, warna);
            indexAwal++;    
            cout << endl;
            Mobil mobilBaru(plat, merk, warna);
            kendaraan.push_back(mobilBaru);
            waktuArray.push_back(mobilBaru.waktuMasuk);
        }

    } else {
        int indexTemp = indexAwal + jumlahMobil;
        if (indexTemp > 20) {
            cout << " Maaf, parkiran hanya dapat memuat 20 mobil ! \n";
            cout << endl;
        } else{
            for (i = indexAwal; i < indexTemp; i++) {
                cout << " Mobil ke " << i+1 << endl;
                cout << " Masukkan plat mobil  : ";
                getline(cin, plat);

                cout << " Masukkan merk mobil  : ";
                getline(cin, merk);

                cout << " Masukkan warna mobil : ";
                getline(cin, warna);
                indexAwal++;
                cout << endl;
                Mobil mobilBaru(plat, merk, warna);
                kendaraan.push_back(mobilBaru);
                waktuArray.push_back(mobilBaru.waktuMasuk);
            }    
        }
    }
}

void displaysemuaMobil(vector<Mobil>& kendaraan) { // menampilkan daftar mobil yang sudah terparkir
    system("cls");
    if (indexAwal != 0) {
        cout << "\n DAFTAR MOBIL YANG SUDAH TERPARKIR : \n";
        cout << " ===================================================================================" << endl;
        for (int i = 0; i < kendaraan.size(); i++) {
        cout << " Mobil ke-" << i + 1 << endl;
        const_cast<Mobil&>(kendaraan[i]).display();
        cout << " ===================================================================================" << endl;
        }
    } else {
        cout << " ===================================================================================" << endl;
        cout << " B E L U M  A D A  M O B I L  Y A N G  M A S U K \n"; // apabila tidak ada mobil yang masuk
        cout << " ===================================================================================" << endl;
        cout << endl;
    }
}

int bayarParkir(vector<Mobil>& kendaraan) {
    system("cls");
    string platInput;
    displaysemuaMobil(kendaraan);
    reply: // label untuk menginput ulang plat mobil
    cout << " Masukkan plat mobil yang ingin dibayar : ";
    getline(cin, platInput);
    int index = -1;
    for (int i = 0; i < kendaraan.size(); i++) {
        if (kendaraan[i].plat == platInput) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << " PLAT TIDAK DITEMUKAN !" << endl;
        cout << endl;
        goto reply; // apabila plat tidak di temukan, lompat ke label reply
    } else {
        time_t sekarang = time(0);
        tm *waktuSekarang = localtime(&sekarang);
        time_t waktuMasuk = waktuArray[index];
        time_t selisihDetik = difftime(sekarang, waktuMasuk);
        kendaraan.erase(kendaraan.begin() + index);
        waktuArray.erase(waktuArray.begin() + index);
        indexAwal--;
        return (selisihDetik/3600.00)*5000; // mengembalikan biaya parkir 5000 per jam
    }
}

PenjagaParkir inputPenjagaParkir() { // meminta inputan data Petugas
    string nama;
    string id;

    cout << " ===================================================================================" << endl;
    cout << " --------------------------- S E L A M A T   D A T A N G ---------------------------" << endl;
    cout << "                            DI PORTAL PARKIR KHUSUS MOBIL                           " << endl;
    cout << "                                    MALL PRIENAL                                    " << endl;
    cout << " ===================================================================================" << endl;
    cout << endl;
    cout << " Kami senang Anda telah hadir.\n Sebelum melanjutkan, silahkan masukkan informasi Anda yang akan bertugas hari ini." << endl;
    cout <<endl;
    cout << " Masukkan nama : ";
    getline(cin, nama);

    cout << " Masukkan ID   : ";
    cin >> id;
    cout << endl;
    cin.ignore(); // Membersihkan newline dari buffer

    return PenjagaParkir(nama, id);
}


int main() {

    system("Color F5");
    system("cls");

    vector<Mobil> kendaraan; // menyimpan daftar mobil
    int input;

    PenjagaParkir penjagaParkir = inputPenjagaParkir();

    penjagaParkir.displayInfo(); // menampilkan informasi petugas

    while (true) {
        cout << " Silahkan input opsi berikut dalam bentuk angka. \n";
        cout << " 1. Tambahkan Daftar Kendaraan \n";
        cout << " 2. Tampilkan Daftar Kendaraan \n";
        cout << " 3. Pembayaran \n";
        cout << " 4. Keluar Program \n";
        cout << " Masukkan opsi : "; cin >> input;
        if (cin.fail()) {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
            } 
            else {
        if(input < 1 || input > 4){
            cout << " ERROR, tidak ada pilihan \n";
        } 
        cin.ignore();
        switch (input) {
            case 1:
                InputMobil(kendaraan);
                break;
            case 2:
                displaysemuaMobil(kendaraan);
                break;
            case 3:
                if (indexAwal != 0){
                    cout << " B I A Y A  P A R K I R : " << "Rp" << bayarParkir(kendaraan) << endl;
                    cout << " ===================================================================================" << endl;
                    cout << endl;
                }else {
                    cout << " ===================================================================================" << endl;
                    cout << " B E L U M  A D A  M O B I L  Y A N G  M A S U K \n"; // apabila tidak ada mobil yang masuk
                    cout << " ===================================================================================" << endl;
                    cout << endl;
                }
                break;
            case 4:
                if (indexAwal == 0){
                    cout << " ===================================================================================" << endl;
                    cout << " ------------------------------ T E R I M A  K A S I H -----------------------------" << endl;
                    cout << "                           SUDAH MENGGUNAKAN PORTAL PARKIR                          " << endl;
                    cout << "                                    MALL PRIENAL                                    " << endl;
                    cout << " ===================================================================================" << endl;
                    cout << endl;
                    exit(0);
                }
                else {
                    cout << "MASIH TERDAPAT MOBIL DI DALAM PARKIRAN \n";
                } 
                break;
        }
    }
}
    return 0;
}



