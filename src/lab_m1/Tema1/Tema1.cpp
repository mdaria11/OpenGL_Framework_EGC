#include "lab_m1/Tema1/Tema1.h"
#include "lab_m1/Tema1/transform2D.h"
#include "lab_m1/Tema1/Meshes.h"

#include <glm/gtx/string_cast.hpp>
#include <vector>
#include <iostream>
#include <random>

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema1::Tema1()
{
}


Tema1::~Tema1()
{
}

void Tema1::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    //MESHES

    { // body triangle mesh

        std::vector<VertexFormat> verticesbody =
        {
            VertexFormat(glm::vec3(0, 0, 0), glm::vec3(0.58, 0.29, 0)), //0
            VertexFormat(glm::vec3(100, 0, 0), glm::vec3(0.58, 0.29, 0)), //1
            VertexFormat(glm::vec3(50, 150, 0), glm::vec3(0.58, 0.29, 0)), //2
        };

        std::vector<unsigned int> indicesbody = { 0, 1, 2 };

        meshes["duckbody"] = new Mesh("duckbody");
        meshes["duckbody"]->InitFromData(verticesbody, indicesbody);

    }

    { // beak triangle mesh

        std::vector<VertexFormat> verticesbeak =
        {
            VertexFormat(glm::vec3(0, 0, 0), glm::vec3(0.9, 0.9, 0)), //0
            VertexFormat(glm::vec3(100, 0, 0), glm::vec3(0.9, 0.9, 0)), //1
            VertexFormat(glm::vec3(50, 150, 0), glm::vec3(0.9, 0.9, 0)), //2
        };

        std::vector<unsigned int> indicesbeak = { 0, 1, 2 };

        meshes["duckbeak"] = new Mesh("duckbeak");
        meshes["duckbeak"]->InitFromData(verticesbeak, indicesbeak);

    }

    { // right wing triangle mesh

        std::vector<VertexFormat> verticeswingr =
        {
            VertexFormat(glm::vec3(0, 0, 0), glm::vec3(0.58, 0.29, 0)), //0
            VertexFormat(glm::vec3(70, 0, 0), glm::vec3(0.58, 0.29, 0)), //1
            VertexFormat(glm::vec3(110, 50, 0), glm::vec3(0.58, 0.29, 0)), //2
        };

        std::vector<unsigned int> indiceswingr = { 0, 1, 2 };

        meshes["duckwingr"] = new Mesh("duckwingr");
        meshes["duckwingr"]->InitFromData(verticeswingr, indiceswingr);

    }

    { // left wing triangle mesh

        std::vector<VertexFormat> verticeswingl =
        {
            VertexFormat(glm::vec3(0, 0, 0), glm::vec3(0.58, 0.29, 0)), //0
            VertexFormat(glm::vec3(-70, 0, 0), glm::vec3(0.58, 0.29, 0)), //1
            VertexFormat(glm::vec3(-110, 50, 0), glm::vec3(0.58, 0.29, 0)), //2
        };

        std::vector<unsigned int> indiceswingl = { 0, 1, 2 };

        meshes["duckwingl"] = new Mesh("duckwingl");
        meshes["duckwingl"]->InitFromData(verticeswingl, indiceswingl);

    }

    //head circle mesh
    Mesh* circle = Meshes::createCircle("circle", 40, glm::vec3(0.0, 0.4, 0.0), 0.1);
    AddMeshToList(circle);

    //eye and pupil circle meshes
    Mesh* circleeye = Meshes::createCircle("circleeye", 15, glm::vec3(1, 1, 1), 0.2);
    AddMeshToList(circleeye);
    Mesh* circleeyepupil = Meshes::createCircle("circleeyepupil", 8, glm::vec3(0, 0, 0), 0.3);
    AddMeshToList(circleeyepupil);

    //interface meshes
    Mesh* scoreframe = Meshes::CreateRectangle("scoreframe", 250, 50, 1, glm::vec3(1, 1, 1), false);
    AddMeshToList(scoreframe);
    Mesh* scorem = Meshes::CreateRectangle("scorem", 1, 50, 0.9, glm::vec3(0.5, 0, 0), true);
    AddMeshToList(scorem);
    Mesh* life = Meshes::createCircle("life", 15, glm::vec3(0.236, 0.666, 0.241), 0.9);
    AddMeshToList(life);
    Mesh* bullet = Meshes::CreateRectangle("bullet", 5, 30, 0.9, glm::vec3(0.89, 0.97, 0.40), false);
    AddMeshToList(bullet);
    Mesh* grass = Meshes::CreateRectangle("grass", resolution.x, 200, 1, glm::vec3(0.3, 0.8, 0), true);
    AddMeshToList(grass);

    //red pointer mesh
    Mesh* mouse = Meshes::createCircle("mouse", 5, glm::vec3(1, 0, 0), 2);
    AddMeshToList(mouse);
    //box used to visualise shooting area around the duck
    Mesh* collisionbox = Meshes::CreateRectangle("collisionbox", 120, 260, 0, glm::vec3(0, 0, 0), false);
    AddMeshToList(collisionbox);

    //VARIABLES

    //speeds for direction and wings movement
    speedx = 500; 
    speedxinit = 500;
    wingstep = -1.5;
    wingstepleft = 1.5;
    wingup = true;

    //variables used for moving the duck around
    directionx = 0;
    directiony = 0;
    angle = 0;

    duckin = true;
    nrducks = 0;

    circlex = -1;
    circley = -1;
    score = 0;
    maxscoredreached = false;
    escape = false;
    shot = false;
    lives = 3;
    bullets = 3;
    maxtime = 5;
    rback = 0;
    gback = 0.5f;
    bback = 1.0f;

    //matrix used for the shooting area rectangle
    CollisionMatrix = glm::mat3(1);
    CollisionMatrix *= transform2D::Translate(-60, -180);

    //arrange parts of the duck relative to each other

    modelMatrixheadaux = glm::mat3(1);

    modelMatrixbody = glm::mat3(1);
    modelMatrixbody *= transform2D::Translate(-50, -180);

    modelMatrixbeak = glm::mat3(1);
    modelMatrixbeak *= transform2D::Translate(-10, 30);
    modelMatrixbeak *= transform2D::Rotate(-0.4);
    modelMatrixbeak *= transform2D::Scale(0.4, 0.4);

    modelMatrixhead = glm::mat3(1);

    modelMatrixeye = glm::mat3(1);
    modelMatrixeye *= transform2D::Translate(-10, 10);
}


