from subprocess import *
from os import getcwd
from threading import Thread
from time import sleep

def main():
    k = Popen(
            [getcwd() + "/Kalashnikov", "nospace"],
            stdin = PIPE,
            stdout = PIPE,
            stderr = PIPE
            )

    read = Thread(target = readInput, args = ())
    write = Thread(target = giveInput, args = (k,))
    
    read.start()
    sleep(.5)
    write.start()
    
    read.join()
    write.join()

def readInput():
    prevhand = ''
    while 1==1:
        f = open("move.txt", "rb")
        hand = f.readlines()
        f.close()
        if hand != prevhand and len(hand) != 0:
            h = [b.decode() for i, b in enumerate(hand) if i != 0]
            newh = []
            for s in h:
                sl = slice(len(s))
                if s[-1] == '\n':
                    sl = slice(len(s)-1)
                newh.append(s[sl])
            print('&'.join(newh))
            prevhand = hand

def giveInput(p):
    while 1==1:
        command = input("Card? ") + '\n'
        if command == "quit\n":
            exit(0)
        p.stdin.write(command.encode("UTF-8"))
        p.stdin.flush()
        sleep(1)

if __name__ == "__main__":
    main()
