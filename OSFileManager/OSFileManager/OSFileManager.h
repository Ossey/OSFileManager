//
//  OSFileManager.h
//  OSFileManager
//
//  Created by Ossey on 2017/7/22.
//  Copyright © 2017年 Ossey. All rights reserved.
//

#import <Foundation/Foundation.h>

#if TARGET_OS_IPHONE
#elif TARGET_OS_MAC
#import <Cocoa/Cocoa.h>
#endif


typedef NS_ENUM(NSInteger, OSFileWriteStatus) {
    OSFileWriteCanceled,      // 取消写入
    OSFileWriteWaiting,       // 等待写入
    OSFileWriteExecuting,     // 正在执行该写入
    OSFileWriteFinished,      // 写入完成
    OSFileWriteFailure        // 写入失败
};

@protocol OSFileOperation;

typedef unsigned long long OSFileInteger;
typedef void(^OSFileOperationCompletionHandler)(id<OSFileOperation> fileOperation, NSError *error);
typedef void(^OSFileOperationProgress)(NSProgress *progress);

@interface OSFileManager : NSObject

@property (nonatomic, assign) NSInteger maxConcurrentOperationCount;
@property (nonatomic, assign) NSUInteger pendingOperationCount;
@property (nonatomic, strong) NSNumber *totalProgressValue;
@property (nonatomic, strong) NSNumber *totalSourceBytes;
@property (nonatomic, strong) NSNumber *totalCopiedBytes;
@property (nonatomic, strong) OSFileOperationProgress totalProgressBlock;
@property (nonatomic, strong, readonly) NSArray<id<OSFileOperation>> *operations;

+ (OSFileManager *)defaultManager;

- (void)copyItemAtURL:(NSURL *)srcURL toURL:(NSURL *)dstURL progress:(OSFileOperationProgress)progress completionHandler:(OSFileOperationCompletionHandler)handler;

- (void)moveItemAtURL:(NSURL *)srcURL toURL:(NSURL *)dstURL progress:(OSFileOperationProgress)progress completionHandler:(OSFileOperationCompletionHandler)handler;

- (void)cancelAllOperation;

@end

@protocol OSFileOperation <NSObject>

@property (nonatomic, copy) NSURL *sourceURL;
@property (nonatomic, copy) NSURL *dstURL;
@property (nonatomic, assign) OSFileInteger sourceTotalBytes;
@property (nonatomic, assign) OSFileInteger receivedCopiedBytes;
@property (nonatomic, assign) NSTimeInterval secondsRemaining;
@property (nonatomic, strong) NSError *error;
@property (nonatomic, copy, readonly) NSString *fileName;
@property (nonatomic, readonly, assign) BOOL isCancelled;
@property (nonatomic, strong) NSProgress *progress;
@property (nonatomic, assign) OSFileWriteStatus writeState;

- (instancetype)initWithSourceURL:(NSURL *)sourceURL
                           desURL:(NSURL *)desURL
                         progress:(OSFileOperationProgress)progress
                completionHandler:(OSFileOperationCompletionHandler)completionHandler;
- (void)cancel;

@end