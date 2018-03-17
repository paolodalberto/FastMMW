import string
import copy


architecturetemplate = """
#ifndef PTHREADARCHITECTURE 
#define PTHREADARCHITECTURE 


#define NUM_THREADS %d
#define NUM_CORES %d

static int _P[NUM_CORES]   = {%s};
static int _A[NUM_THREADS] = {%s};
static int _T[NUM_THREADS] = {%s};

#endif
"""

Type  = ['Single','Double','SComplex','DComplex']
#Type  = ['Single'] #,'Double','SComplex','DComplex']
Macro = ['-DSINGLE_PRECISION','-DDOUBLE_PRECISION','-DSINGLE_COMPLEX','-DDOUBLE_COMPLEX']
NSIZE = [10000, 5000,5000,3000]

unrolling = [4,8,16,32,64 ]

blas = 'GotoBLAS'
BLASLIB = "../OpenBLAS/install/lib"
policy = "parallel"
config = []





TypeLibrary = {
    'Single': 'singlelib',
    'Double':'doublelib',
    'SComplex':'scomplexlib',
    'DComplex':'dcomplexlib'
    }

complete = True



def prepareThreadsHeaders_old(L,include,template):
    
    #print "prepareThreadsHeaders",L,include,template


    F = open(include,'w')
    p = '%d' %(2**L[0])
    for i in range(1,len(L)):
        p += ",%d" % (2**L[i])

    i = len(L)-1
    a = '%d' %(2**L[i])
    i -= 1
    while i>=0:
        a += ",%d" % (2**L[i])
        i-=1
    
    s = template % (len(L),len(L),p,a,p)
    
    F.write(s)
    F.close()

def prepareThreadsHeaders(L,include,template):
    
    #print "prepareThreadsHeaders",L,include,template


    F = open(include,'w')
    p = '%d' %(L[0])
    for i in range(1,len(L)):
        p += ",%d" % (L[i])

    i = len(L)-1
    a = '%d' %(L[i])
    i -= 1
    while i>=0:
        a += ",%d" % (L[i])
        i-=1
    
    s = template % (len(L),len(L),p,a,p)
    
    F.write(s)
    F.close()

    
def createLibrary(L,u,include,template,t,m,blas,B): 
    import subprocess




    print "Thread allocation",L," Unrolling", u, "Starting", B
    prepareThreadsHeaders(L,include,template)

    if blas=='ATLAS':
        gemm = 'ex3_atlas'
        winograd = 'winograd3atlas'
        gemmx = 'atlas'
        winogradx = 'winogradatlas'
        marcopipe2 = 'marcoatlas_pipe_2'
        wmpipe = 'winograd3atlaspipe'
        libflag = '-DATLAS '
        LIB = ""
    elif blas == 'GotoBLAS':
        gemm = 'gotos3'
        winograd = 'winograd3'
        gemmx= 'gotos'
        winogradx = 'winograd'
        marcopipe2 = 'marco_pipe_2'
        wmpipe = 'ex3_pipe'
        libflag = '-DGOTO_BLAS'
        #LIB = "export LD_LIBRARY_PATH=../GotoBLAS2;"
        LIB = "export LD_LIBRARY_PATH=%s;" %(BLASLIB)
    
    B = int(B)

    s = "MACROS=\"%s  -DMYSCHED=1 -DLIBRARY_PACKAGE -DAUTOMATIC -DLEAF=%d\" TYPE=%s UNROLL=%d " % (m,B,t,u) 
    cmd = '/usr/bin/make clean add-gen %s %s %s %s %s' % (gemm, winograd,marcopipe2, wmpipe,s)
    print cmd
    process = subprocess.Popen([cmd], shell=True, stdout=subprocess.PIPE,stderr=subprocess.PIPE)

    T = process.communicate()
    

    s = "MACROS=\"%s  -DMYSCHED=1 -DLIBRARY_PACKAGE -DAUTOMATIC -DLEAF=%d %s \" TYPE=%s " % (m,B,libflag,t) 
    cmd = '/usr/bin/make  %s %s' % (TypeLibrary[t],s)
    print cmd
    process = subprocess.Popen([cmd], shell=True, stdout=subprocess.PIPE,stderr=subprocess.PIPE)

    T = process.communicate()
    print T

    return B

