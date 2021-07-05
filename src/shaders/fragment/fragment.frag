#version 400 core
out vec4 FragColor;

in vec3 vertexColor; // the input variable from the vertex shader (same name and same type)

//uniform vec4 globalColor; // Global across all shaders

void main()
{
    FragColor = vec4(vertexColor, 1.0);
}