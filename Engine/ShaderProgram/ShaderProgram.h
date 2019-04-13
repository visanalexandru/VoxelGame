#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H
#include"../Shader/VertexShader.h"
#include"../Shader/FragmentShader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class ShaderProgram
{
public:
    ShaderProgram(VertexShader vertex_shader,FragmentShader fragment_shader);
    virtual ~ShaderProgram();
    unsigned shader_program_index;
    void attach_vertex_shader(VertexShader v) const;
    void attach_fragment_shader(FragmentShader v) const;
    void check_for_succes() const;
    void use_program() const;
    void delete_program();
    void set_mat4(glm::mat4 to_set,string& name) const;
protected:

private:
};

#endif // SHADERPROGRAM_H
