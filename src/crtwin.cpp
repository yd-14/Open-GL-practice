#include "crtwin.h"

#include<iostream>

GLFWwindow* create_window()
{
    GLFWwindow* w;
    /* Initialize the library */
    if (!glfwInit())
       std::cout<<"GLFW Init Error"<<std::endl;// return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    w = glfwCreateWindow(800, 800, "Open_GL Triangle", NULL, NULL);
    if (!w)
    {
        glfwTerminate();
        std::cout<<"GLFW window create Error"<<std::endl;//return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(w);

    glfwSetWindowPos(w,650,220);

    glfwSwapInterval(2);

    return w;
}