#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <regex>

#include "Exception.hpp"
#include "Controller.hpp"
#include "Model.hpp"
#include "Raymarched.hpp"
#include "RaymarchedSurface.hpp"
#include "Light.hpp"

typedef struct  s_window {
    GLFWwindow* ptr;
    int         width;
    int         height;
}               t_window;

class Env {

public:
    Env( void );
    ~Env( void );

    const t_window&                     getWindow( void ) const { return (window); };
    Controller*                         getController( void ) { return (controller); };
    std::vector<Model*>&                getModels( void ) { return (models); };
    Raymarched*                         getRaymarched( void ) { return (raymarched); };
    std::vector<RaymarchedSurface*>&    getRaymarchedSurfaces( void ) { return (raymarchedSurfaces); };
    std::vector<RaymarchedSurface*>&    getTexturedSurfaces( void ) { return (texturedSurfaces); };
    std::vector<Light*>&                getLights( void ) { return (lights); };
    Model*                              getSkybox( void ) { return (skybox); };
    Light*                              getDirectionalLight( void );

private:
    t_window                        window;
    Controller*                     controller;
    std::vector<Model*>             models;
    std::vector<Light*>             lights;
    Model*                          skybox;
    Raymarched*                     raymarched;
    std::vector<RaymarchedSurface*> raymarchedSurfaces;
    std::vector<RaymarchedSurface*> texturedSurfaces;
    unsigned int                    skyboxTexture;
    unsigned int                    noiseTexture;

    void        initGlfwEnvironment( const std::string& glVersion = "4.0" );
    void        initGlfwWindow( size_t width, size_t height );
    void        setupController( void );
    // callback to be called each time the window is resized to update the viewport size as well
    static void framebufferSizeCallback( GLFWwindow* window, int width, int height );

};
