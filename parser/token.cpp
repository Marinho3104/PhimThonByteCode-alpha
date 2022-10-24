#include "./token.h"

#include "./../utils/linkedList.h"
#include <iostream>

token::Token::~Token() { free(phr); }
        
token::Token::Token() : phr(NULL), id(0) {}

token::TokensCollection::~TokensCollection() {

    if (tokens != NULL) tokens->~LinkedList();
    free(tokens);

}

token::TokensCollection::TokensCollection() {

    tokens = (utils::LinkedList <token::Token>*) malloc(sizeof(utils::LinkedList <token::Token>));
    new (tokens) utils::LinkedList <token::Token>();

}

int token::checkFirstCharacterSpecialToken(int _frst) {

    switch (_frst)
    {

    case '=': return TOKEN_EQUAL;
    case ';': return TOKEN_ENDLINE;
    case '(': return TOKEN_OPENPARENTHESES;
    case ')': return TOKEN_CLOSEPARENTHESES;
    case '{': return TOKEN_OPENCURLYBRACKET;
    case '}': return TOKEN_CLOSECURLYBRACKET;
    case '"': return TOKEN_QUOTATIONMARK;
    case '?': return TOKEN_QUESTIONMARK;
    case ':': return TOKEN_TWOPOINTS;

    case '+': return TOKEN_ADDITION;
    case '-': return TOKEN_SUBTRACTION;
    case '*': return TOKEN_MULTIPLICATION;
    case '/': return TOKEN_DIVISION;
    case '%': return TOKEN_MODULUS;
    // case '+': return TOKEN_ADDITION; -> ++
    // case '-': return TOKEN_SUBTRACTION; -> --

    // case '=': return TOKEN_EQUALTO;
    case '!': return TOKEN_NOTEQUALTO;
    case '>': return TOKEN_GREATERTHAN;
    case '<': return TOKEN_LESSTHAN;
    // case '>': return TOKEN_GREATERTHANEQUALTO; -> >
    // case '<': return TOKEN_LESSTHANEQUALTO; -> <

    case '&': return TOKEN_AND; // -> &&
    case '||': return TOKEN_OR; // -> ||
    // case '!': return TOKEN_NOT;

    // case '+': return TOKEN_ADDITIONASSIGMENT; // -> +=
    // case '-': return TOKEN_SUBTRACTIONASSIGMENT; // -> -=
    // case '*': return TOKEN_MULTIPLICATIONASSIGMENT; // -> *=
    // case '/': return TOKEN_DIVISIONASSIGMENT; // -> /=
    // case '%': return TOKEN_MODULOSASSIGMENT; // -> %=
    // case '&': return TOKEN_BITWISEANDASSIGMENT; // -> &=
    case '|': return TOKEN_BITWISEORSASSIGMENT; // -> |=
    case '^': return TOKEN_BITWISEXORASSIGMENT; // -> ^=
    // case '<': return TOKEN_BITWISELEFTSHFTASSIGMENT; // -> <<=
    // case '>': return TOKEN_BITWISERIGHTSHIFTASSIGMENT; // -> >>=

    // case '&': return TOKEN_BITWISEAND;
    // case '|': return TOKEN_BITWISEOR;
    // case '^': return TOKEN_BITWISEXOR;
    case '~': return TOKEN_BITWISENOT;
    // case '<': return TOKEN_BITWISEAND; -> <<
    // case '>': return TOKEN_BITWISEAND; -> >>

    // case '*': return TOKEN_POINTER;
    // case '&': return TOKEN_ADDRESS;
    case ',': return TOKEN_COMMA;
    // case '/': return TOKEN_COMMENT; // -> //
    case '#': return TOKEN_HASHTAG;

    }

    return TOKEN_WORD;

}

int token::checkSecondCharacterSpecialToken(int _frst, int _scnd) { 

    switch (_frst)
    {

    case '=':

        switch (_scnd)
        {
        case '=': return TOKEN_EQUALTO;
        }
        break;
    
    case '!':

        switch (_scnd)
        {
        case '=': return TOKEN_NOTEQUALTO;
        }
        break;

    case '>':

        switch (_scnd)
        {
        case '=': return TOKEN_GREATERTHANEQUALTO;
        case '>': return TOKEN_BITWISERIGHTSHIFT;
        }
        break;

    case '<':

        switch (_scnd)
        {
        case '=': return TOKEN_LESSTHANEQUALTO;
        case '<': return TOKEN_BITWISELEFTSHIFT;
        }
        break;

    case '&':

        switch (_scnd)
        {
        case '&': return TOKEN_AND;
        case '=': return TOKEN_BITWISEANDASSIGMENT;
        }
        break;

    case '|':

        switch (_scnd)
        {
        case '|': return TOKEN_OR;
        case '=': return TOKEN_BITWISEORSASSIGMENT;
        }
        break;

    case '+':
        
        switch (_scnd)
        {
        case '+': return TOKEN_INCREMENT;
        case '=': return TOKEN_ADDITIONASSIGMENT;
        }
            break;

    case '-':

        switch (_scnd)
        {
        case '-': return TOKEN_DECREMENT;
        case '=': return TOKEN_SUBTRACTIONASSIGMENT;
        }

        break;

    case '*':

        switch (_scnd)
        {
        case '=': return TOKEN_MULTIPLICATIONASSIGMENT;
        }
        break;

    case '/':

        switch (_scnd)
        {
        case '/': return TOKEN_COMMENT;
        case '=': return TOKEN_DIVISIONASSIGMENT;
        }
        break;

    case '%':

        switch (_scnd)
        {
        case '=': return TOKEN_MODULOSASSIGMENT;
        }
        break;
    
    case '^':

        switch (_scnd)
        {
        case '=': return TOKEN_BITWISEXORASSIGMENT;
        }
        break;


    }

    return TOKEN_WORD;

}

int token::checkThirdCharacterSpecialToken(int _frst, int _scnd, int _thrd) {

    switch (_frst)
    {
    case '<':
        
        switch (_scnd)
        {
        case '<':
            
            switch (_thrd)
            {
            case '=': return TOKEN_BITWISELEFTSHIFTASSIGMENT;
            }

            break;

        }

        break;

    case '>':
        
        switch (_scnd)
        {
        case '>':
            
            switch (_thrd)
            {
            case '=': return TOKEN_BITWISERIGHTSHIFTASSIGMENT;
            }

            break;

        }

        break;

    }


    return TOKEN_WORD;

}




