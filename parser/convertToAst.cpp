#include "./convertToAst.h"

#include "./../utils/commonFunctions.h"
#include "./../utils/linkedList.h"
#include "./keyWordsReserved.h"
#include "./token.h"

#include <iostream>

/////////// Block ///////////

parser::convertToAst::Block::Block(Block* _previousBlock) : previousBlock(_previousBlock) {

    type = AST_NODE_BLOCK;

    environment = (Environment*) malloc(sizeof(Environment));
    new(environment) Environment();

    body = (utils::LinkedList <Node>*) malloc(sizeof(utils::LinkedList <Node>));
    new (body) utils::LinkedList <Node>();

}

void parser::convertToAst::Block::generateBlockBody(Ast* _ast, int* _crrntTokenPos) {
    
    while(*_crrntTokenPos < _ast->tokensCollection->tokens->count) {// std::cout << "Loop" << std::endl;
        body->join(
            _ast->getNodes(_ast->tokensCollection->tokens, _crrntTokenPos, this, 0)
        );
    
        if (body->last->object->type == AST_NODE_BLOCKEND) { body->remove(body->last); break; }

    }

}

parser::convertToAst::NodeVariableDeclaration* 
    parser::convertToAst::Block::getVariableDeclaration(int _namePos) {
        parser::convertToAst::NodeVariableDeclaration* _rtr;
        if (!(_rtr = environment->getVariableDeclaration(_namePos)))
            if (previousBlock) _rtr = previousBlock->getVariableDeclaration(_namePos);
            else _rtr = NULL;
        return _rtr;
}

parser::convertToAst::Block* 
    parser::convertToAst::Block::generate(utils::LinkedList <token::Token>* _instr, int* _instrCrrntPos, Ast* _ast, Block* _crrntBlock) {

        std::cout << "--> Node Block <--" << std::endl;

        parser::convertToAst::Block* _rtr = (parser::convertToAst::Block*) malloc(sizeof(parser::convertToAst::Block));
        new (_rtr) parser::convertToAst::Block(_crrntBlock);

        (*_instrCrrntPos)++;

        _rtr->generateBlockBody(_ast, _instrCrrntPos);

        return _rtr;

}

/////////// Node Variable Declaration ///////////

parser::convertToAst::NodeVariableDeclaration::NodeVariableDeclaration(int _variableTypePos, int _namePos, int _pointerLevel, int _referenceLevel, Node* _value) :
    namePos(_namePos), value(_value) {
        type = AST_NODE_VARIABLEDECLARATION;
        typeInfo = new parser::convertToAst::TypeInformation(_variableTypePos, _pointerLevel, _referenceLevel);
}

