#include "shader.h"
#include "renderer.h"
#include<sstream>
#include<fstream>



shader::shader(const std::string &filepath)
    :m_filepath(filepath)
{
    m_src=ParseShader();
    crtprg();
}

shader::~shader()
{
    GLCALL(glDeleteProgram(m_renderer_id));
}

ShaderProgramSource shader::ParseShader()
{
    std::stringstream ss[2];
    std::ifstream s(m_filepath);
    
    enum class ShaderType{
        None=-1, Vertex=0, Fragment=1
    };

    ShaderType type= ShaderType::None;

    std::string line;
    while(getline(s, line))
    {
        if(line.find("#shader") != std::string::npos)
        {
            if(line.find("vertex") != std::string::npos)
            type=ShaderType::Vertex;
            else if(line.find("fragment") != std::string::npos)
            type=ShaderType::Fragment;
        }
        else
        {
            ss[(int)type]<<line<<"\n";
        }
    }

    return { ss[0].str(), ss[1].str()};
}

void shader::crtprg()
{
    m_renderer_id = glCreateProgram();
    const char *vxs=m_src.VertexSource.c_str();
    const char *fgs=m_src.FragmentSource.c_str();
    unsigned int vs= compshad(GL_VERTEX_SHADER, vxs);
    unsigned int fs= compshad(GL_FRAGMENT_SHADER, fgs);
    glAttachShader(m_renderer_id, vs);
    glAttachShader(m_renderer_id, fs);
    glLinkProgram(m_renderer_id);
    glValidateProgram(m_renderer_id);

    glDeleteShader(vs);
    glDeleteShader(fs);
}

unsigned int shader::compshad(unsigned int type, const char* source)
{
    unsigned int shadid=glCreateShader(type);
    glShaderSource(shadid, 1, &source, NULL);
    glCompileShader(shadid);

    int result;
    glGetShaderiv(shadid, GL_COMPILE_STATUS, &result);
    if(result == GL_FALSE)
    {
        int length;
        glGetShaderiv(shadid, GL_INFO_LOG_LENGTH, &length);
        char *msg=(char*)alloca(length);
        int unused_vab;
        glGetShaderInfoLog(shadid, length, &unused_vab, msg);
        std::cout<<"  Failed to compile "<<(type == GL_VERTEX_SHADER? "vertex" : "fragment")<<" shader!"<<std::endl;
        std::cout<<msg<<std::endl; 
    }

    /*
    else
    {
        std::cout<<"shader compilation sucessfull !"<<std::endl;
    }*/
    

    return shadid;
}

void shader::bind() const
{
    GLCALL(glUseProgram(m_renderer_id));
}

void shader::unbind() const
{
    GLCALL(glUseProgram(0));
}

void shader::setuniform4f(const char* name, float v0, float v1, float v2, float v3)
{
    GLCALL(glUniform4f(Getuniformlocation(name), v0, v1, v2, v3));
}

void shader::setuniformMat4f(const char* name, glm::mat4& matrix)
{
    GLCALL(glUniformMatrix4fv(Getuniformlocation(name), 1, GL_FALSE, &matrix[0][0]));
}

unsigned int shader::Getuniformlocation(const char* name)
{
    if(m_uniformloc_cache.find(name) != m_uniformloc_cache.end())
        return m_uniformloc_cache[name];
    int loc=glGetUniformLocation(m_renderer_id, name);
    if(loc == -1)
        std::cout<<" Warning "<<name<<" does not exist!"<<std::endl;
    m_uniformloc_cache[name] = loc;
    return loc;
}

void shader::setuniform1i(const char* name, int value)
{
    GLCALL(glUniform1i(Getuniformlocation(name), value));
}