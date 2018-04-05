#version 150

in vec2 fTexCoord;

out vec4 FragColor;

uniform sampler2D texture_diffuse1;

void main()
{
    FragColor = texture(texture_diffuse1, fTexCoord);
}