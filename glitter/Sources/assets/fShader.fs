#version 150

in vec2 fTexCoord;

out vec4 FragColor;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_diffuse2;
//uniform sampler2D texture_specular;
//uniform sampler2D texture_normal;
//uniform sampler2D texture_height;

void main()
{
    //if (tid == 1) {
        FragColor = texture(texture_diffuse1, fTexCoord);
    /*} else if (tid == 2) {
        FragColor = texture(texture_diffuse2, fTexCoord);
    } else {
        FragColor = vec4(1.0f, 0.0f, 1.0f, 1.0f);
    }*/
}