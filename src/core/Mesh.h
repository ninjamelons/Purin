#if !defined(OBJECT_MESH)
#define OBJECT_MESH

#include "Component.h"
#include "Shader.h"

#include <string>
#include <vector>

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
    glm::vec3 Tangent;
    glm::vec3 Bitangent;
};

struct Texture {
    unsigned int id;
    std::string type;
    std::string path;
};

class Mesh : public Component {
    private:
        //  render data
        unsigned int _VAO, _VBO, _EBO;
        std::vector<Mesh> _children;

        void setupMesh();
    public:
        // mesh data
        std::vector<Vertex>       _vertices;
        std::vector<unsigned int> _indices;
        std::vector<Texture>      _textures;

        Mesh(std::vector<Vertex> vertices,
            std::vector<unsigned int> indices,
            std::vector<Texture> textures);
        void Draw(Shader &shader);

        ~Mesh();
};

#endif