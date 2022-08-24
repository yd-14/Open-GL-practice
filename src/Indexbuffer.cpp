#include "Indexbuffer.h"
#include "renderer.h"

Indexbuffer::Indexbuffer(unsigned int* data, unsigned int count)
    :m_count(count)
{
    GLCALL(glGenBuffers(1, &m_renderer_id));
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderer_id));
    
    GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count*sizeof(unsigned int), data, GL_STATIC_DRAW));
}

Indexbuffer::~Indexbuffer()
{
    GLCALL(glDeleteBuffers(1, &m_renderer_id));
}

void Indexbuffer::bind() const
{
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderer_id));
}

void Indexbuffer::unbind() const
{
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}