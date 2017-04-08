#include<stdlib.h>
#include<stdio.h>

// include the methods of the file //

main() {
// use fgets to read from stdin
// if the user sends an invalid command, send an error
// assuming the command is in the following format: http://www.cs.mcgill.ca/~USERNAME/cgi-bin/room.cgi?command=STRING&inventory=INT,INT,INT
  
  //create an array, input, of arbritary length. We will store the entire String of the user's input into input array
  //create an array, command, of arbritrary length to store only the command of the user's input
  char input[80], command[40];
  
  //reads from stdin for 80 chars and saves into input array
  fgets(input, 80, stdin)
  {
    //reads input until the first '=' AKA http://www.cs.mcgill.ca/~USERNAME/cgi-bin/room.cgi?command=STRING&inventory=_,_ now becomes
    //STRING&inventory=_,_
    for(int i = 0; i<80 && input!='='; i++);
    //reads the String containing the command by reading input from '=' until '&'
    for(int j = i; i<80 && input[i]!='&'; i++)
    {
      //saves the command into command array
      command[i] = input[i];
    }
    //turns command array into a string by adding a CR
    command[i] = "\0";
  }
  
  char * DROP = "DROP", PLAY = "PLAY", EXIT = "EXIT", REFRESH = "REFRESH";
  
  if(strncmp(command, DROP, 4) == 0)
  {
    //execute code for DROP
  }
  
  else if(strncmp(command, PLAY, 4) == 0)
  {
    //execute code for PLAY
  }
  
  else if(strncmp(command, EXIT, 4) == 0)
  {
    //execute code for EXIT
  }
  
  else if(strncmp(commmand, REFRESH, 7) == 0)
  {
    //execute code for REFRESH
  }  
  else {
    fprintf("There was an error reading the given input. Recall that only: DROP n, PLAY, EXIT or REFRESH are valid inputs.");
  }
  
  //method to read inventory.csv
  char *getInventory()
  {
    FILE *inventory;
    inventory = fopen("inventory.txt", "r+");
    int char = 0;
    int inventory[3];
    int len = 0;
    
    //while(char != EOF && char != '\n')
    //{
      //fgets(
    for(int i = 0; i < 3; i++)
    {
      fscanf(inventory, "%[^','], %d, %d, %d", &inventory
    } 
  
  void DROP()
  {
    
  }
}
