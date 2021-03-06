//
// AFSENCommonProtocols.h
//
// Copyright (c) 2012 ap4y (lod@pisem.net)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

/**
 Common domain for the all engine errors
 */
#define kErrorDomain @"com.sonan.engine.error"

/**
 Libarary error codes
 */
#ifndef NS_ENUM
#import <Foundation/Foundation.h>
#endif
typedef NS_ENUM(NSInteger, AFSENErrorCodes) {
    AFSENErrorCodesSourceFailed,
    AFSENErrorCodesConverterFailed,
    AFSENErrorCodesDecoderFailed,
    AFSENErrorCodesContainerFailed
};


@protocol AFSENSource;


@protocol AFSENSourceDelegate <NSObject>

@optional

- (void)sourceDidReceiveData:(nonnull id<AFSENSource>)source;

- (void)source:(nonnull id<AFSENSource>)source didFailWithError:(nonnull NSError *)error;

@end

/**
 All classes that act as plugins must adopt the `AFSENObject` protocol. This protocol is a stub, future versions may require common plugin object protocol.
 */
@protocol AFSENObject <NSObject>
@end

/**
 All classes that act as input source must adopt the `AFSENSource` protocol. This protocol contains methods for communication with plugin manager.
 */
@protocol AFSENSource <AFSENObject>

@property (nonatomic, weak, nullable) id<AFSENSourceDelegate> sourceDelegate;

/**
 Returns supported url scheme.
 
 @return A string with supported url scheme.
 */
+ (nonnull NSString *)scheme;

/**
 Returns current source file url.
 
 @return Current file url.
 */
@property (readonly, copy) NSURL * _Nonnull url;

@property (readonly, copy) NSString * _Nonnull pathExtension;

/**
 Returns source file size.
 
 @return A file size in `bytes`.
 */
@property (readonly) long size;

@property (readonly) long preloadSize;

/**
 Opens source file for `read`.
 
 @param url A source file url.
 
 @return `YES` if success, otherwise `NO`.
 */
- (BOOL)open:(nonnull NSURL *)url;

/**
 Determines if source is seekable.
 
 @return `YES` if seekable, otherwise `NO`.
 */
@property (readonly) BOOL seekable;

/**
 Seeks within a source file in specified direction.
 
 @param position Offset within a source file in `bytes`.
 @param whence Seek base. Supported values `SEEK_SET`, `SEEK_CUR`, or `SEEK_END`.
 
 @return `YES` if success, otherwise `NO`.
 */
- (BOOL)seek:(long)position whence:(int)whence;

/**
 Returns current position offset within a source file.
 
 @return A position offset in `bytes`.
 */
@property (readonly) long tell;

/**
 Reads specified amount of data from a source file into provided buffer.
 
 @param buffer A pointer to a buffer. You should allocate enough memory for a buffer.
 @param amount Amount of `bytes` to read from a source.
 
 @return Actual amount of `bytes` read from a source.
 */
- (int)read:(nonnull void *)buffer amount:(int)amount;

/**
 Closes a source file. 
 */
- (void)close;

@property (getter=isRemoteSource, readonly) BOOL remoteSource;

@end

/**
 All classes that act as tracks container decoders must adopt the `AFSENContainer` protocol. This protocol contains methods for communication with plugin manager.
 */
@protocol AFSENContainer <AFSENObject>

/**
 Returns supported file extensions.
 
 @return An array with supported file extensions.
 */
+ (nonnull NSArray *)fileTypes;

/**
 Parses and returns track urls from specified container.
 
 @param url A url of a container file to parse.
 
 @return An array of track urls from container.
 */
+ (nullable NSArray *)urlsForContainerURL:(nonnull NSURL *)url;
@end

/**
 All classes that act as decoders must adopt the `AFSENDecoder` protocol. This protocol contains methods for communication with plugin manager.
 */
@protocol AFSENDecoder <AFSENObject>
@required

/**
 Returns supported file extensions.
 
 @return An array with supported file extensions.
 */
+ (nonnull NSArray *)fileTypes;

/**
 Returns current audio properties.
 
 @discussion Dictionary data format contains keys:
 
 - `(int)channels`
 - `(int)bitsPerSample`,
 - `(float)sampleRate`,
 - `(double)totalFrames`,
 - `(BOOL)seekable`,
 - `(NSString *)endian`.
 
 @return A properties dictionary.
 */
@property (readonly, copy) NSDictionary * _Nonnull properties;

/**
 Returns current track metadata.
 
 @discussion Dictionary data format depends on the track format. Cover art is included as `NSData` object.
 
 @return A Metadata dictionary or `nil` if track don't have metadata.
 */
@property (readonly, copy) NSDictionary * _Nullable metadata;

/**
 Reads and decodes specified amount of frames from a source into provided buffer.
 
 @param buffer A pointer to a buffer. You should allocate enough memory for a buffer.
 @param frames Amount of `frames` to read from a source.
 
 @return Actual amount of `frames` read from a source.
 */
- (int)readAudio:(nonnull void *)buffer frames:(UInt32)frames;

/**
 Initialises decoder from specified source.
 
 @param source A source instance.
 
 @return `YES` if success, otherwise `NO`.
 */
- (BOOL)open:(nonnull id<AFSENSource>)source;

/**
 Seeks to a specified frame and continues decoding from that frame.
 
 @param frame Desired offset in `frames`.
 
 @return Actual offset in `frames`.
 */
- (long)seek:(long)frame;

/**
 Closes decoder and corresponding source, deallocates unnecessary resources.
 */
- (void)close;
@end