#include "lab_m1/Tema2/Tema2.h"

#include <vector>
#include <string>
#include <iostream>
#include <cmath>

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema2::Tema2()
{
}


Tema2::~Tema2()
{
}


void Tema2::Init()
{
    //camera with initial vectors
    camera = new implemented::Camerahw();
    camera->Set(glm::vec3(1.1258, 0.6, 0), glm::vec3(0, 0.25, 0), glm::vec3(-2.7553, 8.86261, 0));
    camera->RotateThirdPerson_OY(RADIANS(-30));

    //Tree geometry
    {
        CreateRectangle("trunktree", 1, 1, 5, glm::vec3(0.38, 0.30, 0.14));
        CreateRectangle("bigleaftree", 3, 3, 1, glm::vec3(0.21, 0.30, 0.18));
        CreateRectangle("smallleaftree", 1.5, 1.5, 1.5, glm::vec3(0.21, 0.30, 0.18));

        //arrange tree mesh parts relative to eachother
        TrunkMatrix = glm::mat4(1);
        TrunkMatrix = glm::translate(TrunkMatrix, glm::vec3(0, 0.375, 0));
        TrunkMatrix = glm::scale(TrunkMatrix, glm::vec3(0.25, 0.25, 0.25));

        BigLeafMatrix = glm::mat4(1);
        BigLeafMatrix = glm::translate(BigLeafMatrix, glm::vec3(0, 0.8, 0));
        BigLeafMatrix = glm::scale(BigLeafMatrix, glm::vec3(0.25, 0.25, 0.25));

        SmallLeafMatrix = glm::mat4(1);
        SmallLeafMatrix = glm::translate(SmallLeafMatrix, glm::vec3(0, 1, 0));
        SmallLeafMatrix = glm::scale(SmallLeafMatrix, glm::vec3(0.25, 0.25, 0.25));
    }

    //points that makes the road path and obstacles paths
    initialpoints =
    {
        glm::vec3(-13.76514, 0, 7.94472),
        glm::vec3(-14.3607, 0, 8.68734),
        glm::vec3(-14.73495, 0, 9.46891),
        glm::vec3(-14.81678, 0, 10.37014),
        glm::vec3(-14.76867, 0, 11.08913),
        glm::vec3(-14.61233, 0, 12.08439),
        glm::vec3(-14.45738, 0, 12.85312),
        glm::vec3(-14.04616, 0, 13.70428),
        glm::vec3(-13.69823, 0, 14.36734),
        glm::vec3(-12.83517, 0, 15.32417),
        glm::vec3(-11.75712, 0, 16.34166),
        glm::vec3(-10.59345, 0, 17.40836),
        glm::vec3(-9.10008, 0, 18.40718),
        glm::vec3(-7.34488, 0, 19.34781),
        glm::vec3(-5.30845, 0, 20.14298),
        glm::vec3(-3.57265, 0, 20.51148),
        glm::vec3(-1.74957, 0, 20.73451),
        glm::vec3(-0.13982, 0, 20.70542),
        glm::vec3(1.67356, 0, 20.36602),
        glm::vec3(3.72938, 0, 19.59994), //F
        glm::vec3(5.86277, 0, 18.58173),
        glm::vec3(7.97812, 0, 17.37794),
        glm::vec3(9.68816, 0, 16.22065),
        glm::vec3(11.0991, 0, 14.5144),
        glm::vec3(12.28234, 0, 12.58883),
        glm::vec3(13.00222, 0, 10.18316),
        glm::vec3(13.46159, 0, 7.29566),
        glm::vec3(13.65847, 0, 4.5066), //I
        glm::vec3(13.71784, 0, 1.8288),
        glm::vec3(13.67628, 0, -0.87256),
        glm::vec3(13.63472, 0, -3.32457),
        glm::vec3(13.63472, 0, -5.85969),
        glm::vec3(13.64966, 0, -8.58025),
        glm::vec3(13.63203, 0, -10.75453),
        glm::vec3(13.60372, 0, -13.01645),
        glm::vec3(13.65042, 0, -14.96351),
        glm::vec3(13.66868, 0, -16.75295),
        glm::vec3(13.64886, 0, -18.33875),
        glm::vec3(13.74797, 0, -19.7957),
        glm::vec3(13.81735, 0, -21.12381),
        glm::vec3(13.87681, 0, -22.54112),
        glm::vec3(13.98398, 0, -24.15552),
        glm::vec3(14.08465, 0, -25.47341),
        glm::vec3(13.85982, 0, -26.72771), //N
        glm::vec3(13.40295, 0, -27.75565),
        glm::vec3(12.71766, 0, -28.74552),
        glm::vec3(12.01333, 0, -29.48792),
        glm::vec3(11.22924, 0, -29.83889),
        glm::vec3(10, 0, -30),
        glm::vec3(8.81312, 0, -29.74737),
        glm::vec3(7.76832, 0, -29.22142),
        glm::vec3(7, 0, -28.5),
        glm::vec3(6.56906, 0, -27.43204),
        glm::vec3(6.28352, 0, -26.23278),
        glm::vec3(6.1499, 0, -24.77786),
        glm::vec3(6.0585, 0, -23.43881),
        glm::vec3(6, 0, -22),
        glm::vec3(6.01702, 0, -20.42682),
        glm::vec3(5.9211, 0, -19.06703),
        glm::vec3(5.71975, 0, -18.0237),
        glm::vec3(5.42689, 0, -16.95292), //K3
        glm::vec3(5, 0, -16),
        glm::vec3(4.60321, 0, -15.06762),
        glm::vec3(4.03579, 0, -14.33546),
        glm::vec3(3.1572, 0, -13.78634),
        glm::vec3(2.24201, 0, -13.38366),
        glm::vec3(1.23529, 0, -13.23722),
        glm::vec3(0.24688, 0, -13.26468),
        glm::vec3(-0.58595, 0, -13.36535),
        glm::vec3(-1.51945, 0, -13.61245),
        glm::vec3(-2.37974, 0, -13.96023),
        glm::vec3(-3.24002, 0, -14.63748),
        glm::vec3(-3.69762, 0, -15.44285), //W
        glm::vec3(-3.88066, 0, -16.34889),
        glm::vec3(-3.99048, 0, -17.15427),
        glm::vec3(-4.07285, 0, -18.2525),
        glm::vec3(-3.99048, 0, -19.88155),
        glm::vec3(-4.00879, 0, -21.30011),
        glm::vec3(-4.05455, 0, -22.58138),
        glm::vec3(-4.02909, 0, -24.20451),
        glm::vec3(-4, 0, -26), //P2
        glm::vec3(-4.09879, 0, -27.06243),
        glm::vec3(-4.23046, 0, -27.72076),
        glm::vec3(-4.38536, 0, -28.14674),
        glm::vec3(-4.73389, 0, -28.6037),
        glm::vec3(-5.3284, 0, -29.03106),
        glm::vec3(-6.02731, 0, -29.40918),
        glm::vec3(-6.61594, 0, -29.7035),
        glm::vec3(-7.15809, 0, -29.88163),
        glm::vec3(-7.76221, 0, -29.99781),
        glm::vec3(-8.3973, 0, -30.00555),
        glm::vec3(-9.08661, 0, -29.95134),
        glm::vec3(-9.7372, 0, -29.78095), //T2
        glm::vec3(-10.3568, 0, -29.50987),
        glm::vec3(-10.91445, 0, -29.12262),
        glm::vec3(-11.41788, 0, -28.64242),
        glm::vec3(-11.80513, 0, -28.16998),
        glm::vec3(-12.21562, 0, -27.61233),
        glm::vec3(-12.61061, 0, -26.92302),
        glm::vec3(-12.88944, 0, -26.12528),
        glm::vec3(-13.09081, 0, -25.31979),
        glm::vec3(-13.25345, 0, -24.32068),
        glm::vec3(-13.38512, 0, -23.25186),
        glm::vec3(-13.54596, 0, -21.31535),
        glm::vec3(-13.6884, 0, -19.17882),
        glm::vec3(-13.72324, 0, -17.26686),
        glm::vec3(-13.79938, 0, -15.55362),
        glm::vec3(-13.81842, 0, -13.74521),
        glm::vec3(-13.83746, 0, -12.05101),
        glm::vec3(-14.01851, 0, -10.12896),
        glm::vec3(-14.09728, 0, -8.55348),
        glm::vec3(-14.1416, 0, -7.04592),
        glm::vec3(-14.04101, 0, -5.74013),
        glm::vec3(-13.74019, 0, -4.33965),
        glm::vec3(-13.23077, 0, -3.09558),
        glm::vec3(-12.28994, 0, -2.24197),
        glm::vec3(-10.7102, 0, -1.65928),
        glm::vec3(-8.72906, 0, -1.34851),
        glm::vec3(-6.73496, 0, -1.20608),
        glm::vec3(-5.01279, 0, -1.15428), //Z1
        glm::vec3(-3.82404, 0, -1.14454),
        glm::vec3(-2.59139, 0, -0.93415),
        glm::vec3(-1.7214, 0, -0.50177),
        glm::vec3(-1, 0, 0),
        glm::vec3(-0.31601, 0, 0.65304),
        glm::vec3(0.05951, 0, 1.34952),
        glm::vec3(0.23336, 0, 2.0192),
        glm::vec3(0.34064, 0, 2.69861),
        glm::vec3(0.30488, 0, 3.29756),
        glm::vec3(0.17973, 0, 4.01273),
        glm::vec3(0.00195, 0, 4.61577),
        glm::vec3(-0.26154, 0, 5.38125), //F5
        glm::vec3(-0.62694, 0, 6.10972),
        glm::vec3(-1.20821, 0, 6.58643),
        glm::vec3(-1.80855, 0, 6.98748),
        glm::vec3(-2.60146, 0, 7.19915),
        glm::vec3(-3.64023, 0, 7.32709),
        glm::vec3(-4.961, 0, 7.46953),
        glm::vec3(-6.52778, 0, 7.49543),
        glm::vec3(-8.32765, 0, 7.40479),
        glm::vec3(-10.03687, 0, 7.39184),
        glm::vec3(-11.56482, 0, 7.19013),
        glm::vec3(-12.75653, 0, 7.34935)
    };

    //generate road
    CreatePista();

    //generate grass
    CreateGrass();

    //generate paths for dynamic obstacles
    MakePathsObstacles();

    //debug marker
    CreateRectangle("debugpoint", 0.1, 0.1, 0.5, glm::vec3(1, 0, 0));

    //generate cars
    {
        CreateRectangle("playercar", 0.8, 2, 1, glm::vec3(0.69, 0.27, 0.92));
        CreateRectangle("obscar1", 0.8, 2, 1, glm::vec3(0.67, 0.25, 0.12));
        CreateRectangle("obscar2", 0.8, 2, 1, glm::vec3(0.27, 0.53, 0.27));
        CreateRectangle("obscar3", 0.8, 2, 1, glm::vec3(0.8, 0.68, 0.12));
        CreateRectangle("obscar4", 0.8, 2, 1, glm::vec3(0.74, 0.16, 0.26));
        CreateRectangle("obscar5", 0.8, 2, 1, glm::vec3(0.20, 0.13, 0.69));
        CreateRectangle("obscar6", 0.8, 2, 1, glm::vec3(0.92, 0.44, 0.89));

        PlayerCarMatrix = glm::mat4(1);
        PlayerCarMatrix = glm::scale(PlayerCarMatrix, glm::vec3(0.25, 0.25, 0.25));
        PlayerCarMatrix = glm::translate(PlayerCarMatrix, glm::vec3(0, 0.5, 0));
    }

    //variables initialization

    angle = 0;
    directioncar = glm::vec3(0, 0, 0);
    collisiondetected = false;
    timestopped = 0;
    outpathdetected = false;

    //Obs Car 1 variables
    directionobscar1 = obscar1points[0];
    directionobscar1aux= obscar1points[1] - obscar1points[0];
    indpointcar1 = 0;

    //Obs Car 2 variables
    directionobscar2 = obscar2points[0];
    directionobscar2aux = obscar2points[1] - obscar2points[0];
    indpointcar2 = 0;

    //Obs Car 3 variables
    directionobscar3 = obscar3points[0];
    directionobscar3aux = obscar3points[1] - obscar3points[0];
    indpointcar3 = 0;

    //Obs Car 4 variables
    directionobscar4 = obscar4points[0];
    directionobscar4aux = obscar4points[1] - obscar4points[0];
    indpointcar4 = 0;

    //Obs Car 5 variables
    directionobscar5 = obscar5points[0];
    directionobscar5aux = obscar5points[1] - obscar5points[0];
    indpointcar5 = 0;

    //Obs Car 6 variables
    directionobscar6 = obscar6points[0];
    directionobscar6aux = obscar6points[1] - obscar6points[0];
    indpointcar6 = 0;

    //shader
    {
        Shader* shader = new Shader("LabShader");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }

    //projection matrix used for main viewport
    projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);

    // Sets the resolution of the small viewport
    glm::ivec2 resolution = window->GetResolution();
    miniViewportArea = ViewportArea(50, 50, resolution.x / 5.f, resolution.y / 5.f);

}

