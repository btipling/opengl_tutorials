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
#endif //OPENGL_TUTORIALS_OPENGL_TUTORIALS_H
