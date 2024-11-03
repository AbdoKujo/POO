#include <iostream>
#include <cmath>
using namespace std;

class Vecteur3d {
private:
    float x, y, z;

public:
    Vecteur3d(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) {}
    void afficher() const {
        cout << "(" << x << ", " << y << ", " << z << ")" << endl;
    }
    Vecteur3d somme(const Vecteur3d& other) const {
        return Vecteur3d(x + other.x, y + other.y, z + other.z);
    }
    float produitScalaire(const Vecteur3d& other) const {
        return x * other.x + y * other.y + z * other.z;
    }
    bool coincide(const Vecteur3d& other) const {
        return (x == other.x && y == other.y && z == other.z);
    }
    float norme() const {
        return sqrt(x * x + y * y + z * z);
    }
    Vecteur3d normaxParValeur(const Vecteur3d& other) const {
        return (this->norme() > other.norme()) ? *this : other;
    }
    const Vecteur3d* normaxParAdresse(const Vecteur3d* other) const {
        return (this->norme() > other->norme()) ? this : other;
    }
    const Vecteur3d& normaxParReference(const Vecteur3d& other) const {
        return (this->norme() > other.norme()) ? *this : other;
    }
};
int main() {
    Vecteur3d v1(1, 2, 3);
    Vecteur3d v2(4, 5, 6);
    cout << "V1 : ";
    v1.afficher();
    cout << "V2 : ";
    v2.afficher();
    Vecteur3d v3 = v1.somme(v2);
    cout << "Somme de V1 et V2 : ";
    v3.afficher();
    float produit = v1.produitScalaire(v2);
    cout << "Produit scalaire de V1 et V2 : " << produit << endl;
    bool coincident = v1.coincide(v2);
    cout << "V1 et V2 sont-ils identiques ? " << (coincident ? "Oui" : "Non") << endl;
    cout << "Norme de V1 : " << v1.norme() << endl;
    cout << "Norme de V2 : " << v2.norme() << endl;
    Vecteur3d maxValeur = v1.normaxParValeur(v2);
    cout << "Vecteur avec la plus grande norme (par valeur) : ";
    maxValeur.afficher();
    const Vecteur3d* maxAdresse = v1.normaxParAdresse(&v2);
    cout << "Vecteur avec la plus grande norme (par adresse) : ";
    maxAdresse->afficher();
    const Vecteur3d& maxReference = v1.normaxParReference(v2);
    cout << "Vecteur avec la plus grande norme (par référence) : ";
    maxReference.afficher();
    return 0;
}