utils::LinkedList <parser::convertToAst::Node>* 
    parser::convertToAst::NodeVariableDeclaration::generate(
        utils::LinkedList <token::Token>* _instr, int* _instrCrrntPos, int _type, Ast* _ast, Block* _crrntBlock) {
            std::cout << "--> Variable Declaration <--" << std::endl;
            utils::LinkedList <Node>* _rtr = (utils::LinkedList <Node>*) malloc(sizeof(utils::LinkedList <Node>));
            new (_rtr) utils::LinkedList <Node>();
            int _keyWordPos = _ast->storage->addKeyWord(_type), _constsNamesPos, _pntrLevel, _referenceLevel;
            (*_instrCrrntPos)++;
            while((*_instr)[(*_instrCrrntPos)]->id != TOKEN_ENDLINE) {
                _pntrLevel = 0; _referenceLevel = 0;
                if ((*_instr)[(*_instrCrrntPos)]->id == TOKEN_MULTIPLICATION) {
                    while((*_instr)[(*_instrCrrntPos)]->id == TOKEN_MULTIPLICATION) { (*_instrCrrntPos)++; _pntrLevel++; }
                    if ((*_instr)[(*_instrCrrntPos)]->id == TOKEN_AND) _ast->setException("Error nesty tokens");
                }
                else if ((*_instr)[(*_instrCrrntPos)]->id == TOKEN_AND) {
                    while((*_instr)[(*_instrCrrntPos)]->id == TOKEN_AND) { (*_instrCrrntPos)++; _referenceLevel++; }
                    if ((*_instr)[(*_instrCrrntPos)]->id == TOKEN_MULTIPLICATION) _ast->setException("Error nesty tokens");
                }
                _constsNamesPos = _ast->storage->addConstsNames((*_instr)[(*_instrCrrntPos)]->phr);
                if (_crrntBlock->environment->getVariableDeclaration(_constsNamesPos)) _ast->setException("Redefetion of variable");
                (*_instrCrrntPos)++;
                if ((*_instr)[(*_instrCrrntPos)]->id != TOKEN_EQUAL) { // Just declaration, no assigment -> int p;
                    std::cout << "Added, no assigment" << std::endl;
                    _rtr->add(
                        new NodeVariableDeclaration(_keyWordPos, _constsNamesPos, _pntrLevel, _referenceLevel, NULL)
                    );
                    _crrntBlock->environment->addVariableDeclaration(_rtr->last->object);
                    if ((*_instr)[(*_instrCrrntPos)]->id == TOKEN_COMMA) 
                        (*_instrCrrntPos)++; // If is not "," means is end of instruction ";", should not be changing value cuss to leave need ";"
                }
                else { // Declaration have assigment as well
                    std::cout << "Added with assigment" << std::endl;
                    (*_instrCrrntPos)++;
                    utils::LinkedList<Node>* _node = _ast->getNodes(_instr, _instrCrrntPos, _crrntBlock, 0);
                    _rtr->add(
                        new NodeVariableDeclaration(
                            _keyWordPos, 
                            _constsNamesPos, 
                            _pntrLevel, 
                            _referenceLevel,
                            !_node->count ? NULL : _node->frst->object
                        )
                    );
                    _crrntBlock->environment->addVariableDeclaration(_rtr->last->object);
                    if ((*_instr)[(*_instrCrrntPos)]->id == TOKEN_COMMA) 
                        (*_instrCrrntPos)++; // If is not "," means is end of instruction ";", should not be changing value cuss to leave need ";"
                }
            }
            return _rtr;
}

/////////// Node Value ///////////

parser::convertToAst::NodeValue::NodeValue(int _posValue) : valuePos(_posValue) {}

parser::convertToAst::NodeValue* parser::convertToAst::NodeValue::generate(utils::LinkedList <token::Token>* _instr, int* _instrCrrntPos, Ast* _ast) {
    std::cout << "--> Node Value added <--" << std::endl;
    return new NodeValue(_ast->storage->addConstsValue((*_instr)[(*_instrCrrntPos)++]->phr));
}

/////////// Node Variable Value ///////////

parser::convertToAst::NodeVariableValue::NodeVariableValue(utils::LinkedList <int>* _operatorsBeforeVariable, NodeVariableDeclaration* _declarationAddr) :  
    operatorsBeforeVariable(_operatorsBeforeVariable), declarationAddr(_declarationAddr) { type = AST_NODE_VARIABLEVALUE; }

