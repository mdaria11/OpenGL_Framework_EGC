#version 330

// Input
// TODO(student): Get vertex attributes from each location
layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_coordinate;
layout(location = 3) in vec3 v_color;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform vec3 Position_car;

// Output
// TODO(student): Output values to fragment shader
out vec3 frag_color;
out vec3 frag_position;
out vec3 frag_normal;
out vec2 frag_coordinate;

void main()
{
    vec4 new_v_position;
    float delta;
    float scalefactor;

    scalefactor = 0.02;

    //we have to apply the effect on the actual y coordonate of the vertex aka after aplying Model matrix
    new_v_position = Model * vec4(v_position, 1.0);

    delta= length(Position_car - new_v_position.xyz) * length(Position_car - new_v_position.xyz);

    new_v_position.y = new_v_position.y - delta * scalefactor;

    frag_position = new_v_position.xyz;
    frag_color = v_color;
    frag_normal = v_normal;
    frag_coordinate = v_coordinate;

    // TODO(student): Compute gl_Position
    gl_Position = Projection * View * new_v_position;

}
