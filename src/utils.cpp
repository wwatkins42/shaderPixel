#include "utils.hpp"

glm::vec4    hex2vec( int64_t hex ) {
    return glm::vec4(
        ((hex >> 16) & 0xFF) / 255.0f,
        ((hex >>  8) & 0xFF) / 255.0f,
        ((hex      ) & 0xFF) / 255.0f,
        1.0f
    );
}

glm::vec2    mousePosToClipSpace( const glm::dvec2& pos, int winWidth, int winHeight ) {
    glm::vec2    mouse = glm::vec2({(float)pos[0] / winWidth, (float)pos[1] / winHeight}) * 2.0f - 1.0f;
    mouse.y = -mouse.y;
    return (mouse);
}

// TMP
void    createCube( std::vector<GLfloat>& vertices, std::vector<GLuint>& indices ) {
    vertices = {{
        -0.5, -0.5,  0.5,
         0.5, -0.5,  0.5,
         0.5,  0.5,  0.5,
        -0.5,  0.5,  0.5,
        -0.5, -0.5, -0.5,
         0.5, -0.5, -0.5,
         0.5,  0.5, -0.5,
        -0.5,  0.5, -0.5,
    }};
    indices = {{
        0, 1, 2,  2, 3, 0,
        1, 5, 6,  6, 2, 1,
        7, 6, 5,  5, 4, 7,
        4, 0, 3,  3, 7, 4,
        4, 5, 1,  1, 0, 4,
        3, 2, 6,  6, 7, 3,
    }};
}