parser::convertToAst::NodeVariableValue* 
    parser::convertToAst::NodeVariableValue::generate(utils::LinkedList <token::Token>* _instr, int* _instrCrrntPos, Ast* _ast, Block* _crrntBlock) {
        std::cout << "--> Variable value use  <--" << std::endl;
        utils::LinkedList <int>* _operatorsUsed = (utils::LinkedList <int>*) malloc(sizeof(utils::LinkedList <int>));
        parser::convertToAst::NodeVariableDeclaration* _declaration;
        new (_operatorsUsed) utils::LinkedList <int>();
        while((*_instr)[(*_instrCrrntPos)]->id == TOKEN_AND || (*_instr)[(*_instrCrrntPos)]->id == TOKEN_MULTIPLICATION) {
            if ((*_instr)[(*_instrCrrntPos)]->id == TOKEN_AND) (*_instr)[(*_instrCrrntPos)]->id = TOKEN_ADDRESS;
            else (*_instr)[(*_instrCrrntPos)]->id = TOKEN_POINTER;
            _operatorsUsed->add((*_instr)[(*_instrCrrntPos)++]->id);
        }
        int _constsNamesPos = _ast->storage->addConstsNames((*_instr)[(*_instrCrrntPos)]->phr);
        if (!(_declaration = _crrntBlock->getVariableDeclaration(_constsNamesPos))) _ast->setException("Variable not defined");
        return new NodeVariableValue(_operatorsUsed, _declaration);
}


/////////// Node Variable Assignment ///////////

parser::convertToAst::NodeVariableAssignmet::NodeVariableAssignmet(NodeVariableDeclaration* _declarationAddr, int _assignmentPos, Node* _value) :
    declarationAddr(_declarationAddr), assignmentPos(_assignmentPos), value(_value) { type = AST_NODE_VARIABLEASSIGNMENT; }

parser::convertToAst::NodeVariableAssignmet* 
    parser::convertToAst::NodeVariableAssignmet::generate(utils::LinkedList <token::Token>* _instr, int* _instrCrrntPos, Ast* _ast, Block* _crrntBlock) {
        std::cout << "--> Assignment added <--" << std::endl;
        int _constsNamesPos = _ast->storage->addConstsNames((*_instr)[(*_instrCrrntPos)++]->phr);
        int _assignmentPos = _ast->storage->addAssignment((*_instr)[(*_instrCrrntPos)++]->id);
        parser::convertToAst::NodeVariableDeclaration* _declaration;
        utils::LinkedList<Node>* _node;
        if (!(_declaration = _crrntBlock->getVariableDeclaration(_constsNamesPos))) _ast->setException("Variable not defined");
        _node = _ast->getNodes(_instr, _instrCrrntPos, _crrntBlock, 0);
        return new NodeVariableAssignmet(
            _declaration,
            _assignmentPos, 
            !_node->count ? NULL : _node->frst->object
        );
}

/////////// Node Variable Assignment Single ///////////

parser::convertToAst::NodeVariableAssignmetSingle::NodeVariableAssignmetSingle(
    NodeVariableDeclaration* _declarationAddr, bool _assignmentIsPosLeft, int _assignmentPos) : 
        declarationAddr(_declarationAddr), assignmentIsPosLeft(_assignmentIsPosLeft), assignmentPos(_assignmentPos) {
            type = AST_NODE_VARIABLEASSIGNMENTSINGLE; }

parser::convertToAst::NodeVariableAssignmetSingle* 
    parser::convertToAst::NodeVariableAssignmetSingle::generate(utils::LinkedList <token::Token>* _instr, int* _instrCrrntPos, Ast* _ast, Block* _crrntBlock) {
        std::cout << "--> Assignment Single added <--" << std::endl;
        int _constsNamesPos, _assignmentPos;
        bool _isLeftSide;
        if (_isLeftSide = token::checkIfOperatorIsSingleAssignment((*_instr)[(*_instrCrrntPos)]->id)) {
            _assignmentPos = _ast->storage->addAssignment((*_instr)[(*_instrCrrntPos)++]->id);
            _constsNamesPos = _ast->storage->addConstsNames((*_instr)[(*_instrCrrntPos)++]->phr);
        }
        else {
            _constsNamesPos = _ast->storage->addConstsNames((*_instr)[(*_instrCrrntPos)++]->phr);
            _assignmentPos = _ast->storage->addAssignment((*_instr)[(*_instrCrrntPos)++]->id);
        }
        parser::convertToAst::NodeVariableDeclaration* _declaration;
        if (!token::checkIfOperatorIsSingleAssignment(*(*_ast->storage->assignment)[_assignmentPos])) // Should never happen
            _ast->setException("Compiler internal error");
        if (!(_declaration = _crrntBlock->getVariableDeclaration(_constsNamesPos))) _ast->setException("Variable not defined");
        return new NodeVariableAssignmetSingle(
            _declaration, _isLeftSide, _assignmentPos
        );
}

