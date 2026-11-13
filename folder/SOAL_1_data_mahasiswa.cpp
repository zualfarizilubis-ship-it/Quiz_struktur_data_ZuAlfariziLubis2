#include <iostream> // Menyertakan pustaka standar untuk input dan output (cin, cout)
#include <string>   // Menyertakan pustaka untuk menggunakan tipe data string

using namespace std; // Menggunakan namespace std agar tidak perlu menulis std:: berulang kali

// Struktur Node untuk Single Linked List (menyimpan data lengkap mahasiswa)
struct Mahasiswa {
    string nim;          // Variabel menyimpan NIM mahasiswa
    string nama;         // Variabel menyimpan Nama mahasiswa
    int nilai;           // Variabel menyimpan Nilai mahasiswa
    Mahasiswa* next;     // Pointer yang menunjuk ke node mahasiswa berikutnya
};

// Fungsi untuk menambah data mahasiswa ke dalam Single Linked List
void tambahMahasiswa(Mahasiswa*& head, string nim, string nama, int nilai) {
    Mahasiswa* baru = new Mahasiswa(); // Mengalokasikan memori baru untuk node mahasiswa
    baru->nim = nim;                   // Mengisi NIM pada node baru
    baru->nama = nama;                 // Mengisi Nama pada node baru
    baru->nilai = nilai;               // Mengisi Nilai pada node baru
    baru->next = nullptr;              // Set pointer next ke null karena akan ditaruh di akhir

    if (head == nullptr) {             // Cek apakah Linked List masih kosong
        head = baru;                   // Jika kosong, node baru menjadi head (elemen pertama)
    } else {                           // Jika tidak kosong
        Mahasiswa* temp = head;        // Buat pointer sementara mulai dari head
        while (temp->next != nullptr) {// Telusuri hingga node terakhir
            temp = temp->next;         // Geser ke node berikutnya
        }
        temp->next = baru;             // Hubungkan node terakhir dengan node baru
    }
}

// Fungsi menampilkan semua data dari Single Linked List
void tampilkanMahasiswa(Mahasiswa* head) {
    cout << "\n--- Daftar Data Mahasiswa (Single Linked List) ---\n"; // Header tampilan
    Mahasiswa* temp = head;            // Pointer bantu mulai dari head
    while (temp != nullptr) {          // Loop selama belum mencapai akhir list
        cout << "NIM: " << temp->nim << " | Nama: " << temp->nama << " | Nilai: " << temp->nilai << endl; // Cetak data
        temp = temp->next;             // Pindah ke node selanjutnya
    }
}

// Fungsi Linear Search untuk mencari mahasiswa berdasarkan NIM pada Linked List
void linearSearchNIM(Mahasiswa* head, string targetNIM) {
    Mahasiswa* temp = head;            // Mulai pencarian dari node pertama (head)
    bool ditemukan = false;            // Penanda apakah data ditemukan
    while (temp != nullptr) {          // Telusuri setiap node satu per satu
        if (temp->nim == targetNIM) {  // Bandingkan NIM node saat ini dengan target
            cout << "[Ditemukan] NIM: " << temp->nim << ", Nama: " << temp->nama << ", Nilai: " << temp->nilai << endl; // Cetak hasil
            ditemukan = true;          // Ubah status menjadi ditemukan
            break;                     // Hentikan pencarian karena NIM bersifat unik
        }
        temp = temp->next;             // Lanjut ke node berikutnya jika belum cocok
    }
    if (!ditemukan) {                  // Jika sampai akhir tidak ditemukan
        cout << "[Tidak Ditemukan] Mahasiswa dengan NIM " << targetNIM << " tidak ada.\n"; // Tampilkan pesan gagal
    }
}

// Fungsi Insertion Sort untuk mengurutkan Dynamic Array nilai dari terkecil ke terbesar
void insertionSort(int* arr, int n) {
    for (int i = 1; i < n; i++) {      // Mulai dari elemen kedua (indeks 1) hingga akhir array
        int key = arr[i];              // Simpan nilai elemen yang sedang diperiksa sebagai 'key'
        int j = i - 1;                 // Indeks elemen sebelumnya untuk dibandingkan
        // Geser elemen yang lebih besar dari 'key' ke satu posisi di sebelah kanannya
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];       // Geser elemen ke kanan
            j = j - 1;                 // Mundur ke indeks sebelumnya
        }
        arr[j + 1] = key;              // Tempatkan 'key' pada posisi yang tepat
    }
}

