#include <iostream> 
#include <string>   

using namespace std; 

//1. QUEUE (FIFO - Antrean Peminjaman) 
struct NodeQueue {
    string namaPeminjam; // Menyimpan nama mahasiswa yang mengantre
    NodeQueue* next;     // Pointer ke antrean berikutnya
};

class QueueAntrean {
private:
    NodeQueue *front, *rear; // Pointer depan (keluar) dan belakang (masuk)
public:
    QueueAntrean() { front = rear = nullptr; } // Konstruktor: inisialisasi antrean kosong

    // Enqueue: Menambah mahasiswa ke belakang antrean
    void enqueue(string nama) {
        NodeQueue* baru = new NodeQueue{nama, nullptr}; // Buat node baru
        if (rear == nullptr) {         // Jika antrean kosong
            front = rear = baru;       // Front dan rear menunjuk ke node baru
            return;
        }
        rear->next = baru;             // Sambungkan node paling belakang ke node baru
        rear = baru;                   // Pindahkan posisi rear ke node baru
    }

    // Dequeue: Melayani mahasiswa paling depan (First In, First Out)[span_18](start_span)[span_18](end_span)
    void dequeue() {
        if (front == nullptr) {        // Cek jika antrean kosong
            cout << "Antrean kosong!\n";
            return;
        }
        NodeQueue* temp = front;       // Simpan node terdepan sementara
        cout << "Melayani peminjaman buku untuk: " << front->namaPeminjam << endl; // Info layanan
        front = front->next;           // Geser front ke orang berikutnya
        if (front == nullptr) rear = nullptr; // Jika antrean jadi kosong, reset rear
        delete temp;                   // Hapus memori node yang sudah dilayani
    }

    // Menampilkan seluruh antrean saat ini[span_19](start_span)[span_19](end_span)
    void display() {
        cout << "Antrean Peminjaman (FIFO): ";
        NodeQueue* temp = front;       // Mulai dari depan
        if (!temp) cout << "[Kosong]"; // Info jika kosong
        while (temp != nullptr) {      // Loop hingga belakang
            cout << temp->namaPeminjam << " -> "; // Cetak nama
            temp = temp->next;         // Geser ke berikutnya
        }
        cout << "NULL\n";
    }
};

// 2. STACK (LIFO - Riwayat Pengembalian)
struct NodeStack {
    int idBuku;      // Menyimpan ID buku yang dikembalikan
    NodeStack* next; // Pointer ke tumpukan di bawahnya
};

class StackRiwayat {
private:
    NodeStack* top;  // Pointer ke elemen paling atas tumpukan
public:
    StackRiwayat() { top = nullptr; } // Konstruktor: tumpukan kosong

    // Push: Mencatat buku yang baru dikembalikan ke posisi paling atas
    void push(int id) {
        NodeStack* baru = new NodeStack{id, top}; // Buat node baru yang menunjuk ke top lama
        top = baru;                    // Jadikan node baru sebagai top
        cout << "Buku ID " << id << " masuk ke riwayat pengembalian.\n";
    }

    // Pop: Mengambil/memproses buku terakhir yang dikembalikan (Last In, First Out)[span_21](start_span)[span_21](end_span)
    void pop() {
        if (top == nullptr) {          // Cek jika stack kosong
            cout << "Riwayat pengembalian kosong!\n";
            return;
        }
        NodeStack* temp = top;         // Simpan top sementara
        cout << "Memproses ulang buku terakhir dikembalikan (ID: " << top->idBuku << ")\n";
        top = top->next;               // Turunkan top ke elemen di bawahnya
        delete temp;                   // Hapus memori node teratas
    }

    // Menampilkan isi Stack dari atas ke bawah[span_22](start_span)[span_22](end_span)
    void display() {
        cout << "Riwayat Pengembalian (LIFO / Top ke Bottom): ";
        NodeStack* temp = top;         // Mulai dari atas
        if (!temp) cout << "[Kosong]";
        while (temp != nullptr) {      // Telusuri ke bawah
            cout << "[" << temp->idBuku << "] "; // Cetak ID buku
            temp = temp->next;         // Geser ke bawah
        }
        cout << endl;
    }
};

// ==================== 3. BINARY SEARCH TREE (Penyimpanan ID Buku) ====================[span_23](start_span)[span_23](end_span)
struct NodeBST {
    int idBuku;            // Kunci utama (ID Buku)
    NodeBST *left, *right; // Pointer anak kiri (lebih kecil) dan anak kanan (lebih besar)
};

// Fungsi membuat node BST baru
NodeBST* buatNodeBST(int id) {
    return new NodeBST{id, nullptr, nullptr}; // Alokasi dan kembalikan node baru
}

