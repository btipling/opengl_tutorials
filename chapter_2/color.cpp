
#include "sb7.h"
#include <iostream>

class color : public sb7::application {
    public:
    void render(double currentTime) {
        float r = (float) sin(currentTime) * 0.5f + 0.5f;
        float g = (float) cos(currentTime) * 0.5f + 0.5f;
        GLfloat red[] = { r, g, 0.0f, 1.0f };
        glClearBufferfv(GL_COLOR, 0, red);
        std::cout << "lol " << currentTime << " " << red << '\n';
    }

};

DECLARE_MAIN(color);