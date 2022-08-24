#pragma once
#include<iostream>
#include<unordered_map>
#include<glm/glm.hpp>

struct ShaderProgramSource{
    std::string VertexSource;
    std::string FragmentSource;
};

class shader{
    private:
        unsigned int m_renderer_id;
        const std::string m_filepath;
        ShaderProgramSource m_src;
        std::unordered_map<std::string,int> m_uniformloc_cache;
    public:
        shader(const std::string &filepath);
        ~shader();
        void bind() const;
        void unbind() const;
        void setuniform4f(const char* name, float v0, float v1, float v2, float v3);
        void setuniformMat4f(const char* name, glm::mat4& matrix);
        void setuniform1i(const char* name, int value);
        inline const std::string Getfilepath() const { return m_filepath; }
    private:
        void crtprg();
        unsigned int compshad(unsigned int type, const char* source);
        ShaderProgramSource ParseShader();
        unsigned int Getuniformlocation(const char* name);
};