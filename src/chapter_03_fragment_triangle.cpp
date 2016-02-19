
#include "sb7.h"
#include <iostream>
#include "opengl_tutorials.h"

class chapter_02_dot : public sb7::application {
public:
    void render(double currentTime) {
        float r = (float) sin(currentTime) * 0.5f + 0.5f;
        float g = (float) cos(currentTime) * 0.5f + 0.5f;
        GLfloat red[] = { r, g, 0.0f, 1.0f };
        glClearBufferfv(GL_COLOR, 0, red);
        glUseProgram(rendering_program);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

    GLuint compile_shaders(void) {
        GLuint vertex_shader;
        GLuint fragment_shader;
        GLuint program;

        std::string vertex_shader_source_string = get_shader("triangle_vertex.vert");
        const GLchar * vertex_shader_source = vertex_shader_source_string.c_str();

        std::string fragment_shader_source_string = get_shader("triangle_frag.vert");
        const GLchar * fragment_shader_source = fragment_shader_source_string.c_str();


        vertex_shader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
        glCompileShader(vertex_shader);

        fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
        glCompileShader(fragment_shader);

        program = glCreateProgram();
        glAttachShader(program, vertex_shader);
        glAttachShader(program, fragment_shader);
        glLinkProgram(program);

        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);

        return program;
    }

    void startup() {
        rendering_program = compile_shaders();
        glCreateVertexArrays(1, &vertex_array_object);
        glBindVertexArray(vertex_array_object);
    }

    void shutdown() {
        glDeleteVertexArrays(1, &vertex_array_object);
        glDeleteProgram(rendering_program);
        glDeleteVertexArrays(1, &vertex_array_object);
    }

private:
    GLuint rendering_program;
    GLuint vertex_array_object;

};

DECLARE_MAIN(chapter_02_dot);