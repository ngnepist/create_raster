# include <cstdlib>
# include <iostream>

using namespace std;

# include "matrix_image.h"
# include "pixel.h"
# include "pgm_io.h"

//****************************************************************************

void pgma_write ( const string output_name, const Matrix_image& matrix)

/** \n
*\****************************************************************************\n
*\ \n
*\  Purpose:\n
*\ \n
*\    PGMA_WRITE writes the header and data for an ASCII PGM file.\n
*\ \n
*\  Example:\n
*\ \n
*\    P2\n
*\    # feep.pgm\n
*\    24 7\n
*\    15\n
*\    0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0\n
*\    0  3  3  3  3  0  0  7  7  7  7  0  0 11 11 11 11  0  0 15 15 15 15  0\n
*\    0  3  0  0  0  0  0  7  0  0  0  0  0 11  0  0  0  0  0 15  0  0 15  0\n
*\    0  3  3  3  0  0  0  7  7  7  0  0  0 11 11 11  0  0  0 15 15 15 15  0\n
*\    0  3  0  0  0  0  0  7  0  0  0  0  0 11  0  0  0  0  0 15  0  0  0  0\n
*\    0  3  0  0  0  0  0  7  7  7  7  0  0 11 11 11 11  0  0 15  0  0  0  0\n
*\    0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0\n
*\ \n
*\  Author:\n
*\ \n
*\    stephane NGNEPIEPAYE WEMBE\n
*\ \n
*\  Parameters:\n
*\ \n
*\    Input, string OUTPUT_NAME, the name of the file.\n
*\ \n
*\    Input, Matrix_image& matrix matrix of pixel.\n
*\ \n
*/
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

//****************************************************************************

void pgma_write_data ( ofstream &output, const Matrix_image& matrix)

/** \n
*\****************************************************************************\n
*\ \n
*\  Purpose:\n
*\ \n
*\    PGMA_WRITE_DATA writes the data for an ASCII PGM file.\n
*\ \n
*\  Author:\n
*\ \n
*\    Stephane NGNEPIEPAYE WEMBE\n
*\ \n
*\  Parameters:\n
*\ \n
*\    Input, ofstream &OUTPUT, a pointer to the file.\n
*\ \n
*\    Input, Matrix_image& matrix matrix of pixel.\n
*\ \n
*/
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

//****************************************************************************

void pgma_write_header ( ofstream &output, const string output_name, const Matrix_image& matrix, const unsigned int maxg)

/** \n
*\****************************************************************************\n
*\ \n
*\  Purpose:\n
*\ \n
*\    PGMA_WRITE_HEADER writes the header of an ASCII PGM file.\n
*\ \n
*\  Author:\n
*\ \n
*\    Steĥane NGNEPIEPAYE WEMBE\n
*\ \n
*\  Parameters:\n
*\ \n
*\    Input, ofstream &OUTPUT, a pointer to the file.\n
*\ \n
*\    Input, string OUTPUT_NAME, the name of the file.\n
*\ \n
*\    Input, Matrix_image& matrix matrix of pixel.\n
*\ \n
*\    Input, unsigned int MAXG, the maximum gray value.\n
*\ \n
*/
{
  output << "P2\n";
  output << "# " << output_name << " created by PGMA_IO::PGMA_WRITE.\n";
  output << matrix.xsize << "  " << matrix.ysize << "\n";
  output << maxg << "\n";

  return;
}

//****************************************************************************

void pgmb_write ( const string output_name, const Matrix_image& matrix)

/** \n
*\****************************************************************************\n
*\ \n
*\  Purpose:\n
*\ \n
*\    PGMB_WRITE writes the header and data for a binary PGM file.\n
*\ \n
*\  example\n
*\ \n
*\  P3\n
*\  # Le P3 signifie que les couleurs sont en ASCII, et qu'elles sont en RGB.\n
*\  # Par 3 colonnes et 2 lignes :\n
*\  3 2\n
*\  # Ayant 255 pour valeur maximum :\n
*\  data ...\n
*\ \n
*\  Author:\n
*\ \n
*\    Stephane NGNEPIEPAYE WEMBE\n
*\ \n
*\  Parameters:\n
*\ \n
*\    Input, string OUTPUT_NAME, the name of the file.\n
*\ \n
*\    Input, Matrix_image& matrix matrix of pixel.\n
*\ \n
*/
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

//****************************************************************************

void pgmb_write_data ( ofstream &output, const Matrix_image& matrix)

/** \n
*\****************************************************************************\n
*\ \n
*\  Purpose:\n
*\ \n
*\    PGMB_WRITE_DATA writes the data for a binary PGM file.\n
*\ \n
*\  Author:\n
*\ \n
*\    Stephane NGNEPIEPAYE WEMBE\n
*\ \n
*\  Parameters:\n
*\ \n
*\    Input, ofstream &OUTPUT, a pointer to the file.\n
*\ \n
*\    Input, Matrix_image& matrix matrix of pixel.\n
*\ \n
*/
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

//****************************************************************************

void pgmb_write_header ( ofstream &output, const string output_name, const Matrix_image& matrix, const unsigned int maxg)

/** \n
*\****************************************************************************80\n
*\ \n
*\  Purpose:\n
*\ \n
*\    PGMB_WRITE_HEADER writes the header of a binary PGM file.\n
*\ \n
*\  Author:\n
*\ \n
*\    Stephane NGNEPIEPAYE WEMBE\n
*\ \n
*\  Parameters:\n
*\ \n
*\    Input, ofstream &OUTPUT, a pointer to the file.\n
*\ \n
*\    Input, string OUTPUT_NAME, the name of the file.\n
*\ \n
*\    Input, Matrix_image& matrix matrix of pixel.\n
*\ \n
*\    Input, unsigned int MAXG, the maximum gray value.\n
*\ \n
*/
{
  output << "P5\n";
  output << "# " << output_name << " created by PGMB_IO::PGMB_WRITE.\n";
  output << matrix.xsize << "  " << matrix.ysize << "\n";
  output << maxg << "\n";

  return;
}