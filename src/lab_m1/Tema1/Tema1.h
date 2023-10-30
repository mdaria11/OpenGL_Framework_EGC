#pragma once

#include "components/simple_scene.h"


namespace m1
{
    class Tema1 : public gfxc::SimpleScene
    {
    public:
        Tema1();
        ~Tema1();

        void Init() override;

    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

        glm::mat3 MovementMatrix(float directionX, float directionY, float radians);
        void CalculateDirectionLine(float *directionX, float *radians);
        void checkShooting();

        void DuckAnimation(float directionx, float directiony, float angle, float deltaTimeSeconds);
        void DrawInterface();
        void DrawMouse();

        void GameOver();

    protected:
        float directionx, directiony, angle, speedx, speedxinit, speedy, wingstep, wingstepleft, actualangle, relativeangle;
        float timeduck;
        float circlex, circley, logiccircley;
        float rback, gback, bback;

        int nrducks, score, lives, bullets, maxtime;
        float shootingx, shootingy;
        float sx, sy;

        glm::mat3 modelMatrixbody, modelMatrixwingl, modelMatrixhead, modelMatrixbeak,
            modelMatrixwingr, modelMatrixbodyaux, modelMatrixwinglaux,
            modelMatrixheadaux, modelMatrixbeakaux, modelMatrixwingraux, modelMatrixeye, modelMatrixeyeaux,
            modelMatrixmouse;

        glm::mat3 CollisionMatrix, CollisionMatrixaux;

        glm::ivec2 resolution;

        bool wingup, duckin, up, down, left, right, goingup, upperwall, downwall, rightwall, leftwall,
            goingleft, goingright, escape, shot, maxscoredreached;

    };
}   // namespace m1
