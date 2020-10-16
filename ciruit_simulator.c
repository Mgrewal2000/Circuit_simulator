#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<string.h>

typedef struct Node
{
   char* xInput;
   int data;

   struct Node* nextNode;
}Node;

int traverse(char* seen, Node* topNode);
void change(int data,char* val, Node* topNode);
void addVal(char* addVal, Node* currValue);
void create(int** pointerToArray, int rows,int cols);
void outputStatement(int** pointerToArray, int rows,int cols);

int main(int argc, char* argv[])
{

  FILE* f = fopen(argv[1],"r");
        if(f == NULL){
        printf("Could not open test.txt\n");
        return 1;}

  int x; //all the input variables
  int y; //all the output variables

  fscanf(f,"%*s %d", &x);
   Node* xInput = NULL;
   Node* yOutput = NULL;
   int i;
   for(i=0 ; i < x; i++)
    {

	char* placeHolderTemp =(char*) malloc(20*sizeof(char));
         fscanf(f,"%s", placeHolderTemp);

         if(xInput == NULL)
	   {
	     Node* makeNode = (Node*)malloc(sizeof(Node));
             makeNode->nextNode = NULL;
             makeNode->xInput = placeHolderTemp;
             xInput = makeNode;

	   }
	 else
	   {
             addVal(placeHolderTemp,xInput);
           }
      }
    fscanf(f,"%*s %d\n",&y);
    for(i=0 ; i < y; i++)
    {

	char* placeHolderTemp =(char*) malloc(20*sizeof(char));
         fscanf(f,"%s", placeHolderTemp);
         if(yOutput == NULL)
	   {
	     Node* makeNode = (Node*)malloc(sizeof(Node));
             makeNode->nextNode = NULL;
             makeNode->xInput = placeHolderTemp;
             yOutput = makeNode;

	   }
	 else
	   {
             addVal(placeHolderTemp,yOutput);
           }

      }
    int** rowsColsCombine = (int**)malloc((int)pow(2,x)*sizeof(int*));
    int tracker;
    for(tracker = 0; tracker <(int) pow(2,x);tracker++)
      {
	rowsColsCombine[tracker]= (int*)malloc((x + y)*sizeof(int));
      }
    create(rowsColsCombine,(int)pow(2,x),x +y);
    int numAppeared=1;
    int numRows;
    int numColumns;
    int caseStatement= 0;
    int z = 0; // keeps count of increments
    int rowsInTable = (int)pow(2,x);
    int colsInTable = x + y;

    for( numColumns = x -1; numColumns >= 0; numColumns--)
      {
	       z = 0;
        caseStatement= 0;
	         for(numRows = 0; numRows < (int)pow(2,x); numRows++)
	           {
	               if(z == numAppeared)
	                {
		                    if(caseStatement ==0){ caseStatement =1;}
                else { caseStatement = 0; }
                        z = 0;
	      }
	    rowsColsCombine[numRows][numColumns]= caseStatement;
	      z++;

	  }
	numAppeared = numAppeared *2;
      }

    int R1;
    int C1;
    for(R1 = 0; R1 < rowsInTable  ;R1++)
      {

        Node* incr = xInput;
	for(C1 = 0; C1 < colsInTable -y; C1++)
	  {
	    int sumTable = rowsColsCombine[R1][C1];

            incr->data = sumTable;
            incr = incr->nextNode;

          }
         char* operand = malloc(5*sizeof(char));
          fclose(f);
          f= fopen(argv[1],"r");
          fscanf(f,"%*[^\n]");
          fscanf(f,"\n");
          fscanf(f,"%*[^\n]");
          fscanf(f,"\n");
	 while(fscanf(f,"%s",operand)!= EOF) {

	    char* mainFirstVar = malloc(20*sizeof(char));

            fscanf(f,"%s",mainFirstVar);
            char* mainSecondVar = malloc(20*sizeof(char));
             fscanf(f,"%s",mainSecondVar);
            if(strcmp("NOT",operand)==0 )
	     {

               if(mainSecondVar[0] >= 'a' && mainSecondVar[0] <= 'z')
		 {
		   if(traverse(mainSecondVar,xInput) == -1)
		     {
		       addVal(mainSecondVar,xInput);
                     }
                 }
	       if(traverse(mainFirstVar,xInput)!= -1)
		 {
		   int notOperation = !traverse(mainFirstVar,xInput);
		   if(traverse(mainSecondVar,xInput) != -1)
                     {
                       change(notOperation,mainSecondVar,xInput);
                     }
                   else if(traverse(mainSecondVar,yOutput) != -1)
                     {
                       change(notOperation,mainSecondVar,yOutput);
                     }

                 }
	       else
		 {
		   int notOperation = !traverse(mainFirstVar,yOutput);
                     if(traverse(mainSecondVar,xInput) != -1)
                     {
                       change(notOperation,mainSecondVar,xInput);
                     }
                   else if(traverse(mainSecondVar,yOutput) != -1)
                     {
                       change(notOperation,mainSecondVar,yOutput);
                     }
                 }
             }
             if(strcmp("AND",operand)==0 )
	       {
		             int var1;
                 int var2;
                 int varResult;
                 if(traverse(mainFirstVar,xInput)!= -1){ var1 = traverse(mainFirstVar,xInput);}
                 else var1 = traverse(mainFirstVar,yOutput);
                 if(traverse(mainSecondVar,xInput)!= -1){ var2 = traverse(mainSecondVar,xInput);}
                 else var2 = traverse(mainSecondVar,yOutput);

		             varResult = var1 && var2;
                 char* heapSpaceThird = malloc(20*sizeof(char));
                 fscanf(f,"%s",heapSpaceThird);
                 if(heapSpaceThird[0] >= 'a' && heapSpaceThird[0] <= 'z')
		   {
		     if(traverse(heapSpaceThird,xInput) == -1) addVal(heapSpaceThird,xInput);


                   }

                 if(traverse(heapSpaceThird,xInput) != -1) change(varResult,heapSpaceThird,xInput);

                 else change(varResult,heapSpaceThird,yOutput);
               }

                 if(strcmp("OR",operand)==0 )
	       {
		             int var1;
                 int var2;
                 int varResult;
                 if(traverse(mainFirstVar,xInput)!= -1){ var1 = traverse(mainFirstVar,xInput);}
                 else var1 = traverse(mainFirstVar,yOutput);
                 if(traverse(mainSecondVar,xInput)!= -1){ var2 = traverse(mainSecondVar,xInput);}
                 else var2 = traverse(mainSecondVar,yOutput);

		             varResult = var1 || var2;
                 char* heapSpaceThird = malloc(20*sizeof(char));
                 fscanf(f,"%s",heapSpaceThird);
                 if(heapSpaceThird[0] >= 'a' && heapSpaceThird[0] <= 'z')
		   {
		     if(traverse(heapSpaceThird,xInput) == -1) addVal(heapSpaceThird,xInput);

                   }
                 if(traverse(heapSpaceThird,xInput) != -1) change(varResult,heapSpaceThird,xInput);
                 else change(varResult,heapSpaceThird,yOutput);
               }
                 if(strcmp("NOR",operand)==0 )
	       {
		             int var1;
                 int var2;
                 int varResult;
                 if(traverse(mainFirstVar,xInput)!= -1){ var1 = traverse(mainFirstVar,xInput);}
                 else var1 = traverse(mainFirstVar,yOutput);
                 if(traverse(mainSecondVar,xInput)!= -1){ var2 = traverse(mainSecondVar,xInput);}
                 else var2 = traverse(mainSecondVar,yOutput);

		             varResult = !(var1 || var2);//

                 char* heapSpaceThird = malloc(20*sizeof(char));
                 fscanf(f,"%s",heapSpaceThird);
                 if(heapSpaceThird[0] >= 'a' && heapSpaceThird[0] <= 'z')
		   {
		     if(traverse(heapSpaceThird,xInput) == -1) addVal(heapSpaceThird,xInput);


                   }
                 if(traverse(heapSpaceThird,xInput) != -1) change(varResult,heapSpaceThird,xInput);
                 else change(varResult,heapSpaceThird,yOutput);
               }


               if(strcmp("XOR",operand)==0 )
       {
               int var1;
                int var2;
                int varResult;
                if(traverse(mainFirstVar,xInput)!= -1){ var1 = traverse(mainFirstVar,xInput);}
                else var1 = traverse(mainFirstVar,yOutput);
                if(traverse(mainSecondVar,xInput)!= -1){ var2 = traverse(mainSecondVar,xInput);}
                else var2 = traverse(mainSecondVar,yOutput);

               varResult = var1 ^ var2;
                char* heapSpaceThird = malloc(20*sizeof(char));
                fscanf(f,"%s",heapSpaceThird);
                if(heapSpaceThird[0] >= 'a' && heapSpaceThird[0] <= 'z')
     {
               if(traverse(heapSpaceThird,xInput) == -1) addVal(heapSpaceThird,xInput);
                  }
                if(traverse(heapSpaceThird,xInput) != -1) change(varResult,heapSpaceThird,xInput);

                else change(varResult,heapSpaceThird,yOutput);
              }



                 if(strcmp("NAND",operand)==0 )
	       {
		             int var1;
                 int var2;
                 int varResult;
                 if(traverse(mainFirstVar,xInput)!= -1){

                   var1 = traverse(mainFirstVar,xInput);

                 }
                 else var1 = traverse(mainFirstVar,yOutput);
                 if(traverse(mainSecondVar,xInput)!= -1){ var2 = traverse(mainSecondVar,xInput);}
                 else var2 = traverse(mainSecondVar,yOutput);

		             varResult = !(var1 && var2);
                 char* heapSpaceThird = malloc(20*sizeof(char));
                 fscanf(f,"%s",heapSpaceThird);
                 if(heapSpaceThird[0] >= 'a' && heapSpaceThird[0] <= 'z')
		   {
		     if(traverse(heapSpaceThird,xInput) == -1) addVal(heapSpaceThird,xInput);


                   }

                 if(traverse(heapSpaceThird,xInput) != -1) change(varResult,heapSpaceThird,xInput);

                 else change(varResult,heapSpaceThird,yOutput);


               }


	 }
                Node* placeHolderTemp = yOutput;
                for(C1 = colsInTable - y; C1 < colsInTable ; C1++)
	  {
	          rowsColsCombine[R1][C1] = placeHolderTemp->data;
            placeHolderTemp = placeHolderTemp->nextNode;
          }
      }
    outputStatement(rowsColsCombine,rowsInTable,colsInTable);

  return 0;
}

