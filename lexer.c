/************************************************************************
University of Leeds
School of Computing
COMP2932- Compiler Design and Construction
Lexer Module

I confirm that the following code has been developed and written by me and it is entirely the result of my own work.
I also confirm that I have not copied any parts of this program from another person or any other source or facilitated someone to copy this program from me.
I confirm that I will not publish the program online or share it with anyone without permission of the module leader.

Student Name:
Student ID:
Email:
Date Work Commenced:
*************************************************************************/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "lexer.h"


// YOU CAN ADD YOUR OWN FUNCTIONS, DECLARATIONS AND VARIABLES HERE


const char* keywords[] = {
        "class", "constructor", "function", "method", "field",
        "static", "var", "int", "char", "boolean", "void", "true",
        "false", "null", "this", "let", "do", "if", "else", "while", "return"
    };


char symbols[] = { '(', ')', '[', ']', '{', '}', ',', ';', '=', '.', '+', 
'-', '*', '/', '&', '|', '~', '<', '>' };

char fileName[] = {"Ball.Jack"};
// symbols[0]=('(','/0')
// if(c==symbols[0][0])


FILE* fp;


// IMPLEMENT THE FOLLOWING functions
//***********************************

// Initialise the lexer to read from source file
// file_name is the name of the source file
// This requires opening the file and making any necessary initialisations of the lexer
// If an error occurs, the function should return 0
// if everything goes well the function should return 1
int InitLexer (char* file_name)

{

  fp = fopen(file_name, "r"); // should this be the .jack file

  if (fp == NULL) {
    printf("Error opening file");
    return 0; //error
    }

    return 1; //success
}


// Get the next token from the source file
Token GetNextToken() {

  char prev;

  Token t;

  int c = getc(fp);

  int lineNumber = 0;

  // may have to change *current_char into getc(fp)
  //t.type = ERR;
  
  // char c = *current_char;
  while(isspace(c)) {
      if (c == '\n') {
        lineNumber += 1;
      }
      c = getc(fp);
    }
  

 
  while (c == '/') {
      // Check for comment
      //c = getc(fp);
      //printf("%c\n", c);
    // while (isspace(c)) {
    // c = getc(fp);
    // }
    c = getc(fp);
    
    if (c == '/') { // I think it not exiting this if statement when it finishes the while loop
      // Line comment - skip until end of line
      while (c != '\n')  { // do new line after
      // if (c == -1) {
      //   t.ln = lineNumber;
      //   strcpy(t.lx, "Error: unexpected eof in comment");
      //   t.tp = ERR;
      //   exit(0);
      // }
        c = getc(fp);
        // printf("%c",c);
        //break;
      }
      lineNumber += 1;
      c = getc(fp);
      //break;
      //printf("%c", c);
  } else if (c == '*') {
      // Block comment - skip until end of block
      //printf("A");
      //c = getc(fp);
      while (c != -1) {
        // c = getc(fp);
        if (c == '\n') {
          lineNumber += 1;
        }
        if (prev == '*' && c == '/') {
          //prev = c;
          // c = getc(fp);
          // printf("%c", prev);
          // printf("%c", c);
          
          break;
        }
        prev = c; // do i need this
        c = getc(fp);
        // printf("%c" ,prev);
        // exit(1);
      } 
      // lineNumber += 1;
      prev = c;
      c = getc(fp);
      // printf("%c", c);
    }else {
      // Not a comment
        ungetc(c, fp);
        break;
      }
    
    while(isspace(c)) {
      if (c == '\n') {
        lineNumber += 1;
      }
      c = getc(fp);
    }
  }
  // printf("%c", prev);
  // printf("%c", c);


  




    

    
  

    // Check for EOF
  if (c == -1) {
    t.tp = EOFile;
    strcpy(t.lx, "End of File");
    t.ln = lineNumber;
    return t;
  }

  char temp[128];
  int i = 0;

  // Check if Character is a letter
  
  if (isalpha(c)) {

    while (isalpha(c)) {
      temp[i] = c;
      i ++;
      c = getc(fp);
    }
    temp[i] = '\0';


    for (int j = 0; j< 1; j++) {
      if (strcmp(temp, keywords[j]) == 0) {
        if (strcmp(temp, keywords[j]) == 0) {
          t.tp = RESWORD;
          return t;
        } else {
          t.tp = ID;
          return t;
        }
      }
    }
    } else if (isdigit(c)) {

        while (isdigit(c)) {
        temp[i] = c;
        i += 1;
        c = getc(fp);
      }
      //temp[i] = '/0'
    }
    // if(c == '"') {
    // // Start building the lexeme by adding the opening quote
    // // char lexeme[MAX_LEXEME_LENGTH];
    // // int lexemeLength = 0;
    // temp[i++] = c;

    // for (int j = 0; j< 1; j++) {
    //   if (strcmp(temp, keywords[j]) == 0) {
    //     if (strcmp(temp, keywords[j]) == 0) {
    //       t.tp = RESWORD;
    //       return t;
    //     } else {
    //       t.tp = ID;
    //       return t;
    //     }
    //   }
    // }

  



  // Check for literal String f C is a quote ("), it may be the start of a literal string


  if (c == '"') {
    // Start building the lexeme by adding the opening quote
    // char lexeme[MAX_LEXEME_LENGTH];
    // int lexemeLength = 0;
    temp[i++] = c;

    // Keep reading characters until a closing quote is found or the lexeme exceeds the maximum length
    while ((c != -1) && (c != '\0')) {
      if (i < 128) { // or is it 128 - 1
        temp[i] = c;
        i += 1;
        c = getc(fp);
      } else {
        // Error: string literal is too long
        strcpy(t.lx, "Literal String to Long");
        exit(1);
      }

      // Check for closing quote to end the string literal
      if (c == '"') {
        temp[i++] = c;
        return t;
      }
    }

    // Error: string literal was not terminated
    strcpy(t.lx, "Literal String Was Not Terminated");
    exit(1);
    }










  //Check for symbols
  // for (int j = 0; j < 1; j++) {
  //   if (strcmp(c, symbols[j])) {
  //   t.tp = SYMBOL;
  //   return t;
  // }
  // }



  // Invalid character
  strcpy(t.lx, "Error: illegal symbol in source file");
  t.tp = ERR;
  lineNumber++;
  //strcpy(t.fl, "IllegalSymbol.jack");
  t.ln = lineNumber;
  return t;
}



    



