"""
 



"""

pythontemplate ="""

/* ==== matrix multiply  =========================
    Returns a NEW  NumPy vector array
    interface:  %s(a,b)
                a is NumPy vector, b is Python vector (%s)
                returns a NumPy vector                                        */

static PyObject* %s(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm,dims[2];
  int k=0;
  %s cf=1.0;
  int T=0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!%s", 
			&PyArray_Type, &a,&PyArray_Type, &b%s))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is '%s' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_%s(a) || not_%s(b)) return NULL;
    
  /* Get the dimension of the input */
  

  cn=a->dimensions[0];
  cm=b->dimensions[1];
  dims[0] = cn;
  dims[1] = cm;

  an = a->dimensions[0];
  am = a->dimensions[1];

  bn = b->dimensions[0];
  bm = b->dimensions[1];
  


  /* Make a new %s vector of same dimension */
  c=(PyArrayObject *) PyArray_FromDims(2,dims,%s);
  
  if (not_%s(c)) return NULL;

  %s(&cf, &k, &cm, &cn,&cm, &cn, (%s *)c->data,
	&cf, &k, &am, &an,&am, &an, (%s *)a->data,
	&cf, &k, &bm, &bn,&bm, &bn, (%s *)b->data%s);

  return PyArray_Return(c);
}

"""


pythontemplate2 = """

/* ==== matrix multiply  =========================
    Returns a NumPy vector array
    interface:  %s(c,a,b)
                c,a,b are NumPy Python vector (%s)
                returns a NumPy vector                                        */
static PyObject* %s(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm;
  int k=0;
  int T=0;

  %s cf=1.0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!O!%s", 
			&PyArray_Type, &c,&PyArray_Type, &a,&PyArray_Type, &b%s))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is '%s' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_%s(c) || not_%s(a) || not_%s(b)) return NULL;
    
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
  


  %s(&cf, &k, &cm, &cn,&cm, &cn, (%s *)c->data,
	   &cf, &k, &am, &an,&am, &an, (%s *)a->data,
	   &cf, &k, &bm, &bn,&bm, &bn, (%s *)b->data%s);

  return PyArray_Return(c);
}
"""



pythontemplategpu ="""

/* ==== matrix multiply  =========================
    Returns a NEW  NumPy vector array
    interface:  %s(a,b)
                a is NumPy vector, b is Python vector (%s)
                returns a NumPy vector                                        */

static PyObject* %s(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm,dims[2];
  int k=0;
  %s cf=1.0;
  int T=0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!%s", 
			&PyArray_Type, &a,&PyArray_Type, &b%s))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is '%s' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_%s(a) || not_%s(b)) return NULL;
    
  /* Get the dimension of the input */
  

  cn=a->dimensions[0];
  cm=b->dimensions[1];
  dims[0] = cn;
  dims[1] = cm;

  an = a->dimensions[0];
  am = a->dimensions[1];

  bn = b->dimensions[0];
  bm = b->dimensions[1];
  


  /* Make a new %s vector of same dimension */
  c=(PyArrayObject *) PyArray_FromDims(2,dims,%s);
  
  if (not_%s(c)) return NULL;

  %s(&cf, &k, &cm, &cn,&cm, &cn, (%s *)c->data,
	&cf, &k, &am, &an,&am, &an, (%s *)a->data,
	&cf, &k, &bm, &bn,&bm, &bn, (%s *)b->data%s);

  return PyArray_Return(c);
}

"""


pythontemplate2 = """

/* ==== matrix multiply  =========================
    Returns a NumPy vector array
    interface:  %s(c,a,b)
                c,a,b are NumPy Python vector (%s)
                returns a NumPy vector                                        */
static PyObject* %s(PyObject *self, PyObject *args)  {
  

  PyArrayObject *a,*b, *c;
  int an,am,bn,bm,cn,cm;
  int k=0;
  int T=0;

  %s cf=1.0;

  /* Parse tuples separately since args will differ between C fcns */
  if (!PyArg_ParseTuple(args, "O!O!O!%s", 
			&PyArray_Type, &c,&PyArray_Type, &a,&PyArray_Type, &b%s))  return NULL;
  if (NULL == a || NULL == b)  return NULL;
    
  /* Check that object input is '%s' type and a vector
     Not needed if python wrapper function checks before call to this routine */
  if (not_%s(c) || not_%s(a) || not_%s(b)) return NULL;
    
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
  


  %s(&cf, &k, &cm, &cn,&cm, &cn, (%s *)c->data,
	   &cf, &k, &am, &an,&am, &an, (%s *)a->data,
	   &cf, &k, &bm, &bn,&bm, &bn, (%s *)b->data%s);

  return PyArray_Return(c);
}
"""



