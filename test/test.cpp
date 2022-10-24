
#include "./../parser/convertToTokens.h"
#include "./../parser/convertToAst.h"
#include "./../utils/linkedList.h"
#include "./../parser/token.h"

#include <iostream>

int main() {

    token::TokensCollection* _tokensColl = parser::convertToTokens::createTokens(

    "int* l;int l = 10;"

    );

    // for (int _ = 0; _ < _tokensColl->tokens->count; _++) std::cout << (*_tokensColl->tokens)[_]->id << " -> " << (*_tokensColl->tokens)[_]->phr << std::endl;

    std::cout << "Done tokens coll" << std::endl;

    parser::convertToAst::Ast* _ast = (parser::convertToAst::Ast*) malloc(sizeof(parser::convertToAst::Ast));
    new (_ast) parser::convertToAst::Ast();

    _ast->generateAst(_tokensColl);

    // std::cout << _ast->body->count << std::endl;

    //std::cout << ( (parser::convertToAst::NodeValue*) ((parser::convertToAst::NodeVariableDeclaration*) _ast->body->frst->object)->valuePos)->valuePos << std::endl;

}