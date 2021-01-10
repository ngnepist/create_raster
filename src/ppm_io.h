#ifndef __PPM_IO_H__
#define __PPM_IO_H__

#include <iostream>
#include "matrix_image.h"

using namespace std;


void ppma_write ( const string file_out_name, const Matrix_image& matrix);


void ppma_write_data ( ofstream &file_out, const Matrix_image& matrix);


void ppma_write_header ( ofstream &file_out, const string file_out_name, const Matrix_image& matrix, const unsigned int maxg);


void ppmb_write ( const string file_out_name, const Matrix_image& matrix);


void ppmb_write_data ( ofstream &file_out, const Matrix_image& matrix);


void ppmb_write_header ( ofstream &file_out, const string file_out_name, const Matrix_image& matrix, const unsigned int maxg);

#endif