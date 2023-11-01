#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 100 // Hash tablosunun boyutu

struct Data {
    int key;
    char value[100];
};

// Hash tablosunun elemanlarýný temsil etmek için bir yapý
struct HashTableEntry {
    struct Data data;
    int isOccupied; //Tablo doluysa 1 boþsa 0 döndürür
    int isDeleted;  // Önceden bir veri silinip boþsa 1 döndürür
};

// Hash tablosu
struct HashTableEntry table[TABLE_SIZE];

// Hash fonksiyonu: Veriyi hash tablosuna eklemek için kullanýlýr
int hashFunction(int key) {
    return key % TABLE_SIZE;
}

// Veriyi hash tablosuna ekler
void insert(int key, const char *value) {
    struct Data newData;
    newData.key = key;
    strcpy(newData.value, value);

    int index = hashFunction(key);

    // Açýk adresleme ile boþ bir yere veriyi eklemeye çalýþ
    while (table[index].isOccupied) {
        if (table[index].data.key == key) {
            // Ayný anahtara sahip bir veri zaten var, güncelle
            strcpy(table[index].data.value, value);
            return;
        }

        // Lineer sondan baþa arama (linear probing)
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
            // Veriyi bulduk, iþaretle ve silme
            table[index].isOccupied = 0;
            table[index].isDeleted = 1;
            return;
        }

        // Lineer sondan baþa arama (linear probing)
        index = (index + 1) % TABLE_SIZE;
    }
}

// Veriyi anahtarýna göre arar ve bulursa deðerini döndürür
const char *search(int key) {
    int index = hashFunction(key);

    while (table[index].isOccupied) {
        if (table[index].data.key == key && !table[index].isDeleted) {
            return table[index].data.value;
        }

        // Lineer sondan baþa arama (linear probing)
        index = (index + 1) % TABLE_SIZE;
    }

    return NULL; // Veri bulunamadý
}

int main() {
    // Verileri hash tablosuna eklemek
    insert(1, "Cakisma ornegi");
    insert(1, "Azra");
    insert(2, "Oyku");
    insert(3, "Ulukan");
    
    // Keylere göre arýyoruz
    printf("Key 1: %s\n", search(1));
    printf("Key 2: %s\n", search(2));
    printf("Key 3: %s\n", search(3));
    printf("Key 4: %s\n", search(4));
    
   
    
    // Veriyi silmek
    remove(2);

    // Silindikten sonra tekrar arama
    printf("Key 2: %s\n", search(2)); // NULL çýktýsý bekleniyor (veri silindi)

    return 0;
}

