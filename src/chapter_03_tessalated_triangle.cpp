
#include "sb7.h"
#include <iostream>
#include "opengl_tutorials.h"

class chapter_03_tessalated_triangle : public sb7::application {
public:
    void render(double currentTime) {
        GLfloat red[] = { 0.25f, 0.0f, 0.0f, 1.0f };
        glClearBufferfv(GL_COLOR, 0, red);

        GLfloat  attrib[] = {
                (float)sin(currentTime) * 0.5f,
                (float)cos(currentTime) * 0.6f,
                0.0f, 0.0f
        };
        glVertexAttrib4fv(0, attrib);
        glUseProgram(rendering_program);
        glDrawArrays(GL_PATCHES, 0, 3);
    }

    GLuint compile_shaders(void) {
        GLuint vertex_shader;
        GLuint fragment_shader;
        GLuint control_shader;
        GLuint eval_shader;
        GLuint program;

        std::string vertex_shader_source_string = get_shader("animated_triangle_vertex.vert");
        const GLchar * vertex_shader_source = vertex_shader_source_string.c_str();

        std::string fragment_shader_source_string = get_shader("tess_triangle_fragment.vert");
        const GLchar * fragment_shader_source = fragment_shader_source_string.c_str();


        std::string control_shader_source_string = get_shader("triangle_control_shader.vert");
        const GLchar * control_shader_source = control_shader_source_string.c_str();


        std::string eval_shader_source_string = get_shader("triangle_eval_shader.vert");
        const GLchar * eval_shader_source = eval_shader_source_string.c_str();


        program = glCreateProgram();
        vertex_shader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
        glCompileShader(vertex_shader);

        fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
        glCompileShader(fragment_shader);

        control_shader = glCreateShader(GL_TESS_CONTROL_SHADER);
        glShaderSource(control_shader, 1, &control_shader_source, NULL);
        glCompileShader(control_shader);

        eval_shader = glCreateShader(GL_TESS_EVALUATION_SHADER);
        glShaderSource(eval_shader, 1, &eval_shader_source, NULL);
        glCompileShader(eval_shader);

        glAttachShader(program, vertex_shader);
        glAttachShader(program, control_shader);
        glAttachShader(program, eval_shader);
        glAttachShader(program, fragment_shader);

        glDeleteShader(vertex_shader);
        glDeleteShader(control_shader);
        glDeleteShader(eval_shader);
        glDeleteShader(fragment_shader);

        glLinkProgram(program);

        return program;
    }

    void startup() {
        rendering_program = compile_shaders();
        glCreateVertexArrays(1, &vertex_array_object);
        glBindVertexArray(vertex_array_object);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
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

DECLARE_MAIN(chapter_03_tessalated_triangle);