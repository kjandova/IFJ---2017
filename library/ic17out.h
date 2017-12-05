#ifndef IFJ_IC17OUT_H
#define IFJ_IC17OUT_H
#include "parser.h"

/**
 * \brief Writes program to file
 * \param f file to be written to
 * \param p program to be written
 */
void writeProgram(FILE *f, struct Program *p);

#endif
