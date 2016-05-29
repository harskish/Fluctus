#define CL_HPP_MINIMUM_OPENCL_VERSION 120
#define CL_HPP_TARGET_OPENCL_VERSION 120

#include <GLFW/glfw3.h>
#include "cl2.hpp"
#include "window.hpp"
#include "clcontext.hpp"

void draw(GLFWwindow *window) {
    float ratio;
    int width, height;
    
    glfwGetFramebufferSize(window, &width, &height);
    ratio = width / (float) height;
    
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
    glMatrixMode(GL_MODELVIEW);
    
    glLoadIdentity();
    glRotatef((float) glfwGetTime() * 50.f, 0.f, 0.f, 1.f);
    
    glBegin(GL_TRIANGLES);
    glColor3f(1.f, 0.f, 0.f);
    glVertex3f(-0.6f, -0.4f, 0.f);
    glColor3f(0.f, 1.f, 0.f);
    glVertex3f(0.6f, -0.4f, 0.f);
    glColor3f(0.f, 0.f, 1.f);
    glVertex3f(0.f, 0.6f, 0.f);
    glEnd();

    glfwSwapBuffers(window);
}

int main(int argc, char* argv[])
{
    const int USE_GPU = (argc > 1) ? atoi(argv[1]) : 1;

    if (!glfwInit())
    {
        exit(EXIT_FAILURE);
    }

    Window window(800, 600);
    GLFWwindow *wptr = window.glfwWindowPtr();

    CLContext ctx(USE_GPU, window.getTexture());
    ctx.executeKernel();

    // Vsync, 4xMSAA
    glfwSwapInterval(1);
    glfwWindowHint(GLFW_SAMPLES, 4);

    // Main loop
    while(window.available())
    {
        // Do stuff
        draw(wptr);
    }

    glfwTerminate();

    return 0;
}

