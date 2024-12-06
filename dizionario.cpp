#include <iostream>

template <typename T>
class Dizionario {
private:
    static const int TABLE_SIZE = 100; // Dimensione fissa della tabella hash
    struct Entry {
        std::string key;
        T value;
        bool isOccupied = false;
    };

    Entry table[TABLE_SIZE];

    // Funzione hash di base
    int hashFunction(const std::string key) const {
        int hash = 0;
        for (char ch : key) {
            hash = (hash * 31 + ch) % TABLE_SIZE; // Algoritmo di hashing semplice
        }
        return hash;
    }

public:
    // Metodo per aggiungere una coppia chiave-valore
    void inserisci(const std::string key, const T value) {
        int index = hashFunction(key);  // Calcola l'indice iniziale

        // Gestione collisione con sondaggio lineare
        while (table[index].isOccupied) {
            if (table[index].key == key) {  // Se la chiave è già presente, aggiorna il valore
                table[index].value = value;
                return;
            }
            // Passa alla posizione successiva (gestione collisioni)
            index = (index + 1) % TABLE_SIZE;
        }

        // Memorizza la nuova coppia chiave-valore
        table[index].key = key;
        table[index].value = value;
        table[index].isOccupied = true;
    }

    // Metodo di rimozione
    void rimuovi(const std::string& key) {
        int index = hashFunction(key);  // Calcola l'indice per la chiave

        // Cerca la chiave nella tabella
        while (table[index].isOccupied) {
            if (table[index].key == key) {  // Se troviamo la chiave
                table[index].isOccupied = false;  // Marca la cella come "libera"
                break;  // Esci dalla funzione
            }
            index = (index + 1) % TABLE_SIZE;  // Passa alla posizione successiva
        }
    }

    // Metodo per ottenere il valore associato a una chiave
    T recupera(const std::string key) const {
        int index = hashFunction(key);

        // Cerca la chiave nella tabella
        while (table[index].isOccupied) {
            if (table[index].key == key) {
                return table[index].value;
            }
            index = (index + 1) % TABLE_SIZE;
        }

        return "Key not found!";  // Se la chiave non è trovata
    }

    // Verifica se una chiave è presente nel dizionario
    bool contiene(const std::string& key) {
        int index = hashFunction(key);  // Calcola l'indice per la chiave

        // Cerca la chiave nella tabella
        while (table[index].isOccupied) {
            if (table[index].key == key) {  // Se troviamo la chiave
                return true;  // La chiave è presente
            }
            index = (index + 1) % TABLE_SIZE;  // Passa alla posizione successiva
        }

        return false;  // La chiave non è presente
    }

    // Metodo per stampare il contenuto del dizionario
    void stampa() const {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            if (table[i].isOccupied) {
                std::cout << "Index " << i << ": " << table[i].key << " => " << table[i].value << "\n";
            }
        }
    }
};


