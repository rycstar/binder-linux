#ifndef __C_CONFIG_H__
#define __C_CONFIG_H__

#ifdef __cplusplus
extern "C" {
#endif

int get_c_config(const char * name);
int set_c_config(const char * name, int value);
int save_c_config(void);

#ifdef __cplusplus
}
#endif
#endif
