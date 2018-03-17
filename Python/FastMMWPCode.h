

/* ==== matrix multiply  =========================
    Returns a NEW  NumPy vector array
    interface:  s_dcmulP(a,b)
                a is NumPy vector, b is Python vector (float)
                returns a NumPy vector                                        */

static PyObject* s_dcmulP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm,dims[2];
  int k=0;
  float cf=1.0;
  int T=0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!", 
			&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'float' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_floatmatrix(a) || not_floatmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

  cn=a->dimensions[0];
  cm=b->dimensions[1];
  dims[0] = cn;
  dims[1] = cm;

  an = a->dimensions[0];
  am = a->dimensions[1];

  bn = b->dimensions[0];
  bm = b->dimensions[1];
  


  /* Make a new float vector of same dimension */
  c=(PyArrayObject *) PyArray_FromDims(2,dims,NPY_FLOAT);
  
  if (not_floatmatrix(c)) return NULL;

  s_dcmulB(&cf, &k, &cm, &cn,&cm, &cn, (float *)c->data,
	&cf, &k, &am, &an,&am, &an, (float *)a->data,
	&cf, &k, &bm, &bn,&bm, &bn, (float *)b->data);

  return PyArray_Return(c);
}



/* ==== matrix multiply  =========================
    Returns a NEW  NumPy vector array
    interface:  s_mulP(a,b)
                a is NumPy vector, b is Python vector (float)
                returns a NumPy vector                                        */

static PyObject* s_mulP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm,dims[2];
  int k=0;
  float cf=1.0;
  int T=0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!", 
			&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'float' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_floatmatrix(a) || not_floatmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

  cn=a->dimensions[0];
  cm=b->dimensions[1];
  dims[0] = cn;
  dims[1] = cm;

  an = a->dimensions[0];
  am = a->dimensions[1];

  bn = b->dimensions[0];
  bm = b->dimensions[1];
  


  /* Make a new float vector of same dimension */
  c=(PyArrayObject *) PyArray_FromDims(2,dims,NPY_FLOAT);
  
  if (not_floatmatrix(c)) return NULL;

  s_mulB(&cf, &k, &cm, &cn,&cm, &cn, (float *)c->data,
	&cf, &k, &am, &an,&am, &an, (float *)a->data,
	&cf, &k, &bm, &bn,&bm, &bn, (float *)b->data);

  return PyArray_Return(c);
}



/* ==== matrix multiply  =========================
    Returns a NEW  NumPy vector array
    interface:  s_mulptP(a,b)
                a is NumPy vector, b is Python vector (float)
                returns a NumPy vector                                        */

static PyObject* s_mulptP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm,dims[2];
  int k=0;
  float cf=1.0;
  int T=0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!", 
			&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'float' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_floatmatrix(a) || not_floatmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

  cn=a->dimensions[0];
  cm=b->dimensions[1];
  dims[0] = cn;
  dims[1] = cm;

  an = a->dimensions[0];
  am = a->dimensions[1];

  bn = b->dimensions[0];
  bm = b->dimensions[1];
  


  /* Make a new float vector of same dimension */
  c=(PyArrayObject *) PyArray_FromDims(2,dims,NPY_FLOAT);
  
  if (not_floatmatrix(c)) return NULL;

  s_mulptB(&cf, &k, &cm, &cn,&cm, &cn, (float *)c->data,
	&cf, &k, &am, &an,&am, &an, (float *)a->data,
	&cf, &k, &bm, &bn,&bm, &bn, (float *)b->data);

  return PyArray_Return(c);
}



/* ==== matrix multiply  =========================
    Returns a NumPy vector array
    interface:  s_maddP(c,a,b)
                c,a,b are NumPy Python vector (float)
                returns a NumPy vector                                        */
static PyObject* s_maddP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm;
  int k=0;
  int T=0;

  float cf=1.0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!O!", 
			&PyArray_Type, &c,&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'float' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_floatmatrix(c) || not_floatmatrix(a) || not_floatmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

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
  


  s_maddB(&cf, &k, &cm, &cn,&cm, &cn, (float *)c->data,
	   &cf, &k, &am, &an,&am, &an, (float *)a->data,
	   &cf, &k, &bm, &bn,&bm, &bn, (float *)b->data);

  return PyArray_Return(c);
}


/* ==== matrix multiply  =========================
    Returns a NumPy vector array
    interface:  s_saddmulP(c,a,b)
                c,a,b are NumPy Python vector (float)
                returns a NumPy vector                                        */
static PyObject* s_saddmulP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm;
  int k=0;
  int T=0;

  float cf=1.0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!O!", 
			&PyArray_Type, &c,&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'float' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_floatmatrix(c) || not_floatmatrix(a) || not_floatmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

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
  


  s_saddmulB(&cf, &k, &cm, &cn,&cm, &cn, (float *)c->data,
	   &cf, &k, &am, &an,&am, &an, (float *)a->data,
	   &cf, &k, &bm, &bn,&bm, &bn, (float *)b->data);

  return PyArray_Return(c);
}


/* ==== matrix multiply  =========================
    Returns a NEW  NumPy vector array
    interface:  s_smulP(a,b)
                a is NumPy vector, b is Python vector (float)
                returns a NumPy vector                                        */

static PyObject* s_smulP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm,dims[2];
  int k=0;
  float cf=1.0;
  int T=0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!", 
			&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'float' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_floatmatrix(a) || not_floatmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

  cn=a->dimensions[0];
  cm=b->dimensions[1];
  dims[0] = cn;
  dims[1] = cm;

  an = a->dimensions[0];
  am = a->dimensions[1];

  bn = b->dimensions[0];
  bm = b->dimensions[1];
  


  /* Make a new float vector of same dimension */
  c=(PyArrayObject *) PyArray_FromDims(2,dims,NPY_FLOAT);
  
  if (not_floatmatrix(c)) return NULL;

  s_smulB(&cf, &k, &cm, &cn,&cm, &cn, (float *)c->data,
	&cf, &k, &am, &an,&am, &an, (float *)a->data,
	&cf, &k, &bm, &bn,&bm, &bn, (float *)b->data);

  return PyArray_Return(c);
}



/* ==== matrix multiply  =========================
    Returns a NumPy vector array
    interface:  s_saddmulRP(c,a,b)
                c,a,b are NumPy Python vector (float)
                returns a NumPy vector                                        */
static PyObject* s_saddmulRP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm;
  int k=0;
  int T=0;

  float cf=1.0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!O!", 
			&PyArray_Type, &c,&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'float' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_floatmatrix(c) || not_floatmatrix(a) || not_floatmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

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
  


  s_saddmulRB(&cf, &k, &cm, &cn,&cm, &cn, (float *)c->data,
	   &cf, &k, &am, &an,&am, &an, (float *)a->data,
	   &cf, &k, &bm, &bn,&bm, &bn, (float *)b->data);

  return PyArray_Return(c);
}


/* ==== matrix multiply  =========================
    Returns a NEW  NumPy vector array
    interface:  s_smulRP(a,b)
                a is NumPy vector, b is Python vector (float)
                returns a NumPy vector                                        */

static PyObject* s_smulRP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm,dims[2];
  int k=0;
  float cf=1.0;
  int T=0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!", 
			&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'float' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_floatmatrix(a) || not_floatmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

  cn=a->dimensions[0];
  cm=b->dimensions[1];
  dims[0] = cn;
  dims[1] = cm;

  an = a->dimensions[0];
  am = a->dimensions[1];

  bn = b->dimensions[0];
  bm = b->dimensions[1];
  


  /* Make a new float vector of same dimension */
  c=(PyArrayObject *) PyArray_FromDims(2,dims,NPY_FLOAT);
  
  if (not_floatmatrix(c)) return NULL;

  s_smulRB(&cf, &k, &cm, &cn,&cm, &cn, (float *)c->data,
	&cf, &k, &am, &an,&am, &an, (float *)a->data,
	&cf, &k, &bm, &bn,&bm, &bn, (float *)b->data);

  return PyArray_Return(c);
}



/* ==== matrix multiply  =========================
    Returns a NEW  NumPy vector array
    interface:  s_wmulP(a,b)
                a is NumPy vector, b is Python vector (float)
                returns a NumPy vector                                        */

static PyObject* s_wmulP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm,dims[2];
  int k=0;
  float cf=1.0;
  int T=0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!", 
			&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'float' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_floatmatrix(a) || not_floatmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

  cn=a->dimensions[0];
  cm=b->dimensions[1];
  dims[0] = cn;
  dims[1] = cm;

  an = a->dimensions[0];
  am = a->dimensions[1];

  bn = b->dimensions[0];
  bm = b->dimensions[1];
  


  /* Make a new float vector of same dimension */
  c=(PyArrayObject *) PyArray_FromDims(2,dims,NPY_FLOAT);
  
  if (not_floatmatrix(c)) return NULL;

  s_wmulB(&cf, &k, &cm, &cn,&cm, &cn, (float *)c->data,
	&cf, &k, &am, &an,&am, &an, (float *)a->data,
	&cf, &k, &bm, &bn,&bm, &bn, (float *)b->data);

  return PyArray_Return(c);
}



/* ==== matrix multiply  =========================
    Returns a NumPy vector array
    interface:  s_waddmulP(c,a,b)
                c,a,b are NumPy Python vector (float)
                returns a NumPy vector                                        */
static PyObject* s_waddmulP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm;
  int k=0;
  int T=0;

  float cf=1.0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!O!", 
			&PyArray_Type, &c,&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'float' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_floatmatrix(c) || not_floatmatrix(a) || not_floatmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

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
  


  s_waddmulB(&cf, &k, &cm, &cn,&cm, &cn, (float *)c->data,
	   &cf, &k, &am, &an,&am, &an, (float *)a->data,
	   &cf, &k, &bm, &bn,&bm, &bn, (float *)b->data);

  return PyArray_Return(c);
}


/* ==== matrix multiply  =========================
    Returns a NEW  NumPy vector array
    interface:  s_wmP(a,b)
                a is NumPy vector, b is Python vector (float)
                returns a NumPy vector                                        */

static PyObject* s_wmP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm,dims[2];
  int k=0;
  float cf=1.0;
  int T=0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!", 
			&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'float' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_floatmatrix(a) || not_floatmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

  cn=a->dimensions[0];
  cm=b->dimensions[1];
  dims[0] = cn;
  dims[1] = cm;

  an = a->dimensions[0];
  am = a->dimensions[1];

  bn = b->dimensions[0];
  bm = b->dimensions[1];
  


  /* Make a new float vector of same dimension */
  c=(PyArrayObject *) PyArray_FromDims(2,dims,NPY_FLOAT);
  
  if (not_floatmatrix(c)) return NULL;

  s_wmB(&cf, &k, &cm, &cn,&cm, &cn, (float *)c->data,
	&cf, &k, &am, &an,&am, &an, (float *)a->data,
	&cf, &k, &bm, &bn,&bm, &bn, (float *)b->data);

  return PyArray_Return(c);
}



/* ==== matrix multiply  =========================
    Returns a NumPy vector array
    interface:  s_wmaddP(c,a,b)
                c,a,b are NumPy Python vector (float)
                returns a NumPy vector                                        */
static PyObject* s_wmaddP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm;
  int k=0;
  int T=0;

  float cf=1.0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!O!", 
			&PyArray_Type, &c,&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'float' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_floatmatrix(c) || not_floatmatrix(a) || not_floatmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

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
  


  s_wmaddB(&cf, &k, &cm, &cn,&cm, &cn, (float *)c->data,
	   &cf, &k, &am, &an,&am, &an, (float *)a->data,
	   &cf, &k, &bm, &bn,&bm, &bn, (float *)b->data);

  return PyArray_Return(c);
}


/* ==== matrix multiply  =========================
    Returns a NEW  NumPy vector array
    interface:  s_wmRP(a,b)
                a is NumPy vector, b is Python vector (float)
                returns a NumPy vector                                        */

static PyObject* s_wmRP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm,dims[2];
  int k=0;
  float cf=1.0;
  int T=0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!", 
			&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'float' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_floatmatrix(a) || not_floatmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

  cn=a->dimensions[0];
  cm=b->dimensions[1];
  dims[0] = cn;
  dims[1] = cm;

  an = a->dimensions[0];
  am = a->dimensions[1];

  bn = b->dimensions[0];
  bm = b->dimensions[1];
  


  /* Make a new float vector of same dimension */
  c=(PyArrayObject *) PyArray_FromDims(2,dims,NPY_FLOAT);
  
  if (not_floatmatrix(c)) return NULL;

  s_wmRB(&cf, &k, &cm, &cn,&cm, &cn, (float *)c->data,
	&cf, &k, &am, &an,&am, &an, (float *)a->data,
	&cf, &k, &bm, &bn,&bm, &bn, (float *)b->data);

  return PyArray_Return(c);
}



/* ==== matrix multiply  =========================
    Returns a NumPy vector array
    interface:  s_wmaddRP(c,a,b)
                c,a,b are NumPy Python vector (float)
                returns a NumPy vector                                        */
static PyObject* s_wmaddRP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm;
  int k=0;
  int T=0;

  float cf=1.0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!O!", 
			&PyArray_Type, &c,&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'float' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_floatmatrix(c) || not_floatmatrix(a) || not_floatmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

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
  


  s_wmaddRB(&cf, &k, &cm, &cn,&cm, &cn, (float *)c->data,
	   &cf, &k, &am, &an,&am, &an, (float *)a->data,
	   &cf, &k, &bm, &bn,&bm, &bn, (float *)b->data);

  return PyArray_Return(c);
}


/* ==== matrix multiply  =========================
    Returns a NEW  NumPy vector array
    interface:  s_wmTRP(a,b)
                a is NumPy vector, b is Python vector (float)
                returns a NumPy vector                                        */

static PyObject* s_wmTRP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm,dims[2];
  int k=0;
  float cf=1.0;
  int T=0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!", 
			&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'float' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_floatmatrix(a) || not_floatmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

  cn=a->dimensions[0];
  cm=b->dimensions[1];
  dims[0] = cn;
  dims[1] = cm;

  an = a->dimensions[0];
  am = a->dimensions[1];

  bn = b->dimensions[0];
  bm = b->dimensions[1];
  


  /* Make a new float vector of same dimension */
  c=(PyArrayObject *) PyArray_FromDims(2,dims,NPY_FLOAT);
  
  if (not_floatmatrix(c)) return NULL;

  s_wmTRB(&cf, &k, &cm, &cn,&cm, &cn, (float *)c->data,
	&cf, &k, &am, &an,&am, &an, (float *)a->data,
	&cf, &k, &bm, &bn,&bm, &bn, (float *)b->data);

  return PyArray_Return(c);
}



/* ==== matrix multiply  =========================
    Returns a NumPy vector array
    interface:  s_wmaddTRP(c,a,b)
                c,a,b are NumPy Python vector (float)
                returns a NumPy vector                                        */
static PyObject* s_wmaddTRP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm;
  int k=0;
  int T=0;

  float cf=1.0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!O!", 
			&PyArray_Type, &c,&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'float' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_floatmatrix(c) || not_floatmatrix(a) || not_floatmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

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
  


  s_wmaddTRB(&cf, &k, &cm, &cn,&cm, &cn, (float *)c->data,
	   &cf, &k, &am, &an,&am, &an, (float *)a->data,
	   &cf, &k, &bm, &bn,&bm, &bn, (float *)b->data);

  return PyArray_Return(c);
}


/* ==== matrix multiply  =========================
    Returns a NEW  NumPy vector array
    interface:  s_adaptive_smulP(a,b)
                a is NumPy vector, b is Python vector (float)
                returns a NumPy vector                                        */

static PyObject* s_adaptive_smulP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm,dims[2];
  int k=0;
  float cf=1.0;
  int T=0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!d", 
			&PyArray_Type, &a,&PyArray_Type, &b,&T))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'float' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_floatmatrix(a) || not_floatmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

  cn=a->dimensions[0];
  cm=b->dimensions[1];
  dims[0] = cn;
  dims[1] = cm;

  an = a->dimensions[0];
  am = a->dimensions[1];

  bn = b->dimensions[0];
  bm = b->dimensions[1];
  


  /* Make a new float vector of same dimension */
  c=(PyArrayObject *) PyArray_FromDims(2,dims,NPY_FLOAT);
  
  if (not_floatmatrix(c)) return NULL;

  s_adaptive_smulB(&cf, &k, &cm, &cn,&cm, &cn, (float *)c->data,
	&cf, &k, &am, &an,&am, &an, (float *)a->data,
	&cf, &k, &bm, &bn,&bm, &bn, (float *)b->data,&T);

  return PyArray_Return(c);
}



/* ==== matrix multiply  =========================
    Returns a NEW  NumPy vector array
    interface:  s_omulP(a,b)
                a is NumPy vector, b is Python vector (float)
                returns a NumPy vector                                        */

static PyObject* s_omulP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm,dims[2];
  int k=0;
  float cf=1.0;
  int T=0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!", 
			&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'float' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_floatmatrix(a) || not_floatmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

  cn=a->dimensions[0];
  cm=b->dimensions[1];
  dims[0] = cn;
  dims[1] = cm;

  an = a->dimensions[0];
  am = a->dimensions[1];

  bn = b->dimensions[0];
  bm = b->dimensions[1];
  


  /* Make a new float vector of same dimension */
  c=(PyArrayObject *) PyArray_FromDims(2,dims,NPY_FLOAT);
  
  if (not_floatmatrix(c)) return NULL;

  s_omulB(&cf, &k, &cm, &cn,&cm, &cn, (float *)c->data,
	&cf, &k, &am, &an,&am, &an, (float *)a->data,
	&cf, &k, &bm, &bn,&bm, &bn, (float *)b->data);

  return PyArray_Return(c);
}



/* ==== matrix multiply  =========================
    Returns a NumPy vector array
    interface:  s_oaddmulP(c,a,b)
                c,a,b are NumPy Python vector (float)
                returns a NumPy vector                                        */
static PyObject* s_oaddmulP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm;
  int k=0;
  int T=0;

  float cf=1.0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!O!", 
			&PyArray_Type, &c,&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'float' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_floatmatrix(c) || not_floatmatrix(a) || not_floatmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

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
  


  s_oaddmulB(&cf, &k, &cm, &cn,&cm, &cn, (float *)c->data,
	   &cf, &k, &am, &an,&am, &an, (float *)a->data,
	   &cf, &k, &bm, &bn,&bm, &bn, (float *)b->data);

  return PyArray_Return(c);
}


/* ==== matrix multiply  =========================
    Returns a NEW  NumPy vector array
    interface:  s_owmulP(a,b)
                a is NumPy vector, b is Python vector (float)
                returns a NumPy vector                                        */

static PyObject* s_owmulP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm,dims[2];
  int k=0;
  float cf=1.0;
  int T=0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!", 
			&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'float' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_floatmatrix(a) || not_floatmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

  cn=a->dimensions[0];
  cm=b->dimensions[1];
  dims[0] = cn;
  dims[1] = cm;

  an = a->dimensions[0];
  am = a->dimensions[1];

  bn = b->dimensions[0];
  bm = b->dimensions[1];
  


  /* Make a new float vector of same dimension */
  c=(PyArrayObject *) PyArray_FromDims(2,dims,NPY_FLOAT);
  
  if (not_floatmatrix(c)) return NULL;

  s_owmulB(&cf, &k, &cm, &cn,&cm, &cn, (float *)c->data,
	&cf, &k, &am, &an,&am, &an, (float *)a->data,
	&cf, &k, &bm, &bn,&bm, &bn, (float *)b->data);

  return PyArray_Return(c);
}



/* ==== matrix multiply  =========================
    Returns a NumPy vector array
    interface:  s_owaddmulP(c,a,b)
                c,a,b are NumPy Python vector (float)
                returns a NumPy vector                                        */
