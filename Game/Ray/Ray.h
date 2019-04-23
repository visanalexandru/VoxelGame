#ifndef RAY_H
#define RAY_H
#include"../../Engine/Transformable/Transformable.h"
class Ray:public Transformable
{
public:
    Ray(glm::vec3 pos,glm::vec3 forward_vector);
    glm::vec3 step_forward(float scalar);
    virtual ~Ray();

protected:

private:
    glm::vec3 fw_vector;
};

#endif // RAY_H
