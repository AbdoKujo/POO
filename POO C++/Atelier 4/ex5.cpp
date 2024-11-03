#include <iostream>
using namespace std;

class objet {
public:
    static int count;
    void call() {
        count++;
    }
};
int objet::count = 0;
int main() {
    objet o;
    o.call();
    cout << "La fonction call a ete apele " << objet::count << " fois." << endl;
    return 0;
}