//function that creates a rectangle but 3d :0
void Tema2::CreateRectangle(const char* name, float latime, float lungime, float h, glm::vec3 color)
{
    //the center is in the middle of the rectangle for easier rotations
    vector<VertexFormat> vertices =
    {
        //position normal texture_coordinates color
        VertexFormat(glm::vec3(-lungime/2, -h/2,  latime/2), color, glm::vec3(0.2, 0.8, 0.2)), //0
        VertexFormat(glm::vec3(lungime / 2, -h / 2,  latime / 2), color, glm::vec3(0.9, 0.4, 0.2)), //1
        VertexFormat(glm::vec3(-lungime / 2,  h / 2,  latime / 2), color, glm::vec3(0.7, 0.7, 0.1)), //2
        VertexFormat(glm::vec3(lungime / 2,  h / 2,  latime / 2), color, glm::vec3(0.7, 0.3, 0.7)), //3
        VertexFormat(glm::vec3(-lungime / 2, -h / 2, -latime / 2), color, glm::vec3(0.3, 0.5, 0.4)), //4
        VertexFormat(glm::vec3(lungime / 2, -h / 2, -latime / 2), color, glm::vec3(0.5, 0.2, 0.9)), //5
        VertexFormat(glm::vec3(-lungime / 2,  h / 2, -latime / 2), color, glm::vec3(0.7, 0.0, 0.7)), //6
        VertexFormat(glm::vec3(lungime / 2,  h / 2, -latime / 2), color, glm::vec3(0.1, 0.5, 0.8)) //7
    };

    vector<unsigned int> indices =
    {
        0, 1, 2,        1, 3, 2,
        2, 3, 7,        2, 7, 6,
        1, 7, 3,        1, 5, 7,
        6, 7, 4,        7, 5, 4,
        0, 4, 1,        1, 4, 5,
        2, 6, 4,        0, 2, 4,
    };

    CreateMesh(name, vertices, indices);
}

