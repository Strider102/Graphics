#include <stdlib.h>
#include "Object.h"
#include "shader.h"
#include "camera.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void cursor_pos_callback(GLFWwindow* winddow, double xpos, double ypos);

//settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const unsigned int numObjects = 2;
static unsigned int curObject = 0;

Camera *camera = nullptr;

int init(GLFWwindow **windowLoc)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
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
    glfwSetCursorPosCallback(window, cursor_pos_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }

    return 0;
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
    int successFlag = init(windowLoc);
    if (successFlag < 0) {
        free(windowLoc);
        glfwTerminate();
        return -1;
    }
    GLFWwindow *window = windowLoc[0];
    free(windowLoc);

    Shader shader = Shader("assets/vShader.vs", "assets/fShader.fs");
    camera = new Camera();

    Object **obj = (Object **) malloc(sizeof(Object **) * numObjects);
    GLuint *vao = (GLuint *) malloc(sizeof(GLuint *) * numObjects);
    initObjects(numObjects, obj, vao, shader.ID);

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
    for (unsigned int i = 0; i < numObjects; i++) {
        delete obj[i];
    }
    free(obj);
    glDeleteVertexArrays(numObjects, vao);
    free(vao);
    delete camera;

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

void cursor_pos_callback(GLFWwindow* winddow, double xpos, double ypos)
{
    //camera->ProcessMouseMovement(xpos, ypos);
}
