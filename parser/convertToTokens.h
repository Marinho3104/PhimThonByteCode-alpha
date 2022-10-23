
#pragma once


#ifndef VARIABLES_1_H
#define VARIABLES_1_H

namespace token { struct Token; }

namespace parser::convertToTokens {

    /* Convert src code into byteCode */

    struct TokenCreation {

        char* initialChar, *currentChar;
        bool special;

    };

    token::Token* handleSingleToken(char**);

    void createTokens(char*);

}

#endif