#include<stdio.h>
#include<stdlib.h> //for exit
#include<string.h>

#define PAGE_MAX 1483277 //#of lines of pages.txt

char** read_page_file(char *file_name){
    FILE* file = fopen(file_name, "r");
    if (file == NULL) {
        printf("Couldn't find file: %s\n", file_name);
        exit(1);
    }

    char** words = (char**)malloc(PAGE_MAX * sizeof(char*));
    int index = 0;
    while (1) {
        char buffer[4096];
        int id;
        int ret = fscanf(file, "%d\t%4095s\n", &id, buffer);
        if (ret == EOF) {
            fclose(file);
            break;
        } else {
            int length = strlen(buffer);
            if (length == 4095) {
                printf("Word is too long\n");
                exit(1);
            }

            char* word = (char*)malloc(length + 1);
            strcpy(word, buffer);
            assert(index < PAGE_MAX);
            words[index++] = word;
        }
    }
    return words;
}

//link_fileを読み，隣接配列を作る
int** read_link_file(char *file_name){
    FILE* file = fopen(file_name, "r");
    if(file == NULL){
        printf("Couldn't find file: %s\n", file_name);
        exit(1);
    }

    int id1, id2;
    int adjacency_matrix[PAGE_MAX][PAGE_MAX];

    while (1) {
        int ret = fscanf(file, "%d\t%d\n", &id1, &id2);
        if(ret == EOF){
            fclose(file);
            break;
        } else {

        }
    }
}
            



