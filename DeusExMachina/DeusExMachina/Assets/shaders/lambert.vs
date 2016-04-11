#version 430

layout(location=0) in vec3 a_position;
layout(location=1) in vec3 a_normal;
layout(location=2) in vec3 a_tangent;
layout(location=3) in vec2 a_uv;

out vec3 v_position;
out vec3 v_normal;
out vec3 v_tangent;
out vec2 v_uv;

uniform mat4 u_world;
uniform mat4 u_view;
uniform mat4 u_proj;

uniform float time;

void main(void)
{
	v_position = a_position;
	v_normal = a_normal;
	v_tangent = a_tangent;
	v_uv = a_uv;
	
	vec3 dpn = a_position + v_normal * cos(a_position.x * time - a_position.y * (time * time));
	
	vec4 pos = vec4(dpn, 1.0);
	gl_Position = u_proj * u_view * u_world * pos;
}