varying vec3 a_position;
varying vec3 a_norm;
varying vec2 a_tex;

uniform vec3 ambientIntense;
//light1 directLight
uniform vec3 difuseIntense1;
uniform vec3 specularIntense1;
uniform float shiness1;
uniform vec3 directLightDir;
//light2 pointLight
uniform vec3 difuseIntense2;
uniform vec3 specularIntense2;
uniform float shiness2;
uniform vec3 lightPos;
uniform vec3 attr;

uniform vec3 eyePos;


void main(void)
{
	//sample texture
	vec3 eyeDirection = normalize(eyePos - a_position);
	vec3 lightColor = vec3(0.0);
	vec3 scatteredLightTotal = vec3(0.0);
	vec3 reflectedLightTotal = vec3(0.0);
	//cal DirectLight;
	{
		
		float diffuse1 = max(0.0, dot(a_norm, -directLightDir));
		float specular1 = 0.0;
		if (diffuse1 == 0.0)
        {
			specular1 = 0.0;
        }
		else
        {
            //vec3 halfDir1 = reflect(directLightDir , a_norm);
            vec3 halfDir1 = normalize(normalize(eyeDirection) - normalize(directLightDir));
            specular1 = max(0.0, dot(a_norm, halfDir1));
			specular1 = pow(specular1, shiness1);
        }

		vec3 scatteredLight1 = diffuse1 * difuseIntense1;
		vec3 reflectedLight1 = specular1 * specularIntense1;
		scatteredLightTotal += scatteredLight1;
		reflectedLightTotal += reflectedLight1;
	}

    

	//cal pointLight
	{
		vec3 lightDirection2 = lightPos - a_position;
		float lightDistance2 = length(lightDirection2);
		lightDirection2 = lightDirection2 / lightDistance2;
        
        
		float attenuation2 = 1.0 / ( attr.x  +attr.y * lightDistance2 + attr.z * lightDistance2 * lightDistance2);
		vec3 halfVector2 = normalize(lightDirection2 + eyeDirection);
		float diffuse2 = max(0.0, dot(a_norm, lightDirection2));
		float specular2 = max(0.0, dot(a_norm, halfVector2));
		if (diffuse2 == 0.0)
			specular2 = 0.0;
		else
			specular2 = pow(specular2, shiness2);
        
        
		vec3 scatteredLight2 = difuseIntense2 * diffuse2 * attenuation2;
		vec3 reflectedLight2 = specularIntense2 * specular2 * attenuation2;
		scatteredLightTotal += scatteredLight2;
		reflectedLightTotal += reflectedLight2;
	}
     
     

	scatteredLightTotal += ambientIntense;
	vec4 color = texture2D(CC_Texture0,a_tex);
	vec3 rgb = color.rgb * scatteredLightTotal + reflectedLightTotal;
	gl_FragColor = vec4(min(rgb,vec3(1.0)),color.a);
    //gl_FragColor = color;
}
