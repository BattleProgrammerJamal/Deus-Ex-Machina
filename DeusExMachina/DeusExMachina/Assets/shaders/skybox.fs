#version 430

in vec3 v_position;

out vec4 o_color;

uniform samplerCube u_texture15;
uniform sampler2D u_cloud;

uniform mat4 u_view;
uniform mat4 u_proj;

uniform float time;

void main(void)
{
	float dt = time / 1000.0;
	vec3 uv = vec3(v_position);
	vec4 cloud = texture(u_cloud, uv.xy);
	vec4 skybox = texture(u_texture15, uv);
	
	o_color = skybox;
}