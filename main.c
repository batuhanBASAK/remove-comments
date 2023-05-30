#include <stdio.h>
#include <stdlib.h>
#include "arrl.h"



#define CHAR 10
#define FORWARD_SLASH 11
#define STAR 12


int get_char_type(char c)
{
    if (c == '/')
        return FORWARD_SLASH;
    else if (c == '*')
        return STAR;
    else
        return CHAR;
}


int multi_line_statement(arrl_t content, int i)
{
    while (i < content.size){
        int ct = get_char_type(content.s[i]);
        switch(ct){
            case STAR:
                ct = get_char_type(content.s[++i]);
                if (ct == FORWARD_SLASH)
                    return i;
            case FORWARD_SLASH:
            case CHAR:
            default:
                break;
        }
        if (i+2 > content.size){
            fprintf(stderr, "Error: The multi-line comment never closed!!!\n");
            exit(EXIT_FAILURE);
        }
        i++;
    }
    return i;
}


int forward_slash_state(arrl_t content, int i)
{
    int ct = get_char_type(content.s[++i]);
    switch(ct){
        case FORWARD_SLASH:
            // single-line comment
            // ignore the rest of line.
            while (i < content.size && content.s[i] != '\n')
                i++;
            i--;
            break;
        case STAR:
            // multi-line comment
            // ignore the content till the see the end marker '*/'.
            i = multi_line_statement(content, ++i);
            i--;
            break;
        case CHAR:
        default:
            // not comment.
            break;
    }
    return i;
}

void remove_comments(const char *filename)
{
    FILE *fp;
    if ((fp = fopen(filename, "r")) == NULL){
        fprintf(stderr, "File '%s' cannot be opened!\n", filename);
        return ;
    }
    arrl_t content;
    init_arrl(&content);
    char c;
    while (fscanf(fp, "%c", &c) == 1){
        add_char(&content, c);
    }
    fclose(fp);


    arrl_t modified_content;
    init_arrl(&modified_content);

    for (int i = 0; i < content.size; i++) {
        int ct = get_char_type(content.s[i]);
        switch(ct){
            case FORWARD_SLASH:
                i = forward_slash_state(content, i);
                break;
            case STAR:
            case CHAR:
                add_char(&modified_content, content.s[i]);
                break;
            default:
                break;
        }
    }
    dealloc_arrl(&content);

    fp = fopen(filename, "w");
    for (int i = 0; i < modified_content.size; i++)
        fprintf(fp, "%c", modified_content.s[i]);
    fclose(fp);
    dealloc_arrl(&modified_content);
}


int main(int argc, const char *argv[])
{
    if (argc < 2){
        fprintf(stderr, "File name must be entered!\n");
        exit(EXIT_FAILURE);
    }
    while (--argc > 0)
        remove_comments((const char*)*++argv);
}
