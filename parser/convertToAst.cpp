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

parser::convertToAst::NodeExpression::NodeExpression(Node* _frst, Node* _scnd, int _exprPos) :
    frst(_frst), scnd(_scnd), expressionPos(_exprPos) { type = AST_NODE_EXPRESSION; }

void parser::convertToAst::NodeExpression::sortByPriority(utils::LinkedList<int>* _valTable) {

    if (expressionPos == -1) return;

    else if (frst->type == AST_NODE_PARENTHESIS) { // Parenthesis 

    }

    else if (frst->type == AST_NODE_EXPRESSION) { // frst is another expression 

        (
            (NodeExpression*) frst
        )->sortByPriority(_valTable);

        // ??

    }

}

int parser::convertToAst::NodeExpression::getExpressionPriority(utils::LinkedList<int>* _valTable) {

    int _exprValue = *((*_valTable)[expressionPos]);

    if (_exprValue >= TOKEN_MULTIPLICATION && _exprValue <= TOKEN_DECREMENT) return 2;
    if (_exprValue >= TOKEN_ADDITION && _exprValue <= TOKEN_SUBTRACTION) return 3;
    if (_exprValue >= TOKEN_BITWISEAND && _exprValue <= TOKEN_BITWISERIGHTSHIFT) return 4;
    if (_exprValue >= TOKEN_AND && _exprValue <= TOKEN_NOT) return 5;

    return -1;

}


parser::convertToAst::NodeVariableValue::NodeVariableValue(int _namePos) : 
    namePos(_namePos) { type = AST_NODE_VARIABLEVALUE; }

parser::convertToAst::NodeParenthesis::NodeParenthesis(Node* _node) 
    : value(_node) { type = AST_NODE_PARENTHESIS; }

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
    parser::convertToAst::Ast::generateVariableDeclaration(utils::LinkedList <token::Token>* _instr, int* _instrCrrntPos, int _type) {

        utils::LinkedList <Node>* _rtr = (utils::LinkedList <Node>*) malloc(sizeof(utils::LinkedList <Node>));
        new (_rtr) utils::LinkedList <Node>();

        int _keyWordPos, _constsNamesPos;
        bool _pntr;

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

        return _rtr;

}

parser::convertToAst::Node* 
    parser::convertToAst::Ast::generateValue(utils::LinkedList <token::Token>* _instr, int* _instrCrrntPos) {

        std::cout << "--> Node Value added <--" << std::endl;
        
        int _constsValuesPos;

        if ((_constsValuesPos = constsValues->getObjectPosition( // Check s if const value is already in LinkedList, if not added
            (*_instr)[(*_instrCrrntPos)]->phr, &utils::compareStrings)) == -1) 
                _constsValuesPos = constsValues->add((*_instr)[(*_instrCrrntPos)]->phr);
        (*_instrCrrntPos)++;

        return new NodeValue(_constsValuesPos);

}

parser::convertToAst::Node* 
    parser::convertToAst::Ast::generateVariableValue(utils::LinkedList <token::Token>* _instr, int* _instrCrrntPos) {

        std::cout << "--> Variable value use  <--" << std::endl;
        
        int _constsNamesPos;

        if ((_constsNamesPos = constsNames->getObjectPosition( // Check s if const name is already in LinkedList if not throw exception
            (*_instr)[(*_instrCrrntPos)++]->phr, &utils::compareStrings)) == -1) setException("Variable not defined");


        return new NodeVariableValue(_constsNamesPos);

}

parser::convertToAst::Node* 
    parser::convertToAst::Ast::generateExpression(utils::LinkedList <token::Token>* _instr, int* _instrCrrntPos, bool _isConst, bool _frstParenthesis) {

        int _frstValuePos, _expressionOperatorPos;
        parser::convertToAst::Node* _frstValue;
        utils::LinkedList<Node> *_node;

        std::cout << "--> Arithmetric expression added <--" << std::endl;

        if (_frstParenthesis) _frstValue = generateParenthesis(_instr, _instrCrrntPos);

        else _frstValue = _isConst ? generateValue(_instr, _instrCrrntPos) : generateVariableValue(_instr, _instrCrrntPos);

        if ((*_instr)[(*_instrCrrntPos)]->id == TOKEN_ENDLINE) {
            _node = (utils::LinkedList <Node>*) malloc(sizeof(utils::LinkedList <Node>)); 
            new (_node) utils::LinkedList <Node>();

            _expressionOperatorPos = -1;
        }

        else {
         
            if ((_expressionOperatorPos = constsExpressionOperator->getObjectPosition( // Check s if assignment type is already in LinkedList if not added
                &(*_instr)[(*_instrCrrntPos)]->id, [](int* _f, int* _s) -> bool { return *_f == *_s; })) == -1) 
                    _expressionOperatorPos = constsExpressionOperator->add(&(*_instr)[(*_instrCrrntPos)]->id);
            (*_instrCrrntPos)++;

            _node = getNodes(_instr, _instrCrrntPos);
            
        }

        return new NodeExpression(
            _frstValue,
            !_node->count ? NULL : _node->frst->object,
            _expressionOperatorPos
        );

}