//function that creates the big green square aka grass
void Tema2::CreateGrass()
{
    vector<VertexFormat> vertices;
    vector<unsigned int> indices;

    // the length of the square and how many small squares we want to use for the mesh triangles
    float l = 80;
    float r = 60;
    float delta = l / r;

    for (float j = -l / 2; j <= l / 2; j = j + delta)
    {
        for (float i = -l / 2; i <= l / 2; i = i + delta)
        {
            vertices.push_back(VertexFormat(glm::vec3(i, -0.04f, j), glm::vec3(0.25, 0.45, 0.08), glm::vec3(0.4, 0.63, 0.32))); //-0.03
        }
    }

    for (int i = 0; i < (r + 1) * r - 1; i++)
    {
        indices.push_back(i);
        indices.push_back(i + r + 1);
        indices.push_back(i + r + 2);

        indices.push_back(i);
        indices.push_back(i + r + 2);
        indices.push_back(i + 1);
    }

    CreateMesh("grass", vertices, indices);
}

//function that creates the road mesh
void Tema2::CreatePista()
{
    vector<unsigned int> indices;

    glm::vec3 D;
    glm::vec3 P;
    glm::vec3 Up = glm::vec3(0, 1, 0);
    float distR = 1;
    float distA = 1.5;
    float lengthvec, delta;
    glm::vec3 aux;

    for (int i = 0; i < initialpoints.size()-1; i++)
    {
        D = initialpoints[i + 1] - initialpoints[i];
        P = glm::normalize(glm::cross(D, Up));

        vertices.push_back(VertexFormat(initialpoints[i] + distR * P, glm::vec3(0.21, 0.21, 0.23), Up));
        vertices.push_back(VertexFormat(initialpoints[i] - distA * P, glm::vec3(0.21, 0.21, 0.23), Up));

        //doing more triangles per segment (100 triangles)
        lengthvec = glm::length(D);
        delta = lengthvec / 20.0f;

        aux = initialpoints[i] + glm::normalize(D) * delta;

        for (int j = 1; j < 20; j++)
        {
            vertices.push_back(VertexFormat(aux + distR * P, glm::vec3(0.21, 0.21, 0.23), Up));
            vertices.push_back(VertexFormat(aux - distA * P, glm::vec3(0.21, 0.21, 0.23), Up));

            aux += glm::normalize(D) * delta;
        }
    }

    //last segment between the last point and first point
    D = initialpoints[0] - initialpoints[initialpoints.size() - 1];
    P = glm::normalize(glm::cross(D, Up));

    vertices.push_back(VertexFormat(initialpoints[initialpoints.size() - 1] + distR * P, glm::vec3(0.21, 0.21, 0.23), Up));
    vertices.push_back(VertexFormat(initialpoints[initialpoints.size() - 1] - distA * P, glm::vec3(0.21, 0.21, 0.23), Up));

    lengthvec = glm::length(D);
    delta = lengthvec / 20.0f;

    aux = initialpoints[initialpoints.size() - 1] + glm::normalize(D) * delta;

    for (int i = 1; i < 20; i++)
    {
        vertices.push_back(VertexFormat(aux + distR * P, glm::vec3(0.21, 0.21, 0.23), Up));
        vertices.push_back(VertexFormat(aux - distA * P, glm::vec3(0.21, 0.21, 0.23), Up));

        aux += glm::normalize(D) * delta;
    } 

    //making the triangles
    for (int i = 0; i < vertices.size() - 2; i = i + 2)
    {
        indices.push_back(i);
        indices.push_back(i+1);
        indices.push_back(i+3);

        indices.push_back(i);
        indices.push_back(i + 3);
        indices.push_back(i + 2);
    }

    indices.push_back(vertices.size() - 2);
    indices.push_back(vertices.size() - 1);
    indices.push_back(1);

    indices.push_back(vertices.size() - 2);
    indices.push_back(1);
    indices.push_back(0);

    CreateMesh("pista", vertices, indices);
}

