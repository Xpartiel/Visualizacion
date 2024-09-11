/*
Archivo para HEADER
Aqui no se encuentran implementaciones; consultar el archivo con mismo nombre
y extension .cpp para verificar la implementacion concreta.
*/

#include "GlUtil.h"

class RenderableUtil{
public:
    RenderableUtil( float vertices[] , int agrupacion );

    /* Modificar el valor especifico en la i-esima posicion */
    void update( int index , float value );

    /* Getter, que indica la cantidad de floats usados para informacion de posicion */
    int getCoordinateSize();

    void setCoordinateSize( int value );

    /* Getter, que indica la cantidad de floats usados para informacion de color */
    int getColorSize();

    void setColorSize( int value );

    /* Getter, que indica la cantidad de floats usados para informacion de UV */
    int getUVSize();

    void setUVSize( int value );

    /* Getter, que indica la cantidad de total de floats usados */
    int getSize();

    void setSize( int value );

    /* Getter, que indica la cantidad de total de 'vertices' */
    int getGroupedSize();

private:

    /* Cantidad de datos concretos usados para informacion de posicion */
    int coordinateSize;

    /* Cantidad de datos concretos usados para informacion de color */
    int colorSize;

    /* Cantidad de datos concretos usados para informacion de UV */
    int uvSize;

    /* Cantidad de datos concretos usados por cada vertice */
    int dataSize;

    /* Arreglo de datos que en conjunto forman todos los vertices  */
    GLfloat vertices[];
};