#include<stdlib.h>
#include<stdio.h>

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
    for(int i = 0; i<200 && input[i]]!='='; i++);
    //reads the String until first '&'
    for(int j = i; i<200 && input[i]!='&'; i++)
    {
      //saves the command into command array
      command[i] = input[i];
    }
    //turns command array into a string by adding a CR
    command[i] = "\0";
    
    //read user input to extract the number of gold pieces to drop
    //reads input until next '+'
    for(int k = 0; k < 200 && input[k]!='+'; k++);
    //reads input until next '&'
    for(int m = k; m < 200 && input[m]!='&'; k++)
    {
      //saves 
      goldDropArray[i] = input[i];
    }
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
    
    printf("Content-Type:text/html\n\n");
    printf("<html>");
    
    if(website == NULL);
    {
      printf("<head><title>ERROR</title></head>");
      printf("<body><p>Unable to open file!</p></body>");
    }
    else
    {
      while((ch=fgetc(website) != EOF) 
	  { 
	  putchar(ch);
	  }
     }
     fclose(website); 
     printf("</html>");
  }
  
  else if(strncmp(command, PLAY, 4) == 0)
  {
    //execute code for PLAY
    FILE *game = fopen("game.c", r);
    int ch;
    
    printf("Content-Type:text/html\n\n");
    printf("<html>");
    
    if(game == NULL);
    {
      printf("<head><title>ERROR</title></head>");
      printf("<body><p>Unable to open file!</p></body>");
    }
    else
    {
      while((ch=fgetc(game) != EOF) 
            { 
              putchar(ch);
            }
     }
     fclose(game); 
     printf("</html>");
  }
  
  else if(strncmp(command, EXIT, 4) == 0)
  {
    //execute code for EXIT
    //must rewrite the html page with a sorry to see you go screen
    //must update the resources file so that the room is unoccupied (resources[3] = 0)
  }
  
  else if(strncmp(commmand, REFRESH, 7) == 0)
  {
    FILE *website = fopen("room.html", r+);
    int ch;
    
    printf("Content-Type:text/html\n\n");
    printf("<html>");
    
    if(website == NULL);
    {
      printf("<head><title>ERROR</title></head>");
      printf("<body><p>Unable to open file!</p></body>");
    }
    else
    {
      while((ch=fgetc(website) != EOF) 
            { 
              putchar(ch);
            }
     }
     fclose(website); 
     printf("</html>");
  }  
  else {
    fprintf("There was an error reading the given input. Recall that only: DROP n, PLAY, EXIT or REFRESH are valid inputs.");
  }
  
  // we could alt create source files with the methods updateResources and updateInventory and compile it into room.o
  gcc -g -Wall room.c -o room;
            
  //method to update resources.csv
  void updateResources(int drop)
  {
    //change gold variable in the resource file to
    char resources[3];
    FILE *fileResources;
    fileResources = fopen("resources.csv", "r+");
    if(fileResources == NULL) { perror("Error opening resource file"); return(-1); }
    
    fscanf(fileResources, "%d,%[^,],%d,%[^,],%d,%[^,]", &resources[0], &resources[1], &resources[2]);
    //manna, gold, occupied
    resources[1] = resources[1] + drop;
    //NEED TO WRITE TO THE FILE

    char comma = ",";
    fprintf(fileResources, "%d, %c, %d, %c", resources[0], comma, resources[1], comma, resources[2]);
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
   }
}
