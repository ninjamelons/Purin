#version 400 core
out vec4 FragColor;

in vec3 vertexColor; // the input variable from the vertex shader (same name and same type)
in vec3 vertexPosition;

//uniform vec4 globalColor; // Global across all shaders

void main()
{
    FragColor = vec4(vertexColor, 1.0);
    //FragColor = vec4(vertexPosition, 1.0);
}