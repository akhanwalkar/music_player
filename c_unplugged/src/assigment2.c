#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library.h"
#include "playlist.h"
#include "command_processor.h"

int main()
{
    SongLibrary* lib = createLibrary();

    if (loadLibraryFromFile(lib, "songfile.txt") != 0) {
        printf("Failed to load song library.\n");
        return 1;
    }

    playlist* pl = create_playlist(101);

    song* curr_song = NULL;

    FILE* logFile = fopen("command.txt", "w");

    if (!logFile)
    {
        printf("Failed to open command log file.\n");
        return 1;
    }

    int choice, index;

    while (1)
    {
        printf("\n--- MENU ---\n");
        printf("1. Add Song\n");
        printf("2. Remove Song\n");
        printf("3. Next Song\n");
        printf("4. Previous Song\n");
        printf("5. Show Playlist\n");
        printf("6. Browse Library\n");
        printf("7. Command Log\n");
        printf("8. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            printf("Enter song index to add: ");
            scanf("%d", &index);
            const char* name = getSongNameByIndex(lib, index);
            if (name)
            {
                add_song(pl, index, name);
                fprintf(logFile, "ADD %d\n", index);
                if (!curr_song) curr_song = pl->head;
            }
            else
            {
                printf("Song not found.\n");
            }
        }

        else if (choice == 2)
        {
            printf("Enter song index to remove: ");
            scanf("%d", &index);
            if (curr_song && curr_song->song_id == index) {
                curr_song = (pl->count > 1) ? curr_song->next : NULL;
            }
            remove_song(pl, index);
            fprintf(logFile, "REMOVE %d\n", index);
        }

        else if (choice == 3)
        {
            if (curr_song)
            {
                curr_song = next_song(curr_song);
                printf("Now playing: %s\n", curr_song->song_name);
                fprintf(logFile, "NEXT\n");
            }
            else
            {
                printf("Playlist is empty.\n");
            }
        }

        else if (choice == 4)
        {
            if (curr_song)
            {
                curr_song = prev_song(curr_song);
                printf("Now playing: %s\n", curr_song->song_name);
                fprintf(logFile, "PREV\n");
            }
            else
            {
                printf("Playlist is empty.\n");
            }
        }

        else if (choice == 5)
        {
            writePlaylistToFile(pl, "playlist.txt");
            printf("Playlist written to playlist.txt\n");
            fprintf(logFile, "SHOW\n");
        }

        else if (choice == 6)
        {
            browseLibrary(lib);
        }

        else if (choice == 7)
        {
            printf("\n--- Command Log ---\n");
            fclose(logFile);
            FILE* readLog = fopen("command.txt", "r");
            if (!readLog)
            {
                printf("Failed to open command log.\n");
            }
            else
            {
                char line[256];
                while (fgets(line, sizeof(line), readLog))
                {
                    printf("%s", line);
                }
                fclose(readLog);
            }
            logFile = fopen("command.txt", "a");
            fprintf(logFile, "SHOW_LOG\n");
        }

        else if (choice == 8)
        {
            fprintf(logFile, "EXIT\n");
            break;
        }

        else
        {
            printf("Invalid choice.\n");
        }
    }
    fclose(logFile);
    freeLibrary(lib);
    free(pl);
    return 0;
}