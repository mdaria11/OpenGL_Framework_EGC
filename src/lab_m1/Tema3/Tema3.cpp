#include "lab_m1/Tema3/Tema3.h"

#include <vector>
#include <string>
#include <iostream>

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema3::Tema3()
{
}


Tema3::~Tema3()
{
}


void Tema3::Init()
{
    camera = new implemented::Camerahomework3();
    camera->Set(glm::vec3(0, 7.65, 8.46), glm::vec3(0, 6.88, 7.83), glm::vec3(0, 0.61, -0.74));
    
    //create tree
    {
        Mesh* mesh = new Mesh("cone");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "cone.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("trunk");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    //create rock
    {
        Mesh* mesh = new Mesh("sphere");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "sphere.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    //create ground
    {
        Mesh* mesh = new Mesh("ground");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "plane50.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    //player variables
    angleplayer = 0;
    positionplayer = glm::vec3(0, 0, 0);
    mouseposx = 0;
    score = 0;

    //Shader variables and stuff
    const string sourceTextureDir = PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema3", "textures");

    // Load textures
    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(sourceTextureDir, "leavessmall_resized.png").c_str(), GL_REPEAT);
        mapTextures["leaves"] = texture;
    }

    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(sourceTextureDir, "trunk_resized.png").c_str(), GL_REPEAT);
        mapTextures["trunk"] = texture;
    }

    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(sourceTextureDir, "snow_resized.png").c_str(), GL_REPEAT);
        mapTextures["ground"] = texture;
    }

    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(sourceTextureDir, "rock_resized.png").c_str(), GL_REPEAT);
        mapTextures["rock"] = texture;
    }

    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(sourceTextureDir, "metal_resized.png").c_str(), GL_REPEAT);
        mapTextures["metal"] = texture;
    }

    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(sourceTextureDir, "present_resized.png").c_str(), GL_REPEAT);
        mapTextures["present"] = texture;
    }

    //shader
    {
        Shader* shader = new Shader("LabShader");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema3", "shaders", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema3", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }

    //projection matrix used for main viewport
    projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);

    obstaclesrendered = 0;
    gameover = false;
    once = true;
}

//function that creates a mesh
Mesh* Tema3::CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned int>& indices)
{
    unsigned int VAO = 0;
    // Create the VAO and bind it
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Create the VBO and bind it
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Send vertices data into the VBO buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

    // Create the IBO and bind it
    unsigned int IBO;
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

    // Send indices data into the IBO buffer
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

    // ========================================================================
    // This section demonstrates how the GPU vertex shader program
    // receives data.

    // TODO(student): If you look closely in the `Init()` and `Update()`
    // functions, you will see that we have three objects which we load
    // and use in three different ways:
    // - LoadMesh   + LabShader (this lab's shader)
    // - CreateMesh + VertexNormal (this shader is already implemented)
    // - CreateMesh + LabShader (this lab's shader)
    // To get an idea about how they're different from one another, do the
    // following experiments. What happens if you switch the color pipe and
    // normal pipe in this function (but not in the shader)? Now, what happens
    // if you do the same thing in the shader (but not in this function)?
    // Finally, what happens if you do the same thing in both places? Why?

    // Set vertex position attribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

    // Set vertex normal attribute
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

    // Set texture coordinate attribute
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));

    // Set vertex color attribute
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));
    // ========================================================================

    // Unbind the VAO
    glBindVertexArray(0);

    // Check for OpenGL errors
    CheckOpenGLError();

    // Mesh information is saved into a Mesh object
    meshes[name] = new Mesh(name);
    meshes[name]->InitFromBuffer(VAO, static_cast<unsigned int>(indices.size()));
    meshes[name]->vertices = vertices;
    meshes[name]->indices = indices;
    return meshes[name];
}

void Tema3::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}

void Tema3::DrawTree(glm::vec3 location)
{
    glm::mat4 treetrunkmodel, treeleafmodellow, treeleafmodelhigh;

    treetrunkmodel = glm::translate(glm::mat4(1), location);
    treetrunkmodel = glm::translate(treetrunkmodel, glm::vec3(0, 0.3, 0));
    treetrunkmodel = glm::scale(treetrunkmodel, glm::vec3(0.2, 1, 0.2));
    RenderSimpleMesh_hw(meshes["trunk"], shaders["LabShader"], treetrunkmodel, glm::vec3(0.27, 0.23, 0.18), mapTextures["trunk"]);

    treeleafmodellow = glm::translate(glm::mat4(1), location);
    treeleafmodellow = glm::translate(treeleafmodellow, glm::vec3(0, 1.2, 0));
    treeleafmodellow = glm::scale(treeleafmodellow, glm::vec3(0.5, 0.5, 0.5));
    RenderSimpleMesh_hw(meshes["cone"], shaders["LabShader"], treeleafmodellow, glm::vec3(0, 1, 0), mapTextures["leaves"]);

    treeleafmodelhigh = glm::translate(glm::mat4(1), location);
    treeleafmodelhigh = glm::translate(treeleafmodelhigh, glm::vec3(0, 1.6, 0));
    treeleafmodelhigh = glm::scale(treeleafmodelhigh, glm::vec3(0.3, 0.3, 0.3));
    RenderSimpleMesh_hw(meshes["cone"], shaders["LabShader"], treeleafmodelhigh, glm::vec3(0, 1, 0), mapTextures["leaves"]);
}

