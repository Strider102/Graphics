#include <stdlib.h>
#include <ctime>
#include "model.h"
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include "camera.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

//settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
static double curFrame = 0;
static double lastFrame = 0;
static double deltaTime = 0;
static bool first = true;
static float lastX = 0;
static float lastY = 0;

Camera *camera = nullptr;

// initialize window and glad
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
    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Anderson_Barks Meme Museum", nullptr, nullptr);
    if(!window){
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    windowLoc[0] = window;
    glfwMakeContextCurrent(window);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, cursor_pos_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }

    return 0;
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

    // initialize shader
    Shader shader = Shader("assets/vShader.vs", "assets/fShader.fs");
    // initialize camera
    camera = new Camera();

    shader.use();
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    // initialize model
    Model obj = Model("assets/MuseumT.obj");
    //Model obj = Model("assets/test/planet.obj");
    //Model obj = Model("assets/test.obj");
    //Model obj = Model("assets/untitled.obj");
    //Model obj = Model("assets/testing.obj");
    //Model obj = Model("assets/dik.obj");

    glm::mat4 model;

    // render loop
    // -----------
    while(!glfwWindowShouldClose(window)){
        // time used to make movement speed independent of frame rate
        curFrame = glfwGetTime();
        deltaTime = curFrame - lastFrame;
        lastFrame = curFrame;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();

        // set matrices to give a first person camera angle
        shader.setMatrix("projection", (float *)glm::value_ptr(glm::perspective(glm::radians(camera->Zoom), (float) SCR_WIDTH / (float) SCR_HEIGHT, 0.1f, 100.0f)));
        shader.setMatrix("view", (float *)glm::value_ptr(camera->GetViewMatrix()));

        model = glm::mat4();
        //model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); // translate it down so it's at the center of the scene
        //model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f)); // it's a bit too big for our scene, so scale it down
        shader.setMatrix("model", (float *)glm::value_ptr(model));

        obj.Draw(shader);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    delete camera;

    // glfw: terminate, clearing all previously allocated GLFW resources
    // -----------------------------------------------------------------
    glfwTerminate();
    return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    // escape to quit
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        exit(EXIT_SUCCESS);
    // movement using classic WASD
    if (key == GLFW_KEY_W) {
        camera->ProcessKeyboard(FORWARD, deltaTime);
    }
    if (key == GLFW_KEY_A) {
        camera->ProcessKeyboard(LEFT, deltaTime);
    }
    if (key == GLFW_KEY_D) {
        camera->ProcessKeyboard(RIGHT, deltaTime);
    }
    if (key == GLFW_KEY_S) {
        camera->ProcessKeyboard(BACKWARD, deltaTime);
    }
}

void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (first) {
        // need to initialize starting position, so first frame of input is not used
        first = false;
    } else {
        // move camera based on changes in cursor position
        camera->ProcessMouseMovement(xpos - lastX, lastY - ypos);
    }
    lastX = xpos;
    lastY = ypos;
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    // zooming
    camera->ProcessMouseScroll(yoffset);
}