//function that creates a mesh
Mesh* Tema2::CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned int>& indices)
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

void Tema2::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0.5, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //main viewport
    glm::ivec2 resolution = window->GetResolution();
    glViewport(0, 0, resolution.x, resolution.y);
}

//function that makes the path points for the obstacles cars
void Tema2::MakePathsObstacles()
{
    glm::vec3 D;
    glm::vec3 P;
    glm::vec3 Up = glm::vec3(0, 1, 0);
    float distObsCar1 = 0.5;
    float distObsCar2 = 1;
    float distObsCar3 = 0.7;
    float distObsCar4 = 1;

    //Car1 Path
    for (int i = 0; i < initialpoints.size() - 1; i++)
    {
        D = initialpoints[i + 1] - initialpoints[i];
        P = glm::normalize(glm::cross(D, Up));
        obscar1points.push_back(initialpoints[i] + distObsCar1 * P);
    }

    D = initialpoints[0] - initialpoints[initialpoints.size() - 1];
    P = glm::normalize(glm::cross(D, Up));
    obscar1points.push_back(initialpoints[initialpoints.size() - 1] + distObsCar1 * P);

    //Car2 Path
    for (int i = initialpoints.size() - 1; i >= 1; i--)
    {
        D = initialpoints[i-1] - initialpoints[i];
        P = glm::normalize(glm::cross(D, Up));
        obscar2points.push_back(initialpoints[i] + distObsCar2 * P);
    }

    D = initialpoints[initialpoints.size() - 1] - initialpoints[0];
    P = glm::normalize(glm::cross(D, Up));
    obscar2points.push_back(initialpoints[0] + distObsCar2 * P);

    //Car3 Path
    for (int i = 100; i < initialpoints.size() - 1; i++)
    {
        D = initialpoints[i + 1] - initialpoints[i];
        P = glm::normalize(glm::cross(D, Up));
        obscar3points.push_back(initialpoints[i] - distObsCar3 * P);
    }

    D = initialpoints[0] - initialpoints[initialpoints.size() - 1];
    P = glm::normalize(glm::cross(D, Up));
    obscar3points.push_back(initialpoints[initialpoints.size() - 1] - distObsCar3 * P);

    for (int i = 0; i < 100; i++)
    {
        D = initialpoints[i + 1] - initialpoints[i];
        P = glm::normalize(glm::cross(D, Up));
        obscar3points.push_back(initialpoints[i] - distObsCar3 * P);
    }

    //Car4 Path
    for (int i = 100; i >= 1; i--)
    {
        D = initialpoints[i - 1] - initialpoints[i];
        P = glm::normalize(glm::cross(D, Up));
        obscar4points.push_back(initialpoints[i] + distObsCar4 * P);
    }

    D = initialpoints[initialpoints.size() - 1] - initialpoints[0];
    P = glm::normalize(glm::cross(D, Up));
    obscar4points.push_back(initialpoints[0] + distObsCar4 * P);
    
    for (int i = initialpoints.size() - 1; i > 100; i--)
    {
        D = initialpoints[i - 1] - initialpoints[i];
        P = glm::normalize(glm::cross(D, Up));
        obscar4points.push_back(initialpoints[i] + distObsCar4 * P);
    }

    //Car5 Path
    for (int i = 50; i >= 1; i--)
    {
        D = initialpoints[i - 1] - initialpoints[i];
        P = glm::normalize(glm::cross(D, Up));
        obscar5points.push_back(initialpoints[i] + distObsCar4 * P);
    }

    D = initialpoints[initialpoints.size() - 1] - initialpoints[0];
    P = glm::normalize(glm::cross(D, Up));
    obscar5points.push_back(initialpoints[0] + distObsCar4 * P);

    for (int i = initialpoints.size() - 1; i > 50; i--)
    {
        D = initialpoints[i - 1] - initialpoints[i];
        P = glm::normalize(glm::cross(D, Up));
        obscar5points.push_back(initialpoints[i] + distObsCar4 * P);
    }

    //Car6 Path
    for (int i = 20; i >= 1; i--)
    {
        D = initialpoints[i - 1] - initialpoints[i];
        P = glm::normalize(glm::cross(D, Up));
        obscar6points.push_back(initialpoints[i] + distObsCar4 * P);
    }

    D = initialpoints[initialpoints.size() - 1] - initialpoints[0];
    P = glm::normalize(glm::cross(D, Up));
    obscar6points.push_back(initialpoints[0] + distObsCar4 * P);

    for (int i = initialpoints.size() - 1; i > 20; i--)
    {
        D = initialpoints[i - 1] - initialpoints[i];
        P = glm::normalize(glm::cross(D, Up));
        obscar6points.push_back(initialpoints[i] + distObsCar4 * P);
    }
}

