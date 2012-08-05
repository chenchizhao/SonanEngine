//
//  ORGMOutputUnit.h
//  Origami-engine
//
//  Created by ap4y on 8/5/12.
//
//

#import "ORGMAudioUnit.h"

#import "ORGMConverter.h"

@interface ORGMOutputUnit : ORGMAudioUnit
@property (nonatomic, readonly) BOOL isProcessing;

- (id)initWithConverter:(ORGMConverter*)converter;
- (AudioStreamBasicDescription)format;
@end