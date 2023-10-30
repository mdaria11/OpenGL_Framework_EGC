#pragma once

#include <vector>

#include "components/simple_scene.h"
#include "lab_m1/Tema2/lab_camera.h"


namespace m1
{
    class Tema2 : public gfxc::SimpleScene
    {
    public:
        struct ViewportArea
        {
            ViewportArea() : x(0), y(0), width(1), height(1) {}
            ViewportArea(int x, int y, int width, int height)
                : x(x), y(y), width(width), height(height) {}
            int x;
            int y;
            int width;
            int height;
        };
        Tema2();
        ~Tema2();

        void Init() override;

        std::vector<glm::vec3> obscar1points;
        std::vector<glm::vec3> obscar2points;
        std::vector<glm::vec3> obscar3points;
        std::vector<glm::vec3> obscar4points;
        std::vector<glm::vec3> obscar5points;
        std::vector<glm::vec3> obscar6points;
        std::vector<glm::vec3> initialpoints;
        std::vector<VertexFormat> vertices;
        std::vector<glm::vec3> treelocations;

    private:

        Mesh* CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned int>& indices);
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void RenderSimpleMesh_hw(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix);
        void CreateRectangle(const char* name, float latime, float lungime, float h, glm::vec3 color);
        void CreatePista();
        void CreateGrass();
        void MakePathsObstacles();
        void DrawObstacles(float deltaTimeSeconds);
        void DrawCar(float deltaTimeSeconds, const char* name, std::vector<glm::vec3> obscarpoints, glm::vec3 *positioncar, glm::vec3 *directionway, int *indpoint);
        void DrawPathDebug();
        void DrawTrees();
        void DrawScene(float deltaTimeSeconds);
        void CheckCollisionCars();
        void CheckCarinPath(glm::vec3 directioncar);
        float TriangleArea(glm::vec3 a, glm::vec3 b, glm::vec3 c);

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

        protected:
            implemented::Camerahw* camera, *cameraminimap;
            glm::mat4 projectionMatrix, TrunkMatrix, BigLeafMatrix, SmallLeafMatrix, PlayerCarMatrix;
            float bottom, znear, zfar, left, right, top;
            ViewportArea miniViewportArea;
            bool minimap;

            bool collisiondetected, outpathdetected;
            float timestopped;

            float angle;
            glm::vec3 directioncar, directionobscar1, directionobscar2, directionobscar3, directionobscar4, directionobscar5, directionobscar6;
            glm::vec3 directionobscar1aux, directionobscar2aux, directionobscar3aux, directionobscar4aux, directionobscar5aux, directionobscar6aux;
            int indpointcar1, indpointcar2, indpointcar3, indpointcar4, indpointcar5, indpointcar6;

            glm::vec3 camera_position;
            glm::vec3 camera_forward;
            glm::vec3 camera_right;
            glm::vec3 camera_up;
    };
}   // namespace m1