//function that renders an obstacle car
void Tema2::DrawCar(float deltaTimeSeconds, const char* name, std::vector<glm::vec3> obscarpoints, glm::vec3* positioncar, glm::vec3* directionway, int* indpoint)
{
    float speed;
    speed = 5 * deltaTimeSeconds;

    if (*indpoint == obscarpoints.size() - 1)
    {
        if (obscarpoints[0].z >= obscarpoints[*indpoint].z)
        {
            if ((*positioncar).z >= obscarpoints[0].z)
            {
                *indpoint = 0;
                *directionway = obscarpoints[*indpoint + 1] - obscarpoints[*indpoint];
                *positioncar = obscarpoints[*indpoint];
            }
        }
        else
        {
            if ((*positioncar).z <= obscarpoints[0].z)
            {
                *indpoint = 0;
                *directionway = obscarpoints[*indpoint + 1] - obscarpoints[*indpoint];
                *positioncar = obscarpoints[*indpoint];

            }
        }
    }
    else
    {
        if (obscarpoints[*indpoint + 1].z >= obscarpoints[*indpoint].z)
        {
            if ((*positioncar).z >= obscarpoints[*indpoint + 1].z)
            {
                (*indpoint)++;

                if (*indpoint == obscarpoints.size() - 1)
                {
                    *directionway = obscarpoints[0] - obscarpoints[*indpoint];
                    *positioncar = obscarpoints[*indpoint];
                }
                else
                {
                    *directionway = obscarpoints[*indpoint + 1] - obscarpoints[*indpoint];
                    *positioncar = obscarpoints[*indpoint];
                }

            }
        }
        else
        {
            if ((*positioncar).z <= obscarpoints[*indpoint + 1].z)
            {

                (*indpoint)++;

                if (*indpoint == obscarpoints.size() - 1)
                {
                    *directionway = obscarpoints[0] - obscarpoints[*indpoint];
                    *positioncar = obscarpoints[*indpoint];
                }
                else
                {
                    *directionway = obscarpoints[*indpoint + 1] - obscarpoints[*indpoint];
                    *positioncar = obscarpoints[*indpoint];
                }

            }
        }
    }

    *positioncar += glm::normalize(*directionway) * speed;

    glm::mat4 ObstacleCar1 = glm::mat4(1);
    ObstacleCar1 = glm::translate(ObstacleCar1, *positioncar);
    ObstacleCar1 = glm::rotate(ObstacleCar1, -1 * glm::atan((*directionway).z / (*directionway).x), glm::vec3(0, 1, 0));
    ObstacleCar1 *= PlayerCarMatrix;
    RenderSimpleMesh_hw(meshes[name], shaders["LabShader"], ObstacleCar1);
}

