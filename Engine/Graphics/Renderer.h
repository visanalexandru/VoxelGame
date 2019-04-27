#ifndef RENDERER_H
#define RENDERER_H
#include"../Drawable/Drawable3d.h"
#include"../Drawable/Drawable2d.h"
#include"../Skybox/Skybox.h"
#include"../Camera/Camera.h"
#include"../Scene/Scene.h"
class Renderer
{
public:
    Renderer(GLFWwindow*context,Camera&camera);
    void Render(const Drawable3d&to_draw,bool bind_resources);
    void Render_water(const Drawable3d&water,bool bind_resources);
    void Render(const Skybox&skybox);
    void Render(const Drawable2d&to_draw);
    void Prepare_frame();
    virtual ~Renderer();
    void End_frame();
    void Render_scene(const Scene&scene);
    void Render_water_scene(const Scene&scene);
    void Set_Camera(Camera&newcamera);
protected:

private:
    Camera&main_camera;
    GLFWwindow*context_window;
    int vertices_rendered;
    string model="model";
    string proj="projection";
    string view="view";
    string timex="time_off";
    glm::mat4 camera_view_matrix;
    void Set_mvp(const ShaderProgram&prog,glm::mat4 m,glm::mat4 v,glm::mat4 p);

};

#endif // RENDERER_H
