import cgi
import csv

#check the form I receive from cgi, see if there are two URLs, and what are they called 
form = cgi.FieldStorage()
url = form["URL"] #check with room.c what the URL we just came from is called
inventory = form["Inventory"] #inventory from the room.c
is_occupied = 0
url_to= form["URLNorth"] #check what the URL_to is called

with open('inventory.csv', 'r') as file:
	reader = csv.reader(file)
	for row in reader:
		is_occupied = row[



with open('example.csv', 'r+') as example:

	reader                                                                                                     
	#get the csv, and have access to inventory (read from url), 