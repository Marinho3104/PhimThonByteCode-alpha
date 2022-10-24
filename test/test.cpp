
#include "./../parser/convertToTokens.h"
#include "./../parser/convertToAst.h"
#include "./../utils/linkedList.h"
#include "./../parser/token.h"

#include <iostream>

int main() {

    token::TokensCollection* _tokensColl = parser::convertToTokens::createTokens(

    "int l = 10;"

    );

    std::cout << "Done tokens coll" << std::endl;

    parser::convertToAst::createAst(_tokensColl);

}