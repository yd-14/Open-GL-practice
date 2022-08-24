#include<stdint.h>

#include "VertexArray.h"
#include "Vertexbufferlayout.h"

VertexArray::VertexArray()
{
    GLCALL(glGenVertexArrays(1, &m_renderer_id));
}

VertexArray::~VertexArray()
{
    GLCALL(glDeleteVertexArrays(1, &m_renderer_id));
}

void VertexArray::Addlayout(Vertexbuffer& vb, Vertexbufferlayout& lo)
{
    bind();
    vb.bind();
    const auto& elements=lo.Getelement();
    unsigned int offset=0;
    for(unsigned int i=0; i < elements.size(); i++)
    {
        const auto& element=elements[i];
        GLCALL(glEnableVertexAttribArray(i));
        GLCALL(glVertexAttribPointer(i, element.count, element.type, element.normalized, lo.Getstride(), (const void*) (intptr_t) offset));
        offset += element.count * VertexElement::Getsizeoftype(element.type);
    }
}

void VertexArray::bind() const
{
    GLCALL(glBindVertexArray(m_renderer_id));
}

void VertexArray::unbind() const
{
    GLCALL(glBindVertexArray(0));
}