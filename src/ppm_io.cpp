# include <cstdlib>
# include <iostream>

using namespace std;

# include "matrix_image.h"
# include "pixel.h"
# include "ppm_io.h"

//****************************************************************************

void ppma_write ( const string output_name, const Matrix_image& matrix)

/** \n
*\****************************************************************************\n
*\ \n
*\  Purpose:\n
*\ \n
*\    PPMA_WRITE writes the header and data for an ASCII PPM file.\n
*\ \n
*\  example\n
*\ \n
*\  P3\n
*\  # Le P3 signifie que les couleurs sont en ASCII, et qu'elles sont en RGB.\n
*\  # Par 3 colonnes et 2 lignes :\n
*\  3 2\n
*\  # Ayant 255 pour valeur maximum :\n
*\  255\n
*\  255  0   0     \n
*\  0  255  0      \n 
*\  0   0  255\n
*\  255 255  0    \n
*\  255 255 255   \n   
*\  0   0   0\n
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
  ppma_write_header ( output, output_name, matrix, maxg );
//
//  Write the data.
//
  ppma_write_data ( output, matrix );
//
//  Close the file.
//
  output.close ( );

  return;
}

//****************************************************************************

void ppma_write_data ( ofstream &output, const Matrix_image& matrix)

/** \n
*\****************************************************************************\n
*\ \n
*\  Purpose:\n
*\ \n
*\    PPMA_WRITE_DATA writes the data for an ASCII PPM file.\n
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
      output << matrix.tab_pixel[j][i].p_r;
      output << " ";
      output << matrix.tab_pixel[j][i].p_g;
      output << " ";
      output << matrix.tab_pixel[j][i].p_b;
      output << " ";
      output << "\n";
    }
  }
  return;
}

//****************************************************************************

void ppma_write_header ( ofstream &output, const string output_name, const Matrix_image& matrix, const unsigned int maxg)

/** \n
*\****************************************************************************\n
*\ \n
*\  Purpose:\n
*\ \n
*\    PPMA_WRITE_HEADER writes the header of an ASCII PPM file.\n
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
  output << "P3\n";
  output << "# " << output_name << " created by PPMA_IO::PPMA_WRITE.\n";
  output << matrix.xsize << "  " << matrix.ysize << "\n";
  output << maxg << "\n";

  return;
}

//****************************************************************************

void ppmb_write ( string output_name, const Matrix_image& matrix)

/** \n
*\**************************************************************************** \n
*\ \n
*\  Purpose: \n
*\ \n
*\    PPMB_WRITE writes the header and data for a binary PPM file. \n
*\ \n
*\  example \n
*\ \n
*\  P3 \n
*\  # Le P3 signifie que les couleurs sont en ASCII, et qu'elles sont en RGB. \n
*\  # Par 3 colonnes et 2 lignes : \n
*\  3 2 \n
*\  # Ayant 255 pour valeur maximum : \n
*\  data ... \n
*\ \n
*\  Author:\n
*\ \n
*\    Stephane NGNEPIEPAYE WEMBE \n
*\ \n
*\  Parameters: \n
*\ \n
*\    Input, string OUTPUT_NAME, the name of the file. \n
*\ \n 
*\    Input, Matrix_image& matrix matrix of pixel. \n
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
  ppmb_write_header ( output, output_name, matrix, maxg );
//
//  Write the data.
//
  ppmb_write_data ( output, matrix );
//
//  Close the file.
//
  output.close ( );

  return;
}


void ppmb_write_data ( ofstream &output, const Matrix_image& matrix)

/** \n
*\**************************************************************************** \n
*\ \n
*\  Purpose: \n
*\ \n
*\    PPMB_WRITE_DATA writes the data for a binary PPM file. \n
*\ \n
*\  Author: \n
*\ \n
*\    Stephane NGNEPIEPAYE WEMBE \n
*\ \n
*\  Parameters: \n
*\ \n
*\    Input, ofstream &OUTPUT, a pointer to the file.\n
*\ \n
*\    Input, Matrix_image& matrix matrix of pixel. \n 
*\ \n 
*/
{
  int i;
  int j;

  for ( j = matrix.ysize-1; j >=0; j-- )
  {
    for ( i = 0; i < matrix.xsize; i++ )
    {

      output << (char) (matrix.tab_pixel[j][i].p_r);
      output << (char) (matrix.tab_pixel[j][i].p_g);
      output << (char) (matrix.tab_pixel[j][i].p_b);
    }
  }
  return;
}

void ppmb_write_header ( ofstream &output, const string output_name, const Matrix_image& matrix, const unsigned int maxg)

/** \n
*\**************************************************************************** \n
*\ \n
*\  Purpose: \n
*\ \n
*\    PPMB_WRITE_HEADER writes the header of a binary PPM file. \n
*\ \n
*\  Author: \n
*\ \n
*\    Stephane NGNEPIEPAYE WEMBE \n
*\ \n
*\  Parameters:\n
*\ \n
*\    Input, ofstream &OUTPUT, a pointer to the file. \n
*\ \n
*\    Input, string OUTPUT_NAME, the name of the file.\n
*\ \n
*\    Input, Matrix_image& matrix matrix of pixel. \n
*\ \n
*\    Input, unsigned int MAXG, the maximum gray value. \n
*\ \n
*/
{
  output << "P6\n";
  output << "# " << output_name << " created by PPMB_IO::PPMB_WRITE.\n";
  output << matrix.xsize << "  " << matrix.ysize << "\n";
  output << maxg << "\n";

  return;
}