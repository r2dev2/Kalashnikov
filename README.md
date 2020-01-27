# Kalashnikov Text Based

# Build
To build on UNIX-based systems, execute

``make``


# Execution
To run, execute

``./bin/Kalashnikov``

# Multiplayer
Step 1: Start both clients and put a commandline argument of either: ``guestKA`` or ``guestKB``

On UNIX-based systems, execute:

``python3 onlineMulti/KalashnikovClient.py guestKA``

On Windows systems, execute:

``python onlineMulti/Kalashnikov.py guestKB``

Step 2: Start the host on one computer, this starts the game

On UNIX-based systems, execute:

``python3 onlineMulti/KalashnikovHost.py``

On Windows systems, execute:

``python onlineMulti/KalashnikovHost.py``

# Use
See https://github.com/r2dev2bb8/KalashnikovJava
