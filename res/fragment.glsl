#version 330 core
in vec3 ourColor;
out vec4 color;
uniform float aAplha;

void main(){
    color=vec4(ourColor.x,aAplha,ourColor.z,1.f);
}