void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(rback, gback, bback, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}

//function that does a black screen when its game over
void Tema1::GameOver()
{
    rback = 0;
    gback = 0;
    bback = 0;
}

//function that draws a little red circle around the mouse
void Tema1::DrawMouse()
{
    glm::mat3 MouseMatrix;
    MouseMatrix = glm::mat3(1);
    MouseMatrix *= transform2D::Translate(circlex, logiccircley);
    RenderMesh2D(meshes["mouse"], shaders["VertexColor"], MouseMatrix);
}

//draws the interface of the game
void Tema1::DrawInterface()
{
    glm::mat3 GrassMatrix;
    GrassMatrix = glm::mat3(1);
    RenderMesh2D(meshes["grass"], shaders["VertexColor"], GrassMatrix);

    glm::mat3 ScoreFrameMatrix;
    ScoreFrameMatrix = glm::mat3(1);
    ScoreFrameMatrix *= transform2D::Translate(1000, 600);
    RenderMesh2D(meshes["scoreframe"], shaders["VertexColor"], ScoreFrameMatrix);

    //if we hit max score we do a "flash" on the screen and reset the score, going to the next level (duck moves faster)
    if (score >= 250)
    {
        maxscoredreached = true;
        score = 0;
    }
    glm::mat3 ScoremMatrix;
    ScoremMatrix = glm::mat3(1);
    ScoremMatrix *= transform2D::Translate(1000, 600);
    ScoremMatrix *= transform2D::Scale(score, 1);
    RenderMesh2D(meshes["scorem"], shaders["VertexColor"], ScoremMatrix);

    glm::mat3 LivesMatrix;
    glm::mat3 BulletsMatrix;

    if (bullets >= 1)
    {
        BulletsMatrix = glm::mat3(1);
        BulletsMatrix *= transform2D::Translate(1160, 675);
        RenderMesh2D(meshes["bullet"], shaders["VertexColor"], BulletsMatrix);

        if (bullets >= 2)
        {
            BulletsMatrix = glm::mat3(1);
            BulletsMatrix *= transform2D::Translate(1180, 675);
            RenderMesh2D(meshes["bullet"], shaders["VertexColor"], BulletsMatrix);

            if (bullets == 3)
            {
                BulletsMatrix = glm::mat3(1);
                BulletsMatrix *= transform2D::Translate(1200, 675);
                RenderMesh2D(meshes["bullet"], shaders["VertexColor"], BulletsMatrix);
            }
        }
    }

    if (lives >= 1)
    {
        LivesMatrix = glm::mat3(1);
        LivesMatrix *= transform2D::Translate(1040, 690);
        RenderMesh2D(meshes["life"], shaders["VertexColor"], LivesMatrix);

        if (lives >= 2)
        {
            LivesMatrix = glm::mat3(1);
            LivesMatrix *= transform2D::Translate(1080, 690);
            RenderMesh2D(meshes["life"], shaders["VertexColor"], LivesMatrix);

            if (lives == 3)
            {
                LivesMatrix = glm::mat3(1);
                LivesMatrix *= transform2D::Translate(1120, 690);
                RenderMesh2D(meshes["life"], shaders["VertexColor"], LivesMatrix);
            }
        }
    }


}

