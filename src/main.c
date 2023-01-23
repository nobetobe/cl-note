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
#include "sect.h"

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
    struct sect *curr_sect = sect_new_sect(argv[2]);
    char *display_sect = calloc(BUFF_LEN, 1);
    strncpy(display_sect, curr_sect->name, BUFF_LEN-1);

    bool isRunning = true;
    while (isRunning) {

        printf("CL-Note (%s) > ", display_sect);
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
        
        case CHANGE_SECT:
            if (curr_command->contents[0] == '.') {
                if (curr_sect->parent == NULL) {
                    printf("Already at top section.\n");
                    break;
                }
            
                curr_sect = curr_sect->parent;
                while (display_sect[strlen(display_sect)-1] != '/') {
                    display_sect[strlen(display_sect)-1] = '\0';
                }
                display_sect[strlen(display_sect)-1] = '\0';
                break;
            }
            else if (curr_command->contents[0] == '\0') {
                while (curr_sect->parent != NULL)
                    curr_sect = curr_sect->parent;
                strncpy(display_sect, curr_sect->name, BUFF_LEN);
                break;
            }
            else {
                bool shouldBreak = false;
                for (unsigned short i = 0; i < curr_sect->num_subsects; i++) {
                    if (strcmp(curr_sect->subsects[i]->name, curr_command->contents) == 0) {
                        curr_sect = curr_sect->subsects[i];
                        strcat(display_sect, "/");
                        strcat(display_sect, curr_sect->name);
                        shouldBreak = true;
                    }
                }
                if (shouldBreak) break;
            }

            char response[512] = { 0 };
            printf("Create new section '%s'? [y/n] ", curr_command->contents);
            scanf("%s", response);
            printf("%s", response);

            if (response[0] == 'y' || response[0] == 'Y') {
                printf("aa");
                sect_add_subsect(sect_new_sect(curr_command->contents), curr_sect);
                curr_sect = curr_sect->subsects[curr_sect->num_subsects-1];
                strcat(display_sect, "/");
                strcat(display_sect, curr_sect->name);
            }

            break;
        
        case NOTE:
            sect_add_note(curr_command->contents, curr_sect);
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
