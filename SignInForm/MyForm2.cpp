#include "MyForm2.h"
using namespace SignInForm;

enum TypeToken_
{
    // Token types declaration
    IF,
    ELSE,
    WHILE,
    DO,
    FOR,
    RoundBracketOpen,
    RoundBracketClose,
    OPR,
    ID,
    FLOAT_,
    NUM,
    MINUS,
    OR,
    AND,
    NOTEQUAL,
    NOT,
    RIGHTSHIFT,
    LEFTSHIFT,
    MODULUS,
    LCB,
    RCB,
    MINUSEQ,
    DIV,
    BEGIN,
    END,
    MULTIEQ,
    LSB,
    RSB,
    PLUSPLUS,
    PLUS,
    PLUSEQ,
    EQEQ,
    EQUAL,
    SEMICOLON,
    COLON,
    COMMA,
    COMMENT,
    MINUSMINUS,
    LESS,
    MULTI,
    LESSEQ,
    GREATER,
    GREATEREQ,
    INT_,
    STRING,
    CHAR_,
    DOUBLE_
};

struct Token
{
    TypeToken_ tokenType; // Enum representing the token number
    string Value;                 // String representing the type of token
    int integerValue = 0;         // Integer value associated with the token (initialized to 0)

} _Token, currToken, nxtToken; // Two instances of the Token_ struct:  and current_token

typedef enum
{
    opk,
    constk,
    idk
} expkind;
typedef enum
{
    ifk,
    assignk,
    dok,
    whilek
} stmtkind;
typedef enum
{
    stmtk,
    expk
} nodekind1;

struct treenodde
{
    expkind expk;
    nodekind1 nodek;
    stmtkind stmtk;
    TypeToken_ Tok1;
    int value;
    string name;
    treenodde *leftchild = NULL;
    treenodde *rightchild = NULL;
    treenodde *middlechild = NULL;
    treenodde *sibling = NULL;
};

// Function Prototypes
void ungetToken();
Token gettToken();
Token Lexical();
treenodde *expression();
treenodde *term();
treenodde *factor();
void printTree(treenodde *, int, string);
int evaluateExpression(treenodde *);

bool flagBoolean = 0;
ifstream inFILE;
ofstream outPUT_file("TreeGeneration.txt");
ofstream evaluateExpFile("EvaluateExpression.txt");

// -- puBack funtion to set boolFLAG for token.
void ungetToken()
{
    flagBoolean = 1;
}

// getToken Function
Token gettToken()
{
    if (flagBoolean == 0) // Check if boolFLAG is 0
    {
        currToken = Lexical(); // Call Lexical function to obtain a new token
        return currToken;              // Return the new token
    }
    else
    {
        flagBoolean = 0;  // Set boolFLAG to 0
        return currToken; // Return the previously obtained token
    }
}

