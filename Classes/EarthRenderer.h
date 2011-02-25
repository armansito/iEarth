//
//  EarthRenderer.h
//  Earth
//
//  Created by Arman Uguray on 2/21/11.
//  Copyright 2011 Brown University. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>

// TODO: implement Moon tracking

typedef struct OrbitingCamera OrbitingCamera;

@interface EarthRenderer : NSObject {
	
	GLuint program, mv_loc, proj_loc, moon_program, sun_program;
	GLuint tex_index;
	
	GLuint day_texture, night_texture, clouds_texture, moon_texture, sun_texture, earth_bumpmap;
	GLfloat *vertices; // holds both vertices and normals
	GLfloat *tex_coords;
	GLfloat *tangents;
	OrbitingCamera *m_camera;
	
	BOOL track_moon;
	
	CGFloat speed_factor, distance_factor;
	
	GLfloat mv[16], proj[16];
}

@property(nonatomic, readonly) OrbitingCamera *camera;

- (id)init;
- (void)loadTextures;
- (void)updateMatrices;
- (void)drawFrame;

- (void)speedUp:(BOOL)up;
- (void)changeDistance;

- (void)trackMoon:(BOOL)track;

- (void)dragX:(CGFloat)x Y:(CGFloat)y;
- (void)zoom:(CGFloat)delta;

@end
