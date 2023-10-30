#include "lab_m1/lab4/lab4.h"

#include <vector>
#include <string>
#include <iostream>

#include "lab_m1/lab4/transform3D.h"

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Lab4::Lab4()
{
}


Lab4::~Lab4()
{
}


void Lab4::Init()
{
    polygonMode = GL_FILL;

    Mesh* mesh = new Mesh("box");
    mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
    meshes[mesh->GetMeshID()] = mesh;

    // Initialize tx, ty and tz (the translation steps)
    translateX = 0;
    translateY = 0;
    translateZ = 0;

    // Initialize sx, sy and sz (the scale factors)
    scaleX = 1;
    scaleY = 1;
    scaleZ = 1;

    // Initialize angular steps
    angularStepOX = 0;
    angularStepOY = 0;
    angularStepOZ = 0;

    angularstepplanet1 = 0;
    angularstepplanet2 = 0;
    angularstepplanet3 = 0;

    // Sets the resolution of the small viewport
    glm::ivec2 resolution = window->GetResolution();
    miniViewportArea = ViewportArea(50, 50, resolution.x / 5.f, resolution.y / 5.f);

    speed = 5;
    speed1 = 2;
}

void Lab4::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Sets the screen area where to draw
    glm::ivec2 resolution = window->GetResolution();
    glViewport(0, 0, resolution.x, resolution.y); //primul viewport
}

void Lab4::RenderScene() {
    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(-2.5f, 0.5f, -1.5f);
    modelMatrix *= transform3D::Translate(translateX, translateY, translateZ);
    RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(0.0f, 0.5f, -1.5f);
    modelMatrix *= transform3D::Scale(scaleX, scaleY, scaleZ);
    RenderMesh(meshes["box"], shaders["Simple"], modelMatrix);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(2.5f, 0.5f, -1.5f);
    modelMatrix *= transform3D::RotateOX(angularStepOX);
    modelMatrix *= transform3D::RotateOY(angularStepOY);
    modelMatrix *= transform3D::RotateOZ(angularStepOZ);
    RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::RotateOZ(angularstepplanet2);
    modelMatrix *= transform3D::Translate(5.0f, 0.5f, 0.0f);
    modelMatrix *= transform3D::RotateOY(0.52);
    modelMatrix *= transform3D::RotateOX(angularstepplanet1);
    RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::RotateOZ(angularstepplanet2);
    modelMatrix *= transform3D::Translate(5.0f, 0.5f, 0.0f);
    modelMatrix *= transform3D::RotateOZ(angularstepplanet2);
    modelMatrix *= transform3D::Translate(3.0f, 0.5f, 0.0f);
    modelMatrix *= transform3D::RotateOY(0.52);
    modelMatrix *= transform3D::RotateOX(angularstepplanet1);
    modelMatrix *= transform3D::Scale(0.5, 0.5, 0.5);
    RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::RotateOY(0.52);
    modelMatrix *= transform3D::RotateOX(angularstepplanet1);
    modelMatrix *= transform3D::Scale(1.3, 1.3, 1.3);
    RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);
}

void Lab4::Update(float deltaTimeSeconds)
{
    glLineWidth(3);
    glPointSize(5);
    glPolygonMode(GL_FRONT_AND_BACK, polygonMode);

    angularstepplanet1 = angularstepplanet1 + speed * deltaTimeSeconds;
    angularstepplanet2 = angularstepplanet2 + speed1 * deltaTimeSeconds;
    angularstepplanet3 = angularstepplanet3 + speed * deltaTimeSeconds;

    RenderScene();
    DrawCoordinateSystem();

    glClear(GL_DEPTH_BUFFER_BIT);
    glViewport(miniViewportArea.x, miniViewportArea.y, miniViewportArea.width, miniViewportArea.height); //al doilea viewpoint

    // TODO(student): render the scene again, in the new viewport
    RenderScene();
    DrawCoordinateSystem();
}

