/*
Archivo header, AQUI NO HAY IMPLEMENTACIONES

Si buscas implementaciones, buscalas en el archivo con el mismo nombre
per con formato .cpp y en la carpeta src
*/

#ifndef SHADER_UTIL_H

#define SHADER_UTIL_H

#include "GlUtil.h"
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

class ShaderUtil {
public:
    /* Constructor que requiere las rutas de los archivos de shaders */
    ShaderUtil(const std::string& vertexPath, const std::string& fragmentPath);

    /* Utilizar los Shaders */
    void use();

    /* Obtener el ID del programa de shader */
    GLuint getProgramID();

    void update( GLuint programa );

private:
    /* ID del programa-shader */
    GLuint programID;

    /* Leer el codigo de shader desde algun archivo */
    std::string readShaderSource(const std::string& filePath);

    /* Compilar shader */
    GLuint compileShader(GLenum type, const std::string& source);
};

#endif