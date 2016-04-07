#version 330

struct Material
{
	vec3 ambient;
	vec3 diffuse;
};

in vec3 v_position;
in vec3 v_normal;
in vec3 v_tangent;
in vec2 v_uv;

uniform Material u_material;
uniform float time;
uniform sampler2D u_texture0;

out vec4 o_color;

void main(void)
{
	vec3 L = normalize(vec3(0.0, 0.0, 1.0));
	
	vec3 N = normalize(v_normal);
	float NDotL = dot(N, L);
	vec3 ambient = u_material.ambient * 0.01;
	vec3 diffuse = u_material.diffuse * max(NDotL, 0.0) * 1.0;
	vec3 I = ambient + diffuse;
	
	vec4 tex = texture(u_texture0, 2.0 * v_uv);
	
    o_color = tex + vec4(I, 1.0);
}