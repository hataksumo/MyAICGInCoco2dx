varying vec4 v_color;
uniform mat4 cmatrix;

void main()
{
	gl_FragColor = cmatrix * v_color;
}