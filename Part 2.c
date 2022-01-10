/* Logic Homework 3, Part 2 */
/* Team Number: 31 */
/* Team Members:
1. Anirudh A <2018B4A70936H>
2. Aswath Vinayak K <2018B4A70713H>
3. Deepti Kumar <2018B5A77090H>
*/


#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#include<math.h>

#define MAX 100 // macro indicating the maximum size of stack




/*********************/
/*******stack operations**********/

// Inserting data onto top of stack. Takes as arguments the data to be pushed, the array used for implementing the stack and an integer pointer referencing the index of the top of that stack.

void push(char data, char stack[], int *top)  
{ 
   if(*top != MAX-1) // if stack is not full
   {  *top = *top + 1;   
      stack[*top] = data;
   } 	
   else 
   {
      printf("Could not insert data, Stack is full.\n");
   }
}


// Removing element from top of stack. Takes as arguments the array used for implementing the stack and an integer pointer referencing the index of the top of that stack. Returns the popped character.

char pop(char stack[], int *top) 
{
   char data;
	
   if(*top != -1) //checking whether stack contains some elements
   {
      data = stack[*top];
      *top = *top - 1;   
      return data;
   }

   else 
   {
      printf("Could not retrieve data, Stack is empty.\n");
   }
}

// NOTE:
// A pointer to the variable top is passed instead of passing the top variable itself. This is done to ensure top is passed as reference and any modifications to the top variable 
// would be reflected in the calling function



/*********************/
/******* implementation **********/

// function to implement the solution for Part 1. Takes as arguments the number of atoms, the character array to store the completely parenthesized input formula and the array to store the valuation of the atoms
// returns the final result of evaluating the formula (either T or F)

char eval_formula(int n, char formula[], char operand_val[])    
{
   //printf("fucntion called") ;
   char operand_stack[MAX];  // character array to implement operand stack
   char operator_stack[MAX]; // character array to implement operator stack 
   int operand_top = -1; // integer pointing to the top of the operand stack
   int operator_top = -1;  // integer pointing to the top of the operand stack
   
   // Complete the implementation function to calculate the final valuation of the formula
   //separating into stacks
   for(int i=0;i<strlen(formula);i++)
   {
    // printf("  enetered loop %d %c \n" , i, formula[i]) ;
      if(formula[i]=='V'||formula[i]=='~'||formula[i]=='>'||formula[i]=='^'||formula[i]=='(')
        { push(formula[i],operator_stack,&operator_top);
        // printf("check 1 \n") ;
        }
      else if(formula[i]=='F'||formula[i]=='T')
         {push(formula[i],operand_stack,&operand_top);
        // printf("check 2 \n" ) ;
         }
      if(formula[i]==')')
      {
      //process
        //printf("  encountered loop ) \n ") ;
          for(int i=0;i<strlen(operator_stack);i++)
          {
            char op=pop(operator_stack, &operator_top);
            // printf("popping after encountering (  %c \n" , op) ;
            if(op=='(')
               break;
            else if(op=='^')
            {
               char a=pop(operand_stack,&operand_top);
               char b=pop(operand_stack,&operand_top);
               if(a=='T'&&b=='T')
                  push('T',operand_stack,&operand_top);
               else
                  push('F',operand_stack,&operand_top);
            }
            else if(op=='V')
            {
               char a=pop(operand_stack,&operand_top);
               char b=pop(operand_stack,&operand_top);
               if(a=='F'&&b=='F')
                  push('F',operand_stack,&operand_top);
               else
                  push('T',operand_stack,&operand_top);
            }
            else if(op=='>')
            {
               char a=pop(operand_stack,&operand_top);
               char b=pop(operand_stack,&operand_top);
               if(a=='F'&&b=='T')
                  push('F',operand_stack,&operand_top);
               else
                  push('T',operand_stack,&operand_top);
            }
            else if(op=='~')
            { char a=pop(operand_stack,&operand_top);
               if(a=='F')
                  push('T',operand_stack,&operand_top);
               else
                  push('F',operand_stack,&operand_top);
            }
          }
      }
   }
   char A = pop(operand_stack, &operand_top) ;
  // printf( "Valuation: %c \n" , A );
   return A ;
   
}
// function to get the truth valuations
void binary(int n , char b[] , const int m )
{

    
    int a[m] ;
    for (int k = 0  ; k < m ; k++) 
    {
        a[k] = 0 ;
    }
     int i ;
     
     
    for( i=0;n>0;i++)    
    {    
        a[i]=n%2;    
        n=n/2;    
    }    
    int j =0 ;

     for(i = m-1 ;i>=0;i--, j++)    
    {    
           
           if(a[i] == 0 )
           {
               b[j] = 'F' ;
           } 

           else if(a[i] == 1) b[j] = 'T' ;
    }
    b[j] = '\0' ;
    
}

