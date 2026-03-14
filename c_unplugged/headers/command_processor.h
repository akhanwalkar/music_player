
#ifndef COMMAND_PROCESSOR_H
#define COMMAND_PROCESSOR_H
#include "library.h"
#include "playlist.h"

void processCommands(const char* commandFile, playlist* play, SongLibrary* lib, const char* playlistFile);

#endif
