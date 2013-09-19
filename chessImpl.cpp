#include<string>
#include "color.h"
#include "chessFunc1.h"
               
int main(void){
    using namespace std; 
    cout<<"welcome to chess 1.0!"<<endl<<"created by pavan!!!!"<<endl<<endl;
    cout << "please enter your moves in 4 letter algebraic" << endl << "ie e2e4 in lower case only" << endl;
    cout << "commands: exit = quit, abort = quit, print = displays the board, undo=to undo a move" << endl << "new = new game" << endl << endl;
    string passed; 
    setup();
    while(1){
       getline(cin,passed);
       if(passed.substr(0,4)=="exit" || passed.substr(0,5)=="abort" || passed.substr(0,4)=="quit"){
              break;                             
       }         
       if(passed.substr(0,4)=="undo"){
            undo();
            printb();                               
       }
       if(passed.substr(0,1)>="a" && passed.substr(0,1)<="h" &&
          passed.substr(1,1)>="1" && passed.substr(1,1)<="8" &&
          passed.substr(2,1)>="a" && passed.substr(2,1)<="h" &&
          passed.substr(3,1)>="1" && passed.substr(3,1)<="8" ){
               
               int a,b,c,d;
               
               a=passed[0]-'a';
               b=passed[1]-'1';
               c=passed[2]-'a';
               d=passed[3]-'1';
               
               if(isValidMove(board[b][a],a,b,c,d)==1 && ((move%2==0 && isWhiteMove(b,a)==1)||(move%2==1 && isBlackMove(b,a)==1))){
                  update();
                  board[d][c] = board[b][a];
                  board[b][a] = 0;
                  printb();
                  move++;       
                  if(isGameOver()==1){
                     printf("***********Game is over*********************");
                  }{
                     if(board[d][c]==100 && isAtLast(board[d][c],d)==1){
                          int replacement;
                          printf("\nenter replacement options \n");
                          printf("enter 300 for knight\n");
                          printf("enter 305 for bishop\n");
                          printf("enter 500 for rook \n");
                          printf("enter 900 for queen \n");
                          scanf("%d",&replacement);
                          if(replacement==300 ||replacement==305 ||replacement==500 ||replacement==900 ){
                              board[d][c]=replacement;
                              printb();
                              }
                     }              
                     if(board[d][c]==-100 && isAtLast(board[d][c],d)==1){
                          int replacement;
                          printf("\nenter replacement options \n");
                          printf("enter -300 for knight\n");
                          printf("enter -305 for bishop\n");
                          printf("enter -500 for rook \n");
                          printf("enter -900 for queen \n");
                          scanf("%d",&replacement);
                          if(replacement==-300 ||replacement==-305 ||replacement==-500 ||replacement==-900 ){
                               board[d][c]=replacement;
                               printb();
                               }
                     }             
                  }             
               }else{
                  cout<<"move is invalid"<<endl<<endl;      
               }

          }
       if(passed.substr(0,5)=="print"){
           printb();                               
       }
       if(passed.substr(0,3)=="new"){
           setup();     
           printb();                         
       }
    }    
}
