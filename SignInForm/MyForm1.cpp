#include "MyForm1.h"

using namespace SignInForm;

enum _TokenType
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

struct Token_
{
    _TokenType TokenNumber; // Enum representing the token number
    string TokenType;               // String representing the type of token
    int value = 0;                  // Integer value associated with the token (initialized to 0)

} Tokn, current_token; // Two instances of the Token_ struct:  and current_token

ifstream MyFile;
ofstream outFile("TokenGen.txt");

// Function Prototypes
bool statement_list();
void unGetTOKEN();
Token_ gettToken();
Token_ Lexical();
bool Program();
bool Statement_();
bool IfStmt_();
bool IfElseIFstmnt_();
bool IfElseStmt_();
bool DoWhileStmt_();
bool WhileStmt_();
bool Expression_();
bool Term_();
bool Factor_();
bool expr_();
bool ORexp_();
bool ANDexp_();
bool EQexp_();
bool CMPexp_();
bool ShiftExp_();
void displayTokens();

bool flag = 0;

// -- puBack funtion to set flag for token.
void unGetTOKEN()
{
    flag = 1;
}

Token_ gettToken()
{
    if (flag == 0) // Check if flag is 0
    {
        current_token = Lexical(); // Call Lexical function to obtain a new token
        return current_token;              // Return the new token
    }
    else
    {
        flag = 0;             // Set flag to 0
        return current_token; // Return the previously obtained token
    }
}

