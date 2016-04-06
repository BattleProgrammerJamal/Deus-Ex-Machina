#version 330

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

uniform vec3 u_eye;
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
	vec3 R = (2.0 * NDotL) * N - L;
	vec3 V = normalize(u_eye * v_position);
	float RDotV = dot(R, V);
	vec3 ambient = u_material.ambient * 1.0;
	vec3 diffuse = u_material.diffuse * max(NDotL, 0.0) * 1.0;
	vec3 specular = u_material.specular * pow(RDotV, u_material.shininess) * 1.0;
	vec3 I = ambient + diffuse + specular;
	
    o_color = vec4(u_material.ambient, 1.0);
}