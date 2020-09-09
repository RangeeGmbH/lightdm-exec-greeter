//
// Created by justin on 05.06.20.
//

#ifndef EXECGREETER_EXECGREETER_H
#define EXECGREETER_EXECGREETER_H

#include "config.h"
#include <lightdm.h>
typedef struct ExecGreeter_ {
    LightDMGreeter *greeter;
    Config *config;
    GMainLoop *mainLoop;
} ExecGreeter;

ExecGreeter *initializeExecGreeter();
void startExecGreeter(ExecGreeter* execGreeter);
void registerSignals(ExecGreeter *execGreeter);
void connectToDaemon(ExecGreeter *execGreeter);
void authenticateUser(ExecGreeter *execGreeter);
void authenticationCompleteCb(LightDMGreeter *greeter, ExecGreeter *execGreeter);
void executeUntilSuccessful(ExecGreeter *execGreeter);
void destroyExecGreeter(ExecGreeter *execGreeter);
#endif //EXECGREETER_EXECGREETER_H
