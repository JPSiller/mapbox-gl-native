#import <Foundation/Foundation.h>

#import "MGLFoundation.h"

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, MGLLoggingLevel) {
    /**
     None-level messages are ignored.
     */
    MGLLoggingLevelNone = 0,
    /**
     Info-level messages contain information that may be helpful for flow tracing
     but is not essential.
     */
    MGLLoggingLevelInfo,
    /**
     Debug-level messages contain information that may be helpul for troubleshooting
     specific problems.
     */
    MGLLoggingLevelDebug,
    /**
     Error-level messages contain information that is intended to aid in process-level
     errors.
     */
    MGLLoggingLevelError,
    /**
     Fault-level messages contain system-level error information.
     */
    MGLLoggingLevelFault,
    
};

typedef void (^MGLLoggingBlockHandler)(MGLLoggingLevel, NSString *, NSString *);

MGL_EXPORT
@interface MGLLogging : NSObject

@property (nonatomic, copy, null_resettable) MGLLoggingBlockHandler handler;
@property (assign, nonatomic) MGLLoggingLevel loggingLevel;

+ (instancetype)sharedInstance;

- (MGLLoggingBlockHandler)handler UNAVAILABLE_ATTRIBUTE;

@end

NS_ASSUME_NONNULL_END
