#!/usr/bin/python

import csv
import os

with open('resources.csv', 'rb') as csvfile:
    reader = csv.reader(csvfile)
    for row in reader:
        manna  = row[0]
        gold = row[1]

os.remove("resources.csv")

with open('resources.csv', 'wb') as csvfile:
    csvfile.write(('{0},{1},0').format(manna,gold))
