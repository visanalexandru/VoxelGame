#include "Camera.h"

Camera::Camera(glm::vec3 newpos, program_properties prop):Transformable(newpos)
{
    //ctor
    camera_fov=prop.get_fov();
    update_projection_matrix(prop.get_width(),prop.get_height());
    update_orto_matrix(prop.get_width(),prop.get_height());
    cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
    camera_speed=10.f;
    yaw=0;
    pitch=0;
}
glm::mat4 Camera::getProjectionMatrix()
{
    return projection_matrix;
}
glm::mat4 Camera::getOrtographicMatrix()
{
    return orto_matrix;
}
glm::mat4 Camera::getViewMatrix()
{
    glm::mat4 view(1);
    glm::vec3 pos=get_position();
    view = glm::lookAt(pos, pos + cameraFront, cameraUp);
    return view;
}
void Camera::Update_frustum()
{
    frustum.update(getProjectionMatrix()*getViewMatrix());
}
bool Camera::can_see(const AABB&box)
{
    return frustum.boxInFrustum(box);
}
void Camera::update_orto_matrix(int width,int height)
{
    orto_matrix=makeOrtographicMatrix(width,height);

}
void Camera::Update_front_vector()
{
    if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;
    glm::vec3 frontv;
    frontv.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    frontv.y = sin(glm::radians(pitch));
    frontv.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(frontv);
}
void Camera::update_projection_matrix(int width,int height)
{
    projection_matrix = makeProjectionMatrix(camera_fov,width,height);
}
glm::mat4 Camera::makeProjectionMatrix(float fov,int width,int height)
{
    return glm::perspective(glm::radians(fov), (float)width / (float)height, 0.1f, 1000.0f);
}
glm::mat4 Camera::makeOrtographicMatrix(int width,int height)
{
    return glm::ortho(0.0f, (float)width, (float)height, 0.0f, -1.0f, 1.0f);
}
Camera::~Camera()
{
    //dtor
}
