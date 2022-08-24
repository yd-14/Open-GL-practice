#include<vector>
#include "renderer.h"

struct VertexElement{
    unsigned int type;
    unsigned int count;
    unsigned char normalized;

    static unsigned int Getsizeoftype(unsigned int type)
    {
        switch(type)
        {
            case GL_FLOAT: return 4;
            case GL_UNSIGNED_INT: return 4;
            case GL_UNSIGNED_BYTE: return 1;
        }
        return 0;
        assert(false);
    }    
};

class Vertexbufferlayout{
    private:
        std::vector<VertexElement> m_Elements;
        unsigned int m_stride;
    public:
        Vertexbufferlayout()
            :m_stride(0){}

        template <typename T>
        void Push(unsigned int count){}
                    
        inline unsigned int Getstride() const { return m_stride;}
        
        inline const std::vector<VertexElement> Getelement() const { return m_Elements;}

};

template<>
    inline void Vertexbufferlayout::Push<float> (unsigned int count)
    {
        m_Elements.push_back({GL_FLOAT, count, GL_FALSE});
        m_stride += count * sizeof(float);
    }

template<>
    inline void Vertexbufferlayout::Push<unsigned int> (unsigned int count)
    {
        m_Elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
        m_stride += count * sizeof(unsigned int);
    }

template<>
    inline void Vertexbufferlayout::Push<unsigned char> (unsigned int count)
    {
        m_Elements.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE});
        m_stride += count * sizeof(unsigned char);
    }
