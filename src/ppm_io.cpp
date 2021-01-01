# include <cstdlib>
# include <iostream>

using namespace std;

# include "matrix_image.h"
# include "pixel.h"
# include "ppm_io.h"

//****************************************************************************

void ppma_write ( string output_name, Matrix_image& matrix)

//****************************************************************************
//
//  Purpose:
//
//    PPMA_WRITE writes the header and data for an ASCII PPM file.
//
//  example
//
//  P3
//  # Le P3 signifie que les couleurs sont en ASCII, et qu'elles sont en RGB.
//  # Par 3 colonnes et 2 lignes :
//  3 2
//  # Ayant 255 pour valeur maximum :
//  255
//  255  0   0     
//  0  255  0       
//  0   0  255
//  255 255  0    
//  255 255 255      
//  0   0   0
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

void ppma_write_data ( ofstream &output, Matrix_image& matrix)

//****************************************************************************
//
//  Purpose:
//
//    PPMA_WRITE_DATA writes the data for an ASCII PPM file.
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

void ppma_write_header ( ofstream &output, string output_name, Matrix_image& matrix, unsigned int maxg)

//****************************************************************************
//
//  Purpose:
//
//    PPMA_WRITE_HEADER writes the header of an ASCII PPM file.
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
  output << "P3\n";
  output << "# " << output_name << " created by PPMA_IO::PPMA_WRITE.\n";
  output << matrix.xsize << "  " << matrix.ysize << "\n";
  output << maxg << "\n";

  return;
}

//****************************************************************************

void ppmb_write ( string output_name, Matrix_image& matrix)

//****************************************************************************
//
//  Purpose:
//
//    PPMB_WRITE writes the header and data for a binary PPM file.
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


void ppmb_write_data ( ofstream &output, Matrix_image& matrix)

//****************************************************************************80
//
//  Purpose:
//
//    PPMB_WRITE_DATA writes the data for a binary PPM file.
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

      output << (char) (matrix.tab_pixel[j][i].p_r);
      output << (char) (matrix.tab_pixel[j][i].p_g);
      output << (char) (matrix.tab_pixel[j][i].p_b);
    }
  }
  return;
}

void ppmb_write_header ( ofstream &output, string output_name, Matrix_image& matrix, unsigned int maxg)

//****************************************************************************80
//
//  Purpose:
//
//    PPMB_WRITE_HEADER writes the header of a binary PPM file.
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
  output << "P6\n";
  output << "# " << output_name << " created by PPMB_IO::PPMB_WRITE.\n";
  output << matrix.xsize << "  " << matrix.ysize << "\n";
  output << maxg << "\n";

  return;
}

