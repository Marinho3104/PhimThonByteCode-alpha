#include "./convertToAst.h"

#include "./../utils/commonFunctions.h"
#include "./../utils/linkedList.h"
#include "./keyWordsReserved.h"
#include "./token.h"

#include <iostream>

parser::convertToAst::NodeValue::NodeValue(int _valuePos) :
    valuePos(_valuePos) { type = AST_NODE_VALUE; }

parser::convertToAst::NodeVariableDeclaration::NodeVariableDeclaration(int _variableTypePos, int _namePos, bool _isPointer, Node* _valuePos) :
    variableTypePos(_variableTypePos), namePos(_namePos), isPointer(_isPointer), valuePos(_valuePos)  { type = AST_NODE_VARIABLEDECLARATION; }

parser::convertToAst::Ast::Ast() {

    body = (utils::LinkedList <Node>*) malloc(sizeof(utils::LinkedList <Node>));
    new (body) utils::LinkedList <Node>();

    constsNames = (utils::LinkedList <char>*) malloc(sizeof(utils::LinkedList <char>));
    new (constsNames) utils::LinkedList <char>();

    constsValues = (utils::LinkedList <char>*) malloc(sizeof(utils::LinkedList <char>));
    new (constsValues) utils::LinkedList <char>();

    keyWords = (utils::LinkedList <int>*) malloc(sizeof(utils::LinkedList <int>));
    new (keyWords) utils::LinkedList <int>();

}

int parser::convertToAst::Ast::setFullInstruction(
    utils::LinkedList <token::Token>* _instrSet, token::TokensCollection* _tokensColl, int _crrntTokenPos) {

    for (; _crrntTokenPos < _tokensColl->tokens->count; _crrntTokenPos++) {

        _instrSet->add(
            (*_tokensColl->tokens)[_crrntTokenPos]
        );

        if (_instrSet->last->object->id == TOKEN_ENDLINE) break;

    }

    return _crrntTokenPos;

}

//  TODO: Make a function to check if a name already exist in a Linkedist and function to return a position of a values in LinkedList
utils::LinkedList<parser::convertToAst::Node>* 
    parser::convertToAst::Ast::getNodes(utils::LinkedList <token::Token>* _instr, int _instrCrrntPos) { 

        utils::LinkedList <Node>* _rtr = (utils::LinkedList <Node>*) malloc(sizeof(utils::LinkedList <Node>));
        new (_rtr) utils::LinkedList <Node>();

        int _type; bool _pntr;

        if ((_type = keyWordsReserved::checkIfWordIsVariableType((*_instr)[_instrCrrntPos]->phr))) {
        
            ++_instrCrrntPos;

            while(_instrCrrntPos < _instr->count) {

                if ((_pntr = ((*_instr)[_instrCrrntPos]->id == TOKEN_MULTIPLICATION))) { (*_instr)[_instrCrrntPos]->id = TOKEN_POINTER; _instrCrrntPos++; }

                constsNames->add(
                    (*_instr)[_instrCrrntPos++]->phr
                );

                keyWords->add( // Not in correct place
                    &_type
                );

                if ((*_instr)[_instrCrrntPos++]->id != TOKEN_EQUAL) {

                    _rtr->add(
                        new NodeVariableDeclaration(keyWords->count - 1, constsNames->count - 1, _pntr, NULL)
                    );
                }
                else {

                    utils::LinkedList<Node>* _node = getNodes(_instr, _instrCrrntPos);
                                        
                    _rtr->add(
                        new NodeVariableDeclaration(
                            keyWords->count - 1, 
                            constsNames->count - 1, 
                            _pntr, 
                            !_node->count ? NULL : _node->frst->object
                        )
                    );
                }

            }

        }

        else if (utils::isNumber((*_instr)[_instrCrrntPos]->phr)) {

            constsValues->add(
                (*_instr)[_instrCrrntPos++]->phr
            );

            _rtr->add(
                new NodeValue(constsValues->count - 1)
            );

        } else _instrCrrntPos++;

        return _rtr;

}

parser::convertToAst::Ast* 
    parser::convertToAst::Ast::generateAst(token::TokensCollection* _tokensColl) {

        utils::LinkedList <token::Token>* _crrntInstruction = (utils::LinkedList <token::Token>*) malloc(sizeof(utils::LinkedList <token::Token>));
        new (_crrntInstruction) utils::LinkedList <token::Token>();

        int _crrntInstrcPos = 0;

        // TODO Need to check for breaked sentences and stuff first 

        while(_crrntInstrcPos < _tokensColl->tokens->count - 1) {

            _crrntInstrcPos = setFullInstruction(_crrntInstruction, _tokensColl, _crrntInstrcPos);

            body->join(
                getNodes(_crrntInstruction, 0)
            );

            _crrntInstruction->clean();

        }

        return this;

}
