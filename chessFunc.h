
const int pawn = 100; 
const int bishop = 305; 
const int knight = 300; 
const int rook  = 500; 
const int queen  = 900; 
const int king = 2000; 
int move=0; 
int board[8][8];
int pboard[8][8];
const int startup[8][8] = { rook, knight, bishop, queen, king, bishop, knight, rook, pawn, pawn,pawn,pawn,pawn,pawn,pawn, pawn,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
               -pawn, -pawn, -pawn, -pawn, -pawn, -pawn, -pawn, -pawn, -rook, -knight, -bishop, -queen, -king, -bishop, -knight, -rook};

void setup(void){
   int i,j;
   for(i=0;i<8;i++){
       for( j=0;j<8;j++){
            board[i][j]=startup[i][j];     
       }             
   }     
}

//if value of piece is less than 0, then it is black;
int isBlack(int i, int j){
   if(board[i][j]<0)
       return 1;
   return 0;    
}

//if value of piece is greater than 0, then it is white; 
int isWhite(int i, int j){
    if(board[i][j]>0)
         return 1; 
    return 0;     
}

//returns 1 if the character is lowercase
int isLower(string piece){
if(piece.substr(0,1)>="a" && piece.substr(0,1)<="z"){
   return 1; 
}    
return 0;
}

//returns 1 if character is uppercase
int isUpper(string piece){
if(piece.substr(0,1)>="A" && piece.substr(0,1)<="Z"){
   return 1; 
}    
return 0;
}
//checks if move is white
int isWhiteMove(int inrank,int infile){
  if(board[inrank][infile]>0) return 1; 
  return 0;                
}

//checks if move is black
int isBlackMove(int inrank, int infile){
  if(board[inrank][infile]<0) return 1; 
  return 0;                
}
//prints board
void printb(void){
  using namespace std ;
  int a,b; 
  string piece; 
  HANDLE chandle = GetStdHandle(STD_OUTPUT_HANDLE);
      cout<<setcolour(PINK,chandle)<<"     a  "<<setcolour(PINK,chandle)<<"b  "<<setcolour(PINK,chandle)<<"c  "<<setcolour(PINK,chandle)<<"d  "<<setcolour(PINK,chandle)<<"e  "<<setcolour(PINK,chandle)<<"f  "<<setcolour(PINK,chandle)<<"g  "<<setcolour(PINK,chandle)<<"h  ";
  for(a=7;a>=0;a--){
      cout<<endl;
      cout<<setcolour(PINK,chandle)<<(a+1)<<"   "; 
      for(b=0;b<8;b++){
          switch(board[a][b]){
             case 0: 
                  piece = "-";
                  break; 
             case pawn: 
                  piece ="P";
                  break;
             case knight:
                  piece ="N";
                  break; 
             case bishop: 
                  piece = "B";
                  break; 
             case rook: 
                  piece = "R";
                  break;
             case queen: 
                  piece = "Q";
                  break;
             case king: 
                  piece ="K";
                  break;
             case -pawn: 
                  piece ="p";
                  break;
             case -knight:
                  piece ="n";
                  break; 
             case -bishop: 
                  piece = "b";
                  break; 
             case -rook: 
                  piece = "r";
                  break;
             case -queen: 
                  piece = "q";
                  break;
             case -king: 
                  piece ="k";
                  break;
                                 
          }                
         if(isLower(piece)==1){
          cout<<" "<<setcolour(RED,chandle)<<piece<<" ";                     
         }
         else if(isUpper(piece)==1){
                  cout<<" "<<setcolour(GREEN,chandle)<<piece<<" ";
              }
             else{
                 cout<<" "<<setcolour(BLUE,chandle)<<piece<<" ";     
             } 
      }       
            cout<<"   "<<setcolour(PINK,chandle)<<(a+1)<<"   ";           
  }     
  cout<<endl;
      cout<<setcolour(PINK,chandle)<<"     a  "<<setcolour(PINK,chandle)<<"b  "<<setcolour(PINK,chandle)<<"c  "<<setcolour(PINK,chandle)<<"d  "<<setcolour(PINK,chandle)<<"e  "<<setcolour(PINK,chandle)<<"f  "<<setcolour(PINK,chandle)<<"g  "<<setcolour(PINK,chandle)<<"h  ";
  cout<<endl<<endl<<endl;
}

//returns absolute value
int abs(int val){
  if(val<0){
     val = -val;
  }    
  return val;
}

//checks if game is over
int isGameOver(){
  int i,j;
  int count=0;
  for(i=0;i<8;i++){
     for(j=0;j<8;j++){
        if(abs(board[i][j])==2000)
           count++;                 
     }                 
  }    
  if(count!=2)
      return 1;
  return 0;
}

//undo a move
int undo(){
   int i,j,count=0;
   for(i=0;i<8;i++){
      for(j=0;j<8;j++){
          if(board[i][j]!=pboard[i][j])
              count++;
          board[i][j]=pboard[i][j];                 
      }                 
   }
   //if there is exactly difference of two pieces, then this is the first undo
   if(count==2)
      move--;
}

