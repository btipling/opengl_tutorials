
#include "sb7.h"
class my_application : public sb7::application {
    public:
    void render(double currentTime) {
        static const GLfloat red[] = { 1.0f, 0.0f, 0.0f, 1.0f };
        glClearBufferfv(GL_COLOR, 0, red);
    }

};

DECLARE_MAIN(my_application);