varying vec4 light1_diffuse,ambientGlobal,light1_ambient;
varying vec3 normal,light1_lightDir,light1_halfVector;
varying float light1_dist;

varying vec4 light0_diffuse,light0_ambient;
varying vec3 light0_lightDir,light0_halfVector;
varying float light0_dist;

void main()
{
    vec3 n,halfV,viewV,ldir;
	float NdotL,NdotHV;
	vec4 color = ambientGlobal;
	float att;

	n = normalize(normal);

	NdotL = max(dot(n,normalize(light0_lightDir)),0.0);
	if (NdotL > 0.0) {

		att = 1.0 / (gl_LightSource[0].constantAttenuation +
				gl_LightSource[0].linearAttenuation * light0_dist +
				gl_LightSource[0].quadraticAttenuation * light0_dist * light0_dist);
		color += att * (light0_diffuse * NdotL + light0_ambient);
		halfV = normalize(light0_halfVector);

		NdotHV = max(dot(n,halfV),0.0);
		color += att * gl_FrontMaterial.specular * gl_LightSource[0].specular *
						pow(NdotHV,gl_FrontMaterial.shininess);
	}
    
    vec3 light1_halfV;
	float light1_NdotL, light1_NdotHV;
	float light1_att,spotEffect;
	
	light1_NdotL = max(dot(n,normalize(light1_lightDir)),0.0);

	if (light1_NdotL > 0.0) {
	
		spotEffect = dot(normalize(gl_LightSource[1].spotDirection), normalize(-light1_lightDir));
		if (spotEffect > gl_LightSource[1].spotCosCutoff) {
			spotEffect = pow(spotEffect, gl_LightSource[1].spotExponent);
			light1_att = spotEffect / (gl_LightSource[1].constantAttenuation +
					gl_LightSource[1].linearAttenuation * light1_dist +
					gl_LightSource[1].quadraticAttenuation * light1_dist * light1_dist);
				
			color += light1_att * (light1_diffuse * light1_NdotL + light1_ambient);
		
			
			light1_halfV = normalize(light1_halfVector);
			light1_NdotHV = max(dot(n,light1_halfV),0.0);
			color += light1_att * gl_FrontMaterial.specular * gl_LightSource[1].specular * pow(light1_NdotHV,gl_FrontMaterial.shininess);
		}
	}

    color[0] = min(color[0], 1.0);
    color[1] = min(color[1], 1.0);
    color[2] = min(color[2], 1.0);
    color[3] = min(color[3], 1.0);
	gl_FragColor = color;

}
