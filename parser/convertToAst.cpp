#include "./convertToAst.h"

#include "./../utils/linkedList.h"
#include "./keyWordsReserved.h"
#include "./token.h"

#include <iostream>

int parser::convertToAst::getInstructionType(utils::LinkedList <token::Token>* _instr) {

    // Check Variable Declaration
    if (keyWordsReserved::checkIfWordIsVariableType(_instr->frst->object->phr)) return AST_NODE_VARIABLEDECLARATION;

    return 10;

}

parser::convertToAst::Node* parser::convertToAst::handleSingleInstruction(utils::LinkedList <token::Token>* _instr) {

    int _instrType = getInstructionType(_instr);

    std::cout << "Instruction type -> " << _instrType << std::endl;

}

parser::convertToAst::Ast* parser::convertToAst::createAst(token::TokensCollection* _tokensColl) {

    utils::LinkedList <token::Token>* _crrntInstruction = (utils::LinkedList <token::Token>*) malloc(sizeof(utils::LinkedList <token::Token>));
    new (_crrntInstruction) utils::LinkedList <token::Token>();

    for (int _ = 0 ; _ < _tokensColl->tokens->count; _++) {

        _crrntInstruction->add(
            (*_tokensColl->tokens)[_]
        );

        if (_crrntInstruction->last->object->id != TOKEN_ENDLINE) continue;

        handleSingleInstruction(_crrntInstruction);

        _crrntInstruction->clean();

    }

}
