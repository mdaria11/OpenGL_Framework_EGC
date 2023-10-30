#pragma once

#include "components/simple_scene.h"
#include "lab_m1/Tema3/lab_camera.h"


namespace m1
{
    class Tema3 : public gfxc::SimpleScene
    {
    public:
        Tema3();
        ~Tema3();

        void Init() override;

    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        Mesh* CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned int>& indices);
        void RenderSimpleMesh_hw(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color = glm::vec3(1), Texture2D* texture1 = NULL);

        void DrawTree(glm::vec3 location);
        void DrawRock(glm::vec3 location);
        void DrawPole(glm::vec3 location);
        void DrawPresent(glm::vec3 location);
        void DrawPlayer(glm::mat4 model);

        void DrawObstacles();
        void CheckCollision();

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

    protected:
        implemented::Camerahomework3* camera;
        glm::mat4 projectionMatrix;

        glm::vec3 positionplayer;
        float angleplayer;
        int score;

        float mouseposx;
        glm::ivec2 resolution;

        std::unordered_map<std::string, Texture2D*> mapTextures;
        int textureapplied, deplasamenttrue;
        glm::vec2 deplasamenttext;

        int obstaclesrendered;

        std::vector<int> nrmesh;
        std::vector<glm::vec3> positionobs;

        bool gameover, once;

    };
}   // namespace m1