//function that renders the obstacle cars
void Tema2::DrawObstacles(float deltaTimeSeconds)
{
    DrawCar(deltaTimeSeconds, "obscar1", obscar1points, &directionobscar1, &directionobscar1aux, &indpointcar1);
    DrawCar(deltaTimeSeconds, "obscar2", obscar2points, &directionobscar2, &directionobscar2aux, &indpointcar2);
    DrawCar(deltaTimeSeconds, "obscar3", obscar3points, &directionobscar3, &directionobscar3aux, &indpointcar3);
    DrawCar(deltaTimeSeconds, "obscar4", obscar4points, &directionobscar4, &directionobscar4aux, &indpointcar4);
    DrawCar(deltaTimeSeconds, "obscar5", obscar5points, &directionobscar5, &directionobscar5aux, &indpointcar5);
    DrawCar(deltaTimeSeconds, "obscar6", obscar6points, &directionobscar6, &directionobscar6aux, &indpointcar6);
}

//function that renders the trees around the road
void Tema2::DrawTrees()
{
    glm::vec3 D;
    glm::vec3 P;
    glm::vec3 Up = glm::vec3(0, 1, 0);

    glm::mat4 TreeMat;
    glm::mat4 TrunkMatrixaux;
    glm::mat4 BigLeafMatrixaux;
    glm::mat4 SmallLeafMatrixaux;

    for (int i = 0; i < initialpoints.size() - 1; i = i+3)
    {
        D = initialpoints[i + 1] - initialpoints[i];
        P = glm::normalize(glm::cross(D, Up));

        TreeMat = glm::mat4(1);
        TreeMat = glm::translate(TreeMat, (glm::vec3)initialpoints[i] + 2.0f * P);
        TrunkMatrixaux = TreeMat * TrunkMatrix;
        RenderSimpleMesh_hw(meshes["trunktree"], shaders["LabShader"], TrunkMatrixaux);
        BigLeafMatrixaux = TreeMat * BigLeafMatrix;
        RenderSimpleMesh_hw(meshes["bigleaftree"], shaders["LabShader"], BigLeafMatrixaux);
        SmallLeafMatrixaux = TreeMat * SmallLeafMatrix;
        RenderSimpleMesh_hw(meshes["smallleaftree"], shaders["LabShader"], SmallLeafMatrixaux);
    }

    for (int i = 0; i < initialpoints.size() - 1; i = i + 5)
    {
        D = initialpoints[i + 1] - initialpoints[i];
        P = glm::normalize(glm::cross(D, Up));

        TreeMat = glm::mat4(1);
        TreeMat = glm::translate(TreeMat, (glm::vec3)initialpoints[i] + -3.0f * P);
        TrunkMatrixaux = TreeMat * TrunkMatrix;
        RenderSimpleMesh_hw(meshes["trunktree"], shaders["LabShader"], TrunkMatrixaux);
        BigLeafMatrixaux = TreeMat * BigLeafMatrix;
        RenderSimpleMesh_hw(meshes["bigleaftree"], shaders["LabShader"], BigLeafMatrixaux);
        SmallLeafMatrixaux = TreeMat * SmallLeafMatrix;
        RenderSimpleMesh_hw(meshes["smallleaftree"], shaders["LabShader"], SmallLeafMatrixaux);
    }

    for (int i = 9; i < initialpoints.size() - 1; i = i + 5)
    {
        D = initialpoints[i + 1] - initialpoints[i];
        P = glm::normalize(glm::cross(D, Up));

        TreeMat = glm::mat4(1);
        TreeMat = glm::translate(TreeMat, (glm::vec3)initialpoints[i] + -5.0f * P);
        TrunkMatrixaux = TreeMat * TrunkMatrix;
        RenderSimpleMesh_hw(meshes["trunktree"], shaders["LabShader"], TrunkMatrixaux);
        BigLeafMatrixaux = TreeMat * BigLeafMatrix;
        RenderSimpleMesh_hw(meshes["bigleaftree"], shaders["LabShader"], BigLeafMatrixaux);
        SmallLeafMatrixaux = TreeMat * SmallLeafMatrix;
        RenderSimpleMesh_hw(meshes["smallleaftree"], shaders["LabShader"], SmallLeafMatrixaux);
    }
}

//debug function that draws some markers on the road
void Tema2::DrawPathDebug()
{
    glm::mat4 DebugMat;
    for (int i = 0; i < vertices.size(); i++)
    {
        DebugMat = glm::mat4(1);
        DebugMat = glm::translate(DebugMat, vertices[i].position);
        RenderSimpleMesh_hw(meshes["debugpoint"], shaders["LabShader"], DebugMat);
    }
}

