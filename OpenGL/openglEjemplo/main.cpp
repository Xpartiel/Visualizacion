#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include <vector>

#define PI 3.141592

// Vertex Shader source code (GLSL 4.10)
const char *vertexShaderSource = R"(
    #version 410 core
    layout (location = 0) in vec3 aPos;
    layout (location = 1) in vec3 aCol;
    uniform float aTime;
    out vec3 color;

    void main()
    {
        gl_Position = vec4(aPos.x + cos(aTime), aPos.y, aPos.z, 1.0);
        //color = (aPos*cos(aTime) +1) * 0.5;
        color = aCol;
    }
)";

// Fragment Shader source code (GLSL 4.10)
const char *fragmentShaderSource = R"(
    #version 410 core
    out vec4 FragColor;
    in vec3 color;

    void main()
    {
        FragColor = vec4(color, 1.0);
        //FragColor = vec4(1.0,1.0, 0.0, 1.0);
    }
)";

float *creaCirculo(int tam, float radius){

    float *vertices = new float[(tam + 1) * 3];

    vertices[0] = 0.0f;
    vertices[1] = 0.0f;
    vertices[2] = 0.0f;
    float dosPI_entre_tam = 2.0f * M_PI / (float)(tam - 1);
    for (int i = 1; i < tam + 1; i++)
    {

        vertices[(i * 3) + 0] = radius * cosf(dosPI_entre_tam * (i - 1)); // x
        vertices[(i * 3) + 1] = radius * sinf(dosPI_entre_tam * (i - 1)); // y
        vertices[(i * 3) + 2] = 0.0f;                                     // z
    }

    return vertices;
}

std::vector<float> creaCirculoVector(int tam, float radius){

    std::vector<float> vertices;

    vertices.push_back(0.0f);
    vertices.push_back(0.0f);
    vertices.push_back(0.0f);

    for (int i = 1; i < tam + 1; i++)
    {

        vertices.push_back(radius * cosf((2.0f * M_PI / (tam - 1)) * (i - 1))); // x
        vertices.push_back(radius * sinf((2.0f * M_PI / (tam - 1)) * (i - 1))); // y
        vertices.push_back(0.0f);                                               // z
    }

    return vertices;
}

int main(int argc, char *argv[])
{

    /***************************************************************************************************************
     * Con los parámetros de entrada en el main, podemos obtener información al ejecutar la linea de comandos
     * En este ejemplo queremos obtener el método de pintado "1: float* Apuntador " o "2: Vector<float>"
     ****************************************************************************************************************/

    std::cout << argc << " : Número argumentos" << std::endl; // no indica cuantos argumentos está en la línea de comandos
    std::cout << argv[0];
    if (argc > 1)
        for (int i = 1; i < argc; i++)
            std::cout << "," << argv[i];

    std::cout << " : Valor argumentos" << std::endl; // siempre está el ejecutable y si hay más los podemos imprimir

    // Initialize GLFW
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Set OpenGL version to 4.1
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a GLFWwindow object
    GLFWwindow *window = glfwCreateWindow(800, 600, "OpenGL Triangle", NULL, NULL);
    if (!window){
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    if (glewInit() != GLEW_OK){
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

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
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
    }

    // Build and compile the fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // Check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
    }

    // Link shaders to a shader program
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
                  << infoLog << std::endl;
    }

    // Delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Set up vertex data and buffers and configure vertex attributes
    //int tam = 100;

    /*****************************************************************************************************************************
     * Crea un circulo con N (tam) puntos utilizando apuntadores
     * llama la función creaCirculo
     ******************************************************************************************************************************/
    //float *vertices = creaCirculo(tam, 0.5);

    /*****************************************************************************************************************************
     * Crea un circulo con N (tam) puntos utilizando la clase vector
     * llama la función creaCirculo
     *****************************************************************************************************************************/
    // std::vector<float> vertices = creaCirculoVector(tam, 0.5);

    /******************************************************************************************************************************
     * Para la clase del miércoles 4 de septiembre
     * Otra configuración
     ******************************************************************************************************************************/
    /* */
     GLfloat vertices[] = {
    //Positions          // Colors
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f, 0.0f , 0.0f // Top Right
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f, // Bottom Right
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f, // Bottom Left
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f  // Top Left
    };
    
    /* * /
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // */

    GLuint VAO;
    glGenVertexArrays(1, &VAO);

    GLuint VBO, VBOcolors;

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, 4*6*sizeof(float), vertices, GL_STATIC_DRAW); // utilizando apuntadores
    // glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW); // utilizando Clase vector
    
    /*****************************************************************************************************************************
     * Para la clase del miércoles 4 de septiembre
     ******************************************************************************************************************************/
    /* * /
    glGenBuffers(1, &VBOcolors);
    glBindBuffer(GL_ARRAY_BUFFER, VBOcolors);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
    // */

    /**
     * Variables para mandar iformación del CPU -> GPU (shader)
     */
    GLuint timeLocation = -1;
    float time = -1.0;

    // Render loop
    while (!glfwWindowShouldClose(window))
    {
        // Input
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        time = glfwGetTime(); // obtiene el valor en segundos desde que se inicializó GLFW

        // Render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw the triangle
        glUseProgram(shaderProgram);
        /**
         * Inicializaciín de variables para mandar iformación del CPU -> GPU (shader)
         * Mandamos una variable de tiempo para actuzalizar datos en el shader
         * En estes caso la variable se llama aTime
         */
        timeLocation = glGetUniformLocation(shaderProgram, "aTime"); // Obtenemos una
        glUniform1f(timeLocation, time);

        //Habilitamos que Array queremos dibujar
        glBindVertexArray(VAO);
        // Bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
        /* */
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);
        
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
        glEnableVertexAttribArray(2);
        // */
        // Bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).

        // Clase del 4 de septiembre
        /* * /
        glBindBuffer(GL_ARRAY_BUFFER, VBOcolors);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
        // */
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

        glDisableVertexAttribArray(0);
        // glDisableVertexAttribArray(1);
        //  Unbind the VAO
        glBindVertexArray(0);
        // Swap buffers and poll IO events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Deallocate resources
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &VBOcolors);
    glDeleteProgram(shaderProgram);
    //delete[] vertices; // utilizar solamente si se inicializó usando new.... Comentar si se utiliza Vector
    //  Terminate GLFW
    glfwTerminate();
    return 0;
}