#version 150

in vec3 vPosition;
in vec3 vNormal;
in vec2 vTexCoord;
in vec3 vTangent;
in vec3 vBitangent;

out vec3 fPosition;
out vec3 fNormal;
out vec2 fTexCoord;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

uniform vec4 clip_plane = vec4(1.0, 1.0, 0.0, 0.85);
uniform vec4 clip_sphere = vec4(0.0, 0.0, 0.0, 10.0);

void main()
{
    gl_ClipDistance[0] = dot(vec4(vPosition, 1.0), clip_plane);
    gl_ClipDistance[1] = length(vPosition.xyz / 1.0 - clip_sphere.xyz) - clip_sphere.w;

    fPosition = vPosition;
    fNormal = vNormal;
    fTexCoord = vTexCoord;
    gl_Position = projection * view * vec4(vPosition, 1.0);
}

