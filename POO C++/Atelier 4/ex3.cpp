#include <iostream>
#include <string>
using namespace std;

class Personne {
protected:
    string nom;
    string prenom;
    string date;

public:
    Personne(string n, string p, string d) : nom(n), prenom(p), date(d) {}

    virtual void afficher() const {
        cout << "Le nom est : " << nom << endl;
        cout << "Le prenom est : " << prenom << endl;
        cout << "La date de naissance est : " << date << endl;
    }
};

class Employe : public Personne {
protected:
    float salaire;

public:
    Employe(string n, string p, string d, float s) : Personne(n, p, d), salaire(s) {}

    void afficher() const  {
        Personne::afficher();
        cout << "Le salaire est : " << salaire << endl;
    }
};

class Chef : public Employe {
protected:
    string service;

public:
    Chef(string n, string p, string d, float s, string srv) : Employe(n, p, d, s), service(srv) {}

    void afficher() const{
        Employe::afficher();
        cout << "Le service est : " << service << endl;
    }
};

class Directeur : public Chef {
    string societe;

public:
    Directeur(string n, string p, string d, float s, string srv, string so) : Chef(n, p, d, s, srv), societe(so) {}

    void afficher() const {
        Chef::afficher();
        cout << "La société est : " << societe << endl;
    }
};

int main() {
    Directeur d("Abderrahmane", "Hafdane", "2003", 3500.09, "modir", "charika");
    d.afficher();

    return 0;
}