//peek (look) at the next token in the source file without removing it from the stream


Token PeekNextToken ()
{
  Token t;

  int c = getc(fp);
  

  //t.tp = ERR;

  // used to keep track of curent position
  int start_column;
  int start_line;

  // start_column = column;
  // start_line = line;

  c = getc(fp);

  while (isspace(c)) {
    if (c == '\n') {
      start_line++;
      start_column = 0;
    } else {
      start_column++;
    }
    c = fgetc(fp);
  }

  if (c == EOF) {
    t.tp = EOFile;
    return t;
  }

  ungetc(c, fp);
  // column = start_column;
  // line = start_line;


  t = GetNextToken();
  return t;
}


// clean out at end, e.g. close files, free memory, ... etc
int StopLexer ()
{
  if (fp == NULL) {
    return 0;
  }

  fclose(fp);
  fp = NULL;
  return 1;
}



// do not remove the next line
#ifndef TEST

char* TokenTypeString (TokenType t)
{
	switch (t)
	{
		case RESWORD: return "RESWORD";
		case ID: return "ID";
		case INT: return "INT";
		case SYMBOL: return "SYMBOL";
		case STRING: return "STRING";
		case EOFile: return "EOFile";
		case ERR: return "ERR";
		default: return "Not a recognised token type";
	}

}

int main ()
{
	// implement your main function here
  // NOTE: the autograder will not use your main function



  setbuf(stdout, NULL);
  //fprintf(stdout, "Give the JACK File!");
  //gets(fileName);


  // InitLexer("Ball.jack");
  // InitLexer("IllegalSymbol.jack");
  //InitLexer("Empty.jack");
  // InitLexer("OnlyComments.jack");
  InitLexer("EoflnComment.jack");




  //c = getc(stdin);
  //fp = fopen();
  Token t;

  t = GetNextToken();
  strcpy(t.fl, "EofInComment.jack");

  printf ("<%s, %i, %s, %s>\n", t.fl, t.ln , t.lx, TokenTypeString(t.tp));

  
	return 0;
}
// do not remove the next line
#endif




