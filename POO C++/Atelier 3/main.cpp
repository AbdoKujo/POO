
#include "Voiture.h"
#include <iostream>

using namespace std;

int main() {
    // Création d'une voiture avec le constructeur par défaut
    Voiture v1;
    v1.afficherInfo();

    // Création d'une voiture avec le constructeur avec paramètres
    Voiture v2("Toyota", "Corolla", 2020, 15000.0, 50.0);
    v2.afficherInfo();

    // Accélérer la voiture
    v2.accelerer(20.0);

    // Freiner la voiture
    v2.freiner(30.0);

    // Faire avancer la voiture
    v2.avancer(100.0);

    // Afficher à nouveau les informations de la voiture
    v2.afficherInfo();

    return 0;
}
