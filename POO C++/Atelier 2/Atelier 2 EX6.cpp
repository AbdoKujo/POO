#include <iostream>

using namespace std;
//passage par adress la seul methode en c
void incrementer(int* p){
	(*p)++;
}
void permuter(int* a, int* b){
	int temp = *a;
	*a = *b;
	*b = temp;
}
//passage par reference
void Rincrementer(int& ref){
	ref++;
}
void Rpermuter(int& a, int& b){
	int temp = a;
	a = b;
	b = temp;
}
int main(){
	int a,b;
	cout<<"donner la valeur de a et b"<<endl;
	cin>>a;
	cin>>b;
	// passage par adress
	cout<<"passage par adress"<<endl;
	
	cout<<"avant incrementaion : a = "<<a<<" et b = "<<b<<endl;
	incrementer(&a);incrementer(&b);
	cout<<"apres incrementaion : a = "<<a<<" et b = "<<b<<endl;
	permuter(&a,&b);// Passe les adresses de a et b
	cout<<"apres permutaion : a = "<<a<<" et b = "<<b<<endl;
	
	// passage par reference
	cout<<"passage par reference"<<endl;// passage par reference
	
	cout<<"avant incrementaion : a = "<<a<<" et b = "<<b<<endl;
	Rincrementer(a);Rincrementer(b);
	cout<<"apres incrementaion : a = "<<a<<" et b = "<<b<<endl;
	Rpermuter(a,b);// Passe les adresses de a et b
	cout<<"apres permutaion : a = "<<a<<" et b = "<<b<<endl;
	return 0;
}