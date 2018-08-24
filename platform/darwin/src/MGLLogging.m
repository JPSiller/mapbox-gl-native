#import "MGLLogging_Private.h"

#if __has_builtin(__builtin_os_log_format)
#import <os/log.h>
#endif

@implementation MGLLogging

+ (instancetype)sharedInstance
{
    static dispatch_once_t once;
    static id sharedInstance;
    dispatch_once(&once, ^{
        sharedInstance = [[self alloc] init];
        ((MGLLogging *)sharedInstance).handler = nil;
    });
    return sharedInstance;
}

- (void)setHandler:(void (^)(MGLLoggingLevel, NSString *, NSString *))handler {
    
    if (!handler) {
        _handler = [self defaultBlockHandler];
    } else {
        _handler = handler;
    }
}

- (void)logMessageFormat:(NSString *)fmt callingFunction:(const char *)callingFunction functionLine:(NSUInteger)functionLine messageType:(MGLLoggingLevel)type
{
    _handler(type, [NSString stringWithFormat:@"%s", callingFunction], fmt);
}

- (MGLLoggingBlockHandler)defaultBlockHandler {
    MGLLoggingBlockHandler mapboxHandler = ^(MGLLoggingLevel level, NSString *fileName, NSString *message) {
        
        if (@available(iOS 10.0, macOS 10.12.0, *)) {
            static dispatch_once_t once;
            static os_log_t mapbox_log;
            static NSArray *logTypes;
            dispatch_once(&once, ^ {
                mapbox_log = os_log_create("com.mapbox.maps-ios-sdk", "SDK");
                logTypes = @[@(OS_LOG_TYPE_DEFAULT),
                             @(OS_LOG_TYPE_INFO),
                             @(OS_LOG_TYPE_DEBUG),
                             @(OS_LOG_TYPE_ERROR),
                             @(OS_LOG_TYPE_FAULT)];
            });
            os_log_type_t logType = [[logTypes objectAtIndex:level] intValue];
            NSString *formattedMessage = [NSString stringWithFormat:@"%@ %@", fileName, message];
            const char *msg = [formattedMessage UTF8String];
            os_log_with_type(mapbox_log, logType, "%{public}s", msg);
        } else {
            NSLog(@"[SDK] %@ %@", fileName, message);
        }
    };
    
    return mapboxHandler;
}

@end