void Tema3::DrawRock(glm::vec3 location)
{
    glm::mat4 rockmodel, rockmodel2, rockmodel3;

    rockmodel = glm::translate(glm::mat4(1), location);
    rockmodel = glm::translate(rockmodel, glm::vec3(-0.3, 0.2, 0));
    RenderSimpleMesh_hw(meshes["sphere"], shaders["LabShader"], rockmodel, glm::vec3(1, 0, 0), mapTextures["rock"]);

    rockmodel2 = glm::translate(glm::mat4(1), location);
    rockmodel2 = glm::translate(rockmodel2, glm::vec3(0.2, 0.2, 0));
    rockmodel2 = glm::scale(rockmodel2, glm::vec3(0.8, 0.8, 0.8));
    RenderSimpleMesh_hw(meshes["sphere"], shaders["LabShader"], rockmodel2, glm::vec3(1, 0, 0), mapTextures["rock"]);

    rockmodel3 = glm::translate(glm::mat4(1), location);
    rockmodel3 = glm::translate(rockmodel3, glm::vec3(0.5, 0.25, 0));
    rockmodel3 = glm::scale(rockmodel3, glm::vec3(1.1, 1.1, 1.1));
    RenderSimpleMesh_hw(meshes["sphere"], shaders["LabShader"], rockmodel3, glm::vec3(1, 0, 0), mapTextures["rock"]);
}

void Tema3::DrawPole(glm::vec3 location)
{
    glm::mat4 pole, theotherthing;

    pole = glm::translate(glm::mat4(1), location);
    pole = glm::translate(pole, glm::vec3(0, 1.2, 0));
    pole = glm::scale(pole, glm::vec3(0.2, 3.5, 0.2));
    RenderSimpleMesh_hw(meshes["trunk"], shaders["LabShader"], pole, glm::vec3(0, 0, 0), mapTextures["metal"]);

    theotherthing = glm::translate(glm::mat4(1), location);
    theotherthing = glm::translate(theotherthing, glm::vec3(0, 3, 0));
    theotherthing = glm::scale(theotherthing, glm::vec3(1.2, 0.2, 0.3));
    RenderSimpleMesh_hw(meshes["trunk"], shaders["LabShader"], theotherthing, glm::vec3(0, 0, 0), mapTextures["metal"]);
}

void Tema3::DrawPresent(glm::vec3 location)
{
    glm::mat4 presentmodel;

    presentmodel = glm::translate(glm::mat4(1), location);
    presentmodel = glm::translate(presentmodel, glm::vec3(0, 0.2, 0));
    presentmodel = glm::scale(presentmodel, glm::vec3(0.4, 0.4, 0.4));
    RenderSimpleMesh_hw(meshes["trunk"], shaders["LabShader"], presentmodel, glm::vec3(0.27, 0.23, 0.18), mapTextures["present"]);
}

void Tema3::DrawPlayer(glm::mat4 model)
{
    glm::mat4 playermodel, rightskimodel, leftskimodel;

    glm::mat4 playermov, skimov, skileftmov;

    playermodel = glm::mat4(1);
    playermodel = glm::translate(playermodel, glm::vec3(0, 0.53, 0));
    playermodel = glm::scale(playermodel, glm::vec3(0.5, 1, 0.5));
    playermov = model * playermodel;
    RenderSimpleMesh_hw(meshes["trunk"], shaders["LabShader"], playermov, glm::vec3(0.41, 0.28, 0.47));

    rightskimodel = glm::mat4(1);
    rightskimodel = glm::translate(rightskimodel, glm::vec3(-0.2, 0.015, 0.1));
    rightskimodel = glm::scale(rightskimodel, glm::vec3(0.1, 0.05, 1.6));
    skimov = model * rightskimodel;
    RenderSimpleMesh_hw(meshes["trunk"], shaders["LabShader"], skimov, glm::vec3(0.23, 0.85, 0.7));

    leftskimodel = glm::mat4(1);
    leftskimodel = glm::translate(leftskimodel, glm::vec3(0.2, 0.015, 0.1));
    leftskimodel = glm::scale(leftskimodel, glm::vec3(0.1, 0.05, 1.6));
    skileftmov = model * leftskimodel;
    RenderSimpleMesh_hw(meshes["trunk"], shaders["LabShader"], skileftmov, glm::vec3(0.23, 0.85, 0.7));
}

