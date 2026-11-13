#include <iostream> 
#include <string>   

using namespace std;

const int TABLE_SIZE = 20; // Ukuran tetap Hash Table adalah 20

// Enum untuk menandai status setiap slot di dalam Hash Table
enum Status {
    EMPTY,   // Slot belum pernah diisi
    OCCUPIED,// Slot sedang terisi data aktif
    DELETED  // Slot pernah terisi namun datanya sudah dihapus (penting untuk probing)
};

// Struktur data untuk menyimpan setiap entri mahasiswa
struct Entry {
    long long nim; 
    string nama;  
    Status status;
};

class HashTable {
private:
    Entry table[TABLE_SIZE]; // Array Hash Table berukuran 20

    // Fungsi Hash pertama: Hash1(key) = key % 20
    int hash1(long long key) {
        return key % TABLE_SIZE; // Menghasilkan indeks awal (0 - 19)
    }

    // Fungsi Hash kedua untuk menangani collision: Hash2(key) = 19 - (key % 19)
    int hash2(long long key) {
        return 19 - (key % 19);  // Menghasilkan langkah lompatan (1 - 19)
    }

public:
    // Konstruktor: menginisialisasi seluruh slot dalam keadaan EMPTY
    HashTable() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            table[i].status = EMPTY; // Set semua status ke kosong
        }
    }

    // Fitur INSERT: Menyisipkan data mahasiswa dengan Double Hashing
    void insert(long long nim, string nama) {
        int index1 = hash1(nim);   // Hitung posisi awal dengan Hash1
        int step = hash2(nim);     // Hitung ukuran lompatan dengan Hash2
        int i = 0;                 // Penghitung percobaan probing (collision)

        while (i < TABLE_SIZE) {   // Coba maksimal sebanyak ukuran tabel
            int idx = (index1 + i * step) % TABLE_SIZE; // Rumus Double Hashing

            // Jika slot kosong atau bekas dihapus, data bisa dimasukkan
            if (table[idx].status == EMPTY || table[idx].status == DELETED) {
                table[idx].nim = nim;         // Simpan NIM sebagai key
                table[idx].nama = nama;       // Simpan Nama sebagai value
                table[idx].status = OCCUPIED; // Ubah status menjadi terisi
                if (i > 0) {                  // Jika i > 0 berarti sempat terjadi collision
                    cout << "[Collision Teratasi] NIM " << nim << " ditempatkan di indeks " << idx << " (setelah " << i << "x probing).\n";
                }
                return;                       // Keluar dari fungsi setelah berhasil insert
            }

            // Jika NIM sudah ada, perbarui namanya saja
            if (table[idx].status == OCCUPIED && table[idx].nim == nim) {
                table[idx].nama = nama;
                return;
            }
            i++; // Tambah hitungan collision dan lompat ke indeks berikutnya
        }
        cout << "Hash Table penuh! Gagal memasukkan NIM " << nim << endl; // Pesan jika tabel penuh
    }

    // Fitur SEARCH: Mencari data mahasiswa berdasarkan NIM
    void search(long long nim) {
        int index1 = hash1(nim);   // Hitung posisi awal
        int step = hash2(nim);     // Hitung langkah lompatan
        int i = 0;                 // Penghitung langkah pencarian

        while (i < TABLE_SIZE) {
            int idx = (index1 + i * step) % TABLE_SIZE; // Hitung indeks probing

            if (table[idx].status == EMPTY) { // Jika ketemu slot yang benar-benar EMPTY, data dipastikan tidak ada
                break;
            }
            if (table[idx].status == OCCUPIED && table[idx].nim == nim) { // Jika ketemu dan status aktif
                cout << "[Search Ditemukan] Indeks " << idx << " -> NIM: " << table[idx].nim << ", Nama: " << table[idx].nama << endl;
                return;
            }
            i++; // Lanjut memeriksa slot berikutnya jika status OCCUPIED (beda NIM) atau DELETED
        }
        cout << "[Search Gagal] NIM " << nim << " tidak ditemukan dalam tabel.\n";
    }

    // Fitur REMOVE: Menghapus data mahasiswa berdasarkan NIM
    void remove(long long nim) {
        int index1 = hash1(nim);   // Hitung posisi awal
        int step = hash2(nim);     // Hitung langkah lompatan
        int i = 0;                 // Penghitung langkah

        while (i < TABLE_SIZE) {
            int idx = (index1 + i * step) % TABLE_SIZE; // Hitung indeks probing

            if (table[idx].status == EMPTY) { // Berhenti jika menemui slot yang belum pernah dipakai
                break;
            }
            if (table[idx].status == OCCUPIED && table[idx].nim == nim) { // Jika data ditemukan
                table[idx].status = DELETED; // Tandai DELETED (jangan EMPTY agar rantai probing data lain tidak putus)
                cout << "[Remove Berhasil] Data NIM " << nim << " (" << table[idx].nama << ") dihapus dari indeks " << idx << ".\n";
                return;
            }
            i++; // Lanjut mencari di posisi probing berikutnya
        }
        cout << "[Remove Gagal] NIM " << nim << " tidak ditemukan.\n";
    }

    // Fitur DISPLAY: Menampilkan seluruh isi Hash Table dari indeks 0 sampai 19
    void display() {
        cout << "\n================ ISI HASH TABLE (SIZE 20) ================\n";
        for (int i = 0; i < TABLE_SIZE; i++) { // Loop seluruh indeks tabel
            cout << "Indeks [" << (i < 10 ? "0" : "") << i << "] : "; // Format nomor indeks 2 digit
            if (table[i].status == OCCUPIED) { // Jika terisi, cetak NIM dan Nama
                cout << "NIM: " << table[i].nim << " | Nama: " << table[i].nama << endl;
            } else if (table[i].status == DELETED) { // Jika bekas dihapus
                cout << "<DELETED>" << endl;
            } else { // Jika kosong
                cout << "<EMPTY>" << endl;
            }
        }
        
    }
};

