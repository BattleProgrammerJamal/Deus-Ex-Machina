#version 330

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

in vec3 v_position;
in vec3 v_normal;
in vec3 v_tangent;
in vec2 v_uv;

uniform vec3 u_eye;
uniform Material u_material;
uniform float time;
uniform mat4 u_view;

out vec4 o_color;

void main(void)
{
	vec3 L = normalize(vec3(0.0, 0.0, 1.0));
	
	vec3 N = normalize(v_normal);
	float NDotL = dot(N, L);
	vec3 R = normalize((2.0 * NDotL) * N - L);
	vec3 V = normalize(vec3(u_view * vec4(v_position, 1.0)));
	float RDotV = dot(R, V);
	vec3 ambient = u_material.ambient * 0.1;
	vec3 diffuse = u_material.diffuse * max(NDotL, 0.0) * 1.0;
	float specularTerm = 0.0;
	if(NDotL >= 0.0)
	{
		specularTerm = pow(RDotV, u_material.shininess);
	}
	vec3 specular = u_material.specular * specularTerm * 1.0;
	vec3 I = ambient + diffuse + specular;
	
    o_color = tex * vec4(I, 1.0);
}