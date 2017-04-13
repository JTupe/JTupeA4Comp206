#include<stdlib.h>
#include<stdio.h>

// include the methods of the file //
void updateInventory(int);
void updateResources(int);
void exitUpdateInventory(void);

main(char inputCommand[]) {
	char input[200], command[200];
	char inventoryManna[200], inventoryGold[200], goldDropArray[200];
	int len = atoi(getenv("CONTENT_LENGTH"));
	char c;
	
	// to read how many resources are in the room
	int rmMan, rmGold, occ;
	FILE *fileResources = fopen("resources.csv", "r+");
	fscanf(fileResources, "%d,%[^,],%d,%[^,],%d", &rmMan, &rmGold, &occ);
	// we will fclose(fileResources) at the very end of this file.
	
	while((c = getchar()) != EOF && c < len){
		fgets(input,len+1,stdin);
	}
		
		if(input == NULL) 
		{ 
			printf("Content-Type:text/html\n\n");
			printf("<html><head>There was an error reading the given input. Recall that only: DROP n, PLAY, EXIT or REFRESH are valid inputs.</head></html>");
		}
    
		//data received will have the following format: 
    		//file:///C:/Users/JustineTupe/Desktop/index.htm?command=DROP+10&inventory=10%10
    		//reads input until the first '='
		for(int i = 0; input[i]!='='; i++);
		{
			//reads the input until first '&'
			for(int j = i; input[i]!='&'; i++)
			{
				//saves the command into command array
				command[j] = input[i];
			}
		}
		//turns command array into a string by adding a CR
		command[j] = "\0";
		
		//read user input to extract the number of gold pieces to drop
		//reads input until first '+'
		for(int k = 0; input[k]!='+'; k++);
		{
			//reads input until next '&'
			for(int m = k; input[m]!='&'; k++)
			{
				//saves 
				goldDropArray[j] = input[i];
			}
		}
		goldDropArray[j] = "\0";  
		int goldDrop = atoi(goldDropArray);
		
		// read hidden tag for the inventoryManna
		//Desktop/index.htm?command=DROP+10&inventory=10%10
		for(int i = 0; i < len+1 && input[i]!='&'; i++); 
		{
			for(int j = i; i<len+1 && input[i]!='='; i++);
			{
				for(int k = i; i < len+1 && input[i]!='%'; i++)
				{
					inventoryManna[k] = input[i];
				}
				
				// read hidden tag for the inventoryGold
				for(int l = i; i < len+1 && input[i]!='\0'; i++)
				{
					inventoryGold[l] = input[i];
				}
			}
		}
		inventoryManna[k]='\0';
		inventoryGold[l] = '\0';

		int playMan = atoi(inventoryManna);
		int playGold = atoi(inventoryGold);
		
		
  // test for which command the user input. Run the code accordingly
  if(strncmp(command, "DROP", 4) == 0)
  {
	  int manAdd = goldDrop / 2;
	  
	  playGold = playGold - goldDrop;
	  playMan = playMan + manAdd;
	  rmGold = rmGold + goldDrop;

  }
  
  else if(strncmp(command, "PLAY", 4) == 0)
  {
    //execute code for PLAY
    FILE *challenge = fopen("../challenge.c", r);
    int ch;
	  
	while((ch=fgetc(challenge) != EOF) 
	{ 
		printf("%c", ch);
	}
		
    fclose(challenge);
  }
  
  else if(strncmp(command, "EXIT", 4) == 0)
  {
	  //must update the variables in the resources file
	  rmMan = rmMan + playMan;
	  rmGold = rmGold + playGold;
	  occ = 0;
	  
	  //reprint page with sorry to see you go
	  printf("Content-Type:text/html\n\n");
	  printf("<html>");
	  printf("<head><title>Bye! Au Revoir!</title><h1>Aw shucks! Leaving already? Prison isn't for everyone. Come back later, if you dare.</h1>");
	  printf("<h2>Quel dommamge! Vous-partez deja? Je comprends. La prison ce n'est pas pour tout le monde. Reviennez plutard, si vous l'osez faire.</h2>");
	  printf("</head></html>");
  }
  
  else if(strncmp(commmand, "REFRESH", 7) == 0)
  {
	  printf("Content-Type:text/html\n\n");
	  printf("<html><head><center><title> The Room</title></head><body bgcolor=\"grey\"><h1>Welcome to your room / Bienvenue dans votre chambre</h1><p><i>An eternity of terror awaits you / Une eternite de terreur vous attend</i></p>");
	  printf("<center><p><img src=\" https://aos.iacpublishinglabs.com/question/aq/700px-394px/what-is-the-size-of-a-prison-cell_a3b78e5d-2784-49d5-bf43-44bf4fbfd908.jpg?domain=cx.aos.ask.com\"></p>");	
	  printf("<form action=\"https://www.cs.mcgill.ca/~aturim/cgi-bin/transporter.py\" method=\"post\" stlye=\"display\": inLine\"><input type=\"hidden\" name=\"inventory\" value=\"%d,%d\">",playMan,playGold);
	  printf("<input type=\"hidden\" name=\"URL\" value=\"https://www.cs.mcgill.ca/~aturim/cgi-bin/room.cgi\"><input type=\"submit\" value=\"North\"></form><br>");				
	  printf("<form action=\"https://www.cs.mcgill.ca/~aturim/cgi-bin/transporter.py\" method=\"post\" style=\"display: inLine\"><input type=\"hidden\" name=\"inventory\" value=\"%d,%d\">",playMan,playGold);
	  printf("<input type=\"hidden\" name=\"URL\" value=\"https://www.cs.mcgill.ca/~aturim/cgi-bin/room.cgi\"><input type=\"submit\" name=\"button\" value=\"West\"");
	  printf("</form><form action=\"https://www.cs.mcgill.ca/~aturim/cgi-bin/transporter.py\" method=\"post\" style=\"display: inLine\"><input type=\"hidden\" name=\"inventory\" value=\"%d,%d\">",playMan,playGold");
	  printf("<input type=\"hidden\" name=\"URL\" value=\"https://www.cs.mcgill.ca/~aturim/room.cgi\"><input type=\"submit\" name=\"button\" value=\"East\"></form><br>");	
	  printf("<form action=\"https://www.cs.mcgill.ca/~aturim/cgi-bin/transporter.py\" method=\"post\" style=\"display: inLine\"><input type=\"hidden\" name=\"inventory\" value=\"%d,%d\">",playMan,playGold");
	  printf("<input type=\"hidden\" name=\"URL\" value=\"https://www.cs.mcgill.ca/~aturim/room.cgi\"><input type=\"submit\" name=\"button\" value=\"South\"></form><br>");
	  printf("<p>Type in Command. Valid actions are PLAY, DROP n, EXIT, REFRESH</p><div><form action=\"https://www.cs.mcgill.ca/~aturim/room.cgi\"method=\"post\" id=\"textbox\" style=\"display: inline\"></div><div>");
	  printf("<label>COMMAND:<input name=\"command\" size=\"20\"></label></div><input type=\"hidden\" value=\"%d,%d\">",playMan,playGold");
	  printf("name=\"inventory\"></form><div><b><u>Current Player Inventory</u></b></div><b>MANNA: </b> %d<b>GOLD:</b>%d</center></body></html>",playMan, playGold);
  }  
  else { //the user input an invalid command. Reprint the page
	  printf("Content-Type:text/html\n\n");
	  printf("<html><head><center><title> The Room</title></head><body bgcolor=\"grey\"><h1>Welcome to your room / Bienvenue dans votre chambre</h1><p><i>An eternity of terror awaits you / Une eternite de terreur vous attend</i></p>");
	  printf("<center><p><img src=\" https://aos.iacpublishinglabs.com/question/aq/700px-394px/what-is-the-size-of-a-prison-cell_a3b78e5d-2784-49d5-bf43-44bf4fbfd908.jpg?domain=cx.aos.ask.com\"></p>");	
	  printf("<form action=\"https://www.cs.mcgill.ca/~aturim/cgi-bin/transporter.py\" method=\"post\" stlye=\"display\": inLine\"><input type=\"hidden\" name=\"inventory\" value=\"%d,%d\">",playMan,playGold);
	  printf("<input type=\"hidden\" name=\"URL\" value=\"https://www.cs.mcgill.ca/~aturim/cgi-bin/room.cgi\"><input type=\"submit\" value=\"North\"></form><br>");				
	  printf("<form action=\"https://www.cs.mcgill.ca/~aturim/cgi-bin/transporter.py\" method=\"post\" style=\"display: inLine\"><input type=\"hidden\" name=\"inventory\" value=\"%d,%d\">",playMan,playGold);
	  printf("<input type=\"hidden\" name=\"URL\" value=\"https://www.cs.mcgill.ca/~aturim/cgi-bin/room.cgi\"><input type=\"submit\" name=\"button\" value=\"West\"");
	  printf("</form><form action=\"https://www.cs.mcgill.ca/~aturim/cgi-bin/transporter.py\" method=\"post\" style=\"display: inLine\"><input type=\"hidden\" name=\"inventory\" value=\"%d,%d\">",playMan,playGold");
	  printf("<input type=\"hidden\" name=\"URL\" value=\"https://www.cs.mcgill.ca/~aturim/room.cgi\"><input type=\"submit\" name=\"button\" value=\"East\"></form><br>");	
	  printf("<form action=\"https://www.cs.mcgill.ca/~aturim/cgi-bin/transporter.py\" method=\"post\" style=\"display: inLine\"><input type=\"hidden\" name=\"inventory\" value=\"%d,%d\">",playMan,playGold");
	  printf("<input type=\"hidden\" name=\"URL\" value=\"https://www.cs.mcgill.ca/~aturim/room.cgi\"><input type=\"submit\" name=\"button\" value=\"South\"></form><br>");
	  printf("<p>Type in Command. Valid actions are PLAY, DROP n, EXIT, REFRESH</p><div><form action=\"https://www.cs.mcgill.ca/~aturim/room.cgi\"method=\"post\" id=\"textbox\" style=\"display: inline\"></div><div>");
	  printf("<label>COMMAND:<input name=\"command\" size=\"20\"></label></div><input type=\"hidden\" value=\"%d,%d\">",playMan,playGold");
	  printf("name=\"inventory\"></form><div><b><u>Current Player Inventory</u></b></div><b>MANNA: </b> %d<b>GOLD:</b>%d</center></body></html>",playMan, playGold);
  }
		 
	// update the resource file
	char comma = ",";
	fprintf(fileResources, "%d, %c, %d, %c, %d", rmMan, comma, rmGold, comma, occ);
	fclose(fileResources);
	
	//update the inventory file
	FILE *fileInventory;
	fileInventory = fopen("inventory.csv", "r+");
	char comma = ",";
     	fprintf(fileInventory, "%d, %c, %d, %c", playMan, comma, playGold, comma);
	fclose(fileInventory);
		 
	// we could alt create source files with the methods updateResources and updateInventory and compile it into room.o
	gcc -g -Wall room.c -o room;
}
