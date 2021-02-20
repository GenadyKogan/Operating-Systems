

To run the program add run permission to "compile" file
then run ./compile which will compile the files and start the program.
to manually run (after compilation) run ./_executable

OR

compile maunally :
"gcc src/shell.c src/single_commands.c src/globals.c src/piped_commands.c  -o _executable"

compile is a bash script
compile content :
"
    #!/bin/bash
    clear

    gcc src/shell.c src/single_commands.c src/globals.c src/piped_commands.c  -o _executable
    ./_executable
"
