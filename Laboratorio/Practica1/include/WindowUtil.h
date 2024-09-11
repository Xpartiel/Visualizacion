/*
Archivo header, AQUI NO HAY IMPLEMENTACIONES

Si buscas implementaciones, buscalas en el archivo con el mismo nombre
per con formato .cpp y en la carpeta src
*/

#ifndef WINDOW_UTIL_H
#define WINDOW_UTIL_H

#include "GlUtil.h"
#include <iostream>

class WindowUtil{

public:
    /*
    Constructor que solicita el ancho y alto de la ventana
    (en pixeles) mediante valores int
    y el titulo que se le va a asignar.
    */
    WindowUtil(const int ancho, int alto, const std::string title);

    /* Usar la Ventana */
    void use();

    /* Liberar memoria al acabar */
    int finaliza();

private:

    /* El alto asignado a la ventana, en pixeles */
    int ancho_px;

    /* El ancho asignado de la ventana, en pixeles */
    int alto_px;

    /* El titulo de la ventana */
    std::string titulo;

    /* El objeto GLFWwindow que hace todo */
    GLFWwindow* ventana;

    /* El coso de tiempo, no le se, magia */
    float time;
};

#endif