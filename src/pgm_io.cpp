# include <cstdlib>
# include <iostream>

using namespace std;

# include "matrix_image.h"
# include "pixel.h"
# include "pgm_io.h"

//****************************************************************************

void pgma_write ( string output_name, Matrix_image& matrix)

//****************************************************************************
//
//  Purpose:
//
//    PGMA_WRITE writes the header and data for an ASCII PGM file.
// 
//  Example:
//
//    P2
//    # feep.pgm
//    24 7
//    15
//    0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
//    0  3  3  3  3  0  0  7  7  7  7  0  0 11 11 11 11  0  0 15 15 15 15  0
//    0  3  0  0  0  0  0  7  0  0  0  0  0 11  0  0  0  0  0 15  0  0 15  0
//    0  3  3  3  0  0  0  7  7  7  0  0  0 11 11 11  0  0  0 15 15 15 15  0
//    0  3  0  0  0  0  0  7  0  0  0  0  0 11  0  0  0  0  0 15  0  0  0  0
//    0  3  0  0  0  0  0  7  7  7  7  0  0 11 11 11 11  0  0 15  0  0  0  0
//    0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
//
//  Author:
// 
//    stephane NGNEPIEPAYE WEMBE
//
//  Parameters:
//
//    Input, string OUTPUT_NAME, the name of the file.
//
//    Input, Matrix_image& matrix matrix of pixel.
//
{
  ofstream output;
  int i;
  int j;
  unsigned int maxg;
//
//  Open the output file.
//
  output.open ( output_name.c_str ( ) );

  if ( !output )
  {
    cerr << "\n";
    cerr << "PGMA_WRITE - Fatal error!\n";
    cerr << "  Cannot open the output file \"" << output_name << "\".\n";
    exit ( 1 );
  }
//
//  Compute the maximum.
//
  maxg = 0;

  for ( j = 0; j < matrix.ysize; j++ )
  {
    for ( i = 0; i < matrix.xsize; i++ )
    {
      if ( maxg < matrix.tab_pixel[j][i].p_val )
      {
        maxg = matrix.tab_pixel[j][i].p_val;
      }

    }
  }
//
//  Write the header.
//
  pgma_write_header ( output, output_name, matrix, maxg );
//
//  Write the data.
//
  pgma_write_data ( output, matrix );
//
//  Close the file.
//
  output.close ( );

  return;
}


void pgma_write_data ( ofstream &output, Matrix_image& matrix)

//****************************************************************************80
//
//  Purpose:
//
//    PGMA_WRITE_DATA writes the data for an ASCII PGM file.
//
//  Author:
//
//    Stephane NGNEPIEPAYE WEMBE
//
//  Parameters:
//
//    Input, ofstream &OUTPUT, a pointer to the file.
//
//    Input, Matrix_image& matrix matrix of pixel.
//
{
  int i;
  int j;
  int numval;

  numval = 0;

  for ( j = matrix.ysize-1; j >=0; j-- )
  {
    for ( i = 0; i < matrix.xsize; i++ )
    {
      output << matrix.tab_pixel[j][i].p_val;
      numval = numval + 1;

      if ( numval % 12 == 0 || i == matrix.xsize - 1 || numval == matrix.xsize * matrix.ysize )
      {
        output << "\n";
      }
      else
      {
        output << " ";
      }

    }
  }
  return;
}

void pgma_write_header ( ofstream &output, string output_name, Matrix_image& matrix, unsigned int maxg)

//****************************************************************************80
//
//  Purpose:
//
//    PGMA_WRITE_HEADER writes the header of an ASCII PGM file.
//
//  Author:
//
//    Steĥane NGNEPIEPAYE WEMBE
//
//  Parameters:
//
//    Input, ofstream &OUTPUT, a pointer to the file.
//
//    Input, string OUTPUT_NAME, the name of the file.
//
//    Input, Matrix_image& matrix matrix of pixel.
//
//    Input, unsigned int MAXG, the maximum gray value.
//
{
  output << "P2\n";
  output << "# " << output_name << " created by PGMA_IO::PGMA_WRITE.\n";
  output << matrix.xsize << "  " << matrix.ysize << "\n";
  output << maxg << "\n";

  return;
}

//****************************************************************************

void pgmb_write ( string output_name, Matrix_image& matrix)

//****************************************************************************
//
//  Purpose:
//
//    PGMB_WRITE writes the header and data for a binary PGM file.
//
//  example
//
//  P3
//  # Le P3 signifie que les couleurs sont en ASCII, et qu'elles sont en RGB.
//  # Par 3 colonnes et 2 lignes :
//  3 2
//  # Ayant 255 pour valeur maximum :
//  data ...
//
//  Author:
// 
//    Stephane NGNEPIEPAYE WEMBE
//
//  Parameters:
//
//    Input, string OUTPUT_NAME, the name of the file.
//
//    Input, Matrix_image& matrix matrix of pixel.
//
{
  ofstream output;
  int i;
  int j;
  unsigned int maxg;
//
//  Open the output file.
//
  output.open ( output_name.c_str ( ) );

  if ( !output )
  {
    cerr << "\n";
    cerr << "PGMB_WRITE - Fatal error!\n";
    cerr << "  Cannot open the output file \"" << output_name << "\".\n";
    exit ( 1 );
  }
//
//  Compute the maximum.
//
  maxg = 0;

  for ( j = 0; j < matrix.ysize; j++ )
  {
    for ( i = 0; i < matrix.xsize; i++ )
    {
      if ( maxg < matrix.tab_pixel[j][i].p_val )
      {
        maxg = matrix.tab_pixel[j][i].p_val;
      }

    }
  }
//
//  Write the header.
//
  pgmb_write_header ( output, output_name, matrix, maxg );
//
//  Write the data.
//
  pgmb_write_data ( output, matrix );
//
//  Close the file.
//
  output.close ( );

  return;
}


void pgmb_write_data ( ofstream &output, Matrix_image& matrix)

//****************************************************************************80
//
//  Purpose:
//
//    PGMB_WRITE_DATA writes the data for a binary PGM file.
//
//  Author:
//
//    Stephane NGNEPIEPAYE WEMBE
//
//  Parameters:
//
//    Input, ofstream &OUTPUT, a pointer to the file.
//
//    Input, Matrix_image& matrix matrix of pixel.
//
{
  int i;
  int j;

  for ( j = matrix.ysize-1; j >=0; j-- )
  {
    for ( i = 0; i < matrix.xsize; i++ )
    {

      output << (char)matrix.tab_pixel[j][i].p_val;
    }
  }
  return;
}

void pgmb_write_header ( ofstream &output, string output_name, Matrix_image& matrix, unsigned int maxg)

//****************************************************************************80
//
//  Purpose:
//
//    PGMB_WRITE_HEADER writes the header of a binary PGM file.
//
//  Author:
//
//    Stephane NGNEPIEPAYE WEMBE
//
//  Parameters:
//
//    Input, ofstream &OUTPUT, a pointer to the file.
//
//    Input, string OUTPUT_NAME, the name of the file.
//
//    Input, Matrix_image& matrix matrix of pixel.
//
//    Input, unsigned int MAXG, the maximum gray value.
//
{
  output << "P5\n";
  output << "# " << output_name << " created by PGMB_IO::PGMB_WRITE.\n";
  output << matrix.xsize << "  " << matrix.ysize << "\n";
  output << maxg << "\n";

  return;
}