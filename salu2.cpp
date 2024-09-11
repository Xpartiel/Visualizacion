#include <iostream>
#include <string>

int suma(int a , int b){
    return a + b;
}

int main(){

    int a = 1;
    float b = 0.5f;
    bool c = true;
    char s[] = "True";
    char d = 'S';
    double e = 3.14159784;
    std::cout << "Hola" << std::endl;

    std::cout << a << " " << b << " " << c << " " << d << " " << std::endl;

    std::cout << "Suma de los enteros 5 y 8: " << suma(5,8) << std::endl;
    return 0;

}