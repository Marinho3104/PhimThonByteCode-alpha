#include "./convertToTokens.h"

#include "./../utils/commonFunctions.h"
#include "./../utils/linkedList.h"
#include "./token.h"

#include <iostream>

token::Token* parser::convertToTokens::createNewToken(char** _) {

    char* _phr = 0;
    int _size = 0, _specialId, __, ___;

    TokenCreation _tokenCreation; 
    _tokenCreation.initialChar = *_;
    _tokenCreation.currentChar = *_;

    token::Token* _token = (token::Token*) malloc(sizeof(token::Token));
    new(_token) token::Token();

    if (_token->id = token::checkFirstCharacterSpecialToken(*_tokenCreation.currentChar)) {

        __ = *_tokenCreation.currentChar;

        if (_specialId = token::checkSecondCharacterSpecialToken(__, *(++_tokenCreation.currentChar))) { 

            _token->id = _specialId;

            if (_token->id == TOKEN_COMMENT) 
                { do _tokenCreation.currentChar++; while(*_tokenCreation.currentChar != '\n'); 
                    _size = _tokenCreation.currentChar - _tokenCreation.initialChar + 1; _token = NULL; }

            else {  
            
                ___ = *_tokenCreation.currentChar;
                _token->id = _specialId;

                if (_specialId = token::checkThirdCharacterSpecialToken(__, ___, *(++_tokenCreation.currentChar))) 
                    { _size = 3; _token->id = _specialId; }
                
                else _size = 2; 
            
            }

        }

        else _size = 1;

    } else {

        do _tokenCreation.currentChar++;

        while(
            !token::checkFirstCharacterSpecialToken(*_tokenCreation.currentChar) && *_tokenCreation.currentChar != ' '
        );

        _size = _tokenCreation.currentChar - _tokenCreation.initialChar;

    } 

    if (_token != NULL) {

        _token->phr = (char*) malloc(sizeof(char) * (_size + 1));
        
        utils::copyTo(_tokenCreation.initialChar, _token->phr, _size);

        _token->phr[_size] = 0;

    }

    *_ += _size; 

    return _token;

}

token::TokensCollection* parser::convertToTokens::createTokens(char* _src) {

    token::TokensCollection* _rtr = new token::TokensCollection();
    token::Token* _returnedToken;
    
    while(*_src != 0) {

        if (*_src == ' ') { _src++; continue;}

        if ((_returnedToken = createNewToken(&_src)) != NULL)

            _rtr->tokens->add(_returnedToken);

    }

    return _rtr;
    
}





