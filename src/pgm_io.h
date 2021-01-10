#ifndef __PGM_IO_H__
#define __PGM_IO_H__

#include <iostream>
#include "matrix_image.h"
using namespace std;


void pgma_write ( const string file_out_name, const Matrix_image& matrix);


void pgma_write_data ( ofstream &file_out, const Matrix_image& matrix);


void pgma_write_header ( ofstream &file_out, const string file_out_name, const Matrix_image& matrix, const unsigned int maxg);


void pgmb_write ( const string file_out_name, const Matrix_image& matrix);


void pgmb_write_data ( ofstream &file_out, const Matrix_image& matrix);


void pgmb_write_header ( ofstream &file_out, const string file_out_name, const Matrix_image& matrix, const unsigned int maxg);

#endif