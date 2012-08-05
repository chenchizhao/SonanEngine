//
//  ORGMInputUnit.h
//  Origami-engine
//
//  Created by ap4y on 8/5/12.
//
//

#import "ORGMAudioUnit.h"

@interface ORGMInputUnit : ORGMAudioUnit
@property (nonatomic, strong, readonly) NSMutableData* data;
@property (nonatomic, readonly) BOOL isProcessing;

- (BOOL)openWithUrl:(NSURL*)url;
- (void)requestNext;
- (AudioStreamBasicDescription)format;
@end