void Tema3::DrawObstacles()
{
    for (int i = obstaclesrendered; i < 20; i++)
    {
        int choose = rand() % 4;
        float obsx, obsz, obsy;

        obsx = positionplayer.x - 12 + fmod(rand(), positionplayer.x + 13 - positionplayer.x + 12); 
        obsz = positionplayer.z + 8 + fmod(rand(), ((positionplayer.z + 8 + 10 + 1) - (positionplayer.z + 8)));
        obsy = 0;

        glm::vec3 auxplayerpos = glm::vec3(positionplayer.x, 0, positionplayer.z);
        glm::vec3 inbetween = glm::vec3(obsx, obsy, obsz) - auxplayerpos;
        
        float auxy = inbetween.y;
        inbetween.y = inbetween.y * glm::cos(RADIANS(20)) - inbetween.z * glm::sin(RADIANS(20));
        inbetween.z = inbetween.z * glm::cos(RADIANS(20)) + auxy * glm::sin(RADIANS(20));

        glm::vec4 posobs = glm::mat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, positionplayer.x, positionplayer.y, positionplayer.z, 1) * glm::vec4(inbetween.x, inbetween.y, inbetween.z, 1);

        nrmesh.push_back((int)choose);
        positionobs.push_back(glm::vec3(posobs.x, posobs.y, posobs.z));
    }

    obstaclesrendered = 20;

    for (int i = 0; i < nrmesh.size(); i++)
    {
        int auxmesh = nrmesh[i];

        switch (auxmesh) {
        case 0:
            DrawTree(positionobs[i]);
            break;
        case 1:
            DrawRock(positionobs[i]);
            break;
        case 2:
            DrawPole(positionobs[i]);
            break;
        case 3:
            DrawPresent(positionobs[i]);
            break;
        }
    }

    for (int i = 0; i < nrmesh.size(); i++)
    {
        if (positionobs[i].z < positionplayer.z - 8)
        {
            nrmesh.erase(nrmesh.begin() + i);
            positionobs.erase(positionobs.begin() + i);
            obstaclesrendered --;
        }
    }
}

void Tema3::CheckCollision()
{
    float distance;

    for (int i = 0; i < nrmesh.size(); i++)
    {
        distance = sqrt((positionplayer.x - positionobs[i].x) * (positionplayer.x - positionobs[i].x) + (positionplayer.z - positionobs[i].z) * (positionplayer.z - positionobs[i].z));
        
        if (distance < 0.40)
        {
            if (nrmesh[i] == 3)
            {
                score++;

            }
            else
            {
                gameover = true;
            }

            nrmesh.erase(nrmesh.begin() + i);
            positionobs.erase(positionobs.begin() + i);
            obstaclesrendered--;

            return;
        }
    }
}


void Tema3::Update(float deltaTimeSeconds)
{
    if (gameover)
    {
        if (once)
        {
            printf("Your score is %d\n", score);
            once = false;
        }
        return;
    }

    textureapplied = 0;
    deplasamenttrue = 0;

    float auxangleplayer = RADIANS( -1 * mouseposx * 8);

    if (auxangleplayer <  0.87 && auxangleplayer > -0.87)
    {
        angleplayer = auxangleplayer;
    }

    glm::vec3 dir;
    float theta;
    float speed;

    speed = 6 * deltaTimeSeconds;
    theta = RADIANS(270) - angleplayer;
    dir = glm::vec3(glm::cos(theta), 0, glm::sin(theta));

    float auxy = dir.y;
    dir.y = dir.y * glm::cos(RADIANS(20)) - dir.z * glm::sin(RADIANS(20));
    dir.z = dir.z * glm::cos(RADIANS(20)) + auxy * glm::sin(RADIANS(20));

    positionplayer -= glm::normalize(dir) * speed;
    camera->MoveonDirection(glm::normalize(dir), -speed);

    glm::mat4 Movementmatrix = glm::translate(glm::mat4(1), positionplayer);
    Movementmatrix = glm::rotate(Movementmatrix, RADIANS(20), glm::vec3(1, 0, 0));
    Movementmatrix = glm::rotate(Movementmatrix, angleplayer, glm::vec3(0, 1, 0));
    DrawPlayer(Movementmatrix);

    textureapplied = 1;
    deplasamenttrue = 1;

    deplasamenttext = glm::vec2(positionplayer.x * 0.02, positionplayer.z * 0.02);

    glm::mat4 Groundmatrix = glm::translate(glm::mat4(1), positionplayer);
    Groundmatrix = glm::rotate(Groundmatrix, RADIANS(20), glm::vec3(1, 0, 0));
    RenderSimpleMesh_hw(meshes["ground"], shaders["LabShader"], Groundmatrix,  glm::vec3(1, 1, 1), mapTextures["ground"]);

    deplasamenttrue = 0;

    //other meshes
   
    DrawObstacles();

    CheckCollision();
}


