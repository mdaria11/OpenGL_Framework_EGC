#include "Meshes.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"


//function that creates a circle mesh
Mesh* Meshes::createCircle(const std::string& name, float r, glm::vec3 color, float z)
{
    std::vector<VertexFormat> verticescircle;

    //center of the circle
    verticescircle.push_back(VertexFormat(glm::vec3(0, 0, z), color)); //0

    //doing 360 points around the origin 
    for (float i = 0; i < 6.5; i += 0.018f)
    {
        verticescircle.push_back(VertexFormat(glm::vec3(r * cosf(i), r * sinf(i), z), color));
    }

    Mesh* circle = new Mesh(name);
    std::vector<unsigned int> indicescircle;

    //doing the triangles
    for (int i = 1; i < verticescircle.size()-1; i++)
    {
        indicescircle.push_back(0);
        indicescircle.push_back(i);
        indicescircle.push_back(i + 1);
    }

    indicescircle.push_back(0);
    indicescircle.push_back(verticescircle.size()-1);
    indicescircle.push_back(1);

    circle->InitFromData(verticescircle, indicescircle);
    return circle;
}

//function that creates a rectangle 
Mesh* Meshes::CreateRectangle(const std::string& name, float width, float height, float z, glm::vec3 color, bool fill)
{
    std::vector<VertexFormat> vertices =
    {
        VertexFormat(glm::vec3(0, 0, z), color),
        VertexFormat(glm::vec3(width, 0, z), color),
        VertexFormat(glm::vec3(width, height, z), color),
        VertexFormat(glm::vec3(0, height, z), color)
    };

    Mesh* rectangle = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        rectangle->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    rectangle->InitFromData(vertices, indices);
    return rectangle;
}