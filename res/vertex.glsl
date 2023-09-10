#version 330 core
layout(location=0) in vec3 aPos;
layout(location=1) in vec3 aColor;

uniform mat4 world;
uniform mat4 view;
uniform mat4 projection;

out vec3 ourColor;
out vec3 FragPos;

void main(){
    FragPos = vec3(world * vec4(aPos, 1.0));
    gl_Position = projection * view * vec4(FragPos, 1.0f);
    ourColor = aColor;
}