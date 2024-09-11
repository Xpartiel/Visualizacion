#include <ostream>
#include <string>
#include <iostream>

class Palabra{

    private:
    std::string palabra;

    char* descubiertos;
    int coincidencias;


    public:

    Palabra( std::string nueva ){

        this -> palabra = nueva;
        this -> descubiertos = new char[ nueva.length() + 1 ];

        for( int i=0; i< nueva.length(); i++ ){
            descubiertos[i] = '*';
        }
        descubiertos[nueva.length()] = '\0';
        
        this -> coincidencias = 0;
    };

    std::string muestraDescubierto(){
        return descubiertos;
    }

    bool adivinado(){
        return ( coincidencias == palabra.length() );
    }

    bool encuentraLetra( char letra ){
        bool encontrado = false;
        for( int i=0; i<palabra.length(); i++ ){
            if( letra == palabra[i] ){//Evitar contar coincidencias repetidas
                encontrado = true;
                if( letra != descubiertos[i] ){
                    descubiertos[i] = letra;
                    coincidencias++;
                }
            }
        }
        return encontrado;
    }
};

int main(){

    Palabra adivinar( "electroencefalografista" );

    char ingreso;
    int intentos;
    int continuar;

    do{
        std::cout << " JUEGO DEL AHORCADO " << std::endl
        << "Tienes 10 intentos para descubrir la palabra secreta" << std::endl
        << "Escribe cada letra solo en minusculas" << std::endl;
        
        intentos = 1;
        continuar = 1;
        while( (! adivinar.adivinado() ) && ( intentos<10 ) ){
            std::cout << "Intento "<<intentos<<"/10" << std::endl << "Letras adivinadas: "<< adivinar.muestraDescubierto() << std::endl;
            std::cout << "Con que letra quieres probar ahora? ";
            std::cin >> ingreso;

            if(! adivinar.encuentraLetra(ingreso) ){
                intentos++;
                std::cout << "Te has equivocado ";
            }else{
                std::cout << "Acertaste ";
            }
            std::cout << "con la letra \"" <<ingreso<< "\"" << std::endl << std::endl;
        }
        if( adivinar.adivinado() ){
            std::cout << "GANASTE" << std::endl;
        }else{
            std::cout << "PERDISTE" << std::endl;
        }

        std::cout << "Quieres continuar jugando?"<<std::endl << "[1] Si"<<std::endl <<"[0] No"<< std::endl;
        std::cin >> continuar;
    }while( continuar != 0 );

    return 0;
}