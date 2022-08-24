#pragma once

class Vertexbuffer{
    private:
        unsigned int m_renderer_id;
    public:
        Vertexbuffer(const void* data, unsigned int size);
        ~Vertexbuffer();
    void bind() const;
    void unbind() const;
    void add_data(const void* data, unsigned int size, unsigned int offset) const;        
};