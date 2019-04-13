#include "ModelLoader.h"
#include<sstream>
ModelLoader::ModelLoader(string path):reader(path)
{
    //ctor
}
bool ModelLoader::is_digit(char a)
{
    return a>='0'&&a<='9';
}
void ModelLoader::load_vertices()
{
    string line;
    string tokened;
    int params[6];
    int params2[6];
    char delimiter;
    vector<glm::vec3> positions;
    vector<glm::vec2> uvs;
    while(reader>>line)
    {
        if(line=="v")//vertex
        {
            glm::vec3 to_insert;
            reader>>to_insert.x>>to_insert.y>>to_insert.z;
            positions.push_back(to_insert);//add coordinate to positions
        }
        else if(line=="vt")//vertex texture coordinate
        {
            glm::vec2 to_insert;
            reader>>to_insert.x>>to_insert.y;
            uvs.push_back(to_insert);//add texture coordinate to uvs

        }
        else if(line=="f")//face
        {
            int p1,p2,countx=0;
            while(reader>>tokened)
            {
                if(is_digit(tokened[0]))
                {
                    stringstream sstream;
                    sstream<<tokened;
                    sstream>>p1>>delimiter>>p2;
                    params[countx]=p1;
                    params2[countx]=p2;
                    countx++;
                }
                else
                {
                    for(unsigned i=0; i<tokened.length(); i++)
                        reader.unget();//we move 1 character back
                    break;

                }
            }
            if(countx==3)//3 vertices (1 face)
            {
                glm::vec3 a=positions[params[0]-1];
                glm::vec3 b=positions[params[1]-1];
                glm::vec3 c=positions[params[2]-1];
                glm::vec2 uv1=uvs[params2[0]-1];
                glm::vec2 uv2=uvs[params2[1]-1];
                glm::vec2 uv3=uvs[params2[2]-1];
                verts.push_back(vertex(a,uv1));//we create different vertices with given attributes
                verts.push_back(vertex(b,uv2));
                verts.push_back(vertex(c,uv3));

            }
            else if(countx==4)//this is a rectangular face, we triangulate it into 2 triangles(6 vertices)
            {
                glm::vec3 a=positions[params[0]-1];
                glm::vec3 b=positions[params[1]-1];
                glm::vec3 c=positions[params[2]-1];
                glm::vec3 d=positions[params[3]-1];
                glm::vec2 uv1=uvs[params2[0]-1];
                glm::vec2 uv2=uvs[params2[1]-1];
                glm::vec2 uv3=uvs[params2[2]-1];
                glm::vec2 uv4=uvs[params2[3]-1];
                verts.push_back(vertex(a,uv1));
                verts.push_back(vertex(b,uv2));
                verts.push_back(vertex(c,uv3));
                verts.push_back(vertex(c,uv3));
                verts.push_back(vertex(d,uv4));
                verts.push_back(vertex(a,uv1));
            }
        }

    }
}
void ModelLoader::load_model(MeshData<texture_vertex>&data)
{
    load_vertices();
    cout<<"Loaded model data ,creating attributes"<<endl;
    int sizex=verts.size();
    int pushed=0;
    for(int i=0; i<sizex; i++)
    {
        int index=get_unique_index(verts[i]);
        if(index!=-1)
        {
            data.add_index(index);//has found an identical vertex->do not use this one
        }
        else
        {
            data.add_index(pushed);
            unique_vertices.insert({verts[i].get_id(),pushed});
            data.add_vertex(texture_vertex(verts[i].position,verts[i].uv));
            pushed++;

        }

    }
    cout<<"model loaded successfully: "<<data.get_vertices_size()<<" vertices, "<<data.get_triangles_size()<<" triangles"<<endl;
}
int ModelLoader::get_unique_index(vertex&vert)
{
    std::unordered_map<string,int>::const_iterator got = unique_vertices.find(vert.get_id());
    if(got==unique_vertices.end())
        return -1;
    else
        return got->second;
}
ModelLoader::~ModelLoader()
{
    //dtor
}
