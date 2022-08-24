#include<renderer.h>
#include<iostream>


void GLclearerror()
{
    while(glGetError() != GL_NO_ERROR);
}

bool Geterr()
{
    while(GLenum err=glGetError())
    {
        std::cout<<"   ***\nOpenGL error: "<<err<<std::endl; 
        return false;
    };
    return true;
}

void renderer::draw_indices(const VertexArray& va, const Indexbuffer& ib, const shader& sd, int height, int width) const
{
    sd.bind();        
    va.bind();
    ib.bind();
    glViewport(0, 0, width, height);
    GLCALL(glDrawElements(GL_TRIANGLES, ib.getcount(), GL_UNSIGNED_INT, nullptr));
}

void renderer::draw_positions(const VertexArray& va, const shader& sd, const Vertexbuffer& vb, int height, int width, unsigned int start_index) const
{
    sd.bind();        
    va.bind();
    vb.bind();
    glViewport(0, 0, width, height);
    GLCALL(glDrawArrays(GL_TRIANGLES, start_index, 3));
}

void renderer::clear() const
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}