#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#ifdef _WIN32
    #define clear() system("cls")
#else
    #define clear() system("clear")
#endif

#include "utils.h"
#include "command_parser.h"

#define HASH_OPEN 2090588023UL
#define HASH_NEW 193500239UL

void fail(int argc, char **argv);

int main(int argc, char **argv) {

    if (argc < 2) {
        fail(argc, argv);
    }

    FILE *note_file = NULL;
    switch (hash(argv[1]))
    {
    case HASH_OPEN:
        if (argc < 3) {
            printf("No note_file specified.\n");
            printf("usage: %s open <note_filename>\n", argv[0]);
            exit(EXIT_FAILURE);
        }

        note_file = fopen(argv[2], "r+");
        if (!note_file) {
            printf("Error opening note_file.\n");
            exit(EXIT_FAILURE);
        }
        break;
    
    case HASH_NEW:
        if (argc < 3) {
            printf("No note_file specified.\n");
            printf("usage: %s new <note_filename>\n", argv[0]);
            exit(EXIT_FAILURE);
        }
    
        note_file = fopen(argv[2], "w+");
        if (!note_file) {
            printf("Error opening note_file.\n");
            exit(EXIT_FAILURE);
        }
        break;
    
    default:
        printf("Unrecognized command '%s'.\n", argv[1]);
        fail(argc, argv);
    }


    char *input_buff = calloc(BUFF_LEN, 1);
    char *curr_sect = calloc(256, 1);
    strcpy_s(curr_sect, 256, argv[2]);

    bool isRunning = true;
    while (isRunning) {
        printf("CL-Note (%s) > ", curr_sect);
        scanf("%[^\n]", input_buff);

        struct command *curr_command = parse(input_buff);
        printf("Command type is %d and command contents is %s.\n", curr_command->type, curr_command->contents);

        switch (curr_command->type)
        {
        case EXIT:
            isRunning = false;
            break;
        
        case CLEAR:
            clear();
            break;
        
        default:
            printf("Unrecognized command.\n");
        }

        free(curr_command->contents);
        free(curr_command);
        memset(input_buff, 0, BUFF_LEN);
        getc(stdin);
    }


    free(curr_sect);
    free(input_buff);

    return 0;
}

void fail(int argc, char **argv) {
    printf("usage: %s <command> [<args>]\n\n", argv[0]);
    printf("Commands: \n\n");
    printf("  open\tOpen an existing note_file\n");
    printf("  new\tCreate a new note note_file\n");

    exit(EXIT_FAILURE);
}
