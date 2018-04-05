#version 150

in vec3 vPosition;
in vec3 vNormal;
in vec2 vTexCoord;
in vec3 vTangent;
in vec3 vBitangent;

out vec2 fTexCoord;

uniform mat4 camera_pos;

void main()
{
    gl_Position = camera_pos * vec4(vPosition.x, vPosition.y, vPosition.z, 1.0);
    fTexCoord = vTexCoord;
}