//main function that draws road, grass, trees, obstacles and player car
void Tema2::DrawScene(float deltaTimeSeconds)
{
    DrawTrees();
    DrawObstacles(deltaTimeSeconds);

    RenderSimpleMesh_hw(meshes["pista"], shaders["LabShader"], glm::mat4(1));
    RenderSimpleMesh_hw(meshes["grass"], shaders["LabShader"], glm::mat4(1));

    glm::mat4 PlayerCarMatrixaux = glm::mat4(1);
    PlayerCarMatrixaux = glm::translate(PlayerCarMatrixaux, directioncar);
    PlayerCarMatrixaux = glm::rotate(PlayerCarMatrixaux, angle, glm::vec3(0, 1, 0));
    PlayerCarMatrixaux *= PlayerCarMatrix * glm::rotate(glm::mat4(1), RADIANS(-30), glm::vec3(0, 1, 0));
    RenderSimpleMesh_hw(meshes["playercar"], shaders["LabShader"], PlayerCarMatrixaux);
}

//function that checks the collision between player and an obstacle car
void Tema2::CheckCollisionCars()
{
    float distance;

    distance = sqrt((directioncar.x - directionobscar1.x) * (directioncar.x - directionobscar1.x) + (directioncar.z - directionobscar1.z) * (directioncar.z - directionobscar1.z));

    if (distance < 0.25)
    {
        collisiondetected = true;
        return;
    }

    distance = sqrt((directioncar.x - directionobscar2.x) * (directioncar.x - directionobscar2.x) + (directioncar.z - directionobscar2.z) * (directioncar.z - directionobscar2.z));

    if (distance < 0.25)
    {
        collisiondetected = true;
        return;
    }

    distance = sqrt((directioncar.x - directionobscar3.x) * (directioncar.x - directionobscar3.x) + (directioncar.z - directionobscar3.z) * (directioncar.z - directionobscar3.z));

    if (distance < 0.25)
    {
        collisiondetected = true;
        return;
    }

    distance = sqrt((directioncar.x - directionobscar4.x) * (directioncar.x - directionobscar4.x) + (directioncar.z - directionobscar4.z) * (directioncar.z - directionobscar4.z));

    if (distance < 0.25)
    {
        collisiondetected = true;
        return;
    }

    distance = sqrt((directioncar.x - directionobscar5.x) * (directioncar.x - directionobscar5.x) + (directioncar.z - directionobscar5.z) * (directioncar.z - directionobscar5.z));

    if (distance < 0.25)
    {
        collisiondetected = true;
        return;
    }

    distance = sqrt((directioncar.x - directionobscar6.x) * (directioncar.x - directionobscar6.x) + (directioncar.z - directionobscar6.z) * (directioncar.z - directionobscar6.z));

    if (distance < 0.25)
    {
        collisiondetected = true;
        return;
    }
}

//function that returns the area of the triangle abc
float Tema2::TriangleArea(glm::vec3 a, glm::vec3 b, glm::vec3 c)
{
    glm::vec3 v1, v2, sum;
    float trianglearea;

    v1 = b - a;
    v2 = c - a;

    sum = glm::cross(v1, v2);
    trianglearea = glm::length(sum) / 2;

    return trianglearea;
}

//function that checks if the player car is on the road
void Tema2::CheckCarinPath(glm::vec3 directioncar)
{
    float trianglearea;
    float area_sum;
    int found, i;

    found = 0;

    for (i = 0; i < vertices.size() - 2; i = i + 2)
    {
        area_sum = 0;

        trianglearea = TriangleArea(vertices[i].position, vertices[i + 1].position, vertices[i + 3].position);

        area_sum += TriangleArea(vertices[i].position, vertices[i + 1].position, directioncar);
        area_sum += TriangleArea(vertices[i].position, vertices[i + 3].position, directioncar);
        area_sum += TriangleArea(vertices[i + 1].position, vertices[i + 3].position, directioncar);

        //if we found the triangle our car is on
        if (abs(area_sum - trianglearea) < 0.0001f)
        {
            found = 1;
            outpathdetected = false;
            break;
        }

        area_sum = 0;

        trianglearea = TriangleArea(vertices[i].position, vertices[i + 3].position, vertices[i + 2].position);

        area_sum += TriangleArea(vertices[i].position, vertices[i + 3].position, directioncar);
        area_sum += TriangleArea(vertices[i].position, vertices[i + 2].position, directioncar);
        area_sum += TriangleArea(vertices[i + 3].position, vertices[i + 2].position, directioncar);

        if (abs(area_sum - trianglearea) < 0.0001f)
        {
            found = 1;
            outpathdetected = false;
            break;
        }
    }

    //case for the last 2 triangles between the last 2 points of the road
    if (i == vertices.size() - 2)
    {
        area_sum = 0;

        trianglearea = TriangleArea(vertices[i].position, vertices[i + 1].position, vertices[1].position);

        area_sum += TriangleArea(vertices[i].position, vertices[i + 1].position, directioncar);
        area_sum += TriangleArea(vertices[i].position, vertices[1].position, directioncar);
        area_sum += TriangleArea(vertices[i + 1].position, vertices[1].position, directioncar);

        if (abs(area_sum - trianglearea) < 0.0001f)
        {
            found = 1;
            outpathdetected = false;
        }

        area_sum = 0;

        trianglearea = TriangleArea(vertices[i].position, vertices[1].position, vertices[0].position);

        area_sum += TriangleArea(vertices[i].position, vertices[1].position, directioncar);
        area_sum += TriangleArea(vertices[i].position, vertices[0].position, directioncar);
        area_sum += TriangleArea(vertices[1].position, vertices[0].position, directioncar);

        if (abs(area_sum - trianglearea) < 0.0001f)
        {
            found = 1;
            outpathdetected = false;
        }
    }

    //if we checked all triangles and we didnt find one
    if (found == 0)
    {
        outpathdetected = true;
    }
}

