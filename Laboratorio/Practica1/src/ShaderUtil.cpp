#include "../include/ShaderUtil.h"

/* Constructor que carga y compila los shaders */
ShaderUtil::ShaderUtil(const std::string& vertexPath, const std::string& fragmentPath) {
    
    /* Leer codigo de los Shaders */
    std::string vertexCode = readShaderSource(vertexPath);
    std::string fragmentCode = readShaderSource(fragmentPath);

    /* Compilar Shaders obtenidos */
    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexCode);
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentCode);

    /* Crear el programa-shader y enlazar los Shader creados */
    programID = glCreateProgram();
    GLint success;
    linkShader( programID ,  )
    glAttachShader(programID, vertexShader);
    glAttachShader(programID, fragmentShader);
    glLinkProgram(programID);

    /* Verificar que se hayan enlazado exitosamente */
    GLint success;
    GLchar infoLog[512];
    glGetProgramiv(programID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(programID, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    /* Una vez enlazados, elimina los Shader de memoria */
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

/* Utilizar los Shader enlazados */
void ShaderUtil::use() {
    glUseProgram(programID);
}

/* Getter de la ID asignada al programa-shader */
GLuint ShaderUtil::getProgramID() const {
    return programID;
}

/* Obtiene el codigo de shader desde un archivo */
std::string ShaderUtil::readShaderSource(const std::string& filePath) {
    std::ifstream file(filePath);   //Es un constructor muy parecido 
    std::stringstream buffer;

    if (!file.is_open()) {
        std::cerr << "No se pudo abrir el archivo de shader: " << filePath << std::endl;
        return "";
    }

    buffer << file.rdbuf();
    return buffer.str();
}

/* Compilar el Shader almacenado como String */
GLuint ShaderUtil::compileShader(GLenum type, const std::string& source) {
    GLuint shader = glCreateShader(type);
    const char* shaderCode = source.c_str(); //Puntero a una cadena de caracteres (apunta a la direccion de memoria de la fuente)
    glShaderSource(shader, 1, &shaderCode, NULL); //La direccion de el puntero shaderCode
    glCompileShader(shader);

    // Verificar errores de compilación
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    return shader;
}