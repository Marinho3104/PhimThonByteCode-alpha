
#define BYTECODE_STACK_LOAD 0 // Load value into stack 
#define BYTECODE_STACK_NAME 1 // Create a new Assinged Variable with given argument (indicates name position) and top value in stack
#define BYTECODE_LOAD_NAME 2 // Puts the value assigned to name in top of stack
#define BYTECODE_GO_TO 3 // Go to indicate instruction by argument
#define BYTECODE_ADD 4 // Add last 2 values in stack and load it into stack
#define BYTECODE_SUB 5 // Subtract last 2 values in stack and load it into stack
#define BYTECODE_MUL 6 // Multiplicate last 2 values in stack and load it into stack
#define BYTECODE_DIV 7 // Divide last 2 values in stack and load it into stack
#define BYTECODE_MOD 8 // Module last 2 values in stack and load it into stack
#define BYTECODE_BITWISE_AND 9
#define BYTECODE_BITWISE_OR 10
#define BYTECODE_BITWISE_XOR 11
#define BYTECODE_BITWISE_LEFT_SHIFT 12
#define BYTECODE_BITWISE_RIGHT_SHIFT 13
#define BYTECODE_BITWISE_NOT 14
#define BYTECODE_PRINT 15 // Print top value of stack
