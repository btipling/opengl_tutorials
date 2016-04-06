//
// Created by swart on 2/15/2016.
//

#ifndef OPENGL_TUTORIALS_OPENGL_TUTORIALS_H
#define OPENGL_TUTORIALS_OPENGL_TUTORIALS_H

#include <fstream>
#include <sstream>

std::string get_shader(std::string path) {
    std::string fullpath = "./resources/shaders/" + path;
    std::ifstream vertexShaderFile(fullpath);
    std::ostringstream vertexBuffer;
    vertexBuffer << vertexShaderFile.rdbuf();
    return vertexBuffer.str();
}

void check_error(const char * filename, int line_number) {
    GLenum error;
    while ((error = glGetError()) != 0) {
        printf("GL Error %x: %s:%d\n", error, filename, line_number);
        exit(1);
    }
}

#endif //OPENGL_TUTORIALS_OPENGL_TUTORIALS_H
