#include "Mesh.hpp"
#include "glm/ext.hpp"

Mesh::Mesh( std::vector<tVertex> vertices, std::vector<unsigned int> indices, std::vector<tTexture> textures, tMaterial material ) : vertices(vertices), indices(indices), textures(textures), material(material) {
    this->setup(GL_STATIC_DRAW);
}

Mesh::~Mesh( void ) {
    // glDeleteVertexArrays(1, &this->vao); // this is the faulty part
    glDeleteBuffers(1, &this->vbo);
    glDeleteBuffers(1, &this->ebo);
}

void    Mesh::render( Shader shader ) {
    /* set material attributes */
    shader.setVec3UniformValue("material.ambient", this->material.ambient);
    shader.setVec3UniformValue("material.diffuse", this->material.diffuse);
    shader.setVec3UniformValue("material.specular", this->material.specular);
    shader.setFloatUniformValue("material.shininess", this->material.shininess);

    /* set texture attributes */
    std::array<unsigned int, 4> n = { 1, 1, 1, 1 };
    for (size_t i = 0; i < this->textures.size(); ++i) {
        if (this->textures[i].type == "skybox")
            glBindTexture(GL_TEXTURE_CUBE_MAP, this->textures[i].id);
        else {
            glActiveTexture(GL_TEXTURE0 + i);
            std::string number;
            std::string name = this->textures[i].type;
            if (name == "texture_diffuse")  number = std::to_string((n[0])++);
            if (name == "texture_specular") number = std::to_string((n[1])++);
            if (name == "texture_normal")   number = std::to_string((n[2])++);
            if (name == "texture_height")   number = std::to_string((n[3])++);
            glUniform1i(glGetUniformLocation(shader.id, (name + number).c_str()), i);
            glBindTexture(GL_TEXTURE_2D, this->textures[i].id);
        }
    }
    /* render */
    glBindVertexArray(this->vao);
    glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
    glActiveTexture(GL_TEXTURE0);
}

void    Mesh::setup( int mode ) {
    // gen buffers and vertex arrays
	glGenVertexArrays(1, &this->vao);
    glGenBuffers(1, &this->vbo);
	glGenBuffers(1, &this->ebo);
    // bind vertex array object, basically this is an object to allow us to not redo all of this process each time
    // we want to draw an object to screen, all the states we set are stored in the VAO
	glBindVertexArray(this->vao);
    // copy our vertices array in a buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(tVertex), this->vertices.data(), mode);
    // copy our indices array in a buffer for OpenGL to use
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(unsigned int), this->indices.data(), mode);
    // set the vertex attribute pointers:
    // position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(tVertex), (void*)0);
    // normal coord attributes
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(tVertex), (void*)offsetof(tVertex, Normal));
    // texture coord attribute
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(tVertex), (void*)offsetof(tVertex, TexCoords));
    // vertex color attribute
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(tVertex), (void*)(offsetof(tVertex, Colors)));
    // glEnableVertexAttribArray(3);
    // glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(tVertex), reinterpret_cast<GLvoid*>(offsetof(tVertex, Tangent)));
    // glEnableVertexAttribArray(4);
    // glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(tVertex), reinterpret_cast<GLvoid*>(offsetof(tVertex, Bitangent)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
