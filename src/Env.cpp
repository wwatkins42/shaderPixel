#include "Env.hpp"

Env::Env( void ) {
    try {
        this->initGlfwEnvironment("4.0");
        this->initGlfwWindow(1920, 1080);
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
            throw Exception::InitError("glad initialization failed");
        this->controller = new Controller(this->window.ptr);
        this->models = {{
            // new Model(
            //     "/Users/wwatkins/Downloads/workshop/source/model.obj",
            //     glm::vec3(0.0f, 0.0f, 0.0f),
            //     glm::vec3(0.0f, -M_PI/2.0f, 0.0f),
            //     glm::vec3(10.0f, 10.0f, 10.0f)
            // ),
            // new Model(
            //     "/Users/wwatkins/Downloads/stone-figure-of-xiuhcoatl-fire-serpent/source/2842228_201410112217/mesh/sculpt.obj",
            //     glm::vec3(0.0f, 0.0f, 0.0f),
            //     glm::vec3(-M_PI/2.0f, 0.0f, -M_PI/2.0f),
            //     glm::vec3(1.0f, 1.0f, 1.0f)
            // )
            // new Model(
            //     "/Users/wwatkins/Downloads/rameses-iv/source/model/model.obj",
            //     glm::vec3(0.0f, 0.0f, 0.0f),
            //     glm::vec3(-0.75, M_PI+0.25, M_PI/2.0f+0.07),
            //     glm::vec3(1.0f, 1.0f, 1.0f)
            // ),
            new Model(
                "/Users/wwatkins/Downloads/house01/source/House01.obj",
                glm::vec3(0.0f, 0.0f, 0.0f),
                glm::vec3(0.0f),
                glm::vec3(1.0f)
            ),
            new Model(
                "/Users/wwatkins/Downloads/house02/source/House02.obj",
                glm::vec3(10.0f, 0.0f, 0.0f),
                glm::vec3(0.0f),
                glm::vec3(1.0f)
            ),
            new Model(
                "/Users/wwatkins/Downloads/house03/source/House03.obj",
                glm::vec3(20.0f, 0.0f, 0.0f),
                glm::vec3(0.0f),
                glm::vec3(1.0f)
            ),
            new Model(
                "/Users/wwatkins/Downloads/house04/source/House04.obj",
                glm::vec3(30.0f, 0.0f, 0.0f),
                glm::vec3(0.0f),
                glm::vec3(1.0f)
            ),
            // new Model(
            //     "/Users/wwatkins/Downloads/center-structure/source/Center_structure.obj",
            //     glm::vec3(5.0f, 0.0f, 0.0f),
            //     glm::vec3(0.0f),
            //     glm::vec3(1.0f)
            // ),

            // new Model(
            //     "/Users/wwatkins/Downloads/pillar01/source/Pillar_LP.obj",
            //     glm::vec3(0.0f, 0.0f, 0.0f),
            //     glm::vec3(0.0f),
            //     glm::vec3(0.5f)
            // ),
            // new Model(
            //     "/Users/wwatkins/Downloads/pillar01/source/Pillar_LP.obj",
            //     glm::vec3(5.0f, 0.0f, 0.0f),
            //     glm::vec3(0.0f),
            //     glm::vec3(0.5f)
            // ),
            // new Model(
            //     "/Users/wwatkins/Downloads/pillar01/source/Pillar_LP.obj",
            //     glm::vec3(0.0f, 0.0f, 5.0f),
            //     glm::vec3(0.0f),
            //     glm::vec3(0.5f)
            // ),
            // new Model(
            //     "/Users/wwatkins/Downloads/pillar01/source/Pillar_LP.obj",
            //     glm::vec3(5.0f, 0.0f, 5.0f),
            //     glm::vec3(0.0f),
            //     glm::vec3(0.5f)
            // ),

        }};
        this->lights = {{
            new Light(
                glm::vec3(10, 10, 6),
                glm::vec3(0.77f, 0.88f, 1.0f) * 0.05f,
                glm::vec3(1.0f, 0.964f, 0.77f),
                glm::vec3(1.0f, 1.0f, 1.0f),
                eLightType::directional
            ),
            new Light(
                glm::vec3(3.0f, 1.0f, 0.0f),
                glm::vec3(0.0f, 0.0f, 0.0f),
                glm::vec3(1.0f, 0.0f, 0.0f),
                glm::vec3(1.0f, 1.0f, 1.0f),
                1.0f,
                0.09f,
                0.032f,
                eLightType::point
            ),
            // new Light(
            //     glm::vec3(-2.0f, 1.0f, 5.0f),
            //     glm::vec3(0.0f, 0.0f, 0.0f),
            //     glm::vec3(0.0f, 1.0f, 0.0f),
            //     glm::vec3(1.0f, 1.0f, 1.0f),
            //     1.0f,
            //     0.09f,
            //     0.032f,
            //     eLightType::point
            // ),
        }};
        this->skybox = new Model(std::vector<std::string>{{
            "./resource/ThickCloudsWater/ThickCloudsWaterLeft2048.png",
            "./resource/ThickCloudsWater/ThickCloudsWaterRight2048.png",
            "./resource/ThickCloudsWater/ThickCloudsWaterUp2048.png",
            "./resource/ThickCloudsWater/ThickCloudsWaterDown2048.png",
            "./resource/ThickCloudsWater/ThickCloudsWaterFront2048.png",
            "./resource/ThickCloudsWater/ThickCloudsWaterBack2048.png",
        }});

        this->setupController();
    } catch (const std::exception& err) {
        std::cout << err.what() << std::endl;
    }
}

