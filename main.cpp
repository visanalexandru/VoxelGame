#include <iostream>
#include"Engine/Graphics/GraphicsUtil.h"
#include"Engine/Input/PlayerInput.h"
#include"Engine/Graphics/Renderer.h"
#include"Engine/Mesh/Mesh.h"
#include"Engine/Skybox/Skybox.h"
#include"Engine/Noise/NoiseGenerator.h"
#include"Engine/ResourceManager/ResourceManager.h"
#include"Engine/ModelLoader/ModelLoader.h"
#include"Engine/MeshData/Meshdata_simple.h"
#include"Game/Chunk/ChunkManager.h"
#include"Game/Crosshair.h"
using namespace std;
void load_all_resources(ResourceManager&manager)
{
    manager.load_vertex_shader("Resources/Shaders/vertex_shader3d.vert","basicvert");
    manager.load_vertex_shader("Resources/Shaders/vertex_shader2d.vert","2dvert");
    manager.load_fragment_shader("Resources/Shaders/fragment_shader.frag","basicfrag");
    manager.load_vertex_shader("Resources/Shaders/skybox_shader.vert","skyboxvert");
    manager.load_fragment_shader("Resources/Shaders/skybox_shader.frag","skyboxfrag");
    manager.create_program("basicvert","basicfrag","basic_shader");
    manager.create_program("2dvert","basicfrag","basic_2dshader");
    manager.create_program("skyboxvert","skyboxfrag","skybox_shader");
    manager.load_texture("Resources/Textures/terrain.png","test3");
    manager.load_texture("Resources/Textures/crosshair.png","crosshair");
    manager.load_cubemap("Resources/Cubemap","test4");



}
ConfigParser parse_config()
{
    return ConfigParser("Resources/config.txt");

}
int main()
{
    ConfigParser parsed=parse_config();
    GraphicsUtil::initialize_glfw();
    ResourceManager manager;
    GLFWwindow*window=GraphicsUtil::create_window(parsed.Get_parsed());
    if(window==NULL)
        return -1;
    load_all_resources(manager);
    ShaderProgram& basic_prog=manager.get_shader_program("basic_shader");
    ShaderProgram& crosshair_prog=manager.get_shader_program("basic_2dshader");
    ShaderProgram& skybox_prog=manager.get_shader_program("skybox_shader");
    Texture2d&basic_texture=manager.get_texture("test3");
    Texture2d&crosshair_texture=manager.get_texture("crosshair");
    Crosshair crosshair(crosshair_prog,crosshair_texture);
    Skybox sky(skybox_prog,manager.get_cubemap("test4"));
    Camera camera(glm::vec3(0,40,0),parsed.Get_parsed());
    GraphicsUtil::set_main_camera(&camera);
    Renderer renderer(window,camera);
    ChunkManager chunk_manager(basic_prog,basic_texture,camera,15);
    PlayerInput input_processer(window,camera,chunk_manager);
    while(!glfwWindowShouldClose(window))
    {
        float a=glfwGetTime();
        chunk_manager.destroy_chunks_out_of_range();
        chunk_manager.create_meshes();
        input_processer.process_input();
        renderer.Prepare_frame();
        renderer.Render(sky);
        renderer.Render(crosshair);
        chunk_manager.lock();
        renderer.Render_scene(chunk_manager.get_scene());
        chunk_manager.unlock();
        renderer.End_frame();
        cout<<1/(glfwGetTime()-a)<<'\n';

    }
    GraphicsUtil::destroy_window(window);
    GraphicsUtil::terminate_glfw();
    return 0;
}
