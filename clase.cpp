#include <iostream>
#include <string>

class Animal{

    /* Modificadores de Acceso
        - public:
        - private:
        - protected:
    */
    private:
    std::string name;
    int patas;

    public:

    Animal(std::string nombre , int patas): name(nombre) , patas(patas){};

    void setNombre( std::string nuevo ){
        this -> name = nuevo;
    }
    std::string getNombre(){
        return name;
    }

    void setPatas( int numero ){
        this -> patas = numero;
    }

    void printInfo(){

        std::cout << name << std::endl;
        std::cout << patas << std::endl;
    }

    virtual void respirar(){
        std::cout<<"Inhala y exhala"<<endl;
    }
};

class Gato : public Animal{
    private:
    std::string pelaje;

    public:
    Gato(std::string name , int patas , std::string pelaje):Animal(name,patas) , pelaje(pelaje){};

    void treparArbol(){
        printInfo();
        std::cout << "Trepando asi bien chido" << std::endl;
    }

    void respirar override(){
        std::cout<<"Hola (se ahoga)"
    }
};

int main(){

    Animal gato("DonGato",2);

    gato.printInfo();
    return 0;
}