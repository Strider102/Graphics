#version 150

in vec3 vPosition;
in vec3 vNormal;
in vec2 vTexCoord;
in vec3 vTangent;
in vec3 vBitangent;

out vec2 fTexCoord;

uniform mat4 camera_pos;
uniform vec4 clip_plane = vec4(1.0, 1.0, 0.0, 0.85);
uniform vec4 clip_sphere = vec4(0.0, 0.0, 0.0, 10.0);


void main()
{
    gl_ClipDistance[0] = dot(position, clip_plane);
    gl_ClipDistance[1] = length(position.xyz / position.w - clip_sphere.xyz) - clip_sphere.w;

    gl_Position = camera_pos * vec4(vPosition.x, vPosition.y, vPosition.z, 1.0);
    fTexCoord = vTexCoord;
}

