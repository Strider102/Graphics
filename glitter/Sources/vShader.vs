const char *vertexShaderSource = "#version 150\n"
        "in vec4 vPosition;\n"
        "in vec4 vColor;\n"
        "out vec4 fColor;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vPosition;\n"
        "   fColor = vColor;\n"
        "}\0";

