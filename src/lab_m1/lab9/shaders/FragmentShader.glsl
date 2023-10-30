#version 330

// Input
in vec2 texcoord;

// Uniform properties
uniform sampler2D texture_1;
uniform sampler2D texture_2;
// TODO(student): Declare various other uniforms
uniform int mix;

// Output
layout(location = 0) out vec4 out_color;


void main()
{
    // TODO(student): Calculate the out_color using the texture2D() function.
    vec4 color = texture2D(texture_1, texcoord);        
    vec4 color2 = texture2D(texture_2, texcoord); 

    if (mix == 0)
    {
        out_color = color;
    }
	else
    {
        vec4 colorfinal = mix(color, color2, 0.5f);
        out_color = colorfinal;
    }

    if(out_color.a < 0.5f)
    {
        discard;
    }

}
