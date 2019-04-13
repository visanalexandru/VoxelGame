#ifndef DRAWABLE3D_H
#define DRAWABLE3D_H
#include"../Transformable/Transformable.h"
#include"../AABB/AABB.h"
#include"../Mesh/Mesh.h"

class Drawable3d:public AABB,public Transformable
{
public:
    Drawable3d(glm::vec3 position,const ShaderProgram&prog,const Texture2d&tex);
    virtual ~Drawable3d();
    void UpdateAABB();
    const Mesh&Get_mesh() const;
    void set_position(glm::vec3 newpos) override;
    void set_mesh_data(const Buffer&data);
protected:
    Mesh mesh;
private:
};

#endif // DRAWABLE3D_H
