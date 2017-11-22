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
//	@File				tokens.c
//	@Description
//
///////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////
//
//  PARSER
//


enum ParserStats {
    PARSER_START,
    PARSER_DECLARE_FUNCTION,
    PARSER_DECLARE_VARIABLE
};

/*
*   @function      parserInit
*   @param         char * fileNameSource
*   @param         string       name
*   @description
*/
parserInit(char * fileNameSource) {
    Token       tok;
    Token       tokID;
    TFunctions  fceTable;

    scanner_init(fileNamePath);

    functionsInit(&fceTable);

    int stateMain   = PARSER_START,
        stateReturn = PARSER_START;

    while(1) {
        switch(stateMain) {

            ////////////////////////////////////
            //
            case PARSER_START: {
                tok = scanner_next_token();
                switch(tok.flag) {
                    case TOKEN_DECLARE:
                        state = PARSER_DECLARE_FUNCTION;
                    break;
                }
            } break;

            ///////////////////////////////////////////////////////////////////////
            // Declare Function ID (ID As DT[, ID As DT] ..) As DT
            //
            case PARSER_DECLARE_FUNCTION: {

                // Declare >Function<
                tok = scanner_next_token();
                if (tok.flag != TOKEN_FUNCTION) {
                    ErrorException(ERROR_SYNTAX, "ERROR_SYNTAX :: Function is miss");
                }

                // Declare Function >ID<
                tok = scanner_next_token();
                if (tok.flag != TOKEN_ID) {
                    ErrorException(ERROR_SYNTAX, "ERROR_SYNTAX :: ID id miss");
                }

                // Create Function
                functionsAdd(&fceTable, tok.name);

                // Declare Function ID >(<
                tok = scanner_next_token();
                if (tok.flag == TOKEN_BRACKET_LEFT) {
                    // Declare Function ID (>)<

                    tok = scanner_next_token();
                }

                if (tok.flag != TOKEN_ID) {
                    ErrorException(ERROR_SYNTAX, "ERROR_SYNTAX :: ID is missing");
                }


            } break;

            ///////////////////////////////////////////////////////////////////////
            // Declare Function ID (ID As DT[, ID As DT] ..) As DT
            //
            case PARSER_DECLARE_VARIABLE: {

                LABEL_DataType:

                // >ID< As DT
                tokID = scanner_next_token();
                if (tok.flag != TOKEN_ID) {
                    ErrorException(ERROR_SYNTAX, "ERROR_SYNTAX :: ID is missing");
                }

                // ID >As< DT
                tok = scanner_next_token();
                if (tok.flag != TOKEN_AS) {
                    ErrorException(ERROR_SYNTAX, "ERROR_SYNTAX :: AS is missing");
                }

                // ID As >DT<
                tok = scanner_next_token();
                switch (tok.flag) {
                    case TOKEN_INTEGER:
                    case TOKEN_DOUBLE:
                    case TOKEN_STRING: {
                        functionAddParam(&function, );
                    } break;

                    default: {
                        ErrorException(ERROR_SYNTAX, "ERROR_SYNTAX :: Data Type is missing");
                    }
                }

                // ID As DT>[, ID As DT ..]<
                tok = scanner_next_token();

                if (tok.flag == TOKEN_COMMA) goto LABEL_DataType;
                if (stateReturn == )

            } break;

        }
    }
}

///////////////////////////////////////////////////////////////////////////////////
//
//  FUNCTIONS
//


/*
*   @function      functionsInit
*   @description
*/
void functionsInit(TFunctions *table) {
    table.count     = 0;
    table.functions = NULL;
}


/*
*   @function      functionAdd
*   @param         TFunctions * fceTable
*   @param         string       name
*   @description
*/
Function functionsAdd(TFunctions * fceTable, string name) {

    if (fceTable == NULL || !name.length) {
        ErrorException(ERROR_INTER, "Parser :: FunctionAdd");
    }

    fceTable.count++;

    Function functionsTmp = (Function*) realloc (fceTable.functions, fceTable.count * sizeof(Function));

     if (functionsTmp != NULL) {
       fceTable.functions                   = functionsTmp;
       fceTable.functions[fceTable.count-1] = functionCreate(name);

     } else {

         free (numbers);
         ErrorException(ERROR_INTER, "Parser :: FunctionAdd (re)allocating memory");
     }
}


/*
*   @function      functionCreate
*   @param         string       name
*   @description
*/
Function functionCreate(string name) {
    Function fce;
    fce.Name = name;
    return fce;
}




/*
*   @function      functionAdd
*   @param         TFunctions * fceTable
*   @param         string       name
*   @description
*/
parser_set_setting(parserSetting setting)




/*
*   @function      functionAdd
*   @param         TFunctions * fceTable
*   @param         string       name
*   @description
*/
parser_run(char * fileNameDestiny) {

}


/*
*   @function      functionAdd
*   @param         TFunctions * fceTable
*   @param         string       name
*   @description
*/
void addFunctionParam(Function * fce, string name, short int dateType) {

}


/*
*   @function      functionAdd
*   @param         TFunctions * fceTable
*   @param         string       name
*   @description
*/
void dumpFunctionParams(Function * fce) {

}