Env::~Env( void ) {
    for (size_t i = 0; i < this->models.size(); ++i)
        delete this->models[i];
    for (size_t i = 0; i < this->lights.size(); ++i)
        delete this->lights[i];
    delete this->skybox;
    delete this->controller;
    glfwDestroyWindow(this->window.ptr);
    glfwTerminate();
}

void	Env::initGlfwEnvironment( const std::string& glVersion ) {
	if (!glfwInit())
		throw Exception::InitError("glfw initialization failed");
    if (!std::regex_match(glVersion, static_cast<std::regex>("^[0-9]{1}.[0-9]{1}$")))
        throw Exception::InitError("invalid openGL version specified");
    size_t  p = glVersion.find('.');
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, std::stoi(glVersion.substr(0,p)));
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, std::stoi(glVersion.substr(p+1)));
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
}

void	Env::initGlfwWindow( size_t width, size_t height ) {
    // glfwWindowHint(GLFW_SAMPLES, 4); // NOTE: check if anti-aliasing is slow
	if (!(this->window.ptr = glfwCreateWindow(width, height, "shaderPixel", NULL, NULL)))
        throw Exception::InitError("glfwCreateWindow failed");
	glfwMakeContextCurrent(this->window.ptr);
	glfwSetFramebufferSizeCallback(this->window.ptr, this->framebufferSizeCallback);
	glfwSetInputMode(this->window.ptr, GLFW_STICKY_KEYS, 1);
    this->window.width = width;
    this->window.height = height;
}

void    Env::setupController( void ) {
    /* set key properties here */
    this->controller->setKeyProperties(GLFW_KEY_P, eKeyMode::toggle, 1, 1000);
    // this->controller->setKeyProperties(GLFW_KEY_M, eKeyMode::cycle, 1, 300, 3);
}

void    Env::framebufferSizeCallback( GLFWwindow* window, int width, int height ) {
    glViewport(0, 0, width, height);
}

Light*  Env::getDirectionalLight( void ) {
    for (auto it = this->lights.begin(); it != this->lights.end(); it++)
        if ((*it)->getType() == eLightType::directional)
            return (*it);
    return (nullptr);
}