// Lexical function: Generates and returns the next token based on the input source code.
Token_ Lexical()
{
    char inputChar;
    string st = "";
    string ST = "";
    while (!MyFile.eof())
    {
        MyFile.get(inputChar);
        if (inputChar == '(')
        {
            Tokn.TokenNumber = RoundBracketOpen;
            Tokn.TokenType = "Round Bracket Open";
            displayTokens();
            return Tokn;
        }
        else if (inputChar == ')')
        {
            Tokn.TokenNumber = RoundBracketClose;
            Tokn.TokenType = "Round Bracket Close";
            displayTokens();
            return Tokn;
        }
        else if (inputChar == '[')
        {
            Tokn.TokenNumber = LSB;
            Tokn.TokenType = "Left Square Bracket";
            displayTokens();
            return Tokn;
        }
        else if (inputChar == ']')
        {
            Tokn.TokenNumber = RSB;
            Tokn.TokenType = "Right Square Bracket";
            displayTokens();
            return Tokn;
        }
        else if (inputChar == '{')
        {
            Tokn.TokenNumber = LCB;
            Tokn.TokenType = "Left Curly Bracket";
            displayTokens();
            return Tokn;
        }
        else if (inputChar == '}')
        {
            Tokn.TokenNumber = RCB;
            Tokn.TokenType = "Right Curly Bracket";
            displayTokens();
            return Tokn;
        }
        else if (inputChar == ';')
        {
            Tokn.TokenNumber = SEMICOLON;
            Tokn.TokenType = "Semi Colon";
            displayTokens();
            return Tokn;
        }
        else if (inputChar == ':')
        {
            Tokn.TokenNumber = COLON;
            Tokn.TokenType = "Colon";
            displayTokens();
            return Tokn;
        }
        else if (inputChar == ',')
        {
            Tokn.TokenNumber = COMMA;
            Tokn.TokenType = "Comma";
            displayTokens();
            return Tokn;
        }
        else if (inputChar == '%')
        {
            Tokn.TokenNumber = MODULUS;
            Tokn.TokenType = "Modulus";
            displayTokens();
            return Tokn;
        }
        else if (inputChar == '||')
        {
            Tokn.TokenNumber = OR;
            Tokn.TokenType = "OR";
            displayTokens();
            return Tokn;
        }
        else if (inputChar == '&&')
        {
            Tokn.TokenNumber = AND;
            Tokn.TokenType = "AND";
            displayTokens();
            return Tokn;
        }
        else if (inputChar == '!')
        {
            MyFile.get(inputChar);
            if (inputChar == '=')
            {
                Tokn.TokenNumber = NOTEQUAL;
                Tokn.TokenType = "NOT Equal";
                displayTokens();
                return Tokn;
            }
            else
            {
                MyFile.unget();
                Tokn.TokenNumber = NOT;
                Tokn.TokenType = "NOT";
                displayTokens();
                return Tokn;
            }
        }
        else if (inputChar == '/')
        {
            MyFile.get(inputChar);
            if (inputChar == '/')
            {
                cout << "Singleline comment found // \n";
                do
                {
                    MyFile.get(inputChar);
                } while (inputChar != '\n');
            }
            else if (inputChar == '*')
            {
                cout << "Multiline comment found /*.... */\n";
                while (1)
                {
                    MyFile.get(inputChar);
                    if (inputChar == '*')
                    {
                        MyFile.get(inputChar);
                        if (inputChar == '/')
                        {
                            break;
                        }
                    }
                }
            }
            else
            {
                Tokn.TokenNumber = DIV;
                Tokn.TokenType = "DIV";
                displayTokens();
                return Tokn;
            }
        }
        else if (inputChar == '*')
        {
            if (inputChar == '/')
            {
                Tokn.TokenNumber = COMMENT;
                Tokn.TokenType = "Comment";
                displayTokens();
                return Tokn;
            }
            else if (inputChar == '=')
            {
                Tokn.TokenNumber = MULTIEQ;
                Tokn.TokenType = "Multiply Equal";
                displayTokens();
                return Tokn;
            }
            else
            {
                Tokn.TokenNumber = MULTI;
                Tokn.TokenType = "Multiply";
                displayTokens();
                return Tokn;
            }
        }

        else if (inputChar == '+')
        {
            MyFile.get(inputChar);
            if (inputChar == '=')
            {
                Tokn.TokenNumber = PLUSEQ;
                Tokn.TokenType = "Plus Equal";
                displayTokens();
                return Tokn;
            }
            else if (inputChar == '+')
            {
                Tokn.TokenNumber = PLUSPLUS;
                Tokn.TokenType = "Plus Plus";
                displayTokens();
                return Tokn;
            }
            else
            {
                MyFile.unget();
                Tokn.TokenNumber = PLUS;
                Tokn.TokenType = "Plus";
                displayTokens();
                return Tokn;
            }
        }

        else if (inputChar == '-')
        {
            MyFile.get(inputChar);
            if (inputChar == '=')
            {
                Tokn.TokenNumber = MINUSEQ;
                Tokn.TokenType = "Minus Equal";
                displayTokens();
                return Tokn;
            }
            else if (inputChar == '-')
            {
                Tokn.TokenNumber = MINUSMINUS;
                Tokn.TokenType = "Minus Minus";
                displayTokens();
                return Tokn;
            }
            else
            {
                MyFile.unget();
                Tokn.TokenNumber = MINUS;
                Tokn.TokenType = "Minus";
                displayTokens();
                return Tokn;
            }
        }

        else if (inputChar == '=')
        {
            MyFile.get(inputChar);
            if (inputChar == '=')
            {
                Tokn.TokenNumber = EQEQ;
                Tokn.TokenType = "Equal Equal";
                displayTokens();
                return Tokn;
            }
            else
            {
                MyFile.unget();
                Tokn.TokenNumber = EQUAL;
                Tokn.TokenType = "Equal";
                displayTokens();
                return Tokn;
            }
        }

        else if (inputChar == '<')
        {
            MyFile.get(inputChar);
            if (inputChar == '=')
            {
                Tokn.TokenNumber = LESSEQ;
                Tokn.TokenType = "Less Equal";
                displayTokens();
                return Tokn;
            }
            else if (inputChar == '<')
            {
                Tokn.TokenNumber = LEFTSHIFT;
                Tokn.TokenType = "Left Shift";
                displayTokens();
                return Tokn;
            }
            else
            {
                MyFile.unget();
                Tokn.TokenNumber = LESS;
                Tokn.TokenType = "Less";
                displayTokens();
                return Tokn;
            }
        }

        else if (inputChar == '>')
        {
            MyFile.get(inputChar);
            if (inputChar == '=')
            {
                Tokn.TokenNumber = GREATEREQ;
                Tokn.TokenType = "Greater Equal";
                displayTokens();
                return Tokn;
            }
            else if (inputChar == '>')
            {
                Tokn.TokenNumber = RIGHTSHIFT;
                Tokn.TokenType = "Right Shift";
                displayTokens();
                return Tokn;
            }
            else
            {
                MyFile.unget();
                Tokn.TokenNumber = GREATER;
                Tokn.TokenType = "Greater";
                displayTokens();
                return Tokn;
            }
        }

        else if ((int)inputChar >= 48 && (int)inputChar <= 57)
        {
            string b = "";
            do
            {
                b += inputChar;
                MyFile.get(inputChar);
            } while (isdigit(inputChar));
            MyFile.unget();
            Tokn.TokenNumber = NUM;
            Tokn.TokenType = "Number";
            displayTokens();
            return Tokn;
        }

        else if (((int)inputChar >= 65 && (int)inputChar <= 99) || ((int)inputChar >= 97 && (int)inputChar <= 122))
        {
            st = "";
            ST = "";
            do
            {
                ST += toupper(inputChar);
                st += inputChar;
                MyFile.get(inputChar);
            } while (isalnum(inputChar) && st != "END");
            if (st != "END")
            {
                MyFile.unget();
            }
            char v;
            
            if (st == "int")
            {
                string b = "";
                do
                {
                    MyFile.get(inputChar);
                    v = inputChar;
                } while (v != '=');
                MyFile.get(inputChar);
                do
                {
                    b += inputChar;
                    MyFile.get(inputChar);
                } while (isdigit(inputChar));
                Tokn.TokenNumber = INT_;
                Tokn.TokenType = "Integer";
                displayTokens();
                return Tokn;
            }
            else if (st == "string")
            {
                string b = "", v1, x;
                do
                {
                    MyFile.get(inputChar);
                    v1 = inputChar;
                } while (v1 != "=");
                MyFile.get(inputChar);
                do
                {
                    b += inputChar;
                    MyFile.get(inputChar);
                    x = inputChar;
                } while (x != "'");
                Tokn.TokenNumber = STRING;
                Tokn.TokenType = "String";
                displayTokens();
                return Tokn;
            }
            else if (st == "for")
            {
                Tokn.TokenNumber = FOR;
                Tokn.TokenType = "For";
                displayTokens();
                return Tokn;
            }
            else if (st == "while")
            {
                Tokn.TokenNumber = WHILE;
                Tokn.TokenType = "While";
                displayTokens();
                return Tokn;
            }
            else if (st == "BEGIN" || ST == "BEGIN")
            {
                Tokn.TokenNumber = BEGIN;
                Tokn.TokenType = "Begin";
                displayTokens();
                return Tokn;
            }
            else if (st == "END" || ST == "END")
            {
                Tokn.TokenNumber = END;
                Tokn.TokenType = "End";
                displayTokens();
                return Tokn;
            }
            else if (st == "do")
            {
                Tokn.TokenNumber = DO;
                Tokn.TokenType = "Do";
                displayTokens();
                return Tokn;
            }
            else if (st == "if")
            {
                Tokn.TokenNumber = IF;
                Tokn.TokenType = "If";
                displayTokens();
                return Tokn;
            }
            else if (st == "else")
            {
                Tokn.TokenNumber = ELSE;
                Tokn.TokenType = "Else";
                displayTokens();
                return Tokn;
            }
            else if (st == "float")
            {
                Tokn.TokenNumber = FLOAT_;
                Tokn.TokenType = "Float";
                displayTokens();
                return Tokn;
            }
            else if (st == "double")
            {
                Tokn.TokenNumber = DOUBLE_;
                Tokn.TokenType = "Double";
                displayTokens();
                return Tokn;
            }
            else
            {
                Tokn.TokenNumber = ID;
                Tokn.TokenType = "Variable";
                displayTokens();
                return Tokn;
            }
        }
    }
    return Tokn;
}

