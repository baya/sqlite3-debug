#!/bin/bash

gcc sqlite3.c -lpthread -ldl -fPIC -shared -o libsqlite3.so

gcc $1 -L. -lsqlite3