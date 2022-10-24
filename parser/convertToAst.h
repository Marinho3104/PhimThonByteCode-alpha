#pragma once

#ifndef CONVERTTOAST_H
#define CONVERTOTAST_H

#define AST_NODE_VARIABLEDECLARATION 0 // declaration of a variable -> int _ = 10
#define AST_NODE_EXPRESSION 1 // any expression -> 10 + 50

namespace utils { template <typename> struct LinkedList; }

namespace token { struct TokensCollection; struct Token; }

namespace parser::convertToAst {

    struct Node {

        int type;
        
    };

    struct Ast {

        utils::LinkedList<Node>* body;

    };
    
    struct NodeVariableDeclaration : public Node {

        int _varType;
        char* _varName;



    };

    struct NodeExpression : public Node {

        int type;
        Node* left, *right;

    };

    struct NodeValue : public Node { int value; };

    int getInstructionType(utils::LinkedList <token::Token>*);

    Node* handleSingleInstruction(utils::LinkedList <token::Token>*);

    Ast* createAst(token::TokensCollection*);

}

#endif