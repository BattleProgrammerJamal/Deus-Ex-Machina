#version 330

struct Material
{
	vec3 color;
};

uniform Material u_material;
uniform float time;

in vec3 v_position;
in vec3 v_normal;
in vec3 v_tangent;
in vec2 v_uv;

out vec4 o_color;

void main(void)
{
    o_color = vec4(u_material.color, 1.0);
}