// function to generate all truth values
void truth_values(int n , char formula[]  )
{
   const int N = pow(2, n) ;
   char sub[MAX], valuation[N];
   char operand_val[10]; // array to store the valuation of operands (either T or F)
   
   char cnf[MAX] = "(" , buffer[10] ;
   
  
    int countF = 0 , countT = 0 ;
     // if there is a single valuation = F countV is incremented and the formula is invalid, if T then countS is incremented and formula is satisfiable 
   for(int i = 0 ; i < pow(2, n) ; i++  )
   {
       //getting the operand value for each line in truth table
        
       binary(i , operand_val , n )  ; 
       //itoa(i, operand_val, n);
       //printf("%d line in truth table %s \n" , i+1 , operand_val) ;
       strcpy(sub,formula);
       //converting operands to TF 1 2 3  TFT
        for(int i=0;i<strlen(sub);i++)

        {
            for(int j=1;j<=n;j++)
            {
                 if(sub[i]==((char)(j+48)))
                sub[i]=operand_val[j-1];
            }
        }
       // printf("sub after operand_val substitute: %s \n" , sub) ;
        valuation[i] = eval_formula(n,sub,operand_val);
        //printf("%s    %c \n ",operand_val, valuation[i]) ;
        if(valuation[i] == 'F')
        {
           countF++ ;
            // valuation taken in consideration for cnf form
            strcat(cnf,"(") ;
            for(int l = 0 ; l < strlen(operand_val); l++)
            {
               itoa(l+1, buffer, 10 );
               if(operand_val[l] == 'F')
               {
                 
                  strcat(cnf,buffer);
               }
               else
               {
                  strcat(cnf,"(~") ;
                  strcat(cnf, buffer); 
                  strcat(cnf, ")") ;
               }
               if( l+1 == strlen(operand_val)) strcat(cnf,")") ;
               else strcat(cnf, "v" ) ;

            }        
            if(i+1== pow(2,n)) strcat(cnf, ")" ) ;
               else strcat(cnf, "^" ) ;
        }
        else if(valuation[i] == 'T')
        {
           countT++ ;
           if(i+1 == pow(2,n)){

              cnf[strlen(cnf)-1] =')' ;
           }
        }
        
        

   }
  
   if (countT != 0) printf("Formula is satisfiable \n") ;
   else printf("Formula is not satisfiable \n ");
   if(countF ==  0) {
      printf("Formula is valid \n" ) ;
      printf("(T) \n") ;
   }
   else{
      printf("Formula is not valid \n") ;
      printf("%s \n" , cnf) ;
   }
   
     
}



/*********************/
/********main function**********/

int main()
{  
   int n; // number of operands
   char formula[MAX]; // character array to store the input formula
  
   char *temp;
   
   // Complete the main function to get the inputs and call the implementation function
   printf("Enter number of operands \n");
   scanf("%d",&n);
   printf("Enter formula \n");
    fflush(stdin);
   gets(formula);
  //printf("Enter values \n");
  // gets(operand_val);
   
   
  // printf("This is after the operand loop \n");
  //printf("%s",sub);
   truth_values(n , formula) ;
   
   // printf("This is after eval sub is called \n");

    return 0;
}