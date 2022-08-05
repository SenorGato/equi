#!/bin/sh
# if you don't have the script's cwd set, you get XML errors
export WINEPREFIX=~/.wine/
cd /home/senoraraton/.wine/drive_c/Program\ Files/Sony/EverQuest
# The client will spew a lot of errors, especially every time
# you target a mob, hence the stdout/stderr redirect.
# You probably want to leave off the 2>/dev/null until you're satisfied
# everything is working.
wine eqgame.exe patchme  

