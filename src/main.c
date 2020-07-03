#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#ifdef __APPLE__
// #include <OpenGL/gl.h>
#else
// #include <GL/gl.h>
#endif

#include "gameWindow.h"
#include "shaders.h"


int main(void)
{
    bool quit = false;

    if ( initWindow() != 0)
    {
        printf("Initialisation failure %s\n", SDL_GetError());
         return 1;
    }

    printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
    printf("OpenGL renderer: %s\n", glGetString(GL_RENDERER));
    printf("OpenGL Shader Language Version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

    glViewport(0, 0, 640, 480);
    glClearColor(0.5f, 0.5f, 0.5f, 0.f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    GLfloat vertices[] = {
        0.0f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f
    };
    GLuint vertexBufferObject = 0;
    glGenBuffers(1, &vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    GLuint vertexArrayObject = 0;
    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);

    GLuint shader_program = buildShaderProgram();
    if (!shader_program)
    {
        destroyWindow();
        return 1;
    }

    while (!quit)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                printf("Close button clicked closing window\n");
                quit = true;
            }

        }
        // rendering
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        float timeValue = SDL_GetTicks() * 0.001;
        float greenVal = (sin(timeValue) / 2.0f) + 0.5f;
        int vertexColorLocation = glGetUniformLocation(shader_program, "ourColor");
        glUseProgram(shader_program);
        glUniform4f(vertexColorLocation, 0.0f, greenVal, 0.0f, 1.0f);
        glBindVertexArray(vertexArrayObject);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        SDL_GL_SwapWindow(window);

    }
    destroyWindow();
    return 0;
}