static PyObject* s_owaddmulP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm;
  int k=0;
  int T=0;

  float cf=1.0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!O!", 
			&PyArray_Type, &c,&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'float' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_floatmatrix(c) || not_floatmatrix(a) || not_floatmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

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
  


  s_owaddmulB(&cf, &k, &cm, &cn,&cm, &cn, (float *)c->data,
	   &cf, &k, &am, &an,&am, &an, (float *)a->data,
	   &cf, &k, &bm, &bn,&bm, &bn, (float *)b->data);

  return PyArray_Return(c);
}


/* ==== matrix multiply  =========================
    Returns a NEW  NumPy vector array
    interface:  s_bmP(a,b)
                a is NumPy vector, b is Python vector (float)
                returns a NumPy vector                                        */

static PyObject* s_bmP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm,dims[2];
  int k=0;
  float cf=1.0;
  int T=0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!", 
			&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'float' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_floatmatrix(a) || not_floatmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

  cn=a->dimensions[0];
  cm=b->dimensions[1];
  dims[0] = cn;
  dims[1] = cm;

  an = a->dimensions[0];
  am = a->dimensions[1];

  bn = b->dimensions[0];
  bm = b->dimensions[1];
  


  /* Make a new float vector of same dimension */
  c=(PyArrayObject *) PyArray_FromDims(2,dims,NPY_FLOAT);
  
  if (not_floatmatrix(c)) return NULL;

  s_bmB(&cf, &k, &cm, &cn,&cm, &cn, (float *)c->data,
	&cf, &k, &am, &an,&am, &an, (float *)a->data,
	&cf, &k, &bm, &bn,&bm, &bn, (float *)b->data);

  return PyArray_Return(c);
}



/* ==== matrix multiply  =========================
    Returns a NumPy vector array
    interface:  s_bmaddP(c,a,b)
                c,a,b are NumPy Python vector (float)
                returns a NumPy vector                                        */
static PyObject* s_bmaddP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm;
  int k=0;
  int T=0;

  float cf=1.0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!O!", 
			&PyArray_Type, &c,&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'float' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_floatmatrix(c) || not_floatmatrix(a) || not_floatmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

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
  


  s_bmaddB(&cf, &k, &cm, &cn,&cm, &cn, (float *)c->data,
	   &cf, &k, &am, &an,&am, &an, (float *)a->data,
	   &cf, &k, &bm, &bn,&bm, &bn, (float *)b->data);

  return PyArray_Return(c);
}


/* ==== matrix multiply  =========================
    Returns a NumPy vector array
    interface:  s_ptaddmulP(c,a,b)
                c,a,b are NumPy Python vector (float)
                returns a NumPy vector                                        */
static PyObject* s_ptaddmulP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm;
  int k=0;
  int T=0;

  float cf=1.0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!O!", 
			&PyArray_Type, &c,&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'float' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_floatmatrix(c) || not_floatmatrix(a) || not_floatmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

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
  


  s_ptaddmulB(&cf, &k, &cm, &cn,&cm, &cn, (float *)c->data,
	   &cf, &k, &am, &an,&am, &an, (float *)a->data,
	   &cf, &k, &bm, &bn,&bm, &bn, (float *)b->data);

  return PyArray_Return(c);
}


/* ==== matrix multiply  =========================
    Returns a NEW  NumPy vector array
    interface:  s_wmpipeP(a,b)
                a is NumPy vector, b is Python vector (float)
                returns a NumPy vector                                        */

static PyObject* s_wmpipeP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm,dims[2];
  int k=0;
  float cf=1.0;
  int T=0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!", 
			&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'float' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_floatmatrix(a) || not_floatmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

  cn=a->dimensions[0];
  cm=b->dimensions[1];
  dims[0] = cn;
  dims[1] = cm;

  an = a->dimensions[0];
  am = a->dimensions[1];

  bn = b->dimensions[0];
  bm = b->dimensions[1];
  


  /* Make a new float vector of same dimension */
  c=(PyArrayObject *) PyArray_FromDims(2,dims,NPY_FLOAT);
  
  if (not_floatmatrix(c)) return NULL;

  s_wmpipeB(&cf, &k, &cm, &cn,&cm, &cn, (float *)c->data,
	&cf, &k, &am, &an,&am, &an, (float *)a->data,
	&cf, &k, &bm, &bn,&bm, &bn, (float *)b->data);

  return PyArray_Return(c);
}



/* ==== matrix multiply  =========================
    Returns a NumPy vector array
    interface:  s_wmaddpipeP(c,a,b)
                c,a,b are NumPy Python vector (float)
                returns a NumPy vector                                        */
static PyObject* s_wmaddpipeP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm;
  int k=0;
  int T=0;

  float cf=1.0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!O!", 
			&PyArray_Type, &c,&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'float' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_floatmatrix(c) || not_floatmatrix(a) || not_floatmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

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
  


  s_wmaddpipeB(&cf, &k, &cm, &cn,&cm, &cn, (float *)c->data,
	   &cf, &k, &am, &an,&am, &an, (float *)a->data,
	   &cf, &k, &bm, &bn,&bm, &bn, (float *)b->data);

  return PyArray_Return(c);
}


/* ==== matrix multiply  =========================
    Returns a NEW  NumPy vector array
    interface:  s_bmpipeP(a,b)
                a is NumPy vector, b is Python vector (float)
                returns a NumPy vector                                        */

static PyObject* s_bmpipeP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm,dims[2];
  int k=0;
  float cf=1.0;
  int T=0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!", 
			&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'float' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_floatmatrix(a) || not_floatmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

  cn=a->dimensions[0];
  cm=b->dimensions[1];
  dims[0] = cn;
  dims[1] = cm;

  an = a->dimensions[0];
  am = a->dimensions[1];

  bn = b->dimensions[0];
  bm = b->dimensions[1];
  


  /* Make a new float vector of same dimension */
  c=(PyArrayObject *) PyArray_FromDims(2,dims,NPY_FLOAT);
  
  if (not_floatmatrix(c)) return NULL;

  s_bmpipeB(&cf, &k, &cm, &cn,&cm, &cn, (float *)c->data,
	&cf, &k, &am, &an,&am, &an, (float *)a->data,
	&cf, &k, &bm, &bn,&bm, &bn, (float *)b->data);

  return PyArray_Return(c);
}



/* ==== matrix multiply  =========================
    Returns a NumPy vector array
    interface:  s_bmaddpipeP(c,a,b)
                c,a,b are NumPy Python vector (float)
                returns a NumPy vector                                        */
static PyObject* s_bmaddpipeP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm;
  int k=0;
  int T=0;

  float cf=1.0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!O!", 
			&PyArray_Type, &c,&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'float' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_floatmatrix(c) || not_floatmatrix(a) || not_floatmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

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
  


  s_bmaddpipeB(&cf, &k, &cm, &cn,&cm, &cn, (float *)c->data,
	   &cf, &k, &am, &an,&am, &an, (float *)a->data,
	   &cf, &k, &bm, &bn,&bm, &bn, (float *)b->data);

  return PyArray_Return(c);
}


/* ==== matrix multiply  =========================
    Returns a NEW  NumPy vector array
    interface:  s_smpipeP(a,b)
                a is NumPy vector, b is Python vector (float)
                returns a NumPy vector                                        */

static PyObject* s_smpipeP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm,dims[2];
  int k=0;
  float cf=1.0;
  int T=0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!", 
			&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'float' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_floatmatrix(a) || not_floatmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

  cn=a->dimensions[0];
  cm=b->dimensions[1];
  dims[0] = cn;
  dims[1] = cm;

  an = a->dimensions[0];
  am = a->dimensions[1];

  bn = b->dimensions[0];
  bm = b->dimensions[1];
  


  /* Make a new float vector of same dimension */
  c=(PyArrayObject *) PyArray_FromDims(2,dims,NPY_FLOAT);
  
  if (not_floatmatrix(c)) return NULL;

  s_smpipeB(&cf, &k, &cm, &cn,&cm, &cn, (float *)c->data,
	&cf, &k, &am, &an,&am, &an, (float *)a->data,
	&cf, &k, &bm, &bn,&bm, &bn, (float *)b->data);

  return PyArray_Return(c);
}



/* ==== matrix multiply  =========================
    Returns a NumPy vector array
    interface:  s_smaddpipeP(c,a,b)
                c,a,b are NumPy Python vector (float)
                returns a NumPy vector                                        */
static PyObject* s_smaddpipeP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm;
  int k=0;
  int T=0;

  float cf=1.0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!O!", 
			&PyArray_Type, &c,&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'float' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_floatmatrix(c) || not_floatmatrix(a) || not_floatmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

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
  


  s_smaddpipeB(&cf, &k, &cm, &cn,&cm, &cn, (float *)c->data,
	   &cf, &k, &am, &an,&am, &an, (float *)a->data,
	   &cf, &k, &bm, &bn,&bm, &bn, (float *)b->data);

  return PyArray_Return(c);
}


/* ==== matrix multiply  =========================
    Returns a NEW  NumPy vector array
    interface:  s_RmulP(a,b)
                a is NumPy vector, b is Python vector (float)
                returns a NumPy vector                                        */

static PyObject* s_RmulP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm,dims[2];
  int k=0;
  float cf=1.0;
  int T=0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!", 
			&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'float' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_floatmatrix(a) || not_floatmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

  cn=a->dimensions[0];
  cm=b->dimensions[1];
  dims[0] = cn;
  dims[1] = cm;

  an = a->dimensions[0];
  am = a->dimensions[1];

  bn = b->dimensions[0];
  bm = b->dimensions[1];
  


  /* Make a new float vector of same dimension */
  c=(PyArrayObject *) PyArray_FromDims(2,dims,NPY_FLOAT);
  
  if (not_floatmatrix(c)) return NULL;

  s_RmulB(&cf, &k, &cm, &cn,&cm, &cn, (float *)c->data,
	&cf, &k, &am, &an,&am, &an, (float *)a->data,
	&cf, &k, &bm, &bn,&bm, &bn, (float *)b->data);

  return PyArray_Return(c);
}



/* ==== matrix multiply  =========================
    Returns a NEW  NumPy vector array
    interface:  s_adaptive_wmP(a,b)
                a is NumPy vector, b is Python vector (float)
                returns a NumPy vector                                        */

static PyObject* s_adaptive_wmP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm,dims[2];
  int k=0;
  float cf=1.0;
  int T=0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!d", 
			&PyArray_Type, &a,&PyArray_Type, &b,&T))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'float' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_floatmatrix(a) || not_floatmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

  cn=a->dimensions[0];
  cm=b->dimensions[1];
  dims[0] = cn;
  dims[1] = cm;

  an = a->dimensions[0];
  am = a->dimensions[1];

  bn = b->dimensions[0];
  bm = b->dimensions[1];
  


  /* Make a new float vector of same dimension */
  c=(PyArrayObject *) PyArray_FromDims(2,dims,NPY_FLOAT);
  
  if (not_floatmatrix(c)) return NULL;

  s_adaptive_wmB(&cf, &k, &cm, &cn,&cm, &cn, (float *)c->data,
	&cf, &k, &am, &an,&am, &an, (float *)a->data,
	&cf, &k, &bm, &bn,&bm, &bn, (float *)b->data,&T);

  return PyArray_Return(c);
}



/* ==== matrix multiply  =========================
    Returns a NumPy vector array
    interface:  s_BMADD_PIPEP(c,a,b)
                c,a,b are NumPy Python vector (float)
                returns a NumPy vector                                        */
static PyObject* s_BMADD_PIPEP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm;
  int k=0;
  int T=0;

  float cf=1.0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!O!", 
			&PyArray_Type, &c,&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'float' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_floatmatrix(c) || not_floatmatrix(a) || not_floatmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

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
  


  s_BMADD_PIPEB(&cf, &k, &cm, &cn,&cm, &cn, (float *)c->data,
	   &cf, &k, &am, &an,&am, &an, (float *)a->data,
	   &cf, &k, &bm, &bn,&bm, &bn, (float *)b->data);

  return PyArray_Return(c);
}


/* ==== matrix multiply  =========================
    Returns a NumPy vector array
    interface:  s_BMADDP(c,a,b)
                c,a,b are NumPy Python vector (float)
                returns a NumPy vector                                        */
static PyObject* s_BMADDP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm;
  int k=0;
  int T=0;

  float cf=1.0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!O!", 
			&PyArray_Type, &c,&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'float' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_floatmatrix(c) || not_floatmatrix(a) || not_floatmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

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
  


  s_BMADDB(&cf, &k, &cm, &cn,&cm, &cn, (float *)c->data,
	   &cf, &k, &am, &an,&am, &an, (float *)a->data,
	   &cf, &k, &bm, &bn,&bm, &bn, (float *)b->data);

  return PyArray_Return(c);
}


/* ==== matrix multiply  =========================
    Returns a NumPy vector array
    interface:  s_BMADDRP(c,a,b)
                c,a,b are NumPy Python vector (float)
                returns a NumPy vector                                        */
static PyObject* s_BMADDRP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm;
  int k=0;
  int T=0;

  float cf=1.0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!O!", 
			&PyArray_Type, &c,&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'float' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_floatmatrix(c) || not_floatmatrix(a) || not_floatmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

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
  


  s_BMADDRB(&cf, &k, &cm, &cn,&cm, &cn, (float *)c->data,
	   &cf, &k, &am, &an,&am, &an, (float *)a->data,
	   &cf, &k, &bm, &bn,&bm, &bn, (float *)b->data);

  return PyArray_Return(c);
}


/* ==== matrix multiply  =========================
    Returns a NEW  NumPy vector array
    interface:  s_BMOWR_PIPEP(a,b)
                a is NumPy vector, b is Python vector (float)
                returns a NumPy vector                                        */

static PyObject* s_BMOWR_PIPEP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm,dims[2];
  int k=0;
  float cf=1.0;
  int T=0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!", 
			&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'float' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_floatmatrix(a) || not_floatmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

  cn=a->dimensions[0];
  cm=b->dimensions[1];
  dims[0] = cn;
  dims[1] = cm;

  an = a->dimensions[0];
  am = a->dimensions[1];

  bn = b->dimensions[0];
  bm = b->dimensions[1];
  


  /* Make a new float vector of same dimension */
  c=(PyArrayObject *) PyArray_FromDims(2,dims,NPY_FLOAT);
  
  if (not_floatmatrix(c)) return NULL;

  s_BMOWR_PIPEB(&cf, &k, &cm, &cn,&cm, &cn, (float *)c->data,
	&cf, &k, &am, &an,&am, &an, (float *)a->data,
	&cf, &k, &bm, &bn,&bm, &bn, (float *)b->data);

  return PyArray_Return(c);
}



/* ==== matrix multiply  =========================
    Returns a NEW  NumPy vector array
    interface:  s_BMOWRP(a,b)
                a is NumPy vector, b is Python vector (float)
                returns a NumPy vector                                        */

static PyObject* s_BMOWRP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm,dims[2];
  int k=0;
  float cf=1.0;
  int T=0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!", 
			&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'float' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_floatmatrix(a) || not_floatmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

  cn=a->dimensions[0];
  cm=b->dimensions[1];
  dims[0] = cn;
  dims[1] = cm;

  an = a->dimensions[0];
  am = a->dimensions[1];

  bn = b->dimensions[0];
  bm = b->dimensions[1];
  


  /* Make a new float vector of same dimension */
  c=(PyArrayObject *) PyArray_FromDims(2,dims,NPY_FLOAT);
  
  if (not_floatmatrix(c)) return NULL;

  s_BMOWRB(&cf, &k, &cm, &cn,&cm, &cn, (float *)c->data,
	&cf, &k, &am, &an,&am, &an, (float *)a->data,
	&cf, &k, &bm, &bn,&bm, &bn, (float *)b->data);

  return PyArray_Return(c);
}



/* ==== matrix multiply  =========================
    Returns a NEW  NumPy vector array
    interface:  s_BMOWRRP(a,b)
                a is NumPy vector, b is Python vector (float)
                returns a NumPy vector                                        */

static PyObject* s_BMOWRRP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm,dims[2];
  int k=0;
  float cf=1.0;
  int T=0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!", 
			&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'float' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_floatmatrix(a) || not_floatmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

  cn=a->dimensions[0];
  cm=b->dimensions[1];
  dims[0] = cn;
  dims[1] = cm;

  an = a->dimensions[0];
  am = a->dimensions[1];

  bn = b->dimensions[0];
  bm = b->dimensions[1];
  


  /* Make a new float vector of same dimension */
  c=(PyArrayObject *) PyArray_FromDims(2,dims,NPY_FLOAT);
  
  if (not_floatmatrix(c)) return NULL;

  s_BMOWRRB(&cf, &k, &cm, &cn,&cm, &cn, (float *)c->data,
	&cf, &k, &am, &an,&am, &an, (float *)a->data,
	&cf, &k, &bm, &bn,&bm, &bn, (float *)b->data);

  return PyArray_Return(c);
}



/* ==== matrix multiply  =========================
    Returns a NEW  NumPy vector array
    interface:  d_dcmulP(a,b)
                a is NumPy vector, b is Python vector (double)
                returns a NumPy vector                                        */

static PyObject* d_dcmulP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm,dims[2];
  int k=0;
  double cf=1.0;
  int T=0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!", 
			&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'double' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_doublematrix(a) || not_doublematrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

  cn=a->dimensions[0];
  cm=b->dimensions[1];
  dims[0] = cn;
  dims[1] = cm;

  an = a->dimensions[0];
  am = a->dimensions[1];

  bn = b->dimensions[0];
  bm = b->dimensions[1];
  


  /* Make a new double vector of same dimension */
  c=(PyArrayObject *) PyArray_FromDims(2,dims,NPY_DOUBLE);
  
  if (not_doublematrix(c)) return NULL;

  d_dcmulB(&cf, &k, &cm, &cn,&cm, &cn, (double *)c->data,
	&cf, &k, &am, &an,&am, &an, (double *)a->data,
	&cf, &k, &bm, &bn,&bm, &bn, (double *)b->data);

  return PyArray_Return(c);
}



/* ==== matrix multiply  =========================
    Returns a NEW  NumPy vector array
    interface:  d_mulP(a,b)
                a is NumPy vector, b is Python vector (double)
                returns a NumPy vector                                        */

static PyObject* d_mulP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm,dims[2];
  int k=0;
  double cf=1.0;
  int T=0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!", 
			&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'double' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_doublematrix(a) || not_doublematrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

  cn=a->dimensions[0];
  cm=b->dimensions[1];
  dims[0] = cn;
  dims[1] = cm;

  an = a->dimensions[0];
  am = a->dimensions[1];

  bn = b->dimensions[0];
  bm = b->dimensions[1];
  


  /* Make a new double vector of same dimension */
  c=(PyArrayObject *) PyArray_FromDims(2,dims,NPY_DOUBLE);
  
  if (not_doublematrix(c)) return NULL;

  d_mulB(&cf, &k, &cm, &cn,&cm, &cn, (double *)c->data,
	&cf, &k, &am, &an,&am, &an, (double *)a->data,
	&cf, &k, &bm, &bn,&bm, &bn, (double *)b->data);

  return PyArray_Return(c);
}



/* ==== matrix multiply  =========================
    Returns a NEW  NumPy vector array
    interface:  d_mulptP(a,b)
                a is NumPy vector, b is Python vector (double)
                returns a NumPy vector                                        */

static PyObject* d_mulptP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm,dims[2];
  int k=0;
  double cf=1.0;
  int T=0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!", 
			&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'double' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_doublematrix(a) || not_doublematrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

  cn=a->dimensions[0];
  cm=b->dimensions[1];
  dims[0] = cn;
  dims[1] = cm;

  an = a->dimensions[0];
  am = a->dimensions[1];

  bn = b->dimensions[0];
  bm = b->dimensions[1];
  


  /* Make a new double vector of same dimension */
  c=(PyArrayObject *) PyArray_FromDims(2,dims,NPY_DOUBLE);
  
  if (not_doublematrix(c)) return NULL;

  d_mulptB(&cf, &k, &cm, &cn,&cm, &cn, (double *)c->data,
	&cf, &k, &am, &an,&am, &an, (double *)a->data,
	&cf, &k, &bm, &bn,&bm, &bn, (double *)b->data);

  return PyArray_Return(c);
}



