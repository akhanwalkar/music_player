#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "library.h"

SongLibrary* createLibrary() {
    SongLibrary* lib = (SongLibrary*)malloc(sizeof(SongLibrary));
    if (!lib) return NULL;
    lib->head = NULL;
    lib->count = 0;
    return lib;
}

void browseLibrary(const SongLibrary* lib) {
    if (!lib->head) {
        printf("Song library is empty.\n");
        return;
    }
    printf("Song Library contains %d songs:\n", lib->count);
    LibraryNode* temp = lib->head;
    while (temp) {
        printf("[%d] %s\n", temp->song_id, temp->song_name);
        temp = temp->next;
    }
}

const char* getSongNameByIndex(const SongLibrary* lib, int song_id) {
    LibraryNode* temp = lib->head;
    while (temp) {
        if (temp->song_id == song_id) return temp->song_name;
        temp = temp->next;
    }
    return NULL; // Not found
}

void freeLibrary(SongLibrary* lib) {
    LibraryNode* temp = lib->head;
    while (temp) {
        LibraryNode* next = temp->next;
        free(temp);
        temp = next;
    }
    free(lib);
}

int loadLibraryFromFile(SongLibrary* lib, const char* filename) 
{
    FILE* file = fopen(filename, "r");
    if (!file) return -1;

    int index;
    char name[MAX_LEN];

    while (fscanf(file, "%d %[^\n]", &index, name) == 2) {
        LibraryNode* node = (LibraryNode*)malloc(sizeof(LibraryNode));
        node->song_id = index;
        strcpy(node->song_name, name);
        node->next = lib->head;
        lib->head = node;
        lib->count++;
    }

    fclose(file);
    return 0;
}
