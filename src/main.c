#include "execgreeter.h"

int main() {
    ExecGreeter *execGreeter = initializeExecGreeter();
    startExecGreeter(execGreeter);
}
