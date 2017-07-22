//
//  OSFileManager.h
//  OSFileManager
//
//  Created by Ossey on 2017/7/22.
//  Copyright © 2017年 Ossey. All rights reserved.
//

#import <Cocoa/Cocoa.h>


@protocol OSFileOperation;

typedef unsigned long long OSFileInteger;
typedef void(^OSFileOperationCompletionHandler)(id<OSFileOperation> fileOperation, NSError *error);
typedef void(^OSFileOperationProgress)(float progress);

@interface OSFileManager : NSObject

@property (nonatomic, assign) NSInteger maxConcurrentOperationCount;
@property (nonatomic, assign) NSUInteger pendingOperationCount;
@property (nonatomic, strong) NSNumber *totalProgress;
@property (nonatomic, strong) NSNumber *totalSourceBytes;
@property (nonatomic, strong) NSNumber *totalCopiedBytes;

+ (OSFileManager *)defaultManager;

- (void)copyItemAtURL:(NSURL *)srcURL toURL:(NSURL *)dstURL progress:(OSFileOperationProgress)progress completionHandler:(OSFileOperationCompletionHandler)handler;

- (void)moveItemAtURL:(NSURL *)srcURL toURL:(NSURL *)dstURL progress:(OSFileOperationProgress)progress completionHandler:(OSFileOperationCompletionHandler)handler;

- (void)cancelAllOperation;

@end

@protocol OSFileOperation <NSObject>

@property (nonatomic, copy) NSURL *sourceURL;
@property (nonatomic, copy) NSURL *dstURL;
@property (nonatomic, strong) NSNumber *sourceBytes;
@property (nonatomic, strong) NSNumber *copiedBytes;
@property (nonatomic, readonly) NSNumber *progress;
@property (nonatomic, strong) NSNumber *secondsRemaining;
@property (nonatomic, strong) NSError *error;
@property (nonatomic, copy, readonly) NSString *fileName;
@property (nonatomic, readonly, assign) BOOL isCancelled;

- (instancetype)initWithSourceURL:(NSURL *)sourceURL desURL:(NSURL *)desURL progress:(OSFileOperationProgress)progress completionHandler:(OSFileOperationCompletionHandler)completionHandler;
- (void)cancel;

@end