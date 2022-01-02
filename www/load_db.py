#!/usr/bin/env python3

import sqlite3
import os, stat

table = \
  "create table coordinates" + \
  "(" + \
  "  coordinate_id integer primary key autoincrement," + \
  "  name char(16)," + \
  "  r0 char(80)," + \
  "  r1 char(80)," + \
  "  i0 char(80)," + \
  "  i1 char(80)," + \
  "  completed int," + \
  "  ip_address char(16)," + \
  "  timestamp integer," + \
  "  end_time integer" + \
  ");"

count = 0

db = sqlite3.connect("coordinates.db")
fp = open("coordinates.txt", "r")

#cursor = db.cursor()
#cursor.execute(table)
db.execute(table)

while True:
  line = fp.readline()
  if not line: break

  name = line.split(".")[0].strip()
  r0 = fp.readline().replace(" ","").strip()
  r1 = fp.readline().replace(" ","").strip()
  i0 = fp.readline().replace(" ","").strip()
  i1 = fp.readline().replace(" ","").strip()

  #print(name)
  #print(r0)
  #print(r1)
  #print(i0)
  #print(i1)

  query = \
    "insert into coordinates " + \
    "(name, r0, r1, i0, i1, completed, timestamp, end_time) values (" + \
    "'" + name + "', " + \
    "'" + r0 + "', " + \
    "'" + r1 + "', " + \
    "'" + i0 + "', " + \
    "'" + i1 + "', " + \
    "0, 0, 0)"

  db.execute(query)
  db.commit()

  count += 1

  # This if-statement is To help with debugging a small group of pictures.
  if count == 4: break

fp.close()
db.close()

os.chmod("coordinates.db", \
  stat.S_IRUSR | stat.S_IWUSR | \
  stat.S_IRGRP | stat.S_IWGRP | \
  stat.S_IROTH | stat.S_IWOTH)

