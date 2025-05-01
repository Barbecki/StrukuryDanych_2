#include <iostream>
#include <chrono>
#include <random>
#include <fstream>
#include "heap/heap.h"
#include "LinkedList/LinkedList.h"
#include "heap2/heap2.h"

using namespace std;

// Funkcja wypełniająca kolejkę priorytetową 
template <typename T>
void fillValues(T &structure, int size, int seed, vector<int> &insertedValues) {
    mt19937 gen(seed);
    uniform_int_distribution<int> distVal(0, 1000000);
    uniform_int_distribution<int> distPri(0, 4 * size);

    for (int i = 0; i < size; i++) {
        int x = distVal(gen); // Losowa wartość
        structure.insert(x, distPri(gen)); // Wstawiamy wartość i priorytet
        // Dodajemy wartość do wektora
        if (insertedValues.size() < size) {
            insertedValues.push_back(x); 
        }
  
    }
}

// funkcja do pomiaru czasu
template <typename F>
long long timer(F fun) {
    auto start = chrono::high_resolution_clock::now();
    fun();
    auto end = chrono::high_resolution_clock::now();
    return chrono::duration_cast<chrono::nanoseconds>(end - start).count();
}

// Funkcja mierząca wydajność operacji
template <typename T>
void performMeasurementsPQ(int size, int quantity, mt19937 &gen, const string &filename) {
    uniform_int_distribution<int> distVal(0, 1000000);
    uniform_int_distribution<int> distPri(0, 4 * size);

    long long insertTotal = 0;
    long long extractTotal = 0;
    long long findMaxTotal = 0;
    long long modifyKeyTotal = 0;
    long long sizeTotal = 0;

    for (int i = 0; i < quantity; i++) {
        // Tworzymy oddzielne struktury dla każdej operacji, by zaczynały z jednakowym stanem
        T structureInsert, structureExtract, structureFind, structureModify, structureSize;
        vector<int> insertedValues;
        // Wypełniamy je danymi (wartości + priorytety)
        fillValues(structureInsert, size, size + i,insertedValues);
        fillValues(structureExtract, size, size + i,insertedValues);
        fillValues(structureFind, size, size + i,insertedValues);
        fillValues(structureModify, size, size + i,insertedValues);
        fillValues(structureSize, size, size + i,insertedValues);

        // insert 
        insertTotal += timer([&]() {
            structureInsert.insert(1234, 4321);
        });

        // extract_max
        extractTotal += timer([&]() {
            structureExtract.extract_max(); 
        });

        // find_max
        findMaxTotal += timer([&]() {
            structureFind.find_max();
        });


        // modifyKey

        int randomValue = insertedValues[1234];
        int newPriority = 3212;
        modifyKeyTotal += timer([&]() {
            structureModify.modify_key(randomValue, newPriority); 
        });

        // return_size
        sizeTotal += timer([&]() {
            structureSize.return_size();
        });
    }

    // Zapisujemy średnie czasy do pliku
    ofstream plik(filename, ios::app);
    if (plik.is_open()) {
        plik << "Rozmiar: " << size << "\n";
        plik << "Średni Insert:      " << (insertTotal / quantity) << " ns\n";
        plik << "Średni ExtractMax:  " << (extractTotal / quantity) << " ns\n";
        plik << "Średni FindMax:     " << (findMaxTotal / quantity) << " ns\n";
        plik << "Średni ModifyKey:   " << (modifyKeyTotal / quantity) << " ns\n";
        plik << "Średni ReturnSize:  " << (sizeTotal / quantity) << " ns\n";
        plik << "----------------------------------------\n";
        plik.close();
    }
}

int main() {
    // Przykładowe rozmiary
    int sizes[] = { 20000, 40000, 60000, 80000, 100000, 120000, 140000, 160000 };
    int quantity = 100;

    mt19937 gen(777);

    while (true) {
        cout << "Wybierz implementacje kolejki priorytetowej do zbadania:\n";
        cout << "1. Kolejka priorytetowa (lista wiazana)\n";
        cout << "2. Kolejka priorytetowa (Heap z mapa)\n";
        cout << "3. Kolejka priorytetowa (Heap bez mapy)\n";
        cout << "4. Wyjscie\n";
        cout << "Wybor: ";
        char choice;
        cin >> choice;

        switch (choice) {
        case '1': {
            cout << "Badanie kolejki priorytetowej (Lista wiazana)\n";
            ofstream plik("pomiary_czas_PQ_LinkedList.txt");
            if (plik.is_open()) {
                plik << "Pomiar czasu (LinkedList) - PQ:\n";
                plik.close();
            }

            for (int size : sizes) {
                cout << "Rozmiar: " << size << endl;
                //performMeasurementsPQ<LinkedList>(size, quantity, gen, "pomiary_czas_PQ_LinkedList.txt");
            }
            break;
        }
        case '2': {
            cout << "Badanie kolejki priorytetowej (Heap z mapa).\n";
            ofstream plik("pomiary_czas_PQ_Heap.txt");
            if (plik.is_open()) {
                plik << "Pomiar czasu (Heap) - PQ:\n";
                plik.close();
            }

            for (int size : sizes) {
                cout << "Rozmiar: " << size << endl;
                performMeasurementsPQ<heapPQ>(size, quantity, gen, "pomiary_czas_Opti_PQ_Heap.txt");
            }
            break;
        }
        case '3': {
            cout << "Badanie kolejki priorytetowej (Heap bez mapy).\n";
            ofstream plik("pomiary_czas_PQ_Heap.txt");
            if (plik.is_open()) {
                plik << "Pomiar czasu (Heap) - PQ:\n";
                plik.close();
            }

            for (int size : sizes) {
                cout << "Rozmiar: " << size << endl;
                performMeasurementsPQ<heapOPQ>(size, quantity, gen, "pomiary_czas_PQ_Heap.txt");
            }
            break;
        }
        case '4':
            cout << "Wyjscie z programu.\n";
            return 0;
        default:
            cout << "Nie ma takiej opcji.\n";
        }
    }
    return 0;
}

