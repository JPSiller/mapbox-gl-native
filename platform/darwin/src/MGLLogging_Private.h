#import "MGLLogging.h"

#define mgl_log_info(message, ...)  mgl_log_with_type(MGLLoggingLevelInfo, __PRETTY_FUNCTION__, __LINE__, message, ##__VA_ARGS__)
#define mgl_log_debug(message, ...) mgl_log_with_type(MGLLoggingLevelDebug, __PRETTY_FUNCTION__, __LINE__, message, ##__VA_ARGS__)
#define mgl_log_error(message, ...) mgl_log_with_type(MGLLoggingLevelError, __PRETTY_FUNCTION__, __LINE__, message, ##__VA_ARGS__)
#define mgl_log_fault(message, ...) mgl_log_with_type(MGLLoggingLevelFault, __PRETTY_FUNCTION__, __LINE__, message, ##__VA_ARGS__)
#define mgl_log_with_type(type, function, line, message, ...) \
{ \
    if ([MGLLogging sharedInstance].loggingLevel != MGLLoggingLevelNone && type <= [MGLLogging sharedInstance].loggingLevel) \
    { \
        NSString *fmt = [NSString stringWithFormat:(message), ##__VA_ARGS__];  \
        [[MGLLogging sharedInstance] logMessageFormat:fmt callingFunction:function functionLine:line messageType:type]; \
    } \
}

@interface MGLLogging (Private)

- (void)logMessageFormat:(NSString *)fmt callingFunction:(const char *)callingFunction functionLine:(NSUInteger)functionLine messageType:(MGLLoggingLevel)type;

@end