int traverse(char* seen, Node* topNode)
{
  Node* node;
  for(node = topNode; node!= NULL; node= node->nextNode)
    {
      if(strcmp(node->xInput,seen) == 0)
	    {
	  return node->data;
      }
    }
  return -1;
}

void change(int data,char* val, Node* topNode)
{
    Node* placeHolder;
   for(placeHolder = topNode; placeHolder != NULL; placeHolder = placeHolder->nextNode)
    {
      if(strcmp(placeHolder->xInput,val) == 0)
	{
	  placeHolder->data = data;
          break;
        }
    }
}

void addVal(char* addVal, Node* currValue)
{
  Node* t;
  Node* sum = (Node*)malloc(sizeof(Node));

  sum->xInput = malloc(20*sizeof(char));
  strcpy(sum->xInput,addVal);
  sum->nextNode = NULL;

  for(t = currValue; t != NULL; t = t->nextNode)
    {
      if(t->nextNode == NULL)
	{
	  t->nextNode = sum;
          break;
        }
    }
}

void create(int** pointerToArray, int rows,int cols)
{
  int r;
  int c;
   for(r = 0; r < rows; r++)
      {
	       for(c = 0; c < cols; c++)
	  {
	         pointerToArray[r][c]=0;
	  }
      }
}

void outputStatement(int** pointerToArray, int rows,int cols)
{
  int r;
  int c;
   for(r= 0; r < rows; r++)
      {
	for(c = 0; c < cols; c++)
	  {
	    printf("%d ",pointerToArray[r][c]);

	  }
	printf("\n");
      }
}

