attribute vec4 vPosition;
attribute vec4 vColor;
varying vec4 a_color;

uniform mat4 model_matrix;
uniform mat4 projection_matrix;

void
main()
{
	a_color = vColor;
	gl_Position = projection_matrix * (model_matrix * vPosition);
}