#pragma once

#include "Vertexbuffer.h"
class Vertexbufferlayout;

class VertexArray{
    private:
        unsigned int m_renderer_id;
    public:
        VertexArray();
        ~VertexArray();
        void Addlayout(Vertexbuffer& vb, Vertexbufferlayout& lo);
        void bind() const;
        void unbind() const;
};