/* ==== matrix multiply  =========================
    Returns a NumPy vector array
    interface:  d_maddP(c,a,b)
                c,a,b are NumPy Python vector (double)
                returns a NumPy vector                                        */
static PyObject* d_maddP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm;
  int k=0;
  int T=0;

  double cf=1.0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!O!", 
			&PyArray_Type, &c,&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'double' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_doublematrix(c) || not_doublematrix(a) || not_doublematrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

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
  


  d_maddB(&cf, &k, &cm, &cn,&cm, &cn, (double *)c->data,
	   &cf, &k, &am, &an,&am, &an, (double *)a->data,
	   &cf, &k, &bm, &bn,&bm, &bn, (double *)b->data);

  return PyArray_Return(c);
}


/* ==== matrix multiply  =========================
    Returns a NumPy vector array
    interface:  d_saddmulP(c,a,b)
                c,a,b are NumPy Python vector (double)
                returns a NumPy vector                                        */
static PyObject* d_saddmulP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm;
  int k=0;
  int T=0;

  double cf=1.0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!O!", 
			&PyArray_Type, &c,&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'double' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_doublematrix(c) || not_doublematrix(a) || not_doublematrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

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
  


  d_saddmulB(&cf, &k, &cm, &cn,&cm, &cn, (double *)c->data,
	   &cf, &k, &am, &an,&am, &an, (double *)a->data,
	   &cf, &k, &bm, &bn,&bm, &bn, (double *)b->data);

  return PyArray_Return(c);
}


/* ==== matrix multiply  =========================
    Returns a NEW  NumPy vector array
    interface:  d_smulP(a,b)
                a is NumPy vector, b is Python vector (double)
                returns a NumPy vector                                        */

static PyObject* d_smulP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm,dims[2];
  int k=0;
  double cf=1.0;
  int T=0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!", 
			&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'double' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_doublematrix(a) || not_doublematrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

  cn=a->dimensions[0];
  cm=b->dimensions[1];
  dims[0] = cn;
  dims[1] = cm;

  an = a->dimensions[0];
  am = a->dimensions[1];

  bn = b->dimensions[0];
  bm = b->dimensions[1];
  


  /* Make a new double vector of same dimension */
  c=(PyArrayObject *) PyArray_FromDims(2,dims,NPY_DOUBLE);
  
  if (not_doublematrix(c)) return NULL;

  d_smulB(&cf, &k, &cm, &cn,&cm, &cn, (double *)c->data,
	&cf, &k, &am, &an,&am, &an, (double *)a->data,
	&cf, &k, &bm, &bn,&bm, &bn, (double *)b->data);

  return PyArray_Return(c);
}



/* ==== matrix multiply  =========================
    Returns a NumPy vector array
    interface:  d_saddmulRP(c,a,b)
                c,a,b are NumPy Python vector (double)
                returns a NumPy vector                                        */
static PyObject* d_saddmulRP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm;
  int k=0;
  int T=0;

  double cf=1.0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!O!", 
			&PyArray_Type, &c,&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'double' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_doublematrix(c) || not_doublematrix(a) || not_doublematrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

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
  


  d_saddmulRB(&cf, &k, &cm, &cn,&cm, &cn, (double *)c->data,
	   &cf, &k, &am, &an,&am, &an, (double *)a->data,
	   &cf, &k, &bm, &bn,&bm, &bn, (double *)b->data);

  return PyArray_Return(c);
}


/* ==== matrix multiply  =========================
    Returns a NEW  NumPy vector array
    interface:  d_smulRP(a,b)
                a is NumPy vector, b is Python vector (double)
                returns a NumPy vector                                        */

static PyObject* d_smulRP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm,dims[2];
  int k=0;
  double cf=1.0;
  int T=0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!", 
			&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'double' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_doublematrix(a) || not_doublematrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

  cn=a->dimensions[0];
  cm=b->dimensions[1];
  dims[0] = cn;
  dims[1] = cm;

  an = a->dimensions[0];
  am = a->dimensions[1];

  bn = b->dimensions[0];
  bm = b->dimensions[1];
  


  /* Make a new double vector of same dimension */
  c=(PyArrayObject *) PyArray_FromDims(2,dims,NPY_DOUBLE);
  
  if (not_doublematrix(c)) return NULL;

  d_smulRB(&cf, &k, &cm, &cn,&cm, &cn, (double *)c->data,
	&cf, &k, &am, &an,&am, &an, (double *)a->data,
	&cf, &k, &bm, &bn,&bm, &bn, (double *)b->data);

  return PyArray_Return(c);
}



/* ==== matrix multiply  =========================
    Returns a NEW  NumPy vector array
    interface:  d_wmulP(a,b)
                a is NumPy vector, b is Python vector (double)
                returns a NumPy vector                                        */

static PyObject* d_wmulP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm,dims[2];
  int k=0;
  double cf=1.0;
  int T=0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!", 
			&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'double' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_doublematrix(a) || not_doublematrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

  cn=a->dimensions[0];
  cm=b->dimensions[1];
  dims[0] = cn;
  dims[1] = cm;

  an = a->dimensions[0];
  am = a->dimensions[1];

  bn = b->dimensions[0];
  bm = b->dimensions[1];
  


  /* Make a new double vector of same dimension */
  c=(PyArrayObject *) PyArray_FromDims(2,dims,NPY_DOUBLE);
  
  if (not_doublematrix(c)) return NULL;

  d_wmulB(&cf, &k, &cm, &cn,&cm, &cn, (double *)c->data,
	&cf, &k, &am, &an,&am, &an, (double *)a->data,
	&cf, &k, &bm, &bn,&bm, &bn, (double *)b->data);

  return PyArray_Return(c);
}



/* ==== matrix multiply  =========================
    Returns a NumPy vector array
    interface:  d_waddmulP(c,a,b)
                c,a,b are NumPy Python vector (double)
                returns a NumPy vector                                        */
static PyObject* d_waddmulP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm;
  int k=0;
  int T=0;

  double cf=1.0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!O!", 
			&PyArray_Type, &c,&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'double' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_doublematrix(c) || not_doublematrix(a) || not_doublematrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

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
  


  d_waddmulB(&cf, &k, &cm, &cn,&cm, &cn, (double *)c->data,
	   &cf, &k, &am, &an,&am, &an, (double *)a->data,
	   &cf, &k, &bm, &bn,&bm, &bn, (double *)b->data);

  return PyArray_Return(c);
}


/* ==== matrix multiply  =========================
    Returns a NEW  NumPy vector array
    interface:  d_wmP(a,b)
                a is NumPy vector, b is Python vector (double)
                returns a NumPy vector                                        */

static PyObject* d_wmP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm,dims[2];
  int k=0;
  double cf=1.0;
  int T=0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!", 
			&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'double' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_doublematrix(a) || not_doublematrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

  cn=a->dimensions[0];
  cm=b->dimensions[1];
  dims[0] = cn;
  dims[1] = cm;

  an = a->dimensions[0];
  am = a->dimensions[1];

  bn = b->dimensions[0];
  bm = b->dimensions[1];
  


  /* Make a new double vector of same dimension */
  c=(PyArrayObject *) PyArray_FromDims(2,dims,NPY_DOUBLE);
  
  if (not_doublematrix(c)) return NULL;

  d_wmB(&cf, &k, &cm, &cn,&cm, &cn, (double *)c->data,
	&cf, &k, &am, &an,&am, &an, (double *)a->data,
	&cf, &k, &bm, &bn,&bm, &bn, (double *)b->data);

  return PyArray_Return(c);
}



/* ==== matrix multiply  =========================
    Returns a NumPy vector array
    interface:  d_wmaddP(c,a,b)
                c,a,b are NumPy Python vector (double)
                returns a NumPy vector                                        */
static PyObject* d_wmaddP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm;
  int k=0;
  int T=0;

  double cf=1.0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!O!", 
			&PyArray_Type, &c,&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'double' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_doublematrix(c) || not_doublematrix(a) || not_doublematrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

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

  return PyArray_Return(c);
}


/* ==== matrix multiply  =========================
    Returns a NEW  NumPy vector array
    interface:  d_wmRP(a,b)
                a is NumPy vector, b is Python vector (double)
                returns a NumPy vector                                        */

static PyObject* d_wmRP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm,dims[2];
  int k=0;
  double cf=1.0;
  int T=0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!", 
			&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'double' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_doublematrix(a) || not_doublematrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

  cn=a->dimensions[0];
  cm=b->dimensions[1];
  dims[0] = cn;
  dims[1] = cm;

  an = a->dimensions[0];
  am = a->dimensions[1];

  bn = b->dimensions[0];
  bm = b->dimensions[1];
  


  /* Make a new double vector of same dimension */
  c=(PyArrayObject *) PyArray_FromDims(2,dims,NPY_DOUBLE);
  
  if (not_doublematrix(c)) return NULL;

  d_wmRB(&cf, &k, &cm, &cn,&cm, &cn, (double *)c->data,
	&cf, &k, &am, &an,&am, &an, (double *)a->data,
	&cf, &k, &bm, &bn,&bm, &bn, (double *)b->data);

  return PyArray_Return(c);
}



/* ==== matrix multiply  =========================
    Returns a NumPy vector array
    interface:  d_wmaddRP(c,a,b)
                c,a,b are NumPy Python vector (double)
                returns a NumPy vector                                        */
static PyObject* d_wmaddRP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm;
  int k=0;
  int T=0;

  double cf=1.0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!O!", 
			&PyArray_Type, &c,&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'double' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_doublematrix(c) || not_doublematrix(a) || not_doublematrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

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
  


  d_wmaddRB(&cf, &k, &cm, &cn,&cm, &cn, (double *)c->data,
	   &cf, &k, &am, &an,&am, &an, (double *)a->data,
	   &cf, &k, &bm, &bn,&bm, &bn, (double *)b->data);

  return PyArray_Return(c);
}


/* ==== matrix multiply  =========================
    Returns a NEW  NumPy vector array
    interface:  d_wmTRP(a,b)
                a is NumPy vector, b is Python vector (double)
                returns a NumPy vector                                        */

static PyObject* d_wmTRP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm,dims[2];
  int k=0;
  double cf=1.0;
  int T=0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!", 
			&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'double' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_doublematrix(a) || not_doublematrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

  cn=a->dimensions[0];
  cm=b->dimensions[1];
  dims[0] = cn;
  dims[1] = cm;

  an = a->dimensions[0];
  am = a->dimensions[1];

  bn = b->dimensions[0];
  bm = b->dimensions[1];
  


  /* Make a new double vector of same dimension */
  c=(PyArrayObject *) PyArray_FromDims(2,dims,NPY_DOUBLE);
  
  if (not_doublematrix(c)) return NULL;

  d_wmTRB(&cf, &k, &cm, &cn,&cm, &cn, (double *)c->data,
	&cf, &k, &am, &an,&am, &an, (double *)a->data,
	&cf, &k, &bm, &bn,&bm, &bn, (double *)b->data);

  return PyArray_Return(c);
}



/* ==== matrix multiply  =========================
    Returns a NumPy vector array
    interface:  d_wmaddTRP(c,a,b)
                c,a,b are NumPy Python vector (double)
                returns a NumPy vector                                        */
static PyObject* d_wmaddTRP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm;
  int k=0;
  int T=0;

  double cf=1.0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!O!", 
			&PyArray_Type, &c,&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'double' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_doublematrix(c) || not_doublematrix(a) || not_doublematrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

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
  


  d_wmaddTRB(&cf, &k, &cm, &cn,&cm, &cn, (double *)c->data,
	   &cf, &k, &am, &an,&am, &an, (double *)a->data,
	   &cf, &k, &bm, &bn,&bm, &bn, (double *)b->data);

  return PyArray_Return(c);
}


/* ==== matrix multiply  =========================
    Returns a NEW  NumPy vector array
    interface:  d_adaptive_smulP(a,b)
                a is NumPy vector, b is Python vector (double)
                returns a NumPy vector                                        */

static PyObject* d_adaptive_smulP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm,dims[2];
  int k=0;
  double cf=1.0;
  int T=0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!d", 
			&PyArray_Type, &a,&PyArray_Type, &b,&T))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'double' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_doublematrix(a) || not_doublematrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

  cn=a->dimensions[0];
  cm=b->dimensions[1];
  dims[0] = cn;
  dims[1] = cm;

  an = a->dimensions[0];
  am = a->dimensions[1];

  bn = b->dimensions[0];
  bm = b->dimensions[1];
  


  /* Make a new double vector of same dimension */
  c=(PyArrayObject *) PyArray_FromDims(2,dims,NPY_DOUBLE);
  
  if (not_doublematrix(c)) return NULL;

  d_adaptive_smulB(&cf, &k, &cm, &cn,&cm, &cn, (double *)c->data,
	&cf, &k, &am, &an,&am, &an, (double *)a->data,
	&cf, &k, &bm, &bn,&bm, &bn, (double *)b->data,&T);

  return PyArray_Return(c);
}



/* ==== matrix multiply  =========================
    Returns a NEW  NumPy vector array
    interface:  d_omulP(a,b)
                a is NumPy vector, b is Python vector (double)
                returns a NumPy vector                                        */

static PyObject* d_omulP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm,dims[2];
  int k=0;
  double cf=1.0;
  int T=0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!", 
			&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'double' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_doublematrix(a) || not_doublematrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

  cn=a->dimensions[0];
  cm=b->dimensions[1];
  dims[0] = cn;
  dims[1] = cm;

  an = a->dimensions[0];
  am = a->dimensions[1];

  bn = b->dimensions[0];
  bm = b->dimensions[1];
  


  /* Make a new double vector of same dimension */
  c=(PyArrayObject *) PyArray_FromDims(2,dims,NPY_DOUBLE);
  
  if (not_doublematrix(c)) return NULL;

  d_omulB(&cf, &k, &cm, &cn,&cm, &cn, (double *)c->data,
	&cf, &k, &am, &an,&am, &an, (double *)a->data,
	&cf, &k, &bm, &bn,&bm, &bn, (double *)b->data);

  return PyArray_Return(c);
}



/* ==== matrix multiply  =========================
    Returns a NumPy vector array
    interface:  d_oaddmulP(c,a,b)
                c,a,b are NumPy Python vector (double)
                returns a NumPy vector                                        */
static PyObject* d_oaddmulP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm;
  int k=0;
  int T=0;

  double cf=1.0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!O!", 
			&PyArray_Type, &c,&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'double' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_doublematrix(c) || not_doublematrix(a) || not_doublematrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

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
  


  d_oaddmulB(&cf, &k, &cm, &cn,&cm, &cn, (double *)c->data,
	   &cf, &k, &am, &an,&am, &an, (double *)a->data,
	   &cf, &k, &bm, &bn,&bm, &bn, (double *)b->data);

  return PyArray_Return(c);
}


/* ==== matrix multiply  =========================
    Returns a NEW  NumPy vector array
    interface:  d_owmulP(a,b)
                a is NumPy vector, b is Python vector (double)
                returns a NumPy vector                                        */

static PyObject* d_owmulP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm,dims[2];
  int k=0;
  double cf=1.0;
  int T=0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!", 
			&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'double' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_doublematrix(a) || not_doublematrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

  cn=a->dimensions[0];
  cm=b->dimensions[1];
  dims[0] = cn;
  dims[1] = cm;

  an = a->dimensions[0];
  am = a->dimensions[1];

  bn = b->dimensions[0];
  bm = b->dimensions[1];
  


  /* Make a new double vector of same dimension */
  c=(PyArrayObject *) PyArray_FromDims(2,dims,NPY_DOUBLE);
  
  if (not_doublematrix(c)) return NULL;

  d_owmulB(&cf, &k, &cm, &cn,&cm, &cn, (double *)c->data,
	&cf, &k, &am, &an,&am, &an, (double *)a->data,
	&cf, &k, &bm, &bn,&bm, &bn, (double *)b->data);

  return PyArray_Return(c);
}



/* ==== matrix multiply  =========================
    Returns a NumPy vector array
    interface:  d_owaddmulP(c,a,b)
                c,a,b are NumPy Python vector (double)
                returns a NumPy vector                                        */
static PyObject* d_owaddmulP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm;
  int k=0;
  int T=0;

  double cf=1.0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!O!", 
			&PyArray_Type, &c,&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'double' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_doublematrix(c) || not_doublematrix(a) || not_doublematrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

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
  


  d_owaddmulB(&cf, &k, &cm, &cn,&cm, &cn, (double *)c->data,
	   &cf, &k, &am, &an,&am, &an, (double *)a->data,
	   &cf, &k, &bm, &bn,&bm, &bn, (double *)b->data);

  return PyArray_Return(c);
}


/* ==== matrix multiply  =========================
    Returns a NEW  NumPy vector array
    interface:  d_bmP(a,b)
                a is NumPy vector, b is Python vector (double)
                returns a NumPy vector                                        */

static PyObject* d_bmP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm,dims[2];
  int k=0;
  double cf=1.0;
  int T=0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!", 
			&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'double' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_doublematrix(a) || not_doublematrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

  cn=a->dimensions[0];
  cm=b->dimensions[1];
  dims[0] = cn;
  dims[1] = cm;

  an = a->dimensions[0];
  am = a->dimensions[1];

  bn = b->dimensions[0];
  bm = b->dimensions[1];
  


  /* Make a new double vector of same dimension */
  c=(PyArrayObject *) PyArray_FromDims(2,dims,NPY_DOUBLE);
  
  if (not_doublematrix(c)) return NULL;

  d_bmB(&cf, &k, &cm, &cn,&cm, &cn, (double *)c->data,
	&cf, &k, &am, &an,&am, &an, (double *)a->data,
	&cf, &k, &bm, &bn,&bm, &bn, (double *)b->data);

  return PyArray_Return(c);
}



/* ==== matrix multiply  =========================
    Returns a NumPy vector array
    interface:  d_bmaddP(c,a,b)
                c,a,b are NumPy Python vector (double)
                returns a NumPy vector                                        */
static PyObject* d_bmaddP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm;
  int k=0;
  int T=0;

  double cf=1.0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!O!", 
			&PyArray_Type, &c,&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'double' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_doublematrix(c) || not_doublematrix(a) || not_doublematrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

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
  


  d_bmaddB(&cf, &k, &cm, &cn,&cm, &cn, (double *)c->data,
	   &cf, &k, &am, &an,&am, &an, (double *)a->data,
	   &cf, &k, &bm, &bn,&bm, &bn, (double *)b->data);

  return PyArray_Return(c);
}


/* ==== matrix multiply  =========================
    Returns a NumPy vector array
    interface:  d_ptaddmulP(c,a,b)
                c,a,b are NumPy Python vector (double)
                returns a NumPy vector                                        */
static PyObject* d_ptaddmulP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm;
  int k=0;
  int T=0;

  double cf=1.0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!O!", 
			&PyArray_Type, &c,&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'double' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_doublematrix(c) || not_doublematrix(a) || not_doublematrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

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
  


  d_ptaddmulB(&cf, &k, &cm, &cn,&cm, &cn, (double *)c->data,
	   &cf, &k, &am, &an,&am, &an, (double *)a->data,
	   &cf, &k, &bm, &bn,&bm, &bn, (double *)b->data);

  return PyArray_Return(c);
}


/* ==== matrix multiply  =========================
    Returns a NEW  NumPy vector array
    interface:  d_wmpipeP(a,b)
                a is NumPy vector, b is Python vector (double)
                returns a NumPy vector                                        */

