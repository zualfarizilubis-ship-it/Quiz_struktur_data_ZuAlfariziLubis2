#include <iostream> 
#include <queue>   
#include <vector>   
#include <climits> 

using namespace std; 

const int V = 6; 

// Fungsi bantuan mengubah karakter vertex (A-F) menjadi indeks array (0-5)
int charToIndex(char c) {
    return toupper(c) - 'A'; // Mengubah huruf kecil/besar menjadi indeks 0 sampai 5
}

// Fungsi bantuan mengubah indeks array (0-5) kembali menjadi karakter (A-F)
char indexToChar(int idx) {
    return 'A' + idx;        // Mengembalikan huruf A sampai F
}

// Fungsi penelusuran graf menggunakan BFS (Breadth-First Search)
void BFS(int graph[V][V], int start) {
    bool visited[V] = {false}; // Array penanda vertex yang sudah dikunjungi
    queue<int> q;              // Antrean untuk menyimpan vertex yang akan dikunjungi

    visited[start] = true;     // Tandai vertex awal sudah dikunjungi
    q.push(start);             // Masukkan vertex awal ke antrean

    cout << "Hasil Penelusuran BFS: ";
    while (!q.empty()) {       // Ulangi selama antrean tidak kosong
        int curr = q.front();  // Ambil vertex paling depan dari antrean
        q.pop();               // Keluarkan dari antrean
        cout << indexToChar(curr) << " "; // Cetak nama vertex

        for (int i = 0; i < V; i++) { // Cek semua tetangga dari vertex saat ini
            // Jika ada jalur (bobot > 0) dan tetangga belum dikunjungi
            if (graph[curr][i] > 0 && !visited[i]) {
                visited[i] = true; // Tandai tetangga sudah dikunjungi
                q.push(i);         // Masukkan tetangga ke antrean
            }
        }
    }
    cout << endl;
}

// Fungsi rekursif bantu untuk DFS
void DFSUtil(int graph[V][V], int curr, bool visited[V]) {
    visited[curr] = true;      // Tandai vertex saat ini sudah dikunjungi
    cout << indexToChar(curr) << " "; // Cetak nama vertex

    for (int i = 0; i < V; i++) { // Periksa semua kemungkinan tetangga
        if (graph[curr][i] > 0 && !visited[i]) { // Jika terhubung dan belum dikunjungi
            DFSUtil(graph, i, visited); // Lakukan penelusuran mendalam secara rekursif
        }
    }
}

// Fungsi utama penelusuran graf menggunakan DFS (Depth-First Search)
void DFS(int graph[V][V], int start) {
    bool visited[V] = {false}; // Array penanda kunjungan
    cout << "Hasil Penelusuran DFS: ";
    DFSUtil(graph, start, visited); // Panggil fungsi rekursif DFS
    cout << endl;
}

