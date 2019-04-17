#ifndef DRAWABLE2D_H
#define DRAWABLE2D_H
#include"../Transformable/Transformable2d.h"
#include"../Mesh/Mesh.h"
class Drawable2d:public Transformable2d
{
public:
    Drawable2d(glm::vec2 position,glm::vec2 size,const ShaderProgram&prog,const Texture2d&tex);
    virtual ~Drawable2d();
    const Mesh&Get_mesh() const;
    void set_mesh_data(const Buffer&data);
protected:
    Mesh mesh;
private:
};

#endif // DRAWABLE2D_H
