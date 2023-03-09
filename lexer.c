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


const char* keywords[22] = {
        "class", "constructor", "function", "method", "field",
        "static", "var", "int", "char", "boolean", "void", "true",
        "false", "null", "this", "let", "do", "if", "else", "while", "return"
    };



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

  fp = fopen("Ball.jack_tokens.txt", "r"); // should this be the .jack file

  if (fp == NULL) {
    printf("Error opening file");
    return 0; //error
    }

    return 1; //success
}


// Get the next token from the source file
Token GetNextToken() {

  Token t;

  int c = getc(fp);

  // may have to change *current_char into getc(fp)
  //t.type = ERR;
  
  // char c = *current_char;

 
  while (isspace(c) || c == '/') {
    if (c == '/') {
      // Check for comment
      c = getc(fp);
      if (c == '/') {
        // Line comment - skip until end of line
        while (c != '\n' && c != EOFile) {
          c = getc(fp);
        }
    } else if (c == '*') {
        // Block comment - skip until end of block
        c = getc(fp);
        int prev = ' ';
        while (c != EOFile) {
          if (prev == '*' && c == '/') {
            break;
          }
          prev = c;
          c = getc(fp);
        }
        if (c == EOFile) {
          strcpy(t.lx, "Error: unexpected eof in comment");
          return t;
        }
        // Advance to the next character after the end of the block comment
        c = getc(fp);
      } else {
        // Not a comment
        ungetc(c, fp);
        break;
      }
    } else {
        c = getc(fp);
      }
  }







    // Check for EOF
  if (c == -1) {
    strcpy(t.tp, EOFile);
    return t;
  }

  char temp[128];
  int i = 0;

  // Check if Character is a letter
  
  if (isalpha(c)) {

  while (isalpha(c)) {
    temp[i] = c;
    i += 1;
    c = getc(fp);
  }
  temp[i] = '/0';


  for (int j = 0; j< 1; j++) {
    if (strcmp(temp, keywords[j]) == 0) {
      if (strcmp(temp, keywords[j] == 0)) {
        strcpy(t.tp, RESWORD);
        return t;
      } else {
        strcpy(t.tp, ID);
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
    temp[i] = '/0'
  }


    for (int j = 0; j< 1; j++) {
      if (strcmp(temp, keywords[j]) == 0) {
        if (strcmp(temp, keywords[j] == 0)) {
          strcpy(t.tp, RESWORD);
          return t;
        } else {
          strcpy(t.tp, ID);
          return t;
        }
      }
    }
  



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
        i += 1
        c = getc(fp)
      } else {
        // Error: string literal is too long
        strcpy(t.lx, ERR);
        exit(1);
      }

      // Check for closing quote to end the string literal
      if (c == '"') {
        temp[i++] = c;
        return t;
      }
    }

    // Error: string literal was not terminated
    strcpy(t.lx, ERR);
    exit(1);
    }












  // Check for symbols
  for (int j = 0; j < NUM_SYMBOLS; j++) {
      if (c == symboif (c == -1) {
    strcpy(t.tp, EOFile);
    return t;
  }



  // Invalid character
  strcpy(t.lx, "Error: illegal symbol in source file");
  return t;
  }
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

  start_column = column;
  start_line = line;

  c = getc(fp);

  while (isspace(c)) {
    if (c == '\n') {
      line++;
      column = 0;
    } else {
      column++;
    }
    c = fgetc(fp);
  }

  if (c == EOF) {
    strcpy(t.tp, EOFile);
    return t;
  }

  ungetc(c, fp);
  column = start_column;
  line = start_line;

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
int main ()
{
	// implement your main function here
  // NOTE: the autograder will not use your main function

  
	return 0;
}
// do not remove the next line
#endif