//function that makes the matrix used for movement and rotation of the duck
glm::mat3 Tema1::MovementMatrix(float directionX, float directionY, float radians)
{
    glm::mat3 modelMatrixmovement = glm::mat3(1);
    modelMatrixmovement *= transform2D::Translate(directionX, directionY);
    modelMatrixmovement *= transform2D::Rotate(radians);

    return modelMatrixmovement;
}

//function that generates a random starting point and angle of the duck
void Tema1::CalculateDirectionLine(float *directionX, float *radians)
{
    *directionX = rand() % 801 + 200; //generates a random x coordonate spawn point for the duck

    //generates a random angle between 30-60 and 120-150 degrees for the duck 
    float radians1 = 0.52 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1.04 - 0.52)));
    float radians2 = 2.09 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (2.61 - 2.09)));
    int choose = rand() % 2;

    if (choose == 0)
    {
        *radians = radians1;
    }
    else
    {
        *radians = radians2;
    }
}

//function that renders the duck depending on its coordonates and angle
void Tema1::DuckAnimation(float directionx, float directiony, float angle, float deltaTimeSeconds)
{
    modelMatrixbodyaux = MovementMatrix(directionx, directiony, angle) * modelMatrixbody;
    RenderMesh2D(meshes["duckbody"], shaders["VertexColor"], modelMatrixbodyaux);

    modelMatrixbeakaux = MovementMatrix(directionx, directiony, angle) * modelMatrixbeak;
    RenderMesh2D(meshes["duckbeak"], shaders["VertexColor"], modelMatrixbeakaux);

    //here we do the wings animation
    if (wingup)
    {
        wingstep = wingstep + 4 * deltaTimeSeconds;
        wingstepleft = wingstepleft - 4 * deltaTimeSeconds;

        if (wingstep >= 0.5)
        {
            wingup = false;
        }
    }
    else
    {
        wingstep = wingstep - 2 * deltaTimeSeconds;
        wingstepleft = wingstepleft + 2 * deltaTimeSeconds;

        if (wingstep <= -1)
        {
            wingup = true;
        }
    }

    if (shot) //if the duck was shot the wings will not move and we re going to keep them at the same angle
    {
        wingstep = -1.5;
        wingstepleft = 1.5;
    }

    modelMatrixwingr = glm::mat3(1);
    modelMatrixwingr *= transform2D::Translate(20, -50);
    modelMatrixwingr *= transform2D::Rotate(wingstep);
    modelMatrixwingraux = MovementMatrix(directionx, directiony, angle) * modelMatrixwingr;
    RenderMesh2D(meshes["duckwingr"], shaders["VertexColor"], modelMatrixwingraux);


    modelMatrixwingl = glm::mat3(1);
    modelMatrixwingl *= transform2D::Translate(-20, -50);
    modelMatrixwingl *= transform2D::Rotate(wingstepleft);
    modelMatrixwinglaux = MovementMatrix(directionx, directiony, angle) * modelMatrixwingl;
    RenderMesh2D(meshes["duckwingl"], shaders["VertexColor"], modelMatrixwinglaux);

    modelMatrixheadaux = MovementMatrix(directionx, directiony, angle) * modelMatrixhead;
    RenderMesh2D(meshes["circle"], shaders["VertexColor"], modelMatrixheadaux);

    modelMatrixeyeaux = MovementMatrix(directionx, directiony, angle) * modelMatrixeye;
    RenderMesh2D(meshes["circleeye"], shaders["VertexColor"], modelMatrixeyeaux);
    RenderMesh2D(meshes["circleeyepupil"], shaders["VertexColor"], modelMatrixeyeaux);

    //uncomment these 2 lines if you want to see the collision box for the shooting 

    //CollisionMatrixaux = MovementMatrix(directionx, directiony, angle) * CollisionMatrix;
    //RenderMesh2D(meshes["collisionbox"], shaders["VertexColor"], CollisionMatrixaux);
}