// Lexical function: Generates and returns the next token based on the input source code.
Token Lexical()
{
    char inputChar;
    string st = "";
    while (!inFILE.eof())
    {
        inFILE.get(inputChar);
        if (inputChar == '(')
        {
            _Token.tokenType = RoundBracketOpen;
            _Token.Value = "Round Bracket Open";
            return _Token;
        }
        else if (inputChar == ')')
        {
            _Token.tokenType = RoundBracketClose;
            _Token.Value = "Round Bracket Close";
            return _Token;
        }
        else if (inputChar == '[')
        {
            _Token.tokenType = LSB;
            _Token.Value = "Left Square Bracket";
            return _Token;
        }
        else if (inputChar == ']')
        {
            _Token.tokenType = RSB;
            _Token.Value = "Right Square Bracket";
            return _Token;
        }
        else if (inputChar == '{')
        {
            _Token.tokenType = LCB;
            _Token.Value = "Left Curly Bracket";
            return _Token;
        }
        else if (inputChar == '}')
        {
            _Token.tokenType = RCB;
            _Token.Value = "Right Curly Bracket";
            return _Token;
        }
        else if (inputChar == ';')
        {
            _Token.tokenType = SEMICOLON;
            _Token.Value = "Semi Colon";
            return _Token;
        }
        else if (inputChar == ':')
        {
            _Token.tokenType = COLON;
            _Token.Value = "Colon";
            return _Token;
        }
        else if (inputChar == ',')
        {
            _Token.tokenType = COMMA;
            _Token.Value = "Comma";
            return _Token;
        }
        else if (inputChar == '%')
        {
            _Token.tokenType = MODULUS;
            _Token.Value = "Modulus";
            return _Token;
        }
        else if (inputChar == '|')
        {
            inFILE.get(inputChar);
            if (inputChar == '|')
            {
                _Token.tokenType = OR;
                _Token.Value = "OR";
                return _Token;
            }
            else
            {
                inFILE.unget();
            }
        }
        else if (inputChar == '&')
        {
            inFILE.get(inputChar);
            if (inputChar == '&')
            {
                _Token.tokenType = AND;
                _Token.Value = "AND";
                return _Token;
            }
            else
            {
                inFILE.unget();
            }
        }
        else if (inputChar == '!')
        {
            inFILE.get(inputChar);
            if (inputChar == '=')
            {
                _Token.tokenType = NOTEQUAL;
                _Token.Value = "NOT Equal";
                return _Token;
            }
            else
            {
                inFILE.unget();
                _Token.tokenType = NOT;
                _Token.Value = "NOT";
                return _Token;
            }
        }
        else if (inputChar == '/')
        {
            // Check if the next character is '/'
            if (inFILE.peek() == '/')
            {
                cout << "Singleline comment found // \n";
                do
                {
                    inFILE.get(inputChar);
                } while (inputChar != '\n');
            }
            // Check if the next character is '*'
            else if (inFILE.peek() == '*')
            {
                cout << "Multiline comment found /*.... */\n";
                while (1)
                {
                    inFILE.get(inputChar);
                    if (inputChar == '*')
                    {
                        inFILE.get(inputChar);
                        if (inputChar == '/')
                        {
                            break;
                        }
                    }
                }
            }
            // If neither '/' nor '*', assume it's a division operator
            else
            {
                _Token.tokenType = DIV;
                _Token.Value = "DIV";
                return _Token;
            }
        }
        else if (inputChar == '*')
        {
            if (inputChar == '/')
            {
                _Token.tokenType = COMMENT;
                _Token.Value = "Comment";
                return _Token;
            }
            else if (inputChar == '=')
            {
                _Token.tokenType = MULTIEQ;
                _Token.Value = "Multiply Equal";
                return _Token;
            }
            else
            {
                _Token.tokenType = MULTI;
                _Token.Value = "Multiply";
                return _Token;
            }
        }

        else if (inputChar == '+')
        {
            inFILE.get(inputChar);
            if (inputChar == '=')
            {
                _Token.tokenType = PLUSEQ;
                _Token.Value = "Plus Equal";
                return _Token;
            }
            else if (inputChar == '+')
            {
                _Token.tokenType = PLUSPLUS;
                _Token.Value = "Plus Plus";
                return _Token;
            }
            else
            {
                inFILE.unget();
                _Token.tokenType = PLUS;
                _Token.Value = "Plus";
                return _Token;
            }
        }

        else if (inputChar == '-')
        {
            inFILE.get(inputChar);
            if (inputChar == '=')
            {
                _Token.tokenType = MINUSEQ;
                _Token.Value = "Minus Equal";
                return _Token;
            }
            else if (inputChar == '-')
            {
                _Token.tokenType = MINUSMINUS;
                _Token.Value = "Minus Minus";
                return _Token;
            }
            else
            {
                inFILE.unget();
                _Token.tokenType = MINUS;
                _Token.Value = "Minus";
                return _Token;
            }
        }

        else if (inputChar == '=')
        {
            inFILE.get(inputChar);
            if (inputChar == '=')
            {
                _Token.tokenType = EQEQ;
                _Token.Value = "Equal Equal";
                return _Token;
            }
            else
            {
                inFILE.unget();
                _Token.tokenType = EQUAL;
                _Token.Value = "Equal";
                return _Token;
            }
        }

        else if (inputChar == '<')
        {
            inFILE.get(inputChar);
            if (inputChar == '=')
            {
                _Token.tokenType = LESSEQ;
                _Token.Value = "Less Equal";
                return _Token;
            }
            else if (inputChar == '<')
            {
                _Token.tokenType = LEFTSHIFT;
                _Token.Value = "Left Shift";
                return _Token;
            }
            else
            {
                inFILE.unget();
                _Token.tokenType = LESS;
                _Token.Value = "Less";
                return _Token;
            }
        }

        else if (inputChar == '>')
        {
            inFILE.get(inputChar);
            if (inputChar == '=')
            {
                _Token.tokenType = GREATEREQ;
                _Token.Value = "Greater Equal";
                return _Token;
            }
            else if (inputChar == '>')
            {
                _Token.tokenType = RIGHTSHIFT;
                _Token.Value = "Right Shift";
                return _Token;
            }
            else
            {
                inFILE.unget();
                _Token.tokenType = GREATER;
                _Token.Value = "Greater";
                return _Token;
            }
        }

        else if (isdigit(inputChar))
        {
            string word = "";

            while (isdigit(inputChar))
            {
                word += inputChar;
                if (inFILE.peek() == EOF)
                    break;
                inFILE.get(inputChar);
            }
            inFILE.seekg(-1, ios::cur);
            _Token.tokenType = NUM;
            _Token.Value = "Number";
            _Token.integerValue = stoi(word);
            return _Token;
        }

        else if (((int)inputChar >= 65 && (int)inputChar <= 99) || ((int)inputChar >= 97 && (int)inputChar <= 122))
        {
            st = "";
            do
            {
                st += inputChar;
                inFILE.get(inputChar);
            } while (isalnum(inputChar) && st != "END");
            if (st != "END")
            {
                inFILE.unget();
            }
            char v;
            if (st == "int")
            {
                string b = "";
                do
                {
                    inFILE.get(inputChar);
                    v = inputChar;
                } while (v != '=');
                inFILE.get(inputChar);
                do
                {
                    b += inputChar;
                    inFILE.get(inputChar);
                } while (isdigit(inputChar));
                _Token.tokenType = INT_;
                _Token.Value = "Integer";
                return _Token;
            }
            else if (st == "string")
            {
                string b = "", v1, x;
                do
                {
                    inFILE.get(inputChar);
                    v1 = inputChar;
                } while (v1 != "=");
                inFILE.get(inputChar);
                do
                {
                    b += inputChar;
                    inFILE.get(inputChar);
                    x = inputChar;
                } while (x != "'");
                _Token.tokenType = STRING;
                _Token.Value = "String";
                return _Token;
            }
            else if (st == "for")
            {
                _Token.tokenType = FOR;
                _Token.Value = "For";
                return _Token;
            }
            else if (st == "while")
            {
                _Token.tokenType = WHILE;
                _Token.Value = "While";
                return _Token;
            }
            else if (st == "BEGIN")
            {
                _Token.tokenType = BEGIN;
                _Token.Value = "Begin";
                return _Token;
            }
            else if (st == "END")
            {
                _Token.tokenType = END;
                _Token.Value = "End";
                return _Token;
            }
            else if (st == "do")
            {
                _Token.tokenType = DO;
                _Token.Value = "Do";
                return _Token;
            }
            else if (st == "if")
            {
                _Token.tokenType = IF;
                _Token.Value = "If";
                return _Token;
            }
            else if (st == "else")
            {
                _Token.tokenType = ELSE;
                _Token.Value = "Else";
                return _Token;
            }
            else if (st == "float")
            {
                _Token.tokenType = FLOAT_;
                _Token.Value = "Float";
                return _Token;
            }
            else if (st == "double")
            {
                _Token.tokenType = DOUBLE_;
                _Token.Value = "Double";
                return _Token;
            }
            else
            {
                _Token.tokenType = ID;
                _Token.Value = "Variable";
                return _Token;
            }
        }
    }
    return _Token;
}

