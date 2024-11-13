#include <iostream>

using namespace std;

class Pile {
	
private:
    struct Node {
        int data ;
        Node* next ;
    };
    Node* head;
public:
    Pile() : head(nullptr) {}
    ~Pile() {
        while (head != nullptr) {
            pop();
        }
    }
    void push(int valeur) {
        Node* nouveau = new Node;
        nouveau->data = valeur;
        nouveau->next = head;
        head = nouveau;
        cout << "Empilé : " << valeur << endl;
    }
    int pop() {
        if (head == nullptr) {
            cout << "Erreur : la pile est vide !" << endl;
            return -1; 
        }
        int valeur = head->data;
        Node* ancienhead = head;
        head = head->next;
        delete ancienhead;
        cout << "Dépilé : " << valeur << endl;
        return valeur;
    }
    bool estVide() const {
        return head == nullptr;
    }
};

int main() {
    Pile p1;
    Pile p2;
    p1.push(10);
    p1.push(20);
    p1.push(30);
    while (!p1.estVide()) {
        p1.pop();
    }
    p2.push(100);
    p2.push(200);
    while (!p2.estVide()) {
        p2.pop();
    }
    return 0;
}
// autre methode

#include<iostream>
#include<list>
using namespace std;
class pile{
	list<int> p;
	public : 
	pile() : p(1,0){}
	pile(int v) : p(1,v){}
	~pile(){
		cout<<"\nelement supprime"<<endl;
	};
	void push(int v){
		p.push_front(v);
	}
	void pop(){
		if(!p.empty())
		p.pop_front();
		else cout<<" \nle pile est vide"<<endl;
	}
	void display(){
		for(auto it : p) cout<<it<<" " ; //for(auto it=p.be....)
	}
};
int main(){
	pile p1(5) , p2(8) ;
	for(size_t i=0 ; i<5; i++){
			p1.push(i*i);
			p2.push(i+i);
	}
	p1.pop();
	p2.pop();
	p1.display();
	cout<<endl;
	p2.display();
}
