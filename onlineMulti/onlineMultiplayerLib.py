from sys import argv
from time import sleep
from threading import Thread

from IO import io

def main() -> None:
    FICS = io("freechess.org", 5000)
    if argv[1] == "host":
        host(FICS)
    elif argv[1] == "client" and len(argv) != 2:
        client(FICS, argv[2])
    else:
        print("Use mode 'host' or 'client'")
        print("If client, specify whether guestKA or guestKB")
        exit(1)

def host(server: io) -> None:
    server.login("guestKS")
    prev = server.receive_tell()
    print("Host Server has started up!")
    while 1==1:
        name, msg = server.receive_tell()
        if msg is None:
            sleep(1)
            continue
        server.tell(other_user(name), msg)

def client(server: io, name: str, chat: bool = True) -> None:
    server.login(name)
    prev = server.receive_tell()
    receive = Thread(target = client_receive, args = (server, chat))
    send = Thread(target = client_send, args = (server, "guestKS"))
    receive.start()
    send.start()
    receive.join()
    send.join()

def client_receive(server: io, chat: bool = True) -> None:
    server.receive_tell()
    print("Receiving has started.")
    while 1 == 1:
        name, msg = server.receive_tell()
        if msg is None:
            sleep(1)
            continue
        if "KA(U)" in msg or "KB(U)" in msg or "*" in msg:
            continue
        if chat:
            print(f"{name} sent you a message: {msg}")
        else:
            for card in msg.split('&'):
                print(toStrCard(card), flush = True)

def client_send(server: io, other):
    print("Sending has started.")
    while 1 == 1:
        msg = input('')
        if msg == "$QUIT":
            exit(0)
        print()
        server.tell(other, msg)

def other_user(uname: str) -> str:
    if uname == "guestKA":
        return "guestKB"
    return "guestKA"

def toStrCard(card: str) -> str:
    if "victor" in card:
        return card
    cardnum = int(card.split(',')[0][1:])
    cardsuit = int(card.split(',')[1][:-1])
    nstr = str(cardnum)
    cstr = ["Clubs", "Spades", "Hearts", "Diamonds"][cardsuit-1]
    switcher = {1: "Ace", 11: "Jack", 12: "Queen", 13: "King"}
    if cardnum in [1, 11, 12, 13]:
        nstr = switcher[cardnum]
    return f"{nstr} of {cstr}"

if __name__ == "__main__":
    main()