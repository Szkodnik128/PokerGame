#!/bin/bash

protoc -I=./protocol --cpp_out=./protocol Protocol.proto
protoc -I=./protocol --python_out=./client Protocol.proto