#version 400 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec3 aTangent;
layout (location = 4) in vec3 aBitangent;

out vec3 Normal;
out vec3 FragPos;
out vec2 TexCoords;
out mat4 Proj;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * aNormal;
    TexCoords = aTexCoords;
    Proj = projection;

    /* spherical billboarding */
    mat4 modelView = view * model;
    modelView[0].xyz = vec3(model[0][0], 0, 0);
    modelView[1].xyz = vec3(0, model[1][1], 0);
    modelView[2].xyz = vec3(0, 0, model[2][2]);
    gl_Position = projection * modelView * vec4(aPos, 1.0);
}