void Lab4::FrameEnd()
{
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Lab4::OnInputUpdate(float deltaTime, int mods)
{
    // TODO(student): Add transformation logic

    if (window->KeyHold(GLFW_KEY_W))
    {
        translateY = translateY + speed * deltaTime;
    }
    if (window->KeyHold(GLFW_KEY_A))
    {
        translateX = translateX - speed * deltaTime;
    }
    if (window->KeyHold(GLFW_KEY_S))
    {
        translateY = translateY - speed * deltaTime;
    }
    if (window->KeyHold(GLFW_KEY_D))
    {
        translateX = translateX + speed * deltaTime;
    }
    if (window->KeyHold(GLFW_KEY_R))
    {
        translateZ = translateZ + speed * deltaTime;
    }
    if (window->KeyHold(GLFW_KEY_F))
    {
        translateZ = translateZ - speed * deltaTime;
    }


    if (window->KeyHold(GLFW_KEY_1))
    {
        scaleX = scaleX + speed * deltaTime;
        scaleY = scaleY + speed * deltaTime;
        scaleZ = scaleZ + speed * deltaTime;
    }
    if (window->KeyHold(GLFW_KEY_2))
    {
        scaleX = scaleX - speed * deltaTime;
        scaleY = scaleY - speed * deltaTime;
        scaleZ = scaleZ - speed * deltaTime;
    }


    if (window->KeyHold(GLFW_KEY_3))
    {
        angularStepOX = angularStepOX + speed * deltaTime;
    }
    if (window->KeyHold(GLFW_KEY_4))
    {
        angularStepOX = angularStepOX - speed * deltaTime;
    }
    if (window->KeyHold(GLFW_KEY_5))
    {
        angularStepOY = angularStepOY + speed * deltaTime;
    }
    if (window->KeyHold(GLFW_KEY_6))
    {
        angularStepOY = angularStepOY - speed * deltaTime;
    }
    if (window->KeyHold(GLFW_KEY_7))
    {
        angularStepOZ = angularStepOZ + speed * deltaTime;
    }
    if (window->KeyHold(GLFW_KEY_8))
    {
        angularStepOZ = angularStepOZ - speed * deltaTime;
    }

}


void Lab4::OnKeyPress(int key, int mods)
{
    // Add key press event
    if (key == GLFW_KEY_SPACE)
    {
        switch (polygonMode)
        {
        case GL_POINT:
            polygonMode = GL_FILL;
            break;
        case GL_LINE:
            polygonMode = GL_POINT;
            break;
        default:
            polygonMode = GL_LINE;
            break;
        }
    }

    if (key == GLFW_KEY_I)
    {
        miniViewportArea.y = miniViewportArea.y + 3;
        //miniViewportArea.height = miniViewportArea.height + 20;
    }
    if (key == GLFW_KEY_J)
    {
        miniViewportArea.y = miniViewportArea.y - 3;
        //miniViewportArea.height = miniViewportArea.height - 20;
    }
    if (key == GLFW_KEY_K)
    {
        miniViewportArea.x = miniViewportArea.x + 3;
        //miniViewportArea.width = miniViewportArea.width + 20;
    }
    if (key == GLFW_KEY_L)
    {
        miniViewportArea.x = miniViewportArea.x - 3;
        //miniViewportArea.width = miniViewportArea.width - 20;
    }
    if (key == GLFW_KEY_U)
    {
        miniViewportArea.x = miniViewportArea.x - 2;
        miniViewportArea.y = miniViewportArea.y - 2;
        miniViewportArea.width = miniViewportArea.width + 4;
        miniViewportArea.height = miniViewportArea.height + 4;
    }
    if (key == GLFW_KEY_O)
    {
        miniViewportArea.x = miniViewportArea.x + 2;
        miniViewportArea.y = miniViewportArea.y + 2;
        miniViewportArea.width = miniViewportArea.width - 4;
        miniViewportArea.height = miniViewportArea.height - 4;
    }
    
    // TODO(student): Add viewport movement and scaling logic
}


void Lab4::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Lab4::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}


void Lab4::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Lab4::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Lab4::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Lab4::OnWindowResize(int width, int height)
{
}
