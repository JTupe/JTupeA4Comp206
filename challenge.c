#include <stdio.h>
#include <time.h>
#include <stdlib.h>
//overall TO DO
//gcc all of the programs, make sure all errors pass, create a room.html that works, test room.c, then test PLAY opens challenge.c, then test the transporter and success
//TO DO
//compile the c to cgi, push it on the server
//need to debug, host it on my server/Ander's server
//fetch the url of the challenge.cgi for the refresh
//test it by setting up what opens the program (aka PLAY command in room.c)

// When someone clicks on PLAY 
// hide the 4 buttons in the HTML page
// room.c controls the buttons - so tell the person responsible for it
int main(){

	//printf("<p>Welcome to this challenge! Please guess a number between 1 and 6</p>");
	char *data = getenv("QUERY_STRING");
	printf("%s", data);
	int number =4;
	//int number; // assume we fetched this from cgi by talking to your teammate
	srand((unsigned)time(NULL));   // should only be called once
	int random_number = rand() % 7; // rand%n means generate from 0 to n-1


	if(number >=1 && number <=6){

	
		if (random_number == number){
			//Modify resourses.txt. Change to .csv later
			int resources[3];
			FILE *resources_p = fopen("http://www.cs.mcgill.ca/~gzhang16/cgi-bin/resources.csv", "w+");
			if(resources_p == NULL) { perror("Error opening resource file"); return(-1); }
    		fscanf(resources_p, "%d,%d,%d", &resources[0], &resources[1], &resources[2]);
    		//I assumed I can make the game rules, which is gold +10. But in the assignment prof says 
    		//when they win, they get access to the hidden resources in the room, and they can take 5 of anything (2 gold 3 manna for example)
    		//resources[1]=     resources[1] +10;

    
    		printf("<p>this is the room's resources: %d manna and %d gold</p>", resources[0], resources[1]);
    		//FILE*website = fopen("room.html", r+);

    		printf("<form>"
    			"manna: "
    				"<input type=\"text\" name=\"requested_manna\"/>"
    			"gold:"
    				"<input type=\"text\" name=\"requested_gold\"/>"
    				"<input type=\"submit\" value=\"Ask for prize!\" /> "
    			"</form>");

    		//check how to access the two inputs using their names in cgi
    		//check two things: if two numbers sum up to 5, and if they are less or equal to my resources, if not, promt them to insert again
    		int requested_gold;
    		int requested_manna;
    		if (requested_gold + requested_manna > 5){
    			printf("%s", "<p>The total request units is beyond 5. Please insert a new combination of manna and gold.</p>");
    			return -1;
    		}
    		if (requested_gold > resources[1]){
    			printf("%s", "<p>The room does not have enough gold. Please insert a new combination of manna and gold.</p>");
    			return -1;
    		}
    		if(requested_manna > resources[0]){
    			printf("%s", "<p>The room does not have enough manna. Please insert a new combination of manna and gold.</p>");
    			return -1;
    		}
    		else{
    			// make changes and update resources file
				int inventory[3];
				FILE *inventory_p = fopen("http://www.cs.mcgill.ca/~gzhang16/cgi-bin/inventory.csv", "w+");
				if(inventory_p == NULL) { perror("Error opening inventory file"); return(-1); }
				fscanf(inventory_p, "%d,%d,%d", &inventory[0], &inventory[1], &inventory[2]);
				}
				inventory[0] = inventory[0]-requested_manna;
				inventory[1]= inventory[1]-requested_gold;

    		fprintf(inventory_p, "%d,%d,%d", inventory[0], inventory[1], inventory[2]);
    		fclose(inventory_p);
    		return 1;

    		//i print resources, then get input from the user, read the text, then update the scv

			//change their inventory in accordance
			/*int inventory[2];
			FILE *inventory_p=fopen("http://www.cs.mcgill.ca/~gzhang16/cgi-bin/inventory.csv");
			if(inventory_p == NULL) { perror("Error opening resource file"); return(-1); }
    
    		inventory[1]=     inventory[1] +10;
    		fprintf(inventory_p, "%d, %d,%d", resources[0], resources[1], resources[2]);
    		fclose(inventory_p);
    		*/


    		//Print to HTML directly
    		//TODO: Print HTML"Congrats"
			}
		}

		else{
			printf("<p>Wrong guess! Try again.</p>");
			printf("<meta http-equiv='refresh' content='0;url=http://www.cs.mcgill.XXXX/challenge.cgi'>");
		}
	
	}

	else {
		printf("<p>Invalid entry. Enter number between 1 and 6.</p>");
		printf("<meta http-equiv='refresh' content='0;url=http://www.cs.mcgill.XXXX/challenge.cgi'>");
		}
	
	return 0;
}




//html receives 1, it needs to print congrats, and show room resources
//if it receives 0, print play again
//Justine for opening and overwriting in csv, you need to use w+ instead of r+