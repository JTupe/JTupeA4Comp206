#include <stdio.h>
#include <time.h>
#include <stdlib.h>

srand(time(NULL));   // should only be called once
int r = rand(); 

// When someone clicks on PLAY 
// hide the 4 buttons in the HTML page
// room.c controls the buttons - so tell the person responsible for it
int main(){
	//printf("<p>Welcome to this challenge! Please guess a number between 1 and 6</p>");
	
	void game(int number)
	//int number; // assume we fetched this from cgi by talking to your teammate
	if(number >=1 && number <=6){
		srand(time(NULL));   // should only be called once
		int random_number = rand() % (6 +1 - 1) + 1
		if (random_number == number){
			//Modify resourses.txt. Change to .csv later
			int resources[3];
			FILE *resources_p;
			if(resourses_p == NULL) { perror("Error opening resource file"); return(-1); }
    		fscanf(resourses_p, "%d,%[^,],%d,%[^,],%d", &resources[0], &resources[1], &resources[2]);
    		resources[1]=     resources[1] +10;
    		char comma = ",";
    		fprintf(resourses_p, "%d, %c, %d, %c,%d", resources[0], comma, resources[1], comma, resources[2]);
    		fclose(resourses_p);
    		

			//Modify inventory.txt. Change to .csv later
			//need to change
			int inventory[2];
			FILE *resources_p;
			if(resourses_p == NULL) { perror("Error opening resource file"); return(-1); }
    		fscanf(resourses_p, "%d,%[^,],%d,%[^,],%d", &resources[0], &resources[1], &resources[2]);
    		resources[1]=     resources[1] +10;
    		char comma = ",";
    		fprintf(resourses_p, "%d, %c, %d, %c,%d", resources[0], comma, resources[1], comma, resources[2]);
    		fclose(resourses_p);

    		//TODO: Print HTML"Congrats"
		}
		else{
			//Return HTML "Please try again";
		}


	}
	else 
		printf("Invalid entry\n");
		exit(-1);
}



//html receives 1, it needs to print congrats, and show room resources
//html also needs to print the game rules, everytime the player wins, he/she gets 10 gold, loses nothing if lose
//if it receives 0, print play again
//Justine for opening and overwriting in csv, you need to use w+ instead of r+