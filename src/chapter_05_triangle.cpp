
#include "sb7.h"
#include <iostream>
#include <vmath.h>
#include "opengl_tutorials.h"

class chapter_05_triangle : public sb7::application {
public:
    void render(double currentTime) {
        float r = (float) sin(currentTime) * 0.5f + 0.5f;
        float g = (float) cos(currentTime) * 0.5f + 0.5f;
        float b = (float) tan(currentTime) * 0.5f + 0.5f;
        GLfloat bg_color[] = { 0.0f, 0.0f, 0.0f, 1.0f };
        for (int i = 0; i < 3; i++) {
            current_colors[i][0] = r;
            current_colors[i][1] = g;
            current_colors[i][2] = b;
        }
        glNamedBufferSubData(buffer, 0, sizeof(current_colors), current_colors);
        glClearBufferfv(GL_COLOR, 0, bg_color);
        glUseProgram(rendering_program);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

    GLuint compile_shaders(void) {
        GLuint vertex_shader;
        GLuint fragment_shader;
        GLuint program;

        std::string vertex_shader_source_string = get_shader("buffer_triangle_vertex.vert");
        const GLchar * vertex_shader_source = vertex_shader_source_string.c_str();

        std::string fragment_shader_source_string = get_shader("buffer_fragment.vert");
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
        glCreateBuffers(1, &buffer);
        glNamedBufferStorage(buffer, sizeof(current_colors), current_colors, GL_DYNAMIC_STORAGE_BIT);
        glVertexArrayVertexBuffer(vertex_array_object, 0, buffer, 0, 4*sizeof(float));
        glVertexArrayAttribFormat(vertex_array_object, 0, 4, GL_FLOAT, GL_FALSE, 0);
        glVertexArrayAttribBinding(vertex_array_object, 0, 0);
        glEnableVertexArrayAttrib(vertex_array_object, 0);
    }

    void shutdown() {
        glDisableVertexArrayAttrib(vertex_array_object, 0);
        glDeleteVertexArrays(1, &vertex_array_object);
        glDeleteProgram(rendering_program);
        glDeleteVertexArrays(1, &vertex_array_object);
    }

private:
    GLfloat current_colors[3][4] = {
            { 1.0f, 0.0f, 0.0f, 1.0f },
            { 1.0f, 0.0f, 0.0f, 1.0f },
            { 1.0f, 0.0f, 0.0f, 1.0f },
    };
    GLuint rendering_program;
    GLuint vertex_array_object;
    GLuint buffer;

};

DECLARE_MAIN(chapter_05_triangle);