bool statement_list()
{

    bool hasStatement = false;

    while (true)
    {

        Tokn = gettToken();

        if (Tokn.TokenNumber == IF || Tokn.TokenNumber == DO ||
            Tokn.TokenNumber == ID || Tokn.TokenNumber == WHILE)
        {
            unGetTOKEN();
            if (!Statement_())
            {
                return false;
            }
            hasStatement = true;
        }
        else
        {
            unGetTOKEN();
            break;
        }
    }

    /*if at least one statement is encountered or the loop is not executed at all,
    return true. otherwise return false.
    */
    return hasStatement || !hasStatement;
}

bool Statement_()
{
    Tokn = gettToken(); // Get the next token

    if (Tokn.TokenNumber == ID) // Check if the token number is ID
    {
        Tokn = gettToken(); // Get the next token

        if (Tokn.TokenNumber == EQUAL || Tokn.TokenNumber == NOTEQUAL ||
            Tokn.TokenNumber == PLUSEQ || Tokn.TokenNumber == MINUSEQ || Tokn.TokenNumber == EQEQ)
        {
            if (ORexp_()) // Call ORexp_ function
            {
                Tokn = gettToken(); // Get the next token

                if (Tokn.TokenNumber == SEMICOLON) // Check if the token number is SEMICOLON
                    return true;                               // Return true if a valid statement is found
            }
        }
    }

    // Check for if-else statement
    else if (IfElseStmt_()) // Check if it's a valid if-statement
    {
        return true; // Return true if a valid if-statement is found
    }

    else if (IfStmt_()) // Check if it's a valid if-statement
    {
        return true; // Return true if a valid if-statement is found
    }

    else if (IfElseIFstmnt_()) // Check if it's a valid if-else statement
    {
        return true; // Return true if a valid if-else statement is found
    }

    else if (WhileStmt_()) // Check if it's a valid while statement
    {
        return true; // Return true if a valid while statement is found
    }
    else if (DoWhileStmt_()) // Check if it's a valid do-while statement
    {
        return true; // Return true if a valid while statement is found
    }

    return false; // Return false if no valid statement is found
}

