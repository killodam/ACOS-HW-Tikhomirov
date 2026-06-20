#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

char **split(const char *str) {
    char *copy = strdup(str);
    int cap = 16, n = 0;
    char **argv = malloc(cap * sizeof(char *));

    char *tok = strtok(copy, " \t");
    while (tok) {
        if (n + 1 >= cap) {
            cap *= 2;
            argv = realloc(argv, cap * sizeof(char *));
        }
        argv[n++] = strdup(tok);
        tok = strtok(NULL, " \t");
    }
    argv[n] = NULL;
    free(copy);
    return argv;
}

void free_argv(char **argv) {
    for (int i = 0; argv[i]; i++) free(argv[i]);
    free(argv);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s \"cmd arg0 arg1\" \"cmd2 arg0\" ...\n", argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        char **cmd_argv = split(argv[i]);

        int pipe_fd[2];
        if (pipe(pipe_fd) == -1) {
            perror("pipe");
            return 1;
        }

        pid_t pid1 = fork();
        if (pid1 == -1) { perror("fork"); return 1; }

        if (pid1 == 0) {
            close(pipe_fd[0]);
            dup2(pipe_fd[1], STDOUT_FILENO);
            close(pipe_fd[1]);
            execvp(cmd_argv[0], cmd_argv);
            perror("execvp");
            exit(1);
        }

        pid_t pid2 = fork();
        if (pid2 == -1) { perror("fork"); return 1; }

        if (pid2 == 0) {
            close(pipe_fd[1]);
            dup2(pipe_fd[0], STDIN_FILENO);
            close(pipe_fd[0]);
            execlp("wc", "wc", "-c", NULL);
            perror("execlp");
            exit(1);
        }

        close(pipe_fd[0]);
        close(pipe_fd[1]);

        waitpid(pid1, NULL, 0);
        waitpid(pid2, NULL, 0);

        free_argv(cmd_argv);
    }

    return 0;
}
