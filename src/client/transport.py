import socket


class Transport(object):

    def __init__(self, host, port):
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM, socket.IPPROTO_TCP)
        self.sock.connect((host, port))

    def send(self, data):
        self.sock.send(data)

    def recv(self, data, length):
        data = self.sock.recv(length)
