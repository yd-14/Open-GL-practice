#define GLEW_STATIC
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>

#include "Vertexbuffer.h"
#include "Indexbuffer.h"
#include "crtwin.h"
#include "VertexArray.h"
#include "shader.h"
#include "renderer.h"
#include "Vertexbufferlayout.h"
#include "M_mat.h"

M_mat cam;


void keycall(GLFWwindow* win, int key, int scancode, int action, int mods)
{
    switch (key)
    {
    case GLFW_KEY_UP:
        cam.rotate('x',20.0);
        break;
    case GLFW_KEY_DOWN:
        cam.reset();
        break;
    }
}



int main(void)
{
    GLFWwindow* window=create_window();
    glfwSetKeyCallback(window, keycall);

    if(GLEW_OK != glewInit())
      std::cout<<"Glew not ok!";
    
    GLCALL(glEnable(GL_DEPTH_TEST));

    GLCALL(glEnable(GL_BLEND));
    GLCALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));  
    
    {   // start of scope for vbo and ibo

    unsigned int indices[]={
         0, 2, 4,   2, 4, 6, //face:1 red
         1, 3, 5,   3, 5, 7, //face:2 red
         8, 9,12,   9,12,13, //face:3 blue
        10,11,14,  11,14,15, //face:4 blue
        16,17,18,  17,18,19, //face:5 green
        20,21,22,  21,22,23  //face:6 green
    };
    
    float pos[] = {
            -1.0f, -1.0f, -1.0f,//0
             1.0f, 0.0f, 0.0f,

            -1.0f, -1.0f,  1.0f,//1
             1.0f, 0.0f, 0.0f,

            -1.0f,  1.0f, -1.0f,//2
            1.0f, 0.0f, 0.0f,

            -1.0f,  1.0f,  1.0f,//3
            1.0f, 0.0f, 0.0f,

             1.0f, -1.0f, -1.0f,//4
            1.0f, 0.0f, 0.0f,

             1.0f, -1.0f,  1.0f,//5
            1.0f, 0.0f, 0.0f,

             1.0f,  1.0f, -1.0f,//6
            1.0f, 0.0f, 0.0f,

             1.0f,  1.0f,  1.0f,//7
            1.0f, 0.0f, 0.0f,

            -1.0f, -1.0f, -1.0f,//8
             0.0f, 0.0f, 1.0f,

            -1.0f, -1.0f,  1.0f,//9
             0.0f, 0.0f, 1.0f,

            -1.0f,  1.0f, -1.0f,//10
            0.0f, 0.0f, 1.0f,

            -1.0f,  1.0f,  1.0f,//11
            0.0f, 0.0f, 1.0f,

             1.0f, -1.0f, -1.0f,//12
            0.0f, 0.0f, 1.0f,

             1.0f, -1.0f,  1.0f,//13
            0.0f, 0.0f, 1.0f,

             1.0f,  1.0f, -1.0f,//14
            0.0f, 0.0f, 1.0f,

             1.0f,  1.0f,  1.0f,//15
            0.0f, 0.0f, 1.0f,

            -1.0f, -1.0f, -1.0f,//16
             0.0f, 1.0f, 0.0f,

            -1.0f, -1.0f,  1.0f,//17
             0.0f, 1.0f, 0.0f,

            -1.0f,  1.0f, -1.0f,//18
            1.0f, 1.0f, 0.0f,

            -1.0f,  1.0f,  1.0f,//19
            0.0f, 1.0f, 0.0f,

             1.0f, -1.0f, -1.0f,//20
            0.0f, 1.0f, 0.0f,

             1.0f, -1.0f,  1.0f,//21
            0.0f, 1.0f, 0.0f,

             1.0f,  1.0f, -1.0f,//22
            0.0f, 1.0f, 0.0f,

             1.0f,  1.0f,  1.0f,//23
            0.0f, 1.0f, 0.0f   
    };
    

    VertexArray va;
    Vertexbuffer vbo(pos, 24*6*sizeof(float));

    Vertexbufferlayout lo;
    lo.Push<float>(3);
    lo.Push<float>(3);
    va.Addlayout(vbo, lo);

    Indexbuffer ibo(indices, 36);
    
    shader sd("shaders\\basic.shader");
    sd.bind();    

    std::cout<<glGetString(GL_VERSION)<<std::endl;

    sd.unbind();
    va.unbind();
    vbo.unbind();
    ibo.unbind();

    renderer rd;        

    int height, width;

    glm::mat4 translate_mat= glm::translate(glm::mat4(1), glm::vec3(0.0f, 0.0f, -4.0f));
    glm::mat4 project_mat(1.0f, 0.0f,  0.0f, 0.0f,
                          0.0f, 1.0f,  0.0f, 0.0f,
                          0.0f, 0.0f,  1.0f, 0.0f,
                          0.0f, 0.0f, -1.0f, 0.0f) ;


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        rd.clear();

        sd.bind();  

        glfwGetWindowSize(window, &width, &height);
        glm::mat4 projectivemat= glm::perspective(glm::radians(60.0f), ((float)width) / height, 0.1f, 10.0f);    

        glm::mat4 lastmat = projectivemat * translate_mat * cam.m_mat;


        sd.setuniformMat4f("final_mat", lastmat);
         
        rd.draw_indices(va, ibo, sd, height, width);


        // Swap front and back buffers 
        glfwSwapBuffers(window);

        // Poll for and process events 
        glfwPollEvents();
    }

    } //end of scope for vbo and ibo so that OpenGL context is valid when destructors are called

    glfwTerminate();
    return 0;
}