//update move into pboard
int update(){
 int i, j;
 for(i=0;i<8;i++){
   for(j=0;j<8;j++){
       pboard[i][j]=board[i][j];                 
   }                 
 }    
}

//check final position
int isAtLast(int piece, int finrank){
  if(piece<0 && finrank==0){ return 1; }
  if(piece>0 && finrank==7){ return 1; }
  return 0;    
}
//checks if move is valid
int isValidMove(int piece, int infile, int inrank, int finfile, int finrank){
       if(inrank>=0 && inrank <=7 && finrank >=0 && finrank <=7 && infile>=0 && infile <=7 && finfile >=0 && finfile <=7){
          switch(piece){
            case -100: {                    //black pawn can move only one position downwards, if that position is not occupied
                 if(isBlack(finrank,finfile)==0 && isWhite(finrank,finfile)==0)
                    if(infile==finfile && inrank-finrank==1)
                       return 1; 
                 if(inrank-finrank==1 && abs(infile-finfile)==1 && isWhite(finrank,finfile)==1)
                        return 1; 
                 if(inrank==6 && infile==finfile && inrank-finrank==2)
                        return 1; 
                 return 0;
            }             
            case 100: {               //white pawn can move only one position upward
                 if(isBlack(finrank,finfile)==0 && isWhite(finrank,finfile)==0)
                    if(infile==finfile && finrank-inrank==1)
                       return 1; 
                 if(finrank-inrank==1 && abs(infile-finfile)==1 && isBlack(finrank,finfile)==1)
                        return 1; 
                 if(inrank==1 && infile==finfile && finrank-inrank==2)
                        return 1; 
                 return 0;     
            }  
            case -300:{
                 if(isBlack(finrank,finfile)==0){
                       if(abs(infile-finfile)==1){    //one horizontal movement
                          if(abs(inrank-finrank)==2){  //two vertical movements
                               return 1 ;                           
                          }               
                          return 0;               
                       }                          
                       if(abs(infile-finfile)==2){   //two horizontal movements
                          if(abs(inrank-finrank)==1){  //one vertical movement
                               return 1 ;                           
                          }               
                          return 0;                
                       }
                 }
                 return 0;
            }
            case 300:{
                 if(isWhite(finrank,finfile)==0){
                       if(abs(infile-finfile)==1){    //one horizontal movement
                          if(abs(inrank-finrank)==2){  //two vertical movements
                               return 1 ;                           
                          }               
                          return 0;               
                       }                          
                       if(abs(infile-finfile)==2){   //two horizontal movements
                          if(abs(inrank-finrank)==1){  //one vertical movement
                               return 1 ;                           
                          }               
                          return 0;                
                       }                           
                 }
                 return 0;
            }
            case -500: case 500:{
                   if(infile==finfile ){
                      int i; 
                      if(finrank>inrank){
                             for(i=inrank+1;i<finrank;i++){   //from start  position to end position
                                 if(board[i][infile]!=0)     //if any position is not vacant, move is not valid
                                       return 0;                        
                             }   
                             if((piece<0 && isBlack(finrank,finfile)==0)|| (piece>0 && isWhite(finrank,finfile)==0))            
                                return 1;
                             
                      }               
                      if(finrank<inrank){
                             for(i=inrank-1;i>finrank;i--){   //from start position to end position
                                  if(board[i][infile]!=0)    //if any position is not vacant, move is not valid
                                       return 0;                             
                             }
                             if((piece<0 && isBlack(finrank,finfile)==0)|| (piece>0 && isWhite(finrank,finfile)==0))            
                                return 1;

                      }        
                   }                  
                   else if(inrank==finrank){
                        int i;
                        if(finfile>infile){
                           for(i=infile+1;i<finfile;i++){
                               if(board[inrank][i]!=0)
                                    return 0;                             
                           }                 
                           if((piece<0 && isBlack(finrank,finfile)==0)|| (piece>0 && isWhite(finrank,finfile)==0))
                              return 1;   
                        }
                        if(finfile<infile){
                           for( i=infile-1;i>finfile;i--){
                               if(board[inrank][i]!=0)
                                     return 0;     
                           }
                           if((piece<0 && isBlack(finrank,finfile)==0)|| (piece>0 && isWhite(finrank,finfile)==0))
                              return 1;       
                        }
                   }             
                 return 0;
                 
            }
            case -305: case 305: {
                 if(abs(infile-finfile)==abs(inrank-finrank)){
                      int i;
                      if(finrank>inrank && finfile>infile){
                            for(i=1;i<(finrank-inrank);i++){
                                   if(board[inrank+i][infile+i]!=0)
                                        return 0;         
                            }         
                         if((piece<0 && isBlack(finrank,finfile)==0)|| (piece>0 && isWhite(finrank,finfile)==0))  
                           return 1; 
                      }
                      if(finrank<inrank && finfile<infile){
                            for(i=1;i<(inrank-finrank);i++){
                                   if(board[inrank-i][infile-i]!=0)
                                        return 0;                                
                            }        
                      if((piece<0 && isBlack(finrank,finfile)==0)|| (piece>0 && isWhite(finrank,finfile)==0))
                            return 1; 
                      }
                      if(finrank>inrank && finfile<infile){
                            for(i=1;i<(finrank-inrank);i++){
                                   if(board[inrank+i][infile-i]!=0)
                                        return 0;         
                            }         
                      if((piece<0 && isBlack(finrank,finfile)==0)|| (piece>0 && isWhite(finrank,finfile)==0))    
                         return 1; 
                      }
                      if(finrank<inrank && finfile>infile){
                            for(i=1;i<(inrank-finrank);i++){
                                   if(board[inrank-i][infile+i]!=0)
                                        return 0;                                
                            }        
                      if((piece<0 && isBlack(finrank,finfile)==0)|| (piece>0 && isWhite(finrank,finfile)==0))
                            return 1; 
                      }
                 }
                 return 0;
            }
            case -2000: {
                if((isBlack(finrank,finfile)==0)){
                   if(abs((inrank-finrank)*(infile-finfile))==1)  //diagonal move does not contain black piece
                      return 1 ;
                   if(inrank==finrank && abs(infile-finfile)==1)  // one move in vertical direction
                      return 1; 
                   if(infile==finfile && abs(inrank-finrank)==1)  //one move in horizontal direction
                      return 1;  
                }
                return 0;
            }
            case 2000:{
                if((isWhite(finrank,finfile)==0)){
                   if(abs((inrank-finrank)*(infile-finfile))==1)  //diagonal move does not contain black piece
                      return 1 ;
                   if(inrank==finrank && abs(infile-finfile)==1)  // one move in vertical direction
                      return 1; 
                   if(infile==finfile && abs(inrank-finrank)==1)  //one move in horizontal direction
                      return 1;  
                }
                return 0;
            }
            case -900: case 900: {
                 if(abs(infile-finfile)==abs(inrank-finrank)){
                      int i;
                      if(finrank>inrank && finfile>infile){
                            for(i=1;i<(finrank-inrank);i++){
                                   if(board[inrank+i][infile+i]!=0)
                                        return 0;         
                            }         
                         if((piece<0 && isBlack(finrank,finfile)==0)|| (piece>0 && isWhite(finrank,finfile)==0))  
                           return 1; 
                      }
                      if(finrank<inrank && finfile<infile){
                            for(i=1;i<(inrank-finrank);i++){
                                   if(board[inrank-i][infile-i]!=0)
                                        return 0;                                
                            }        
                      if((piece<0 && isBlack(finrank,finfile)==0)|| (piece>0 && isWhite(finrank,finfile)==0))
                            return 1; 
                      }
                      if(finrank>inrank && finfile<infile){
                            for(i=1;i<(finrank-inrank);i++){
                                   if(board[inrank+i][infile-i]!=0)
                                        return 0;         
                            }         
                      if((piece<0 && isBlack(finrank,finfile)==0)|| (piece>0 && isWhite(finrank,finfile)==0))    
                         return 1; 
                      }
                      if(finrank<inrank && finfile>infile){
                            for(i=1;i<(inrank-finrank);i++){
                                   if(board[inrank-i][infile+i]!=0)
                                        return 0;                                
                            }        
                      if((piece<0 && isBlack(finrank,finfile)==0)|| (piece>0 && isWhite(finrank,finfile)==0))
                            return 1; 
                      }
                 }
                   if(infile==finfile ){
                      int i; 
                      if(finrank>inrank){
                             for(i=inrank+1;i<finrank;i++){   //from start  position to end position
                                 if(board[i][infile]!=0)     //if any position is not vacant, move is not valid
                                       return 0;                        
                             }   
                             if((piece<0 && isBlack(finrank,finfile)==0)|| (piece>0 && isWhite(finrank,finfile)==0))            
                                return 1;
                             
                      }               
                      if(finrank<inrank){
                             for(i=inrank-1;i>finrank;i--){   //from start position to end position
                                  if(board[i][infile]!=0)    //if any position is not vacant, move is not valid
                                       return 0;                             
                             }
                             if((piece<0 && isBlack(finrank,finfile)==0)|| (piece>0 && isWhite(finrank,finfile)==0))            
                                return 1;

                      }        
                   }                  
                   else if(inrank==finrank){
                        int i;
                        if(finfile>infile){
                           for(i=infile+1;i<finfile;i++){
                               if(board[inrank][i]!=0)
                                    return 0;                             
                           }                 
                           if((piece<0 && isBlack(finrank,finfile)==0)|| (piece>0 && isWhite(finrank,finfile)==0))
                              return 1;   
                        }
                        if(finfile<infile){
                           for( i=infile-1;i>finfile;i--){
                               if(board[inrank][i]!=0)
                                     return 0;     
                           }
                           if((piece<0 && isBlack(finrank,finfile)==0)|| (piece>0 && isWhite(finrank,finfile)==0))
                              return 1;       
                        }
                   }             
                 return 0;
                 
            }
            default:{
               return 0;         
            }
          }            
       }
       else{
            return 0;
       }
       
}
