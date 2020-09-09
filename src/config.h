//
// Created by justin on 04.06.20.
//

#ifndef EXECGREETER_CONFIG_H
#define EXECGREETER_CONFIG_H

#include <glib.h>

#ifndef CONFIG_FILE
#define CONFIG_FILE "/etc/lightdm/lightdm-exec-greeter.conf"
#endif


typedef struct Config {
    gchar *username;
    gchar *exec;
    gint requiredExitcode;
    gint execRetryTimeout;
} Config;


Config *initializeConfig(void);
void destroyConfig(Config *config);

#endif //EXECGREETER_CONFIG_H


