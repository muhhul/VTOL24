### Usage

* `roslaunch uav_commander sitlgazebo-2.launch pilot_filename:=LALALA.txt`
* Pastikan file pilot sudah sesuai format (**Warning**: file checker belum di-implement. File pilot yang tidak sesuai format leads to undefined behaviour)
* NB. Kalau tambah fungsi baru di `uav_missions.cpp`, jangan lupa tambahin ke uav_funcs di constructor `pilot.cpp`

### Pilot file format
Ini ada supaya tidak perlu compile terus-terusan kalau hanya ganti misi

* Format .txt
* Tidak sensitif terhadap baris kosong. Sensitif terhadap karakter apapun di baris yang tidak kosong (walaupun hanya spasi!)
* Sekali lagi, sensitif terhadap spasi. Tidak boleh ada leading spaces atau trailing spaces di baris.
* Baris komentar diawali //
* Case sensitive. Semua dalam camelCase.
* Contoh 1: `someFunction; m;`
* Contoh 2: `someFunction; m 2 doubles 3.0 1.5;`
* Contoh 3: `someFunction; m 1 strings LALALA; m 3 ints 10 5 1;`
* Untuk contoh 3 walaupun valid, di `uav_missions` belum ada fungsi yang memakai lebih dari satu type.
* Misalkan `n` adalah banyak argumen, kayak di contoh 2 itu `n==2`. Barangkali perlu diingat, dalam sebuah tipe (misal `doubles`), nilai `n` diimplementasi dari `uint8_t`.

TEST COMMIT

Test cOmmit 2

test comit 3

tes cCOMOPIT

aw
