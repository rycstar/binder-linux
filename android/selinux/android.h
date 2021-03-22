#ifndef __SELINUX_ANDROID_H__
#define __SELINUX_ANDROID_H__

#ifdef SELINUX_ENABLE

#include <selinux/selinux.h>
#include <selinux/avc.h>
#include <selinux/label.h>

extern struct selabel_handle* selinux_android_service_context_handle(void);
extern int selinux_log_callback(int type, const char *fmt, ...);
#endif

#endif /* __SELINUX_ANDROID_H__ */
