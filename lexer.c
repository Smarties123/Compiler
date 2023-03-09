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

typedef enum {RESWORD, ID , INT , SYMBOL, STRING, EOFile, ERR} TokenTypes;

const char* keywords[22] = {
        "class", "constructor", "function", "method", "field",
        "static", "var", "int", "char", "boolean", "void", "true",
        "false", "null", "this", "let", "do", "if", "else", "while", "return"
    };


typedef struct {
    TokenTypes t;
    char value[128];
} Token;


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

  fp = fopen("Ball.jack_tokens.txt", "r");

  if (fp == NULL) {
    printf("Error opening file");
    return 0; //error
    }

    return 1; //success
}


// Get the next token from the source file
Token GetNextToken()
{

  Token t;

  int c = getc(fp);

  // may have to change *current_char into getc(fp)
  //t.type = ERR;
  
  // char c = *current_char;

  // Skip white space and comments
  while (isspace(c) || c == '/') {
      if (c == '/') {
          // Check for comment
          //advance();
          c = getc(fp);
          if (c == '/') {
              // Line comment - skip until end of line
              while (c != '\n' && c != EOFile) {
                  //advance();
                  c = getc(fp);
              }
          
          } else if (c == '*') {
              // Block comment - skip until end of block
              //advance();
              c = getc(fp);
              int prev =' ';
              while (c != '\0') { //while (c != EOFile)
                  if (c == '*') { //if (prev == '*' && c == '/') 
                      //advance();
                      c = getc(fp);
                      if (c == '/') {
                          //advance();
                          c = getc(fp);
                          break;
                      }
                  } else {
                      c = getc(fp);
                  }
              }
          




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
                    printf("Error: Unterminated block comment\n");
                    t.t = ERR;
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
    if (c == EOFile) {
        strcpy(t.value, "EOFile");
        t.t = EOFile;
        return t;
    }

    // Check if Character is a letter
    if (isalpha(c) || c == '_') {
        char temp[128];
        int i = 0;
        while (isalnum(c) || c == '_') {
            temp[i++] = c;
            c = getc(fp);
        }
        temp[i] = '\0';
        ungetc(c, fp);

        for (int j = 0; j < NUM_KEYWORDS; j++) {
            if (strcmp(temp, keywords[j]) == 0) {
                strcpy(t.value, temp);
                t.t = j;
                return t;
            }
        }
        strcpy(t.value, temp);
        t.t = id;
        return t;
    }

    // Check if Character is a digit
    if (isdigit(c)) {
        char temp[128];
        int i = 0;
        while (isdigit(c)) {
            temp[i++] = c;
            c = getc(fp);
        }
        temp[i] = '\0';
        ungetc(c, fp);
        strcpy(t.value, temp);
        t.t = number;
        return t;
    }

    // Check for symbols
    for (int j = 0; j < NUM_SYMBOLS; j++) {
        if (c == symbols[j].c) {
            t.t = symbols[j].t;
            strcpy(t.value, symbols[j].s);
            return t;
        }
    }

    // Invalid character
    printf("Error: Invalid character %c\n", c);
    t.t = ERR;
    return t;
}

    






























 






// peek (look) at the next token in the source file without removing it from the stream


// Token PeekNextToken ()
// {
//   Token t;
  
//   nextToken = GetNextToken(t)


//   //t.t = ERR;
//   return nextToken;  
// }

// Token PeekNextToken(Lexer* lexer) {
//     Token* nextToken = GetNextToken(lexer);
//     lexer->pos--;
//     lexer->currentPos--;
//     Token peekedToken = *nextToken;
//     free(nextToken);
//     return peekedToken;
// }





// // clean out at end, e.g. close files, free memory, ... etc
// int StopLexer ()
// {
// 	return 0;
// }

// int StopLexer(Lexer* lexer) {
//     if (lexer == NULL) {
//         return 1;
//     }
//     if (lexer->inputStream != NULL) {
//         fclose(lexer->inputStream);
//     }
//     free(lexer);
//     return 0;
// }



// // do not remove the next line
// #ifndef TEST
// int main ()
// {
// 	// implement your main function here
//   // NOTE: the autograder will not use your main function

  
// 	return 0;
// }
// // do not remove the next line
// #endif










// Token GetNextToken()
// {
//     Token t;
//     int c = getc(fp);

//     // Skip white space and comments
//     while (isspace(c) || c == '/') {
//         if (c == '/') {
//             // Check for comment
//             c = getc(fp);
//             if (c == '/') {
//                 // Line comment - skip until end of line
//                 while (c != '\n' && c != EOFile) {
//                     c = getc(fp);
//                 }
//             } else if (c == '*') {
//                 // Block comment - skip until end of block
//                 c = getc(fp);
//                 int prev = ' ';
//                 while (c != EOFile) {
//                     if (prev == '*' && c == '/') {
//                         break;
//                     }
//                     prev = c;
//                     c = getc(fp);
//                 }
//                 if (c == EOFile) {
//                     printf("Error: Unterminated block comment\n");
//                     t.t = ERR;
//                     return t;
//                 }
//                 // Advance to the next character after the end of the block comment
//                 c = getc(fp);
//             } else {
//                 // Not a comment
//                 ungetc(c, fp);
//                 break;
//             }
//         } else {
//             c = getc(fp);
//         }
//     }

//     // Check for EOF
//     if (c == EOFile) {
//         strcpy(t.value, "EOFile");
//         t.t = EOFile;
//         return t;
//     }

//     // Check if Character is a letter
//     if (isalpha(c) || c == '_') {
//         char temp[128];
//         int i = 0;
//         while (isalnum(c) || c == '_') {
//             temp[i++] = c;
//             c = getc(fp);
//         }
//         temp[i] = '\0';
//         ungetc(c, fp);

//         for (int j = 0; j < NUM_KEYWORDS; j++) {
//             if (strcmp(temp, keywords[j]) == 0) {
//                 strcpy(t.value, temp);
//                 t.t = j;
//                 return t;
//             }
//         }
//         strcpy(t.value, temp);
//         t.t = id;
//         return t;
//     }

//     // Check if Character is a digit
//     if (isdigit(c)) {
//         char temp[128];
//         int i = 0;
//         while (isdigit(c)) {
//             temp[i++] = c;
//             c = getc(fp);
//         }
//         temp[i] = '\0';
//         ungetc(c, fp);
//         strcpy(t.value, temp);
//         t.t = number;
//         return t;
//     }

//     // Check for symbols
//     for (int j = 0; j < NUM_SYMBOLS; j++) {
//         if (c == symbols[j].c) {
//             t.t = symbols[j].t;
//             strcpy(t.value, symbols[j].s);
//             return t;
//         }
//     }

//     // Invalid character
//     printf("Error: Invalid character %c\n", c);
//     t.t = ERR;
//     return t;
// }
