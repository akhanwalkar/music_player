#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "playlist.h"

playlist* create_playlist(int id)
{
    playlist* play = (playlist*)malloc(sizeof(playlist));
    if (play == NULL)
    {
        exit(1);
    }
    play->playlist_id = id;
    play->head = NULL;
    play->count = 0;
    return play;
}

void display_playlist(const playlist* play)
{
    if (play->head == NULL)
    {
        printf("playlist %d-%s is empty\n", play->playlist_id, play->playlist_name);
        return;
    }
    song* temp = play->head;
    for (int i = 0; i < play->count; i++)
    {
        printf("%d-%s\n", temp->song_id, temp->song_name);
        temp = temp->next;
    }
}

song* search_in_playlist(const playlist* play, int song_id)
{
    if (play->head == NULL)
    {
        printf("playlist %d is empty\n", play->playlist_id);
        return NULL;
    }
    song* temp = play->head;
    for (int i = 0; i < play->count; i++)
    {
        if (temp->song_id == song_id) return temp;
        temp = temp->next;
    }
    return NULL;
}

void add_song(playlist* play, int song_id, const char* song_name)
{
    song* newsong = (song*)malloc(sizeof(song));
    if (newsong == NULL)
    {
        exit(1);
    }
    newsong->song_id = song_id;
    strcpy(newsong->song_name, song_name);

    if (play->head == NULL)
    {
        newsong->next = newsong;
        newsong->prev = newsong;
        play->head = newsong;
    }
    else
    {
        song* end = play->head->prev;
        end->next = newsong;
        newsong->prev = end;
        newsong->next = play->head;
        play->head->prev = newsong;
    }
    play->count++;
    return;
}

void remove_song(playlist* play, int song_id)
{
    if (play->head == NULL)
    {
        printf("Playlist is empty, cannot remove.\n");
        return;
    }
    song* temp = play->head;
    int flag = 0;
    for (int i = 0; i < play->count; i++)
    {
        if (temp->song_id == song_id)
        {
            flag = 1;
            break;
        }
        temp = temp->next;
    }
    if (flag == 0)
    {
        printf("Song %d not found in playlist.\n", song_id);
        return;
    }
    if (play->count == 1)
    {
        play->head = NULL;
    }
    else
    {
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        if (temp == play->head)
        {
            play->head = temp->next;
        }
    }
    free(temp);
    play->count--;
    return;
}

song* next_song(song* curr_song)
{
    if (curr_song)
    {
        return curr_song->next;
    }
    else
    {
        return NULL;
    }
}

song* prev_song(song* curr_song)
{
    if (curr_song)
    {
        return curr_song->prev;
    }
    else
    {
        return NULL;
    }
}

void writePlaylistToFile(const playlist* pl, const char* filename)
{
    FILE* file = fopen(filename, "w");
    if (!file) return;
    fprintf(file, "Playlist %d:\n", pl->playlist_id);
    if (!pl->head)
    {
        fprintf(file, "Empty playlist.\n");
    }
    else
    {
        song* temp = pl->head;
        for (int i = 0; i < pl->count; i++)
        {
            fprintf(file, "[%d] %s\n", temp->song_id, temp->song_name);
            temp = temp->next;
        }
    }
    fclose(file);
}