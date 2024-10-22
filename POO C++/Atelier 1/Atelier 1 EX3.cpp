#include <iostream>

using namespace std;
int main(){
//EXERCICE 3
	int n;
	cout<<"entrez le nombre de ligne"<<endl;
	cin>>n;
	for(int i=1;i<=n;i++){
		for(int k=0;k<n-i;k++) cout<<" ";
		for(int j=1;j<=(2*i)-1;j++) cout<<"*";
		cout<<endl;
	}
	return 0;
}