//function that checks if the duck was shot or not
void Tema1::checkShooting()
{
    float shootingxaux, shootingyaux;

    shootingxaux = directionx + (shootingx - directionx) * cos(-1 * angle) - (shootingy - directiony) * sin(-1 * angle);
    shootingyaux = directiony + (shootingx - directionx) * sin(-1 * angle) + (shootingy - directiony) * cos(-1 * angle);

    if (shootingxaux > directionx - 60 && shootingxaux < directionx + 60 && shootingyaux > directiony - 180 && shootingyaux < directiony + 80)
    {
        shot = true;
    }
}

void Tema1::Update(float deltaTimeSeconds)
{
    if (lives == 0)
    {
        GameOver();
        return;
    }
    //drawing the grass, lives, bullets, score and red pointer for the mouse
    DrawInterface();
    DrawMouse();

    //if we need to launch a duck on the screen
    if (duckin)
    {
        bullets = 3;
        nrducks++;
        CalculateDirectionLine(&directionx, &actualangle); //generate random x and angle
        speedx = speedxinit;

        //for every 5 ducks we are going to increment the speed (hard cap at 1420-ish speed)
        if (nrducks > 5)
        {
            if (speedx < 1300)
            {
                nrducks = 1;
                speedx += speedx / 5;
                speedxinit = speedx;
            }
        }

        directiony = 50; 
        angle = -1 * (1.57 - actualangle); //calculate the angle of the duck to match the direction

        //calculate the angle of the reflection
        if (actualangle < 1.57)
        {
            relativeangle = actualangle;
        }
        else
        {
            relativeangle = 3.14 - actualangle;
        }

        //scaling for speedx and speedy to match the direction
        speedx = speedx * cos(actualangle);

        if (speedx < 0)
        {
            speedx = speedx * -1;
        }

        speedy = speedx * tan(actualangle);

        //initialize the boolean values (at first the duck is going up and last collision was on the downwall)
        goingup = true;
        upperwall = false;
        downwall = true;
        rightwall = false;
        leftwall = false;

        //initialize the boolean values for the direction of the duck (its either going left or right based on initial angle value)
        if (actualangle < 1.57)
        {
            goingleft = false;
            goingright = true;
        }
        else
        {
            goingleft = true;
            goingright = false;
        }

        timeduck = 0;
        escape = false;
        shot = false;
        duckin = false;
    }

    if (shot) //if the duck was shot
    {
        if (directiony <= -200)
        {
            shot = false;
            duckin = true;
            score += 50;
        }
        DuckAnimation(directionx, directiony, 3.14, deltaTimeSeconds);
        directiony = directiony - 400 * deltaTimeSeconds;
        return;
    }

    if (escape) //if the duck escaped
    {
        if (directiony >= 900)
        {
            lives--;
            escape = false;
            duckin = true;
        }
        DuckAnimation(directionx, directiony, 0, deltaTimeSeconds);
        directiony = directiony + 200 * deltaTimeSeconds;
        return;
    }

    //escape conditions
    if (timeduck >= maxtime || bullets == 0)
    {
        escape = true;

        return;
    }

    //conditions for reaching the edge of the window

    if (directionx > 1260) //the right wall was hit
    {
        if (upperwall) 
        {
            relativeangle = 1.57 - relativeangle;
            angle = 3.14 - relativeangle;
            actualangle = 4.71 - relativeangle;

            upperwall = false;
        }
        if (downwall)
        {
            relativeangle = 1.57 - relativeangle;
            angle = relativeangle;
            actualangle = 1.57 + relativeangle;

            downwall = false;
        }
        if (!goingup && leftwall)
        {
            //relativeangle = relativeangle; relative angle remains the same
            actualangle = 4.71 - relativeangle;
            angle = -1 * (3.14 + relativeangle);

            leftwall = false;
        }
        if (goingup && leftwall)
        {
            //relativeangle = relativeangle; relative angle remains the same
            actualangle = 1.57 + relativeangle;
            angle = relativeangle;

            leftwall = false;
        }

        speedy = speedx * tan(actualangle);
        directionx = directionx - 400 * deltaTimeSeconds;

        rightwall = true;
        goingright = false;
        goingleft = true;
    }
    else if (directiony > 700) // the upper wall was hit
    {
        if (goingright && downwall)
        {
            //relativeangle = relativeangle;
            angle = -1 * (1.57 + relativeangle);
            actualangle = 6.28 - relativeangle;

            downwall = false;
        }
        if (goingleft && downwall)
        {
            //relativeangle = relativeangle;
            angle = 1.57 + relativeangle;
            actualangle = 3.14 + relativeangle;

            downwall = false;
        }
        if (leftwall)
        {
            relativeangle = 1.57 - relativeangle;
            angle = -1 * (1.57 + relativeangle);
            actualangle = 6.28 - relativeangle;

            leftwall = false;
        }
        if (rightwall)
        {
            relativeangle = 1.57 - relativeangle;
            angle = (1.57 + relativeangle);
            actualangle = 3.14 + relativeangle;

            rightwall = false;
        }

        speedy = speedx * tan(actualangle);
        directiony = directiony - 400 * deltaTimeSeconds;

        upperwall = true;
        goingup = false;
    }
    else if (directionx < -10) //the left wall was hit
    {
        if (upperwall)
        {
            relativeangle = 1.57 - relativeangle;
            angle = 3.14 + relativeangle;
            actualangle = 4.71 + relativeangle;

            upperwall = false;
        }
        if (downwall)
        {
            relativeangle = 1.57 - relativeangle;
            angle = -1 * relativeangle;
            actualangle = 1.57 - relativeangle;

            downwall = false;
        }
        if (!goingup && rightwall)
        {
            //relativeangle = relativeangle; relative angle remains the same
            actualangle = 4.71 + relativeangle;
            angle = 3.14 + relativeangle;

            rightwall = false;
        }
        if (goingup && rightwall)
        {
            //relativeangle = relativeangle; relative angle remains the same
            actualangle = 1.57 - relativeangle;
            angle = -1 * relativeangle;

            rightwall = false;
        }

        speedy = speedx * tan(actualangle);
        directionx = directionx + 400 * deltaTimeSeconds;

        leftwall = true;
        goingright = true;
        goingleft = false;
    }
    else if (directiony < 10) //the lower wall was hit
    {
        if (goingright && upperwall)
        {
            //relativeangle = relativeangle;
            angle = -1 * (1.57 - relativeangle);
            actualangle = relativeangle;

            upperwall = false;
        }
        if (goingleft && upperwall)
        {
            //relativeangle = relativeangle;
            angle = 1.57 - relativeangle;
            actualangle = 3.14 - relativeangle;

            upperwall = false;
        }
        if (rightwall)
        {
            relativeangle = 1.57 - relativeangle;
            angle = 1.57 - relativeangle;
            actualangle = 3.14 - relativeangle;

            rightwall = false;
        }
        if (leftwall)
        {
            relativeangle = 1.57 - relativeangle;
            angle = -1 * (1.57 - relativeangle);
            actualangle = relativeangle;

            leftwall = false;
        }

        speedy = speedx * tan(actualangle);
        directiony = directiony + 400 * deltaTimeSeconds;

        downwall = true;
        goingup = true;
    }
    else
    {
        if (actualangle > 1.57 && actualangle < 4.71) //the duck is moving to the left
        {
            directionx = directionx - speedx * deltaTimeSeconds;
            directiony = directiony - speedy * deltaTimeSeconds;
        }
        else //the duck is moving to the right
        {
            directionx = directionx + speedx * deltaTimeSeconds;
            directiony = directiony + speedy * deltaTimeSeconds;
        }
    }

    //render the duck with the coordonates and the angle calculated previously
    DuckAnimation(directionx, directiony, angle, deltaTimeSeconds);

    timeduck += deltaTimeSeconds;
}


