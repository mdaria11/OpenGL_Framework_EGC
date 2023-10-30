#version 330

// Input
// vertex attributes from creating the mesh
layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_coordinate;
layout(location = 3) in vec3 v_color;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

uniform vec2 deplasamenttext;
uniform int deplasamenttrue;

// Output
// output values for fragment shader
out vec3 frag_color;
out vec3 frag_position;
out vec3 frag_normal;
out vec2 frag_coordinate;

void main()
{
    frag_color = v_color;
    frag_position = v_position;
    frag_normal = v_normal;

    if(deplasamenttrue == 1)
    {
        frag_coordinate = v_coordinate + deplasamenttext;
    }
    else
    {
        frag_coordinate = v_coordinate;
    }

    gl_Position = Projection * View * Model * vec4(v_position, 1.0);

}
