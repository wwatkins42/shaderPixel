#include "Env.hpp"

/* Models from :
    https://sketchfab.com/models/192bf30a7e28425ab385aef19769d4b0
    https://sketchfab.com/models/5cfc211a49164bf2835a121b5069ee08
*/

Env::Env( void ) {
    try {
        this->initGlfwEnvironment("4.0");
        // this->initGlfwWindow(480, 480);
        this->initGlfwWindow(720, 480);
        // this->initGlfwWindow(1280, 720);
        // this->initGlfwWindow(2560, 1200);
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
            throw Exception::InitError("glad initialization failed");
        this->controller = new Controller(this->window.ptr);
        this->models = {{
            new Model(
                "./resource/models/Inn/theInn.FBX.obj",
                glm::vec3(0.0f, 2.0f, 0.0f),
                glm::vec3(0.0f),
                glm::vec3(75.0f)
            ),
            new Model( /* stand emplacement 1 - Marble */
                "./resource/models/Crystal/crystal.obj",
                glm::vec3(10.0f, -0.75f, 14.f),
                glm::vec3(0.0f),
                glm::vec3(2.5f)
            ),
            new Model( /* stand emplacement 2 - IFS */
                "./resource/models/Crystal/crystal.obj",
                glm::vec3(11.3f, 1.15f, -17.65f),
                glm::vec3(0.0f, 1.0f, 0.0f),
                glm::vec3(3.0f)
            ),
            new Model( /* stand emplacement 3 - Mandelbulb */
                "./resource/models/Crystal/crystal.obj",
                glm::vec3(-15.f, -1.5f, 3.1f),
                glm::vec3(0.0f, 0.5f, 0.0f),
                glm::vec3(2.5f)
            ),
            new Model( /* stand emplacement 4 - Cloud */
                "./resource/models/Crystal/crystal.obj",
                glm::vec3(-27.6f, 3.53f, -22.55f),
                glm::vec3(0.0f, 2.5f, 0.0f),
                glm::vec3(2.5f)
            ),
        }};
        //     // new Model(
        //     //     "/Users/wwatkins/Downloads/old-romanic-pilar/source/model/model.obj",
        //     //     glm::vec3(4.0f, 0.0f, 0.0f),
        //     //     glm::vec3(0.0f),
        //     //     glm::vec3(5.0f)
        //     // ),
        //     // new Model(
        //     //     "/Users/wwatkins/Downloads/old-romanic-pilar/source/model/model.obj",
        //     //     glm::vec3(8.0f, 0.0f, 0.0f),
        //     //     glm::vec3(0.0f),
        //     //     glm::vec3(5.0f)
        //     // ),
        // }};
        // IFS with rounded cubes in Raymarching with fog generated by FBM in Volumetric Raymarching.
        this->raymarched = new Raymarched({
            (tObject){
                eRaymarchObject::marble,
                glm::vec3(10.0f, 2.5f, 14.f),
                glm::vec3(0.0),
                1.0,
                1.0,
                (tMaterial){ glm::vec3(0.0), glm::vec3(1.0), glm::vec3(0.0), 1.0, 1.0 }
            },
            (tObject){
                eRaymarchObject::cloud,
                glm::vec3(-27.6f, 7.73f, -22.55f),
                glm::vec3(0.0),
                2.0,
                1.0,
                (tMaterial){ glm::vec3(0.0), glm::vec3(1.0), glm::vec3(0.0), 1.0, 1.0 }
            },
            (tObject){
                eRaymarchObject::ifs,
                glm::vec3(11.3f, 5.0f, -17.65f),
                glm::vec3(0.0),
                0.5,
                0.03,
                (tMaterial){
                    glm::vec3(0),
                    glm::vec3(1.0),
                    glm::vec3(0.35),
                    128.0,
                    1.0
                }
            },
            // (tObject){ // put bounding sphere around to optimise
            //     eRaymarchObject::mandelbox,
            //     glm::vec3(2.0, 0.0, 0.0),
            //     glm::vec3(0.0),
            //     0.5,
            //     0.015,
            //     (tMaterial){
            //         glm::vec3(0.0),
            //         glm::vec3(0.0),
            //         glm::vec3(0.659, 1.0, 0.537),
            //         50.0,
            //         1.0
            //     }
            // },
            (tObject){
                eRaymarchObject::mandelbulb,
                glm::vec3(-15.f, 2.0f, 3.1f),
                glm::vec3(0.0),
                1.0f,
                0.1,
                (tMaterial){
                    glm::vec3(0.0),
                    glm::vec3(0.0),
                    glm::vec3(0.35, 0.35, 0.35),
                    82.0,
                    1.0
                }
            },
            // (tObject){
            //     eRaymarchObject::torus,
            //     glm::vec3(1.0, 1.5, 0.0),
            //     glm::vec3(0.0),
            //     0.1,
            //     1.0,
            //     (tMaterial){
            //         glm::vec3(0.0),
            //         glm::vec3(1.0),
            //         glm::vec3(0.0, 0.0, 1.0),
            //         128.0,
            //         1.0
            //     }
            // }

        });
        this->lights = {{
            new Light(
                glm::vec3(30, 30, 18), //glm::vec3(10, 10, 6),
                glm::vec3(0.77f, 0.88f, 1.0f) * 0.075f,
                glm::vec3(1.0f, 0.964f, 0.77f),
                glm::vec3(1.0f, 1.0f, 1.0f),
                eLightType::directional
            ),
            /* lights from fractals stands */
            new Light(
                glm::vec3(10.0f, 1.f, 14.f),
                glm::vec3(0.0f, 0.0f, 0.0f),
                glm::vec3(0.937f, 0.474f, 0.212f),
                glm::vec3(0.937f, 0.474f, 0.212f),
                1.0f,
                0.18f,
                0.064f,
                eLightType::point
            ),
            new Light(
                glm::vec3(11.3f, 2.9f, -17.65f),
                glm::vec3(0.0f, 0.0f, 0.0f),
                glm::vec3(0.937f, 0.474f, 0.212f),
                glm::vec3(0.937f, 0.474f, 0.212f),
                1.0f,
                0.18f,
                0.064f,
                eLightType::point
            ),
            new Light(
                glm::vec3(-15.f, 0.4f, 3.1f),
                glm::vec3(0.0f, 0.0f, 0.0f),
                glm::vec3(0.937f, 0.474f, 0.212f),
                glm::vec3(0.937f, 0.474f, 0.212f),
                1.0f,
                0.18f,
                0.064f,
                eLightType::point
            )
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
    delete this->raymarched;
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
    // glfwWindowHint(GLFW_SAMPLES, 4);
}

void	Env::initGlfwWindow( size_t width, size_t height ) {
	if (!(this->window.ptr = glfwCreateWindow(width, height, "shaderPixel", NULL, NULL)))
        throw Exception::InitError("glfwCreateWindow failed");
	glfwMakeContextCurrent(this->window.ptr);
	glfwSetFramebufferSizeCallback(this->window.ptr, this->framebufferSizeCallback);
	glfwSetInputMode(this->window.ptr, GLFW_STICKY_KEYS, 1);
    // get the size of the framebuffer
    glfwGetFramebufferSize(this->window.ptr, &this->window.width, &this->window.height);
}

void    Env::setupController( void ) {
    this->controller->setKeyProperties(GLFW_KEY_P, eKeyMode::toggle, 1, 1000);
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