// Fungsi menyisipkan ID buku ke dalam BST[span_24](start_span)[span_24](end_span)
NodeBST* insertBST(NodeBST* root, int id) {
    if (root == nullptr) return buatNodeBST(id); // Jika posisi kosong, buat node di sini
    if (id < root->idBuku) {           // Jika ID lebih kecil dari root saat ini
        root->left = insertBST(root->left, id);   // Rekursif ke cabang kiri
    } else if (id > root->idBuku) {    // Jika ID lebih besar dari root saat ini
        root->right = insertBST(root->right, id); // Rekursif ke cabang kanan
    }
    return root;                       // Kembalikan pointer root
}

// Fungsi mencari ID buku di dalam BST[span_25](start_span)[span_25](end_span)
bool searchBST(NodeBST* root, int id) {
    if (root == nullptr) return false; // Basis: sampai ujung daun dan tidak ketemu
    if (root->idBuku == id) return true; // Ketemu!
    if (id < root->idBuku) return searchBST(root->left, id); // Cari di kiri jika lebih kecil
    return searchBST(root->right, id); // Cari di kanan jika lebih besar
}

// Traversal Pre-Order (Root -> Left -> Right)[span_26](start_span)[span_26](end_span)
void preOrder(NodeBST* root) {
    if (root != nullptr) {
        cout << root->idBuku << " ";   // Cetak Root dulu
        preOrder(root->left);          // Kunjungi cabang kiri
        preOrder(root->right);         // Kunjungi cabang kanan
    }
}

// Traversal In-Order (Left -> Root -> Right) - Menghasilkan urutan terurut[span_27](start_span)[span_27](end_span)
void inOrder(NodeBST* root) {
    if (root != nullptr) {
        inOrder(root->left);           // Kunjungi cabang kiri dulu
        cout << root->idBuku << " ";   // Cetak Root
        inOrder(root->right);          // Kunjungi cabang kanan
    }
}

// Traversal Post-Order (Left -> Right -> Root)[span_28](start_span)[span_28](end_span)
void postOrder(NodeBST* root) {
    if (root != nullptr) {
        postOrder(root->left);         // Kunjungi cabang kiri dulu
        postOrder(root->right);        // Kunjungi cabang kanan
        cout << root->idBuku << " ";   // Cetak Root terakhir
    }
}

int main() {
    QueueAntrean antrean;              // Instansiasi objek Queue
    StackRiwayat riwayat;              // Instansiasi objek Stack
    NodeBST* rootBuku = nullptr;       // Inisialisasi BST kosong

    // 1. Simulasi Queue (Antrean Peminjaman)[span_29](start_span)[span_29](end_span)
    cout << "=== SIMULASI ANTREAN (QUEUE) ===\n";
    antrean.enqueue("Andi");           // Andi masuk antrean pertama
    antrean.enqueue("Budi");           // Budi masuk antrean kedua
    antrean.enqueue("Citra");          // Citra masuk antrean ketiga
    antrean.display();                 // Tampilkan antrean
    antrean.dequeue();                 // Layani Andi (pertama masuk, pertama keluar)
    antrean.display();                 // Tampilkan sisa antrean

    // 2. Simulasi Stack (Riwayat Pengembalian)[span_30](start_span)[span_30](end_span)
    cout << "\n=== SIMULASI RIWAYAT PENGEMBALIAN (STACK) ===\n";
    riwayat.push(105);                 // Buku 105 dikembalikan
    riwayat.push(102);                 // Buku 102 dikembalikan
    riwayat.push(110);                 // Buku 110 dikembalikan terakhir
    riwayat.display();                 // Tampilkan tumpukan riwayat
    riwayat.pop();                   // Proses buku 110 (terakhir masuk, pertama keluar)
    riwayat.display();                 // Tampilkan sisa riwayat

    // 3. Simulasi Binary Search Tree (ID Buku)[span_31](start_span)[span_31](end_span)
    cout << "\n=== SIMULASI DATA BUKU (BST) ===\n";
    int daftarID[] = {105, 102, 110, 101, 104, 108}; // Data contoh ID buku
    for (int id : daftarID) {          // Loop memasukkan semua ID ke BST
        rootBuku = insertBST(rootBuku, id);
    }

    cout << "Pre-Order  : "; preOrder(rootBuku); cout << endl;  
    cout << "In-Order   : "; inOrder(rootBuku); cout << endl;   
    cout << "Post-Order : "; postOrder(rootBuku); cout << endl; 

    int cariID = 104;                  // ID yang akan dicari
    cout << "Mencari Buku ID " << cariID << ": " 
         << (searchBST(rootBuku, cariID) ? "Ditemukan!" : "Tidak Ditemukan!") << endl; 

    return 0;                          
}