// Fungsi Binary Search untuk mencari nilai tertentu pada array yang sudah terurut
int binarySearchNilai(int* arr, int n, int target) {
    int kiri = 0;                      // Batas indeks paling kiri
    int kanan = n - 1;                 // Batas indeks paling kanan
    while (kiri <= kanan) {            // Ulangi selama ruang pencarian masih valid
        int tengah = kiri + (kanan - kiri) / 2; // Hitung indeks tengah untuk menghindari overflow
        if (arr[tengah] == target) {   // Jika nilai di tengah sama dengan target
            return tengah;             // Kembalikan indeks ditemukannya nilai
        }
        if (arr[tengah] < target) {    // Jika nilai tengah lebih kecil dari target
            kiri = tengah + 1;         // Abaikan bagian kiri, cari di bagian kanan
        } else {                       // Jika nilai tengah lebih besar dari target
            kanan = tengah - 1;        // Abaikan bagian kanan, cari di bagian kiri
        }
    }
    return -1;                         // Kembalikan -1 jika nilai tidak ditemukan
}

int main() {
    Mahasiswa* head = nullptr;         // Inisialisasi Single Linked List kosong
    int jumlah;                        // Variabel menampung jumlah mahasiswa

    cout << "Masukkan jumlah mahasiswa: "; // Minta input jumlah data
    cin >> jumlah;                     // Baca input jumlah

    // Alokasi Dynamic Array untuk menyimpan kumpulan nilai mahasiswa
    int* daftarNilai = new int[jumlah];

    for (int i = 0; i < jumlah; i++) { // Loop untuk menginput data setiap mahasiswa
        string nim, nama;              // Variabel lokal untuk NIM dan Nama
        int nilai;                     // Variabel lokal untuk Nilai
        cout << "\nMahasiswa ke-" << i + 1 << endl; // Penanda urutan input
        cout << "NIM   : "; cin >> nim; // Input NIM
        cin.ignore();                  // Membersihkan buffer newline sebelum getline
        cout << "Nama  : "; getline(cin, nama); // Input Nama lengkap (bisa mengandung spasi)
        cout << "Nilai : "; cin >> nilai; // Input Nilai

        tambahMahasiswa(head, nim, nama, nilai); // Simpan ke Single Linked List
        daftarNilai[i] = nilai;        // Simpan nilai ke Dynamic Array
    }

    tampilkanMahasiswa(head);          // Tampilkan seluruh data dari Linked List

    // Proses Pengurutan dengan Insertion Sort
    insertionSort(daftarNilai, jumlah); // Panggil fungsi pengurutan pada Dynamic Array
    cout << "\n--- Hasil Pengurutan Nilai (Insertion Sort) ---\n"; // Header hasil sort
    for (int i = 0; i < jumlah; i++) { // Loop mencetak isi array yang sudah terurut
        cout << daftarNilai[i] << " "; // Cetak nilai
    }
    cout << endl;                      // Baris baru

    // Fitur Pencarian NIM (Linear Search)
    string cariNIM;                    // Variabel menampung NIM yang dicari
    cout << "\nMasukkan NIM yang ingin dicari (Linear Search): "; // Minta input NIM
    cin >> cariNIM;                    // Baca input NIM
    linearSearchNIM(head, cariNIM);    // Jalankan Linear Search

    // Fitur Pencarian Nilai (Binary Search)
    int cariNilai;                     // Variabel menampung nilai yang dicari
    cout << "\nMasukkan Nilai yang ingin dicari (Binary Search): "; // Minta input nilai
    cin >> cariNilai;                  // Baca input nilai
    int hasilIndex = binarySearchNilai(daftarNilai, jumlah, cariNilai); // Jalankan Binary Search
    if (hasilIndex != -1) {            // Cek jika indeks bukan -1 (berarti ketemu)
        cout << "[Ditemukan] Nilai " << cariNilai << " ditemukan pada indeks ke-" << hasilIndex << " (setelah diurutkan).\n";
    } else {                           // Jika tidak ditemukan
        cout << "[Tidak Ditemukan] Nilai " << cariNilai << " tidak ada dalam daftar.\n";
    }

    delete[] daftarNilai;              // Dealokasi memori Dynamic Array agar tidak terjadi memory leak
    return 0;                          // Akhiri program dengan sukses
}