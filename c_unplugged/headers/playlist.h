#ifndef PLAYLIST_H
#define PLAYLIST_H
#define MAX_SONGS 50
#define MAX_LEN 100
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "library.h"
//playlist is basically queue

typedef struct song{
    int song_id;
    char song_name[MAX_LEN];
    char song_artist[MAX_LEN];
    int duration;
    struct song* next;
    struct song* prev;
}song;

typedef struct playlist{
    int playlist_id; //to figure out which album this is
    char playlist_name[MAX_LEN];
    song* head;
    int count;
}playlist;

//functions to make
playlist* create_playlist(int id);
song* search_in_playlist(const playlist* play, int song_id);
void add_song(playlist* play, int song_id, const char* song_name);
void remove_song(playlist* play, int song_id);
song* next_song(song* curr_song);
song* prev_song(song* curr_song);
void writePlaylistToFile(const playlist* play, const char* filename);

#endif
