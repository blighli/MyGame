#version 450 core

layout (location = 0) in vec4 pos;
layout (location = 1) in vec4 color;

out vec4 vert_color;

void main(){
    gl_Position = pos;
    vert_color = color;
}
