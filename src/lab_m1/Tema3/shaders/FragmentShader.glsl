#version 330

// Input
// values from vertex shader
in vec3 frag_color;
in vec3 frag_position;
in vec3 frag_normal;
in vec2 frag_coordinate;

uniform vec3 object_color;
uniform sampler2D texture_1;
uniform sampler2D texture_2;

uniform int textureapplied;

// Output
layout(location = 0) out vec4 out_color;


void main()
{
    if(textureapplied == 1)
    {
        vec4 color = texture2D(texture_1, frag_coordinate);
        out_color=color;

        if(out_color.a < 0.5f)
        {
            discard;
        }
    }
    else
    {
        if(frag_color.x == 0 && frag_color.y == 0 && frag_color.z == 0)
        {
            out_color = vec4(object_color, 1);
        }
        else
        {
            out_color = vec4(frag_color, 1);
        }
    }
}
