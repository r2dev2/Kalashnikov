from subprocess import *
from threading import Thread
from time import sleep
from sys import argv

from onlineMultiplayerLib import *
from IO import io

def main() -> None:
    FICS = io("freechess.org", 5000)
    if len(argv) < 2 or argv[1] not in ["guestKA", "guestKB"]:
        print("Enter in either guestKA or guestKB as a commandline argument")
    client(FICS, argv[1], False)

def put(p: Popen, command: str) -> None:
    c = command + '\n'
    p.stdin.write(c.encode("UTF-8"))
    p.stdin.flush()

def get() -> str:
    f = open("move.txt", "rb+")
    hand = f.readlines()
    f.close()
    h = [b.decode() for i, b in enumerate(hand) if i != 0]
    newh = []
    for s in h:
        sl = slice(len(s))
        if s[-1] == '\n':
            sl = slice(len(s)-1)
        newh.append(s[sl])
    return '&'.join(newh)

if __name__ == "__main__":
    main()
