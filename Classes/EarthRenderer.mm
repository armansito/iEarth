//
//  EarthRenderer.m
//  Earth
//
//  Created by Arman Uguray on 2/21/11.
//  Copyright 2011 Brown University. All rights reserved.
//

#import "EarthRenderer.h"
#import <QuartzCore/QuartzCore.h>
#include "OrbitingCamera.h"
#import "GLESFileLoader.h"

#define RES 50
#define SUN_DISTANCE 20000.f
#define MOON_DISTANCE 60.f

@interface EarthRenderer(PrivateMethods)

- (void)renderEarth;
- (void)renderMoon;
- (void)renderSun;

@end

@implementation EarthRenderer

@dynamic camera;

- (OrbitingCamera *)camera
{
	return m_camera;
}

- (id)init
{
	if ((self = [super init])) {
		vertices = (GLfloat *)malloc(RES*RES*6*3*sizeof(GLfloat));
		tex_coords = (GLfloat *)malloc(RES*RES*6*2*sizeof(GLfloat));
		tangents = (GLfloat *)malloc(RES*RES*6*3*sizeof(GLfloat));
		GLfloat lat,lon;
		GLfloat lat_incr = M_PI/RES;
		GLfloat lon_incr = 2*lat_incr;
		REAL u, v, tanlon;
		lon = 0;
		int index = -1;
		int tindex = -1;
		int tanindex = -1;
		for (int i = 0; i < RES; i++) {
			lat = 0;
			for (int j = 0; j < RES; j++) {
				// V1
				vertices[++index] = sin(lat)*cos(lon);
				vertices[++index] = cos(lat);
				vertices[++index] = sin(lat)*sin(lon);
				
				u = lon*0.5*M_1_PI;
				v = asin(vertices[index-1])*M_1_PI + 0.5;
				if (v == 0 || v == 1) u = 0.5;
				
				tex_coords[++tindex] = 1.f-u;
				tex_coords[++tindex] = 1.f-v;
				
				tanlon = lon + M_PI_2;
				
				tangents[++tanindex] = cos(tanlon);
				tangents[++tanindex] = 0.0;
				tangents[++tanindex] = sin(tanlon);
				
				// V2			
				vertices[++index] = sin(lat+lat_incr)*cos(lon+lon_incr);
				vertices[++index] = cos(lat+lat_incr);
				vertices[++index] = sin(lat+lat_incr)*sin(lon+lon_incr);
				
				u = (lon+lon_incr)*0.5*M_1_PI;
				v = asin(vertices[index-1])*M_1_PI + 0.5;
				if (v == 0 || v == 1) u = 0.5;
				
				tex_coords[++tindex] = 1.f-u;
				tex_coords[++tindex] = 1.f-v;
				
				tanlon = lon + lon_incr + M_PI_2;
				
				tangents[++tanindex] = cos(tanlon);
				tangents[++tanindex] = 0.0;
				tangents[++tanindex] = sin(tanlon);
				
				// V3
				vertices[++index] = sin(lat+lat_incr)*cos(lon);
				vertices[++index] = cos(lat+lat_incr);
				vertices[++index] = sin(lat+lat_incr)*sin(lon);
				
				u = lon*0.5*M_1_PI;
				v = asin(vertices[index-1])*M_1_PI + 0.5;
				if (v == 0 || v == 1) u = 0.5;
				
				tex_coords[++tindex] = 1.f-u;
				tex_coords[++tindex] = 1.f-v;
				
				tanlon = lon + M_PI_2;
				
				tangents[++tanindex] = cos(tanlon);
				tangents[++tanindex] = 0.0;
				tangents[++tanindex] = sin(tanlon);
				
			
				// V4			
				vertices[++index] = sin(lat+lat_incr)*cos(lon+lon_incr);
				vertices[++index] = cos(lat+lat_incr);
				vertices[++index] = sin(lat+lat_incr)*sin(lon+lon_incr);
				
				u = (lon+lon_incr)*0.5*M_1_PI;
				v = asin(vertices[index-1])*M_1_PI + 0.5;
				if (v == 0 || v == 1) u = 0.5;
				
				tex_coords[++tindex] = 1.f-u;
				tex_coords[++tindex] = 1.f-v;
				
				tanlon = lon + lon_incr + M_PI_2;
				
				tangents[++tanindex] = cos(tanlon);
				tangents[++tanindex] = 0.0;
				tangents[++tanindex] = sin(tanlon);
				
				// V5				
				vertices[++index] = sin(lat)*cos(lon);
				vertices[++index] = cos(lat);
				vertices[++index] = sin(lat)*sin(lon);
				
				u = lon*0.5*M_1_PI;
				v = asin(vertices[index-1])*M_1_PI + 0.5;
				if (v == 0 || v == 1) u = 0.5;
				
				tex_coords[++tindex] = 1.f-u;
				tex_coords[++tindex] = 1.f-v;
				
				tanlon = lon + M_PI_2;
				
				tangents[++tanindex] = cos(tanlon);
				tangents[++tanindex] = 0.0;
				tangents[++tanindex] = sin(tanlon);
			
				// V6				
				vertices[++index] = sin(lat)*cos(lon+lon_incr);
				vertices[++index] = cos(lat);
				vertices[++index] = sin(lat)*sin(lon+lon_incr);
				
				u = (lon+lon_incr)*0.5*M_1_PI;
				v = asin(vertices[index-1])*M_1_PI + 0.5;
				if (v == 0 || v == 1) u = 0.5;
				
				tex_coords[++tindex] = 1.f-u;
				tex_coords[++tindex] = 1.f-v;
				
				tanlon = lon + lon_incr + M_PI_2;
				
				tangents[++tanindex] = cos(tanlon);
				tangents[++tanindex] = 0.0;
				tangents[++tanindex] = sin(tanlon);

				lat += lat_incr;
			}
			lon += lon_incr;
		}
		
		glEnable(GL_TEXTURE_2D);
		
		[self loadTextures];
		
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		
		program = [GLESFileLoader loadShaderNamed:@"Earth"];
		moon_program = [GLESFileLoader loadShaderNamed:@"Moon"];
		sun_program = [GLESFileLoader loadShaderNamed:@"Sun"];
		
		mv_loc = glGetUniformLocation(program, "mv");
		proj_loc = glGetUniformLocation(program, "proj");
		tex_index = glGetAttribLocation(program, "TextureCoord");
		
		m_camera = new OrbitingCamera();
		[self updateMatrices];
		track_moon = NO;
		speed_factor = 1.f;
		distance_factor = 1.f;
	}
	return self;
}

