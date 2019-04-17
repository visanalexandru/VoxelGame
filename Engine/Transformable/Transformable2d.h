#ifndef TRANSFORMABLE2D_H
#define TRANSFORMABLE2D_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Transformable2d
{
public:
    Transformable2d(glm::vec2 position,glm::vec2 size);
    virtual ~Transformable2d();
    glm::vec2 get_position()const;
    glm::vec2 get_scale()const;
    void set_position(glm::vec2 pos);
    void set_scale(glm::vec2 size);
    glm::mat4 Get_position_matrix()const;
protected:
    glm::vec2 position;
    glm::vec2 scale;
private:
};

#endif // TRANSFORMABLE2D_H
