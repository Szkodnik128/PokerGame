#/usr/bin/env python

from transport import Transport

import Protocol_pb2

import thread

HOST = "localhost"
PORT = 9988

class Client(object):

    def __init__(self):
        self.command_map = {
            'login': self.login,
            'create_table': self.create_table,
            'join_table': self.join_table,
            'leave_table': self.leave_table,
            'raise': self.raise_pot,
            'fold': self.fold,
            'call': self.call
        }

        self.transport = Transport(HOST, PORT)

    def run(self):
        thread.start_new_thread(self.recv_response, ())
        while True:
            command = raw_input('# ')
            try:
                handler = self.command_map[command]
                msg = handler()
                self.transport.send(msg)
            except KeyError:
                print("Wrong command")
            except ValueError:
                print("Wrong argument")

    def recv_response(self):
        data = b''

        while True:
            self.transport.recv(data, 2048)
            print("Recv data")


    def login(self):
        username = raw_input('Username = ')
        msg = Protocol_pb2.Request(login=Protocol_pb2.Login(username=username))

        return msg.SerializeToString()

    def create_table(self):
        table_name = raw_input('Table name = ')
        max_players = int(raw_input('Max players = '))

        msg = Protocol_pb2.Request(createTable=Protocol_pb2.CreateTable(name=table_name, maxPlayers=max_players))

        return msg.SerializeToString()

    def join_table(self):
        pass

    def leave_table(self):
        pass

    def raise_pot(self):
        pass

    def fold(self):
        pass

    def call(self):
        pass


client = Client()
client.run()