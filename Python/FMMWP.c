#include <FMMWP.h>
/ to make the parameters copy free, we encode the transposition and conjucation caracter.                                                                                                                                                    
   static char flags[3]="ntc";
static int timing=1;

#define TEXECUTE(X) \
  { if (timing) {START_CLOCK;}                  \
    X;                                          \
    if (timing) {END_CLOCK;}                    \
    }


#include "FastMMWRcode.h"



static PyMethodDef FMMWPMethods[] = {
  {"wmp", d_wmp, METH_VARARGS},
  {NULL, NULL}     /* Sentinel - marks the end of this structure */
};

/* ==== Initialize the C_test functions ====================== */
// Module name must be _C_arraytest in compile and linked 
void init_C_arraytest()  {
  (void) Py_InitModule("FMMWP", FMMWPMethods);
  import_array();  // Must be present for NumPy.  Called first after above line.
}


/* ==== Square vector components & multiply by a float =========================
    Returns a NEW  NumPy vector array
    interface:  wmp(vec1, vec2)
                vec1 is NumPy vector, vec2 is Python vector (double)
                returns a NumPy vector                                        */
static PyObject *d_wmp(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int i,j,an,am,bn,bm,cn,cm;
  int k=0;
  double cf=1.0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!", 
			&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'double' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_doublevector(a) || not_doublevector(b)) return NULL;
    
  /* Get the dimension of the input */
  

  cn=a->dimensions[0];
  cm=b->dimensions[1];
    
  /* Make a new double vector of same dimension */
  c=(PyArrayObject *) PyArray_FromDims(1,cn*cm,NPY_DOUBLE);
        
  d_wmB(&cf, &k, &cm, &cn,&cm, &cn, (double) c->array,
	&cf, &k, a->dimensions+1, a->dimensions+0,a->dimensions+1, a->dimensions+0, (double) a->array,
	&cf, &k, b->dimensions+1, b->dimensions+0,b->dimensions+1, b->dimensions+0, (double) b->array);

  return PyArray_Return(vecout);
}
