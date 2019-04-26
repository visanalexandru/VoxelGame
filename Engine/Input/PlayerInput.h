#ifndef PLAYERINPUT_H
#define PLAYERINPUT_H
#include"../Graphics/GraphicsUtil.h"
#include"../Camera/Camera.h"
#include"../../Game/Chunk/ChunkManager.h"
#include"../../Game/Ray/Ray.h"
class PlayerInput
{
public:
    PlayerInput(GLFWwindow*context,Camera&player_camera_in,ChunkManager&world);
    Camera&player_camera;
    GLFWwindow*context_window;
    virtual ~PlayerInput();
    void process_input();
    float get_delta_time();
protected:

private:
    static void key_callbacks(GLFWwindow* window, int key, int scancode, int action, int mods);
    const float block_break_cooldown=0.5f;
    const float ray_step=0.05f;
    float last_time_pressed_mouse1;
    float last_time_pressed_mouse2;
    ChunkManager&chunk_manager;
    void game_input();
    void raycast_break();
    void raycast_place();
    static unsigned held_block;
    float sensitivity;
    double lastX;
    double lastY;
    float last_time;
    void check_for_exit();
    void move_camera();
    void rotate_camera();
    void update_camera_frustum();
};

#endif // PLAYERINPUT_H
