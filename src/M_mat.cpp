#include "M_mat.h"

#include<glm/gtc/matrix_transform.hpp>
#include<iostream>

M_mat::M_mat()
{
    m_mat=glm::mat4(1);
}

M_mat::~M_mat()
{
    
}

void M_mat::rotate(char axis, float angle)
{
    glm::vec3 ax;
        if(axis == 'x')
            ax=glm::vec3(1.0f, 0.0f, 0.0f);
        else if(axis == 'y')
            ax=glm::vec3(0.0f, 1.0f, 0.0f); 
        else if(axis == 'z')
            ax=glm::vec3(0.0f, 0.0f, 1.0f); 
    m_mat = glm::rotate(glm::mat4(1), glm::radians(angle), ax) * m_mat;
}

void M_mat::scale(char axis, float scale_factor)
{
    glm::vec3 ax;
        if(axis == 'x')
            ax=glm::vec3(scale_factor, 1.0f, 1.0f);
        else if(axis == 'y')
            ax=glm::vec3(1.0f, scale_factor, 1.0f); 
        else if(axis == 'z')
            ax=glm::vec3(1.0f, 1.0f, scale_factor);

    m_mat=glm::scale(glm::mat4(1), ax) * m_mat;
}

void M_mat::translate(char axis, float distance)
{
     glm::vec3 ax;
        if(axis == 'x')
            ax=glm::vec3(distance, 0.0f, 0.0f);
        else if(axis == 'y')
            ax=glm::vec3(0.0f, distance, 0.0f); 
        else if(axis == 'z')
            ax=glm::vec3(0.0f, 0.0f, distance); 

    m_mat = glm::translate(glm::mat4(1), ax) * m_mat;
}

void M_mat::display_mat()
{
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            std::cout<<m_mat[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
}
