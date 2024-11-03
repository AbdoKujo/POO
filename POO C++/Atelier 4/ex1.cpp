#include<iostream>
using namespace std;
class Complex{
	private :
		double reel;
		double img;
	public :
		Complex(){}
		Complex(double r , double i);
		Complex(const Complex& C);
		double get_reel();
		double get_img();
		void egalite(Complex a , Complex b);
		Complex addition(Complex a , Complex b);
		Complex soustraction(Complex a , Complex b);
		Complex multiplication(Complex a , Complex b);
		Complex conjuguee(Complex a);
		Complex devison(Complex a , Complex b);
};
Complex::Complex(double r , double i) : reel(r) , img(i){}
Complex::Complex(const Complex& C) : reel(C.reel) , img(C.img){}
double Complex::get_reel(){return this->reel;}
double Complex::get_img(){return this->img;}
void Complex::egalite(Complex a , Complex b){
	if(a.get_reel()==b.get_reel()){
		cout<<"les reel sont egeaux"<<endl;
		if(a.get_img()==b.get_img()){
			cout<<"les imaginaires sont aussi egeaux ."<<endl<<"donc les deux nombres sont egeaux";
	    }else cout<<" ils sont defferents"<<endl;
    }
}
Complex Complex::addition(Complex a, Complex b) {
    return Complex(a.get_reel() + b.get_reel(), a.get_img() + b.get_img());
}
Complex Complex::soustraction(Complex a, Complex b) {
    return Complex(a.get_reel() - b.get_reel(), a.get_img() - b.get_img());
}
Complex Complex::multiplication(Complex a, Complex b) {
        double real_part = a.get_reel() * b.get_reel() - a.get_img() * b.get_img();
        double imag_part = a.get_reel() * b.get_img() + a.get_img() * b.get_reel();
        return Complex(real_part, imag_part);
    }
Complex Complex::conjuguee(Complex a){
	return Complex(a.get_reel() , -a.get_img());
}
Complex Complex::devison(Complex a , Complex b){
	Complex C = b.conjuguee(b);
	C=C.multiplication(a , C);
	double R=C.get_reel() / (b.get_reel() * b.get_reel() + b.get_img() * b.get_img());
	double I=C.get_img() / (b.get_reel() * b.get_reel() + b.get_img() * b.get_img());
	Complex D(R,I);
	return D;
}
int main(){
	Complex C1(1,2) , C2(3,4);
	Complex C3=C1.devison(C1 , C2);
	cout<<" Reel = "<<C3.get_reel()<<" Img = "<<C3.get_img()<<endl;
}