treenodde *expression()
{
    treenodde *t = nullptr;
    treenodde *p = nullptr;
    int boolFLAGe = 0;
    do
    {
        t = term();
        if (boolFLAGe)
        {
            p->rightchild = t;
            boolFLAGe = 0;
            t = p;
        }
        _Token = gettToken();
        if (_Token.tokenType == PLUS || _Token.tokenType == MINUS)
        {
            p = new treenodde;
            p->expk = opk;
            p->Tok1 = _Token.tokenType;
            p->leftchild = t;
            boolFLAGe = 1;
        }
    } while (_Token.tokenType == PLUS || _Token.tokenType == MINUS);
    ungetToken();
    return (t);
}

treenodde *term()
{
    treenodde *t = nullptr;
    treenodde *p = nullptr;
    int boolFLAGe = 0;
    do
    {
        t = factor();
        if (boolFLAGe)
        {
            p->rightchild = t;
            boolFLAGe = 0;
            t = p;
        }
        _Token = gettToken();
        if (_Token.tokenType == MULTI || _Token.tokenType == DIV || _Token.tokenType == MODULUS)
        {
            p = new treenodde;
            p->expk = opk;
            p->Tok1 = _Token.tokenType;
            p->leftchild = t;
            boolFLAGe = 1;
        }
    } while (_Token.tokenType == MULTI || _Token.tokenType == DIV || _Token.tokenType == MODULUS);
    ungetToken();
    return t;
}

