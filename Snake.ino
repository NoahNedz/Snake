
int rowA = PF_4;
int rowB = PD_7;
int rowC = PD_6;

int colA = PC_7;
int colB = PC_6;
int colC = PC_5;

int upButton = PB_3;
int downButton = PC_4;
int leftButton = PF_3;
int rightButton = PF_2;
int buttonBounce = 0;

int direction = 0;
int positionX = 5;
int positionY = 5;
int moveCounter = 0;

int i = 1;
int j = 1;
int matrix[8][8];

void setup() {
  // put your setup code here, to run once:

pinMode(rowA,OUTPUT);
pinMode(rowB,OUTPUT);
pinMode(rowC,OUTPUT);
pinMode(colA,OUTPUT);
pinMode(colB,OUTPUT);
pinMode(colC,OUTPUT);
pinMode(upButton,INPUT);
pinMode(downButton,INPUT);
pinMode(leftButton, INPUT);
pinMode(rightButton,INPUT);

}

void loop() {
  readButtons();
  if(moveCounter > 9){moveSnake();moveCounter = 0;}
 writeMatrix();
 moveCounter++;
  

}

void clearAll(){
  digitalWrite(rowA,LOW);
  digitalWrite(rowB,LOW);
  digitalWrite(rowC,LOW);
  digitalWrite(colA,LOW);
  digitalWrite(colB,LOW);
  digitalWrite(colC,LOW);
}


void writeLED(int col, int row, int value){
  clearAll();
  
  switch(col){
    case 1:
      break;
    case 2:
      digitalWrite(colA,value);
      break;
    case 3:
      digitalWrite(colB,value);
      break;
    case 4:
      digitalWrite(colA,value);
      digitalWrite(colB,value);
      break;
    case 5:
      digitalWrite(colC,value);
      break;
    case 6:
      digitalWrite(colA,value);
      digitalWrite(colC,value);
      break;
    case 7: 
      digitalWrite(colB,value);
      digitalWrite(colC,value);
      break;
    case 8 :
      digitalWrite(colA,value);
      digitalWrite(colB,value);
      digitalWrite(colC,value);
      break;      
  }

  switch(row){
    case 1:
      break;
    case 2:
      digitalWrite(rowA,value);
      break;
    case 3:
      digitalWrite(rowB,value);
      break;
    case 4:
      digitalWrite(rowA,value);
      digitalWrite(rowB,value);
      break;
    case 5:
      digitalWrite(rowC,value);
      break;
    case 6:
      digitalWrite(rowA,value);
      digitalWrite(rowC,value);
      break;
    case 7: 
      digitalWrite(rowB,value);
      digitalWrite(rowC,value);
      break;
    case 8 :
      digitalWrite(rowA,value);
      digitalWrite(rowB,value);
      digitalWrite(rowC,value);
      break;      
  }
  delayMicroseconds(10000);
}

void writeMatrix(){
  i = 1; j = 1;
  while(i < 9){
    while(j< 9){
      if(matrix[i-1][j-1] == 1){
        writeLED(i,j,matrix[i-1][j-1]);
      }
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
      j++;
    } 
    j = 0;
    i++;
  }
  positionX = 0;
  positionY = 0; 
  writeMatrix();
}

void readButtons(){
  if(digitalRead(upButton)){
    direction = 1;
  }
  else if(digitalRead(downButton)){
    direction = 2;
  }
  else if(digitalRead(leftButton)){
    direction = 3;
  }
  else if(digitalRead(rightButton)){
    direction = 4;
  }
  
}

void moveSnake(){
  if(direction == 1){
    matrix[positionX][positionY] = 0;
    positionX++;
    
  }
  else if(direction == 2){
    matrix[positionX][positionY] = 0;

    positionX--;
  }
  else if(direction == 3){
    matrix[positionX][positionY] = 0;

    positionY--;
  }
  else if(direction == 4){
    matrix[positionX][positionY] = 0;

    positionY++;
  }
  if(positionX > 7){positionX = 7;}
  if(positionY > 7){positionY = 7;}
  if(positionX < 0){positionX = 0;}
  if(positionY < 0){positionY = 0;}
  matrix[positionX][positionY] = 1;
}
  
