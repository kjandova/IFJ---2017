///////////////////////////////////////////////////////////////////////////////////
//
//	@Project 			IFJ 2017
//
//  @Authors
//  Kristýna Jandová  	xjando04
//  Vilém Faigel		xfaige00
//  Nikola Timková		xtimko01
//	Bc. Václav Doležal	xdolez76
//
//	@File				parser.h
//	@Description
//
///////////////////////////////////////////////////////////////////////////////////


// Vytvoreni promenne
struct DIM {
    string            name;          // ID
    short int         dataType;      // DT
    string            valueString;   // String
    int               valueInteger;  // Integer
    double            valueDouble;   // Double
};


// Prikaz
struct Command        TWCode;        // Three Way Code (instruction.h)

// Telo funkce
struct Function {
    string            name;          // ID
    short int         priority;      // Priorite
    struct tree *     parameters;
    struct tree *     variables;
    struct tree *     commands;
    DIM               _return;
};

struct Program {
    struct Function   scope;
    struct tree *     functions;
    struct tree *     globalVariables;
};
