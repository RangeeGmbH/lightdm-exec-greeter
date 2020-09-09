//
// Created by justin on 04.06.20.
//

#include <stdlib.h>
#include <string.h>

#include <glib.h>
#include "config.h"

Config *initializeConfig(void) {
    Config *config = malloc(sizeof(Config));
    if (config == NULL) {
        g_error("Couldn't allocate memory for Config");
    }

    GKeyFile *keyfile = g_key_file_new();
    g_autoptr(GError) error = NULL;
    gboolean keyfile_loaded = g_key_file_load_from_file(keyfile, CONFIG_FILE, G_KEY_FILE_NONE, &error);
    if (!keyfile_loaded) {
        g_error("Couldn't load configuration file in '%s' reason: %s", CONFIG_FILE, error->message);
    }

    config->username = g_key_file_get_string(keyfile, "greeter", "username", NULL);
    if(config->username == NULL || strlen(g_strchomp(config->username)) == 0) {
        g_error("No username is set!");
    }
    config->username = g_strchomp(config->username);


    config->exec = g_key_file_get_string(keyfile, "greeter", "exec", NULL);

    if(config->exec == NULL || (config->exec != NULL && strlen(g_strchomp(config->exec)) == 0)) {
        g_error("exec path is empty!");
    }

    //let the string go to the barbershop and trim those unnecessary whitespaces
    config->exec = g_strchomp(config->exec);

    config->requiredExitcode = g_key_file_get_integer(keyfile, "greeter", "requiredExitcode", NULL);
    config->execRetryTimeout = g_key_file_get_integer(keyfile, "greeter", "execRetryTimeout", NULL);

    g_key_file_free(keyfile);
    return config;
}

/* Cleanup any memory allocated for the Config */
void destroyConfig(Config *config) {
    free(config->username);
    free(config->exec);
    free(config);
}
