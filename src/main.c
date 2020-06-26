#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#ifdef __APPLE__
// #include <OpenGL/gl.h>
#else
// #include <GL/gl.h>
#endif

#include "gameWindow.h"


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

    const GLchar* vertex_shader =
    "#version 410\n"
    "layout (location = 0) in vec3 vp;"
    "void main() {"
    "    gl_Position = vec4(vp.x ,vp.y, vp.z, 1.0);"
    "}\0";

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertex_shader, NULL);
    glCompileShader(vertexShader);

    int success;
    char infolog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infolog);
        printf("Error compiling vertex shader %s\n", infolog);
    }

    const GLchar* fragment_shader = 
    "#version 410\n"
    "out vec4 frag_colour;"
    "void main() {"
    "    frag_colour = vec4(0.5, 0.0, 0.5, 1.0);"
    "}\0";

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragment_shader, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infolog);
        printf("Error compiling vertex shader %s\n", infolog);
    }

    GLuint shader_program = glCreateProgram();
    glAttachShader(shader_program, vertexShader);
    glAttachShader(shader_program, fragmentShader);
    glLinkProgram(shader_program);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader); 

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
        glUseProgram(shader_program);
        glBindVertexArray(vertexArrayObject);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        SDL_GL_SwapWindow(window);

    }
    destroyWindow();
    return 0;
}