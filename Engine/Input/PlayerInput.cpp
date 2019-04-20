#include "PlayerInput.h"

PlayerInput::PlayerInput(GLFWwindow*context,Camera&player_camera_in,ChunkManager&world):player_camera(player_camera_in),
    chunk_manager(world)
{
    //ctor
    last_time_pressed_mouse1=glfwGetTime();
    last_time_pressed_mouse2=glfwGetTime();
    context_window=context;
    last_time=glfwGetTime();
    glfwGetCursorPos(context,&lastX,&lastY);
    sensitivity=0.05f;
}
void PlayerInput::process_input()
{
    GraphicsUtil::poll_events();
    check_for_exit();
    move_camera();
    game_input();
    rotate_camera();
    update_camera_frustum();
}
void PlayerInput::update_camera_frustum()
{
    player_camera.Update_frustum();
}
void PlayerInput::rotate_camera()
{
    double newx,newy;
    glfwGetCursorPos(context_window,&newx,&newy);
    float diffx=newx-lastX;
    float diffy=lastY-newy;
    diffx*=sensitivity;
    diffy*=sensitivity;
    lastX=newx;
    lastY=newy;
    player_camera.pitch+=diffy;
    player_camera.yaw+=diffx;
    player_camera.Update_front_vector();
}
void PlayerInput::check_for_exit()
{
    if(glfwGetKey(context_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(context_window, true);
}
float PlayerInput::get_delta_time()
{
    float now=glfwGetTime();
    float to_return=now-last_time;
    last_time=now;
    return to_return;
}
void PlayerInput::check_callbacks()
{
    if(glfwGetKey(context_window,GLFW_KEY_1)==GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    if(glfwGetKey(context_window,GLFW_KEY_2)==GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

}
void PlayerInput::game_input()
{
    bool left_click = glfwGetMouseButton(context_window, GLFW_MOUSE_BUTTON_LEFT);
    bool right_click = glfwGetMouseButton(context_window, GLFW_MOUSE_BUTTON_RIGHT);
    if(left_click)
    {
        if(glfwGetTime()-last_time_pressed_mouse1>=block_break_cooldown)
        {
            raycast_break();
            last_time_pressed_mouse1=glfwGetTime();
        }
    }
    else if(right_click)
    {
        if(glfwGetTime()-last_time_pressed_mouse2>=block_break_cooldown)
        {
            raycast_place();
            last_time_pressed_mouse2=glfwGetTime();
        }
    }

}
void PlayerInput::raycast_break()
{
    Ray ray(player_camera.get_position(),player_camera.cameraFront);
    glm::vec3 pos,fixed,offset;
    for(float i=0; i<10; i+=ray_step)
    {
        pos=ray.step_forward(i);
        fixed=chunk_manager.get_chunk_relative_position(pos);
        offset=pos-fixed;
        if(chunk_manager.does_chunk_exists_at(fixed) &&ChunkConstants::is_inside(offset.y))
        {
            Chunk*hit=chunk_manager.get_chunk_at(fixed);
            BlockId block_hit=hit->get_block_at(offset.x,offset.y,offset.z);
            if(ChunkConstants::can_block_be_hit(block_hit))
            {
                hit->set_block_at(offset.x,offset.y,offset.z,BlockId::Air_block);
                break;
            }
        }
    }
}
void PlayerInput::raycast_place()
{
    Ray ray(player_camera.get_position(),player_camera.cameraFront);
    glm::vec3 pos,fixed,offset,last_position;
    Chunk*last_chunk=NULL;
    for(float i=0; i<10; i+=ray_step)
    {
        pos=ray.step_forward(i);
        fixed=chunk_manager.get_chunk_relative_position(pos);
        offset=pos-fixed;
        if(chunk_manager.does_chunk_exists_at(fixed) &&ChunkConstants::is_inside(offset.y))
        {
            Chunk*hit=chunk_manager.get_chunk_at(fixed);
            BlockId block_hit=hit->get_block_at(offset.x,offset.y,offset.z);
            if(ChunkConstants::can_block_be_hit(block_hit))
            {
                if(ChunkConstants::is_inside(last_position.y) &&last_chunk)
                {
                    last_chunk->set_block_at(last_position.x,last_position.y,last_position.z,BlockId::Dirt_block);
                }
                break;
            }
            last_chunk=hit;
        }
        last_position=offset;
    }
}
void PlayerInput::move_camera()
{
    check_callbacks();
    float delta_time=get_delta_time();
    float cameraSpeed = player_camera.camera_speed*delta_time;
    glm::vec3 cameraPos=player_camera.get_position();
    glm::vec3 cameraFront=player_camera.cameraFront;
    glm::vec3 cameraUp=player_camera.cameraUp;
    if(glfwGetKey(context_window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        cameraSpeed/=5;
    if (glfwGetKey(context_window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(context_window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(context_window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(context_window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    player_camera.set_position(cameraPos);

}
PlayerInput::~PlayerInput()
{
    //dtor
}
