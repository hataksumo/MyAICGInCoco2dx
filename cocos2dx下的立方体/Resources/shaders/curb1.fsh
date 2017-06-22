varying vec2 tex_coord;
void main(void)
{
   gl_FragColor =  vec4(1.0,1.0,1.0,1.0) * texture2D(CC_Texture0,tex_coord);
   //color = vec4(1.0,1.0,1.0,1.0);
}