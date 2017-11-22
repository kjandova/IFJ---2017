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
    string Name;
    string value_string;
    int    value_int;
    double value_double;
};

struct TVariable DIM;

// Parametry
struct TParameters {

};

// Prikaz
struct Comand {
    short int instruction
functionCreate
};

struct TCommands {

};

// Founkce
struct TFunctions {

} TFunctions;

// Telo funkce
typedef struct Function {
    string       Name;
    short int    priority;
    TParameters  parameters;
    TVariables   variables;
    TCommands    commands;
    DIM          _return;
};

typedef struct TFunctions {
    int        count;
    Function * functions;
}