int main() {
    HashTable ht; // Membuat objek Hash Table

    // Pengujian dengan 15 data mahasiswa (NIM dirancang agar beberapa memicu collision)
    cout << "=== MEMASUKKAN 15 DATA MAHASISWA ===\n";
    ht.insert(240101, "Ahmad Fauzi");     // 240101 % 20 = 1
    ht.insert(240121, "Budi Santoso");    // 240121 % 20 = 1 -> COLLISION dengan Ahmad! Ditangani Double Hashing
    ht.insert(240141, "Citra Lestari");   // 240141 % 20 = 1 -> COLLISION lagi!
    ht.insert(240102, "Dewi Sartika");    // 240102 % 20 = 2
    ht.insert(240103, "Eko Prasetyo");    // 240103 % 20 = 3
    ht.insert(240104, "Fitriani");        // 240104 % 20 = 4
    ht.insert(240105, "Gilang Ramadhan"); // 240105 % 20 = 5
    ht.insert(240125, "Hana Pertiwi");    // 240125 % 20 = 5 -> COLLISION dengan Gilang!
    ht.insert(240107, "Indra Lesmana");   // 240107 % 20 = 7
    ht.insert(240108, "Joko Widodo");     // 240108 % 20 = 8
    ht.insert(240110, "Kartika Putri");   // 240110 % 20 = 10
    ht.insert(240112, "Lukman Hakim");    // 240112 % 20 = 12
    ht.insert(240115, "Maya Anggraini");  // 240115 % 20 = 15
    ht.insert(240135, "Nanda Putra");     // 240135 % 20 = 15 -> COLLISION dengan Maya!
    ht.insert(240119, "Oki Setiana");     // 240119 % 20 = 19

    // Menampilkan tabel setelah 15 data dimasukkan
    ht.display();

    // Pengujian fitur Search 
    cout << "=== PENGUJIAN SEARCH ===\n";
    ht.search(240141); // Mencari Citra yang berpindah posisi akibat collision
    ht.search(999999); // Mencari NIM yang tidak ada

    // Pengujian fitur Remove 
    cout << "\n=== PENGUJIAN REMOVE ===\n";
    ht.remove(240121); // Menghapus Budi Santoso (posisi probing pertama dari indeks 1)

    // Memastikan data setelahnya (Citra - 240141) tetap bisa ditemukan meski Budi dihapus
    cout << "\n=== PENGUJIAN SEARCH SETELAH REMOVE ===\n";
    ht.search(240141);


    ht.display();

    return 0; 
}