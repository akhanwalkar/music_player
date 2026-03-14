#include "command_processor.h"

void processCommands(const char* commands, playlist* play, SongLibrary* lib, const char* playlistFile) {
    FILE* cmdFile = fopen(commands, "r");
    if (!cmdFile) {
        printf("Error opening command file.\n");
        return;
    }

    char command[50];
    int index;
    song* curr_song = play->head;

    while (fscanf(cmdFile, "%s", command) != EOF) {
        if (strcmp(command, "ADD") == 0)
        {
            fscanf(cmdFile, "%d", &index);
            const char* name = getSongNameByIndex(lib, index);
            if (name) add_song(play, index, name);
        }
        else if (strcmp(command, "REMOVE") == 0)
        {
            fscanf(cmdFile, "%d", &index);
            if (curr_song && curr_song->song_id == index) {
                curr_song = (play->count > 1) ? curr_song->next : NULL;
            }
            remove_song(play, index);
        }
        else if (strcmp(command, "NEXT") == 0)
        {
            if (curr_song) curr_song = next_song(curr_song);
        }
        else if (strcmp(command, "PREV") == 0)
        {
            if (curr_song) curr_song = prev_song(curr_song);
        }
        else if (strcmp(command, "SHOW") == 0)
        {
            writePlaylistToFile(play, playlistFile);
        }
    }
    fclose(cmdFile);
}