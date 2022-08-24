#pragma once

#define GLEW_STATIC
#include<GL/glew.h>
#include<assert.h>
#include<GLFW/glfw3.h>
#include "VertexArray.h"
#include "Indexbuffer.h"
#include "Vertexbuffer.h"
#include "shader.h"

#define GLCALL(x) GLclearerror();\
        x;\
        if(Geterr()==false)\
        {\
            glfwTerminate();\
            _assert(#x,__FILE__,__LINE__);\
        } 


void GLclearerror();

bool Geterr();

class renderer{
    public:
        void draw_indices(const VertexArray& va, const Indexbuffer& ib, const shader& sd, int height, int width) const;
        void draw_positions(const VertexArray& va, const shader& sd, const Vertexbuffer& vb, int height, int width, unsigned int start_index) const;
        void clear() const;
};