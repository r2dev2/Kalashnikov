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

def client(server: io, name: str) -> None:
    server.login(name)
    prev = server.receive_tell()
    receive = Thread(target = client_receive, args = (server,))
    send = Thread(target = client_send, args = (server, "guestKS"))
    receive.start()
    send.start()
    receive.join()
    send.join()

def client_receive(server: io) -> None:
    server.receive_tell()
    print("Receiving has started.")
    while 1 == 1:
        name, msg = server.receive_tell()
        if msg is None:
            sleep(1)
            continue
        if "KA(U)" in msg or "KB(U)" in msg:
            continue
        print(f"{name} sent you a message: {msg}")

def client_send(server: io, other):
    print("Sending has started.")
    while 1 == 1:
        msg = input('')
        if msg == "$QUIT":
            exit(0)
        server.tell(other, msg)

def other_user(uname: str) -> str:
    if uname == "guestKA":
        return "guestKB"
    return "guestKA"

if __name__ == "__main__":
    main()