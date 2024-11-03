#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Traitement {
private:
    vector<int> entiers;

public:
    void Initialise() {
        int nombre;
        while (entiers.size() < 15) {
            cout << "Entrez un entier pair (non nul) : ";
            cin >> nombre;
            if (cin.fail() || nombre == 0 || nombre % 2 != 0) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Erreur : veuillez entrer un entier pair et non nul." << endl;
            } else {
                entiers.push_back(nombre);
            }
        }
    }

    void show() const {
        showRecursif(0);
        cout << endl;
    }

private:
    void showRecursif(size_t index) const {
        if (index < entiers.size()) {
            cout << entiers[index] << " ";
            showRecursif(index + 1);
        }
    }

    friend double moyenne(const Traitement& t);
    friend double median(const Traitement& t);
};

double moyenne(const Traitement& t) {
    if (t.entiers.empty()) return 0.0;
    double somme = 0;
    for (int val : t.entiers) {
        somme += val;
    }
    return somme / t.entiers.size();
}

double median(const Traitement& t) {
    if (t.entiers.empty()) return 0.0;
    vector<int> copie = t.entiers;
    sort(copie.begin(), copie.end());
    size_t n = copie.size();
    if (n % 2 == 0) {
        return (copie[n / 2 - 1] + copie[n / 2]) / 2.0;
    } else {
        return copie[n / 2];
    }
}

int main() {
    Traitement t;
    t.Initialise();
    cout << "Les elements du vecteur sont : ";
    t.show();
    cout << "Moyenne : " << moyenne(t) << endl;
    cout << "Mediane : " << median(t) << endl;

    return 0;
}


