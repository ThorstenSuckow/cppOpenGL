#version 450 core
    
out vec4 FragColor;

uniform vec3 sinColor;

void main() {

    FragColor = vec4(sinColor, 1.0f);

}