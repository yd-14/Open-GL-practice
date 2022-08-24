#pragma once

#include<glm/glm.hpp>

class M_mat{
    public:
    glm::mat4 m_mat;
    M_mat();
    ~M_mat();
    void rotate(char axis, float angle);
    void scale(char axis, float scale_factor);
    void translate(char axis, float distance);
    void display_mat();
    inline void reset(){m_mat=glm::mat4(1);}
};