bool IfStmt_()
{
    if (Tokn.TokenNumber == IF)
    {
        Tokn = gettToken(); // Get the next token

        if (Tokn.TokenNumber == RoundBracketOpen) // Check if the token number is RoundBracketOpen
        {
            if (expr_()) // Call expr_ function
            {
                Tokn = gettToken(); // Get the next token

                if (Tokn.TokenNumber == RoundBracketClose) // Check if the token number is RoundBracketClose
                {
                    Tokn = gettToken(); // Get the next token

                    if (Tokn.TokenNumber == LCB) // Check if the token number is LCB
                    {
                        if (statement_list()) // Call statement_list function
                        {
                            Tokn = gettToken(); // Get the next token

                            if (Tokn.TokenNumber == RCB)
                            { // Check if the token number is RCB

                                Tokn = gettToken();

                                if (Tokn.TokenNumber == ELSE)
                                {

                                    return false;
                                }
                                else
                                    return true; // Return true if a valid if statement is parsed successfully
                            }
                        }
                    }
                }
            }
        }
    }

    return false; // Return false if any condition fails
}

bool IfElseStmt_()
{
    if (Tokn.TokenNumber == IF)
    {
        Tokn = gettToken(); // Get the next token

        if (Tokn.TokenNumber == RoundBracketOpen) // Check if the token number is RoundBracketOpen
        {
            if (expr_()) // Call expr_ function
            {
                Tokn = gettToken(); // Get the next token

                if (Tokn.TokenNumber == RoundBracketClose) // Check if the token number is RoundBracketClose
                {
                    Tokn = gettToken(); // Get the next token

                    if (Tokn.TokenNumber == LCB) // Check if the token number is LCB
                    {
                        if (statement_list()) // Call statement_list function
                        {
                            Tokn = gettToken(); // Get the next token

                            if (Tokn.TokenNumber == RCB)
                            { // Check if the token number is RCB

                                Tokn = gettToken();

                                if (Tokn.TokenNumber == ELSE)
                                {

                                    Tokn = gettToken();

                                    if (Tokn.TokenNumber == LCB) // Check if the token number is LCB
                                    {
                                        if (statement_list()) // Call statement_list function
                                        {
                                            Tokn = gettToken(); // Get the next token

                                            if (IfStmt_())
                                            {

                                                Tokn = gettToken();

                                                if (Tokn.TokenNumber == RCB)
                                                {                // Check if the token number is RCB
                                                    return true; // Return true  if a valid statement is found
                                                }
                                            }
                                        }
                                    }
                                }
                                else
                                    unGetTOKEN();
                                return true;
                            }
                        }
                    }
                }
            }
        }
    }

    return false; // Return false if any condition fails
}

