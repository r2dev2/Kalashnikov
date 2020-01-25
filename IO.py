import telnetlib
import time

class io:
    def __init__(self, host, port, mode = 'p'):
        self.tel = telnetlib.Telnet(host, port)
        self.cluttercount = 0
        self.movest = ""
        self.mode = mode

    def close(self):
        self.tel.close()

    def read_line(self):
        return self.tel.read_until(b"\n").decode("utf-8")

    def scrap_row(self, start, move):
        row = ""
        for i in range(start, start + 8):
            row += move[i]
        return row

    def write(self, msg):
        self.tel.write("{msg}\r\n".format(msg=msg).encode())

    def tell(self, whom: str, what: str):
        self.tel.write("tell {whom} {what}\r\n".format(whom=whom, what=what).encode())

    def receive_tell(self) -> (str, str):
        back = self.tel.read_very_eager().decode("utf-8").split("fics%")
        for s in back:
            if "(U)" in s:
                return s[2:9], s[24:-2]
        return None, None

    def seek(self):
        str1 = b"getgame\r\n"
        self.tel.write(str1)
    
    def move(self, m):
        self.tel.write(m.encode() + b"\r\n")


    def startOb(self):
        self.tel.write(b"ob GuestSTOCBOT\r\n")

    def startGame(self):
        if self.tel.read_all().decode("utf-8")[-1:] == "0":
            return True
        return False

    def getShift(self, move):
        shift = 0
        if move[79] == "-":
            shift += 1
        return shift

    #All initializing activities
    def login(self, user: str):
        self.tel.read_until(b"login: ")
        self.tel.write(user.encode('ascii') + b"\n")
        self.tel.read_until(b"Press return to enter the server")
        self.tel.write(b"\r\n")
        self.tel.write(b"set style 12\r\n")
        self.tel.write(b"set seek 0\r\n")
        if self.mode == "ob":
            self.startOb()
