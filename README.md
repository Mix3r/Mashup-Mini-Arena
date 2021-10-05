# Mashup Mini Arena gamecode
Contains source code for all three qvm modules, based on both OpenArena and ioQuake 3 (cgame.qvm  qagame.qvm  ui.qvm)

## Description ##
I'm a new to GitHub, i don't know what to do next.

## Building ##
Use corresponding .cmd files in "windows_scripts" folder to compile each of three qvm modules. For example "windows_compile_cgame.bat" compiles cgame.qvm and places it into windows/basema/vm folder

## Extracting entities ##
It is possible to extract entity definition for use with GtkRadiant and NetRadiant like this:

```
cd code/game
./extract_entities.sh > openarena.def
```

## Links ##
D

## License ##

This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.
