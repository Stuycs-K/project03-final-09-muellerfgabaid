# Final Project Proposal

## Group Members:

Flint Mueller, Daniel Gabai
       
# Intentions:

Terminal based battleship game in bracket style tournaments
    
# Intended usage:

Players will connect to a game server which will host the tournament. Once started, they will be presented with a 10x10 coordinate grid that will be used to play. They will then set up their ships via a selection process. A ship shape will be printed in the terminal and the user will be able to choose the coordinates of where they want it placed. All user input is done through the terminal by typing out coordinates (ex: b4) which will correspond to spaces on the board. This is how the user will select where to shoot.
  
# Technical Details:

Allocating memory for boards
Processes - server forks per game with a main server for tournament
Protocol for server-client communication (pipes / sockets, processes, signals)
Clients send moves to server (after validation)

Maybe:
Semaphore to determine whose turn it is
The board is shared to clients via shared memory

2d array to contain ships
2d array to contain map
    
# Intended pacing:

Responsibilities:
Daniel:
Create basic game design
Setup forking server
Setup server-side logic to handle inputs
Set up server and subserver communication
Flint:
Setup project and files
Set up subserver and client communication
Implement bracket system via server
Switch from pipes to sockets

Timeline:
Setup project and files - Jan 6
Create basic game design (board, ships, user input)  - Jan 7
Setup forking server - Jan 7
Set up subserver and client communication - Jan 8
Create server-side logic to handle inputs - Jan 11
Set up server and subserver communication - Jan 12
