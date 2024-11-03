#include <iostream>
#include <cstring>

using namespace std;

class Fichier {
private:
    char* P;
    size_t length;
public:
    Fichier() : P(nullptr), length(0) {}
    ~Fichier() {
        delete[] P;
    }
    void Creation(size_t len) {
        length = len;
        P = new char[length];
    }
    void Remplit() {
        if (P) {
            memset(P, 'A', length);
        } else {
            cerr << "Erreur : espace non alloué." << endl;
        }
    }
    void Affiche() const {
        if (P) {
            cout.write(P, length);
            cout << endl;
        } else {
            cerr << "Erreur : espace non alloué." << endl;
        }
    }
};

int main() {
    Fichier* fichier = new Fichier();
    fichier->Creation(10);
    fichier->Remplit();
}
