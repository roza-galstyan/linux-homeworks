#include <iostream>
#include <vector>


void Sorting_complex_numbers (std::vector<Complex_number> &arr){
    Complex_number temp;
    for (int i=0;i+1<arr.size();++i){
         for (int j=i+1;j<arr.size();++j){
            if (arr[i].Absolute_value()>arr[j].Absolute_value()){
                temp.a=arr[j].a;
                temp.b=arr[j].b;
                arr[j].a=arr[i].a;
                arr[j].b=arr[i].b;
                arr[i].a=temp.a;
                arr[i].b=temp.b;
            };
            
                }

                    } 
                        };
