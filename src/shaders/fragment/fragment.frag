#version 400 core
out vec4 FragColor;

in vec3 vertexColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

uniform float mixInterpolate;

void main()
{
    FragColor = texture(texture1, TexCoord);
    FragColor += mixInterpolate * texture(texture2, TexCoord) * vec4(vertexColor, 1.0);
}