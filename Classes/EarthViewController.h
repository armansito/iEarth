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

@class EAGLView;

@interface EarthViewController : UIViewController
{
    EAGLContext *context;
	IBOutlet EAGLView *eaglview;
    IBOutlet UIToolbar *toolbar;
	
	EarthRenderer *earthRenderer;
	
	
    BOOL animating;
    NSInteger animationFrameInterval;
    CADisplayLink *displayLink;
}

@property (nonatomic, retain, readonly) IBOutlet UIToolbar *toolbar;
@property (nonatomic, retain, readonly) IBOutlet EAGLView *eaglview;
@property (readonly, nonatomic, getter=isAnimating) BOOL animating;
@property (nonatomic) NSInteger animationFrameInterval;
@property (retain, readonly) EarthRenderer *earthRenderer;

- (IBAction)trackEarth;
- (IBAction)trackMoon;

- (IBAction)speedUp;
- (IBAction)slowDown;

- (IBAction)changeDistances;

- (void)startAnimation;
- (void)stopAnimation;

@end
