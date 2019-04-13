#ifndef BUFFER_H
#define BUFFER_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class Buffer
{
public:
    Buffer();
    virtual void create_attributes()const=0 ;
    virtual const void* get_vertex_data()const=0 ;
    virtual const void* get_triangles_data()const=0;
    virtual int get_vertices_size()const=0;
    virtual int get_triangles_size()const=0;
    virtual int get_vertex_element_size() const=0;
    float get_bounds(int index)const;
    virtual ~Buffer();
protected:
    void Set_bounds(glm::vec3 to_add);
    bool has_not_set_bounds;
private:
    float bounds[6];
};

#endif // BUFFER_H
