#include "ConfigParser.h"

ConfigParser::ConfigParser(string path_to_config)
{
    //ctor
    parse(path_to_config);
}
void ConfigParser::parse(string path)
{
    ifstream file_stream(path);
    string auxiliary;
    int aux;
    float aux2;
    while(file_stream>>auxiliary)
    {
        if(auxiliary=="width")
        {
            file_stream>>aux;
            w_properties.set_width(aux);

        }
        else if(auxiliary=="height")
        {
            file_stream>>aux;
            w_properties.set_height(aux);
        }
        else if(auxiliary=="fov")
        {
            file_stream>>aux2;
            w_properties.set_fov(aux2);
        }
        else if(auxiliary=="use_vsync")
        {
            file_stream>>aux;
            w_properties.set_vsync(aux);
        }
        else if(auxiliary=="program_name")
        {
            file_stream>>auxiliary;
            w_properties.set_title(auxiliary);
        }

    }


}
window_camera_properties ConfigParser::Get_parsed()
{
    return w_properties;
}
ConfigParser::~ConfigParser()
{
    //dtor
}
