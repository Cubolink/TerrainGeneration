#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 v_color;

out vec4 pre_color;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
    gl_Position = projection * view * model * position;
    pre_color = v_color;
}

#shader fragment
#version 330 core

in vec4 pre_color;
out vec4 color;

void main()
{
    color = pre_color;
}
