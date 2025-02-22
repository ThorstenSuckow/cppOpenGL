#version 450 core
    
out vec4 FragColor;

uniform vec3 id2ColorCode;

void main() {

    FragColor = vec4(id2ColorCode, 1.0f);

}