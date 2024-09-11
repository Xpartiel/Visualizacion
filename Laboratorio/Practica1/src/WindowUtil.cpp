/*
Archivo header, AQUI NO HAY IMPLEMENTACIONES

Si buscas implementaciones, buscalas en el archivo con el mismo nombre
per con formato .cpp y en la carpeta src
*/

#include "../include/WindowUtil.h"

#include <string>

/* Constructor de ventana, requiere el ancho y alto en pixeles, ademas de un titulo */
WindowUtil::WindowUtil( const int nuevo_ancho_px , const int nuevo_alto_px , const std::string nuevo_titulo ){

    ancho_px = nuevo_ancho_px;
    alto_px = nuevo_alto_px;
    titulo = nuevo_titulo;

    // Intenta iniciar GLFW
    if ( !glfwInit() ){
        std::cerr << "Fallo de inicio de GLFW" << std::endl;
        return -1;
    }

    // Usar OpenGL version to 4.1
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Crear objeto GLFWwindow
    // glfwCreateWindow(ancho_px , alto_px , titulo_str , monitor , compartiendo )
    ventana = glfwCreateWindow(ancho_px, alto_px, titulo, NULL, NULL);
    if (! ventana ){
        std::cerr << "Fallo de creacion de ventana GLFW" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(ventana);
    // Inicializar GLEW
    if (glewInit() != GLEW_OK){
        std::cerr << "Fallo de inicializacion de GLEW" << std::endl;
        return -1;
    }
};

int finaliza( GLuint shaderProgram ){
        // Deallocate resources
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteProgram(shaderProgram);

        // Terminate GLFW
        glfwTerminate();
        return 0;
}

void use(){
 // Render loop
    while (!glfwWindowShouldClose(ventana))
    {
        time = glfwGetTime();
        // Input
        if (glfwGetKey(ventana, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(ventana, true);

        // Render
        glClearColor(0.0f, 0.3f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        glUseProgram(shaderProgram);
        
        // Draw
        GLuint uniformTime = glGetUniformLocation(shaderProgram , "atime");
        glUniform1f(uniformTime , time);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLE_FAN, 0, (tam+2));

        // Swap buffers and poll IO events
        glfwSwapBuffers(ventana);
        glfwPollEvents();
    }
}

    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // Bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Unbind the VAO
    glBindVertexArray(0);
}

GLuint construirVertexShader( char* vertexShaderSource ){
    // Build and compile the vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // Check for shader compile errors
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    return vertexShader;
}

GLuint construirFragmentShader( char* fragmentShaderSource ){
    // Build and compile the fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // Check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    return fragmentShader;
}
