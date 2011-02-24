//
//  Earth.vert
//  Earth
//
//  Created by Arman Uguray on 2/21/11.
//  Copyright 2011 Brown University. All rights reserved.
//

attribute vec4 position;
attribute vec2 TextureCoord;

uniform sampler2D BumpMap;

uniform mat4 mv;
uniform mat4 proj;
uniform float rot;

varying float Diffuse;
varying vec3  Specular;
varying vec2 TexCoord;

uniform vec3 LightPosition;

void main()
{					
	float c = cos(-rot);
	float s = sin(-rot);
	mat4 ctm = mat4(c,0,s,0,
					0,1,0,0,
				   -s,0,c,0,
				    0,0,0,1);
	vec4 normal = vec4(position.xyz, 0.0);				
	vec4 pos = (mv * (ctm * position));
	vec3 ecPosition = pos.xyz;
    vec3 tnorm      = (mv * ctm * normal).xyz;
	vec3 light = (mv * vec4(LightPosition, 1.0)).xyz;
    vec3 lightVec   = normalize(light - ecPosition);
    vec3 reflectVec = reflect(-lightVec, tnorm);
    vec3 viewVec    = normalize(-ecPosition);

    float spec      = clamp(dot(reflectVec, viewVec), 0.0, 1.0);
    spec            = pow(spec, 3.0);
    Specular        = vec3 (spec) * vec3 (1.0, 0.941, 0.898) * 0.3;

    Diffuse         = max(dot(lightVec, tnorm), 0.0);
	
	TexCoord = TextureCoord;
	gl_Position = proj * pos;
}
