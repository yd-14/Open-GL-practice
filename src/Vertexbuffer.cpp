#include "Vertexbuffer.h"

#include "renderer.h"


Vertexbuffer::Vertexbuffer(const void* data, unsigned int size)
{
    GLCALL(glGenBuffers(1, &m_renderer_id));
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, m_renderer_id));

    GLCALL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

Vertexbuffer::~Vertexbuffer()
{
    GLCALL(glDeleteBuffers(1, &m_renderer_id));
}

void Vertexbuffer::bind() const
{
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, m_renderer_id));
}

void Vertexbuffer::unbind() const
{
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void Vertexbuffer::add_data(const void* data, unsigned int size, unsigned int offset) const
{
    bind();
    GLCALL(glBufferSubData(GL_ARRAY_BUFFER, offset, size, data));
    unbind();
}