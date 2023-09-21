#include <iostream>
#include <math.h>

class Complex_number{
   // a+b*i
    public:
    double a;
    double b;
    public:
    // constructors
    
    Complex_number (int _a,int _b):a(_a),b(_b){};
    Complex_number (int _a):a(_a),b(0){};
    Complex_number ():a(0),b(0){};
    // operators +,-,*const and function Absolute_value
    
    Complex_number operator +(const Complex_number& elem_1){
                return Complex_number(elem_1.a+a,elem_1.b+b);
    };
    Complex_number operator -(const Complex_number& elem_1){
                return Complex_number(a-elem_1.a,b-elem_1.b);
    };
    Complex_number operator *(int n){
                return Complex_number(a*n,b*n);
    };
    double Absolute_value (){
                return sqrt((a*a)+(b*b));
    };
    
};
