#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


namespace Meshes
{
    Mesh* createCircle(const std::string& name, float radius, glm::vec3 color, float z);
    Mesh* CreateRectangle(const std::string& name, float width, float height, float z, glm::vec3 color, bool fill);
}