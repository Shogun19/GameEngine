// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <glm/glm.hpp>
// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
#include <common/objloader.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <common/shader.hpp>
#include "common/texture.hpp"

class Mesh
{
    public:
        
        Mesh(const std::string &filename, std::string name_)
        {

            if (filename != "")
            {

                this->name = name_;

                parent = nullptr;

                bool success = loadOFF(filename, vertices, indices, triangles);
                if (!success)
                {
                    std::cout << "Mesh load failed" << std::endl;
                }
                
                // Generate and bind VAO
                glGenVertexArrays(1, &vao);
                glBindVertexArray(vao);

                // Generate and bind VBO for vertices
                glGenBuffers(1, &vbo_vertices);
                glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
                glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);

                // Set vertex attribute pointers
                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
                glEnableVertexAttribArray(0);

                // Generate and bind VBO for indices
                glGenBuffers(1, &vbo_indices);
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_indices);
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), indices.data(), GL_STATIC_DRAW);
            }

            // Local Transform matrix, identity at start
            localTransformMatrix = glm::mat4(1.0f);

            // Load shaders
            shaderProgram = LoadShaders("vertex_shader.glsl", "fragment_shader.glsl");
        }
        
        ~Mesh()
        {
            glDeleteBuffers(1, &vbo_vertices);
            glDeleteBuffers(1, &vbo_indices);
            glDeleteVertexArrays(1, &vao);
            glDeleteProgram(shaderProgram);
            for (Mesh *child : childs)
            {
                delete child;
            }
        }

        void addChild(Mesh *child)
        {
            child->parent = this;
            childs.push_back(child);
        }

        void translate(const glm::vec3 &translation)
        {
            localTransformMatrix = glm::translate(localTransformMatrix, translation);
        }

        void scale(const glm::vec3 &scale)
        {
            localTransformMatrix = glm::scale(localTransformMatrix, scale);
        }

        void rotate(float angle, const glm::vec3 &axis)
        {
            localTransformMatrix = glm::rotate(localTransformMatrix, angle, axis);
        }

        void draw() const
        {
            glBindVertexArray(vao);

            GLint transformLoc = glGetUniformLocation(shaderProgram, "localTransformMatrix");
            GLint isMeshLoc = glGetUniformLocation(shaderProgram, "isMesh");

            glUniformMatrix4fv(transformLoc, 1, false, &getGlobalTransform()[0][0]);
            glUniform1i(isMeshLoc, true);

            glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_SHORT, 0);

            for (const Mesh *child : childs)
            {
                child->draw();
            }
        }

        void setTransform(const glm::mat4 &transform) { localTransformMatrix = transform; }
        const glm::mat4 &getTransform() const { return localTransformMatrix; }

    private:
        std::string name;

        GLuint vao;
        GLuint vbo_vertices;
        GLuint vbo_indices;
        GLuint shaderProgram;
        
        std::vector<glm::vec3> vertices;
        std::vector<unsigned short> indices;
        std::vector<std::vector<unsigned short>> triangles;
        
        glm::mat4 localTransformMatrix;
        
        Mesh *parent;
        std::vector<Mesh *> childs;


        glm::mat4 getGlobalTransform() const
        {
            if (parent == nullptr)
            {
                return localTransformMatrix;
            }
            else
            {
                return parent->getGlobalTransform() * localTransformMatrix;
            }
        }
};
