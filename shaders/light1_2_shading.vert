varying vec4 light1_diffuse,ambientGlobal,light1_ambient;
varying vec3 normal,light1_lightDir,light1_halfVector;
varying float light1_dist;

varying vec4 light0_diffuse,light0_ambient;
varying vec3 light0_lightDir,light0_halfVector;
varying float light0_dist;

void main()
{
	vec4 ecPos;
	vec3 aux;
    vec3 aux2;
	normal = normalize(gl_NormalMatrix * gl_Normal);

        /* these are the new lines of code to compute the light's direction */
	ecPos = gl_ModelViewMatrix * gl_Vertex;

    aux2 = vec3(gl_LightSource[0].position-ecPos);
    light0_lightDir = normalize(aux2);
    light0_dist = length(aux2);
    light0_halfVector = normalize(gl_LightSource[0].halfVector.xyz);

	aux = vec3(gl_LightSource[1].position-ecPos);
	light1_lightDir = normalize(aux);
	light1_dist = length(aux);
	light1_halfVector = normalize(gl_LightSource[1].halfVector.xyz);

        /* Compute the diffuse, ambient and globalAmbient terms */
    light0_diffuse = gl_FrontMaterial.diffuse * gl_LightSource[0].diffuse;
	light1_diffuse = gl_FrontMaterial.diffuse * gl_LightSource[1].diffuse;
	/* The ambient terms have been separated since one of them */

	/* suffers attenuation */
    light0_ambient = gl_FrontMaterial.ambient * gl_LightSource[0].ambient;
	light1_ambient = gl_FrontMaterial.ambient * gl_LightSource[1].ambient;

	ambientGlobal = gl_LightModel.ambient * gl_FrontMaterial.ambient;
	gl_Position = ftransform();
}

