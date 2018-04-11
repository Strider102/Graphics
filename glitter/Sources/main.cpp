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
static float lastX = 0;
static float lastY = 0;

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

    Shader shader = Shader("assets/vShader.vs", "assets/fShader.fs");
    camera = new Camera();

    shader.use();
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    //Model obj = Model("assets/MuseumT.obj");
    Model obj = Model("assets/test/planet.obj");

    glm::mat4 model;

    // render loop
    // -----------
    while(!glfwWindowShouldClose(window)){
        // render
        // ------
        curFrame = glfwGetTime();
        deltaTime = curFrame - lastFrame;
        lastFrame = curFrame;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();

        shader.setMatrix("projection", (float *)glm::value_ptr(glm::perspective(glm::radians(camera->Zoom), (float) SCR_WIDTH / (float) SCR_HEIGHT, 0.1f, 100.0f)));
        shader.setMatrix("view", (float *)glm::value_ptr(camera->GetViewMatrix()));

        model = glm::mat4();
        //model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); // translate it down so it's at the center of the scene
        //model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// it's a bit too big for our scene, so scale it down
        shader.setMatrix("model", (float *)glm::value_ptr(model));

        //glBindVertexArray(vao[curObject]); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
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
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        exit(EXIT_SUCCESS);
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        //curObject = (curObject + 1) % numObjects;
    }
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
    camera->ProcessMouseMovement(xpos - lastX, lastY - ypos);
    lastX = xpos;
    lastY = ypos;
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera->ProcessMouseScroll(yoffset);
}