void Tema3::FrameEnd()
{
}


//render function
void Tema3::RenderSimpleMesh_hw(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color, Texture2D* texture1)
{
    if (!mesh || !shader || !shader->GetProgramID())
        return;

    // Render an object using the specified shader and the specified position
    glUseProgram(shader->program);

    int object_color = glGetUniformLocation(shader->program, "object_color");
    glUniform3f(object_color, color.r, color.g, color.b);

    // TODO(student): Set any other shader uniforms that you need

    // Bind model matrix
    GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
    glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    // Bind view matrix
    glm::mat4 viewMatrix = camera->GetViewMatrix();
    int loc_view_matrix = glGetUniformLocation(shader->program, "View");
    glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

    // Bind projection matrix
    glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
    int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
    glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    int loc_textureapplied = glGetUniformLocation(shader->program, "textureapplied");
    glUniform1i(loc_textureapplied, textureapplied);

    int loc_deplasamenttrue = glGetUniformLocation(shader->program, "deplasamenttrue");
    glUniform1i(loc_deplasamenttrue, deplasamenttrue);

    int loc_deplasamenttext = glGetUniformLocation(shader->program, "deplasamenttext");
    glUniform2fv(loc_deplasamenttext, 1, glm::value_ptr(deplasamenttext));

    if (texture1)
    {
        // TODO(student): Do these:
        // - activate texture location 0
        // - bind the texture1 ID
        // - send theuniform value

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1->GetTextureID());
        glUniform1i(glGetUniformLocation(shader->program, "texture_1"), 0);

    }

    // Draw the object
    glBindVertexArray(mesh->GetBuffers()->m_VAO);
    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema3::OnInputUpdate(float deltaTime, int mods)
{
    
    if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        float cameraSpeed = 10.0f;

        if (window->KeyHold(GLFW_KEY_W)) {
            // TODO(student): Translate the camera forward
            camera->TranslateForward(cameraSpeed * deltaTime);
        }

        if (window->KeyHold(GLFW_KEY_A)) {
            // TODO(student): Translate the camera to the left
            camera->TranslateRight(-1 * cameraSpeed * deltaTime);
        }

        if (window->KeyHold(GLFW_KEY_S)) {
            // TODO(student): Translate the camera backward
            camera->TranslateForward(-1 * cameraSpeed * deltaTime);
        }

        if (window->KeyHold(GLFW_KEY_D)) {
            // TODO(student): Translate the camera to the right
            camera->TranslateRight(cameraSpeed * deltaTime);
        }

        if (window->KeyHold(GLFW_KEY_Q)) {
            // TODO(student): Translate the camera downward
            camera->TranslateUpward(-1 * cameraSpeed * deltaTime);
        }

        if (window->KeyHold(GLFW_KEY_E)) {
            // TODO(student): Translate the camera upward

            camera->TranslateUpward(cameraSpeed * deltaTime);

        }
    }
   
}


void Tema3::OnKeyPress(int key, int mods)
{
    if (key == GLFW_KEY_S)
    {
        gameover = false;
        once = true;
        score = 0;
    }
}


void Tema3::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema3::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    mouseposx = ((float)resolution.x/2.0f - (float)mouseX)/56.0f;
    

    if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        float sensivityOX = 0.001f;
        float sensivityOY = 0.001f;

        if (window->GetSpecialKeyState() == 0) {
            // TODO(student): Rotate the camera in first-person mode around
            // OX and OY using `deltaX` and `deltaY`. Use the sensitivity
            // variables for setting up the rotation speed.

            camera->RotateFirstPerson_OY(-deltaX * sensivityOY);
            camera->RotateFirstPerson_OX(-deltaY * sensivityOX);

        }

        if (window->GetSpecialKeyState() & GLFW_MOD_CONTROL) {
            // TODO(student): Rotate the camera in third-person mode around
            // OX and OY using `deltaX` and `deltaY`. Use the sensitivity
            // variables for setting up the rotation speed.

            camera->RotateThirdPerson_OY(-deltaX * sensivityOY);
            camera->RotateThirdPerson_OX(-deltaY * sensivityOX);

        }
    }
    
}


void Tema3::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Tema3::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema3::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema3::OnWindowResize(int width, int height)
{
}
