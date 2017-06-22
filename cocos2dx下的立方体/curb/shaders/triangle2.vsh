attribute vec2 position;
attribute vec4 color;

varying vec4 v_color;
uniform mat4 vmatrix;

void main()
{
	gl_Position = vmatrix * vec4(position,0.0,1.0);
	v_color = color;
}