#shader vertex
#version 330 core
layout(location=0) in vec3 pos;
layout(location=1) in vec3 u_Color;

uniform mat4 final_mat;
out vec4 theColor;

void main()
{
    vec4 p=vec4(pos, 1.0);
    gl_Position=final_mat * p;
    theColor= vec4(u_Color, 1.0);
}

#shader fragment
#version 330 core

in vec4 theColor;
out vec4 color;


void main()
{
    color = theColor;
}