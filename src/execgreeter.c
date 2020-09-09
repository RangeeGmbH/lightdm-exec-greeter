//
// Created by justin on 05.06.20.
//

#include "execgreeter.h"
#include "config.h"

/**
 * Prepares the Greeter to be used and initilizes the config
 * @return ExecGreeter
 */
ExecGreeter *initializeExecGreeter() {
    g_message("Initializing lightdm-exec-greeter...");

    ExecGreeter *execGreeter = malloc(sizeof(ExecGreeter));
    execGreeter->greeter = lightdm_greeter_new();
    execGreeter->config = initializeConfig();
    execGreeter->mainLoop = g_main_loop_new(NULL, 0);

    registerSignals(execGreeter);
    connectToDaemon(execGreeter);

    g_message("Initializing done!");

    return execGreeter;
}

/**
 * Starts the Greeter
 * @param execGreeter
 */
void startExecGreeter(ExecGreeter* execGreeter) {
    executeUntilSuccessful(execGreeter);
    //lightdm_greeter_set_resettable(execGreeter->greeter, TRUE); //this is to prevent the greeter from exiting after the session starts
    authenticateUser(execGreeter);

    //Runs until g_main_loop_quit is executed
    g_main_loop_run(execGreeter->mainLoop);

    g_message("Exiting lightdm-exec-greeter...");

    destroyConfig(execGreeter->config);
    destroyExecGreeter(execGreeter);

    g_message("Exiting complete!");
}

/**
 * Registers the signals to listen to events
 * @param execGreeter
 */
void registerSignals(ExecGreeter *execGreeter) {
    g_signal_connect(execGreeter->greeter, "authentication-complete", G_CALLBACK(authenticationCompleteCb), execGreeter);
}

/**
 * Connects the greeter with the LightDM daemon.
 * @param execGreeter
 */
void connectToDaemon(ExecGreeter *execGreeter) {
    g_message("Conneting to daemon...");

    while(!lightdm_greeter_connect_to_daemon_sync(execGreeter->greeter, NULL)) {
        g_message("Can't connect to daemon!");
    }

    g_message("Successfully connected to daemon!");
}

/**
 * Starts Authentication for given user
 * @param greeter
 */
void authenticateUser(ExecGreeter *execGreeter) {
    g_message("Authenticate...");

    while(!lightdm_greeter_authenticate(execGreeter->greeter, execGreeter->config->username, NULL)) {
        g_message("Authentication unsuccessful!");
    }

    g_message("Authentication successful!");
}

/**
 * Starts the session after the authentication is complete
 * @param greeter
 * @param execGreeter
 */
void authenticationCompleteCb(LightDMGreeter *greeter, ExecGreeter *execGreeter) {
    const gchar *session = lightdm_greeter_get_default_session_hint(greeter);
    g_message("Starting session '%s'...", session);

    //Greeter is going to quit after the session was startet when resettable is false
    while(!lightdm_greeter_start_session_sync(greeter, lightdm_greeter_get_default_session_hint(greeter), NULL)) {
        g_message("Session couldn't be started!"); //Todo dont do this in a loop find another way to backup from a failure
    }

    g_message("Session successfully started!");
    g_main_loop_quit(execGreeter->mainLoop);
}

/**
 * Executes the given script until the required exitcode defined in the config is reached
 * @param execGreeter
 */
void executeUntilSuccessful(ExecGreeter *execGreeter) {
    gchar* path = execGreeter->config->exec;

    int exitcode;
    int requiredExitcode = execGreeter->config->requiredExitcode;
    int timeout = execGreeter->config->execRetryTimeout;

    g_message("Executing %s...", path);

    //we multiple it by 256 the system() function return the exitcode * 256
    while((exitcode = system(path)) != requiredExitcode * 256) { //todo make configurable
        g_message("%s Returned with %i but should be %i! retrying in %ims...", path, exitcode/256, requiredExitcode, timeout);
        usleep(timeout * 1000);
    }

    g_message("%s Successfully executed!", path);
}

/**
 * Cleaning up
 * @param execGreeter
 */
void destroyExecGreeter(ExecGreeter *execGreeter) {
    free(execGreeter->mainLoop);
    free(execGreeter->greeter);
    free(execGreeter->config);
    free(execGreeter);
}