template = """
void %s(%s *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, %s *datac, \n\
 %s *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, %s *dataa, \n\
 %s *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, %s *datab%s) {\n\
 \t%s_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; \n\
 \t%s_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  \n\
 \t%s_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};\n\
 \tTEXECUTE(%s(C,A,B%s));\n }
"""

templategpu = """
void %s(%s *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, %s *datac, int *cgpu, \n\
 %s *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, %s *dataa,  int *agpu, \n\
 %s *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, %s *datab%s, int *bgpu) {\n\
 \t%s_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac, *cgpu}; \n\
 \t%s_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa, *agpu};  \n\
 \t%s_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab, *bgpu};\n\
 \tTEXECUTE(%s(C,A,B%s));\n }
"""

templateR2 ="""
%s <- function(c,C,a,A,b,B%s) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;
    nc   = length(C[1,]);
    mc   = length(C[,1]) ;

    n = 0
  
   output <- .C("%s",
     betac = as.%s(c),
     transc = as.integer(n),
     mc =as.integer(mc),
     nc =as.integer(nc),
     Mc =as.integer(mc),
     Nc =as.integer(nc),
     datac = as.%s(C),		
     betaa = as.%s(a),
     transa = as.integer(n),
     ma =as.integer(ma),
     na =as.integer(na),
     Ma =as.integer(ma),
     Na =as.integer(na),
     dataa = as.%s(A),		
     betab = as.%s(b),
     transb = as.integer(n),
     mb =as.integer(mb),
     nb =as.integer(nb),
     Mb =as.integer(mb),
     Nb =as.integer(nb),
     datab = as.%s(B)%s

     )

    array(output$datac,dim=dim(C))
}
"""

templateR1 ="""
%s <- function(a,A,b,B%s) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;

    nc   = length(B[1,]);
    mc   = length(A[,1]) ;
    C = array(0.0, dim=c(mc,nc))
    c = 1.0
    n = 0
    output <- .C("%s",
                 betac = as.%s(c),
                 transc = as.integer(n),
                 mc =as.integer(mc),
                 nc =as.integer(nc),
                 Mc =as.integer(mc),
                 Nc =as.integer(nc),
                 datac = as.%s(C),		
                 betaa = as.%s(a),
                 transa = as.integer(n),
                 ma =as.integer(ma),
                 na =as.integer(na),
                 Ma =as.integer(ma),
                 Na =as.integer(na),
                 dataa = as.%s(A),		
                 betab = as.%s(b),
                 transb = as.integer(n),
                 mb =as.integer(mb),
                 nb =as.integer(nb),
                 Mb =as.integer(mb),
                 Nb =as.integer(nb),
                 datab = as.%s(B)%s
                 )

    array(output$datac,dim=dim(C))
}
"""


def generateP(t,f,template1,template2,F,L,gpus):
    #print f
    items = f.split();
    #print len(items),items
    result = ""
    T = t[0]
    P = t[1]
 
    

    if T == "float":
        PT = "NPY_FLOAT"
        Check = "floatmatrix"
    elif T =='double complex':
        PT = "NPY_CDOUBLE"
        Check = "doublecomplexmatrix"
    elif T == 'float complex':    
        PT = "NPY_CFLOAT"
        Check = "floatcomplexmatrix"
    elif T == 'double':
        PT = "NPY_DOUBLE"
        Check = "doublematrix"

    extra0 =''
    extra1 = ''
    extra2 = ''

    if len(items)==5:
        if items[0].find("adaptive")>=0:
            extra0 = "d";
            extra1 = ",&T"
            extra2 = ',&T'




    name = t[1].lower()+"_"+items[0];

    result = ""

    rname = name+"P"
    bname = name+"B"


    L.append("PyObject* "+rname)

    template = template1
    if (name.lower().find("add")<0  ): 

        result = template % (rname,T,rname,T,extra0, extra1,T,Check,Check,T,PT,Check,bname,T,T,T,extra2)
    else:
        result = template2 %(rname,T,rname,T,extra0, extra1,T,Check,Check,Check,bname,T,T,T,extra2)

    F.write(result);



