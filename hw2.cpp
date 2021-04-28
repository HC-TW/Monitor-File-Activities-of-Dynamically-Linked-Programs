#include <iostream>
#include <string>
#include <string.h>
#include <unistd.h>

#include <sys/wait.h>
#include <sys/ptrace.h>
#include <sys/user.h>

using namespace std;

int main(int argc, char *argv[])
{
    int c, cmdIndex = 1;
    pid_t pid;

    for (int i = 1; i < argc; i++)
    {
        if (!strcmp(argv[i], "--"))
        {
            cmdIndex = i + 1;
            break;
        }
    }

    setenv("LD_PRELOAD", "./logger.so", 1);
    while ((c = getopt(argc, argv, "o:p:")) != -1)
        switch (c)
        {
        case 'o':
            setenv("LOGGER_OUTPUT", optarg, 1);
            break;
        case 'p':
            setenv("LD_PRELOAD", optarg, 1);
            break;
        case '?':
            cerr << "usage: ./logger [-o file] [-p sopath] [--] cmd [cmd args ...]\n"
                    "    -p: set the path to logger.so, default = ./logger.so\n"
                    "    -o: print output to file, print to \"stderr\" if no file specified\n"
                    "    --: separate the arguments for logger and for the command"
                 << endl;
            return 1;
        }

    if (cmdIndex == argc)
    {
        cerr << "no command given." << endl;
        return 1;
    }

    if ((pid = fork()) == 0)
    {
        char *cmd[argc - cmdIndex + 1];
        for (int i = 0; i < argc - cmdIndex; i++)
        {
            cmd[i] = argv[i + cmdIndex];
        }
        cmd[argc - cmdIndex] = NULL;

        execvp(cmd[0], cmd);
    }
    else
    {
        int status;
        wait(&status);
    }

    return 0;
}