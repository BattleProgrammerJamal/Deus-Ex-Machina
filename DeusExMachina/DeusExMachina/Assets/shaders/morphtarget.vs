#version 430

layout(location=0) in vec3 a_position;
layout(location=1) in vec3 a_normal;
layout(location=2) in vec3 a_tangent;
layout(location=3) in vec2 a_uv;
layout(location=4) in vec3 a_morphTarget0;
layout(location=5) in vec3 a_morphTarget1;
layout(location=5) in vec3 a_morphTarget2;

out vec3 v_position;
out vec3 v_normal;
out vec3 v_tangent;
out vec2 v_uv;

uniform float u_morphTargetWeight0;
uniform float u_morphTargetWeight1;
uniform float u_morphTargetWeight2;

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
	
	float sumWeight = 1.0 + u_morphTargetWeight0 + u_morphTargetWeight1 + u_morphTargetWeight2;
	float f0 = 1.0 / sumWeight;
	float f1 = u_morphTargetWeight0 / sumWeight;
	float f2 = u_morphTargetWeight1 / sumWeight;
	float f3 = u_morphTargetWeight2 / sumWeight;
	
	vec3 position = v_position * f0 + a_morphTarget0 * f1 + a_morphTarget1 * f2 + a_morphTarget2 * f3;
	
	vec4 pos = vec4(position, 1.0);
	gl_Position = u_proj * u_view * u_world * pos;
}