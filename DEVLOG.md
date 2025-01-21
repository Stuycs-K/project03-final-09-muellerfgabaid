# Dev Log:

This document must be updated daily by EACH group member.

## Flint Mueller

### 2025-01-06 - Added project files
Updated Makefile, README.md, and DEVLOG.md
40 minutes

### 2024-01-08 - Game protocol
Rename parseData.* to parse_data.*
Create outline for protocol
40 minutes

### 2024-01-09 - Subservers
Create outline + branch for bracket subservers
40 minutes

### 2024-01-10 - Subservers
Write fork_subserver function
Still waiting for game implementation before merging
40 minutes

### 2024-01-13 - Merge subserver and link with game
Merged subserver branch to main
Helped Daniel get the code running
40 minutes

### 2024-01-14 - Started server testing
Fixed some include bugs
Started testing server and need to find a solution for reading
40 minutes

### 2024-01-15 - Started fixing server
Server can't both open WKP and read from input at same time
Select can't be used
40 minutes

### 2024-01-16 - Used select for stdin and clients
Implemented select for communication with stdin and players
40 minutes

### 2024-01-17 - Fixed bracketing and added status prints
Bracket works with multiple players
Prints when players start games and win/lose
40 minutes

### 2024-01-19 - Multiple enter usernames
Multiple clients connected can enter usernames at the same time
The server used to block when one client was entering their username
80 minutes


## Daniel Gabai

### 2025-01-06 - Setting up the project
Transfered files from fork server lab
Set up server/ client communication for a turn based game
Fixed bugs
Created the battleship board and ship data arrays
Total Time: 2hrs

### 2025-01-07 - Worked on sending and parsing data
Created files for parsing functions
Updated server to send data in relavent format
Updated client to process the data sent from server
Worked on protocol for server/ client communication
Total time: 2hrs

### 2025-01-09 - Changed game
Changed logic into rock/paper/scissors (plan to change to battleship once server is working)
Worked on subserver / main server communication
Updated parse_data.h for new game
Total time: 1hr

### 2025-01-10 - Server side logic for game
Wrote functions to handle the logic for the game on the server
Also communicates with clients
Time: 40 mins

### 2025-01-13 - Client side logic for game
Wrote functions to handle game logic on the client
Updated makefile for new targets
Updated client to use the new code
Time: 40 mins

### 2025-01-14 - Created Testing Server and Bug Fixing
Created a seperate testing server to test game functionality
Updated makefile for this new server
Fixed bugs in game.c 
Time: 40 mins

### 2025-01-15 - Bug fixing on server
Fixed an issue where if no clients connect and you try and continue, the server fork bombs
Tried to fix server connectivity issues on test_server
Time: 40 mins

### 2025-01-16 - Testing game logic
Fixed testing server so it runs on 2 client connections
Found error where server side logic reads bad file descriptors
Worked on fix by correcting the to and from client file descriptors; still not working
-Update: Fixed the problem: the from_client file descriptor was being closed too early
Updated game functions to use structs
Time: 1.5hrs

### 2025-01-17 - Added usernames and fixed bugs; Made clients reconnect
Wrote function to get user input for each client's username
Fixed bug where subserver incorrectly writes client data, due to errors in pointer math
Wrote reconnect function that makes the winning client stay open for the new connection
Updated server and client logic to use the new reconnect feature
Time: 1.5hrs

### 2025-01-20 - Final Bug Fixes
Fixed issue where invalid usernames would create segfaults
Fixed issue where if both clients typed scissors then it would not result in a tie
General testing of code
Time: 35mins
