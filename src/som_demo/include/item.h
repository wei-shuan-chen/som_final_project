#ifndef ITEM_H
#define ITEM_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include "Vertex.h"
#include "logger.h"
using namespace std;
class Item{
public:

    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;

    Item(){

    }
    Item(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices = {})
        :VAO(0), VBO(0), EBO(0)
    {
        glGenVertexArrays(1,&VAO);
        glGenBuffers(1,&VBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER,VBO);
        glBufferData(GL_ARRAY_BUFFER,vertices.size()*sizeof(Vertex),vertices.data(),GL_STATIC_DRAW);

        if( !indices.empty() ){
            glGenBuffers(1,&EBO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER,indices.size()*sizeof(unsigned int),indices.data(),GL_STATIC_DRAW);
        }

        //attribute
        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), offsetof(Vertex, position));
        glEnableVertexAttribArray(0);
        // normal attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        // collor attribute
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);
        // tex attribute
        glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(9 * sizeof(float)));
        glEnableVertexAttribArray(3);
    }
    Item(const Item& model){
        log_warn("new");
        // this->VAO = model.VAO;
        // this->VBO = model.VBO;
        // this->EBO = model.EBO;
    }
    Item& operator= (const Item& model){

        unsigned int newVAO;

        glGenVertexArrays(1,&newVAO);

        glBindVertexArray(newVAO);
        glBindBuffer(GL_ARRAY_BUFFER,model.VBO);
        // GLint vb = -1;
        // glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &vb);
        // log_debug("Vertex Array Binding = %d", vb);
        // GLint size = 0;
        // glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
        // log_debug("BufferSize=%d", size);

        //attribute
        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), offsetof(Vertex, position));
        glEnableVertexAttribArray(0);
        // normal attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        // collor attribute
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);
        // tex attribute
        glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(9 * sizeof(float)));
        glEnableVertexAttribArray(3);

        this->VAO = newVAO;
        this->VBO = model.VBO;
        this->EBO = model.EBO;
        return *this;
    }
    ~Item() {
        glDeleteVertexArrays(1, &VAO);

    }
    void renewVBO(const std::vector<Vertex>& vertices){
        glDeleteBuffers(1, &VBO);

        glBindVertexArray(VAO);
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(Vertex), vertices.data(), GL_DYNAMIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), offsetof(Vertex, position));
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(6 * sizeof(float)));
        glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(9 * sizeof(float)));
        // glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size()*sizeof(Vertex), vertices.data());
    }

    void Item_del(){
        glDeleteBuffers(1, &VBO);
        if (EBO != 0) {
            glDeleteBuffers(1, &EBO);
        }
    }

};



#endif