def createBreakEven(L,Cores,u,include,template,t,m,blas,B): 
    import subprocess




    print "Thread allocation",L," Unrolling", u, "Starting", B
    prepareThreadsHeaders(L,include,template)

    if blas=='ATLAS':
        gemm = 'ex3_atlas'
        winograd = 'winograd3atlas'
        gemmx = 'atlas'
        winogradx = 'winogradatlas'
        libflag = '-DATLAS '
        LIB = ""
    elif blas == 'GotoBLAS':
        gemm = 'gotos3'
        winograd = 'winograd3'
        gemmx= 'gotos'
        winogradx = 'winograd'
        libflag = '-DGOTO_BLAS'
        #LIB = "export LD_LIBRARY_PATH=../GotoBLAS2;"
        LIB = "export LD_LIBRARY_PATH=%s;" %(BLASLIB)


    originalB = B = int(B)-200
    
    s = "MACROS=\"%s -DLIBRARY_PACKAGE -DMYSCHED=1 -DAUTOMATIC -DLEAF=%d\" TYPE=%s UNROLL=%d " % (m,int(B),t,u) 
    cmd = '/usr/bin/make clean add-gen %s %s %s' % (gemm, winograd,s)
    print cmd
    process = subprocess.Popen([cmd], shell=True, stdout=subprocess.PIPE,stderr=subprocess.PIPE)

    T = process.communicate()
    
    #print T

    F = True
    attempt = 0
    B = int(B)+1 

    J = "01010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101"

    WFLOPS = 0
    while F and attempt<2:
        
        if (B>2*originalB) :
            attempt +=1
            print " Wow I could not find the break even point", attempt 
            originalB = B-1
            s = "MACROS=\"%s -DLIBRARY_PACKAGE  -DMYSCHED=1 -DAUTOMATIC -DLEAF=%d\" TYPE=%s UNROLL=%d" % (m,originalB,t,u) 
            cmd = '/usr/bin/make clean add-gen %s %s %s' % (gemm, winograd,s)
            print cmd
            process = subprocess.Popen([cmd], shell=True, stdout=subprocess.PIPE,stderr=subprocess.PIPE)
            
            T = process.communicate()
            print T
            


        cmd = "%s echo \"0 0 1 1 1 %d %d %d %d %d %s\" | Executable/%s/%s" % (LIB,B,B,B,B,len(J),J,t,gemmx)
        print cmd
        process = subprocess.Popen([cmd], shell=True, stdout=subprocess.PIPE,stderr=subprocess.PIPE)
        
        T = process.communicate()
        i = 0
        while  (len(T[0])==0 and i < 5):
            
            i+=1
            print T
            print "Failed test trying again " 
            process = subprocess.Popen([cmd], shell=True, stdout=subprocess.PIPE,stderr=subprocess.PIPE)
            T = process.communicate()

        print T


        Performance= [] 
        for line in T[0].split("\n"):
            if (line.find("GFLOPS HOT")>0):
                print line
                l = line.rfind(' ')
                Performance.append(float(line[l:]))

        cmd = "%s echo \"0 0 1 1 1 %d %d %d %d %d %s\" | Executable/%s/%s" % (LIB,B,B,B,B,len(J),J,t,winogradx)   
        print cmd
        process = subprocess.Popen([cmd], shell=True, stdout=subprocess.PIPE,stderr=subprocess.PIPE)
        
        T = process.communicate()
        i = 0
        while  (len(T[0])==0 and i < 5):
            
            i+=1
            print T
            print "Failed test trying again " 
            process = subprocess.Popen([cmd], shell=True, stdout=subprocess.PIPE,stderr=subprocess.PIPE)
            T = process.communicate()


        print T
        for line in T[0].split("\n"):
            if (line.find("GFLOPS HOT")>0):
                print line
                l = line.rfind(' ')
                Performance.append(float(line[l:]))
        #print T

                
        print "Performance", Performance
        error = Performance[0]*2/100
        
        if Performance[1] - Performance[0]>error  :
            F =False
            WFLOPS = Performance[1]
        else:
            B += B/10
            
            
            

    s = "MACROS=\"%s  -DMYSCHED=1 -DLIBRARY_PACKAGE -DAUTOMATIC -DLEAF=%d %s\" TYPE=%s  " % (m,int(B),libflag,t) 
    cmd = '/usr/bin/make clean  %s %s' % (TypeLibrary[t],s)
    print cmd
    process = subprocess.Popen([cmd], shell=True, stdout=subprocess.PIPE,stderr=subprocess.PIPE)
    
    T = process.communicate()
    print T
    
    return B,WFLOPS