void Tema1::FrameEnd()
{
}

//here we're going to do the "flash" thingy on screen when maxscore is reached
void Tema1::OnInputUpdate(float deltaTime, int mods)
{
    if (maxscoredreached)
    {
        if (rback < 1.0f)
        {
            rback = rback + 10 * deltaTime;
        }
        else
        {
            maxscoredreached = false;
            rback = 0;
        }
    }
}


void Tema1::OnKeyPress(int key, int mods)
{
    // Add key press event
}


void Tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
    circlex = (float)mouseX / ((float)resolution.x / 1280.0f);
    circley = mouseY;
    logiccircley = ((float)resolution.y / 2 + (float)resolution.y / 2 - (float)circley)/((float)resolution.y / 720.0f);
}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event

    if (button == GLFW_MOUSE_BUTTON_RIGHT) //its actually the left click but for some reason this one checks it ? i dont know man
    {
        if (bullets > 0) //if we have bullets
        {
            if (!escape && !shot) //the duck can be shot only if it didnt escape nor it is mid-shooting animation
            {
                //convert the mouse coordonates in logic ones
                shootingx = (float)mouseX / ((float)resolution.x / 1280.0f);
                shootingy = ((float)resolution.y / 2 + (float)resolution.y / 2 - (float)mouseY) / ((float)resolution.y / 720.0f);
                checkShooting();
            }

            bullets--;
        }
    }
}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema1::OnWindowResize(int width, int height)
{
}
