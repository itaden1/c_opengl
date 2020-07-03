#include <stdio.h>
#include "shaders.h"

GLuint buildShaderProgram()
{
    printf("building shaders\n");
    int vertSuccess;
    int fragSuccess;
    GLuint shaderProgram = glCreateProgram();
    GLuint vertexShader = buildVertexShader();
    vertSuccess = chechShaderBuildSuccess(vertexShader);
    GLuint fragmentShader = buildFragmentShader();
    fragSuccess = chechShaderBuildSuccess(fragmentShader);
    if (vertSuccess && fragSuccess)
    {
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);
        return shaderProgram;
    }
    else
    {
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader); 
        return 0;
    }
}

GLuint buildVertexShader()
{
    const GLchar* vertex_shader =
    "#version 410\n"
    "layout (location = 0) in vec3 vp;"
    "out vec4 vertexColor;"
    "void main() {"
    "    gl_Position = vec4(vp.x ,vp.y, vp.z, 1.0);"
    "    vertexColor = vec4(0.5, 0.0, 0.0, 1.0);"
    "}\0";
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertex_shader, NULL);
    glCompileShader(vertexShader);

    return vertexShader;
}

GLuint buildFragmentShader()
{
    const GLchar* fragment_shader = 
    "#version 410\n"
    "out vec4 frag_colour;"
    "in vec4 vertexColor;"
    "uniform vec4 ourColor;"
    "void main() {"
    "    frag_colour = ourColor;"
    "}\0";

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragment_shader, NULL);
    glCompileShader(fragmentShader);

    return fragmentShader;
}

int chechShaderBuildSuccess(GLuint shader)
{
    char infolog[512];
    int ok;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &ok);
    if (!ok)
    {
        glGetShaderInfoLog(shader, 512, NULL, infolog);
        printf("Error compiling vertex shader %s\n", infolog);
        return 0;
    }
    return 1;
}