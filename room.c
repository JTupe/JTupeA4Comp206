#include<stdlib.h>
#include<stdio.h>

// include the methods of the file //

main() {
  char input[200];
  char goldDrop[3];
  int n = atoi(getenv("CONTENT_LENGTH"));
  
  fgets(input,n,stdin)
    
  if(input == "NULL") { fprintf("There was an error reading the given input. Recall that only: DROP n, PLAY, EXIT or REFRESH are valid inputs."); }
    
  //data received will have the following format: 
    //file:///C:/Users/JustineTupe/Desktop/index.htm?command=DROP+10&firstname=Mickey&lastname=Mouse
    //reads input until the first '='
    for(int i = 0; i<200 && input!='='; i++);
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
    for(int i = 0; i < 100 && input!='+'; i++);
    //reads input until next '&'
    for(int j = i; i < 100 && input !='&'; i++)
    {
      //saves 
      goldDrop[i] = input[i];
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
    FILE *fileInventory;
    fileInventory = fopen("inventory.txt", "r+");
    int manna[1], gold[1];
    
    if(fileInventory == NULL) { perror("Error opening inventory file"); return(-1); }
    
    while(!feof(fileInventory))
    {
      //reads fileInventory, ignores commas, saves each int into manna and gold
      fscanf(fileInventory, "%[^','], %d, %d", &manna, &gold);
    }
  }
  
  void DROP()
  {
    
    intGoldDrop = atoi(goldDrop);
    // calculate how much manna we need to add to the players inventory
    intMannaAdd = intGoldDrop / 2;
    
    //SOMEHOW Add manna to the inventory file. Deduct gold from inventory file.
    manna = manna + intMannaAdd;
    gold = gold - intGoldDrop;
    //SOMEHOW set the gold variable in the resource file to
    gold = gold + intGoldDrop;
  }
}