void Tema2::Update(float deltaTimeSeconds)
{
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    //save camera positions for the main viewport
    camera_position = camera->position;
    camera_forward = camera->forward;
    camera_right = camera->right;
    camera_up = camera->up;

    //projection matrix for the main viewport
    projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);

    //render scene
    DrawScene(deltaTimeSeconds);
    glClear(GL_DEPTH_BUFFER_BIT);

    //minimap rendering
    glViewport(miniViewportArea.x, miniViewportArea.y, miniViewportArea.width, miniViewportArea.height);

    //setting the camera above the car
    camera->Set(glm::vec3(directioncar.x, 10, directioncar.z), glm::vec3(directioncar.x, 0.25, directioncar.z), glm::vec3(-1, 0, 0));
    //changing the projection matrix
    projectionMatrix = glm::ortho( -8.885f, 8.885f, -5.0f, 5.0f, -50.0f, 50.0f);

    //render scene
    DrawScene(deltaTimeSeconds);
    glClear(GL_DEPTH_BUFFER_BIT);

    //setting the camera back to its original position
    camera->Set(camera_position, camera_forward + camera_position, glm::cross(camera_right, camera_forward));

    //checking for collisions
    CheckCollisionCars();

    //if a collision was detected, we're stopping the car for about a second
    if (collisiondetected)
    {
        timestopped += deltaTimeSeconds;

        if (timestopped >= 1)
        {
            collisiondetected = false;
            timestopped = 0;
        }
    }
}

void Tema2::FrameEnd()
{

}

//render function
void Tema2::RenderSimpleMesh_hw(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix)
{
    glm::mat4 viewMatrix;

    if (!mesh || !shader || !shader->GetProgramID())
        return;

    // Render an object using the specified shader and the specified position
    glUseProgram(shader->program);

    // TODO(student): Get shader location for uniform mat4 "Model"
    int locationmodel = glGetUniformLocation(shader->program, "Model");
    // TODO(student): Get shader location for uniform mat4 "View"
    int locationview = glGetUniformLocation(shader->program, "View");
    // TODO(student): Get shader location for uniform mat4 "Projection"
    int locationprojection = glGetUniformLocation(shader->program, "Projection");

    //for every drawing we need to know the position of the player
    int locationpositioncar = glGetUniformLocation(shader->program, "Position_car");

    // TODO(student): Set shader uniform "Model" to modelMatrix
    glUniformMatrix4fv(locationmodel, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    // TODO(student): Set shader uniform "View" to viewMatrix
    viewMatrix = camera->GetViewMatrix();
    glUniformMatrix4fv(locationview, 1, GL_FALSE, glm::value_ptr(viewMatrix));

    // TODO(student): Set shader uniform "Projection" to projectionMatrix
    glUniformMatrix4fv(locationprojection, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    glUniform3fv(locationpositioncar, 1, glm::value_ptr(directioncar));

    // Draw the object
    glBindVertexArray(mesh->GetBuffers()->m_VAO);
    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema2::OnInputUpdate(float deltaTime, int mods)
{
    float speed, speedrot;
    speed = 3 * deltaTime;
    speedrot = 2 * deltaTime;

    glm::vec3 directioncarnextpos;

    if (window->KeyHold(GLFW_KEY_W)) {

        //calculating the "future" move of the car in case its going to be off the road
        glm::vec3 aux = glm::normalize(glm::vec3(camera->forward.x, 0, camera->forward.z));
        directioncarnextpos = directioncar + aux * speed;
        CheckCarinPath(directioncarnextpos);

        //if the move is out of the road or a collision with an obstacle car was detected we're going to ignore the input
        if (collisiondetected || outpathdetected)
        {
            return;
        }

        directioncar += aux * speed;
        camera->MoveForward(speed);
    }

    if (window->KeyHold(GLFW_KEY_A)) {

        //ignore input in case of collision
        if (collisiondetected)
        {
            return;
        }

        angle += speedrot;
        camera->RotateThirdPerson_OY(speedrot);
    }

    if (window->KeyHold(GLFW_KEY_S)) {

        glm::vec3 aux = glm::normalize(glm::vec3(camera->forward.x, 0, camera->forward.z));
        directioncarnextpos = directioncar - aux * speed;
        CheckCarinPath(directioncarnextpos);

        if (collisiondetected || outpathdetected)
        {
            return;
        }

        directioncar -= aux * speed;
        camera->MoveForward(-speed);
    }

    if (window->KeyHold(GLFW_KEY_D)) {

        if (collisiondetected)
        {
            return;
        }

        angle -= speedrot;
        camera->RotateThirdPerson_OY(-speedrot);
    }

    //keeping this for future possible debugging
    /*
    // move the camera only if MOUSE_RIGHT button is pressed
    if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        float cameraSpeed = 2.0f;

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
    */
}


void Tema2::OnKeyPress(int key, int mods)
{

}


void Tema2::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event

    //keeping this for future possible debugging
    /*
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
    */
}


void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema2::OnWindowResize(int width, int height)
{
}
