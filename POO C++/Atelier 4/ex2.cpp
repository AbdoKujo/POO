#include <iostream>
using namespace std;

class Animal
{
protected:
    string nom;
    int age;

public:
    void set_value(string n, int a)
    {
        nom = n;
        age = a;
    }
};

class Zebra : public Animal
{
private:
    string lieu_or;

public:
    Zebra(string l) : lieu_or(l) {}
    void display()
    {
        cout << "Le nom de zebra est :" << nom << endl;
        cout << "L'age de zebra est :" << age << endl;
        cout << "Le lieu d'origine de zebra est: " << lieu_or << endl;
    }
};

class Dolphin : public Animal
{
private:
    string habitat;

public:
    Dolphin(string h) : habitat(h) {}
    void display()
    {
        cout << "Le nom de Dolphin est :" << nom << endl;
        cout << "L'age de Dolphin est :" << age << endl;
        cout << "L'habitat de Dolphin est :" << habitat << endl;
    };
};

int main()
{
    Zebra zebra("Afrique");
    Dolphin dolphin("Ocean");

    zebra.set_value("zebra", 3);
    zebra.display();
    dolphin.set_value("dolphine", 5);
    dolphin.display();
}
