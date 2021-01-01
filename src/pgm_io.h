#ifndef __PGM_IO_H__
#define __PGM_IO_H__

#include <iostream>
#include "matrix_image.h"
using namespace std;

void pgma_write ( string file_out_name, Matrix_image& matrix);
void pgma_write_data ( ofstream &file_out, Matrix_image& matrix);
void pgma_write_header ( ofstream &file_out, string file_out_name, Matrix_image& matrix, unsigned int maxg);
void pgmb_write ( string file_out_name, Matrix_image& matrix);
void pgmb_write_data ( ofstream &file_out, Matrix_image& matrix);
void pgmb_write_header ( ofstream &file_out, string file_out_name, Matrix_image& matrix, unsigned int maxg);


#endif