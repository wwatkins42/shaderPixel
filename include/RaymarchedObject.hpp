#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <string>
#include <vector>

#include "Exception.hpp"
#include "Shader.hpp"
#include "Camera.hpp"
#include "utils.hpp"
#include "Mesh.hpp" // for material struct

typedef struct  sQuadVertex {
    glm::vec3   Position;
    glm::vec2   TexCoords;
}               tQuadVertex;

class RaymarchedObject {

public:
    RaymarchedObject( const glm::vec3& position, const glm::vec3& orientation, const glm::vec3& scale, const tMaterial& material );
    ~RaymarchedObject( void );

    void            update( void );
    void            render( Shader shader );

    /* getters */
    const glm::mat4&    getTransform( void ) const { return (transform); };
    const glm::vec3&    getPosition( void ) const { return (position); };
    const glm::vec3&    getOrientation( void ) const { return (orientation); };
    const glm::vec3&    getScale( void ) const { return (scale); };
    /* setters */
    void                setPosition( const glm::vec3& t ) { position = t; };
    void                setOrientation( const glm::vec3& r ) { orientation = r; };
    void                setScale( const glm::vec3& s ) { scale = s; };

private:
    glm::mat4                   transform;          // the transform applied to the model
    glm::vec3                   position;           // the position
    glm::vec3                   orientation;        // the orientation
    glm::vec3                   scale;              // the scale

    tMaterial                   material;
    std::vector<tQuadVertex>    vertices;
    std::vector<unsigned int>   indices;

    unsigned int                vao;
    unsigned int                vbo;
    unsigned int                ebo;

    void                        createRenderQuad( void );
    void                        setup( int mode );

};
