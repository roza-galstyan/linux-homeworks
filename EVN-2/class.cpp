#include <iostream>
#include <math.h>
#include "class.h"
	Complex_number Complex_number:: operator +(const Complex_number& elem_1){
                return Complex_number(elem_1.a+a,elem_1.b+b);
    };
	Complex_number Complex_number:: operator -(const Complex_number& elem_1){
                return Complex_number(a-elem_1.a,b-elem_1.b);
    };
	Complex_number Complex_number:: operator *(int n){
                return Complex_number(a*n,b*n);
    };
    

