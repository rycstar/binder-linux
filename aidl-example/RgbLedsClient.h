#ifndef __RGB_LEDS_CLIENT_H__
#define __RGB_LEDS_CLIENT_H__

#ifdef __cplusplus
extern "C" {
#endif
extern void* get_service(const char * name);
extern void call_set_rgb_color(void * srv, int a, int b);
extern void call_set_rgb_list(void *srv, int num);
extern void call_set_rgb_brightness(void * srv, int a, int b);
#ifdef __cplusplus
}
#endif

#endif
