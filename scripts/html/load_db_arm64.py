#!/usr/bin/env python3

import sqlite3
import os, stat

# May 20, 2024: This is a copy of load_db.py which has been updated for
# the ARM64 version of this project. There is an extra rotation value
# for the images, the output filename might be different, and the text
# file that contains all the coordinates to render is in a different
# format. 

table = \
  "create table coordinates" + \
  "(" + \
  "  coordinate_id integer primary key autoincrement," + \
  "  name char(16)," + \
  "  r0 char(80)," + \
  "  r1 char(80)," + \
  "  i0 char(80)," + \
  "  i1 char(80)," + \
  "  rotation int," + \
  "  completed int," + \
  "  ip_address char(16)," + \
  "  timestamp integer," + \
  "  end_time integer" + \
  ");"

count = 0

db = sqlite3.connect("coordinates.db")
fp = open("../../arm64/coordinates.txt", "r")

db.execute(table)

for line in fp:
  tokens = line.strip().split(",")

  frame_number = int(tokens[0])
  name = "frame%05d.png" % (frame_number)
  r0 = tokens[1]
  r1 = tokens[2]
  i0 = tokens[3]
  i1 = tokens[4]
  rotation = tokens[5]

  #print(name)
  #print(r0)
  #print(r1)
  #print(i0)
  #print(i1)
  #print(rotation)

  query = \
    "insert into coordinates " + \
    "(name, r0, r1, i0, i1, rotation, completed, timestamp, end_time) values (" + \
    "'" + name + "', " + \
    "'" + r0 + "', " + \
    "'" + r1 + "', " + \
    "'" + i0 + "', " + \
    "'" + i1 + "', " + \
    "'" + rotation + "', " + \
    "0, 0, 0)"

  db.execute(query)
  db.commit()

  count += 1

  #print(query)
  #print(count)

  # This if-statement is To help with debugging a small group of pictures.
  #if count == 32: break

fp.close()
db.close()

os.chmod("coordinates.db", \
  stat.S_IRUSR | stat.S_IWUSR | \
  stat.S_IRGRP | stat.S_IWGRP | \
  stat.S_IROTH | stat.S_IWOTH)

