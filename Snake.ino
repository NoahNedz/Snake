//row definitions
int row0 = PD_0;
int row1 = PD_1;
int row2 = PD_2;
int row3 = PD_3;
int row4 = PE_1;
int row5 = PE_2;
int row6 = PE_3;
int row7 = PB_2;

//column definitions
int col0 = PB_5;
int col1 = PB_0;
int col2 = PB_1;
int col3 = PE_4;
int col4 = PE_5;
int col5 = PB_4;
int col6 = PA_5;
int col7 = PA_6;

//button definitions
int upButton = PB_3;
int downButton = PC_4;
int leftButton = PF_3;
int rightButton = PF_2;

//button states
int direction = 3;
int newDirection = 5;
int oldDirection = 5;

//position states
int positionX = 0;
int positionY = 0;
int oldPosX = 0;
int oldPosY = 0;

//snake food location
int foodX;
int foodY;

//increment every frame, larger = slower movement
int moveCounter = 0;

//increment counters
int i = 1;
int j = 1;


//dot matrix values
int matrix[8][8];
int matrixTail[8][8];
int matrixTailX[64];
int matrixTailY[64];

//tail length
int tailLength = 0;



void setup() {
  // put your setup code here, to run once:
  
  pinMode(row0,OUTPUT);
  pinMode(row1,OUTPUT);
  pinMode(row2,OUTPUT);
  pinMode(row3,OUTPUT);
  pinMode(row4,OUTPUT);
  pinMode(row5,OUTPUT);
  pinMode(row6,OUTPUT);
  pinMode(row7,OUTPUT);
  pinMode(col0,OUTPUT);
  pinMode(col1,OUTPUT);
  pinMode(col2,OUTPUT);
  pinMode(col3,OUTPUT);
  pinMode(col4,OUTPUT);
  pinMode(col5,OUTPUT);
  pinMode(col6,OUTPUT);
  pinMode(col7,OUTPUT);
  
  pinMode(upButton,INPUT);
  pinMode(downButton,INPUT);
  pinMode(leftButton, INPUT);
  pinMode(rightButton,INPUT);
  
  clearMatrix();
  
  generateFood();
}

void loop() {
  readButtons();
 
  if(moveCounter > 64){//increase this to slow snake movement
    clearMatrix();
    moveSnake();
    matrix[foodX][foodY] = 65; //place food
    moveCounter = 0;
    if(matrix[positionX][positionY] == 65){tailLength++;generateFood();}//if at food, react appropriately
    }
  
  writeMatrix();//update frame
  moveCounter++;

}

void writeLED(int col, int row, int value){
    
  if(value == 0){
    digitalWrite(col0,LOW);
    digitalWrite(col1,LOW);
    digitalWrite(col2,LOW);
    digitalWrite(col3,LOW);
    digitalWrite(col4,LOW);
    digitalWrite(col5,LOW);
    digitalWrite(col6,LOW);
    digitalWrite(col7,LOW);

    digitalWrite(row0,HIGH);
    digitalWrite(row1,HIGH);
    digitalWrite(row2,HIGH);
    digitalWrite(row3,HIGH);
    digitalWrite(row4,HIGH);
    digitalWrite(row5,HIGH);
    digitalWrite(row6,HIGH);
    digitalWrite(row7,HIGH);
    
  }
  else{
    
    switch(col){
      case 1:
        digitalWrite(col0,HIGH);
        break;  
      case 2:
       digitalWrite(col1,HIGH);   
        break;
      case 3:
        digitalWrite(col2,HIGH);
        break;
      case 4:
        digitalWrite(col3,HIGH);      
        break;
      case 5:
        digitalWrite(col4,HIGH);
        break;
      case 6:
        digitalWrite(col5,HIGH);
        break;
      case 7: 
        digitalWrite(col6,HIGH);
        break;
      case 8 :
        digitalWrite(col7,HIGH);
        break;      
       }
    
    switch(row){
         
      case 1:
        digitalWrite(row0,LOW);
        break;
      case 2:
        digitalWrite(row1,LOW);
        break;
      case 3:
        digitalWrite(row2,LOW);
        break;
      case 4:
        digitalWrite(row3,LOW);
        break;
      case 5:
        digitalWrite(row4,LOW);
        break;
      case 6:
        digitalWrite(row5,LOW);
        break;
      case 7: 
        digitalWrite(row6,LOW);
        break;
      case 8 :
        digitalWrite(row7,LOW);
        break;      
    }
  }
  delayMicroseconds(20);
}

void writeMatrix(){
  i = 1; j = 1;
  while(i < 9){
    while(j< 9){
      writeLED(i,j,matrix[i-1][j-1]);
      j++;
    } 
    j = 1;
    i++;
  }
}

void clearMatrix(){
  i = 0; j = 0;
  while(i < 8){
    while(j< 8){
      matrix[i][j] = 0;
      matrixTail[i][j] = 0;
      j++;
    } 
    j = 0;
    i++;
  }
  writeMatrix();
}

void readButtons(){
  if(digitalRead(upButton)){
    newDirection = 4;
  }
  else if(digitalRead(downButton)){
    newDirection = 3;
  }
  else if(digitalRead(leftButton)){
    newDirection = 2;
  }
  else if(digitalRead(rightButton)){
    newDirection = 1;
  }
  if(newDirection != direction){
    oldDirection = direction;
    direction = newDirection;
  }
  
}

void generateFood(){
  foodX = random(7);//create a random value 0 to 7
  foodY = random(7);
  while(matrix[foodX][foodY] > 2){//find a spot where the snake isnt
    foodX = random(7);
    foodY = random(7);
  }
  matrix[foodX][foodY] = 65;
}

void lose(){
  positionX = 0;
  positionY = 0;
  direction = 3;
  oldDirection = 5;
  newDirection = 5;
  tailLength = 0;
  clearMatrix();  
}

void calcTail(){
  i = 62; 

  //shift the array to the right by one
  while(i >= 0){
    matrixTailX[i+1] = matrixTailX[i]; 
    matrixTailY[i+1] = matrixTailY[i];
    i--;
  }
  //populate first matrix value with the last position
  matrixTailX[0] = oldPosX;
  matrixTailY[0] = oldPosY;

  //fill the matrix with the valid tail locals
  i = 0;
  while(i < tailLength and tailLength > 0){
    matrix[matrixTailX[i]][matrixTailY[i]] = 2;
    i++;
  }
}

void moveSnake(){

  oldPosX = positionX; oldPosY = positionY;
  
  //check to see if turned back on itself
  if(direction == 1 && oldDirection == 2){lose();return;}
  if(direction == 2 && oldDirection == 1){lose();return;}
  if(direction == 3 && oldDirection == 4){lose();return;}
  if(direction == 4 && oldDirection == 3){lose();return;}
  
  if(direction == 1){
    positionX++;
  }
  else if(direction == 2){
    positionX--;
  }
  else if(direction == 3){
    positionY--;
  }
  else if(direction == 4){
    positionY++;
  }

  //going out of bounds causes player to lose
  if(positionX > 7){lose();}
  if(positionY > 7){lose();}
  if(positionX < 0){lose();}
  if(positionY < 0){lose();}
  if(matrix[positionX][positionY] == 2){lose();return;}
  
  
  matrix[positionX][positionY] = 1;
  calcTail();
}
  
