//
//  Super_LuperExtensionAudioUnit.h
//  Super LuperExtension
//
//  Created by Asher White on 2024-06-19.
//

#import <AudioToolbox/AudioToolbox.h>
#import <AVFoundation/AVFoundation.h>

@interface Super_LuperExtensionAudioUnit : AUAudioUnit
- (void)setupParameterTree:(AUParameterTree *)parameterTree;
@end
