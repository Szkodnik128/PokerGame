#!/usr/bin/env python

from transport import Transport
import Protocol_pb2

import thread
import os


HOST = "localhost"
PORT = 9988

CLUBS = u"\u2663"
HEARTS = u"\033[91m\u2665\033[0m"
DIAMONDS = u"\033[91m\u2666\033[0m"
SPADES = u"\u2660"

class Client(object):

    def __init__(self):
        self.command_map = {
            'login': self.login,
            'create': self.create,
            'join': self.join,
            'leave': self.leave,
            'raise': self.raise_bet,
            'fold': self.fold,
            'call': self.call,
        }

        self.card_suit_map = {
            1: SPADES,
            2: HEARTS,
            3: DIAMONDS,
            4: CLUBS,
        }

        self.card_value_map = {
            2: '2',
            3: '3',
            4: '4',
            5: '5',
            6: '6',
            7: '7',
            8: '8',
            9: '9',
            10: '10',
            11: 'J',
            12: 'Q',
            13: 'K',
            14: 'A',
        }

        self.round_status_map = {
            0: 'Unknown',
            1: 'Begining',
            2: 'Preflop',
            3: 'Flop',
            4: 'Turn',
            5: 'River',
            6: 'End',
        }

        self.table_status_map = {
            0: 'Unknown',
            1: 'Waiting for players',
            2: 'Game in progress',
            3: 'Game ended',
        }

        self.transport = Transport(HOST, PORT)
        self.working_flag = False

    def run(self):
        self.working_flag = True
        thread.start_new_thread(self.recv_response, ())

        while self.working_flag:
            command = raw_input('# ')
            if command == 'help' or command == '-h' or command == '--help' or command == 'h' or command == '?':
                self.print_commands()
            elif command == 'quit' or command == 'q':
                self.working_flag = False
            elif command == '':
                continue
            else:
                try:
                    handler = self.command_map[command]
                    msg = handler()
                    self.transport.send(msg)
                except KeyError:
                    print("Wrong command")
                except ValueError:
                    print("Wrong argument")

    def print_commands(self):
        for key, value in self.command_map.items():
            print(key)

    def recv_response(self):
        while self.working_flag:
            data = self.transport.recv(2048)
            response = Protocol_pb2.Response()
            response.ParseFromString(data)

            print('')
            which_one_of = response.WhichOneof("payload")
            if which_one_of == "lobbyView":
                self.recv_lobby_view(response.lobbyView)
            elif which_one_of == "tableView":
                self.recv_table_view(response.tableView)
            else:
                print('Error: {}'.format(response.error))

    def login(self):
        username = raw_input('Username = ')
        msg = Protocol_pb2.Request(login=Protocol_pb2.Login(username=username))

        return msg.SerializeToString()

    def create(self):
        table_name = raw_input('Table name = ')
        max_players = int(raw_input('Max players = '))

        msg = Protocol_pb2.Request(createTable=Protocol_pb2.CreateTable(name=table_name, maxPlayers=max_players))

        return msg.SerializeToString()

    def join(self):
        table_name = raw_input('Table name = ')

        msg = Protocol_pb2.Request(joinTable=Protocol_pb2.JoinTable(name=table_name))

        return msg.SerializeToString()

    def leave(self):
        pass

    def raise_bet(self):
        chips = int(raw_input('Chips = '))

        msg = Protocol_pb2.Request(raise_bet=Protocol_pb2.Raise(chips=chips))

        return msg.SerializeToString()

    def fold(self):
        msg = Protocol_pb2.Request(fold=Protocol_pb2.Fold())

        return msg.SerializeToString()

    def call(self):
        msg = Protocol_pb2.Request(call=Protocol_pb2.Call())

        return msg.SerializeToString()

    def recv_lobby_view(self, msg):
        for x in range(5):
            print('')
        print('--------------- TABLES ---------------')
        for table in msg.tables:
            print(table.name)
            print("    players: {}/{}".format(table.players, table.maxPlayers))
            print("")
        print('--------------------------------------')

    def recv_table_view(self, msg):
        for x in range(5):
            print('')
        print('---------------- INFO ----------------')
        print('status: {}'.format(self.table_status_map[msg.tableStatus]))
        print('round: {}'.format(self.round_status_map[msg.roundStatus]))
        print('pot: {}'.format(msg.pot))
        print('--------------- CARDS ----------------')
        for card in msg.cards:
            print("    " + self.card_value_map[card.cardValue] + self.card_suit_map[card.cardSuit])

        print('-------------- PLAYERS ---------------')
        for player in msg.players:
            print(player.name)
            for card in player.hand:
                print("    " + self.card_value_map[card.cardValue] + self.card_suit_map[card.cardSuit])
            print("    chips: {}".format(player.chips))
            print("    bet: {}".format(player.bet))
            if player.turn:
                print("    dealer")
            if msg.tableStatus == 2 and not player.inGame:
                print("    folded")
            if player.turn:
                print("    turn")
            print('--------------------------------------')


client = Client()
client.run()
