#include <iostream>

using namespace std;

struct Element {
    int valeur;
    Element* suivant;
};

class Liste {
private:
    Element* premier;

public:
    Liste() : premier(nullptr) {}

    ~Liste() {
        while (premier) {
            supprimer();
        }
    }

    void ajouter(int val) {
        Element* nouvelElement = new Element;
        nouvelElement->valeur = val;
        nouvelElement->suivant = premier;
        premier = nouvelElement;
    }

    void supprimer() {
        if (premier) {
            Element* temp = premier;
            premier = premier->suivant;
            delete temp;
        }
    }

    void afficher() const {
        Element* courant = premier;
        while (courant) {
            cout << courant->valeur << " ";
            courant = courant->suivant;
        }
        cout << endl;
    }
};

int main() {
    Liste liste;
    liste.ajouter(10);
    liste.ajouter(20);
    liste.ajouter(30);

    cout << "Liste actuelle : ";
    liste.afficher();

    liste.supprimer();
    cout << "Apres suppression : ";
    liste.afficher();

    return 0;
}

