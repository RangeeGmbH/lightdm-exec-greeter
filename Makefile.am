AUTOMAKE_OPTIONS = foreign
#AM_FLAGS = -DCONFIG_FILE=\""$(sysconfdir)/lightdm/lightdm-mini-greeter.conf"\"

bin_PROGRAMS = lightdm-exec-greeter

configdir = /etc/lightdm
dist_config_DATA = data/lightdm-exec-greeter.conf

lightdm_exec_greeter_SOURCES = src/main.c src/config.c src/config.h src/execgreeter.c src/execgreeter.h

lightdm_exec_greeter_CFLAGS = $(LIGHTDM_CFLAGS) $(GLIB_CFLAGS)

lightdm_exec_greeter_LDADD = $(LIGHTDM_LIBS) $(GLIB_LIBS)