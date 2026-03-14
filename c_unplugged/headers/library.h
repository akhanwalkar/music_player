
#ifndef LIBRARY_H
#define LIBRARY_H

#define MAX_LEN 100
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 100

typedef struct LibraryNode {
    int song_id;
    char song_name[MAX_LEN];
    struct LibraryNode* next;
} LibraryNode;

typedef struct {
    LibraryNode* head;
    int count;
} SongLibrary;

SongLibrary* createLibrary();
void browseLibrary(const SongLibrary* lib);
const char* getSongNameByIndex(const SongLibrary* lib, int songIndex);
void freeLibrary(SongLibrary* lib);
int loadLibraryFromFile(SongLibrary* lib, const char* filename);

#endif
