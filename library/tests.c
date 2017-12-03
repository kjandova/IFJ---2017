#include "tests.h"


void tests_run(char * path) {
    scanner_tests(path);
}

void scanner_tests(char * path) {

    string _path = strChars(path);
    string test  = strChars("/Scanner/Tokens_Test_0.txt");
    string file;

    strInit(&file);

    strConat(&file, &_path, &test);

    Dump("%s", file.str);

    scanner_debug(file.str);
}
