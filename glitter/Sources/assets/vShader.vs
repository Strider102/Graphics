#version 150

in vec4 vPosition;
in vec4 vColor;

out vec4 fColor;

uniform mat4 camera_pos;

void main()
{
   gl_Position = camera_pos * vPosition;
   fColor = vColor;
}

