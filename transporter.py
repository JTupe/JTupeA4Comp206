import cgi
import csv
import urllib2

#refresh the room URL they come from 

#First receive the inventory and url of the room they come from
#check the form I receive from cgi, see if there are two URLs, and what are they called 
form = cgi.FieldStorage()
url = form["URL"]
 #check with room.c what the URL we just came from is called
inventory = form["inventory"]
gold = int(inventory.split(',')[0])
manna = int(inventory.split(',')[1]) - 1
   

#url_to= form["URLNorth"] #check what the URL_to is called
#url_to =myural need to get


#updates the new valus of gold and manna to the inventory.csv
with open('inventory.csv', 'w') as inventory_file:
	inventory_file.write("{0},{1}".format(gold,manna))

#reads the resouces.csv, and store the values 
with open('resources.csv' , 'r') as resources_file:
	resources_reader = csv.reader(resources_file)
    for row in resources_reader:
    	resources_gold = int(row[0])
    	resources_manna = int(row[1])
    	is_occupied = int(row[2])

#checks if the room is occupied
 if is_occupied:
 	data= urllib.urlencode({'CMD':'REFRESH'
 							'inventory': "{0},{1}".format(gold,manna+1) })
 	urllib2.urlopen("{0}data?{1}".format(url,data))

#if it's empty, pass the player, update resources.csv, call room.c and success.py
else:
	is_occupied= 1
	with open('resources.csv', 'w') as resources_file:
	resources_file.write("{0},{1},{2}".format(resources_gold,resources_manna,is_occupied))
	data= urllib.urlencode({'CMD':'REFRESH'})
 	urllib2.urlopen("{0}data?{1}".format(url,data))
 	urllib2.urlopen("{0}success.py".format(url))
	#TO DO: ask Justine how to call room.cgi and send REFRESH
	#how to pass data to her URL, aka what to write instead of CMD an




	#HTML needs to have a page where when player try to exit our room trying to go to another room, if not successful, needs 
	#to tell the player not successful, and come back 
	#make sure room.c is generating the initial page with the picture and the directions