static PyObject* d_wmpipeP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm,dims[2];
  int k=0;
  double cf=1.0;
  int T=0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!", 
			&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'double' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_doublematrix(a) || not_doublematrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

  cn=a->dimensions[0];
  cm=b->dimensions[1];
  dims[0] = cn;
  dims[1] = cm;

  an = a->dimensions[0];
  am = a->dimensions[1];

  bn = b->dimensions[0];
  bm = b->dimensions[1];
  


  /* Make a new double vector of same dimension */
  c=(PyArrayObject *) PyArray_FromDims(2,dims,NPY_DOUBLE);
  
  if (not_doublematrix(c)) return NULL;

  d_wmpipeB(&cf, &k, &cm, &cn,&cm, &cn, (double *)c->data,
	&cf, &k, &am, &an,&am, &an, (double *)a->data,
	&cf, &k, &bm, &bn,&bm, &bn, (double *)b->data);

  return PyArray_Return(c);
}



/* ==== matrix multiply  =========================
    Returns a NumPy vector array
    interface:  d_wmaddpipeP(c,a,b)
                c,a,b are NumPy Python vector (double)
                returns a NumPy vector                                        */
static PyObject* d_wmaddpipeP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm;
  int k=0;
  int T=0;

  double cf=1.0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!O!", 
			&PyArray_Type, &c,&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'double' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_doublematrix(c) || not_doublematrix(a) || not_doublematrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

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
  


  d_wmaddpipeB(&cf, &k, &cm, &cn,&cm, &cn, (double *)c->data,
	   &cf, &k, &am, &an,&am, &an, (double *)a->data,
	   &cf, &k, &bm, &bn,&bm, &bn, (double *)b->data);

  return PyArray_Return(c);
}


/* ==== matrix multiply  =========================
    Returns a NEW  NumPy vector array
    interface:  d_bmpipeP(a,b)
                a is NumPy vector, b is Python vector (double)
                returns a NumPy vector                                        */

static PyObject* d_bmpipeP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm,dims[2];
  int k=0;
  double cf=1.0;
  int T=0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!", 
			&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'double' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_doublematrix(a) || not_doublematrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

  cn=a->dimensions[0];
  cm=b->dimensions[1];
  dims[0] = cn;
  dims[1] = cm;

  an = a->dimensions[0];
  am = a->dimensions[1];

  bn = b->dimensions[0];
  bm = b->dimensions[1];
  


  /* Make a new double vector of same dimension */
  c=(PyArrayObject *) PyArray_FromDims(2,dims,NPY_DOUBLE);
  
  if (not_doublematrix(c)) return NULL;

  d_bmpipeB(&cf, &k, &cm, &cn,&cm, &cn, (double *)c->data,
	&cf, &k, &am, &an,&am, &an, (double *)a->data,
	&cf, &k, &bm, &bn,&bm, &bn, (double *)b->data);

  return PyArray_Return(c);
}



/* ==== matrix multiply  =========================
    Returns a NumPy vector array
    interface:  d_bmaddpipeP(c,a,b)
                c,a,b are NumPy Python vector (double)
                returns a NumPy vector                                        */
static PyObject* d_bmaddpipeP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm;
  int k=0;
  int T=0;

  double cf=1.0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!O!", 
			&PyArray_Type, &c,&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'double' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_doublematrix(c) || not_doublematrix(a) || not_doublematrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

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
  


  d_bmaddpipeB(&cf, &k, &cm, &cn,&cm, &cn, (double *)c->data,
	   &cf, &k, &am, &an,&am, &an, (double *)a->data,
	   &cf, &k, &bm, &bn,&bm, &bn, (double *)b->data);

  return PyArray_Return(c);
}


/* ==== matrix multiply  =========================
    Returns a NEW  NumPy vector array
    interface:  d_smpipeP(a,b)
                a is NumPy vector, b is Python vector (double)
                returns a NumPy vector                                        */

static PyObject* d_smpipeP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm,dims[2];
  int k=0;
  double cf=1.0;
  int T=0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!", 
			&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'double' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_doublematrix(a) || not_doublematrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

  cn=a->dimensions[0];
  cm=b->dimensions[1];
  dims[0] = cn;
  dims[1] = cm;

  an = a->dimensions[0];
  am = a->dimensions[1];

  bn = b->dimensions[0];
  bm = b->dimensions[1];
  


  /* Make a new double vector of same dimension */
  c=(PyArrayObject *) PyArray_FromDims(2,dims,NPY_DOUBLE);
  
  if (not_doublematrix(c)) return NULL;

  d_smpipeB(&cf, &k, &cm, &cn,&cm, &cn, (double *)c->data,
	&cf, &k, &am, &an,&am, &an, (double *)a->data,
	&cf, &k, &bm, &bn,&bm, &bn, (double *)b->data);

  return PyArray_Return(c);
}



/* ==== matrix multiply  =========================
    Returns a NumPy vector array
    interface:  d_smaddpipeP(c,a,b)
                c,a,b are NumPy Python vector (double)
                returns a NumPy vector                                        */
static PyObject* d_smaddpipeP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm;
  int k=0;
  int T=0;

  double cf=1.0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!O!", 
			&PyArray_Type, &c,&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'double' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_doublematrix(c) || not_doublematrix(a) || not_doublematrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

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
  


  d_smaddpipeB(&cf, &k, &cm, &cn,&cm, &cn, (double *)c->data,
	   &cf, &k, &am, &an,&am, &an, (double *)a->data,
	   &cf, &k, &bm, &bn,&bm, &bn, (double *)b->data);

  return PyArray_Return(c);
}


/* ==== matrix multiply  =========================
    Returns a NEW  NumPy vector array
    interface:  d_RmulP(a,b)
                a is NumPy vector, b is Python vector (double)
                returns a NumPy vector                                        */

static PyObject* d_RmulP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm,dims[2];
  int k=0;
  double cf=1.0;
  int T=0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!", 
			&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'double' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_doublematrix(a) || not_doublematrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

  cn=a->dimensions[0];
  cm=b->dimensions[1];
  dims[0] = cn;
  dims[1] = cm;

  an = a->dimensions[0];
  am = a->dimensions[1];

  bn = b->dimensions[0];
  bm = b->dimensions[1];
  


  /* Make a new double vector of same dimension */
  c=(PyArrayObject *) PyArray_FromDims(2,dims,NPY_DOUBLE);
  
  if (not_doublematrix(c)) return NULL;

  d_RmulB(&cf, &k, &cm, &cn,&cm, &cn, (double *)c->data,
	&cf, &k, &am, &an,&am, &an, (double *)a->data,
	&cf, &k, &bm, &bn,&bm, &bn, (double *)b->data);

  return PyArray_Return(c);
}



/* ==== matrix multiply  =========================
    Returns a NEW  NumPy vector array
    interface:  d_adaptive_wmP(a,b)
                a is NumPy vector, b is Python vector (double)
                returns a NumPy vector                                        */

static PyObject* d_adaptive_wmP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm,dims[2];
  int k=0;
  double cf=1.0;
  int T=0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!d", 
			&PyArray_Type, &a,&PyArray_Type, &b,&T))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'double' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_doublematrix(a) || not_doublematrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

  cn=a->dimensions[0];
  cm=b->dimensions[1];
  dims[0] = cn;
  dims[1] = cm;

  an = a->dimensions[0];
  am = a->dimensions[1];

  bn = b->dimensions[0];
  bm = b->dimensions[1];
  


  /* Make a new double vector of same dimension */
  c=(PyArrayObject *) PyArray_FromDims(2,dims,NPY_DOUBLE);
  
  if (not_doublematrix(c)) return NULL;

  d_adaptive_wmB(&cf, &k, &cm, &cn,&cm, &cn, (double *)c->data,
	&cf, &k, &am, &an,&am, &an, (double *)a->data,
	&cf, &k, &bm, &bn,&bm, &bn, (double *)b->data,&T);

  return PyArray_Return(c);
}



/* ==== matrix multiply  =========================
    Returns a NumPy vector array
    interface:  d_BMADD_PIPEP(c,a,b)
                c,a,b are NumPy Python vector (double)
                returns a NumPy vector                                        */
static PyObject* d_BMADD_PIPEP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm;
  int k=0;
  int T=0;

  double cf=1.0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!O!", 
			&PyArray_Type, &c,&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'double' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_doublematrix(c) || not_doublematrix(a) || not_doublematrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

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
  


  d_BMADD_PIPEB(&cf, &k, &cm, &cn,&cm, &cn, (double *)c->data,
	   &cf, &k, &am, &an,&am, &an, (double *)a->data,
	   &cf, &k, &bm, &bn,&bm, &bn, (double *)b->data);

  return PyArray_Return(c);
}


/* ==== matrix multiply  =========================
    Returns a NumPy vector array
    interface:  d_BMADDP(c,a,b)
                c,a,b are NumPy Python vector (double)
                returns a NumPy vector                                        */
static PyObject* d_BMADDP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm;
  int k=0;
  int T=0;

  double cf=1.0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!O!", 
			&PyArray_Type, &c,&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'double' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_doublematrix(c) || not_doublematrix(a) || not_doublematrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

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
  


  d_BMADDB(&cf, &k, &cm, &cn,&cm, &cn, (double *)c->data,
	   &cf, &k, &am, &an,&am, &an, (double *)a->data,
	   &cf, &k, &bm, &bn,&bm, &bn, (double *)b->data);

  return PyArray_Return(c);
}


/* ==== matrix multiply  =========================
    Returns a NumPy vector array
    interface:  d_BMADDRP(c,a,b)
                c,a,b are NumPy Python vector (double)
                returns a NumPy vector                                        */
static PyObject* d_BMADDRP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm;
  int k=0;
  int T=0;

  double cf=1.0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!O!", 
			&PyArray_Type, &c,&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'double' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_doublematrix(c) || not_doublematrix(a) || not_doublematrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

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
  


  d_BMADDRB(&cf, &k, &cm, &cn,&cm, &cn, (double *)c->data,
	   &cf, &k, &am, &an,&am, &an, (double *)a->data,
	   &cf, &k, &bm, &bn,&bm, &bn, (double *)b->data);

  return PyArray_Return(c);
}


/* ==== matrix multiply  =========================
    Returns a NEW  NumPy vector array
    interface:  d_BMOWR_PIPEP(a,b)
                a is NumPy vector, b is Python vector (double)
                returns a NumPy vector                                        */

static PyObject* d_BMOWR_PIPEP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm,dims[2];
  int k=0;
  double cf=1.0;
  int T=0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!", 
			&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'double' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_doublematrix(a) || not_doublematrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

  cn=a->dimensions[0];
  cm=b->dimensions[1];
  dims[0] = cn;
  dims[1] = cm;

  an = a->dimensions[0];
  am = a->dimensions[1];

  bn = b->dimensions[0];
  bm = b->dimensions[1];
  


  /* Make a new double vector of same dimension */
  c=(PyArrayObject *) PyArray_FromDims(2,dims,NPY_DOUBLE);
  
  if (not_doublematrix(c)) return NULL;

  d_BMOWR_PIPEB(&cf, &k, &cm, &cn,&cm, &cn, (double *)c->data,
	&cf, &k, &am, &an,&am, &an, (double *)a->data,
	&cf, &k, &bm, &bn,&bm, &bn, (double *)b->data);

  return PyArray_Return(c);
}



/* ==== matrix multiply  =========================
    Returns a NEW  NumPy vector array
    interface:  d_BMOWRP(a,b)
                a is NumPy vector, b is Python vector (double)
                returns a NumPy vector                                        */

static PyObject* d_BMOWRP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm,dims[2];
  int k=0;
  double cf=1.0;
  int T=0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!", 
			&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'double' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_doublematrix(a) || not_doublematrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

  cn=a->dimensions[0];
  cm=b->dimensions[1];
  dims[0] = cn;
  dims[1] = cm;

  an = a->dimensions[0];
  am = a->dimensions[1];

  bn = b->dimensions[0];
  bm = b->dimensions[1];
  


  /* Make a new double vector of same dimension */
  c=(PyArrayObject *) PyArray_FromDims(2,dims,NPY_DOUBLE);
  
  if (not_doublematrix(c)) return NULL;

  d_BMOWRB(&cf, &k, &cm, &cn,&cm, &cn, (double *)c->data,
	&cf, &k, &am, &an,&am, &an, (double *)a->data,
	&cf, &k, &bm, &bn,&bm, &bn, (double *)b->data);

  return PyArray_Return(c);
}



/* ==== matrix multiply  =========================
    Returns a NEW  NumPy vector array
    interface:  d_BMOWRRP(a,b)
                a is NumPy vector, b is Python vector (double)
                returns a NumPy vector                                        */

static PyObject* d_BMOWRRP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm,dims[2];
  int k=0;
  double cf=1.0;
  int T=0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!", 
			&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'double' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_doublematrix(a) || not_doublematrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

  cn=a->dimensions[0];
  cm=b->dimensions[1];
  dims[0] = cn;
  dims[1] = cm;

  an = a->dimensions[0];
  am = a->dimensions[1];

  bn = b->dimensions[0];
  bm = b->dimensions[1];
  


  /* Make a new double vector of same dimension */
  c=(PyArrayObject *) PyArray_FromDims(2,dims,NPY_DOUBLE);
  
  if (not_doublematrix(c)) return NULL;

  d_BMOWRRB(&cf, &k, &cm, &cn,&cm, &cn, (double *)c->data,
	&cf, &k, &am, &an,&am, &an, (double *)a->data,
	&cf, &k, &bm, &bn,&bm, &bn, (double *)b->data);

  return PyArray_Return(c);
}



/* ==== matrix multiply  =========================
    Returns a NEW  NumPy vector array
    interface:  c_dcmulP(a,b)
                a is NumPy vector, b is Python vector (float complex)
                returns a NumPy vector                                        */

static PyObject* c_dcmulP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm,dims[2];
  int k=0;
  float complex cf=1.0;
  int T=0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!", 
			&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'float complex' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_floatcomplexmatrix(a) || not_floatcomplexmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

  cn=a->dimensions[0];
  cm=b->dimensions[1];
  dims[0] = cn;
  dims[1] = cm;

  an = a->dimensions[0];
  am = a->dimensions[1];

  bn = b->dimensions[0];
  bm = b->dimensions[1];
  


  /* Make a new float complex vector of same dimension */
  c=(PyArrayObject *) PyArray_FromDims(2,dims,NPY_CFLOAT);
  
  if (not_floatcomplexmatrix(c)) return NULL;

  c_dcmulB(&cf, &k, &cm, &cn,&cm, &cn, (float complex *)c->data,
	&cf, &k, &am, &an,&am, &an, (float complex *)a->data,
	&cf, &k, &bm, &bn,&bm, &bn, (float complex *)b->data);

  return PyArray_Return(c);
}



/* ==== matrix multiply  =========================
    Returns a NEW  NumPy vector array
    interface:  c_mulP(a,b)
                a is NumPy vector, b is Python vector (float complex)
                returns a NumPy vector                                        */

static PyObject* c_mulP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm,dims[2];
  int k=0;
  float complex cf=1.0;
  int T=0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!", 
			&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'float complex' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_floatcomplexmatrix(a) || not_floatcomplexmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

  cn=a->dimensions[0];
  cm=b->dimensions[1];
  dims[0] = cn;
  dims[1] = cm;

  an = a->dimensions[0];
  am = a->dimensions[1];

  bn = b->dimensions[0];
  bm = b->dimensions[1];
  


  /* Make a new float complex vector of same dimension */
  c=(PyArrayObject *) PyArray_FromDims(2,dims,NPY_CFLOAT);
  
  if (not_floatcomplexmatrix(c)) return NULL;

  c_mulB(&cf, &k, &cm, &cn,&cm, &cn, (float complex *)c->data,
	&cf, &k, &am, &an,&am, &an, (float complex *)a->data,
	&cf, &k, &bm, &bn,&bm, &bn, (float complex *)b->data);

  return PyArray_Return(c);
}



/* ==== matrix multiply  =========================
    Returns a NEW  NumPy vector array
    interface:  c_mulptP(a,b)
                a is NumPy vector, b is Python vector (float complex)
                returns a NumPy vector                                        */

static PyObject* c_mulptP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm,dims[2];
  int k=0;
  float complex cf=1.0;
  int T=0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!", 
			&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'float complex' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_floatcomplexmatrix(a) || not_floatcomplexmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

  cn=a->dimensions[0];
  cm=b->dimensions[1];
  dims[0] = cn;
  dims[1] = cm;

  an = a->dimensions[0];
  am = a->dimensions[1];

  bn = b->dimensions[0];
  bm = b->dimensions[1];
  


  /* Make a new float complex vector of same dimension */
  c=(PyArrayObject *) PyArray_FromDims(2,dims,NPY_CFLOAT);
  
  if (not_floatcomplexmatrix(c)) return NULL;

  c_mulptB(&cf, &k, &cm, &cn,&cm, &cn, (float complex *)c->data,
	&cf, &k, &am, &an,&am, &an, (float complex *)a->data,
	&cf, &k, &bm, &bn,&bm, &bn, (float complex *)b->data);

  return PyArray_Return(c);
}



/* ==== matrix multiply  =========================
    Returns a NumPy vector array
    interface:  c_maddP(c,a,b)
                c,a,b are NumPy Python vector (float complex)
                returns a NumPy vector                                        */
static PyObject* c_maddP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm;
  int k=0;
  int T=0;

  float complex cf=1.0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!O!", 
			&PyArray_Type, &c,&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'float complex' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_floatcomplexmatrix(c) || not_floatcomplexmatrix(a) || not_floatcomplexmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

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
  


  c_maddB(&cf, &k, &cm, &cn,&cm, &cn, (float complex *)c->data,
	   &cf, &k, &am, &an,&am, &an, (float complex *)a->data,
	   &cf, &k, &bm, &bn,&bm, &bn, (float complex *)b->data);

  return PyArray_Return(c);
}


/* ==== matrix multiply  =========================
    Returns a NumPy vector array
    interface:  c_saddmulP(c,a,b)
                c,a,b are NumPy Python vector (float complex)
                returns a NumPy vector                                        */
static PyObject* c_saddmulP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm;
  int k=0;
  int T=0;

  float complex cf=1.0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!O!", 
			&PyArray_Type, &c,&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'float complex' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_floatcomplexmatrix(c) || not_floatcomplexmatrix(a) || not_floatcomplexmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

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
  


  c_saddmulB(&cf, &k, &cm, &cn,&cm, &cn, (float complex *)c->data,
	   &cf, &k, &am, &an,&am, &an, (float complex *)a->data,
	   &cf, &k, &bm, &bn,&bm, &bn, (float complex *)b->data);

  return PyArray_Return(c);
}


/* ==== matrix multiply  =========================
    Returns a NEW  NumPy vector array
    interface:  c_smulP(a,b)
                a is NumPy vector, b is Python vector (float complex)
                returns a NumPy vector                                        */

static PyObject* c_smulP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm,dims[2];
  int k=0;
  float complex cf=1.0;
  int T=0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!", 
			&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'float complex' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_floatcomplexmatrix(a) || not_floatcomplexmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

  cn=a->dimensions[0];
  cm=b->dimensions[1];
  dims[0] = cn;
  dims[1] = cm;

  an = a->dimensions[0];
  am = a->dimensions[1];

  bn = b->dimensions[0];
  bm = b->dimensions[1];
  


  /* Make a new float complex vector of same dimension */
  c=(PyArrayObject *) PyArray_FromDims(2,dims,NPY_CFLOAT);
  
  if (not_floatcomplexmatrix(c)) return NULL;

  c_smulB(&cf, &k, &cm, &cn,&cm, &cn, (float complex *)c->data,
	&cf, &k, &am, &an,&am, &an, (float complex *)a->data,
	&cf, &k, &bm, &bn,&bm, &bn, (float complex *)b->data);

  return PyArray_Return(c);
}



/* ==== matrix multiply  =========================
    Returns a NumPy vector array
    interface:  c_saddmulRP(c,a,b)
                c,a,b are NumPy Python vector (float complex)
                returns a NumPy vector                                        */
