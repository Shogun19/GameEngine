#include "utils.cpp"

Mesh *genScene1()
{

    Mesh *sun = new Mesh("../mesh/off/sphere.off", "sun");
    Mesh *earth = new Mesh("../mesh/off/sphere.off", "earth");
    Mesh *moon = new Mesh("../mesh/off/sphere.off", "moon");

    sun->addChild(earth);
    earth->addChild(moon);

    sun->translate(glm::vec3(0., 1.3, 0.));
    sun->scale(glm::vec3(0.3));
    sun->rotate(glfwGetTime()*0.5, glm::vec3(0., 1, 0.2));

    earth->translate(glm::vec3(-4, 0, 0));
    earth->scale(glm::vec3(0.5));
    earth->rotate(glfwGetTime() * 0.25f, glm::vec3(0., 1, 0.2));
    earth->rotate(glm::radians(23.0f), glm::vec3(1.0f, 0.0f, 0.0f)); 

    moon->translate(glm::vec3(2, 0, 0));
    moon->scale(glm::vec3(0.2));
    moon->rotate(glm::radians(6.0f), glm::vec3(0.0f, 1.0f, 1.0f)); 
    return sun;
}