def createTestAddition(L,Cores,u,include,template,t,m,blas): 
#    print  "createTestAddition", L


    if blas=='ATLAS':
        LIB = ""
        ex3 = 'ex3atlas'
        ex3x= 'ex3atlas_g'
    elif blas == 'GotoBLAS':
        ex3 = 'ex3'
        ex3x= 'ex3_g'
        #LIB = "export LD_LIBRARY_PATH=../GotoBLAS2;"
        LIB = "export LD_LIBRARY_PATH=%s;" %(BLASLIB)

    PER = []
    
    J = "01010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101"
    
    for l in L:
        print "Thread allocation",l," Unrolling", u
        prepareThreadsHeaders(l,include,template)
        
        import subprocess
        s = "MACROS=\"%s -DLIBRARY_PACKAGE -DMYSCHED=1 -DAUTOMATIC -DLEAF=%d\" TYPE=%s UNROLL=%d " % (m,NSIZE[Type.index(t)],t,u) 
        cmd = '/usr/bin/make clean add-gen %s %s' % (ex3,s)
        print cmd
        process = subprocess.Popen([cmd], shell=True, stdout=subprocess.PIPE,stderr=subprocess.PIPE)

        T = process.communicate()
        
        BUILD = T
        buildcmd = cmd
        
        cmd = "%s echo \"0 0 1 1 1 %d %d %d %d %d %s\" | Executable/%s/%s" % (LIB,NSIZE[Type.index(t)],NSIZE[Type.index(t)],NSIZE[Type.index(t)],NSIZE[Type.index(t)],len(J),J,t,ex3x)
        print cmd
        process = subprocess.Popen([cmd], shell=True, stdout=subprocess.PIPE,stderr=subprocess.PIPE)

        T = process.communicate()
        #print T
        i = 0
        while  (len(T[0])==0 and i < 5):
            i+=1
            print T
            print "Failed test trying again " 
            process = subprocess.Popen([cmd], shell=True, stdout=subprocess.PIPE,stderr=subprocess.PIPE)
            T = process.communicate()


        Performance = []

        for line in T[0].split("\n"):
            if (line.find("GFLOPS")>0):
                #print t
                l = line.rfind(' ')
                Performance.append(float(line[l:]))
            if (line.find("alpha")>0):
                #print t
                l = line.rfind(' ')
                Performance.append(float(line[l:]))




        print Performance
        sys.stdout.flush()

        if (len(Performance)<2):
            print " Error "
            print buildcmd
            print BUILD
            print cmd
            print T
            sys.exit()

        PER.append(Performance)
        if (not complete):
            error = PER[-2][0]*2/100        
            if (len(PER)>=2 and  error<PER[-2][0] -PER[-1][0]):
                break



    return PER

def prepareArchitecture(P, C,N, Policy="parallel"):
    i = 0

    # there need to be more cores than N
    if (N>len(C)):
        return []



    L = []
    if Policy=="locality":
        
        for p in P:
            for c in P[p]:
                L.append(c['processor'])
        
        

    elif Policy=="parallel":
        PP = copy.deepcopy(P)
        
        while len(L) < N:
            for p in PP:
                #print "P", PP[p]
                if (len(PP[p])>0):
                    c = PP[p].pop(0)
                    #print "\nCore", c
                    L.append(c['processor'])
            
        
    return L[0:N]
        
        




def parseCore(c):
    C = {}
    Lines = c.split('\n')
    for l in Lines:
        print l
        k,v = l.split(':')
        k= string.strip(k)
        v=string.strip(v)
        try:
            v=int(v)
        except ValueError:
            v=v
        C[k] = v
        
    return C