treenodde *factor()
{
    treenodde *t;
    _Token = gettToken();
    switch (_Token.tokenType)
    {
    case NUM:
        t = new treenodde();
        t->expk = constk;
        t->value = _Token.integerValue;
        t->Tok1 = _Token.tokenType;
        t->name = "Num";
        t->leftchild = NULL;
        t->rightchild = NULL;
        return t;
        break;

    case ID:
        t = new treenodde();
        t->expk = idk;
        t->value = _Token.integerValue;
        t->Tok1 = _Token.tokenType;
        t->name = "ID";
        t->leftchild = NULL;
        t->rightchild = NULL;
        return t;
        break;

    case RoundBracketOpen:
        t = expression();
        nxtToken = gettToken();
        if (nxtToken.tokenType != RoundBracketClose)
        {
            cout << "\nInvalid Input\nexiting...";
            exit(0);
        }
        return t;
    default:
        cout << "\nInvalid Input\nexiting...";
        exit(0);
        return t;
        break;
    }
}

void displayTree(treenodde *node, int indent = 0, string childType = "", int prevOperator = -1)
{
    ofstream outputFILE("TreeGeneration.txt", ios::app);

    // Check if the file was opened successfully
    if (!outputFILE.is_open())
    {
        cout << "Failed to open TreeGeneration.txt" << endl;
        return;
    }

    if (node == NULL)
        return;

    if (node->expk == opk)
    {
        outputFILE << setw(indent) << ""
                   << "+- Operator (" << childType << "): ";

        switch (node->Tok1)
        {
        case PLUS:
            outputFILE << "PLUS" << endl;
            break;

        case MINUS:
            outputFILE << "MINUS" << endl;
            break;

        case MULTI:
            outputFILE << "MULTIPLY" << endl;
            break;

        case DIV:
            outputFILE << "DIVIDE" << endl;
            break;

        case MODULUS:
            outputFILE << "MOD" << endl;
            break;

        default:
            outputFILE << "Unknown operator" << endl;
            break;
        }
    }
    else if (node->expk == constk)
    {
        outputFILE << setw(indent) << ""
                   << "+- Constant (" << childType << "): " << node->value << endl;
    }
    else if (node->expk == idk)
    {
        outputFILE << setw(indent) << ""
                   << "+- Identifier (" << childType << "): " << node->name << endl;
    }

    // Process left child
    if (node->leftchild != NULL)
    {
        outputFILE << setw(indent) << ""
                   << "|";
        displayTree(node->leftchild, indent + 4, "LeftChild", node->Tok1);
    }

    // Process right child only if the operator is different from the previous one
    if (node->rightchild != NULL && node->Tok1 != prevOperator)
    {
        outputFILE << setw(indent) << ""
                   << "|";
        displayTree(node->rightchild, indent + 4, "RightChild", node->Tok1);
    }
}

