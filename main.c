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
//	@File				main.c
//	@Description
//
///////////////////////////////////////////////////////////////////////////////////


#include "./library/init.h"

char * __program_source_path = NULL;

struct globalArgs_T {
    int   help;
    char *filePathInput;
    char *filePathOutput;
    int   dumpEnable;
    char *fileDumpOutput;
} globalArgs;


 void help() {
    printf("PROJEKT IFJ 2017");
 }

void init(int argc, char ** argv) {
    int opt;
    globalArgs.dumpEnable = DEBUG_DISABLE;

    //$IFJ [-h][-f <path>][-o [<path>]][-d [<path>][-i]

    while ((opt = getopt (argc, argv, "hf:o:d::i")) != -1) {
        switch (opt) {
            case 'h': /* -h option - Help */
                help();
            break;
            case 'f': /* -f option - Input File Path  | NULL -> stdin */
                globalArgs.filePathInput   = optarg;
            break;
            case 'o': /* -o option - Output File Path | NULL -> stdout */
                globalArgs.filePathOutput  = optarg;
            break;
            case 'd': /* -d option - DUMP Output File Path  | NULL -> stdout */
                globalArgs.fileDumpOutput  = optarg;
                globalArgs.dumpEnable      = DEBUG_ENABLE;
            break;
            case 'i': /* -i option - DUMP More info */
                globalArgs.dumpEnable     |= DEBUG_LINE;
            break;
        }
    }

    ErrorInit( writeFile(globalArgs.fileDumpOutput),  writeFile(globalArgs.fileDumpOutput), globalArgs.dumpEnable );
}


int main(int argc, char ** argv) {

    init(argc, argv);

    DebugConfigure(DEBUG_ENABLE | DEBUG_LINE /* | DEBUG_TIME */ );

    globalArgs.filePathInput = "./tests/Parser/Test_02_Define_Function.bas";

    parser_init(globalArgs.filePathInput);
    parser_run();

    return 0;
}
