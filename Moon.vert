//
//  Moon.vert
//  Earth
//
//  Created by Arman Uguray on 2/21/11.
//  Copyright 2011 Brown University. All rights reserved.
//

attribute vec4 position;
attribute vec2 TextureCoord;

uniform mat4 mv;
uniform mat4 proj;

uniform float rotate;
const float tranz = 60.0;
const float scale = 0.3;

varying float Diffuse;
varying vec3  Specular;
varying vec2 TexCoord;

uniform vec3 LightPosition;

void main()
{
	float c = cos(-rotate);
	float s = sin(-rotate);
	mat4 m1 = mat4(scale,  0  ,  0  ,  0  ,
					 0  ,scale,  0  ,  0  ,
					 0  ,  0  ,scale,  0  ,
					 0  ,  0  ,tranz,  1  );
	mat4 ctm = mat4( c,0,s,0,
					 0,1,0,0,
					-s,0,c,0,
					 0,0,0,1) * m1;
	TexCoord = TextureCoord;
	
	vec4 pos = mv * (ctm * position);
	vec3 normal = normalize(mv * ctm * vec4(position.xyz, 0.0)).xyz;
	vec3 ecPosition = pos.xyz;
	vec3 light = (mv * vec4(LightPosition, 1.0)).xyz;
    vec3 lightVec   = normalize(light - ecPosition);
    vec3 reflectVec = reflect(-lightVec, normal);
    vec3 viewVec    = normalize(-ecPosition);

    float spec      = clamp(dot(reflectVec, viewVec), 0.0, 1.0);
    spec            = pow(spec, 15.0);
    Specular        = vec3 (spec) * 0.7;

    Diffuse         = max(dot(lightVec, normal), 0.0);
	
	gl_Position = proj * pos;
}

