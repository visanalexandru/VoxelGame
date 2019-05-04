#ifndef CAMERA_H
#define CAMERA_H
#include"../Transformable/Transformable.h"
#include<cmath>
#include"Frustum.h"
#include"../ConfigParser/ConfigParser.h"
class Camera:public Transformable
{
public:
    Camera(glm::vec3 newpos,program_properties prop);
    virtual ~Camera();
    glm::mat4 getProjectionMatrix();
    glm::mat4 getViewMatrix();
    glm::mat4 getOrtographicMatrix();
    float camera_speed;
    glm::vec3 cameraFront;
    glm::vec3 cameraUp;
    float yaw;
    float pitch;
    void Update_front_vector();
    void Update_frustum();
    bool can_see(const AABB&box);
    void update_projection_matrix(int width,int height);
    void update_orto_matrix(int width,int height);
protected:

private:
    float camera_fov;
    Frustum frustum;
    glm::mat4 projection_matrix;
    glm::mat4 orto_matrix;
    glm::mat4 makeProjectionMatrix(float fov,int width,int height);
    glm::mat4 makeOrtographicMatrix(int width,int height);


};

#endif // CAMERA_H
