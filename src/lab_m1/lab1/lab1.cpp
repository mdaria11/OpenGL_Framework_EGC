#include "lab_m1/lab1/lab1.h"

#include <vector>
#include <iostream>

using namespace std;
using namespace m1;

float red, green, blue;
int id;
vector<string> shapes{"box", "sphere", "teapot"};
float x, y, z, xcube, ycube, zcube, yinit;
bool spacepressed, godown;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Lab1::Lab1()
{
    // TODO(student): Never forget to initialize class variables!

}


Lab1::~Lab1()
{
}


void Lab1::Init()
{
    // Load a mesh from file into GPU memory. We only need to do it once,
    // no matter how many times we want to draw this mesh.

    red = 0;
    green = 0.2;
    blue = 0;

    id = 0;

    x = -1;
    y = 0.5;
    z = 0;

    xcube = 3;
    ycube = 0.4;
    yinit = ycube;
    zcube = 0;

    spacepressed = false;
    godown = false;
        
    {
        Mesh* mesh = new Mesh("box");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }


    {
        Mesh* mesh = new Mesh("sphere");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "sphere.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("teapot");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "teapot.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("bunny");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "animals"), "bunny.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    // TODO(student): Load some more meshes. The value of RESOURCE_PATH::MODELS
    // is actually a path on disk, go there and you will find more meshes.

}


void Lab1::FrameStart()
{
}


void Lab1::Update(float deltaTimeSeconds)
{
    glm::ivec2 resolution = window->props.resolution;

    // Sets the clear color for the color buffer

    // TODO(student): Generalize the arguments of `glClearColor`.
    // You can, for example, declare three variables in the class header,
    // that will store the color components (red, green, blue).
    glClearColor(red, green, blue, 1);

    // Clears the color buffer (using the previously set color) and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);

    // Render the object
    RenderMesh(meshes[shapes[id]], glm::vec3(1, 0.5f, 0), glm::vec3(0.5f));

    // Render the object again but with different properties
    RenderMesh(meshes["bunny"], glm::vec3(x, y, z), glm::vec3(0.02f));

    RenderMesh(meshes["box"], glm::vec3(xcube, ycube, zcube), glm::vec3(0.7f));

    // TODO(student): We need to render (a.k.a. draw) the mesh that
    // was previously loaded. We do this using `RenderMesh`. Check the
    // signature of this function to see the meaning of its parameters.
    // You can draw the same mesh any number of times.

}


void Lab1::FrameEnd()
{
    DrawCoordinateSystem();
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Lab1::OnInputUpdate(float deltaTime, int mods)
{
    // Treat continuous update based on input

    // TODO(student): Add some key hold events that will let you move
    // a mesh instance on all three axes. You will also need to
    // generalize the position used by `RenderMesh`.

    //1 sec   3 s
    //0.016   x

    float speed = 3;

    if (window->KeyHold(GLFW_KEY_W))
    {
        y = y + speed*deltaTime;
    }
    if (window->KeyHold(GLFW_KEY_A))
    {
        x = x - speed * deltaTime;
    }
    if (window->KeyHold(GLFW_KEY_S))
    {
        y = y - speed * deltaTime;
    }
    if (window->KeyHold(GLFW_KEY_D))
    {
        x = x + speed * deltaTime;
    }
    if (window->KeyHold(GLFW_KEY_E))
    {
        z = z + speed * deltaTime;
    }
    if (window->KeyHold(GLFW_KEY_Q))
    {
        z = z - speed * deltaTime;
    }

    if (spacepressed)
    {
        ycube = ycube + speed*deltaTime;

        if (ycube > 2)
        {
            godown = true;
            spacepressed = false;
        }
    }

    if (godown)
    {
        ycube = ycube - speed * deltaTime;

        if (ycube <= yinit)
        {
            godown = false;
        }
    }

}


void Lab1::OnKeyPress(int key, int mods)
{
    // Add key press event
    if (key == GLFW_KEY_F) {
        // TODO(student): Change the values of the color components.

        if (red != 1)
        {
            red = red + 0.2;
        }
        else
        {
            red = 0;
        }

    }

    if (key == GLFW_KEY_P)
    {
        if (id == 2)
        {
            id = 0;
        }
        else
        {
            id++;
        }
    }

    if (key == GLFW_KEY_SPACE)
    {
        spacepressed = true;
    }

    // TODO(student): Add a key press event that will let you cycle
    // through at least two meshes, rendered at the same position.
    // You will also need to generalize the mesh name used by `RenderMesh`.

}


void Lab1::OnKeyRelease(int key, int mods)
{
    // Add key release event

}


void Lab1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
  //  x = mouseX/400.0f;
   // y = -mouseY/200.0f;
   // printf("%d %d\n", mouseX, mouseY);
   // printf("%d %d\n", x, y);
}


void Lab1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Lab1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Lab1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
    // Treat mouse scroll event
}


void Lab1::OnWindowResize(int width, int height)
{
    // Treat window resize event
}
