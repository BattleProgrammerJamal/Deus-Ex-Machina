#version 430

#define MAXIMUM_LIGHTS 128

struct Light
{
	vec4	color;
	vec3 	position;
	vec3 	direction;
	float	intensity;
	float	attenuation_constant;
	float	attenuation_linear;
	float	attenuation_quadric;
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

uniform mat4 u_world;
uniform mat4 u_view;

uniform vec3 u_eye;
uniform Material u_material;
uniform Light u_lights[MAXIMUM_LIGHTS];
uniform sampler2D u_texture0;
uniform sampler2D u_texture1;
uniform samplerCube u_skybox;

uniform float time;
uniform int u_wireframe;
uniform vec4 u_wireframeStyle;

out vec4 o_color;

void main(void)
{
	if(u_wireframe == 0)
	{
		vec4 I = vec4(0.0);
		
		vec3 p = vec3(u_world * vec4(v_position, 1.0));
		vec3 Incident = normalize(p - u_eye);
		vec3 Refl = reflect(Incident, normalize(v_normal));
		vec3 Refr = refract(Incident, normalize(v_normal), 1.33 / 1.52);
		
		vec4 skyboxReflections = texture(u_skybox, Refl);
		vec4 skyboxRefractions = texture(u_skybox, Refr);
		
		for(int i = 0; i < u_lights.length(); ++i)
		{
			float attenuation = 1.0;
			
			vec3 L = vec3(0.0);
			if(u_lights[i].type == 0)
			{
				L = normalize(u_lights[i].position);
				vec3 worldLight = vec3(u_world * vec4(L, 1.0));
				float d = length(v_position - worldLight);
				attenuation = u_lights[i].attenuation_constant + u_lights[i].attenuation_linear * d + u_lights[i].attenuation_quadric * d * d;
			}
			else
			{
				attenuation = 1.0;
				L = normalize(u_lights[i].direction);
			}
			
			vec3 N = normalize(v_normal);
			float NDotL = dot(N, L);
			vec3 R = normalize((2.0 * NDotL) * N - L);
			vec3 V = normalize(mat3(u_view) * v_position);
			float RDotV = dot(R, V);
			vec3 ambient = u_material.ambient * 0.01;
			vec3 diffuse = u_material.diffuse * max(NDotL, 0.0) * 1.0;
			float specularTerm = 0.0;
			if(NDotL <= 0.0)
			{
				specularTerm = pow(RDotV, 80.0);
			}
			vec3 specular = vec3(1.0, 1.0, 1.0) * specularTerm * 1.0;
			
			I = I + u_lights[i].color * u_lights[i].intensity * vec4(ambient + (diffuse + specular), 1.0);
		}
		
		vec4 tex = texture(u_texture0, vec2(v_uv.x, v_uv.y));
		vec4 tex2 = texture(u_texture1, v_uv);
		
		o_color = I;
	}
	else
	{
		o_color = u_wireframeStyle;
	}
}