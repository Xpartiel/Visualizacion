#include "include/ShaderUtil.h"
#include "include/WindowUtil.h"
#include "include/RenderableUtil.h"

#include <string>

int main()
{
    //Crear la ventana
    WindowUtil ventana(640,480,"titulo");

    // Crear un objeto ShaderUtil con los shaders
    ShaderUtil shader("shader/shader1.vert", "shader/shader1.frag");

    RenderableUtil renderizable();
    // Configuración de los datos de los vértices

    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    // Bucle de renderizado
    ventana.use();
    ventana.finaliza();

    // Liberar recursos
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}