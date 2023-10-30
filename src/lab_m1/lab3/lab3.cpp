#include "lab_m1/lab3/lab3.h"

#include <vector>
#include <iostream>

#include "lab_m1/lab3/transform2D.h"
#include "lab_m1/lab3/object2D.h"

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Lab3::Lab3()
{
}


Lab3::~Lab3()
{
}

bool diagup, diagdown, scaleup, scaledown, jump = true;
int speed = 20;
float angularstepjump, translatexjump;

void Lab3::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    glm::vec3 corner = glm::vec3(0, 0, 0);
    float squareSide = 100;

    // TODO(student): Compute coordinates of a square's center, and store
    // then in the `cx` and `cy` class variables (see the header). Use
    // `corner` and `squareSide`. These two class variables will be used
    // in the `Update()` function. Think about it, why do you need them?

    // Initialize tx and ty (the translation steps)
    translateX = 150;
    translateY = 250;
    diagup = true;
    diagdown = false;
    scaleup = true;
    scaledown = false;

    // Initialize sx and sy (the scale factors)
    scaleX = 1;
    scaleY = 1;

    // Initialize angularStep
    angularStep = -0.1;

    angularstepjump = -0.1;
    translatexjump = 250;

    Mesh* square1 = object2D::CreateSquare("square1", corner, squareSide, glm::vec3(1, 0, 0), true);
    AddMeshToList(square1);

    Mesh* square2 = object2D::CreateSquare("square2", corner, squareSide, glm::vec3(0, 1, 0));
    AddMeshToList(square2);

    Mesh* square3 = object2D::CreateSquare("square3", corner, squareSide, glm::vec3(0, 0, 1));
    AddMeshToList(square3);

    Mesh* square4 = object2D::CreateSquare("square4", corner, squareSide, glm::vec3(1, 0, 1));
    AddMeshToList(square4);
}


void Lab3::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void Lab3::Update(float deltaTimeSeconds)
{
    // TODO(student): Update steps for translation, rotation and scale,
    // in order to create animations. Use the class variables in the
    // class header, and if you need more of them to complete the task,
    // add them over there!

    if (diagup)
    {
        translateX = translateX + speed * deltaTimeSeconds;
        translateY = translateY + speed * deltaTimeSeconds;
        if (translateX >= 200)
        {
            diagup = false;
            diagdown = true;
        }
    }
    if (diagdown)
    {
        translateX = translateX - speed * deltaTimeSeconds;
        translateY = translateY - speed * deltaTimeSeconds;
        if (translateX <= 150)
        {
            diagup = true;
            diagdown = false;
        }
    }

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(translateX, translateY);
    RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);



    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(450, 300);
    modelMatrix *= transform2D::Rotate(angularStep);
    angularStep = angularStep - 2 * deltaTimeSeconds;
    modelMatrix *= transform2D::Translate(-50, -50);
    RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);

    if (scaleup)
    {
        scaleX = scaleX + 10 * deltaTimeSeconds;
        scaleY = scaleY + 10 * deltaTimeSeconds;

        if (scaleX >= 3)
        {
            scaleup = false;
            scaledown = true;
        }
    }
    if (scaledown)
    {
        scaleX = scaleX - 10 * deltaTimeSeconds;
        scaleY = scaleY - 10 * deltaTimeSeconds;

        if (scaleX <= 0)
        {
            scaleup = true;
            scaledown = false;
        }
    }

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(700, 300);
    modelMatrix *= transform2D::Scale(scaleX, scaleY);
    modelMatrix *= transform2D::Translate(-50, -50);
    RenderMesh2D(meshes["square3"], shaders["VertexColor"], modelMatrix);

    if (jump)
    {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(translatexjump, 200);
        modelMatrix *= transform2D::Rotate(angularstepjump);
        angularstepjump = angularstepjump - 1 * deltaTimeSeconds;
        modelMatrix *= transform2D::Translate(-250, 0);
        RenderMesh2D(meshes["square4"], shaders["VertexColor"], modelMatrix);

        if (angularstepjump <= -3.14)
        {
            jump = false;
        }
    }
    else
    {
        translatexjump = translatexjump + 400;
        angularstepjump = -0.1;
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(translatexjump-250, 200);
        RenderMesh2D(meshes["square4"], shaders["VertexColor"], modelMatrix);
        jump = true;
    }
}


void Lab3::FrameEnd()
{
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Lab3::OnInputUpdate(float deltaTime, int mods)
{
    
}


void Lab3::OnKeyPress(int key, int mods)
{
    // Add key press event
}


void Lab3::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Lab3::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}


void Lab3::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Lab3::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Lab3::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Lab3::OnWindowResize(int width, int height)
{
}