// Fungsi mencari rute terpendek menggunakan Algoritma Dijkstra
void dijkstra(int graph[V][V], int start, int end) {
    int dist[V];               // Menyimpan jarak terpendek dari start ke setiap vertex
    bool visited[V];           // Menandai vertex yang jarak terpendeknya sudah final
    int parent[V];             // Menyimpan vertex sebelumnya untuk melacak rute perjalanan

    for (int i = 0; i < V; i++) { // Inisialisasi awal
        dist[i] = INT_MAX;     // Set semua jarak awal menjadi tak hingga
        visited[i] = false;    // Belum ada vertex yang diproses
        parent[i] = -1;        // Belum ada parent (jalur)
    }

    dist[start] = 0;           // Jarak dari vertex awal ke dirinya sendiri adalah 0

    for (int count = 0; count < V - 1; count++) { // Proses semua vertex
        int minDist = INT_MAX, u = -1; // Cari vertex dengan jarak terkecil yang belum dikunjungi

        for (int v = 0; v < V; v++) {
            if (!visited[v] && dist[v] <= minDist) {
                minDist = dist[v]; // Perbarui jarak minimum
                u = v;             // Simpan indeks vertex terpilih
            }
        }

        if (u == -1) break;    // Hentikan jika tidak ada vertex yang bisa dijangkau lagi
        visited[u] = true;     // Tandai vertex u sudah selesai diproses

        // Perbarui nilai jarak ke semua tetangga dari vertex u (Relaxation)
        for (int v = 0; v < V; v++) {
            if (!visited[v] && graph[u][v] > 0 && dist[u] != INT_MAX &&
                dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v]; // Simpan jarak baru yang lebih pendek
                parent[v] = u;                   // Catat bahwa vertex v dicapai melalui u
            }
        }
    }

    // Menampilkan hasil rute dan total jarak
    cout << "\n--- Hasil Pencarian Rute Terpendek (Dijkstra) ---\n";
    if (dist[end] == INT_MAX) { // Jika vertex tujuan tidak dapat dijangkau
        cout << "Tidak ada rute dari " << indexToChar(start) << " ke " << indexToChar(end) << ".\n";
        return;
    }

    // Rekonstruksi rute dari tujuan mundur ke awal menggunakan array parent
    vector<char> rute;
    for (int v = end; v != -1; v = parent[v]) {
        rute.push_back(indexToChar(v)); // Masukkan vertex ke vector rute
    }

    cout << "Rute yang dilalui : ";
    for (int i = rute.size() - 1; i >= 0; i--) { // Cetak terbalik (dari awal ke tujuan)
        cout << rute[i];
        if (i > 0) cout << " -> "; // Beri tanda panah antar lokasi
    }
    cout << "\nTotal Jarak       : " << dist[end] << endl; // Cetak total bobot jarak
}

int main() {
    // Inisialisasi Adjacency Matrix 6x6 bernilai 0
    int graph[V][V] = {0};

    // Fungsi lambda untuk menambahkan sisi dua arah (undirected graph) beserta bobotnya
    auto tambahSisi = [&](char u, char v, int bobot) {
        int i = charToIndex(u); // Konversi huruf pertama ke indeks
        int j = charToIndex(v); // Konversi huruf kedua ke indeks
        graph[i][j] = bobot;    // Set bobot dari u ke v
        graph[j][i] = bobot;    // Set bobot dari v ke u
    };

    // Memasukkan data sisi dan bobot sesuai tabel pada soal
    tambahSisi('A', 'B', 4); // A - B = 4
    tambahSisi('A', 'C', 2); // A - C = 2
    tambahSisi('B', 'C', 1); // B - C = 1
    tambahSisi('B', 'D', 5); // B - D = 5
    tambahSisi('B', 'E', 3); // B - E = 3
    tambahSisi('C', 'D', 8); // C - D = 8
    tambahSisi('C', 'E', 6); // C - E = 6
    tambahSisi('D', 'E', 2); // D - E = 2
    tambahSisi('D', 'F', 4); // D - F = 4
    tambahSisi('E', 'F', 3); // E - F = 3

    char awal, tujuan; // Variabel menampung pilihan input pengguna[span_56](start_span)[span_56](end_span)
    cout << "Daftar Lokasi Kampus: A, B, C, D, E, F\n";
    cout << "Masukkan Vertex Awal   : "; cin >> awal;   // Input titik awal[span_57](start_span)[span_57](end_span)
    cout << "Masukkan Vertex Tujuan : "; cin >> tujuan; // Input titik tujuan[span_58](start_span)[span_58](end_span)

    int idxAwal = charToIndex(awal);     // Konversi vertex awal ke indeks
    int idxTujuan = charToIndex(tujuan); // Konversi vertex tujuan ke indeks

    // Validasi input agar tidak keluar dari rentang A-F
    if (idxAwal < 0 || idxAwal >= V || idxTujuan < 0 || idxTujuan >= V) {
        cout << "Input vertex tidak valid! Gunakan huruf A sampai F.\n";
        return 1;
    }

    cout << endl;
    BFS(graph, idxAwal);                
    DFS(graph, idxAwal);                 
    dijkstra(graph, idxAwal, idxTujuan); 

    return 0; 
}