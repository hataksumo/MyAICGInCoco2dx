attribute vec3 in_position;
attribute vec3 in_norm;
attribute vec2 in_tex;

varying vec3 a_position;
varying vec3 a_norm;
varying vec2 a_tex;

uniform mat4 modelMatrix;
uniform mat4 modelInverseMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectMatrix;



void main(void)
{
	a_position = (modelMatrix * vec4(in_position,1.0)).xyz;
	gl_Position = projectMatrix * (viewMatrix * vec4(a_position,1.0));
	a_norm = (normalize(modelInverseMatrix * vec4(in_norm,1.0))).xyz;
    //a_norm = vec3(0.0,0.0,0.0);
	a_tex = in_tex;
}