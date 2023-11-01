#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 100 // Hash tablosunun boyutu

struct Data {
    int key;
    char value[100];
};

// Hash tablosunun elemanlar�n� temsil etmek i�in bir yap�
struct HashTableEntry {
    struct Data data;
    int isOccupied; //Tablo doluysa 1 bo�sa 0 d�nd�r�r
    int isDeleted;  // �nceden bir veri silinip bo�sa 1 d�nd�r�r
};

// Hash tablosu
struct HashTableEntry table[TABLE_SIZE];

// Hash fonksiyonu: Veriyi hash tablosuna eklemek i�in kullan�l�r
int hashFunction(int key) {
    return key % TABLE_SIZE;
}

// Veriyi hash tablosuna ekler
void insert(int key, const char *value) {
    struct Data newData;
    newData.key = key;
    strcpy(newData.value, value);

    int index = hashFunction(key);

    // A��k adresleme ile bo� bir yere veriyi eklemeye �al��
    while (table[index].isOccupied) {
        if (table[index].data.key == key) {
            // Ayn� anahtara sahip bir veri zaten var, g�ncelle
            strcpy(table[index].data.value, value);
            return;
        }

        // Lineer sondan ba�a arama (linear probing)
        index = (index + 1) % TABLE_SIZE;
    }

    table[index].data = newData;
    table[index].isOccupied = 1;
    table[index].isDeleted = 0;
}

// Veriyi hash tablosundan siler
void remove(int key) {
    int index = hashFunction(key);

    while (table[index].isOccupied) {
        if (table[index].data.key == key) {
            // Veriyi bulduk, i�aretle ve silme
            table[index].isOccupied = 0;
            table[index].isDeleted = 1;
            return;
        }

        // Lineer sondan ba�a arama (linear probing)
        index = (index + 1) % TABLE_SIZE;
    }
}

// Veriyi anahtar�na g�re arar ve bulursa de�erini d�nd�r�r
const char *search(int key) {
    int index = hashFunction(key);

    while (table[index].isOccupied) {
        if (table[index].data.key == key && !table[index].isDeleted) {
            return table[index].data.value;
        }

        // Lineer sondan ba�a arama (linear probing)
        index = (index + 1) % TABLE_SIZE;
    }

    return NULL; // Veri bulunamad�
}

int main() {
    // Verileri hash tablosuna eklemek
    insert(1, "Cakisma ornegi");
    insert(1, "Azra");
    insert(2, "Oyku");
    insert(3, "Ulukan");
    
    // Keylere g�re ar�yoruz
    printf("Key 1: %s\n", search(1));
    printf("Key 2: %s\n", search(2));
    printf("Key 3: %s\n", search(3));
    printf("Key 4: %s\n", search(4));
    
   
    
    // Veriyi silmek
    remove(2);

    // Silindikten sonra tekrar arama
    printf("Key 2: %s\n", search(2)); // NULL ��kt�s� bekleniyor (veri silindi)

    return 0;
}

