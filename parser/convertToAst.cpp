#include "./convertToAst.h"

#include "./../utils/commonFunctions.h"
#include "./../utils/linkedList.h"
#include "./keyWordsReserved.h"
#include "./token.h"

#include <iostream>

parser::convertToAst::NodeValue::NodeValue(int _valuePos) :
    valuePos(_valuePos) { type = AST_NODE_VALUE; }

parser::convertToAst::NodeVariableDeclaration::NodeVariableDeclaration(int _variableTypePos, int _namePos, bool _isPointer, Node* _value) :
    variableTypePos(_variableTypePos), namePos(_namePos), isPointer(_isPointer), value(_value)  { type = AST_NODE_VARIABLEDECLARATION; }

parser::convertToAst::NodeVariableAssignmet::NodeVariableAssignmet(int _namePos, int _assignmentPos, Node* _value) :
    namePos(_namePos), assignmentPos(_assignmentPos), value(_value) { type = AST_NODE_VARIABLEASSIGNMET; }

parser::convertToAst::NodeArithmetricExpression::NodeArithmetricExpression(Node* _frst, Node* _scnd, int _exprPos) :
    frst(_frst), scnd(_scnd), expressionPos(_exprPos) { type = AST_NODE_ARITHMETRICEXPRESSION; }

parser::convertToAst::NodeVariableValue::NodeVariableValue(int _namePos) : 
    namePos(_namePos) { type = AST_NODE_VARIABLEVALUE; }

parser::convertToAst::AstException::AstException(char* _description) : description(_description) {}

char* parser::convertToAst::AstException::what() { return description; }

parser::convertToAst::Ast::Ast() : exception(NULL) {

    body = (utils::LinkedList <Node>*) malloc(sizeof(utils::LinkedList <Node>));
    new (body) utils::LinkedList <Node>();

    constsNames = (utils::LinkedList <char>*) malloc(sizeof(utils::LinkedList <char>));
    new (constsNames) utils::LinkedList <char>();

    constsValues = (utils::LinkedList <char>*) malloc(sizeof(utils::LinkedList <char>));
    new (constsValues) utils::LinkedList <char>();

    keyWords = (utils::LinkedList <int>*) malloc(sizeof(utils::LinkedList <int>));
    new (keyWords) utils::LinkedList <int>();

    assignment = (utils::LinkedList <int>*) malloc(sizeof(utils::LinkedList <int>));
    new (assignment) utils::LinkedList <int>();

    constsExpressionOperator = (utils::LinkedList <int>*) malloc(sizeof(utils::LinkedList <int>));
    new (constsExpressionOperator) utils::LinkedList <int>();

}

void parser::convertToAst::Ast::setException(char* _description) {

    exception = (parser::convertToAst::AstException*) malloc(sizeof(parser::convertToAst::AstException));
    new (exception) parser::convertToAst::AstException(_description);

    std::cout << "error: " << exception->what() << std::endl;

    exit(1);

}

void parser::convertToAst::Ast::setFullInstruction(
    utils::LinkedList <token::Token>* _instrSet, token::TokensCollection* _tokensColl, int* _crrntTokenPos) {

    for (; *_crrntTokenPos < _tokensColl->tokens->count; (*_crrntTokenPos)++) {

        // std::cout << (*_tokensColl->tokens)[*_crrntTokenPos]->id << " -> " << (*_tokensColl->tokens)[*_crrntTokenPos]->phr << std::endl;

        _instrSet->add(
            (*_tokensColl->tokens)[*_crrntTokenPos]
        );

        if (_instrSet->last->object->id == TOKEN_ENDLINE) break;

    }

    (*_crrntTokenPos)++;

}

