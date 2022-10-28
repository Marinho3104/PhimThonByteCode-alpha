#pragma once


#ifndef TOKEN_H
#define TOKEN_H

#define TOKEN_WORD 0

// Common Operators //

#define TOKEN_EQUAL 1
#define TOKEN_ENDLINE 2
#define TOKEN_OPENPARENTHESES 3
#define TOKEN_CLOSEPARENTHESES 4
#define TOKEN_OPENCURLYBRACKET 5
#define TOKEN_CLOSECURLYBRACKET 6
#define TOKEN_QUOTATIONMARK 7
#define TOKEN_QUESTIONMARK 8
#define TOKEN_TWOPOINTS 9

// Common Operators //

// Arithmetic operators // 

#define TOKEN_ADDITION 10
#define TOKEN_SUBTRACTION 11
#define TOKEN_MULTIPLICATION 12
#define TOKEN_DIVISION 13
#define TOKEN_MODULUS 14
#define TOKEN_INCREMENT 15
#define TOKEN_DECREMENT 16

// Arithmetic operators // 

// Relational Operators //

#define TOKEN_EQUALTO 17
#define TOKEN_NOTEQUALTO 18
#define TOKEN_GREATERTHAN 19
#define TOKEN_LESSTHAN 20
#define TOKEN_GREATERTHANEQUALTO 21
#define TOKEN_LESSTHANEQUALTO 22

// Relational Operators //

// Logical Operators //

#define TOKEN_AND 23
#define TOKEN_OR 24
#define TOKEN_NOT 25

// Logical Operators //

// Assignment Operators //

#define TOKEN_ADDITIONASSIGMENT 26
#define TOKEN_SUBTRACTIONASSIGMENT 27
#define TOKEN_MULTIPLICATIONASSIGMENT 28
#define TOKEN_DIVISIONASSIGMENT 29
#define TOKEN_MODULOSASSIGMENT 30
#define TOKEN_BITWISEANDASSIGMENT 31
#define TOKEN_BITWISEORSASSIGMENT 32
#define TOKEN_BITWISEXORASSIGMENT 33
#define TOKEN_BITWISELEFTSHIFTASSIGMENT 34
#define TOKEN_BITWISERIGHTSHIFTASSIGMENT 35

// Assignment Operators //

// Bitwise Operators //

#define TOKEN_BITWISEAND 36
#define TOKEN_BITWISEOR 37
#define TOKEN_BITWISEXOR 38
#define TOKEN_BITWISENOT 39
#define TOKEN_BITWISELEFTSHIFT 40
#define TOKEN_BITWISERIGHTSHIFT 41

// Bitwise Operators //

// Operators others //

#define TOKEN_POINTER 42
#define TOKEN_ADDRESS 43
#define TOKEN_COMMA 44
#define TOKEN_COMMENT 45
#define TOKEN_HASHTAG 46

// Operators others //

namespace utils { template <typename> struct LinkedList; }

namespace token {

    struct Token {

        char* phr;
        int id;

        ~Token();
        
        Token();

    };

    struct TokensCollection {

        utils::LinkedList <token::Token>* tokens;

        ~TokensCollection();

        TokensCollection();

    };

    int checkFirstCharacterSpecialToken(int);

    int checkSecondCharacterSpecialToken(int, int);

    int checkThirdCharacterSpecialToken(int, int, int);

    /* Check if a given Token Id is a acceptable operator to expression
    *   Needs to be part of Arithmetic, Relational, Logical, Bitwise operators
    */
    bool checkIfExpressionOperator(int);

    /* Check if a given Token Id is a acceptable operator to assignment
    *   Needs to be part of Assignment operators
    */
    bool checkIfOperatorIsAssignment(int);
    
    /*  ++ -- */
    bool checkIfOperatorIsSingleAssignment(int);

}

#endif