- (void)speedUp:(BOOL)up
{
	if (up) 
		speed_factor *= 2.f;
	else { 
		CGFloat temp = speed_factor * 0.5;
		if (temp > 0.f) speed_factor = temp;
	}
}

- (void)changeDistance
{
	if (distance_factor == 1.0) 
		distance_factor = 0.06;
	else distance_factor = 1.0;
}

- (void)trackMoon:(BOOL)track
{
	track_moon = track;
}

- (void)resizeWidth:(CGFloat)w Height:(CGFloat)h
{
    m_camera->setSize(w, h);
    [self updateMatrices];
}

- (void)dragX:(CGFloat)x Y:(CGFloat)y
{
	m_camera->mouse_dragged(x,y);
	[self updateMatrices];
}

- (void)zoom:(CGFloat)delta
{
	m_camera->lookVectorTranslate(delta);
	[self updateMatrices];
}

- (void)updateMatrices
{
	m_camera->getModelviewMatrix().getTranspose().fillArray(mv);
	m_camera->getProjectionMatrix().getTranspose().fillArray(proj);
}


- (void)drawFrame
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	[self renderEarth];
	[self renderMoon];
	[self renderSun];
}

- (void)renderSun
{
	glUseProgram(sun_program);
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, sun_texture);
	
	glUniformMatrix4fv(glGetUniformLocation(sun_program, "mv"), 1, GL_FALSE, mv);
	glUniformMatrix4fv(glGetUniformLocation(sun_program, "proj"), 1, GL_FALSE, proj);
	
	glUniform1i(glGetUniformLocation(sun_program, "SunTexture"), 0);
	glUniform1f(glGetUniformLocation(sun_program, "transx"), SUN_DISTANCE*distance_factor);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, 0, 0, vertices);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(tex_index, 2, GL_FLOAT, GL_FALSE, 0, tex_coords);
	glEnableVertexAttribArray(tex_index);
	glDrawArrays(GL_TRIANGLES, 0, 6*RES*RES);
	
	glUseProgram(0);
}

