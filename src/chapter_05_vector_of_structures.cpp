
#include "sb7.h"
#include <iostream>
#include <vector>
#include "opengl_tutorials.h"

typedef struct {
    // Position
    float x;
    float y;
    float z;
    float w;

    // Color
    float r;
    float g;
    float b;
    float a;
}
Vertex;

class chapter_05_vector_of_structures : public sb7::application {
public:
    void render(double currentTime) {
        GLfloat bg_color[] = { 0.0f, 0.0f, 0.0f, 1.0f };
        glClearBufferfv(GL_COLOR, 0, bg_color);
        glUseProgram(rendering_program);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

    GLuint compile_shaders(void) {
        GLuint vertex_shader;
        GLuint fragment_shader;
        GLuint program;

        std::string vertex_shader_source_string = get_shader("vector_triangle_vertex.vert");
        const GLchar * vertex_shader_source = vertex_shader_source_string.c_str();

        std::string fragment_shader_source_string = get_shader("vector_fragment.vert");
        const GLchar * fragment_shader_source = fragment_shader_source_string.c_str();

        vertex_shader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
        GLint status;
        glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &status);
        if (status == GL_FALSE) {
            GLint infoLogLength;
            glGetShaderiv(vertex_shader, GL_INFO_LOG_LENGTH, &infoLogLength);

            GLchar* strInfoLog = new GLchar[infoLogLength + 1];
            glGetShaderInfoLog(vertex_shader, infoLogLength, NULL, strInfoLog);

            fprintf(stderr, "Compilation error in shader: %s\n", strInfoLog);
            delete[] strInfoLog;
        }
        glCompileShader(vertex_shader);

        fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
        glCompileShader(fragment_shader);

        program = glCreateProgram();
        glAttachShader(program, vertex_shader);
        glAttachShader(program, fragment_shader);

        check_error(__FILE__, __LINE__);

        GLsizei result;

        glLinkProgram(program);

        glGetProgramiv(program, GL_LINK_STATUS, &result);

        if(result == GL_FALSE) {
            GLint length;
            char *log;
            /* get the program info log */
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
            log = (char *) malloc(length);
            glGetProgramInfoLog(program, length, &result, log);

            /* print an error message and the info log */
            fprintf(stderr, "sceneInit(): Program linking failed: %s\n", log);
            free(log);

            /* delete the program */
            glDeleteProgram(program);
            exit(1);
        }

        std::cout << glGetAttribLocation(program, "position");
        std::cout << glGetAttribLocation(program, "color");

        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);
        return program;
    }

    void startup() {

        vertices = {};
        vertices.push_back((Vertex) {
                0.5, 0.1, 1.0, 1.0,
                1.0, 0.0, 0.0, 1.0
        });
        vertices.push_back((Vertex) {
                0.1, 0.1, 1.0, 1.0,
                1.0, 1.0, 0.0, 1.0
        });
        vertices.push_back((Vertex) {
                0.5, 0.5, 1.0, 1.0,
                0.0, 0.0, 1.0, 1.0
        });


        rendering_program = compile_shaders();
        glCreateVertexArrays(1, &vertex_array_object);
        glBindVertexArray(vertex_array_object);
        glCreateBuffers(1, &buffer);
        glNamedBufferStorage(buffer, vertices.size() * sizeof(Vertex), &vertices.front(), 0);

        glVertexArrayAttribBinding(vertex_array_object, 0, 0);
        glVertexArrayAttribFormat(vertex_array_object, 0, 4, GL_FLOAT, GL_FALSE, offsetof(Vertex, x));
        glEnableVertexArrayAttrib(vertex_array_object, 0);

        glVertexArrayAttribBinding(vertex_array_object, 1, 0);
        glVertexArrayAttribFormat(vertex_array_object, 1, 4, GL_FLOAT, GL_FALSE, offsetof(Vertex, r));
        glEnableVertexArrayAttrib(vertex_array_object, 1);

        glVertexArrayVertexBuffer(vertex_array_object, 0, buffer, 0, sizeof(Vertex));
    }

    void shutdown() {
        glDisableVertexArrayAttrib(vertex_array_object, 0);
        glDeleteVertexArrays(1, &vertex_array_object);
        glDeleteProgram(rendering_program);
        glDeleteVertexArrays(1, &vertex_array_object);
    }

private:
    std::vector<Vertex> vertices;
    GLuint rendering_program;
    GLuint vertex_array_object;
    GLuint buffer;

};

DECLARE_MAIN(chapter_05_vector_of_structures);
