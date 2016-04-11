#version 430

#define MAXIMUM_LIGHTS 128

struct Light
{
	vec4	color;
	vec3 	position;
	vec3 	direction;
	float	intensity;
	int		type;
};

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
uniform Light u_lights[MAXIMUM_LIGHTS];
uniform sampler2D u_texture0;
uniform float time;

out vec4 o_color;

void main(void)
{
	vec4 I = vec4(0.0);
	
	for(int i = 0; i < u_lights.length(); ++i)
	{
		vec3 L = vec3(0.0);
		if(u_lights[i].type == 0)
		{
			L = normalize(u_lights[i].position);
		}
		else
		{
			L = normalize(u_lights[i].direction);
		}
		
		vec3 N = normalize(v_normal);
		float NDotL = dot(N, L);
		vec3 ambient = u_material.ambient * 0.01 * u_lights[i].intensity;
		vec3 diffuse = u_material.diffuse * max(NDotL, 0.0) * 1.0 * u_lights[i].intensity;
		I = I + (u_lights[i].color * u_lights[i].intensity) + vec4(ambient + diffuse, 1.0);
	}
	
	vec4 tex = texture(u_texture0, 0.5 * v_uv);
	
    o_color = I;
}