treenodde *statement()
{
    treenodde *t1;
    treenodde *tree;
    _Token = gettToken();
    if (_Token.tokenType == ID)
    {
        tree = new treenodde; // node for statement
        tree->nodek = stmtk;
        tree->stmtk = assignk;

        /* identifierNode = new treenode;
         identifierNode->kind = Identifier;
         identifierNode->name = token.name;
         identifierNode->leftchild = nullptr;
         identifierNode->rightchild = nullptr;*/

        _Token = gettToken();
        if (_Token.tokenType == EQUAL)
        {

            /*tree = new treenode;
            tree->kind = ooperator;
            tree->name = token.name;
            operatorNode->leftchild = nullptr;
            operatorNode->rightchild = nullptr;

            Link the operator node as the left child of the identifier node
            identifierNode->leftchild = operatorNode;*/

            if ((t1 = expression()))
            {
                tree->leftchild = t1;
                _Token = gettToken();
                if (_Token.tokenType == SEMICOLON)
                    return (tree);
            }
        }
    }
    return nullptr;
}

treenodde *statement_list() // statement list
{
    treenodde *stree;
    treenodde *prevtree;
    treenodde *stmttree;
    if ((prevtree = statement()))
    {
        prevtree->sibling = NULL;
        stmttree = prevtree;
        stmttree->sibling = NULL;
        do
        {
            _Token = gettToken();
            if (_Token.tokenType == IF || _Token.tokenType == DO || _Token.tokenType == ID)
            {
                ungetToken();
                if ((stree = statement()) == NULL) // NOT TRUE
                    return NULL;

                stree->sibling = NULL;
                prevtree->sibling = stree;
                prevtree = stree;
            }
            else
            {
                ungetToken();
                break;
            }

        } while (1);
        // return true; // if , not, uid not equal then may be else
        return (stmttree);
    }
    return NULL; // otherwise false
}

// bool program()
//{
//     treenodde* fulltree;
//     _Token = gettToken();
//     if (_Token.tokenType == BEGIN)
//     {
//         if ((fulltree = statement_list()) != NULL)
//         {
//             _Token = gettToken();
//             if (_Token.tokenType == END)
//                 return true;
//         }
//     }
//     return false;
// }

int evaluateExpression(treenodde *root)
{
    if (root == nullptr)
    {
        return 0;
    }

    switch (root->expk)
    {
    case opk:
        switch (root->Tok1)
        {
        case PLUS:
            return evaluateExpression(root->leftchild) + evaluateExpression(root->rightchild);
        case MINUS:
            return evaluateExpression(root->leftchild) - evaluateExpression(root->rightchild);
        case MULTI:
            return evaluateExpression(root->leftchild) * evaluateExpression(root->rightchild);
        case DIV:
            return evaluateExpression(root->leftchild) / evaluateExpression(root->rightchild);
        default:
            return 0;
        }
    case constk:
        return root->value;
    case idk:
        // You can handle variable evaluation here if needed
        return 0;
    default:
        return 0;
    }
}

void runProgram()
{
    inFILE.open("TreeExp.txt");
    if (!inFILE)
    {
        cout << "Unable to open file." << endl;
    }
    treenodde *expressionTree = expression();
    //	// Print the expression tree
    displayTree(expressionTree, 0, "Root", -1);

    int result = evaluateExpression(expressionTree);
    evaluateExpFile << result << endl;

    evaluateExpFile.close();
    inFILE.close();
    outPUT_file.close();
}

//// -- Driver Program
// int main() {
//     inputFILE.open("049.txt");
//     if (!inputFILE) {
//         cout << "Unable to open file." << endl;
//         return 0;
//     }
//     treenode* expressionTree = expression();
//     // Print the expression tree
//     printTree(expressionTree, 0, "Root", -1);
//
//     int result = evaluateExpression(expressionTree);
//     cout << "The Result is: " << result << endl;
//
//
//     inputFILE.close();
//     system("pause");
//     return 0;
// }