static PyObject* c_saddmulRP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm;
  int k=0;
  int T=0;

  float complex cf=1.0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!O!", 
			&PyArray_Type, &c,&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'float complex' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_floatcomplexmatrix(c) || not_floatcomplexmatrix(a) || not_floatcomplexmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

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
  


  c_saddmulRB(&cf, &k, &cm, &cn,&cm, &cn, (float complex *)c->data,
	   &cf, &k, &am, &an,&am, &an, (float complex *)a->data,
	   &cf, &k, &bm, &bn,&bm, &bn, (float complex *)b->data);

  return PyArray_Return(c);
}


/* ==== matrix multiply  =========================
    Returns a NEW  NumPy vector array
    interface:  c_smulRP(a,b)
                a is NumPy vector, b is Python vector (float complex)
                returns a NumPy vector                                        */

static PyObject* c_smulRP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm,dims[2];
  int k=0;
  float complex cf=1.0;
  int T=0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!", 
			&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'float complex' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_floatcomplexmatrix(a) || not_floatcomplexmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

  cn=a->dimensions[0];
  cm=b->dimensions[1];
  dims[0] = cn;
  dims[1] = cm;

  an = a->dimensions[0];
  am = a->dimensions[1];

  bn = b->dimensions[0];
  bm = b->dimensions[1];
  


  /* Make a new float complex vector of same dimension */
  c=(PyArrayObject *) PyArray_FromDims(2,dims,NPY_CFLOAT);
  
  if (not_floatcomplexmatrix(c)) return NULL;

  c_smulRB(&cf, &k, &cm, &cn,&cm, &cn, (float complex *)c->data,
	&cf, &k, &am, &an,&am, &an, (float complex *)a->data,
	&cf, &k, &bm, &bn,&bm, &bn, (float complex *)b->data);

  return PyArray_Return(c);
}



/* ==== matrix multiply  =========================
    Returns a NEW  NumPy vector array
    interface:  c_wmulP(a,b)
                a is NumPy vector, b is Python vector (float complex)
                returns a NumPy vector                                        */

static PyObject* c_wmulP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm,dims[2];
  int k=0;
  float complex cf=1.0;
  int T=0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!", 
			&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'float complex' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_floatcomplexmatrix(a) || not_floatcomplexmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

  cn=a->dimensions[0];
  cm=b->dimensions[1];
  dims[0] = cn;
  dims[1] = cm;

  an = a->dimensions[0];
  am = a->dimensions[1];

  bn = b->dimensions[0];
  bm = b->dimensions[1];
  


  /* Make a new float complex vector of same dimension */
  c=(PyArrayObject *) PyArray_FromDims(2,dims,NPY_CFLOAT);
  
  if (not_floatcomplexmatrix(c)) return NULL;

  c_wmulB(&cf, &k, &cm, &cn,&cm, &cn, (float complex *)c->data,
	&cf, &k, &am, &an,&am, &an, (float complex *)a->data,
	&cf, &k, &bm, &bn,&bm, &bn, (float complex *)b->data);

  return PyArray_Return(c);
}



/* ==== matrix multiply  =========================
    Returns a NumPy vector array
    interface:  c_waddmulP(c,a,b)
                c,a,b are NumPy Python vector (float complex)
                returns a NumPy vector                                        */
static PyObject* c_waddmulP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm;
  int k=0;
  int T=0;

  float complex cf=1.0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!O!", 
			&PyArray_Type, &c,&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'float complex' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_floatcomplexmatrix(c) || not_floatcomplexmatrix(a) || not_floatcomplexmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

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
  


  c_waddmulB(&cf, &k, &cm, &cn,&cm, &cn, (float complex *)c->data,
	   &cf, &k, &am, &an,&am, &an, (float complex *)a->data,
	   &cf, &k, &bm, &bn,&bm, &bn, (float complex *)b->data);

  return PyArray_Return(c);
}


/* ==== matrix multiply  =========================
    Returns a NEW  NumPy vector array
    interface:  c_wmP(a,b)
                a is NumPy vector, b is Python vector (float complex)
                returns a NumPy vector                                        */

static PyObject* c_wmP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm,dims[2];
  int k=0;
  float complex cf=1.0;
  int T=0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!", 
			&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'float complex' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_floatcomplexmatrix(a) || not_floatcomplexmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

  cn=a->dimensions[0];
  cm=b->dimensions[1];
  dims[0] = cn;
  dims[1] = cm;

  an = a->dimensions[0];
  am = a->dimensions[1];

  bn = b->dimensions[0];
  bm = b->dimensions[1];
  


  /* Make a new float complex vector of same dimension */
  c=(PyArrayObject *) PyArray_FromDims(2,dims,NPY_CFLOAT);
  
  if (not_floatcomplexmatrix(c)) return NULL;

  c_wmB(&cf, &k, &cm, &cn,&cm, &cn, (float complex *)c->data,
	&cf, &k, &am, &an,&am, &an, (float complex *)a->data,
	&cf, &k, &bm, &bn,&bm, &bn, (float complex *)b->data);

  return PyArray_Return(c);
}



/* ==== matrix multiply  =========================
    Returns a NumPy vector array
    interface:  c_wmaddP(c,a,b)
                c,a,b are NumPy Python vector (float complex)
                returns a NumPy vector                                        */
static PyObject* c_wmaddP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm;
  int k=0;
  int T=0;

  float complex cf=1.0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!O!", 
			&PyArray_Type, &c,&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'float complex' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_floatcomplexmatrix(c) || not_floatcomplexmatrix(a) || not_floatcomplexmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

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
  


  c_wmaddB(&cf, &k, &cm, &cn,&cm, &cn, (float complex *)c->data,
	   &cf, &k, &am, &an,&am, &an, (float complex *)a->data,
	   &cf, &k, &bm, &bn,&bm, &bn, (float complex *)b->data);

  return PyArray_Return(c);
}


/* ==== matrix multiply  =========================
    Returns a NEW  NumPy vector array
    interface:  c_wmRP(a,b)
                a is NumPy vector, b is Python vector (float complex)
                returns a NumPy vector                                        */

static PyObject* c_wmRP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm,dims[2];
  int k=0;
  float complex cf=1.0;
  int T=0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!", 
			&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'float complex' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_floatcomplexmatrix(a) || not_floatcomplexmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

  cn=a->dimensions[0];
  cm=b->dimensions[1];
  dims[0] = cn;
  dims[1] = cm;

  an = a->dimensions[0];
  am = a->dimensions[1];

  bn = b->dimensions[0];
  bm = b->dimensions[1];
  


  /* Make a new float complex vector of same dimension */
  c=(PyArrayObject *) PyArray_FromDims(2,dims,NPY_CFLOAT);
  
  if (not_floatcomplexmatrix(c)) return NULL;

  c_wmRB(&cf, &k, &cm, &cn,&cm, &cn, (float complex *)c->data,
	&cf, &k, &am, &an,&am, &an, (float complex *)a->data,
	&cf, &k, &bm, &bn,&bm, &bn, (float complex *)b->data);

  return PyArray_Return(c);
}



/* ==== matrix multiply  =========================
    Returns a NumPy vector array
    interface:  c_wmaddRP(c,a,b)
                c,a,b are NumPy Python vector (float complex)
                returns a NumPy vector                                        */
static PyObject* c_wmaddRP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm;
  int k=0;
  int T=0;

  float complex cf=1.0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!O!", 
			&PyArray_Type, &c,&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'float complex' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_floatcomplexmatrix(c) || not_floatcomplexmatrix(a) || not_floatcomplexmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

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
  


  c_wmaddRB(&cf, &k, &cm, &cn,&cm, &cn, (float complex *)c->data,
	   &cf, &k, &am, &an,&am, &an, (float complex *)a->data,
	   &cf, &k, &bm, &bn,&bm, &bn, (float complex *)b->data);

  return PyArray_Return(c);
}


/* ==== matrix multiply  =========================
    Returns a NEW  NumPy vector array
    interface:  c_wmTRP(a,b)
                a is NumPy vector, b is Python vector (float complex)
                returns a NumPy vector                                        */

static PyObject* c_wmTRP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm,dims[2];
  int k=0;
  float complex cf=1.0;
  int T=0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!", 
			&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'float complex' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_floatcomplexmatrix(a) || not_floatcomplexmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

  cn=a->dimensions[0];
  cm=b->dimensions[1];
  dims[0] = cn;
  dims[1] = cm;

  an = a->dimensions[0];
  am = a->dimensions[1];

  bn = b->dimensions[0];
  bm = b->dimensions[1];
  


  /* Make a new float complex vector of same dimension */
  c=(PyArrayObject *) PyArray_FromDims(2,dims,NPY_CFLOAT);
  
  if (not_floatcomplexmatrix(c)) return NULL;

  c_wmTRB(&cf, &k, &cm, &cn,&cm, &cn, (float complex *)c->data,
	&cf, &k, &am, &an,&am, &an, (float complex *)a->data,
	&cf, &k, &bm, &bn,&bm, &bn, (float complex *)b->data);

  return PyArray_Return(c);
}



/* ==== matrix multiply  =========================
    Returns a NumPy vector array
    interface:  c_wmaddTRP(c,a,b)
                c,a,b are NumPy Python vector (float complex)
                returns a NumPy vector                                        */
static PyObject* c_wmaddTRP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm;
  int k=0;
  int T=0;

  float complex cf=1.0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!O!", 
			&PyArray_Type, &c,&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'float complex' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_floatcomplexmatrix(c) || not_floatcomplexmatrix(a) || not_floatcomplexmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

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
  


  c_wmaddTRB(&cf, &k, &cm, &cn,&cm, &cn, (float complex *)c->data,
	   &cf, &k, &am, &an,&am, &an, (float complex *)a->data,
	   &cf, &k, &bm, &bn,&bm, &bn, (float complex *)b->data);

  return PyArray_Return(c);
}


/* ==== matrix multiply  =========================
    Returns a NEW  NumPy vector array
    interface:  c_adaptive_smulP(a,b)
                a is NumPy vector, b is Python vector (float complex)
                returns a NumPy vector                                        */

static PyObject* c_adaptive_smulP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm,dims[2];
  int k=0;
  float complex cf=1.0;
  int T=0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!d", 
			&PyArray_Type, &a,&PyArray_Type, &b,&T))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'float complex' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_floatcomplexmatrix(a) || not_floatcomplexmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

  cn=a->dimensions[0];
  cm=b->dimensions[1];
  dims[0] = cn;
  dims[1] = cm;

  an = a->dimensions[0];
  am = a->dimensions[1];

  bn = b->dimensions[0];
  bm = b->dimensions[1];
  


  /* Make a new float complex vector of same dimension */
  c=(PyArrayObject *) PyArray_FromDims(2,dims,NPY_CFLOAT);
  
  if (not_floatcomplexmatrix(c)) return NULL;

  c_adaptive_smulB(&cf, &k, &cm, &cn,&cm, &cn, (float complex *)c->data,
	&cf, &k, &am, &an,&am, &an, (float complex *)a->data,
	&cf, &k, &bm, &bn,&bm, &bn, (float complex *)b->data,&T);

  return PyArray_Return(c);
}



/* ==== matrix multiply  =========================
    Returns a NEW  NumPy vector array
    interface:  c_omulP(a,b)
                a is NumPy vector, b is Python vector (float complex)
                returns a NumPy vector                                        */

static PyObject* c_omulP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm,dims[2];
  int k=0;
  float complex cf=1.0;
  int T=0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!", 
			&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'float complex' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_floatcomplexmatrix(a) || not_floatcomplexmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

  cn=a->dimensions[0];
  cm=b->dimensions[1];
  dims[0] = cn;
  dims[1] = cm;

  an = a->dimensions[0];
  am = a->dimensions[1];

  bn = b->dimensions[0];
  bm = b->dimensions[1];
  


  /* Make a new float complex vector of same dimension */
  c=(PyArrayObject *) PyArray_FromDims(2,dims,NPY_CFLOAT);
  
  if (not_floatcomplexmatrix(c)) return NULL;

  c_omulB(&cf, &k, &cm, &cn,&cm, &cn, (float complex *)c->data,
	&cf, &k, &am, &an,&am, &an, (float complex *)a->data,
	&cf, &k, &bm, &bn,&bm, &bn, (float complex *)b->data);

  return PyArray_Return(c);
}



/* ==== matrix multiply  =========================
    Returns a NumPy vector array
    interface:  c_oaddmulP(c,a,b)
                c,a,b are NumPy Python vector (float complex)
                returns a NumPy vector                                        */
static PyObject* c_oaddmulP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm;
  int k=0;
  int T=0;

  float complex cf=1.0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!O!", 
			&PyArray_Type, &c,&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'float complex' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_floatcomplexmatrix(c) || not_floatcomplexmatrix(a) || not_floatcomplexmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

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
  


  c_oaddmulB(&cf, &k, &cm, &cn,&cm, &cn, (float complex *)c->data,
	   &cf, &k, &am, &an,&am, &an, (float complex *)a->data,
	   &cf, &k, &bm, &bn,&bm, &bn, (float complex *)b->data);

  return PyArray_Return(c);
}


/* ==== matrix multiply  =========================
    Returns a NEW  NumPy vector array
    interface:  c_owmulP(a,b)
                a is NumPy vector, b is Python vector (float complex)
                returns a NumPy vector                                        */

static PyObject* c_owmulP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm,dims[2];
  int k=0;
  float complex cf=1.0;
  int T=0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!", 
			&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'float complex' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_floatcomplexmatrix(a) || not_floatcomplexmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

  cn=a->dimensions[0];
  cm=b->dimensions[1];
  dims[0] = cn;
  dims[1] = cm;

  an = a->dimensions[0];
  am = a->dimensions[1];

  bn = b->dimensions[0];
  bm = b->dimensions[1];
  


  /* Make a new float complex vector of same dimension */
  c=(PyArrayObject *) PyArray_FromDims(2,dims,NPY_CFLOAT);
  
  if (not_floatcomplexmatrix(c)) return NULL;

  c_owmulB(&cf, &k, &cm, &cn,&cm, &cn, (float complex *)c->data,
	&cf, &k, &am, &an,&am, &an, (float complex *)a->data,
	&cf, &k, &bm, &bn,&bm, &bn, (float complex *)b->data);

  return PyArray_Return(c);
}



/* ==== matrix multiply  =========================
    Returns a NumPy vector array
    interface:  c_owaddmulP(c,a,b)
                c,a,b are NumPy Python vector (float complex)
                returns a NumPy vector                                        */
static PyObject* c_owaddmulP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm;
  int k=0;
  int T=0;

  float complex cf=1.0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!O!", 
			&PyArray_Type, &c,&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'float complex' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_floatcomplexmatrix(c) || not_floatcomplexmatrix(a) || not_floatcomplexmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

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
  


  c_owaddmulB(&cf, &k, &cm, &cn,&cm, &cn, (float complex *)c->data,
	   &cf, &k, &am, &an,&am, &an, (float complex *)a->data,
	   &cf, &k, &bm, &bn,&bm, &bn, (float complex *)b->data);

  return PyArray_Return(c);
}


/* ==== matrix multiply  =========================
    Returns a NEW  NumPy vector array
    interface:  c_bmP(a,b)
                a is NumPy vector, b is Python vector (float complex)
                returns a NumPy vector                                        */

static PyObject* c_bmP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm,dims[2];
  int k=0;
  float complex cf=1.0;
  int T=0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!", 
			&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'float complex' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_floatcomplexmatrix(a) || not_floatcomplexmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

  cn=a->dimensions[0];
  cm=b->dimensions[1];
  dims[0] = cn;
  dims[1] = cm;

  an = a->dimensions[0];
  am = a->dimensions[1];

  bn = b->dimensions[0];
  bm = b->dimensions[1];
  


  /* Make a new float complex vector of same dimension */
  c=(PyArrayObject *) PyArray_FromDims(2,dims,NPY_CFLOAT);
  
  if (not_floatcomplexmatrix(c)) return NULL;

  c_bmB(&cf, &k, &cm, &cn,&cm, &cn, (float complex *)c->data,
	&cf, &k, &am, &an,&am, &an, (float complex *)a->data,
	&cf, &k, &bm, &bn,&bm, &bn, (float complex *)b->data);

  return PyArray_Return(c);
}



/* ==== matrix multiply  =========================
    Returns a NumPy vector array
    interface:  c_bmaddP(c,a,b)
                c,a,b are NumPy Python vector (float complex)
                returns a NumPy vector                                        */
static PyObject* c_bmaddP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm;
  int k=0;
  int T=0;

  float complex cf=1.0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!O!", 
			&PyArray_Type, &c,&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'float complex' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_floatcomplexmatrix(c) || not_floatcomplexmatrix(a) || not_floatcomplexmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

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
  


  c_bmaddB(&cf, &k, &cm, &cn,&cm, &cn, (float complex *)c->data,
	   &cf, &k, &am, &an,&am, &an, (float complex *)a->data,
	   &cf, &k, &bm, &bn,&bm, &bn, (float complex *)b->data);

  return PyArray_Return(c);
}


/* ==== matrix multiply  =========================
    Returns a NumPy vector array
    interface:  c_ptaddmulP(c,a,b)
                c,a,b are NumPy Python vector (float complex)
                returns a NumPy vector                                        */
static PyObject* c_ptaddmulP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm;
  int k=0;
  int T=0;

  float complex cf=1.0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!O!", 
			&PyArray_Type, &c,&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'float complex' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_floatcomplexmatrix(c) || not_floatcomplexmatrix(a) || not_floatcomplexmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

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
  


  c_ptaddmulB(&cf, &k, &cm, &cn,&cm, &cn, (float complex *)c->data,
	   &cf, &k, &am, &an,&am, &an, (float complex *)a->data,
	   &cf, &k, &bm, &bn,&bm, &bn, (float complex *)b->data);

  return PyArray_Return(c);
}


/* ==== matrix multiply  =========================
    Returns a NEW  NumPy vector array
    interface:  c_wmpipeP(a,b)
                a is NumPy vector, b is Python vector (float complex)
                returns a NumPy vector                                        */

static PyObject* c_wmpipeP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm,dims[2];
  int k=0;
  float complex cf=1.0;
  int T=0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!", 
			&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'float complex' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_floatcomplexmatrix(a) || not_floatcomplexmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

  cn=a->dimensions[0];
  cm=b->dimensions[1];
  dims[0] = cn;
  dims[1] = cm;

  an = a->dimensions[0];
  am = a->dimensions[1];

  bn = b->dimensions[0];
  bm = b->dimensions[1];
  


  /* Make a new float complex vector of same dimension */
  c=(PyArrayObject *) PyArray_FromDims(2,dims,NPY_CFLOAT);
  
  if (not_floatcomplexmatrix(c)) return NULL;

  c_wmpipeB(&cf, &k, &cm, &cn,&cm, &cn, (float complex *)c->data,
	&cf, &k, &am, &an,&am, &an, (float complex *)a->data,
	&cf, &k, &bm, &bn,&bm, &bn, (float complex *)b->data);

  return PyArray_Return(c);
}



/* ==== matrix multiply  =========================
    Returns a NumPy vector array
    interface:  c_wmaddpipeP(c,a,b)
                c,a,b are NumPy Python vector (float complex)
                returns a NumPy vector                                        */
static PyObject* c_wmaddpipeP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm;
  int k=0;
  int T=0;

  float complex cf=1.0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!O!", 
			&PyArray_Type, &c,&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'float complex' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_floatcomplexmatrix(c) || not_floatcomplexmatrix(a) || not_floatcomplexmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

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
  


  c_wmaddpipeB(&cf, &k, &cm, &cn,&cm, &cn, (float complex *)c->data,
	   &cf, &k, &am, &an,&am, &an, (float complex *)a->data,
	   &cf, &k, &bm, &bn,&bm, &bn, (float complex *)b->data);

  return PyArray_Return(c);
}


/* ==== matrix multiply  =========================
    Returns a NEW  NumPy vector array
    interface:  c_bmpipeP(a,b)
                a is NumPy vector, b is Python vector (float complex)
                returns a NumPy vector                                        */

