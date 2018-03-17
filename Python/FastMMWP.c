#include <FastMMWP.h>

// to make the parameters copy free, we encode the transposition and conjucation caracter.                          
static char flags[3]="ntc";
static int timing=1;

#define TEXECUTE(X) \
  { if (timing) {START_CLOCK;}                  \
    X;                                          \
    if (timing) {END_CLOCK;}                    \
    }


#include "FastMMWRcode.h"

#include "FastMMWPHeader.h" 


/*
  static PyObject *d_wmp(PyObject *self, PyObject *args);
  static void d_wmaddp(PyObject *self, PyObject *args);
  
  static PyMethodDef FMMWPMethods[] = {
  {"d_wmp", d_wmp, METH_VARARGS,"Winograd"},
  {"d_wmaddp", d_wmaddp, METH_VARARGS,"Winograd MADD"},
  {NULL, NULL,0,NULL}     // Sentinel - marks the end of this structure 
};
*/

/* ==== Initialize the C_test functions ====================== */
// Module name must be _C_arraytest in compile and linked 
void initFastMMWP(void)  {
  (void) Py_InitModule("FastMMWP", FMMWPMethods);
  import_array();  // Must be present for NumPy.  Called first after above line.
}


int  not_floatmatrix(PyArrayObject *mat)  {
  if (mat->descr->type_num != NPY_FLOAT || mat->nd != 2)  {
    PyErr_SetString(PyExc_ValueError,
		    "In not_floatmatrix: array must be of type Float and 2 dimensional (n x m).");
    return 1;  }
  return 0;
}
int  not_doublematrix(PyArrayObject *mat)  {
  if (mat->descr->type_num != NPY_DOUBLE || mat->nd != 2)  {
    PyErr_SetString(PyExc_ValueError,
		    "In not_doublematrix: array must be of type Double and 2 dimensional (n x m).");
    return 1;  }
  return 0;
}
int  not_floatcomplexmatrix(PyArrayObject *mat)  {
  if (mat->descr->type_num != NPY_CFLOAT || mat->nd != 2)  {
    PyErr_SetString(PyExc_ValueError,
		    "In not_floatcomplexmatrix: array must be of type Float Complex and 2 dimensional (n x m).");
    return 1;  }
  return 0;
}
int  not_doublecomplexmatrix(PyArrayObject *mat)  {
  if (mat->descr->type_num != NPY_CDOUBLE || mat->nd != 2)  {
    PyErr_SetString(PyExc_ValueError,
		    "In not_doublecomplexmatrix: array must be of type Double Complex and 2 dimensional (n x m).");
    return 1;  }
  return 0;
}




/* ==== matrix multiply  =========================
    Returns a NEW  NumPy vector array
    interface:  d_wmp(a, b)
                a is NumPy vector, b is Python vector (double)
                returns a NumPy vector                                        
static PyObject *d_wmp(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int i,j,an,am,bn,bm,cn,cm,dims[2];
  int k=0;
  double cf=1.0;

  /* Parse tuples separately since args will differ between C fcns 
  if (!PyArg_ParseTuple(args, "O!O!", 
			&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'double' type and a vector
     Not needed if python wrapper function checks before call to this routine 
  if (not_doublematrix(a) || not_doublematrix(b)) return NULL;
    
  /* Get the dimension of the input 
  

  cn=a->dimensions[0];
  cm=b->dimensions[1];
  dims[0] = cn;
  dims[1] = cm;

  an = a->dimensions[0];
  am = a->dimensions[1];

  bn = b->dimensions[0];
  bm = b->dimensions[1];
  


  /* Make a new double vector of same dimension 
  c=(PyArrayObject *) PyArray_FromDims(2,dims,NPY_DOUBLE);
  
  if (not_doublematrix(c)) return NULL;

  d_wmB(&cf, &k, &cm, &cn,&cm, &cn, (double *)c->data,
	&cf, &k, &am, &an,&am, &an, (double *)a->data,
	&cf, &k, &bm, &bn,&bm, &bn, (double *)b->data);

  return PyArray_Return(c);
}

/* ==== matrix multiply  =========================
    Returns a NumPy vector array
    interface:  d_wmp(c,a,b)
                vec1 is NumPy vector, vec2 is Python vector (double)
                returns a NumPy vector                                        
static void d_wmaddp(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int i,j,an,am,bn,bm,cn,cm,dims[2];
  int k=0;
  double cf=1.0;

  /* Parse tuples separately since args will differ between C fcns 
  if (!PyArg_ParseTuple(args, "O!O!O!", 
			&PyArray_Type, &c,&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'double' type and a vector
     Not needed if python wrapper function checks before call to this routine 
  if (not_doublematrix(c) || not_doublematrix(a) || not_doublematrix(b)) return NULL;
    
  /* Get the dimension of the input 
  

  cn=a->dimensions[0]; 
  if (cn>c->dimensions[0]) {     
    PyErr_SetString(PyExc_ValueError,
		    "cn>c->dimensions[0].");
    return NULL; }
  cm=b->dimensions[1]; 
  if (cm>c->dimensions[1]) {     
    PyErr_SetString(PyExc_ValueError,
		    "cm>c->dimensions[1].");
    return NULL; }

  an = a->dimensions[0];
  am = a->dimensions[1];

  bn = b->dimensions[0];
  bm = b->dimensions[1];
  


  d_wmaddB(&cf, &k, &cm, &cn,&cm, &cn, (double *)c->data,
	   &cf, &k, &am, &an,&am, &an, (double *)a->data,
	   &cf, &k, &bm, &bn,&bm, &bn, (double *)b->data);


}
  */


#include "FastMMWPCode.h"
