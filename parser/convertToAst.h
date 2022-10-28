#pragma once

#ifndef CONVERTTOAST_H
#define CONVERTTOAST_H

#define AST_NODE_BLOCK 1
#define AST_NODE_VARIABLEDECLARATION 2
#define AST_NODE_VALUE 3
#define AST_NODE_VARIABLEVALUE 4
#define AST_NODE_VARIABLEASSIGNMENT 5
#define AST_NODE_VARIABLEASSIGNMENTSINGLE 6
#define AST_NODE_EXPRESSION 7
#define AST_NODE_PARENTHESIS 8
#define AST_NODE_BLOCKEND 9 // Its temporary in tree

namespace utils { template <typename> struct LinkedList; }
namespace token { struct TokensCollection; struct Token; }

namespace parser::convertToAst {

    struct Environment;struct TypeInformation;struct Ast;struct NodeVariableDeclaration;

    /* Node default representation for all types of nodes 
    *   Should never be declared by it self !!
    */
    struct Node { int type; /* Node type representation */ };
    /* Hold a new Block of code created */
    struct Block : public Node {
        Environment* environment; // Environment 
        utils::LinkedList <Node>* body; //
        Block* previousBlock;
        Block(Block*);
        /**/
        void generateBlockBody(Ast*, int*);
        /**/
        parser::convertToAst::NodeVariableDeclaration* getVariableDeclaration(int);
        /**/
        static Block* generate(utils::LinkedList <token::Token>*, int*, Ast*, Block*);
    };
    /* Node to hold a variable declaration */
    struct NodeVariableDeclaration : public Node {
        TypeInformation* typeInfo; // Variable type information
        int namePos; // Value pos to const names in table
        Node* value; // Value assigned to this variable | NULL if no value assigned
        NodeVariableDeclaration(int, int, int, int, Node*);
        static utils::LinkedList <Node>* generate(utils::LinkedList <token::Token>*, int*, int, Ast*, Block*);
    };
    /* Node to hold a value */
    struct NodeValue : public Node { 
        int valuePos; // Value pos in const value table 
        NodeValue(int);
        static NodeValue* generate(utils::LinkedList <token::Token>*, int*, Ast*);
    };
    /* Node to hold a value of a variable name */
    struct NodeVariableValue : public Node {
        utils::LinkedList <int>* operatorsBeforeVariable; // All operators before variable * &
        NodeVariableDeclaration* declarationAddr; // Node Value Declaration address
        NodeVariableValue(utils::LinkedList <int>*, NodeVariableDeclaration*);
        static NodeVariableValue* generate(utils::LinkedList <token::Token>*, int*, Ast*, Block*);
    };
    /*  Node to hold a variable assignmet*/
    struct NodeVariableAssignmet : public Node {
        NodeVariableDeclaration* declarationAddr; // Node Value Declaration address 
        int assignmentPos; // Value pos to consts assignment in table
        Node* value; // Value assigned to this variable
        NodeVariableAssignmet(NodeVariableDeclaration*, int, Node*);
        static NodeVariableAssignmet* generate(utils::LinkedList <token::Token>*, int*, Ast*, Block*);
    };
    /*  Node to hold a variable assignmet Single | ++ --*/
    struct NodeVariableAssignmetSingle : public Node {
        NodeVariableDeclaration* declarationAddr; // Node Value Declaration address 
        bool assignmentIsPosLeft; // Is assignment in left side
        int assignmentPos; // Value pos to consts assignment in table
        NodeVariableAssignmetSingle(NodeVariableDeclaration*, bool, int);
        static NodeVariableAssignmetSingle* generate(utils::LinkedList <token::Token>*, int*, Ast*, Block*);
    };
    /* Node to hold a Expression
    *   First and Second value can either be a NodeValue, NodeVariableValue or another NodeExpression
    */
    struct NodeExpression : public Node {
        Node* frst, *scnd; // Value of first and second values 
        int expressionPos; // Expression value representation 
        NodeExpression(Node*, Node*, int);
        static NodeExpression* generate(utils::LinkedList <token::Token>*, int*, Ast*, Block*);
        /* Return value by expression value
        *   --> return table <--
        *       1 -> ()
        *       2 -> * / % ++ --
        *       3 -> + -
        *       4 -> & | ^ ~ << >>
        *       5 -> && || !
        */
        int getExpressionPriority(utils::LinkedList<int>*);
    };
    /* Node to mark a parenthesis occurrence */
    struct NodeParenthesis : public Node {
        Node* value; // Value inside parenthesis 
        NodeParenthesis(Node*);
        static NodeParenthesis* generate(utils::LinkedList <token::Token>*, int*, Ast*, Block*);
    };
    /* Means end of block of code */
    struct BlockEnd : public Node { BlockEnd(); static BlockEnd* generate(); };    
    /* Hold a the type information about declaration */
    struct TypeInformation {
        int typePos; // Type pos in type table
        int pointerLevel; // Pointer level of declared variable
        int referenceLevel; // Reference level of declared variable
        TypeInformation(int, int, int);
    };
    /* Store every value used in TokendsCollection */
    struct Storage {
        utils::LinkedList<int>* keyWords; // Hold all different keywords used accross TokensCollection
        utils::LinkedList<int>* assignment; // Hold all different assignment used accross TokensCollection
        utils::LinkedList<char>* constsNames; // Hold all different constants Name accross TokensCollection
        utils::LinkedList<char>* constsValues; // Hold all different constants Values accross TokensCollection
        utils::LinkedList<int>* constsExpressionOperator; // Hold all different constants Values accross TokensCollection
        Storage();
        /**/
        int addKeyWord(int);
        /**/
        int addAssignment(int);
        /**/
        int addConstsNames(char*);
        /**/
        int addConstsValue(char*);
        /**/
        int addConstsExpressionOperator(int);
    };
    /* Store every Block modification */
    struct Environment {
        utils::LinkedList <NodeVariableDeclaration>* variablesDeclared;
        Environment();
        /**/
        void addVariableDeclaration(Node*);
        /* Gets the variable declared by given name
        *   @param _namePos Pos of name in Consts Name table 
        *   @return Variable declared or NULL
        */
        NodeVariableDeclaration* getVariableDeclaration(int);
    };
    /* Hold any type of excetion occur in Ast generation*/
    struct AstException {
        char* description; // Exception description
        AstException(char*);
        char* what();
    };
    /* Ast */
    struct Ast {
        Storage* storage;
        Block* globalBlock;
        token::TokensCollection* tokensCollection;
        AstException* exception; // If any exception occur during Ast generation proccess must be saved here
        Ast();
        /* Set and throw exception */
        void setException(char*);
        /*  Generate a new Node
        *   @param  _instr Instruction to work with
        *   @param _instrCrrntPos Instruction current position
        */
        utils::LinkedList<parser::convertToAst::Node>* getNodes(utils::LinkedList <token::Token>*, int*, Block*, bool); 
        /*  Generate a new Ast
        *   @param _tokensColl Tokens collection generated by the src code
        */
        void generateAst(token::TokensCollection*);

    };

}

#endif