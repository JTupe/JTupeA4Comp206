#include<stdlib.h>
#include<stdio.h>

//Alice: you saved the resources and the inventory csv as .txt, why? I think we can save them as .csv?
// include the methods of the file //
void updateInventory(int);
void updateResources(int);

main(char inputCommand[], char userInventory[]) {
  char input[200];
  char command[30];
  char goldDropArray[3];
  int goldDrop = 0;
  int len = atoi(getenv("CONTENT_LENGTH"));
  char c;
  
  while((c = getchar()) != EOF && c < len){
  fgets(input,len,stdin);
  {
    if(input == NULL) 
	{ 
		FILE *website = fopen(room.html, r+);
		fprintf(website, "%s", "There was an error reading the given input. Recall that only: DROP n, PLAY, EXIT or REFRESH are valid inputs."); 
		fclose(website);
	}
    
    //data received will have the following format: 
    //file:///C:/Users/JustineTupe/Desktop/index.htm?command=DROP+10&firstname=Mickey&lastname=Mouse
    //reads input until the first '='
    for(int i = 0; input[i]!='='; i++);{
    //reads the String until first '&'
    for(int j = i; input[i]!='+'; i++)
    {
      //saves the command into command array
      command[j] = input[i];
    }
    }
    //turns command array into a string by adding a CR
    command[j] = "\0";
    //Alice: I think the loop is not saving the drop, but copying everything before the "="
    /*instead should be 
    for (int i = 0; input[i]!='='; i++);{
     for (int j = i; input[i]!='+'; j++){
      command[j] = input[i];
     }
    }
    Command[j] = "\0"
    */
    



    //read user input to extract the number of gold pieces to drop
    //reads input until next '+'
    for(int k = 0; input[k]!='+'; k++);{
    //reads input until next '&'
    for(int m = k; input[m]!='&'; k++)
    {
      //saves 
      goldDropArray[j] = input[i];
    }
    }
	  goldDropArray[j] = "\0";
    goldDrop = atoi(goldDropArray);
  }
}

  char * DROP = "DROP", PLAY = "PLAY", EXIT = "EXIT", REFRESH = "REFRESH";
  
  if(strncmp(command, DROP, 4) == 0)
  {
    //execute code for DROP i.e update both csv files
    updateInventory(goldDrop);
    updateResources(goldDrop);
    
    // NEED TO PUT THE FILENAME OF THE HTML WEBSITE FILE
    FILE *website = fopen("room.html", r+);
    int ch;
    
    if(website == NULL);
    {
      printf("%s", "<head><title>ERROR</title></head>");
      printf("%s", "<body><p>Unable to open file!</p></body>");
    }
    else
    {
      while((ch=fgetc(website) != EOF) 
	  { 
		  printf("%c", ch);
	  }
     }
     fclose(website); 
  }
  
  else if(strncmp(command, PLAY, 4) == 0)
  {
    //execute code for PLAY
    FILE *challenge = fopen("challenge.c", r);
    int ch;
	  
	  while((ch=fgetc(challenge) != EOF) { 
			printf("%c", ch);
		}
		
    fclose(challenge);
  }
  
  else if(strncmp(command, EXIT, 4) == 0)
  {
	  FILE *website = fopen("room.html", r+);
    //execute code for EXIT
    //must update the resources file so that the room is unoccupied (resources[3] = 0)
	  printf("%s", "<html>");
	  printf("%s", "<head><title>Bye! Au Revoir!</title><h1>Aw shucks! Leaving already? Prison isn't for everyone. Come back later, if you dare.</h1>");
	  printf("%s", "<h2>Quel dommamge! Vous-partez deja? Je comprends. La prison ce n'est pas pour tout le monde. Reviennez plutard, si vous l'osez faire.");
	  printf("%s", "</head></html>");
	  fclose(website);
  }
  
  else if(strncmp(commmand, REFRESH, 7) == 0)
  {
    FILE *website = fopen("room.html", r+);
    int ch;
    
    if(website == NULL);
    {
      printf("%s", "<head><title>ERROR</title></head>");
      printf("%s", "<body><p>Unable to open file!</p></body>");
    }
    else
    {
      while((ch=fgetc(website) != EOF) 
            { 
		    printf("%c", ch);
            }
     }
     fclose(website); 
	    
  }  
  else {
	FILE *website = fopen("room.html", r+);
	  fprintf(website, "%s", "There was an error reading the given input. Recall that only: DROP n, PLAY, EXIT or REFRESH are valid inputs.");
	  fclose(website); 
  }
  
  // we could alt create source files with the methods updateResources and updateInventory and compile it into room.o
  gcc -g -Wall room.c -o room;
            
  //method to update resources.csv
  void updateResources(int drop)
  {
    //change gold variable in the resource file to
    int resources[3];
    FILE *fileResources;
    fileResources = fopen("resources.csv", "r+");
    if(fileResources == NULL) { perror("Error opening resource file"); return(-1); }
    
    fscanf(fileResources, "%d,%[^,],%d,%[^,],%d", &resources[0], &resources[1], &resources[2]);
    //manna, gold, occupied
    resources[1] = resources[1] + drop;
    //NEED TO WRITE TO THE FILE

    char comma = ",";
    fprintf(fileResources, "%d, %c, %d, %c, %d", resources[0], comma, resources[1], comma, resources[2]);
	  
	  fclose(fileResources);
   }
          
   void updateInventory(int drop)
   {
     char inventory[2];
     
     if(drop != 0) { int manAdd = drop / 2; }
     else { int manAdd = 0; }
    
     //read and write to the inventory file. Deduct gold from inventory file.
     FILE *fileInventory;
     fileInventory = fopen("inventory.csv", "r+");
     if(fileInventory == NULL) { perror("Error opening inventory file"); return(-1); }
    
     fscanf(fileInventory, "%d,%[^,],%d,%[^,]", &inventory[0], &inventory[1]);
     //manna = inventory[0], gold = inventory[1]
     inventory[0] = inventory[0] + manAdd;
     inventory[1] = inventory[1] - drop;
     
     char comma = ",";
     fprintf(fileInventory, "%d, %c, %d, %c", inventory[0], comma, inventory[1], comma);
	   fclose(fileInventory);
   }
}
