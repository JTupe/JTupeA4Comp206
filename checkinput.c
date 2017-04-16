#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){
    //sacan how many resources are left in this room
    FILE *resources; char c;
    char data1[50]; char data2[50]; char data3[50];
    resources=fopen("../resources.csv", "rt");
    int a = 0;
    while((c=fgetc(resources))!=','){
        data1[a]=c;
        a++;
    }
    data1[a]='\0';
    a=0;
    while((c=fgetc(resources))!=','){
        data2[a]=c;
        a++;
    }
    data2[a]='\0';
    a=0;
    /* I do not know what happens here. With this part, it would compile but lead to a 500 error.
     So, I just do not scan it. Because when it reaches here, this is someone at here. Set it at 1.
     
     
     while((c=fgetc(resources))!= '\n' ){
     data3[a]=c;
     a++;
     }
     data3[a]='\0';*/
    int roomManna, roomGold, occupancy;
    sscanf(data1, "%d", &roomManna);
    sscanf(data2, "%d", &roomGold);
    sscanf(data3, "%d", &occupancy);
    occupancy=1;//as long as room.cgi is active, there is someone in the room. I assign this value to 1 at here.
    
    //to see what is in the packet
    char string[500];
    int n = atoi(getenv("CONTENT_LENGTH"));
    fgets(string,n+1,stdin);
    //initialize strings
    char command[300];
    char inventory1[100];
    char inventory2[100];
    int i = 0, j = 0;
    
    if (string[0] == 'c'){
        //command
        while(i<(n+1) && string[i]!='='){i++;}
        i++;
        while(i<(n+1)&&string[i]!='&'){
            if(string[i]=='+'){
                command[j]=' ';
                j++;i++;
            }
            else{
                command[j]=string[i];
                j++;i++;
            }
        }
        command[j]='\0';
        //inventory1 for player's manna
        j = 0;
        while(i<(n+1)&&string[i]!='='){i++;}
        i++;
        while(i<(n+1)&&string[i]!='%'){
            inventory1[j]=string[i];
            j++;i++;
        }
        inventory1[j]='\0';
        i+=3;j=0;
        //inventory2 for player's golds
        while(i<(n+1)&&string[i]!='\0'){
            inventory2[j]=string[i];
            j++; i++;
        }
        inventory2[j]='\0';
    }
    else if(string[0] == 'i'){
        //inventory1 for player's manna
        while(i<(n+1)&&string[i]!='='){i++;}
        i++;
        while(i<(n+1)&&string[i]!='%'){
            inventory1[j]=string[i];
            j++;i++;
        }
        inventory1[j]='\0';
        i+=3;j=0;
        //inventory2 for player's golds
        while(i<(n+1)&&string[i]!='&'){
            inventory2[j]=string[i];
            j++; i++;
        }
        inventory2[j]='\0';
        //command
        while(i<(n+1) && string[i]!='='){i++;}
        i++;
        j = 0;
        while(i<(n+1)&&string[i]!='\0'){
            if(string[i]=='+'){
                command[j]=' ';
                j++;i++;
            }
            else{
                command[j]=string[i];
                j++;i++;
            }
        }
        command[j]='\0';
    }
    
    
    
    
    int playerManna = atoi(inventory1);
    int playerGold = atoi(inventory2);
    
    int badSyntax = 0; //boolean player entered command that does not exist
    int playerExits = 0;//boolean player exits
    int playerRefreshes = 0;//boolean player refreshes
    int playerPlays = 0;//boolean player plays
    int dead =0; //boolean player deads
    int win=0;  //boolean player wins
    
    //player drops
    int drop=0;
    if(strncmp(command,"DROP",4)==0){
        int b = 0;
        char dropString[50];
        while(command[b+5]!='\0'){
            dropString[b]=command[b+5];
            b++;
        }
        dropString[b]='\0';
        drop = atoi(dropString);
    }
    
    //player plays
    else if(strcmp(command,"PLAY")==0){
        /*LINKED TO XIAOZHOU'S PY LATTERLY*/ playerPlays=1;}
    
    //player exits
    else if(strcmp(command,"EXIT")==0){
        playerExits=1;
        roomManna=roomManna+playerManna;
        roomGold=roomGold+playerGold;
        playerManna=0;playerGold=0;
        occupancy=0;
    }
    
    //player refresh
    else if(strcmp(command,"REFRESH")==0){
        playerRefreshes=1;
    }
    else{
        badSyntax=1;
    }
    //modify those values
    playerManna=playerManna+drop/2;
    playerGold=playerGold-drop;
    roomGold=roomGold+drop;
    //check if player wins or dies
    if(playerManna<=0) dead=1;
    if(playerGold>=100) win=1;
    
    
    //html part
    //player dies
    if((dead!=0)&&(playerExits==0)){
        printf("Content-Type:text/html\n\n");
        printf("<html>\n\t<head><title>Room: Ironbottom</title></head>\n\t");
        printf("<body><center><h1>Ironbottom</h1></center>\n\t");
        printf("<center><img src=\"http://www.cs.mcgill.ca/~jcao25/gg.png\" width=\"300\" height=\"300\"></center>\n\t");
        printf("<p><center>.</certer></p><p><center>You have used up all your manna. Game Over. </center></p>\n\t");
        printf("</body></html>");
    }
    //player wins
    else if((win!=0)&&(playerExits==0)){
        printf("Content-Type:text/html\n\n");
        printf("<html>\n\t<head><title>Room: Ironbottom</title></head>\n\t");
        printf("<body><center><h1>Ironbottom</h1></center>\n\t");
        printf("<center><img src=\"http://www.cs.mcgill.ca/~jcao25/congrats.jpg\" width=\"950\" height=\"300\"></center>\n\t");
        printf("<p><center>.</certer></p><p><center>You have earned 100 gold pieces. You win!</center></p>\n\t");
        printf("</body></html>");
    }
    //badsyntax
    else if(badSyntax){
        printf("Content-Type:text/html\n\n");
        printf("<html>\n\t<head><title>Room: Ironbottom</title></head>\n\t");
        printf("<body><center><h1>Ironbottom</h1></center>\n\t");
        printf("<center><img src=\"http://www.cs.mcgill.ca/~jcao25/wall.png\" width=\"700\" height=\"350\"></center>\n\t");
        printf("<center>\n\t");
        printf("<form action=\"http://www.cs.mcgill.ca/~hnguye124/cgi-bin/transporter.py\" method=\"post\">\n\t");
        printf("<input type=\"hidden\" name=\"inventory\" value=\"%d,%d\">\n\t",playerManna,playerGold);
        printf("<input type=\"hidden\" name=\"URL\" value=\"http://www.cs.mcgill.ca/~jcao25/cgi-bin/room.cgi\">\n\t");
        printf("<input type=\"submit\" value=\"North\">\n\t");
        printf("</form></center><center><table><tr>\n\t");
        printf("<td><form action=\"http://www.cs.mcgill.ca/~sli144/cgi-bin/transporter.py\" method=\"post\">\n\t");
        printf("<input type=\"hidden\" name=\"inventory\" value=\"%d,%d\">\n\t",playerManna,playerGold);
        printf("<input type=\"hidden\" name=\"URL\" value=\"http://www.cs.mcgill.ca/~jcao25/cgi-bin/room.cgi\">\n\t");
        printf("<input type=\"submit\" value=\"West\">\n\t");
        printf("</form></td>");
        printf("<td><form action=\"http://www.cs.mcgill.ca/~jcao25/cgi-bin/room.cgi\" method=\"post\">\n\t");
        printf("<input type=\"text\" name=\"command\">\n\t");
        printf("<input type=\"hidden\" name=\"inventory\" value=\"%d,%d\">\n\t",playerManna,playerGold);
        printf("<input type=\"submit\" value=\"submit\">\n\t");
        printf("</form></td>\n\t");
        printf("<td><form action=\"http://www.cs.mcgill.ca/~hli115/cgi-bin/transporter.py\" method=\"post\">\n\t");
        printf("<input type=\"hidden\" name=\"inventory\" value=\"%d,%d\">\n\t",playerManna,playerGold);
        printf("<input type=\"hidden\" name=\"URL\" value=\"http://www.cs.mcgill.ca/~jcao25/cgi-bin/room.cgi\">\n\t");
        printf("<input type=\"submit\" value=\"East\">\n\t");
        printf("</form></td></tr></table></center>\n\t");
        printf("<center>\n\t");
        printf("<form action=\"http://www.cs.mcgill.ca/~aanich/cgi-bin/transporter.py\" method=\"post\">\n\t");
        printf("<input type=\"hidden\" name=\"inventory\" value=\"%d,%d\">\n\t",playerManna,playerGold);
        printf("<input type=\"hidden\" name=\"URL\" value=\"http://www.cs.mcgill.ca/~jcao25/cgi-bin/room.cgi\">\n\t");
        printf("<input type=\"submit\" value=\"South\">\n\t");
        printf("</form></center>\n\t");
        printf("<p><center>Command can not be identified. %s, Please enter \"DROP n\", \"PLAY\", \"EXIT\", or \"REFRESH\".</certer></p><p><center>You have %d manna and %d gold pieces.</center></p>\n\t",command,playerManna,playerGold);
        printf("</body></html>");
    }
    
    //player exits
    else if(playerExits){
        printf("Content-Type:text/html\n\n");
        printf("<html>\n\t<head><title>Room: Ironbottom</title></head>\n\t");
        printf("<body><center><h1>Ironbottom</h1></center>\n\t");
        printf("<center><img src=\"http://www.cs.mcgill.ca/~jcao25/wall.png\" width=\"700\" height=\"350\"></center>\n\t");
        printf("<center><h2>You left the room.Hope to see you next time :) </h2</center>\n\t");
        printf("</body></html>");
    }
    //refresh
    else if(playerRefreshes){
        printf("Content-Type:text/html\n\n");
        printf("<html>\n\t<head><title>Room: Ironbottom</title></head>\n\t");
        printf("<body><center><h1>Ironbottom</h1></center>\n\t");
        printf("<center><img src=\"http://www.cs.mcgill.ca/~jcao25/wall.png\" width=\"700\" height=\"350\"></center>\n\t");
        printf("<center>\n\t");
        printf("<form action=\"http://www.cs.mcgill.ca/~hnguye124/cgi-bin/transporter.py\" method=\"post\">\n\t");
        printf("<input type=\"hidden\" name=\"inventory\" value=\"%d,%d\">\n\t",playerManna,playerGold);
        printf("<input type=\"hidden\" name=\"URL\" value=\"http://www.cs.mcgill.ca/~jcao25/cgi-bin/room.cgi\">\n\t");
        printf("<input type=\"submit\" value=\"North\">\n\t");
        printf("</form></center><center><table><tr>\n\t");
        printf("<td><form action=\"http://www.cs.mcgill.ca/~sli144/cgi-bin/transporter.py\" method=\"post\">\n\t");
        printf("<input type=\"hidden\" name=\"inventory\" value=\"%d,%d\">\n\t",playerManna,playerGold);
        printf("<input type=\"hidden\" name=\"URL\" value=\"http://www.cs.mcgill.ca/~jcao25/cgi-bin/room.cgi\">\n\t");
        printf("<input type=\"submit\" value=\"West\">\n\t");
        printf("</form></td>");
        printf("<td><form action=\"http://www.cs.mcgill.ca/~jcao25/cgi-bin/room.cgi\" method=\"post\">\n\t");
        printf("<input type=\"text\" name=\"command\">\n\t");
        printf("<input type=\"hidden\" name=\"inventory\" value=\"%d,%d\">\n\t",playerManna,playerGold);
        printf("<input type=\"submit\" value=\"submit\">\n\t");
        printf("</form></td>\n\t");
        printf("<td><form action=\"http://www.cs.mcgill.ca/~hli115/cgi-bin/transporter.py\" method=\"post\">\n\t");
        printf("<input type=\"hidden\" name=\"inventory\" value=\"%d,%d\">\n\t",playerManna,playerGold);
        printf("<input type=\"hidden\" name=\"URL\" value=\"http://www.cs.mcgill.ca/~jcao25/cgi-bin/room.cgi\">\n\t");
        printf("<input type=\"submit\" value=\"East\">\n\t");
        printf("</form></td></tr></table></center>\n\t");
        printf("<center>\n\t");
        printf("<form action=\"http://www.cs.mcgill.ca/~aanich/cgi-bin/transporter.py\" method=\"post\">\n\t");
        printf("<input type=\"hidden\" name=\"inventory\" value=\"%d,%d\">\n\t",playerManna,playerGold);
        printf("<input type=\"hidden\" name=\"URL\" value=\"http://www.cs.mcgill.ca/~jcao25/cgi-bin/room.cgi\">\n\t");
        printf("<input type=\"submit\" value=\"South\">\n\t");
        printf("</form></center>\n\t");
        printf("<p><center>The room has been refreshed. You are send back because the target room is occupied, or you entered REFRESH command.</certer></p><p><center>You have %d manna and %d gold pieces.</center></p>\n\t",playerManna,playerGold);
        printf("</body></html>");
    }
    //GAME!!!!
    else if(playerPlays){
        printf("Content-Type:text/html\n\n");
        printf("<html><head><title>Room: Ironbottom</title></head>\n\t");
        printf("<body><center><h1>Ironbottom</h1></center>\n\t");
        printf("<center><img src=\"http://www.cs.mcgill.ca/~jcao25/wall.png\" width=\"700\"height=\"350\"></center>\n\t");
        printf("<form action=\"http://www.cs.mcgill.ca/~jcao25/cgi-bin/game.py\" method=\"post\">");
        printf("<table style=\"width:100%%\">");
        printf("<tr>");
        printf("<th>");
        printf("<th>Round1");
        printf("<th>Round2");
        printf("<th>Round3");
        printf("<th>Round4");
        printf("<th>Round5");
        printf("</tr>");
        printf("<tr>");
        printf("<td>Your Commands Are");
        printf("<td><input type=\"text\" name=\"r1\">");
        printf("<td><input type=\"text\" name=\"r2\">");
        printf("<td><input type=\"text\" name=\"r3\">");
        printf("<td><input type=\"text\" name=\"r4\">");
        printf("<td><input type=\"text\" name=\"r5\">");
        printf("</tr>");
        printf("</table>");
        printf("<input type=\"hidden\" name=\"inventory\" value=\"%d,%d\">",playerManna, playerGold);
        printf("<center><input type=\"submit\" value=\"Engage!\"></input></center>");
        printf("</form>");
        printf("<pre style=\"font-size:160%%;\"><center>");
        printf("Welcome to Ironbottom! Your objective is to defeat the enemy ship.");
        printf("<p>Enter 5 commands at the same time.</p>");
        printf("<p>There are 3 commands you can use:</p>");
        printf("<p>fire: cause 1 damage, can be avoided.</p>");
        printf("<p>torp: cause 2 damage if enemy does not fire.</p>");
        printf("<p>avoid: avoid enemy fire.</p>");
        printf("<p>Both sides have 3 Hit Points, the one who destroys the other");
        printf("side wins.</p>");
        printf("<p>Please input one command for each round, then press 'Engage!'.</p>");
        printf("<p>If you want to quit, enter 'EXIT' in Round1.</p></center>");
        printf("<p><center>You have %d manna and %d gold pieces.</center></p></pre>", playerManna, playerGold);
        printf("</body></html>");
        
    }else{  // Since we have a badsyntax case, the only case we have not processed is the DROP CASE.
        if(playerGold<0){//player does not have enough gold to drop
            playerManna=playerManna-drop/2;
            playerGold=playerGold+drop;
            roomGold=roomGold-drop;
            printf("Content-Type:text/html\n\n");
            printf("<html>\n\t<head><title>Room: Ironbottom</title></head>\n\t");
            printf("<body><center><h1>Ironbottom</h1></center>\n\t");
            printf("<center><img src=\"http://www.cs.mcgill.ca/~jcao25/wall.png\" width=\"700\" height=\"350\"></center>\n\t");
            printf("<center>\n\t");
            printf("<form action=\"http://www.cs.mcgill.ca/~hnguye124/cgi-bin/transporter.py\" method=\"post\">\n\t");
            printf("<input type=\"hidden\" name=\"inventory\" value=\"%d,%d\">\n\t",playerManna,playerGold);
            printf("<input type=\"hidden\" name=\"URL\" value=\"http://www.cs.mcgill.ca/~jcao25/cgi-bin/room.cgi\">\n\t");
            printf("<input type=\"submit\" value=\"North\">\n\t");
            printf("</form></center><center><table><tr>\n\t");
            printf("<td><form action=\"http://www.cs.mcgill.ca/~sli144/cgi-bin/transporter.py\" method=\"post\">\n\t");
            printf("<input type=\"hidden\" name=\"inventory\" value=\"%d,%d\">\n\t",playerManna,playerGold);
            printf("<input type=\"hidden\" name=\"URL\" value=\"http://www.cs.mcgill.ca/~jcao25/cgi-bin/room.cgi\">\n\t");
            printf("<input type=\"submit\" value=\"West\">\n\t");
            printf("</form></td>");
            printf("<td><form action=\"http://www.cs.mcgill.ca/~jcao25/cgi-bin/room.cgi\" method=\"post\">\n\t");
            printf("<input type=\"text\" name=\"command\">\n\t");
            printf("<input type=\"hidden\" name=\"inventory\" value=\"%d,%d\">\n\t",playerManna,playerGold);
            printf("<input type=\"submit\" value=\"submit\">\n\t");
            printf("</form></td>\n\t");
            printf("<td><form action=\"http://www.cs.mcgill.ca/~hli115/cgi-bin/transporter.py\" method=\"post\">\n\t");
            printf("<input type=\"hidden\" name=\"inventory\" value=\"%d,%d\">\n\t",playerManna,playerGold);
            printf("<input type=\"hidden\" name=\"URL\" value=\"http://www.cs.mcgill.ca/~jcao25/cgi-bin/room.cgi\">\n\t");
            printf("<input type=\"submit\" value=\"East\">\n\t");
            printf("</form></td></tr></table></center>\n\t");
            printf("<center>\n\t");
            printf("<form action=\"http://www.cs.mcgill.ca/~aanich/cgi-bin/transporter.py\" method=\"post\">\n\t");
            printf("<input type=\"hidden\" name=\"inventory\" value=\"%d,%d\">\n\t",playerManna,playerGold);
            printf("<input type=\"hidden\" name=\"URL\" value=\"http://www.cs.mcgill.ca/~jcao25/cgi-bin/room.cgi\">\n\t");
            printf("<input type=\"submit\" value=\"South\">\n\t");
            printf("</form></center>\n\t");
            printf("<p><center>You do not have enough gold pieces to drop. Please try again.</certer></p><p><center>You have %d manna and %d gold pieces.</center></p>\n\t",playerManna,playerGold);
            printf("</body></html>");
            
        }
        else{//enough gold to drop
            printf("Content-Type:text/html\n\n");
            printf("<html>\n\t<head><title>Room: Ironbottom</title></head>\n\t");
            printf("<body><center><h1>Ironbottom</h1></center>\n\t");
            printf("<center><img src=\"http://www.cs.mcgill.ca/~jcao25/wall.png\" width=\"700\" height=\"350\"></center>\n\t");
            printf("<center>\n\t");
            printf("<form action=\"http://www.cs.mcgill.ca/~hnguye124/cgi-bin/transporter.py\" method=\"post\">\n\t");
            printf("<input type=\"hidden\" name=\"inventory\" value=\"%d,%d\">\n\t",playerManna,playerGold);
            printf("<input type=\"hidden\" name=\"URL\" value=\"http://www.cs.mcgill.ca/~jcao25/cgi-bin/room.cgi\">\n\t");
            printf("<input type=\"submit\" value=\"North\">\n\t");
            printf("</form></center><center><table><tr>\n\t");
            printf("<td><form action=\"http://www.cs.mcgill.ca/~sli144/cgi-bin/transporter.py\" method=\"post\">\n\t");
            printf("<input type=\"hidden\" name=\"inventory\" value=\"%d,%d\">\n\t",playerManna,playerGold);
            printf("<input type=\"hidden\" name=\"URL\" value=\"http://www.cs.mcgill.ca/~jcao25/cgi-bin/room.cgi\">\n\t");
            printf("<input type=\"submit\" value=\"West\">\n\t");
            printf("</form></td>");
            printf("<td><form action=\"http://www.cs.mcgill.ca/~jcao25/cgi-bin/room.cgi\" method=\"post\">\n\t");
            printf("<input type=\"text\" name=\"command\">\n\t");
            printf("<input type=\"hidden\" name=\"inventory\" value=\"%d,%d\">\n\t",playerManna,playerGold);
            printf("<input type=\"submit\" value=\"submit\">\n\t");
            printf("</form></td>\n\t");
            printf("<td><form action=\"http://www.cs.mcgill.ca/~hli115/cgi-bin/transporter.py\" method=\"post\">\n\t");
            printf("<input type=\"hidden\" name=\"inventory\" value=\"%d,%d\">\n\t",playerManna,playerGold);
            printf("<input type=\"hidden\" name=\"URL\" value=\"http://www.cs.mcgill.ca/~jcao25/cgi-bin/room.cgi\">\n\t");
            printf("<input type=\"submit\" value=\"East\">\n\t");
            printf("</form></td></tr></table></center>\n\t");
            printf("<center>\n\t");
            printf("<form action=\"http://www.cs.mcgill.ca/~aanich/cgi-bin/transporter.py\" method=\"post\">\n\t");
            printf("<input type=\"hidden\" name=\"inventory\" value=\"%d,%d\">\n\t",playerManna,playerGold);
            printf("<input type=\"hidden\" name=\"URL\" value=\"http://www.cs.mcgill.ca/~jcao25/cgi-bin/room.cgi\">\n\t");
            printf("<input type=\"submit\" value=\"South\">\n\t");
            printf("</form></center>\n\t");
            printf("<p><center>You dropped %d gold pieces.</certer></p><p><center>AND NOW</certer></p><p><center>You have %d manna and %d gold pieces.</center></p>\n\t",drop,playerManna,playerGold);
            printf("</body></html>");
        }
    }
    resources=fopen("../resources.csv","wt");
    fprintf(resources, "%d,%d,%d", roomManna, roomGold, occupancy);
    fclose(resources);
    
    
    
    return 0;
}