static PyObject* c_bmpipeP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm,dims[2];
  int k=0;
  float complex cf=1.0;
  int T=0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!", 
			&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'float complex' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_floatcomplexmatrix(a) || not_floatcomplexmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

  cn=a->dimensions[0];
  cm=b->dimensions[1];
  dims[0] = cn;
  dims[1] = cm;

  an = a->dimensions[0];
  am = a->dimensions[1];

  bn = b->dimensions[0];
  bm = b->dimensions[1];
  


  /* Make a new float complex vector of same dimension */
  c=(PyArrayObject *) PyArray_FromDims(2,dims,NPY_CFLOAT);
  
  if (not_floatcomplexmatrix(c)) return NULL;

  c_bmpipeB(&cf, &k, &cm, &cn,&cm, &cn, (float complex *)c->data,
	&cf, &k, &am, &an,&am, &an, (float complex *)a->data,
	&cf, &k, &bm, &bn,&bm, &bn, (float complex *)b->data);

  return PyArray_Return(c);
}



/* ==== matrix multiply  =========================
    Returns a NumPy vector array
    interface:  c_bmaddpipeP(c,a,b)
                c,a,b are NumPy Python vector (float complex)
                returns a NumPy vector                                        */
static PyObject* c_bmaddpipeP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm;
  int k=0;
  int T=0;

  float complex cf=1.0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!O!", 
			&PyArray_Type, &c,&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'float complex' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_floatcomplexmatrix(c) || not_floatcomplexmatrix(a) || not_floatcomplexmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

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
  


  c_bmaddpipeB(&cf, &k, &cm, &cn,&cm, &cn, (float complex *)c->data,
	   &cf, &k, &am, &an,&am, &an, (float complex *)a->data,
	   &cf, &k, &bm, &bn,&bm, &bn, (float complex *)b->data);

  return PyArray_Return(c);
}


/* ==== matrix multiply  =========================
    Returns a NEW  NumPy vector array
    interface:  c_smpipeP(a,b)
                a is NumPy vector, b is Python vector (float complex)
                returns a NumPy vector                                        */

static PyObject* c_smpipeP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm,dims[2];
  int k=0;
  float complex cf=1.0;
  int T=0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!", 
			&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'float complex' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_floatcomplexmatrix(a) || not_floatcomplexmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

  cn=a->dimensions[0];
  cm=b->dimensions[1];
  dims[0] = cn;
  dims[1] = cm;

  an = a->dimensions[0];
  am = a->dimensions[1];

  bn = b->dimensions[0];
  bm = b->dimensions[1];
  


  /* Make a new float complex vector of same dimension */
  c=(PyArrayObject *) PyArray_FromDims(2,dims,NPY_CFLOAT);
  
  if (not_floatcomplexmatrix(c)) return NULL;

  c_smpipeB(&cf, &k, &cm, &cn,&cm, &cn, (float complex *)c->data,
	&cf, &k, &am, &an,&am, &an, (float complex *)a->data,
	&cf, &k, &bm, &bn,&bm, &bn, (float complex *)b->data);

  return PyArray_Return(c);
}



/* ==== matrix multiply  =========================
    Returns a NumPy vector array
    interface:  c_smaddpipeP(c,a,b)
                c,a,b are NumPy Python vector (float complex)
                returns a NumPy vector                                        */
static PyObject* c_smaddpipeP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm;
  int k=0;
  int T=0;

  float complex cf=1.0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!O!", 
			&PyArray_Type, &c,&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'float complex' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_floatcomplexmatrix(c) || not_floatcomplexmatrix(a) || not_floatcomplexmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

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
  


  c_smaddpipeB(&cf, &k, &cm, &cn,&cm, &cn, (float complex *)c->data,
	   &cf, &k, &am, &an,&am, &an, (float complex *)a->data,
	   &cf, &k, &bm, &bn,&bm, &bn, (float complex *)b->data);

  return PyArray_Return(c);
}


/* ==== matrix multiply  =========================
    Returns a NEW  NumPy vector array
    interface:  c_RmulP(a,b)
                a is NumPy vector, b is Python vector (float complex)
                returns a NumPy vector                                        */

static PyObject* c_RmulP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm,dims[2];
  int k=0;
  float complex cf=1.0;
  int T=0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!", 
			&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'float complex' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_floatcomplexmatrix(a) || not_floatcomplexmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

  cn=a->dimensions[0];
  cm=b->dimensions[1];
  dims[0] = cn;
  dims[1] = cm;

  an = a->dimensions[0];
  am = a->dimensions[1];

  bn = b->dimensions[0];
  bm = b->dimensions[1];
  


  /* Make a new float complex vector of same dimension */
  c=(PyArrayObject *) PyArray_FromDims(2,dims,NPY_CFLOAT);
  
  if (not_floatcomplexmatrix(c)) return NULL;

  c_RmulB(&cf, &k, &cm, &cn,&cm, &cn, (float complex *)c->data,
	&cf, &k, &am, &an,&am, &an, (float complex *)a->data,
	&cf, &k, &bm, &bn,&bm, &bn, (float complex *)b->data);

  return PyArray_Return(c);
}



/* ==== matrix multiply  =========================
    Returns a NEW  NumPy vector array
    interface:  c_adaptive_wmP(a,b)
                a is NumPy vector, b is Python vector (float complex)
                returns a NumPy vector                                        */

static PyObject* c_adaptive_wmP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm,dims[2];
  int k=0;
  float complex cf=1.0;
  int T=0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!d", 
			&PyArray_Type, &a,&PyArray_Type, &b,&T))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'float complex' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_floatcomplexmatrix(a) || not_floatcomplexmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

  cn=a->dimensions[0];
  cm=b->dimensions[1];
  dims[0] = cn;
  dims[1] = cm;

  an = a->dimensions[0];
  am = a->dimensions[1];

  bn = b->dimensions[0];
  bm = b->dimensions[1];
  


  /* Make a new float complex vector of same dimension */
  c=(PyArrayObject *) PyArray_FromDims(2,dims,NPY_CFLOAT);
  
  if (not_floatcomplexmatrix(c)) return NULL;

  c_adaptive_wmB(&cf, &k, &cm, &cn,&cm, &cn, (float complex *)c->data,
	&cf, &k, &am, &an,&am, &an, (float complex *)a->data,
	&cf, &k, &bm, &bn,&bm, &bn, (float complex *)b->data,&T);

  return PyArray_Return(c);
}



/* ==== matrix multiply  =========================
    Returns a NumPy vector array
    interface:  c_BMADD_PIPEP(c,a,b)
                c,a,b are NumPy Python vector (float complex)
                returns a NumPy vector                                        */
static PyObject* c_BMADD_PIPEP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm;
  int k=0;
  int T=0;

  float complex cf=1.0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!O!", 
			&PyArray_Type, &c,&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'float complex' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_floatcomplexmatrix(c) || not_floatcomplexmatrix(a) || not_floatcomplexmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

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
  


  c_BMADD_PIPEB(&cf, &k, &cm, &cn,&cm, &cn, (float complex *)c->data,
	   &cf, &k, &am, &an,&am, &an, (float complex *)a->data,
	   &cf, &k, &bm, &bn,&bm, &bn, (float complex *)b->data);

  return PyArray_Return(c);
}


/* ==== matrix multiply  =========================
    Returns a NumPy vector array
    interface:  c_BMADDP(c,a,b)
                c,a,b are NumPy Python vector (float complex)
                returns a NumPy vector                                        */
static PyObject* c_BMADDP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm;
  int k=0;
  int T=0;

  float complex cf=1.0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!O!", 
			&PyArray_Type, &c,&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'float complex' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_floatcomplexmatrix(c) || not_floatcomplexmatrix(a) || not_floatcomplexmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

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
  


  c_BMADDB(&cf, &k, &cm, &cn,&cm, &cn, (float complex *)c->data,
	   &cf, &k, &am, &an,&am, &an, (float complex *)a->data,
	   &cf, &k, &bm, &bn,&bm, &bn, (float complex *)b->data);

  return PyArray_Return(c);
}


/* ==== matrix multiply  =========================
    Returns a NumPy vector array
    interface:  c_BMADDRP(c,a,b)
                c,a,b are NumPy Python vector (float complex)
                returns a NumPy vector                                        */
static PyObject* c_BMADDRP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm;
  int k=0;
  int T=0;

  float complex cf=1.0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!O!", 
			&PyArray_Type, &c,&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'float complex' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_floatcomplexmatrix(c) || not_floatcomplexmatrix(a) || not_floatcomplexmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

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
  


  c_BMADDRB(&cf, &k, &cm, &cn,&cm, &cn, (float complex *)c->data,
	   &cf, &k, &am, &an,&am, &an, (float complex *)a->data,
	   &cf, &k, &bm, &bn,&bm, &bn, (float complex *)b->data);

  return PyArray_Return(c);
}


/* ==== matrix multiply  =========================
    Returns a NEW  NumPy vector array
    interface:  c_BMOWR_PIPEP(a,b)
                a is NumPy vector, b is Python vector (float complex)
                returns a NumPy vector                                        */

static PyObject* c_BMOWR_PIPEP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm,dims[2];
  int k=0;
  float complex cf=1.0;
  int T=0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!", 
			&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'float complex' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_floatcomplexmatrix(a) || not_floatcomplexmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

  cn=a->dimensions[0];
  cm=b->dimensions[1];
  dims[0] = cn;
  dims[1] = cm;

  an = a->dimensions[0];
  am = a->dimensions[1];

  bn = b->dimensions[0];
  bm = b->dimensions[1];
  


  /* Make a new float complex vector of same dimension */
  c=(PyArrayObject *) PyArray_FromDims(2,dims,NPY_CFLOAT);
  
  if (not_floatcomplexmatrix(c)) return NULL;

  c_BMOWR_PIPEB(&cf, &k, &cm, &cn,&cm, &cn, (float complex *)c->data,
	&cf, &k, &am, &an,&am, &an, (float complex *)a->data,
	&cf, &k, &bm, &bn,&bm, &bn, (float complex *)b->data);

  return PyArray_Return(c);
}



/* ==== matrix multiply  =========================
    Returns a NEW  NumPy vector array
    interface:  c_BMOWRP(a,b)
                a is NumPy vector, b is Python vector (float complex)
                returns a NumPy vector                                        */

static PyObject* c_BMOWRP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm,dims[2];
  int k=0;
  float complex cf=1.0;
  int T=0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!", 
			&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'float complex' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_floatcomplexmatrix(a) || not_floatcomplexmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

  cn=a->dimensions[0];
  cm=b->dimensions[1];
  dims[0] = cn;
  dims[1] = cm;

  an = a->dimensions[0];
  am = a->dimensions[1];

  bn = b->dimensions[0];
  bm = b->dimensions[1];
  


  /* Make a new float complex vector of same dimension */
  c=(PyArrayObject *) PyArray_FromDims(2,dims,NPY_CFLOAT);
  
  if (not_floatcomplexmatrix(c)) return NULL;

  c_BMOWRB(&cf, &k, &cm, &cn,&cm, &cn, (float complex *)c->data,
	&cf, &k, &am, &an,&am, &an, (float complex *)a->data,
	&cf, &k, &bm, &bn,&bm, &bn, (float complex *)b->data);

  return PyArray_Return(c);
}



/* ==== matrix multiply  =========================
    Returns a NEW  NumPy vector array
    interface:  c_BMOWRRP(a,b)
                a is NumPy vector, b is Python vector (float complex)
                returns a NumPy vector                                        */

static PyObject* c_BMOWRRP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm,dims[2];
  int k=0;
  float complex cf=1.0;
  int T=0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!", 
			&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'float complex' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_floatcomplexmatrix(a) || not_floatcomplexmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

  cn=a->dimensions[0];
  cm=b->dimensions[1];
  dims[0] = cn;
  dims[1] = cm;

  an = a->dimensions[0];
  am = a->dimensions[1];

  bn = b->dimensions[0];
  bm = b->dimensions[1];
  


  /* Make a new float complex vector of same dimension */
  c=(PyArrayObject *) PyArray_FromDims(2,dims,NPY_CFLOAT);
  
  if (not_floatcomplexmatrix(c)) return NULL;

  c_BMOWRRB(&cf, &k, &cm, &cn,&cm, &cn, (float complex *)c->data,
	&cf, &k, &am, &an,&am, &an, (float complex *)a->data,
	&cf, &k, &bm, &bn,&bm, &bn, (float complex *)b->data);

  return PyArray_Return(c);
}



/* ==== matrix multiply  =========================
    Returns a NEW  NumPy vector array
    interface:  z_dcmulP(a,b)
                a is NumPy vector, b is Python vector (double complex)
                returns a NumPy vector                                        */

static PyObject* z_dcmulP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm,dims[2];
  int k=0;
  double complex cf=1.0;
  int T=0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!", 
			&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'double complex' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_doublecomplexmatrix(a) || not_doublecomplexmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

  cn=a->dimensions[0];
  cm=b->dimensions[1];
  dims[0] = cn;
  dims[1] = cm;

  an = a->dimensions[0];
  am = a->dimensions[1];

  bn = b->dimensions[0];
  bm = b->dimensions[1];
  


  /* Make a new double complex vector of same dimension */
  c=(PyArrayObject *) PyArray_FromDims(2,dims,NPY_CDOUBLE);
  
  if (not_doublecomplexmatrix(c)) return NULL;

  z_dcmulB(&cf, &k, &cm, &cn,&cm, &cn, (double complex *)c->data,
	&cf, &k, &am, &an,&am, &an, (double complex *)a->data,
	&cf, &k, &bm, &bn,&bm, &bn, (double complex *)b->data);

  return PyArray_Return(c);
}



/* ==== matrix multiply  =========================
    Returns a NEW  NumPy vector array
    interface:  z_mulP(a,b)
                a is NumPy vector, b is Python vector (double complex)
                returns a NumPy vector                                        */

static PyObject* z_mulP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm,dims[2];
  int k=0;
  double complex cf=1.0;
  int T=0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!", 
			&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'double complex' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_doublecomplexmatrix(a) || not_doublecomplexmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

  cn=a->dimensions[0];
  cm=b->dimensions[1];
  dims[0] = cn;
  dims[1] = cm;

  an = a->dimensions[0];
  am = a->dimensions[1];

  bn = b->dimensions[0];
  bm = b->dimensions[1];
  


  /* Make a new double complex vector of same dimension */
  c=(PyArrayObject *) PyArray_FromDims(2,dims,NPY_CDOUBLE);
  
  if (not_doublecomplexmatrix(c)) return NULL;

  z_mulB(&cf, &k, &cm, &cn,&cm, &cn, (double complex *)c->data,
	&cf, &k, &am, &an,&am, &an, (double complex *)a->data,
	&cf, &k, &bm, &bn,&bm, &bn, (double complex *)b->data);

  return PyArray_Return(c);
}



/* ==== matrix multiply  =========================
    Returns a NEW  NumPy vector array
    interface:  z_mulptP(a,b)
                a is NumPy vector, b is Python vector (double complex)
                returns a NumPy vector                                        */

static PyObject* z_mulptP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm,dims[2];
  int k=0;
  double complex cf=1.0;
  int T=0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!", 
			&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'double complex' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_doublecomplexmatrix(a) || not_doublecomplexmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

  cn=a->dimensions[0];
  cm=b->dimensions[1];
  dims[0] = cn;
  dims[1] = cm;

  an = a->dimensions[0];
  am = a->dimensions[1];

  bn = b->dimensions[0];
  bm = b->dimensions[1];
  


  /* Make a new double complex vector of same dimension */
  c=(PyArrayObject *) PyArray_FromDims(2,dims,NPY_CDOUBLE);
  
  if (not_doublecomplexmatrix(c)) return NULL;

  z_mulptB(&cf, &k, &cm, &cn,&cm, &cn, (double complex *)c->data,
	&cf, &k, &am, &an,&am, &an, (double complex *)a->data,
	&cf, &k, &bm, &bn,&bm, &bn, (double complex *)b->data);

  return PyArray_Return(c);
}



/* ==== matrix multiply  =========================
    Returns a NumPy vector array
    interface:  z_maddP(c,a,b)
                c,a,b are NumPy Python vector (double complex)
                returns a NumPy vector                                        */
static PyObject* z_maddP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm;
  int k=0;
  int T=0;

  double complex cf=1.0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!O!", 
			&PyArray_Type, &c,&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'double complex' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_doublecomplexmatrix(c) || not_doublecomplexmatrix(a) || not_doublecomplexmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

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
  


  z_maddB(&cf, &k, &cm, &cn,&cm, &cn, (double complex *)c->data,
	   &cf, &k, &am, &an,&am, &an, (double complex *)a->data,
	   &cf, &k, &bm, &bn,&bm, &bn, (double complex *)b->data);

  return PyArray_Return(c);
}


/* ==== matrix multiply  =========================
    Returns a NumPy vector array
    interface:  z_saddmulP(c,a,b)
                c,a,b are NumPy Python vector (double complex)
                returns a NumPy vector                                        */
static PyObject* z_saddmulP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm;
  int k=0;
  int T=0;

  double complex cf=1.0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!O!", 
			&PyArray_Type, &c,&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'double complex' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_doublecomplexmatrix(c) || not_doublecomplexmatrix(a) || not_doublecomplexmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

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
  


  z_saddmulB(&cf, &k, &cm, &cn,&cm, &cn, (double complex *)c->data,
	   &cf, &k, &am, &an,&am, &an, (double complex *)a->data,
	   &cf, &k, &bm, &bn,&bm, &bn, (double complex *)b->data);

  return PyArray_Return(c);
}


/* ==== matrix multiply  =========================
    Returns a NEW  NumPy vector array
    interface:  z_smulP(a,b)
                a is NumPy vector, b is Python vector (double complex)
                returns a NumPy vector                                        */

static PyObject* z_smulP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm,dims[2];
  int k=0;
  double complex cf=1.0;
  int T=0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!", 
			&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'double complex' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_doublecomplexmatrix(a) || not_doublecomplexmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

  cn=a->dimensions[0];
  cm=b->dimensions[1];
  dims[0] = cn;
  dims[1] = cm;

  an = a->dimensions[0];
  am = a->dimensions[1];

  bn = b->dimensions[0];
  bm = b->dimensions[1];
  


  /* Make a new double complex vector of same dimension */
  c=(PyArrayObject *) PyArray_FromDims(2,dims,NPY_CDOUBLE);
  
  if (not_doublecomplexmatrix(c)) return NULL;

  z_smulB(&cf, &k, &cm, &cn,&cm, &cn, (double complex *)c->data,
	&cf, &k, &am, &an,&am, &an, (double complex *)a->data,
	&cf, &k, &bm, &bn,&bm, &bn, (double complex *)b->data);

  return PyArray_Return(c);
}



/* ==== matrix multiply  =========================
    Returns a NumPy vector array
    interface:  z_saddmulRP(c,a,b)
                c,a,b are NumPy Python vector (double complex)
                returns a NumPy vector                                        */
static PyObject* z_saddmulRP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm;
  int k=0;
  int T=0;

  double complex cf=1.0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!O!", 
			&PyArray_Type, &c,&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'double complex' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_doublecomplexmatrix(c) || not_doublecomplexmatrix(a) || not_doublecomplexmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

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
  


  z_saddmulRB(&cf, &k, &cm, &cn,&cm, &cn, (double complex *)c->data,
	   &cf, &k, &am, &an,&am, &an, (double complex *)a->data,
	   &cf, &k, &bm, &bn,&bm, &bn, (double complex *)b->data);

  return PyArray_Return(c);
}


/* ==== matrix multiply  =========================
    Returns a NEW  NumPy vector array
    interface:  z_smulRP(a,b)
                a is NumPy vector, b is Python vector (double complex)
                returns a NumPy vector                                        */

