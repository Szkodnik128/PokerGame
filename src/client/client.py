#/usr/bin/env python

import protocol_pb2
import socket

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM, socket.IPPROTO_TCP)

sock.connect(('localhost', 9988))

# Send login
login = protocol_pb2.Request(login=protocol_pb2.MsgLogin(username="test"))
msg = login.SerializeToString()

sock.send(msg)
