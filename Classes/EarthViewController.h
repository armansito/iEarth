//
//  EarthViewController.h
//  Earth
//
//  Created by Arman Uguray on 2/21/11.
//  Copyright 2011 Brown University. All rights reserved.
//

#import <UIKit/UIKit.h>

#import <OpenGLES/EAGL.h>

#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>

#import "EarthRenderer.h"

@interface EarthViewController : UIViewController
{
    EAGLContext *context;
    
	EarthRenderer *earthRenderer;
	
    BOOL animating;
    NSInteger animationFrameInterval;
    CADisplayLink *displayLink;
}

@property (readonly, nonatomic, getter=isAnimating) BOOL animating;
@property (nonatomic) NSInteger animationFrameInterval;
@property (retain, readonly) EarthRenderer *earthRenderer;

- (void)startAnimation;
- (void)stopAnimation;

@end
