import socket


class Transport(object):

    def __init__(self, host, port):
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM, socket.IPPROTO_TCP)
        try:
            self.sock.connect((host, port))
        except socket.error:
            print("Cannot connect to host")
            exit(-1)

    def send(self, data):
        self.sock.send(data)

    def recv(self, length):
        data = self.sock.recv(length)
        return data
