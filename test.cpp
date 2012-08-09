#include <mex.h>
#include <algorithm>

using namespace std;

/* this does absolutely nothing interesting. just takes in an image and copies it to an output buffer. */
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
  if (nrhs != 1)
  {
    printf("Takes 1 argument (%d arguments supplied).\n", nrhs);
    return;
  }

  if (!mxIsUint8(prhs[0]))
  {
    printf("Input must be of type uint8\n");
    return;
  }

  const mwSize *dims = mxGetDimensions(prhs[0]);
  const int w = dims[0];
  const int h = dims[1];
  const int n = w*h;

  /* input data pointer */
  unsigned char *input = (unsigned char*)mxGetData(prhs[0]);

  /* output pointer */
  unsigned char *output;

  /* allocate the output images */
  plhs[0] = mxCreateNumericArray(3, dims, mxUINT8_CLASS, mxREAL);

  /* get pointers to the output image memory */
  output = (unsigned char*)mxGetData(plhs[0]);

  // allocate storage for this thing
  unsigned char* buffer = (unsigned char*)malloc(3*n*sizeof(unsigned char));

  int x, y, d;
  for (d = 0; d < 3; d++)
  {
    for (x = 0; x < w; x++)
    {
      for (y = 0; y < h; y++)
      {
        int input_offset = y + x*h + d*n;
        int output_offset = y*w + x + d*n;
        buffer[output_offset] = input[input_offset];
      }
    }
  }

  for (d = 0; d < 3; d++)
  {
    for (x = 0; x < w; x++)
    {
      for (y = 0; y < h; y++)
      {
        int input_offset = y + x*h + d*n;
        int output_offset = y*w + x + d*n;
        output[input_offset] = buffer[output_offset];
      }
    }
  }

  free(buffer);
}