/////////// Node Expression ///////////

parser::convertToAst::NodeExpression::NodeExpression(Node* _frst, Node* _scnd, int _exprPos) :
    frst(_frst), scnd(_scnd), expressionPos(_exprPos) { type = AST_NODE_EXPRESSION; }

parser::convertToAst::NodeExpression* parser::convertToAst::NodeExpression::generate(
    utils::LinkedList <token::Token>* _instr, int* _instrCrrntPos, Ast* _ast, Block* _crrntBlock) {
        std::cout << "--> Arithmetric expression added <--" << std::endl;
        int _frstValuePos, _expressionOperatorPos;
        utils::LinkedList<Node>* _frstValue, *_node;
        _frstValue = _ast->getNodes(_instr, _instrCrrntPos, _crrntBlock, 1);
        if ((*_instr)[(*_instrCrrntPos)]->id == TOKEN_ENDLINE || (*_instr)[(*_instrCrrntPos)]->id == TOKEN_CLOSEPARENTHESES) { // ;
            _expressionOperatorPos = -1;
            _node = (utils::LinkedList <Node>*) malloc(sizeof(utils::LinkedList <Node>)); 
            new (_node) utils::LinkedList <Node>();
        }
        else {
            _expressionOperatorPos = _ast->storage->addConstsExpressionOperator((*_instr)[(*_instrCrrntPos)++]->id);
            _node = _ast->getNodes(_instr, _instrCrrntPos, _crrntBlock, 0);
        }
        return new NodeExpression(
            !_frstValue->count ? NULL : _frstValue->frst->object, // Should not be NULL ever
            !_node->count ? NULL : _node->frst->object,
            _expressionOperatorPos
        );
}

int parser::convertToAst::NodeExpression::getExpressionPriority(utils::LinkedList<int>* _valTable) {
    int _exprValue = *((*_valTable)[expressionPos]);
    if (_exprValue >= TOKEN_MULTIPLICATION && _exprValue <= TOKEN_DECREMENT) return 2;
    if (_exprValue >= TOKEN_ADDITION && _exprValue <= TOKEN_SUBTRACTION) return 3;
    if (_exprValue >= TOKEN_BITWISEAND && _exprValue <= TOKEN_BITWISERIGHTSHIFT) return 4;
    if (_exprValue >= TOKEN_AND && _exprValue <= TOKEN_NOT) return 5;
    return -1;
}


/////////// Node Expression ///////////

parser::convertToAst::NodeParenthesis::NodeParenthesis(Node* _node) 
    : value(_node) { type = AST_NODE_PARENTHESIS; }

parser::convertToAst::NodeParenthesis* parser::convertToAst::NodeParenthesis::generate(
    utils::LinkedList <token::Token>* _instr, int* _instrCrrntPos, Ast* _ast, Block* _crrntBlock) {

        std::cout << "--> Generate Parenthesis <--" << std::endl;

        (*_instrCrrntPos)++;

        new NodeParenthesis(
            _ast->getNodes(
                _instr,
                _instrCrrntPos,
                _crrntBlock,
                0
            )->frst->object
        );

        (*_instrCrrntPos)++;

}

/////////// Block end ///////////

parser::convertToAst::BlockEnd::BlockEnd() { type = AST_NODE_BLOCKEND; }

parser::convertToAst::BlockEnd* 
    parser::convertToAst::BlockEnd::generate() {

        BlockEnd* _rtr = (BlockEnd*) malloc(sizeof(BlockEnd));
        new (_rtr) BlockEnd();

        return _rtr;

} 

/////////// Type Information ///////////

