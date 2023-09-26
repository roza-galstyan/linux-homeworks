#include <iostream>  
#include<vector>
#include "class.h"
#include "Sorting.h"
int main(){
   std::vector<Complex_number> _arr={Complex_number(1,3),Complex_number(1,2),Complex_number(6,1),Complex_number(8,9),Complex_number(4,3),Complex_number(0)};
   Sorting_complex_numbers(_arr);
    for (int i=0;i<6;++i){
        std::cout <<_arr[i].a <<" " << _arr[i].b << "\n";
    }
    return 0;
}