- (void)renderMoon
{
	glUseProgram(moon_program);
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, moon_texture);
	
	static float rotate = 0;
	
	glUniformMatrix4fv(glGetUniformLocation(moon_program, "mv"), 1, GL_FALSE, mv);
	glUniformMatrix4fv(glGetUniformLocation(moon_program, "proj"), 1, GL_FALSE, proj);
	
	glUniform1f(glGetUniformLocation(moon_program, "rotate"), rotate);
	rotate += 0.00033333*speed_factor;
	glUniform1f(glGetUniformLocation(moon_program, "tranz"), MOON_DISTANCE*distance_factor);
	
	glUniform3f(glGetUniformLocation(moon_program, "LightPosition"), SUN_DISTANCE, 0.0, 0.0);
	glUniform1i(glGetUniformLocation(moon_program, "MoonTexture"), 0);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, 0, 0, vertices);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(tex_index, 2, GL_FLOAT, GL_FALSE, 0, tex_coords);
	glEnableVertexAttribArray(tex_index);
	glDrawArrays(GL_TRIANGLES, 0, 6*RES*RES);
	
	glUseProgram(0);
}

- (void)renderEarth
{	
	static float rot = 0;
	
	glUseProgram(program);
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, day_texture);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, night_texture);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, clouds_texture);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, earth_bumpmap);
	glActiveTexture(GL_TEXTURE0);
		
	glUniformMatrix4fv(mv_loc, 1, GL_FALSE, mv);
	glUniformMatrix4fv(proj_loc, 1, GL_FALSE, proj);
	
	glUniform1f(glGetUniformLocation(program, "rot"), rot);
	rot += 0.01*speed_factor;
	
	glUniform3f(glGetUniformLocation(program, "LightPosition"), SUN_DISTANCE, 0.0, 0.0);
	glUniform1i(glGetUniformLocation(program, "EarthDay"), 0);
	glUniform1i(glGetUniformLocation(program, "EarthNight"), 1);
	glUniform1i(glGetUniformLocation(program, "EarthCloudGloss"), 2);
	glUniform1i(glGetUniformLocation(program, "BumpMap"), 3);

	glVertexAttribPointer(0, 3, GL_FLOAT, 0, 0, vertices);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(tex_index, 2, GL_FLOAT, GL_FALSE, 0, tex_coords);
	glEnableVertexAttribArray(tex_index);
	glVertexAttribPointer(glGetAttribLocation(program, "Tangent"), 3, GL_FLOAT, GL_FALSE, 0, tangents);
	glEnableVertexAttribArray(glGetAttribLocation(program, "Tangent"));
	glDrawArrays(GL_TRIANGLES, 0, 6*RES*RES);	
	
	glUseProgram(0); 
}

- (void)loadTextures
{
	moon_texture = [GLESFileLoader loadTextureNamed:@"Moontexture.jpg"]; // TODO: The call fails at first call :S
	moon_texture = [GLESFileLoader loadTextureNamed:@"Moontexture.jpg"];
	day_texture = [GLESFileLoader loadTextureNamed:@"DayHigh.jpg"];
	night_texture = [GLESFileLoader loadTextureNamed:@"Night.jpg"];
	clouds_texture = [GLESFileLoader loadTextureNamed:@"Clouds.jpg"];
	earth_bumpmap = [GLESFileLoader loadTextureNamed:@"earthNormalMap.png"];
	sun_texture = [GLESFileLoader loadTextureNamed:@"sunmap.jpg"];
}

- (void)dealloc
{
	glDeleteTextures(1, &day_texture);
	glDeleteTextures(1, &night_texture);
	glDeleteTextures(1, &clouds_texture);
	glDeleteTextures(1, &moon_texture);
	glDeleteTextures(1, &earth_bumpmap);
	glDeleteTextures(1, &sun_texture);
	if (program) {
        glDeleteProgram(program);
        program = 0;
    }
	if (moon_program) {
		glDeleteProgram(moon_program);
		moon_program = 0;
	}
	if (sun_program) {
		glDeleteProgram(sun_program);
		sun_program = 0;
	}
	
	delete m_camera;
	free(tex_coords);
	free(vertices);
	free(tangents);
	[super dealloc];
}

@end