bool IfElseIFstmnt_()
{
    if (Tokn.TokenNumber == IF)
    {
        Tokn = gettToken(); // Get the next token

        if (Tokn.TokenNumber == RoundBracketOpen) // Check if the token number is RoundBracketOpen
        {
            if (expr_()) // Call expr_ function
            {
                Tokn = gettToken(); // Get the next token

                if (Tokn.TokenNumber == RoundBracketClose) // Check if the token number is RoundBracketClose
                {
                    Tokn = gettToken(); // Get the next token

                    if (Tokn.TokenNumber == LCB) // Check if the token number is LCB
                    {
                        if (statement_list()) // Call statement_list function
                        {
                            Tokn = gettToken(); // Get the next token

                            if (Tokn.TokenNumber == RCB)
                            { // Check if the token number is RCB

                                Tokn = gettToken();

                                if (Tokn.TokenNumber == ELSE) // Check if the token number is ELSE
                                {
                                    Tokn = gettToken();

                                    if (IfStmt_())
                                    {

                                        Tokn = gettToken();

                                        if (Tokn.TokenNumber == LCB) // Check if the token number is LCB
                                        {
                                            if (statement_list()) // Call statement_list function
                                            {
                                                Tokn = gettToken(); // Get the next token

                                                if (Tokn.TokenNumber == RCB) // Check if the token number is RCB
                                                    return true;                         // Return true if a valid statement is found
                                            }
                                        }
                                    }
                                }
                            }
                            else
                                unGetTOKEN();
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false; // Return false if any condition fails
}

bool DoWhileStmt_()
{
    if (Tokn.TokenNumber == DO) // Check if the token number is DO
    {
        Tokn = gettToken(); // Get the next token

        if (Tokn.TokenNumber == LCB) // Check if the token number is LCB
        {

            if (statement_list()) // Call statement_list function
            {
                Tokn = gettToken(); // Get the next token

                if (Tokn.TokenNumber == RCB) // Check if the token number is RCB
                {
                    Tokn = gettToken(); // Get the next token

                    if (Tokn.TokenNumber == WHILE) // Check if the token number is WHILE
                    {
                        Tokn = gettToken(); // Get the next token

                        if (Tokn.TokenNumber == RoundBracketOpen) // Check if the token number is RoundBracketOpen
                        {

                            if (expr_()) // Call expr_ function
                            {
                                Tokn = gettToken(); // Get the next token

                                if (Tokn.TokenNumber == RoundBracketClose) // Check if the token number is RoundBracketClose
                                {
                                    Tokn = gettToken(); // Get the next token

                                    if (Tokn.TokenNumber == SEMICOLON) // Check if the token number is SEMICOLON
                                        return true;                               // Return true if the DO statement is valid
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return false; // Return false if any condition fails
}

bool WhileStmt_()
{
    if (Tokn.TokenNumber == WHILE) // Check if the token number is WHILE
    {
        Tokn = gettToken(); // Get the next token

        if (Tokn.TokenNumber == RoundBracketOpen) // Check if the token number is RoundBracketOpen
        {
            if (expr_()) // Call Expression_ function
            {
                Tokn = gettToken(); // Get the next token

                if (Tokn.TokenNumber == RoundBracketClose) // Check if the token number is RoundBracketClose
                {
                    Tokn = gettToken(); // Get the next token

                    if (Tokn.TokenNumber == LCB) // Check if the token number is LCB
                    {

                        if (statement_list()) // Call statement_list function
                        {
                            Tokn = gettToken(); // Get the next token

                            if (Tokn.TokenNumber == RCB) // Check if the token number is RCB
                            {
                                return true; // Return true if the WHILE statement is valid
                            }
                        }
                    }
                }
            }
        }
    }
    return false; // Return false if any condition fails
}

bool Expression_()
{
    do
    {
        if (!Term_()) // Check if Term_ returns false
            return false;     // Return false if Term_ is not valid

        Tokn = gettToken(); // Get the next token

    } while (Tokn.TokenNumber == PLUS || Tokn.TokenNumber == MINUS); // Continue the loop if the token number is PLUS or MINUS

    unGetTOKEN(); // Put back the last token to the token stream

    return true; // Return true if the loop completes, indicating a valid expression
}

bool Term_()
{
    do
    {
        if (!Factor_()) // Check if Factor_ returns false
            return false;       // Return false if Factor_ is not valid

        Tokn = gettToken(); // Get the next token

    } while (Tokn.TokenNumber == MULTI || Tokn.TokenNumber == DIV || Tokn.TokenNumber == MODULUS); // Continue the loop if the token number is MULTI, DIV, or MODULUS

    unGetTOKEN(); // Put back the last token to the token stream

    return true; // Return true if the loop completes, indicating a valid term
}

bool Factor_()
{
    Tokn = gettToken(); // Get the next token

    if (Tokn.TokenNumber == ID) // Check if the token number is ID
        return true;                        // Return true if it is an identifier

    else if (Tokn.TokenNumber == NUM) // Check if the token number is NUM
        return true;                              // Return true if it is a number

    else if (Tokn.TokenNumber == RoundBracketOpen) // Check if the token number is RoundBracketOpen
    {
        if (Expression_()) // Call Expression_ function
        {
            Tokn = gettToken(); // Get the next token

            if (Tokn.TokenNumber == RoundBracketClose) // Check if the token number is RoundBracketClose
                return true;                                       // Return true if the expression inside the parentheses is valid

            else
                unGetTOKEN(); // Put back the token to the token stream if the closing bracket is missing
        }
        else
            unGetTOKEN(); // Put back the token to the token stream if the expression inside the parentheses is not valid
    }

    unGetTOKEN(); // Put back the token to the token stream if none of the above conditions are met

    return true; // Return true in all cases (except when an error occurs), indicating a valid factor
}

bool expr_()
{
    if (ORexp_()) // Check if ORexp_ returns true
    {
        Tokn = gettToken(); // Get the next token

        if (Tokn.TokenNumber == GREATER || Tokn.TokenNumber == LESS ||
            Tokn.TokenNumber == GREATEREQ || Tokn.TokenNumber == LESSEQ ||
            Tokn.TokenNumber == EQEQ || Tokn.TokenNumber == NOTEQUAL)
        {
            if (ORexp_()) // Check if ORexp_ returns true
                return true;      // Return true if both ORexp_ calls are successful
            else
                return false; // Return false if the second ORexp_ call fails
        }

        unGetTOKEN(); // Put back the token to the token stream

        return true; // Return true if the first condition is met
    }

    return false; // Return false if ORexp_ is not valid
}

bool ORexp_()
{
    do
    {
        if (!ANDexp_()) // Check if ANDexp_ returns false
            return false;       // Return false if ANDexp_ is not valid

        Tokn = gettToken(); // Get the next token

    } while (Tokn.TokenNumber == OR); // Continue the loop if the token number is OR

    unGetTOKEN(); // Put back the last token to the token stream

    return true; // Return true if the loop completes, indicating a valid logical OR expression
}

bool ANDexp_()
{
    do
    {
        if (!EQexp_()) // Check if EQexp_ returns false
            return false;      // Return false if EQexp_ is not valid

        Tokn = gettToken(); // Get the next token

    } while (Tokn.TokenNumber == AND); // Continue the loop if the token number is AND

    unGetTOKEN(); // Put back the last token to the token stream

    return true; // Return true if the loop completes, indicating a valid logical AND expression
}

bool EQexp_()
{
    do
    {
        if (!CMPexp_()) // Check if CMPexp_ returns false
            return false;       // Return false if CMPexp_ is not valid

        Tokn = gettToken(); // Get the next token

    } while (Tokn.TokenNumber == EQEQ || Tokn.TokenNumber == NOTEQUAL); // Continue the loop if the token number is EQEQ or NOTEQUAL

    unGetTOKEN(); // Put back the last token to the token stream

    return true; // Return true if the loop completes, indicating a valid equality expression
}

bool CMPexp_()
{
    do
    {
        if (!ShiftExp_()) // Check if ShiftExp_ returns false
            return false;         // Return false if ShiftExp_ is not valid

        Tokn = gettToken(); // Get the next token

    } while (Tokn.TokenNumber == LESS || Tokn.TokenNumber == LESSEQ ||
             Tokn.TokenNumber == GREATER || Tokn.TokenNumber == GREATEREQ); // Continue the loop if the token number is one of the comparison operators

    unGetTOKEN(); // Put back the last token to the token stream

    return true; // Return true if the loop completes, indicating a valid comparison expression
}

bool ShiftExp_()
{
    do
    {
        if (!Expression_()) // Check if Expression_ returns false
            return false;           // Return false if Expression_ is not valid

        Tokn = gettToken(); // Get the next token

    } while (Tokn.TokenNumber == RIGHTSHIFT || Tokn.TokenNumber == LEFTSHIFT); // Continue the loop if the token number is RIGHTSHIFT or LEFTSHIFT

    unGetTOKEN(); // Put back the last token to the token stream

    return true; // Return true if the loop completes, indicating a valid shift expression
}

void displayTokens()
{
    // ...

    // Open the file for writing
    ofstream outFile("TokenGen.txt", ios::app);

    // Check if the file was opened successfully
    if (!outFile.is_open())
    {
        cout << "Failed to open TokenGen.txt" << endl;
        return;
    }

    // Write the tokens to the file
    outFile << "<" << Tokn.TokenType << ", " << Tokn.TokenNumber << "> ";

    // ...

    // Close the file
    outFile.close();
}

bool Program()
{
    MyFile.open("Expression.txt"); // Open the file "Expression.txt"

    if (MyFile.is_open())
    {
        bool hasBegin = false;
        bool hasEnd = false;

        Tokn = gettToken(); // Get the next token

        if (Tokn.TokenNumber == BEGIN) // Check if the token number is BEGIN
        {
            hasBegin = true;

            if (statement_list()) // Call statement_list function
            {
                Tokn = gettToken(); // Get the next token

                if (Tokn.TokenNumber == END) // Check if the token number is END
                {
                    hasEnd = true;
                }
            }
            else
            {
                return false; // Return false if BEGIN is present but END is not present
            }
        }
        else if (Tokn.TokenNumber == END) // Check if the token number is END without BEGIN
        {
            return false;
        }

        // Return false if 'BEGIN' is not present but 'END' is present
        if (!hasBegin && hasEnd)
        {
            return false;
        }
        outFile.close();
        // Return true if both BEGIN and END are present, or if both are not present
        return (hasBegin && hasEnd) || (!hasBegin && !hasEnd);
    }
    else
    {
        cout << "File not Found\n"; // Print "File not Found" if the file cannot be opened
    }
}

//// -- Driver Program
//[STAThreadAttribute]
// int main() {
//
//    Application::SetCompatibleTextRenderingDefault(false);
//    Application::EnableVisualStyles();
//    SignInForm::MyForm form;
//    Application::Run(% form);
//    return 0; // Add a return statement to indicate successful execution
//
//}