from subprocess import *
from os import getcwd, remove
from platform import platform
from time import sleep

from KalashnikovClient import put, get
from onlineMultiplayerLib import other_user
from IO import io

def main() -> None:
    move = getcwd() + "/move.txt"
    Kalash = getcwd() + "/bin/Kalashnikov"
    if platform() == "Windows":
        move = getcwd() + "\move.txt"
        Kalash = getcwd() + "\\bin\Kalashnikov"
    with open(move, "w+") as fout:
        fout.write("Hello World")
    remove(move)
    kalashnikov = Popen(
        [Kalash, "nospace"],
        stdin = PIPE,
        stdout = PIPE,
        stderr = PIPE
    )
    FICS = io("freechess.org", 5000)
    host(FICS, kalashnikov)

def host(server: io, k: Popen) -> None:
    server.login("guestKS")
    prev = server.receive_tell()
    print("Host Server has started up!")
    turn = 0
    donestuff = True
    prev = ''
    currUser = "guestKA"
    while 1==1:
        name, msg = server.receive_tell()
        current = get()
        # if something comes from process
        if current != prev:
            if "victor" in current:
                print(current, flush = True)
                server.tell("guestKA", current)
                server.tell("guestKB", current)
                exit(0)
            print("Interacting with Kalashnikov process", flush = True)
            prev = current
            server.tell(currUser, current)
        # if something comes from server
        elif not (msg is None) and '*' not in msg:
            print(f"Message from {name}: {msg}", flush = True)
            put(k, msg)
            currUser = other_user(currUser)
        # if nothing happens
        else:
            sleep(.5)

if __name__ == "__main__":
    main()