parser::convertToAst::TypeInformation::TypeInformation(int _typePos, int _pointerLevel, int _referenceLevel) : 
    typePos(_typePos), pointerLevel(_pointerLevel), referenceLevel(_referenceLevel) {}

/////////// Storage ///////////

parser::convertToAst::Storage::Storage() {
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

int parser::convertToAst::Storage::addKeyWord(int _value) {
    int _rtr;
    if ((_rtr = keyWords->getObjectPosition(
        &_value, [](int* _f, int* _s) -> bool { return *_f == *_s; })) == -1) 
            _rtr = keyWords->add(_value);
    return _rtr;
}

int parser::convertToAst::Storage::addAssignment(int _value) {
    int _rtr;
    if ((_rtr = assignment->getObjectPosition(
        &_value, [](int* _f, int* _s) -> bool { return *_f == *_s; })) == -1) 
            _rtr = assignment->add(_value);
    return _rtr;
}

int parser::convertToAst::Storage::addConstsNames(char* _value) {
    int _rtr;
    if ((_rtr = constsNames->getObjectPosition(_value, &utils::compareStrings)) == -1) 
        _rtr = constsNames->add(_value);
    return _rtr;
}

int parser::convertToAst::Storage::addConstsValue(char* _value) {
    int _rtr;
    if ((_rtr = constsValues->getObjectPosition(_value, &utils::compareStrings)) == -1) 
        _rtr = constsValues->add(_value);
    return _rtr;
}

int parser::convertToAst::Storage::addConstsExpressionOperator(int _value) {
    int _rtr;
    if ((_rtr = constsExpressionOperator->getObjectPosition(
        &_value, [](int* _f, int* _s) -> bool { return *_f == *_s; })) == -1) 
            _rtr = constsExpressionOperator->add(_value);
    return _rtr;
}

/////////// Environment ///////////

parser::convertToAst::Environment::Environment() {
    variablesDeclared = (utils::LinkedList <NodeVariableDeclaration>*) malloc(sizeof(utils::LinkedList <NodeVariableDeclaration>));
    new (variablesDeclared) utils::LinkedList <NodeVariableDeclaration>();
}

void parser::convertToAst::Environment::addVariableDeclaration(Node* _) { variablesDeclared->add( (NodeVariableDeclaration*) _); }

parser::convertToAst::NodeVariableDeclaration* parser::convertToAst::Environment::getVariableDeclaration(int _namePos) {
    for (int _ = 0; _ < variablesDeclared->count; _++)
        if ((*variablesDeclared)[_]->namePos == _namePos) return (*variablesDeclared)[_];
    return NULL;
}

/////////// Ast Exception ///////////

parser::convertToAst::AstException::AstException(char* _description) : description(_description) {}

char* parser::convertToAst::AstException::what() { return description; }

/////////// Ast ///////////

parser::convertToAst::Ast::Ast() : exception(NULL) {

    storage = (Storage*) malloc(sizeof(Storage));
    new (storage) Storage();

    globalBlock = (Block*) malloc(sizeof(Block));
    new (globalBlock) Block(NULL);

}

void parser::convertToAst::Ast::setException(char* _description) {

    exception = (parser::convertToAst::AstException*) malloc(sizeof(parser::convertToAst::AstException));
    new (exception) parser::convertToAst::AstException(_description);

    std::cout << "error: " << exception->what() << std::endl;

    exit(-1);

}

utils::LinkedList<parser::convertToAst::Node>* 
    parser::convertToAst::Ast::getNodes(utils::LinkedList <token::Token>* _instr, int* _instrCrrntPos, Block* _crrntBlock, bool _single) {

        std::cout << "In get" << std::endl;
        utils::LinkedList <Node>* _rtr = (utils::LinkedList <Node>*) malloc(sizeof(utils::LinkedList <Node>));
        new (_rtr) utils::LinkedList <Node>();
        
        int _, _type;
        token::Token* _tok, *_tok1;

        if (_instrCrrntPos == NULL) { // if _instrCrrntPos == NULL just set to value 0

            _ = 0;
            _instrCrrntPos = &_;

        }

        std::cout << "Get node -> " << (*_instr)[*_instrCrrntPos]->phr << std::endl;

        if ((*_instr)[(*_instrCrrntPos)]->id == TOKEN_ENDLINE) {

            (*_instrCrrntPos)++;

        }

        else if ((*_instr)[(*_instrCrrntPos)]->id == TOKEN_OPENCURLYBRACKET) {

            _rtr->add(
                Block::generate(_instr, _instrCrrntPos, this, _crrntBlock)
            );

        }

        else if ((*_instr)[(*_instrCrrntPos)]->id == TOKEN_CLOSECURLYBRACKET) {

            _rtr->add(
                BlockEnd::generate()
            );

            (*_instrCrrntPos)++;

        }

        else if ((_type = keyWordsReserved::checkIfWordIsVariableType((*_instr)[*_instrCrrntPos]->phr))) { // declaration type or function declaration

            _rtr->join(
                NodeVariableDeclaration::generate(_instr, _instrCrrntPos, _type, this, _crrntBlock)
            );
            
        }

        else if ((*_instr)[(*_instrCrrntPos)]->id == TOKEN_OPENPARENTHESES && _single) {

            _rtr->add(
                parser::convertToAst::NodeParenthesis::generate(_instr, _instrCrrntPos, this, _crrntBlock)
            );

        }

        else if (utils::isNumber((*_instr)[(*_instrCrrntPos)]->phr)) { // Frst word is number

            if (_single) { // Just use number

                _rtr->add(
                    NodeValue::generate(_instr, _instrCrrntPos, this)
                );

            } else { // Call expression contructor 

                _rtr->add(
                    NodeExpression::generate(_instr, _instrCrrntPos, this, _crrntBlock)
                );

            }

        }

        else { // is a word

            _tok = (*_instr)[(*_instrCrrntPos) + 1];
            _tok1 = (*_instr)[(*_instrCrrntPos) + 2];

            if (
                !_tok ? 0 : token::checkIfOperatorIsSingleAssignment(_tok->id) ||
                !_tok1 ? 0 : token::checkIfOperatorIsSingleAssignment(_tok1->id) && 
                _single
            ) { // Single Assignment

                _rtr->add(
                    NodeVariableAssignmetSingle::generate(_instr, _instrCrrntPos, this, _crrntBlock)
                );

            }

            else if (
                !_tok ? 0 : token::checkIfOperatorIsAssignment(_tok->id) &&
                !_single
            ) { // Assignment 

                _rtr->add(                   
                    NodeVariableAssignmet::generate(_instr, _instrCrrntPos, this, _crrntBlock)
                );

            }

            else if (
                !_tok ? 0 : token::checkIfExpressionOperator(_tok->id) &&
                !_single
            ) { // Expression 

                _rtr->add(                   
                    NodeExpression::generate(_instr, _instrCrrntPos, this, _crrntBlock)
                );

            }

            else if ((*_instr)[(*_instrCrrntPos)]->id == TOKEN_OPENPARENTHESES) {

                _rtr->add(
                    parser::convertToAst::NodeExpression::generate(_instr, _instrCrrntPos, this, _crrntBlock)
                );

            }

            else if (_single) {

                _rtr->add(
                    NodeVariableValue::generate(_instr, _instrCrrntPos, this, _crrntBlock)
                );

            }          

            else 
                
                _rtr->add(                   
                    NodeExpression::generate(_instr, _instrCrrntPos, this, _crrntBlock)
                );


        }

        return _rtr;

} 

void parser::convertToAst::Ast::generateAst(token::TokensCollection* _tokensColl) {

    tokensCollection = _tokensColl;
    int _ = 0;

    globalBlock->generateBlockBody(this, &_);

}



