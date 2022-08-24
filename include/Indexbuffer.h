#pragma once

//extern GLFWwindow* window;

class Indexbuffer{
    private:
        unsigned int m_renderer_id;
        unsigned int m_count;
    public:
        Indexbuffer(unsigned int* data, unsigned int count);
        ~Indexbuffer();
    void bind() const;
    void unbind() const;

    inline unsigned int getcount() const{ return m_count;}        
};