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
uniform sampler2D u_texture1;

uniform mat4 u_view;

uniform float time;
uniform int u_wireframe;
uniform vec4 u_wireframeStyle;

out vec4 o_color;

void main(void)
{
	if(u_wireframe == 0)
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
			I = I + u_lights[i].color * vec4(ambient + diffuse, 1.0);
		}
		
		vec4 tex = texture(u_texture0, v_uv);
		vec4 tex2 = texture(u_texture1, v_uv);
		
		vec3 L = vec3(0.5 * cos(time), 1.0 + 2.0 * sin(0.5 * time), 1.0 + cos(0.25 * time));
		float NDotL = dot(normalize(v_normal), normalize(L));
		float RDotV = dot(normalize((2.0 * NDotL) * v_normal - normalize(L)), normalize(mat3(u_view) * v_position));
		vec3 ka = u_material.ambient * 0.2;
		vec3 kd = u_material.diffuse * max(NDotL, 0.0) * 1.0;
		vec3 ks = vec3(1.0, 1.0, 1.0) * pow(RDotV, 150.0) * 1.0;
		vec3 phong = ka + kd + ks;
		o_color = vec4(phong, 1.0);
	}
	else
	{
		o_color = u_wireframeStyle;
	}
}