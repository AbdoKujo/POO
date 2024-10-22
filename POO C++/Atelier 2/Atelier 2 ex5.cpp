#include <iostream>

using namespace std;

int main() {
    // 1. Déclare un entier a
    int a = 42;

    // 2. Déclare une référence vers cet entier ref_a
    int& ref_a = a;

    // 3. Déclare un pointeur vers cet entier p_a
    int* p_a = &a;

    // 4. Affiche les variables, leurs adresses et la valeur pointée
    cout << "Valeur de a: " << a << endl;
    cout << "Adresse de a: " << &a << endl;

    cout << "\nValeur de ref_a (reference à a): " << ref_a << endl;
    cout << "Adresse de ref_a: " << &ref_a << endl;

    cout << "\nValeur du pointeur p_a (adresse de a): " << p_a << endl;
    cout << "Valeur pointee par p_a (valeur de a): " << *p_a << endl;
    cout << "Adresse du pointeur p_a: " << &p_a << endl;

    return 0;
}