parser::convertToAst::Node* 
    parser::convertToAst::Ast::generateVariableAssignment(utils::LinkedList <token::Token>* _instr, int* _instrCrrntPos) {

        std::cout << "--> Assignment added <--" << std::endl;
        
        int _constsNamesPos, _assignmentPos;

        if ((_constsNamesPos = constsNames->getObjectPosition( // Check s if const name is already in LinkedList if not throw exception
            (*_instr)[(*_instrCrrntPos)++]->phr, &utils::compareStrings)) == -1) setException("Variable not defined");

        if ((_assignmentPos = assignment->getObjectPosition( // Check s if assignment type is already in LinkedList if not added
            &(*_instr)[(*_instrCrrntPos)++]->id, [](int* _f, int* _s) -> bool { return *_f == *_s; })) != -1) 
                _assignmentPos = assignment->add(&(*_instr)[(*_instrCrrntPos)++]->id);
        
        utils::LinkedList<Node>* _node = getNodes(_instr, _instrCrrntPos);


        return new NodeVariableAssignmet(
            _constsNamesPos,
            _assignmentPos, 
            !_node->count ? NULL : _node->frst->object
        );

}

parser::convertToAst::Node* 
    parser::convertToAst::Ast::generateParenthesis(utils::LinkedList <token::Token>* _instr, int* _instrCrrntPos) {

        // Act like the only possible case is Expression //

        std::cout << "--> Generate Parenthesis <--" << std::endl;

        (*_instrCrrntPos)++;

        new NodeParenthesis(
            generateExpression(
                _instr, 
                _instrCrrntPos, 
                utils::isNumber((*_instr)[*_instrCrrntPos]->phr),
                0
            )
        );

        (*_instrCrrntPos)++;

}

utils::LinkedList<parser::convertToAst::Node>* 
    parser::convertToAst::Ast::getNodes(utils::LinkedList <token::Token>* _instr, int* _instrCrrntPos) { 

        utils::LinkedList <Node>* _rtr = (utils::LinkedList <Node>*) malloc(sizeof(utils::LinkedList <Node>));
        new (_rtr) utils::LinkedList <Node>();
        
        int _;

        if (!_instrCrrntPos) { // if _instrCrrntPos == NULL just set to value 0

            _ = 0;
            _instrCrrntPos = &_;

        }

        // std::cout << "Get node -> " << (*_instr)[*_instrCrrntPos]->id << " " << (*_instr)[*_instrCrrntPos]->phr << std::endl;
        // std::cout << "Next Instr -> " << (*_instr)[(*_instrCrrntPos) + 1]->id << " " << (*_instr)[(*_instrCrrntPos) + 1]->phr << std::endl;

        int _type, _assignmentPos, _expressionOperatorPos, _constsValuesPos, _keyWordPos, _constsNamesPos; 
        bool _pntr;

        if ((_type = keyWordsReserved::checkIfWordIsVariableType((*_instr)[*_instrCrrntPos]->phr))) { // declaration type or function declaration

            // Make work with function declaration // TODO

            if ((*_instr)[(*_instrCrrntPos) + 2]->id == TOKEN_EQUAL) // declaration type
                _rtr->join(
                    generateVariableDeclaration(_instr, _instrCrrntPos, _type)
                );

            else setException("Unexpected token");

        }

        else if (utils::isNumber((*_instr)[(*_instrCrrntPos)]->phr)) {

            if ((*_instr)[(*_instrCrrntPos) + 1]->id == TOKEN_ENDLINE || (*_instr)[(*_instrCrrntPos) + 1]->id == TOKEN_CLOSEPARENTHESES) // Just value

                _rtr->add(
                    generateValue(_instr, _instrCrrntPos)
                );

            else if (token::checkIfExpressionOperator((*_instr)[(*_instrCrrntPos) + 1]->id)) // Expression

                _rtr->add(
                    generateExpression(_instr, _instrCrrntPos, 1, 0)
                );

        }

        else if ((*_instr)[(*_instrCrrntPos)]->id == TOKEN_OPENPARENTHESES) { // Open parenthesis. just expression ?

            _rtr->add(
                generateExpression(_instr, _instrCrrntPos, 0, 1)
            );

        }

        else { // Common word <- ola = 10;

            if (token::checkIfOperatorIsAssignment((*_instr)[(*_instrCrrntPos) + 1]->id)) { // assignment to variable <- ola = 10;

                _rtr->add(
                    generateVariableAssignment(_instr, _instrCrrntPos)
                );

            }

            else if (token::checkIfExpressionOperator((*_instr)[(*_instrCrrntPos) + 1]->id)) // Expression

                _rtr->add(
                    generateExpression(_instr, _instrCrrntPos, 0, 0)
                );

            else {

                _rtr->add(
                    generateVariableValue(_instr, _instrCrrntPos)
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
