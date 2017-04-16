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

//JUSTINE'S COMMENTS
//I think you need to add EXIT as an option in the if-loop to leave the game!
//remember that you can only initialize ANY variables/open ANY file in the beginning of the code
//also C does not accept commments like "// //" this, it will not compile it. You MUST comment with "/* */"
//WHENEVER you print a page it must begin with these:
//printf("Content-Type:text/html\n\n");
//printf(<html> WHATEVER OTHER THINGS YOU WANT TO ADD </html>) your code must start with the <html> tag and end with the </html> tag
//I started adding it for you but I may have missed some

//TO THIS: room.c controls the buttons - so tell the person responsible for it
//RESPONSE: in my code I am simply reprinting your challenge.c file so any buttons you want to add are your responsbility!

// When someone clicks on PLAY 
// hide the 4 buttons in the HTML page - requires you to reprint the page (just copy and paste)
int main(){

	printf("Content-Type:text/html\n\n");
	printf("<html><p>Welcome to this challenge! Please guess a number between 1 and 6</p>");
	printf("<FORM ACTION=\"http://cs.mcgill.ca/~aturim/challenge.cgi\""
 			"METHOD=\"POST\">"
			"<DIV>Your number (between 1 and 6):<BR>"	
			"<INPUT NAME=\"number\" SIZE=\"6\" MAXLENGTH=\"10\"><BR>"
			"<INPUT TYPE=\"SUBMIT\" VALUE=\"Go\"></DIV>"
			"</FORM>");

	int requested_gold, requested_manna;
	int rmMan, rmGold, occ, playMan, playGold;
	FILE *resources_p;
	resources_p = fopen("../resources.csv", "w+");
	FILE *inventory_p;
	inventory_p = fopen("../inventory.csv", "w+");
	char *data = getenv("QUERY_STRING");
	printf("%s", data);
	// assume we fetched this from cgi by talking to your teammate
	srand((unsigned)time(NULL));
	int random_number = rand() % 7; // rand%n means generate from 0 to n-1

	printf("<FORM ACTION=\"http://cs.mcgill.ca/~aturim/challenge.cgi\""
	 		"METHOD=\"POST\">"
			"<INPUT TYPE=\"SUBMIT\" VALUE=\"Exit\"></DIV>"
			"</FORM>\"");
	
		char *len_ = getenv("CONTENT_LENGTH");
		int len = strtol (len_, NULL,20);

		char *postdata = malloc (len+1);

		if (!postdata){return -1;}
		fgets(postdata, len+1,stdin);
		free(postdata);
		int number = 2;		
		if(number >=1 && number <=6){

	
			if (random_number == number){
			
				if(resources_p == NULL) {
					printf("<head>There was an error reading the given input. Recall that only: DROP n, PLAY, EXIT or REFRESH are valid inputs.</head></html>"); return(-1); }
					fscanf(resources_p, "%d,[^,],%d,[^,],%d", &rmMan, &rmGold, &occ);
					printf("<p>Congratulations! You guessed right.</p></html>");
							
					//when they win, they get access to the hidden resources in the room, and they can take 5 of anything (2 gold 3 manna for example)
			
					printf("<p>this is the room's resources: %d manna and %d gold</p>", rmMan, rmGold);
			
					printf("<form>"
			       		   "manna: "
			       		   "<input type=\"text\" name=\"requested_manna\"/>"
			       		   "gold:"
			       		   "<input type=\"text\" name=\"requested_gold\"/>"
			       		   "<input type=\"submit\" value=\"Ask for prize!\" /> "
			               "</form></html>");
				
			//check how to access the two inputs using their names in cgi
			//check two things: if two numbers sum up to 5, and if they are less or equal to my resources, if not, promt them to insert again
				if (requested_gold + requested_manna > 5){
					printf("<p>The total request units is beyond 5. Please insert a new combination of manna and gold.</p></html>");
					//shouldn't you resend the form here?
					system("./challenge.cgi");
					return -1;
				}
			
				if (requested_gold > rmGold){
				printf("<p>The room does not have enough gold. Please insert a new combination of manna and gold.</p></html>");
				system("./challenge.cgi");
				//shouldn't you resend the form here?
				return -1;
				}
			
				if(requested_manna > rmMan){
				printf("<p>The room does not have enough manna. Please insert a new combination of manna and gold.</p></html>");
				system("./challenge.cgi");
				//shouldn't you resend the form here?
				return -1;
				}
			
				else{
				// make changes and update resources file
					if(inventory_p == NULL) {
					printf("<head>There was an error reading the given input. Recall that only: DROP n, PLAY, EXIT or REFRESH are valid inputs.</head></html>"); return(-1); }
					fscanf(inventory_p, "%d,[^,], %d", &playMan, &playGold);
					rmMan = rmMan+requested_manna;
					rmGold = rmGold+requested_gold;
					char comma = ',';
					//this is what I was telling you in the fb chat - you can have these fprintf statements at the very end!
					fprintf(resources_p, "%d,%c,%d,%c,%d", rmMan, comma, rmGold, comma, occ);
					//shouldn't you updated the player's inventory as well? If so, add the following:
					playMan = playMan-requested_manna;
					playGold = playGold-requested_gold;
					fprintf(inventory_p, "%d,%c,%d", playMan, comma, playGold);
					fclose(resources_p);
					fclose(inventory_p);
					return 1;
				}
			

			}
			else {
				printf("<p>Wrong guess! Try again.</p></html>");
				//printf("<meta http-equiv='refresh' content='0;url=http://www.cs.mcgill.XXXX/challenge.cgi'></html>");
				system("./challenge.cgi");
				return 0;
			}
		}
		else {
			printf("<p>Invalid entry. Enter number between 1 and 6.</p></html>");
			//printf("<meta http-equiv='refresh' content='0;url=http://www.cs.mcgill.XXXX/challenge.cgi'></html>");
			system("./challenge.cgi");
			return 0;
		}

return 0;

}





