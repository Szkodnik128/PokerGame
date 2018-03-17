#!/bin/bash

protoc -I=./protocol --cpp_out=./protocol protocol.proto
protoc -I=./protocol --python_out=./client protocol.proto