def getProcessorInformation():

    import subprocess

    process = subprocess.Popen(['/bin/cat','/proc/cpuinfo'], shell=False, stdout=subprocess.PIPE)

    L = process.communicate()
    
    #print L
    K = L[0].split('\n\n')
    
    Cores = {}
    Processors = {}

    i = 0
    for p in K:

        if (len(p)>10):
            #print "----"
            DC = parseCore(p)
            #print DC
            key = int(DC['processor'])
            Cores[key] =DC
            #print key, len(Cores)

    #print "Cores", Cores
    #print len(Cores)
        
    for c in Cores:
        key = int(Cores[c]['physical id'])
        if not key in Processors:
            Processors[key] = [ ]
        Processors[key].append(Cores[c])
    #print "Processors", Processors
    
    return Cores,Processors

if __name__ == "__main__":

    import sys
    import os
    import getopt
    import string 
    
    configfile= ''


    try:
        opts, args = getopt.getopt(sys.argv[1:], "hb:p:c:", 
                                   ["help","blas=","policy=","config:"])
    except getopt.error, msg:
        raise Usage(msg)
    
    for o, a in opts:
        if o == "-v":
            verbose = True
        elif o in ("-h", "--help"):
            Usage()
            sys.exit()
        elif o in ("-b", "--blas"):
            blas = a
        elif o in ("-p", "--policy"):
            policy = a
        elif o in ("-c", "--config"):
            configfile = a
            try:
                F = open(configfile,'r')
                l = F.read();
                if (len(l)>0):
                    config = eval(l)
                F.close()
            except IOError:
                #print "I/O error({0}): {1}".format(e.errno, e.strerror)
                config = [] 

        else:
            assert False, "unhandled option"

    """
    Processors information
    """

    Cores,Processors = getProcessorInformation()

    print "Cores"#, Cores
    for c in Cores:
        print c, Cores[c]
    print "Processors"#, Processors
    for c in Processors:
        print c, Processors[c]

    print "Policy", policy

    L = []
    steps = 4
    for n in range(1,len(Cores)+1,4):
        L.append(prepareArchitecture(Processors,Cores,n,policy))
    print L


    #sys.exit()

    i = 0
    while (i< len(Type)):
 

        """
        Matrix Addition optimization and break even point estimation
        """

        if (len(config)<len(Type)):
            PER = []
            for u in unrolling:
                PER.append(
                    createTestAddition(L,Cores,u,
                                       "./PThread/ptarchitecture.h",
                                       architecturetemplate,Type[i],Macro[i],blas)
                    )
                print PER[-1]
                if (len(PER)>=2):
                    error  = PER[-2][0][0]*2/100 
                    error1 = PER[-2][0][1]*2/100 
                if (len(PER)>=2 and  error<PER[-2][0][0] -PER[-1][0][0] and error1<PER[-2][0][1] -PER[-1][0][1]):
                    print "Stop Searching ", error, error1, PER[-2],PER[-1]
                    break


                
            M = 0
            uk = 0
            lk = 0
            
            u =0
            while u< len(PER):
                p = PER[u]
                l = 0
                while l<len(p):
                    k = p[l]
                    
                    if len(k)>0 and k[0]>M:
                        print "MAX", k
                        uk = u
                        lk = l
                        M = k[0]
                    l+=1
                u+=1

            print Type[i], L[lk], unrolling[uk], PER[uk][lk]
            config.append([Type[i], L[lk], unrolling[uk], PER[uk][lk]])

            """
            Break even point measure
        

            Create Libraries
            """
        
            exb,mflops = createBreakEven(config[i][1],Cores,config[i][2],
                                         "./PThread/ptarchitecture.h",
                                         architecturetemplate,Type[i],Macro[i],blas,config[i][-1][-1])
        
            
            config[i].append(exb)
            config[i].append(mflops)


        else:
            createLibrary(config[i][1],config[i][2],
                          "./PThread/ptarchitecture.h",
                          architecturetemplate,Type[i],Macro[i],blas,config[i][-2])
            
            

        i+=1
        
    if len(configfile)>0:
            
        try:
            F = open(configfile,'r')
            l = F.read();
            if (len(l)>0):
                F.close()
        except IOError:
                #print "I/O error({0}): {1}".format(e.errno, e.strerror)
            l = ''

        if len(l)==0:
            F = open(configfile,'w')
            s = "%s" % config
            F.write(s)
            F.close()
