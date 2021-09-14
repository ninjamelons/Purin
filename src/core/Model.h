#if !defined(MODEL)
#define MODEL

#include "Component.h"
#include "Mesh.h"
#include "Shader.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <vector>

#include "stb_image.h"

class Model : public Component {
public:
    void Draw(Shader &shader);
private:
    // model data
    std::vector<Mesh> _meshes;
    std::string _directory;
    std::vector<Texture> _texturesLoaded;

    void loadModel(std::string path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, 
                                            std::string typeName);
    unsigned int textureFromFile(const char *path, const std::string &directory, bool gamma = false);
public:
    Model(const char *path);
    ~Model();
};

#endif