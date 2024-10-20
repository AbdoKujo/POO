#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;

void test(const vector<int>& params) {
    cout << "Fonction appelee avec " << params.size() << " parametres." << endl;
}
int main() {
    try {
        size_t i = 1;
        size_t step = 100000;
        while (true) {
            vector<int> params(i, 1);
            test(params);
            i += step;
        }
    } catch (const bad_alloc& e) {
        cout << "Erreur d'allocation memoire : " << e.what() << endl;
        cout << "Limite atteinte lors de la tentative avec trop de parametres." << endl;
    }
    return 0;
}