utils::LinkedList<parser::convertToAst::Node>* 
    parser::convertToAst::Ast::getNodes(utils::LinkedList <token::Token>* _instr, int* _instrCrrntPos) { 

        int _;

        if (!_instrCrrntPos) { // if _instrCrrntPos == NULL just set to value 0

            _ = 0;
            _instrCrrntPos = &_;

        }

        utils::LinkedList <Node>* _rtr = (utils::LinkedList <Node>*) malloc(sizeof(utils::LinkedList <Node>));
        new (_rtr) utils::LinkedList <Node>();

        int _type, _keyWordPos, _assignmentPos, _expressionOperatorPos, _constsNamesPos, _constsValuesPos; 
        bool _pntr;

        if ((_type = keyWordsReserved::checkIfWordIsVariableType((*_instr)[*_instrCrrntPos]->phr))) { // declaration type

            if ((_keyWordPos = keyWords->getObjectPosition(&_type, [](int* _f, int* _s) -> bool { return *_f == *_s; })) == -1) 
                _keyWordPos = keyWords->add(&_type);

            (*_instrCrrntPos)++;

            while(!utils::compareStrings((*_instr)[(*_instrCrrntPos)]->phr, ";", 1)) { // Keeps the loop until reach ";" <- end of instruction

                if ((_pntr = ((*_instr)[(*_instrCrrntPos)]->id == TOKEN_MULTIPLICATION))) // Check if is pointer declaration -> int* p;
                    (*_instr)[(*_instrCrrntPos)++]->id = TOKEN_POINTER;

                if ((_constsNamesPos = constsNames->getObjectPosition( // Check s if const name is already in LinkedList if not added
                    (*_instr)[(*_instrCrrntPos)]->phr, &utils::compareStrings)) != -1) setException("Redefetion of variable"); 

                else _constsNamesPos = constsNames->add((*_instr)[(*_instrCrrntPos)]->phr);

                (*_instrCrrntPos)++;

                if ((*_instr)[(*_instrCrrntPos)]->id != TOKEN_EQUAL) { // Just declaration, no assigment -> int p;

                    std::cout << "Added, no assigment" << std::endl;

                    _rtr->add(
                        new NodeVariableDeclaration(_keyWordPos, _constsNamesPos, _pntr, NULL)
                    );

                    if ((*_instr)[(*_instrCrrntPos)]->id == TOKEN_COMMA) (*_instrCrrntPos)++; // If is not "," means is end of instruction ";", should not be changing value cuss to leave need ";"

                }

                else { // Declaration have assigment as well

                    std::cout << "Added with assigment" << std::endl;

                    (*_instrCrrntPos)++;

                    utils::LinkedList<Node>* _node = getNodes(_instr, _instrCrrntPos);
                                        
                    _rtr->add(
                        new NodeVariableDeclaration(
                            _keyWordPos, 
                            _constsNamesPos, 
                            _pntr, 
                            !_node->count ? NULL : _node->frst->object
                        )
                    );

                }

            }

        }

        else if (utils::isNumber((*_instr)[(*_instrCrrntPos)]->phr)) {

            if ((*_instr)[(*_instrCrrntPos) + 1]->id == TOKEN_ENDLINE) { // Just value

                if ((_constsValuesPos = constsValues->getObjectPosition( // Check s if const value is already in LinkedList, if not added
                    (*_instr)[(*_instrCrrntPos)]->phr, &utils::compareStrings)) == -1) 
                        _constsValuesPos = constsValues->add((*_instr)[(*_instrCrrntPos)++]->phr);
                
                _rtr->add(
                    new NodeValue(_constsValuesPos)
                );

            }

            else if (token::checkIfExpressionOperator((*_instr)[(*_instrCrrntPos) + 1]->id)) {

                std::cout << "--> Arithmetric expression added <--" << std::endl;

                if ((_constsValuesPos = constsValues->getObjectPosition( // Check s if const value is already in LinkedList, if not added
                    (*_instr)[(*_instrCrrntPos)]->phr, &utils::compareStrings)) == -1) 
                        _constsValuesPos = constsValues->add((*_instr)[(*_instrCrrntPos)]->phr);
                (*_instrCrrntPos)++;

                if ((_expressionOperatorPos = constsExpressionOperator->getObjectPosition( // Check s if assignment type is already in LinkedList if not added
                    &(*_instr)[(*_instrCrrntPos)]->id, [](int* _f, int* _s) -> bool { return *_f == *_s; })) == -1) 
                        _expressionOperatorPos = constsExpressionOperator->add(&(*_instr)[(*_instrCrrntPos)]->id);
                (*_instrCrrntPos)++;

                utils::LinkedList<Node>* _node = getNodes(_instr, _instrCrrntPos);

                _rtr->add(
                    new NodeArithmetricExpression(
                        new NodeValue(_constsValuesPos),
                        !_node->count ? NULL : _node->frst->object,
                        _expressionOperatorPos
                    )
                );                           

            }

        }

        else { // Common word <- ola = 10;

            if (token::checkIfOperatorIsAssignment((*_instr)[(*_instrCrrntPos) + 1]->id)) { // assignment to variable <- ola = 10;

                if ((_constsNamesPos = constsNames->getObjectPosition( // Check s if const name is already in LinkedList if not throw exception
                    (*_instr)[(*_instrCrrntPos)++]->phr, &utils::compareStrings)) == -1) setException("Variable not defined");

                if ((_assignmentPos = assignment->getObjectPosition( // Check s if assignment type is already in LinkedList if not added
                    &(*_instr)[(*_instrCrrntPos)++]->id, [](int* _f, int* _s) -> bool { return *_f == *_s; })) != -1) 
                        _assignmentPos = assignment->add(&(*_instr)[(*_instrCrrntPos)++]->id);
              
                
                std::cout << "Assignment added" << std::endl;

                utils::LinkedList<Node>* _node = getNodes(_instr, _instrCrrntPos);


                _rtr->add(
                    new NodeVariableAssignmet(
                        _constsNamesPos,
                        _assignmentPos, 
                        !_node->count ? NULL : _node->frst->object
                    )
                );

            }

            else {

                if ((_constsNamesPos = constsNames->getObjectPosition( // Check s if const name is already in LinkedList if not throw exception
                    (*_instr)[(*_instrCrrntPos)++]->phr, &utils::compareStrings)) == -1) setException("Variable not defined");

                std::cout << "--> Variable value use  <--" << std::endl;

                _rtr->add(
                    new NodeVariableValue(_constsNamesPos)
                );

            }
        }

        return _rtr;

}

void parser::convertToAst::Ast::generateAst(token::TokensCollection* _tokensColl) {

    utils::LinkedList <token::Token>* _crrntInstruction = (utils::LinkedList <token::Token>*) malloc(sizeof(utils::LinkedList <token::Token>));
    new (_crrntInstruction) utils::LinkedList <token::Token>();
    int _crrntTokenPos = 0;

    // TODO Need to check for breaked sentences and stuff first

    while(_crrntTokenPos < _tokensColl->tokens->count - 1) { // std::cout << "Loop" << std::endl;

        setFullInstruction(_crrntInstruction, _tokensColl, &_crrntTokenPos);

        body->join(
            getNodes(_crrntInstruction, NULL)
        );

        _crrntInstruction->clean();

    }

}
