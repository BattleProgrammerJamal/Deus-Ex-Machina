#version 430

layout(location=0) in vec3 a_position;

out vec3 v_position;

uniform mat4 u_view;
uniform mat4 u_proj;

uniform float time;

void main(void)
{
	v_position = a_position;
	vec4 pos = u_proj * mat4(mat3(u_view)) * vec4(a_position, 1.0);
	
	gl_Position = pos.xyzz;
}