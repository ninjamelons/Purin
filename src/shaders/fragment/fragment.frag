#version 400 core
out vec4 FragColor;

in vec3 vertexColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

uniform float mixInterpolate;

void main()
{
    FragColor = mix(texture(texture1, TexCoord)
        ,texture(texture2, vec2(-TexCoord.x, TexCoord.y))
        , mixInterpolate)
        * vec4(vertexColor, 1.0);
}