static PyObject* z_smulRP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm,dims[2];
  int k=0;
  double complex cf=1.0;
  int T=0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!", 
			&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'double complex' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_doublecomplexmatrix(a) || not_doublecomplexmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

  cn=a->dimensions[0];
  cm=b->dimensions[1];
  dims[0] = cn;
  dims[1] = cm;

  an = a->dimensions[0];
  am = a->dimensions[1];

  bn = b->dimensions[0];
  bm = b->dimensions[1];
  


  /* Make a new double complex vector of same dimension */
  c=(PyArrayObject *) PyArray_FromDims(2,dims,NPY_CDOUBLE);
  
  if (not_doublecomplexmatrix(c)) return NULL;

  z_smulRB(&cf, &k, &cm, &cn,&cm, &cn, (double complex *)c->data,
	&cf, &k, &am, &an,&am, &an, (double complex *)a->data,
	&cf, &k, &bm, &bn,&bm, &bn, (double complex *)b->data);

  return PyArray_Return(c);
}



/* ==== matrix multiply  =========================
    Returns a NEW  NumPy vector array
    interface:  z_wmulP(a,b)
                a is NumPy vector, b is Python vector (double complex)
                returns a NumPy vector                                        */

static PyObject* z_wmulP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm,dims[2];
  int k=0;
  double complex cf=1.0;
  int T=0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!", 
			&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'double complex' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_doublecomplexmatrix(a) || not_doublecomplexmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

  cn=a->dimensions[0];
  cm=b->dimensions[1];
  dims[0] = cn;
  dims[1] = cm;

  an = a->dimensions[0];
  am = a->dimensions[1];

  bn = b->dimensions[0];
  bm = b->dimensions[1];
  


  /* Make a new double complex vector of same dimension */
  c=(PyArrayObject *) PyArray_FromDims(2,dims,NPY_CDOUBLE);
  
  if (not_doublecomplexmatrix(c)) return NULL;

  z_wmulB(&cf, &k, &cm, &cn,&cm, &cn, (double complex *)c->data,
	&cf, &k, &am, &an,&am, &an, (double complex *)a->data,
	&cf, &k, &bm, &bn,&bm, &bn, (double complex *)b->data);

  return PyArray_Return(c);
}



/* ==== matrix multiply  =========================
    Returns a NumPy vector array
    interface:  z_waddmulP(c,a,b)
                c,a,b are NumPy Python vector (double complex)
                returns a NumPy vector                                        */
static PyObject* z_waddmulP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm;
  int k=0;
  int T=0;

  double complex cf=1.0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!O!", 
			&PyArray_Type, &c,&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'double complex' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_doublecomplexmatrix(c) || not_doublecomplexmatrix(a) || not_doublecomplexmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

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
  


  z_waddmulB(&cf, &k, &cm, &cn,&cm, &cn, (double complex *)c->data,
	   &cf, &k, &am, &an,&am, &an, (double complex *)a->data,
	   &cf, &k, &bm, &bn,&bm, &bn, (double complex *)b->data);

  return PyArray_Return(c);
}


/* ==== matrix multiply  =========================
    Returns a NEW  NumPy vector array
    interface:  z_wmP(a,b)
                a is NumPy vector, b is Python vector (double complex)
                returns a NumPy vector                                        */

static PyObject* z_wmP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm,dims[2];
  int k=0;
  double complex cf=1.0;
  int T=0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!", 
			&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'double complex' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_doublecomplexmatrix(a) || not_doublecomplexmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

  cn=a->dimensions[0];
  cm=b->dimensions[1];
  dims[0] = cn;
  dims[1] = cm;

  an = a->dimensions[0];
  am = a->dimensions[1];

  bn = b->dimensions[0];
  bm = b->dimensions[1];
  


  /* Make a new double complex vector of same dimension */
  c=(PyArrayObject *) PyArray_FromDims(2,dims,NPY_CDOUBLE);
  
  if (not_doublecomplexmatrix(c)) return NULL;

  z_wmB(&cf, &k, &cm, &cn,&cm, &cn, (double complex *)c->data,
	&cf, &k, &am, &an,&am, &an, (double complex *)a->data,
	&cf, &k, &bm, &bn,&bm, &bn, (double complex *)b->data);

  return PyArray_Return(c);
}



/* ==== matrix multiply  =========================
    Returns a NumPy vector array
    interface:  z_wmaddP(c,a,b)
                c,a,b are NumPy Python vector (double complex)
                returns a NumPy vector                                        */
static PyObject* z_wmaddP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm;
  int k=0;
  int T=0;

  double complex cf=1.0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!O!", 
			&PyArray_Type, &c,&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'double complex' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_doublecomplexmatrix(c) || not_doublecomplexmatrix(a) || not_doublecomplexmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

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
  


  z_wmaddB(&cf, &k, &cm, &cn,&cm, &cn, (double complex *)c->data,
	   &cf, &k, &am, &an,&am, &an, (double complex *)a->data,
	   &cf, &k, &bm, &bn,&bm, &bn, (double complex *)b->data);

  return PyArray_Return(c);
}


/* ==== matrix multiply  =========================
    Returns a NEW  NumPy vector array
    interface:  z_wmRP(a,b)
                a is NumPy vector, b is Python vector (double complex)
                returns a NumPy vector                                        */

static PyObject* z_wmRP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm,dims[2];
  int k=0;
  double complex cf=1.0;
  int T=0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!", 
			&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'double complex' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_doublecomplexmatrix(a) || not_doublecomplexmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

  cn=a->dimensions[0];
  cm=b->dimensions[1];
  dims[0] = cn;
  dims[1] = cm;

  an = a->dimensions[0];
  am = a->dimensions[1];

  bn = b->dimensions[0];
  bm = b->dimensions[1];
  


  /* Make a new double complex vector of same dimension */
  c=(PyArrayObject *) PyArray_FromDims(2,dims,NPY_CDOUBLE);
  
  if (not_doublecomplexmatrix(c)) return NULL;

  z_wmRB(&cf, &k, &cm, &cn,&cm, &cn, (double complex *)c->data,
	&cf, &k, &am, &an,&am, &an, (double complex *)a->data,
	&cf, &k, &bm, &bn,&bm, &bn, (double complex *)b->data);

  return PyArray_Return(c);
}



/* ==== matrix multiply  =========================
    Returns a NumPy vector array
    interface:  z_wmaddRP(c,a,b)
                c,a,b are NumPy Python vector (double complex)
                returns a NumPy vector                                        */
static PyObject* z_wmaddRP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm;
  int k=0;
  int T=0;

  double complex cf=1.0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!O!", 
			&PyArray_Type, &c,&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'double complex' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_doublecomplexmatrix(c) || not_doublecomplexmatrix(a) || not_doublecomplexmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

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
  


  z_wmaddRB(&cf, &k, &cm, &cn,&cm, &cn, (double complex *)c->data,
	   &cf, &k, &am, &an,&am, &an, (double complex *)a->data,
	   &cf, &k, &bm, &bn,&bm, &bn, (double complex *)b->data);

  return PyArray_Return(c);
}


/* ==== matrix multiply  =========================
    Returns a NEW  NumPy vector array
    interface:  z_wmTRP(a,b)
                a is NumPy vector, b is Python vector (double complex)
                returns a NumPy vector                                        */

static PyObject* z_wmTRP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm,dims[2];
  int k=0;
  double complex cf=1.0;
  int T=0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!", 
			&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'double complex' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_doublecomplexmatrix(a) || not_doublecomplexmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

  cn=a->dimensions[0];
  cm=b->dimensions[1];
  dims[0] = cn;
  dims[1] = cm;

  an = a->dimensions[0];
  am = a->dimensions[1];

  bn = b->dimensions[0];
  bm = b->dimensions[1];
  


  /* Make a new double complex vector of same dimension */
  c=(PyArrayObject *) PyArray_FromDims(2,dims,NPY_CDOUBLE);
  
  if (not_doublecomplexmatrix(c)) return NULL;

  z_wmTRB(&cf, &k, &cm, &cn,&cm, &cn, (double complex *)c->data,
	&cf, &k, &am, &an,&am, &an, (double complex *)a->data,
	&cf, &k, &bm, &bn,&bm, &bn, (double complex *)b->data);

  return PyArray_Return(c);
}



/* ==== matrix multiply  =========================
    Returns a NumPy vector array
    interface:  z_wmaddTRP(c,a,b)
                c,a,b are NumPy Python vector (double complex)
                returns a NumPy vector                                        */
static PyObject* z_wmaddTRP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm;
  int k=0;
  int T=0;

  double complex cf=1.0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!O!", 
			&PyArray_Type, &c,&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'double complex' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_doublecomplexmatrix(c) || not_doublecomplexmatrix(a) || not_doublecomplexmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

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
  


  z_wmaddTRB(&cf, &k, &cm, &cn,&cm, &cn, (double complex *)c->data,
	   &cf, &k, &am, &an,&am, &an, (double complex *)a->data,
	   &cf, &k, &bm, &bn,&bm, &bn, (double complex *)b->data);

  return PyArray_Return(c);
}


/* ==== matrix multiply  =========================
    Returns a NEW  NumPy vector array
    interface:  z_adaptive_smulP(a,b)
                a is NumPy vector, b is Python vector (double complex)
                returns a NumPy vector                                        */

static PyObject* z_adaptive_smulP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm,dims[2];
  int k=0;
  double complex cf=1.0;
  int T=0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!d", 
			&PyArray_Type, &a,&PyArray_Type, &b,&T))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'double complex' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_doublecomplexmatrix(a) || not_doublecomplexmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

  cn=a->dimensions[0];
  cm=b->dimensions[1];
  dims[0] = cn;
  dims[1] = cm;

  an = a->dimensions[0];
  am = a->dimensions[1];

  bn = b->dimensions[0];
  bm = b->dimensions[1];
  


  /* Make a new double complex vector of same dimension */
  c=(PyArrayObject *) PyArray_FromDims(2,dims,NPY_CDOUBLE);
  
  if (not_doublecomplexmatrix(c)) return NULL;

  z_adaptive_smulB(&cf, &k, &cm, &cn,&cm, &cn, (double complex *)c->data,
	&cf, &k, &am, &an,&am, &an, (double complex *)a->data,
	&cf, &k, &bm, &bn,&bm, &bn, (double complex *)b->data,&T);

  return PyArray_Return(c);
}



/* ==== matrix multiply  =========================
    Returns a NEW  NumPy vector array
    interface:  z_omulP(a,b)
                a is NumPy vector, b is Python vector (double complex)
                returns a NumPy vector                                        */

static PyObject* z_omulP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm,dims[2];
  int k=0;
  double complex cf=1.0;
  int T=0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!", 
			&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'double complex' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_doublecomplexmatrix(a) || not_doublecomplexmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

  cn=a->dimensions[0];
  cm=b->dimensions[1];
  dims[0] = cn;
  dims[1] = cm;

  an = a->dimensions[0];
  am = a->dimensions[1];

  bn = b->dimensions[0];
  bm = b->dimensions[1];
  


  /* Make a new double complex vector of same dimension */
  c=(PyArrayObject *) PyArray_FromDims(2,dims,NPY_CDOUBLE);
  
  if (not_doublecomplexmatrix(c)) return NULL;

  z_omulB(&cf, &k, &cm, &cn,&cm, &cn, (double complex *)c->data,
	&cf, &k, &am, &an,&am, &an, (double complex *)a->data,
	&cf, &k, &bm, &bn,&bm, &bn, (double complex *)b->data);

  return PyArray_Return(c);
}



/* ==== matrix multiply  =========================
    Returns a NumPy vector array
    interface:  z_oaddmulP(c,a,b)
                c,a,b are NumPy Python vector (double complex)
                returns a NumPy vector                                        */
static PyObject* z_oaddmulP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm;
  int k=0;
  int T=0;

  double complex cf=1.0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!O!", 
			&PyArray_Type, &c,&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'double complex' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_doublecomplexmatrix(c) || not_doublecomplexmatrix(a) || not_doublecomplexmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

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
  


  z_oaddmulB(&cf, &k, &cm, &cn,&cm, &cn, (double complex *)c->data,
	   &cf, &k, &am, &an,&am, &an, (double complex *)a->data,
	   &cf, &k, &bm, &bn,&bm, &bn, (double complex *)b->data);

  return PyArray_Return(c);
}


/* ==== matrix multiply  =========================
    Returns a NEW  NumPy vector array
    interface:  z_owmulP(a,b)
                a is NumPy vector, b is Python vector (double complex)
                returns a NumPy vector                                        */

static PyObject* z_owmulP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm,dims[2];
  int k=0;
  double complex cf=1.0;
  int T=0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!", 
			&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'double complex' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_doublecomplexmatrix(a) || not_doublecomplexmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

  cn=a->dimensions[0];
  cm=b->dimensions[1];
  dims[0] = cn;
  dims[1] = cm;

  an = a->dimensions[0];
  am = a->dimensions[1];

  bn = b->dimensions[0];
  bm = b->dimensions[1];
  


  /* Make a new double complex vector of same dimension */
  c=(PyArrayObject *) PyArray_FromDims(2,dims,NPY_CDOUBLE);
  
  if (not_doublecomplexmatrix(c)) return NULL;

  z_owmulB(&cf, &k, &cm, &cn,&cm, &cn, (double complex *)c->data,
	&cf, &k, &am, &an,&am, &an, (double complex *)a->data,
	&cf, &k, &bm, &bn,&bm, &bn, (double complex *)b->data);

  return PyArray_Return(c);
}



/* ==== matrix multiply  =========================
    Returns a NumPy vector array
    interface:  z_owaddmulP(c,a,b)
                c,a,b are NumPy Python vector (double complex)
                returns a NumPy vector                                        */
static PyObject* z_owaddmulP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm;
  int k=0;
  int T=0;

  double complex cf=1.0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!O!", 
			&PyArray_Type, &c,&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'double complex' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_doublecomplexmatrix(c) || not_doublecomplexmatrix(a) || not_doublecomplexmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

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
  


  z_owaddmulB(&cf, &k, &cm, &cn,&cm, &cn, (double complex *)c->data,
	   &cf, &k, &am, &an,&am, &an, (double complex *)a->data,
	   &cf, &k, &bm, &bn,&bm, &bn, (double complex *)b->data);

  return PyArray_Return(c);
}


/* ==== matrix multiply  =========================
    Returns a NEW  NumPy vector array
    interface:  z_bmP(a,b)
                a is NumPy vector, b is Python vector (double complex)
                returns a NumPy vector                                        */

static PyObject* z_bmP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm,dims[2];
  int k=0;
  double complex cf=1.0;
  int T=0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!", 
			&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'double complex' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_doublecomplexmatrix(a) || not_doublecomplexmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

  cn=a->dimensions[0];
  cm=b->dimensions[1];
  dims[0] = cn;
  dims[1] = cm;

  an = a->dimensions[0];
  am = a->dimensions[1];

  bn = b->dimensions[0];
  bm = b->dimensions[1];
  


  /* Make a new double complex vector of same dimension */
  c=(PyArrayObject *) PyArray_FromDims(2,dims,NPY_CDOUBLE);
  
  if (not_doublecomplexmatrix(c)) return NULL;

  z_bmB(&cf, &k, &cm, &cn,&cm, &cn, (double complex *)c->data,
	&cf, &k, &am, &an,&am, &an, (double complex *)a->data,
	&cf, &k, &bm, &bn,&bm, &bn, (double complex *)b->data);

  return PyArray_Return(c);
}



/* ==== matrix multiply  =========================
    Returns a NumPy vector array
    interface:  z_bmaddP(c,a,b)
                c,a,b are NumPy Python vector (double complex)
                returns a NumPy vector                                        */
static PyObject* z_bmaddP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm;
  int k=0;
  int T=0;

  double complex cf=1.0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!O!", 
			&PyArray_Type, &c,&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'double complex' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_doublecomplexmatrix(c) || not_doublecomplexmatrix(a) || not_doublecomplexmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

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
  


  z_bmaddB(&cf, &k, &cm, &cn,&cm, &cn, (double complex *)c->data,
	   &cf, &k, &am, &an,&am, &an, (double complex *)a->data,
	   &cf, &k, &bm, &bn,&bm, &bn, (double complex *)b->data);

  return PyArray_Return(c);
}


/* ==== matrix multiply  =========================
    Returns a NumPy vector array
    interface:  z_ptaddmulP(c,a,b)
                c,a,b are NumPy Python vector (double complex)
                returns a NumPy vector                                        */
static PyObject* z_ptaddmulP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm;
  int k=0;
  int T=0;

  double complex cf=1.0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!O!", 
			&PyArray_Type, &c,&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'double complex' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_doublecomplexmatrix(c) || not_doublecomplexmatrix(a) || not_doublecomplexmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

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
  


  z_ptaddmulB(&cf, &k, &cm, &cn,&cm, &cn, (double complex *)c->data,
	   &cf, &k, &am, &an,&am, &an, (double complex *)a->data,
	   &cf, &k, &bm, &bn,&bm, &bn, (double complex *)b->data);

  return PyArray_Return(c);
}


/* ==== matrix multiply  =========================
    Returns a NEW  NumPy vector array
    interface:  z_wmpipeP(a,b)
                a is NumPy vector, b is Python vector (double complex)
                returns a NumPy vector                                        */

static PyObject* z_wmpipeP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm,dims[2];
  int k=0;
  double complex cf=1.0;
  int T=0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!", 
			&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'double complex' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_doublecomplexmatrix(a) || not_doublecomplexmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

  cn=a->dimensions[0];
  cm=b->dimensions[1];
  dims[0] = cn;
  dims[1] = cm;

  an = a->dimensions[0];
  am = a->dimensions[1];

  bn = b->dimensions[0];
  bm = b->dimensions[1];
  


  /* Make a new double complex vector of same dimension */
  c=(PyArrayObject *) PyArray_FromDims(2,dims,NPY_CDOUBLE);
  
  if (not_doublecomplexmatrix(c)) return NULL;

  z_wmpipeB(&cf, &k, &cm, &cn,&cm, &cn, (double complex *)c->data,
	&cf, &k, &am, &an,&am, &an, (double complex *)a->data,
	&cf, &k, &bm, &bn,&bm, &bn, (double complex *)b->data);

  return PyArray_Return(c);
}



/* ==== matrix multiply  =========================
    Returns a NumPy vector array
    interface:  z_wmaddpipeP(c,a,b)
                c,a,b are NumPy Python vector (double complex)
                returns a NumPy vector                                        */
static PyObject* z_wmaddpipeP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm;
  int k=0;
  int T=0;

  double complex cf=1.0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!O!", 
			&PyArray_Type, &c,&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'double complex' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_doublecomplexmatrix(c) || not_doublecomplexmatrix(a) || not_doublecomplexmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

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
  


  z_wmaddpipeB(&cf, &k, &cm, &cn,&cm, &cn, (double complex *)c->data,
	   &cf, &k, &am, &an,&am, &an, (double complex *)a->data,
	   &cf, &k, &bm, &bn,&bm, &bn, (double complex *)b->data);

  return PyArray_Return(c);
}


/* ==== matrix multiply  =========================
    Returns a NEW  NumPy vector array
    interface:  z_bmpipeP(a,b)
                a is NumPy vector, b is Python vector (double complex)
                returns a NumPy vector                                        */

static PyObject* z_bmpipeP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm,dims[2];
  int k=0;
  double complex cf=1.0;
  int T=0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!", 
			&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'double complex' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_doublecomplexmatrix(a) || not_doublecomplexmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

  cn=a->dimensions[0];
  cm=b->dimensions[1];
  dims[0] = cn;
  dims[1] = cm;

  an = a->dimensions[0];
  am = a->dimensions[1];

  bn = b->dimensions[0];
  bm = b->dimensions[1];
  


  /* Make a new double complex vector of same dimension */
  c=(PyArrayObject *) PyArray_FromDims(2,dims,NPY_CDOUBLE);
  
  if (not_doublecomplexmatrix(c)) return NULL;

  z_bmpipeB(&cf, &k, &cm, &cn,&cm, &cn, (double complex *)c->data,
	&cf, &k, &am, &an,&am, &an, (double complex *)a->data,
	&cf, &k, &bm, &bn,&bm, &bn, (double complex *)b->data);

  return PyArray_Return(c);
}



