#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char **cmd_list;
    size_t array_size; 
} commands;
const char *initial_cmds[] = {"kori", "-help", "-v", "--version", "cf"};

void __init__(commands *cmd) {
    const char *initial_cmds[] = {"kori", "-help", "-v", "--version", "cf"};
    cmd->array_size = sizeof(initial_cmds) / sizeof(initial_cmds[0]);
    cmd->cmd_list = malloc(cmd->array_size * sizeof(char *));
    if (cmd->cmd_list == NULL) {
        fprintf(stderr, "Memory allocation failed for cmd->cmd_list\n");
        exit(1);
    }
    // printf("%p\n", &cmd->cmd_list);
    // printf("%zu == %zu\n", sizeof(initial_cmds[0]), sizeof(char *));
    for (size_t i = 0; i < cmd->array_size; i++) {
        size_t len = strlen(initial_cmds[i]);
        cmd->cmd_list[i] = malloc((len + 1) * sizeof(char));
        if (cmd->cmd_list[i] == NULL) {
            fprintf(stderr, "Memory allocation failed for cmd->cmd_list[%zu]\n", i);
            exit(1);
        }
        strcpy(cmd->cmd_list[i], initial_cmds[i]);
    }
}

bool isValid(char *argv, commands *cmd) {
    for (size_t b = 0; b < cmd->array_size; b++) {
        if (strcmp(argv, cmd->cmd_list[b]) == 0) {
            return true;
        }
    }
    return false;
}

int main(int argc, char *argv[]) {
    commands cmd_instance;  

    // Initialize array of commands
    __init__(&cmd_instance);
    ///////////////////////////////
    
    if (argc > 1) {
        for (int x = 1; x < argc; x++) {
            bool isVal = isValid(argv[x], &cmd_instance);
            if (isVal) {
                printf("Command is valid: %s\n", argv[x]);
            } else {
                printf("Invalid Command: %s\n", argv[x]);
            }
        }
    }else{
        printf("No command is passed try using kori -help");
        exit(1);
    }

    if (cmd_instance.cmd_list != NULL) {
        // printf("%s\n", cmd_instance.cmd_list);
        // printf("%p\n", cmd_instance.cmd_list);
        for (size_t i = 0; i < cmd_instance.array_size; i++) {
            free(cmd_instance.cmd_list[i]);
        }
        free(cmd_instance.cmd_list);
    }
    return 0;
}
