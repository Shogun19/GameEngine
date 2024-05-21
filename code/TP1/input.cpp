#ifndef INPUT_CPP
#define INPUT_CPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#include "TP1/variables.cpp"
#include "TP1/utils.cpp"

void processInput(GLFWwindow *window)
{
    float cameraSpeed = 2.5 * deltaTime;

    //----------------------------------- Camera Movements -----------------------------------//

    // UP
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        camera_position += cameraSpeed * camera_up;
    }

    // DOWN
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        camera_position -= cameraSpeed * camera_up;
    }

    // RIGHT
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        glm::vec3 rightVector = -glm::normalize(glm::cross(camera_up, camera_target));
        camera_position += cameraSpeed * rightVector;
    }

    // LEFT
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        glm::vec3 leftVector = glm::normalize(glm::cross(camera_up, camera_target));
        camera_position += cameraSpeed * leftVector;
    }

    // FRONT
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera_position += cameraSpeed * camera_target;
    }

    // BACK
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera_position -= cameraSpeed * camera_target;
    }

    //---------------------------------- Camera Orbit Speed ----------------------------------//
    
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
    {
        cameraOrbitSpeed+=0.001;
    }

    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
    {
        cameraOrbitSpeed-=0.001;
    }

    //------------------------------------- Camera Orbit -------------------------------------//

    static bool isOrbiting = false;

    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
    {
        isOrbiting = true;
        cameraOrbitSpeed=0.001;
    }

    if (isOrbiting)
    {
        targetMesh_fast(indexed_vertices);

        float radius = glm::distance(camera_position, camera_target);
        float horizontalAngle = atan2(camera_position.z - camera_target.z, camera_position.x - camera_target.x);
        float verticalAngle = atan2(camera_position.y - camera_target.y+5, radius/1.1);
    
        horizontalAngle -= cameraOrbitSpeed;

        float newCameraPosX = camera_target.x + radius * cos(verticalAngle) * cos(horizontalAngle);
        float newCameraPosY = camera_target.y + radius * sin(verticalAngle);
        float newCameraPosZ = camera_target.z + radius * cos(verticalAngle) * sin(horizontalAngle);

        camera_position = glm::vec3(newCameraPosX, newCameraPosY, newCameraPosZ);
    }

    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
    {
        isOrbiting = false;
    }

    //----------------------------------- Plane Resolution -----------------------------------//

    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS )
    {
        resolution++;
    }
    if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
    {
        if(resolution > 1)
        resolution--;
    }

    //------------------------------------ Rendering Mode ------------------------------------//

    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
    {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }

    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
    {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    //----------------------------------------- Exit -----------------------------------------//

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
#endif