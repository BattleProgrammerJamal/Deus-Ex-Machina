#version 330

struct Material
{
	vec3 ambient;
	vec3 diffuse;
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
	vec3 L = normalize(vec3(0.0, 0.0, -1.0));
	
	vec3 N = normalize(v_normal);
	float NDotL = dot(N, L);
	vec3 ambient = u_material.ambient * 1.0;
	vec3 diffuse = u_material.diffuse * max(NDotL, 0.0) * 1.0;
	vec3 I = ambient + diffuse;
	
    o_color = vec4(I, 1.0);
}