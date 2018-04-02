#/usr/bin/env python

import Protocol_pb2
import socket

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM, socket.IPPROTO_TCP)

sock.connect(('localhost', 9988))

# Send login
login = Protocol_pb2.Request(login=Protocol_pb2.Login(username="test"))
msg = login.SerializeToString()

sock.send(msg)

# TODO: Recv data

# Create table
createTable = Protocol_pb2.Request(createTable=Protocol_pb2.CreateTable(name="table_test", maxPlayers=6))
msg = createTable.SerializeToString()

sock.send(msg)