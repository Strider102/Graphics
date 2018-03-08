#include <stdlib.h>
#include "Object.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

//settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const unsigned int numObjects = 2;
static unsigned int curObject = 0;

const char *vertexShaderSource = "#version 150\n"
        "in vec4 vPosition;\n"
        "in vec4 vColor;\n"
        "out vec4 fColor;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vPosition;\n"
        "   fColor = vColor;\n"
        "}\0";

const char *fragmentShaderSource = "#version 150\n"
        "in vec4 fColor;\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = fColor;\n"
        "}\n\0";

int init(GLFWwindow **windowLoc, GLuint *shaderProgram)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // glfw window creation
    // --------------------
    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Anderson_Barks Model Loading and Swapping", nullptr, nullptr);
    if(!window){
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    windowLoc[0] = window;
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }

    // build and compile our shader program
    // ------------------------------------
    // vertex shader
    int successFlag = 0;
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        successFlag = -1;
    }
    // fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        successFlag = -1;
    }
    // link shaders
    *shaderProgram = glCreateProgram();
    glAttachShader(*shaderProgram, vertexShader);
    glAttachShader(*shaderProgram, fragmentShader);
    glLinkProgram(*shaderProgram);
    // check for linking errors
    glGetProgramiv(*shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(*shaderProgram, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        successFlag = -1;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glUseProgram(*shaderProgram);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    return successFlag;
}

void initObjects(unsigned int numObjects, Object **obj, GLuint *vao, GLuint shaderProgram)
{
    obj[0] = new Object("assets/cube.obj");
    obj[1] = new Object("assets/Pikachu.obj");

    glGenVertexArrays(numObjects, vao);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    for (unsigned int i = 0; i < numObjects; i++) {
        glBindVertexArray(vao[i]);
        obj[i]->load(shaderProgram);
    }
}

int main(){

    // glfw: initialize and configure
    // ------------------------------
    GLFWwindow **windowLoc = (GLFWwindow **) malloc(sizeof(GLFWwindow *));
    GLuint *shaderProgram = (GLuint *) malloc(sizeof(GLuint));
    int successFlag = init(windowLoc, shaderProgram);
    if (successFlag < 0) {
        free(windowLoc);
        free(shaderProgram);
        glfwTerminate();
        return -1;
    }
    GLFWwindow *window = windowLoc[0];
    free(windowLoc);

    Object **obj = (Object **) malloc(sizeof(Object **) * numObjects);
    GLuint *vao = (GLuint *) malloc(sizeof(GLuint *) * numObjects);
    initObjects(numObjects, obj, vao, *shaderProgram);

    // render loop
    // -----------
    while(!glfwWindowShouldClose(window)){
        // render
        // ------
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glBindVertexArray(vao[curObject]); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        obj[curObject]->draw();

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    free(shaderProgram);
    for (unsigned int i = 0; i < numObjects; i++) {
        delete obj[i];
    }
    free(obj);
    glDeleteVertexArrays(numObjects, vao);
    free(vao);

    // glfw: terminate, clearing all previously allocated GLFW resources
    // -----------------------------------------------------------------
    glfwTerminate();
    return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        exit(EXIT_SUCCESS);
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        curObject = (curObject + 1) % numObjects;
    }
}