def generateR(t,f,template1,template2,F,L,gpus):
    #print f
    items = f.split();
    #print len(items),items
    result = ""
    T = t[0]
    P = t[1]

    extra0 = ''
    extra1 = ''
    if len(items)==5:
        if items[0].find("adaptive")>=0:
            extra0 = ",a=as.integer(K)";
            extra1 = ",K"


 
    
    
    if T in [ "double", "double complex"]:
        extra0 += ',DUP=FALSE'
    
    if T == "float":
        T = "single"
    elif T =='double complex':
        T = "complex"
    elif T == 'float complex':    
        T = "complex"
        extra0 = ''
    


    name = t[1].lower()+"_"+items[0];


    result = ""

    rname = name+"R"
    bname = name+"B"
    L.append(rname)

    template = template1
    if (name.lower().find("add")>=0  ): 
        sys.stderr.write(name+"\n")
        template = template2


    result = template %(rname,extra1,bname,T,T,T,T,T,T,extra0)

    F.write(result);


def generate(t,f,template,F,gpus):
    #print f
    items = f.split();
    #print len(items),items
    result = ""
    extra0 = ''
    extra1 =''


    name = t[1].lower()+"_"+items[0];
    T = t[0]
    P = t[1]

        
    if len(items)==5:
        if items[0].find("adaptive")>=0:
            extra0 = ", int *a";
            extra1 = ",*a"
        else:
            extra1 = ",0"
    #print t,f,name,P,T,extra0,extra1
    if (gpus):
        result = templategpu %(name+"B",T,T,T,T,T,T,extra0,P,P,P,name,extra1)
    else:
        result = template %(name+"B",T,T,T,T,T,T,extra0,P,P,P,name,extra1)
    F.write(result);


def generateleaves(t,f,template,F,gpus):
    #print f
    items = f.split();
    #print len(items),items
    result = ""
    extra0 = ''
    extra1 =''


    name = items[0]+"_"+t[1].lower();
    name1 = t[1].lower()+"_"+items[0];
    T = t[0]
    P = t[1]

        
    if len(items)==5:
        if items[0].find("adaptive")>=0:
            extra0 = ", int *a";
            extra1 = ",*a"
        else:
            extra1 = ",0"
    #print t,f,name,P,T,extra0,extra1
    if (gpus):
        result = templategpu %(name1+"B",T,T,T,T,T,T,extra0,P,P,P,name,extra1)
    else:
        result = template %(name1+"B",T,T,T,T,T,T,extra0,P,P,P,name,extra1)
    F.write(result);

def Usage():
    s = """
     generateBaiscInterface -c ../../R/FastMMWR/src/FastMMWRcode.h -r ../../R/FastMMWR/R/FastMMWR.R 
                            -R ../../R/astMMWR/NAMESPACE -p ../Python/FastMMWCode.c -P ../Python/FastMMWHeader.c
                            [-g] 

    """
    print s