/* ==== matrix multiply  =========================
    Returns a NumPy vector array
    interface:  z_bmaddpipeP(c,a,b)
                c,a,b are NumPy Python vector (double complex)
                returns a NumPy vector                                        */
static PyObject* z_bmaddpipeP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm;
  int k=0;
  int T=0;

  double complex cf=1.0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!O!", 
			&PyArray_Type, &c,&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'double complex' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_doublecomplexmatrix(c) || not_doublecomplexmatrix(a) || not_doublecomplexmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

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
  


  z_bmaddpipeB(&cf, &k, &cm, &cn,&cm, &cn, (double complex *)c->data,
	   &cf, &k, &am, &an,&am, &an, (double complex *)a->data,
	   &cf, &k, &bm, &bn,&bm, &bn, (double complex *)b->data);

  return PyArray_Return(c);
}


/* ==== matrix multiply  =========================
    Returns a NEW  NumPy vector array
    interface:  z_smpipeP(a,b)
                a is NumPy vector, b is Python vector (double complex)
                returns a NumPy vector                                        */

static PyObject* z_smpipeP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm,dims[2];
  int k=0;
  double complex cf=1.0;
  int T=0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!", 
			&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'double complex' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_doublecomplexmatrix(a) || not_doublecomplexmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

  cn=a->dimensions[0];
  cm=b->dimensions[1];
  dims[0] = cn;
  dims[1] = cm;

  an = a->dimensions[0];
  am = a->dimensions[1];

  bn = b->dimensions[0];
  bm = b->dimensions[1];
  


  /* Make a new double complex vector of same dimension */
  c=(PyArrayObject *) PyArray_FromDims(2,dims,NPY_CDOUBLE);
  
  if (not_doublecomplexmatrix(c)) return NULL;

  z_smpipeB(&cf, &k, &cm, &cn,&cm, &cn, (double complex *)c->data,
	&cf, &k, &am, &an,&am, &an, (double complex *)a->data,
	&cf, &k, &bm, &bn,&bm, &bn, (double complex *)b->data);

  return PyArray_Return(c);
}



/* ==== matrix multiply  =========================
    Returns a NumPy vector array
    interface:  z_smaddpipeP(c,a,b)
                c,a,b are NumPy Python vector (double complex)
                returns a NumPy vector                                        */
static PyObject* z_smaddpipeP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm;
  int k=0;
  int T=0;

  double complex cf=1.0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!O!", 
			&PyArray_Type, &c,&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'double complex' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_doublecomplexmatrix(c) || not_doublecomplexmatrix(a) || not_doublecomplexmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

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
  


  z_smaddpipeB(&cf, &k, &cm, &cn,&cm, &cn, (double complex *)c->data,
	   &cf, &k, &am, &an,&am, &an, (double complex *)a->data,
	   &cf, &k, &bm, &bn,&bm, &bn, (double complex *)b->data);

  return PyArray_Return(c);
}


/* ==== matrix multiply  =========================
    Returns a NEW  NumPy vector array
    interface:  z_RmulP(a,b)
                a is NumPy vector, b is Python vector (double complex)
                returns a NumPy vector                                        */

static PyObject* z_RmulP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm,dims[2];
  int k=0;
  double complex cf=1.0;
  int T=0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!", 
			&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'double complex' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_doublecomplexmatrix(a) || not_doublecomplexmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

  cn=a->dimensions[0];
  cm=b->dimensions[1];
  dims[0] = cn;
  dims[1] = cm;

  an = a->dimensions[0];
  am = a->dimensions[1];

  bn = b->dimensions[0];
  bm = b->dimensions[1];
  


  /* Make a new double complex vector of same dimension */
  c=(PyArrayObject *) PyArray_FromDims(2,dims,NPY_CDOUBLE);
  
  if (not_doublecomplexmatrix(c)) return NULL;

  z_RmulB(&cf, &k, &cm, &cn,&cm, &cn, (double complex *)c->data,
	&cf, &k, &am, &an,&am, &an, (double complex *)a->data,
	&cf, &k, &bm, &bn,&bm, &bn, (double complex *)b->data);

  return PyArray_Return(c);
}



/* ==== matrix multiply  =========================
    Returns a NEW  NumPy vector array
    interface:  z_adaptive_wmP(a,b)
                a is NumPy vector, b is Python vector (double complex)
                returns a NumPy vector                                        */

static PyObject* z_adaptive_wmP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm,dims[2];
  int k=0;
  double complex cf=1.0;
  int T=0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!d", 
			&PyArray_Type, &a,&PyArray_Type, &b,&T))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'double complex' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_doublecomplexmatrix(a) || not_doublecomplexmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

  cn=a->dimensions[0];
  cm=b->dimensions[1];
  dims[0] = cn;
  dims[1] = cm;

  an = a->dimensions[0];
  am = a->dimensions[1];

  bn = b->dimensions[0];
  bm = b->dimensions[1];
  


  /* Make a new double complex vector of same dimension */
  c=(PyArrayObject *) PyArray_FromDims(2,dims,NPY_CDOUBLE);
  
  if (not_doublecomplexmatrix(c)) return NULL;

  z_adaptive_wmB(&cf, &k, &cm, &cn,&cm, &cn, (double complex *)c->data,
	&cf, &k, &am, &an,&am, &an, (double complex *)a->data,
	&cf, &k, &bm, &bn,&bm, &bn, (double complex *)b->data,&T);

  return PyArray_Return(c);
}



/* ==== matrix multiply  =========================
    Returns a NumPy vector array
    interface:  z_BMADD_PIPEP(c,a,b)
                c,a,b are NumPy Python vector (double complex)
                returns a NumPy vector                                        */
static PyObject* z_BMADD_PIPEP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm;
  int k=0;
  int T=0;

  double complex cf=1.0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!O!", 
			&PyArray_Type, &c,&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'double complex' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_doublecomplexmatrix(c) || not_doublecomplexmatrix(a) || not_doublecomplexmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

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
  


  z_BMADD_PIPEB(&cf, &k, &cm, &cn,&cm, &cn, (double complex *)c->data,
	   &cf, &k, &am, &an,&am, &an, (double complex *)a->data,
	   &cf, &k, &bm, &bn,&bm, &bn, (double complex *)b->data);

  return PyArray_Return(c);
}


/* ==== matrix multiply  =========================
    Returns a NumPy vector array
    interface:  z_BMADDP(c,a,b)
                c,a,b are NumPy Python vector (double complex)
                returns a NumPy vector                                        */
static PyObject* z_BMADDP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm;
  int k=0;
  int T=0;

  double complex cf=1.0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!O!", 
			&PyArray_Type, &c,&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'double complex' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_doublecomplexmatrix(c) || not_doublecomplexmatrix(a) || not_doublecomplexmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

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
  


  z_BMADDB(&cf, &k, &cm, &cn,&cm, &cn, (double complex *)c->data,
	   &cf, &k, &am, &an,&am, &an, (double complex *)a->data,
	   &cf, &k, &bm, &bn,&bm, &bn, (double complex *)b->data);

  return PyArray_Return(c);
}


/* ==== matrix multiply  =========================
    Returns a NumPy vector array
    interface:  z_BMADDRP(c,a,b)
                c,a,b are NumPy Python vector (double complex)
                returns a NumPy vector                                        */
static PyObject* z_BMADDRP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm;
  int k=0;
  int T=0;

  double complex cf=1.0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!O!", 
			&PyArray_Type, &c,&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'double complex' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_doublecomplexmatrix(c) || not_doublecomplexmatrix(a) || not_doublecomplexmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

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
  


  z_BMADDRB(&cf, &k, &cm, &cn,&cm, &cn, (double complex *)c->data,
	   &cf, &k, &am, &an,&am, &an, (double complex *)a->data,
	   &cf, &k, &bm, &bn,&bm, &bn, (double complex *)b->data);

  return PyArray_Return(c);
}


/* ==== matrix multiply  =========================
    Returns a NEW  NumPy vector array
    interface:  z_BMOWR_PIPEP(a,b)
                a is NumPy vector, b is Python vector (double complex)
                returns a NumPy vector                                        */

static PyObject* z_BMOWR_PIPEP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm,dims[2];
  int k=0;
  double complex cf=1.0;
  int T=0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!", 
			&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'double complex' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_doublecomplexmatrix(a) || not_doublecomplexmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

  cn=a->dimensions[0];
  cm=b->dimensions[1];
  dims[0] = cn;
  dims[1] = cm;

  an = a->dimensions[0];
  am = a->dimensions[1];

  bn = b->dimensions[0];
  bm = b->dimensions[1];
  


  /* Make a new double complex vector of same dimension */
  c=(PyArrayObject *) PyArray_FromDims(2,dims,NPY_CDOUBLE);
  
  if (not_doublecomplexmatrix(c)) return NULL;

  z_BMOWR_PIPEB(&cf, &k, &cm, &cn,&cm, &cn, (double complex *)c->data,
	&cf, &k, &am, &an,&am, &an, (double complex *)a->data,
	&cf, &k, &bm, &bn,&bm, &bn, (double complex *)b->data);

  return PyArray_Return(c);
}



/* ==== matrix multiply  =========================
    Returns a NEW  NumPy vector array
    interface:  z_BMOWRP(a,b)
                a is NumPy vector, b is Python vector (double complex)
                returns a NumPy vector                                        */

static PyObject* z_BMOWRP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm,dims[2];
  int k=0;
  double complex cf=1.0;
  int T=0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!", 
			&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'double complex' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_doublecomplexmatrix(a) || not_doublecomplexmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

  cn=a->dimensions[0];
  cm=b->dimensions[1];
  dims[0] = cn;
  dims[1] = cm;

  an = a->dimensions[0];
  am = a->dimensions[1];

  bn = b->dimensions[0];
  bm = b->dimensions[1];
  


  /* Make a new double complex vector of same dimension */
  c=(PyArrayObject *) PyArray_FromDims(2,dims,NPY_CDOUBLE);
  
  if (not_doublecomplexmatrix(c)) return NULL;

  z_BMOWRB(&cf, &k, &cm, &cn,&cm, &cn, (double complex *)c->data,
	&cf, &k, &am, &an,&am, &an, (double complex *)a->data,
	&cf, &k, &bm, &bn,&bm, &bn, (double complex *)b->data);

  return PyArray_Return(c);
}



/* ==== matrix multiply  =========================
    Returns a NEW  NumPy vector array
    interface:  z_BMOWRRP(a,b)
                a is NumPy vector, b is Python vector (double complex)
                returns a NumPy vector                                        */

static PyObject* z_BMOWRRP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm,dims[2];
  int k=0;
  double complex cf=1.0;
  int T=0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!", 
			&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'double complex' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_doublecomplexmatrix(a) || not_doublecomplexmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

  cn=a->dimensions[0];
  cm=b->dimensions[1];
  dims[0] = cn;
  dims[1] = cm;

  an = a->dimensions[0];
  am = a->dimensions[1];

  bn = b->dimensions[0];
  bm = b->dimensions[1];
  


  /* Make a new double complex vector of same dimension */
  c=(PyArrayObject *) PyArray_FromDims(2,dims,NPY_CDOUBLE);
  
  if (not_doublecomplexmatrix(c)) return NULL;

  z_BMOWRRB(&cf, &k, &cm, &cn,&cm, &cn, (double complex *)c->data,
	&cf, &k, &am, &an,&am, &an, (double complex *)a->data,
	&cf, &k, &bm, &bn,&bm, &bn, (double complex *)b->data);

  return PyArray_Return(c);
}



/* ==== matrix multiply  =========================
    Returns a NumPy vector array
    interface:  s_mm_leaf_computation_maddP(c,a,b)
                c,a,b are NumPy Python vector (float)
                returns a NumPy vector                                        */
static PyObject* s_mm_leaf_computation_maddP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm;
  int k=0;
  int T=0;

  float cf=1.0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!O!", 
			&PyArray_Type, &c,&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'float' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_floatmatrix(c) || not_floatmatrix(a) || not_floatmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

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
  


  s_mm_leaf_computation_maddB(&cf, &k, &cm, &cn,&cm, &cn, (float *)c->data,
	   &cf, &k, &am, &an,&am, &an, (float *)a->data,
	   &cf, &k, &bm, &bn,&bm, &bn, (float *)b->data);

  return PyArray_Return(c);
}


/* ==== matrix multiply  =========================
    Returns a NEW  NumPy vector array
    interface:  s_mm_leaf_computationP(a,b)
                a is NumPy vector, b is Python vector (float)
                returns a NumPy vector                                        */

static PyObject* s_mm_leaf_computationP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm,dims[2];
  int k=0;
  float cf=1.0;
  int T=0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!", 
			&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'float' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_floatmatrix(a) || not_floatmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

  cn=a->dimensions[0];
  cm=b->dimensions[1];
  dims[0] = cn;
  dims[1] = cm;

  an = a->dimensions[0];
  am = a->dimensions[1];

  bn = b->dimensions[0];
  bm = b->dimensions[1];
  


  /* Make a new float vector of same dimension */
  c=(PyArrayObject *) PyArray_FromDims(2,dims,NPY_FLOAT);
  
  if (not_floatmatrix(c)) return NULL;

  s_mm_leaf_computationB(&cf, &k, &cm, &cn,&cm, &cn, (float *)c->data,
	&cf, &k, &am, &an,&am, &an, (float *)a->data,
	&cf, &k, &bm, &bn,&bm, &bn, (float *)b->data);

  return PyArray_Return(c);
}



/* ==== matrix multiply  =========================
    Returns a NumPy vector array
    interface:  d_mm_leaf_computation_maddP(c,a,b)
                c,a,b are NumPy Python vector (double)
                returns a NumPy vector                                        */
static PyObject* d_mm_leaf_computation_maddP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm;
  int k=0;
  int T=0;

  double cf=1.0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!O!", 
			&PyArray_Type, &c,&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'double' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_doublematrix(c) || not_doublematrix(a) || not_doublematrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

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
  


  d_mm_leaf_computation_maddB(&cf, &k, &cm, &cn,&cm, &cn, (double *)c->data,
	   &cf, &k, &am, &an,&am, &an, (double *)a->data,
	   &cf, &k, &bm, &bn,&bm, &bn, (double *)b->data);

  return PyArray_Return(c);
}


/* ==== matrix multiply  =========================
    Returns a NEW  NumPy vector array
    interface:  d_mm_leaf_computationP(a,b)
                a is NumPy vector, b is Python vector (double)
                returns a NumPy vector                                        */

static PyObject* d_mm_leaf_computationP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm,dims[2];
  int k=0;
  double cf=1.0;
  int T=0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!", 
			&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'double' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_doublematrix(a) || not_doublematrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

  cn=a->dimensions[0];
  cm=b->dimensions[1];
  dims[0] = cn;
  dims[1] = cm;

  an = a->dimensions[0];
  am = a->dimensions[1];

  bn = b->dimensions[0];
  bm = b->dimensions[1];
  


  /* Make a new double vector of same dimension */
  c=(PyArrayObject *) PyArray_FromDims(2,dims,NPY_DOUBLE);
  
  if (not_doublematrix(c)) return NULL;

  d_mm_leaf_computationB(&cf, &k, &cm, &cn,&cm, &cn, (double *)c->data,
	&cf, &k, &am, &an,&am, &an, (double *)a->data,
	&cf, &k, &bm, &bn,&bm, &bn, (double *)b->data);

  return PyArray_Return(c);
}



/* ==== matrix multiply  =========================
    Returns a NumPy vector array
    interface:  c_mm_leaf_computation_maddP(c,a,b)
                c,a,b are NumPy Python vector (float complex)
                returns a NumPy vector                                        */
static PyObject* c_mm_leaf_computation_maddP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm;
  int k=0;
  int T=0;

  float complex cf=1.0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!O!", 
			&PyArray_Type, &c,&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'float complex' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_floatcomplexmatrix(c) || not_floatcomplexmatrix(a) || not_floatcomplexmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

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
  


  c_mm_leaf_computation_maddB(&cf, &k, &cm, &cn,&cm, &cn, (float complex *)c->data,
	   &cf, &k, &am, &an,&am, &an, (float complex *)a->data,
	   &cf, &k, &bm, &bn,&bm, &bn, (float complex *)b->data);

  return PyArray_Return(c);
}


/* ==== matrix multiply  =========================
    Returns a NEW  NumPy vector array
    interface:  c_mm_leaf_computationP(a,b)
                a is NumPy vector, b is Python vector (float complex)
                returns a NumPy vector                                        */

static PyObject* c_mm_leaf_computationP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm,dims[2];
  int k=0;
  float complex cf=1.0;
  int T=0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!", 
			&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'float complex' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_floatcomplexmatrix(a) || not_floatcomplexmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

  cn=a->dimensions[0];
  cm=b->dimensions[1];
  dims[0] = cn;
  dims[1] = cm;

  an = a->dimensions[0];
  am = a->dimensions[1];

  bn = b->dimensions[0];
  bm = b->dimensions[1];
  


  /* Make a new float complex vector of same dimension */
  c=(PyArrayObject *) PyArray_FromDims(2,dims,NPY_CFLOAT);
  
  if (not_floatcomplexmatrix(c)) return NULL;

  c_mm_leaf_computationB(&cf, &k, &cm, &cn,&cm, &cn, (float complex *)c->data,
	&cf, &k, &am, &an,&am, &an, (float complex *)a->data,
	&cf, &k, &bm, &bn,&bm, &bn, (float complex *)b->data);

  return PyArray_Return(c);
}



/* ==== matrix multiply  =========================
    Returns a NumPy vector array
    interface:  z_mm_leaf_computation_maddP(c,a,b)
                c,a,b are NumPy Python vector (double complex)
                returns a NumPy vector                                        */
static PyObject* z_mm_leaf_computation_maddP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm;
  int k=0;
  int T=0;

  double complex cf=1.0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!O!", 
			&PyArray_Type, &c,&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'double complex' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_doublecomplexmatrix(c) || not_doublecomplexmatrix(a) || not_doublecomplexmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

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
  


  z_mm_leaf_computation_maddB(&cf, &k, &cm, &cn,&cm, &cn, (double complex *)c->data,
	   &cf, &k, &am, &an,&am, &an, (double complex *)a->data,
	   &cf, &k, &bm, &bn,&bm, &bn, (double complex *)b->data);

  return PyArray_Return(c);
}


/* ==== matrix multiply  =========================
    Returns a NEW  NumPy vector array
    interface:  z_mm_leaf_computationP(a,b)
                a is NumPy vector, b is Python vector (double complex)
                returns a NumPy vector                                        */

static PyObject* z_mm_leaf_computationP(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm,dims[2];
  int k=0;
  double complex cf=1.0;
  int T=0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!", 
			&PyArray_Type, &a,&PyArray_Type, &b))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is 'double complex' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_doublecomplexmatrix(a) || not_doublecomplexmatrix(b)) return NULL;
    
  /* Get the dimension of the input */
  

  cn=a->dimensions[0];
  cm=b->dimensions[1];
  dims[0] = cn;
  dims[1] = cm;

  an = a->dimensions[0];
  am = a->dimensions[1];

  bn = b->dimensions[0];
  bm = b->dimensions[1];
  


  /* Make a new double complex vector of same dimension */
  c=(PyArrayObject *) PyArray_FromDims(2,dims,NPY_CDOUBLE);
  
  if (not_doublecomplexmatrix(c)) return NULL;

  z_mm_leaf_computationB(&cf, &k, &cm, &cn,&cm, &cn, (double complex *)c->data,
	&cf, &k, &am, &an,&am, &an, (double complex *)a->data,
	&cf, &k, &bm, &bn,&bm, &bn, (double complex *)b->data);

  return PyArray_Return(c);
}

