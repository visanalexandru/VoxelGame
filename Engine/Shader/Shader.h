#ifndef SHADER_H
#define SHADER_H
#include"../Graphics/GraphicsUtil.h"
#include"../FileReader/FileReader.h"
class Shader
{
public:
    Shader();
    virtual ~Shader();
    virtual void load_shader(std::string path)=0;
    void delete_shader();
    unsigned get_shader_index()const ;
protected:
    unsigned shader_index;

private:
    virtual void check_for_shader_compilation_succes(std::string path) const =0;

};

#endif // SHADER_H