if __name__ == "__main__":

    import sys
    import os
    import getopt
    import string 
    
    outputc = None
    outputr = None
    outputhr = None
    outputp = None
    outputhp = None

    gpus = False
    
    try:
        opts, args = getopt.getopt(sys.argv[1:], "hc:r:R:p:P:g", 
                                   ["help","outputc=","outputr=","headerr=","outputp=","headerp=","gpus"])
    except getopt.error, msg:
        raise Usage(msg)
    
    for o, a in opts:
        if o == "-v":
            verbose = True
        elif o in ("-h", "--help"):
            Usage()
            sys.exit()
        elif o in ("-c", "--outputc"):
            outputc = a
        elif o in ("-r", "--outputr"):
            outputr = a
        elif o in ("-R", "--headerr"):
            outputhr = a
        elif o in ("-p", "--outputp"):
            outputp = a
        elif o in ("-P", "--headerp"):
            outputhp = a
        elif o in ("-g", "--gpus"):
            gous = True

        else:
            assert False, "unhandled option"



    #print outputc, outputr

    listoftypes  = [['float','S'], ['double','D'], ['float complex','C'], ['double complex','Z' ]]
    
    leaves = [ "mm_leaf_computation_madd   (DEF(c), DEF(a), DEF(b));",
               "mm_leaf_computation  (DEF(c), DEF(a), DEF(b));" ]
 
    
    functions = [
        'dcmul          (DEF(c), DEF(a), DEF(b));',
        'mul            (DEF(c), DEF(a), DEF(b));',
        'mulpt          (DEF(c), DEF(a), DEF(b));',
        'madd           (DEF(c), DEF(a), DEF(b));',
        'saddmul        (DEF(c), DEF(a), DEF(b));',
        'smul           (DEF(c), DEF(a), DEF(b));',
        'saddmulR       (DEF(c), DEF(a), DEF(b));',
        'smulR          (DEF(c), DEF(a), DEF(b));',
        'wmul           (DEF(c), DEF(a), DEF(b));',
        'waddmul        (DEF(c), DEF(a), DEF(b));',
        'wm             (DEF(c), DEF(a), DEF(b));',
        'wmadd          (DEF(c), DEF(a), DEF(b));',
        'wmR            (DEF(c), DEF(a), DEF(b));',
        'wmaddR         (DEF(c), DEF(a), DEF(b));',
        'wmTR           (DEF(c), DEF(a), DEF(b));',
        'wmaddTR        (DEF(c), DEF(a), DEF(b));',
        'adaptive_smul  (DEF(c), DEF(a), DEF(b), int);',
        'omul           (DEF(c), DEF(a), DEF(b));',
        'oaddmul        (DEF(c), DEF(a), DEF(b));',
        'owmul          (DEF(c), DEF(a), DEF(b));',
        'owaddmul       (DEF(c), DEF(a), DEF(b));',
        'bm             (DEF(c), DEF(a), DEF(b));',
        'bmadd          (DEF(c), DEF(a), DEF(b));',
        'ptaddmul       (DEF(c), DEF(a), DEF(b));',
        'wmpipe         (DEF(c), DEF(a), DEF(b), TAddOperands*);', 
        'wmaddpipe      (DEF(c), DEF(a), DEF(b), TAddOperands*);',
        'bmpipe         (DEF(c), DEF(a), DEF(b), TAddOperands*);', 
        'bmaddpipe      (DEF(c), DEF(a), DEF(b), TAddOperands*);',
        'smpipe         (DEF(c), DEF(a), DEF(b), TAddOperands*);', 
        'smaddpipe      (DEF(c), DEF(a), DEF(b), TAddOperands*);',
        'Rmul           (DEF(c), DEF(a), DEF(b));',
        'adaptive_wm    (DEF(c), DEF(a), DEF(b), int);',
        'BMADD_PIPE     (DEF(c), DEF(a), DEF(b), TAddOperands*);',
        'BMADD          (DEF(c), DEF(a), DEF(b));',
        'BMADDR          (DEF(c), DEF(a), DEF(b));',
        'BMOWR_PIPE     (DEF(c), DEF(a), DEF(b), TAddOperands*);',
        'BMOWR          (DEF(c), DEF(a), DEF(b));',                     
        'BMOWRR          (DEF(c), DEF(a), DEF(b));'                     
        ]


    if (outputc != None ):
        F = open(outputc,"w")


        for t in listoftypes:
            for f in functions:
                
                generate(t,f,template,F,gpus)
        
        for t in listoftypes:
            for f in leaves:
                
                generateleaves(t,f,template,F,gpus)
        
        F.close()

    if (outputr != None) :
        
        F=open(outputr,"w")
        
        L = []
        for t in listoftypes:
            for f in functions:
                
                generateR(t,f,templateR1,templateR2,F,L,gpus)
        
        for t in listoftypes:
            for f in leaves:
                
                generateR(t,f,templateR1,templateR2,F,L,gpus)
        
            
        F.close()
    
    if ( outputhr != None):
        s =  "useDynLib(FastMMWR)\n"
    #print L
        s += "export("+L.pop(0)
        for l in L:
            s+= ","+l
        s+=")\n"
        
        F = open(outputhr,"w")
        F.write(s)
        F.close()

    if (outputp != None) :
        
        F=open(outputp,"w")
        
        LP = []
        for t in listoftypes:
            for f in functions:
                
                generateP(t,f,pythontemplate,pythontemplate2,F,LP,gpus)
        
        for t in listoftypes:
            for f in leaves:
                
                generateP(t,f,pythontemplate,pythontemplate2,F,LP,gpus)
        
            
        F.close()
    
    if ( outputhp != None):
        """
        static PyObject *d_wmp(PyObject *self, PyObject *args);
        static void d_wmaddp(PyObject *self, PyObject *args);

        static PyMethodDef FMMWPMethods[] = {
        {"d_wmp", d_wmp, METH_VARARGS,"Winograd"},
        {"d_wmaddp", d_wmaddp, METH_VARARGS,"Winograd MADD"},
        {NULL, NULL,0,NULL}     /* Sentinel - marks the end of this structure */
        };

        """


        F = open(outputhp,"w")
        M = "static PyMethodDef FMMWPMethods[] = {\n" 
        for n in LP:
            F.write("static "+n+"(PyObject *self, PyObject *args);\n") 
            t,name = n.split(' ')
            l = '{"%s", %s, METH_VARARGS},\n' %(name, name)
            M += l
        
        M+="{NULL,NULL}\n};\n"
        F.write(M);
        F.close()

    
