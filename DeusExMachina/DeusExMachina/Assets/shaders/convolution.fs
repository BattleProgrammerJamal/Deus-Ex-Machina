#version 430

#define KERNEL_MAXIMUM 8

in vec3 v_position;
in vec3 v_normal;
in vec3 v_tangent;
in vec2 v_uv;

uniform sampler2D u_texture0;
uniform sampler2D u_texture1;
uniform float time;

out vec4 o_color;

struct ConvKernel
{
	mat3 data;
	int active;
};

uniform ConvKernel u_kernels[KERNEL_MAXIMUM];

vec4 convolution(sampler2D tex, vec2 uv, mat3 kernel, float offset)
{
	vec2 offsets[9] = vec2[](
		vec2(-offset, offset),
		vec2(0.0,    offset),
		vec2(offset,  offset),
		vec2(-offset, 0.0),
		vec2(0.0,    0.0),
		vec2(offset,  0.0),
		vec2(-offset, -offset),
		vec2(0.0,    -offset),
		vec2(offset,  -offset)  
	);
	
	vec3 sampleTex[9];
    for(int i = 0; i < 9; i++)
    {
		sampleTex[i] = vec3(texture(tex, uv + offsets[i]));
    }
    vec3 col = vec3(0.0);
    for(int i = 0; i < 9; i++)
	{
        col += sampleTex[i] * kernel[i];
	}
	
	return vec4(col, 1.0);
}

const float offset = 1.0 / 300.0;

void main(void)
{
	vec4 tex = vec4(0.0);
	for(int i = 0; i < u_kernels.length(); ++i)
	{
		if(u_kernels[i].active == 1)
		{
			tex = tex + convolution(u_texture0, vec2(v_uv.x, -v_uv.y), u_kernels[i].data, offset);
		}
	}
	tex.w = 1.0;
	o_color = tex;
}