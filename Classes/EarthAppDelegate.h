//
//  EarthAppDelegate.h
//  Earth
//
//  Created by Arman Uguray on 2/21/11.
//  Copyright 2011 Brown University. All rights reserved.
//

#import <UIKit/UIKit.h>

@class EarthViewController;

@interface EarthAppDelegate : NSObject <UIApplicationDelegate> {
    UIWindow *window;
    EarthViewController *viewController;
}

@property (nonatomic, retain) IBOutlet UIWindow *window;
@property (nonatomic, retain) IBOutlet EarthViewController *viewController;

@end

