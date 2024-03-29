#include "Renderer.h"

Renderer::Renderer(GLFWwindow*context,Camera&camera):main_camera(camera)
{
    //ctor
    context_window=context;
}
void Renderer::Set_Camera(Camera&newcamera)
{
    main_camera=newcamera;
}
void Renderer::Set_mvp(const ShaderProgram&prog,glm::mat4 m,glm::mat4 v,glm::mat4 p)
{
    prog.set_mat4(v,view);
    prog.set_mat4(p,proj);
    prog.set_mat4(m,model);

}
void Renderer::Render(const Drawable3d&to_draw,bool bind_resources)
{
    if(main_camera.can_see(to_draw) )
    {
        const Mesh&mesh=to_draw.Get_mesh();
        vertices_rendered+=mesh.Get_vertices_size();
        mesh.bind_mesh(bind_resources);
        Set_mvp(mesh.Get_shader(),to_draw.Get_position_matrix(),camera_view_matrix,main_camera.getProjectionMatrix());
        glDrawElements(GL_TRIANGLES, mesh.Get_triangles_size(), GL_UNSIGNED_INT,(void*)0);
    }
}
void Renderer::Render_water(const Drawable3d&to_draw,bool bind_resources)
{
    if(main_camera.can_see(to_draw) )
    {
        glDisable(GL_CULL_FACE);
        const Mesh&mesh=to_draw.Get_mesh();
        const ShaderProgram&prog=mesh.Get_shader();
        vertices_rendered+=mesh.Get_vertices_size();
        mesh.bind_mesh(bind_resources);
        Set_mvp(prog,to_draw.Get_position_matrix(),camera_view_matrix,main_camera.getProjectionMatrix());
        prog.set_float(glfwGetTime(),timex);
        glDrawElements(GL_TRIANGLES, mesh.Get_triangles_size(), GL_UNSIGNED_INT,(void*)0);
        glEnable(GL_CULL_FACE);
    }
}
void Renderer::Render_scene(const Scene&scene)
{
    scene.bind_resources();
    int si=scene.to_draw.size();
    for(int i=0; i<si; i++)
        Render(*scene.to_draw[i],false);

}
void Renderer::Render_water_scene(const Scene&scene)
{
    scene.bind_resources();
    int si=scene.to_draw.size();
    for(int i=0; i<si; i++)
        Render_water(*scene.to_draw[i],false);

}
void Renderer::Render(const Drawable2d&to_draw)
{
    glDisable(GL_DEPTH_TEST);
    const Mesh&mesh=to_draw.Get_mesh();
    const ShaderProgram&prog=mesh.Get_shader();
    mesh.bind_mesh(true);
    prog.set_mat4(to_draw.Get_position_matrix(),model);
    prog.set_mat4(main_camera.getOrtographicMatrix(),proj);
    glDrawElements(GL_TRIANGLES,mesh.Get_triangles_size(),GL_UNSIGNED_INT,(void*)0);
    glEnable(GL_DEPTH_TEST);

}
void Renderer::Render(const Skybox&skybox)
{
    glDepthMask(GL_FALSE);
    const Mesh&mesh=skybox.mesh;
    mesh.bind_mesh(true);
    mesh.Get_shader().set_mat4(glm::mat3(camera_view_matrix),view);
    mesh.Get_shader().set_mat4(main_camera.getProjectionMatrix(),proj);
    glDrawElements(GL_TRIANGLES, mesh.Get_triangles_size(), GL_UNSIGNED_INT,(void*)0);
    glDepthMask(GL_TRUE);


}
void Renderer::Prepare_frame()
{
    vertices_rendered=0;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    camera_view_matrix=main_camera.getViewMatrix();
}
void Renderer::End_frame()
{
    glfwSwapBuffers(context_window);
}
Renderer::~Renderer()
{
    //dtor
}
