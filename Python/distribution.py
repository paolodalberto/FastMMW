import numpy as np
import FastMMWP as fmm
import random
from threading import Thread
import time
import math
#import matplotlib
from datetime import datetime



def heat(W,header,file=False,filename="tmpheat.png", data = 0): 
    import matplotlib.pyplot as plt    
    from matplotlib.pylab import cm
    plt.rc('font',**{'size':18})

    L = W[0][0]
    
    x = np.arange(0, L.shape[1], 1)
    y = np.arange(0, L.shape[0], 1)
    X, Y = np.meshgrid(x,y)
    fig =plt.figure()
    fig.subplots_adjust(left=0.02, bottom=0.06, right=0.95, top=0.94, wspace=0.05)
    
# Make 4 subplots:
    i=1
    for w in W:    
        if (len(W)>=2) :
            ax = fig.add_subplot(2,len(W)/2+len(W)%2,i)
        else :
            ax = fig.add_subplot(1,1,1)
    

        Z = w[data]

        cax = ax.imshow(Z, interpolation='nearest',cmap=cm.gray)
        fig.colorbar(cax)
        t = "%s - max %f" % (w[1],Z.max())
        shape = "(%d,%d)" % L.shape
        print header, "##_heat_max",  shape, w[1],Z.max()
        plt.title(t,fontsize=32)
        
        i +=1

    

    if (not file):
        fig.show()
        return 
    

    F = plt.gcf()

# Now check everything with the defaults:
    DPI = F.get_dpi()
    print "DPI:", DPI
    DefaultSize = F.get_size_inches()
    F.set_size_inches(DefaultSize[0]*3, DefaultSize[1]*3)
    #fig.show();


    plt.savefig(filename,  format='png' )




def heatM(W,header,file=False,filename="tmpheatM.png",data = [-2,-1]): 
    import matplotlib.pyplot as plt    
    from matplotlib.pylab import cm
    L = W[0][0]
    
    plt.rc('font',**{'size':18})

    x = np.arange(0, L.shape[1], 1)
    y = np.arange(0, L.shape[0], 1)
    X, Y = np.meshgrid(x,y)
    fig =plt.figure()
    fig.subplots_adjust(left=0.02, bottom=0.06, right=0.95, top=0.94, wspace=0.05)
    
# Make 4 subplots:
    i=1
    for w in W:    
        if (len(W)>=2):
            ax = fig.add_subplot(2,len(W)/2+len(W)%2,i)
        else :
            ax = fig.add_subplot(1,1,1)

        m = np.array(range(0,L.shape[0]*L.shape[1]),dtype='d') * 0.0 
        m.shape = L.shape
        
        mlocation =  w[data[0]]
        M =  w[data[1]]

        loc = np.argwhere(max(M) == M)
        #print loc, M[loc], mlocation[loc]
        j = 0
        while (j<len(mlocation)):
            #print mlocation[j],M[j]
            m[mlocation[j][0][0]][mlocation[j][0][1]]=M[j]
            j+=1
            


        cax = ax.imshow(m, interpolation='nearest',cmap=cm.gray)
        fig.colorbar(cax)
        t = "%s - max %f" % (w[1],max(M))
        shape = "(%d,%d)" % L.shape
        
        print header, "##_heatM_max",  shape, w[1],M[loc],mlocation[loc]
        plt.title(t,fontsize=32)
        i +=1

    

    if (not file):
        fig.show()
        return 
    

    F = plt.gcf()

# Now check everything with the defaults:
    DPI = F.get_dpi()
    print "DPI:", DPI
    DefaultSize = F.get_size_inches()
    F.set_size_inches(DefaultSize[0]*3, DefaultSize[1]*3)
    #fig.show();


    plt.savefig(filename,  format='png' )



def histogram(W,header,file=False,filename="tmphist.png",data = -1): 
    import matplotlib.pyplot as plt    
    L = W[0][0]
    plt.rc('font',**{'size':18})


    x = np.arange(0, L.shape[1], 1)
    y = np.arange(0, L.shape[0], 1)
    X, Y = np.meshgrid(x,y)
    fig =plt.figure()
    fig.subplots_adjust(left=0.02, bottom=0.06, right=0.95, top=0.94, wspace=0.05)
    
# Make 4 subplots:
    i=1
    for w in W:    
        if (len(W)>=2):
            ax = fig.add_subplot(2,len(W)/2+len(W)%2,i)
        else :
            ax = fig.add_subplot(1,1,1)


        Z = w[data]

        cax = ax.hist(Z,10, histtype='bar')

        t = "%s - max %f" % (w[1],max(Z))
        shape = "(%d,%d)" % L.shape
        print header, "##_hist_max",  shape, w[1],max(Z)
        plt.title(t,fontsize=32)
        i +=1

    

    if (not file):
        fig.show()
        return 
    

    F = plt.gcf()

# Now check everything with the defaults:
    DPI = F.get_dpi()
    print "DPI:", DPI
    DefaultSize = F.get_size_inches()
    F.set_size_inches(DefaultSize[0]*3, DefaultSize[1]*3)
    #fig.show();


    plt.savefig(filename,  format='png' )








def transposed(lists):
    if not lists: return []
    return map(lambda *row: list(row), *lists)

def plot(A,file=False,filename="tmptime.png",title="Compare"):
    import matplotlib.pyplot as plt    
#    lines = [ "b-o", "g--v","r-.^" ,	
#              "c:<" ,	
#              "m->" ,	
#              "y--1" ,	
#              "k-.2",
#              "b--2"]	
    lines = [ "k-o", 
              "k--v",
              "k-.^" ,	
              "k:<" ,	
              "k->" ,	
              "k--1" ,	
              "k-.2",
              "k--2"]	
    plt.rc('font',**{'size':18})
    

    fig = plt.figure()
    ax = fig.add_subplot(111)
    
    i = 0
    for a in A:
        x = range(1,len(a[-1])+1)
        #print x, a[-1]
        ax.plot(x, a[-1],lines[i],linewidth=6,label=a[1])
        i = i+1

    ax.grid(True)
    ax.legend(loc='lower right')
    ax.set_xlabel('N')
    ax.set_ylabel('Maximum Error')
    plt.title(title,fontsize=32)


    if (not file):
        fig.show()
        return 
    F = plt.gcf()

# Now check everything with the defaults:
    DPI = F.get_dpi()
    print "DPI:", DPI
    DefaultSize = F.get_size_inches()
    F.set_size_inches(DefaultSize[0]*3, DefaultSize[1]*3)
    #fig.show();


    plt.savefig(filename,  format='png' )

def plotsaw(a):

#    lines = [ "b-o", "g--v","r-.^" ,	
#              "c:<" ,	
#              "m->" ,	
#              "y--1" ,	
#              "k-.2" ]	
    lines = [ "k-o", 
              "k--v",
              "k-.^" ,	
              "k:<" ,	
              "k->" ,	
              "k--1" ,	
              "k-.2" ]	
    #plt.rc('font',**{'size':30})


    fig = plt.figure()
    ax = fig.add_subplot(111)
    L= a[0][1:]
    b = transposed(a[1:])
    print b
    x = []
    Y = []
    x = b.pop(0)
    m = 0
    M = 0
    
    for d in b:
        Y.append(d)
        t = max(d)
        M = max(M,t)
    w = [] 
    for i in x:
        w.append(0)

    w[0]= M
    print "white", x, w

    ax.plot(x, w,'w')
    
    i=0
    while (i<len(Y)):
        print x, Y[i], i, L[i]
        ax.plot(x, Y[i],lines[i],linewidth=6,label=L[i])
        i = i+1
        

    plt.xscale('symlog')
    ax.grid(True)
    
    ax.legend(loc='lower right')
    plt.show()





class myThread (Thread):
    def __init__(self, threadID, name, A, AS, T,S):
        Thread.__init__(self)
        self.threadID = threadID
        self.name = name
        self.A = A
        self.AS = AS
        self.T = T
        self.S = S
        #threading.Thread.__init__(self)
    def run(self):
        
        if self.S == "[-1,1]": 
            # -1,1
            for i in range(0,self.T):
                for j in range(0,self.T):
                    self.AS[i][j] = self.A[i][j] = random.random()
                    
        elif self.S == "[0,1]":
            
            for i in range(0,self.T):
                for j in range(0,self.T):
                    self.AS[i][j] = self.A[i][j] = 2*(random.random()-0.5)
        elif self.S == "Hilbert":
            for i in range(0,self.T):
                for j in range(0,self.T):
                    self.AS[i][j] = self.A[i][j] = 1.0/(i+1+j+1-1)
        elif S == "Treblih" and k==0:
            for i in range(0,self.T):
                for j in range(0,self.T):
                    self.AS[i][j] = self.A[i][j] = 1.0/(-i-1-j-1+1 + self.T +self.T )

                    
                    

def compareOne(A,B,R,
               m,M,s,
               k,
               method,verb):

    
    a = datetime.now();CS = method(A,B);   b = datetime.now()
    print verb, b-a
    X = R-CS
    
    print X.max()
    m = (m*(k-1)+  X)/k;  M = (M*(k-1)+np.multiply(X,X))/k ; s = M - np.multiply(m,m)
#    print m
#    print s
    
    T = abs(X)
    maximum = T.max()
    mlocation = np.argwhere(T.max() == T)
    del T
    del CS
    del X

    return m,M,s,maximum,mlocation

def compareP(K,T,S, L):

    
    A = np.array(range(0,T*T),dtype='d')
    B = np.array(range(0,T*T),dtype='d')
    A.shape = (T,T)
    B.shape = (T,T)
    
    AS = np.array(range(0,T*T),dtype='f')
    BS = np.array(range(0,T*T),dtype='f')
    AS.shape = (T,T)
    BS.shape = (T,T)
    

    ml = []
    Ml = []
    Sl = []
    R = {}


    for k in L:
        m = np.array(range(0,T*T),dtype='d') * 0.0 
        M = np.array(range(0,T*T),dtype='d') * 0.0 
        s = np.array(range(0,T*T),dtype='d') * 0.0 
        m.shape = (T,T)
        M.shape  = (T,T)
        s.shape  = (T,T)
        R[k] =  {} 
        R[k]['m'] = m
        R[k]['M'] = M
        R[k]['s'] = s
        R[k]['method'] = L[k]
        R[k]['maximum'] = []        
        R[k]['maxlocation'] = []

    for k in range(1,K+1):
        a = datetime.now(); 
        if S == "[-1,1]": 
            # -1,1
            
            print S, "[-1,1]"
            for i in range(0,T):
                AS[i] = A[i] = np.random.uniform(-1,1,T) 
                BS[i] = B[i] = np.random.uniform(-1,1,T) 
                
        elif S == "[0,1]":
            print S, "[0,1]"
            for i in range(0,T):
                AS[i] = A[i] = np.random.uniform(0,1,T) 
                BS[i] = B[i] = np.random.uniform(0,1,T) 
        elif S == "Hilbert" and k==1:
            print S, "Hilbert"
            
            for i in range(0,T):
                for j in range(0,T):
                    AS[i][j] = A[i][j] = 1.0/(i+1+j+1-1)
                    BS[i][j] = B[i][j] = 1.0/(i+1+j+1-1)
        elif S == "Treblih" and k==1:
            print S, "Treblih"

            for i in range(0,T):
                for j in range(0,T):
                    AS[i][j] = A[i][j] = 1.0/(-i-1-j-1+1 + T +T )
                    BS[i][j] = B[i][j] = 1.0/(-i-1-j-1+1 + T +T )
        elif S == "Hilbert*Treblih" and k==1:
            print S, "Hilbert*Treblih"

            for i in range(0,T):
                for j in range(0,T):
                    AS[i][j] = A[i][j] = 1.0/(-i-1-j-1+1 + T +T )
                    BS[i][j] = B[i][j] = 1.0/(i+1+j+1-1)
        elif S == "I" and k==1:
            print S, "Int"

            for i in range(0,T):
                for j in range(0,T):
                    AS[i][j] = A[i][j] = (-i-1-j-1+1 + T +T )
                    BS[i][j] = B[i][j] = (i+1+j+1-1)

        b = datetime.now()
        print "build matrices", b-a
        
        a = datetime.now(); CD = fmm.d_mm_leaf_computationP(A,B);   b = datetime.now()
        print "Goto Double", b-a
        

        for m in  R:
            R[m]['m'],R[m]['M'], R[m]['s'],maximum,mlocation = compareOne(AS,BS,CD,
                                                                          R[m]['m'],R[m]['M'],R[m]['s'],
                                                                          k,
                                                                          R[m]['method'],m)
            R[m]['maximum'].append(maximum)
            R[m]['maxlocation'].append(mlocation)
        #print R



    for m in  R:
        
        #print m,R[m]['s']
        for i in range(0,s.shape[0]):
            for j in range(0,s.shape[1]):
                R[m]['s'][i,j] = math.sqrt(R[m]['s'][i,j])
        

        
    LL = []
    for m in R:
        LL.append([R[m]['s'],m,  R[m]['s'].max(),R[m]['m'],R[m]['maxlocation'],R[m]['maximum']])

    
    return LL



def compare(K,T,S):
    import copy
    from datetime import datetime
# Create new threads

    thread = False
    
    A = np.array(range(0,T*T),dtype='d')
    B = np.array(range(0,T*T),dtype='d')
    A.shape = (T,T)
    B.shape = (T,T)
    

    
    AS = np.array(range(0,T*T),dtype='f')
    BS = np.array(range(0,T*T),dtype='f')
    AS.shape = (T,T)
    BS.shape = (T,T)
    


    musr = np.array(range(0,T*T),dtype='d') * 0.0 
    muss = np.array(range(0,T*T),dtype='d') * 0.0 
    musw = np.array(range(0,T*T),dtype='d') * 0.0 
    musb = np.array(range(0,T*T),dtype='d') * 0.0 
    musbt = np.array(range(0,T*T),dtype='d') * 0.0 
    musbp = np.array(range(0,T*T),dtype='d') * 0.0 

    

    Msr = np.array(range(0,T*T),dtype='d') * 0.0 
    Mss = np.array(range(0,T*T),dtype='d') * 0.0 
    Msw = np.array(range(0,T*T),dtype='d') * 0.0 
    Msb = np.array(range(0,T*T),dtype='d') * 0.0 
    Msbt = np.array(range(0,T*T),dtype='d') * 0.0 
    Msbp = np.array(range(0,T*T),dtype='d') * 0.0 

    ssr = np.array(range(0,T*T),dtype='d') * 0.0 
    ssw = np.array(range(0,T*T),dtype='d') * 0.0 
    ssb = np.array(range(0,T*T),dtype='d') * 0.0 
    ssbt = np.array(range(0,T*T),dtype='d') * 0.0 
    ssbp = np.array(range(0,T*T),dtype='d') * 0.0 
    sss = np.array(range(0,T*T),dtype='d') * 0.0 
    
    musbp.shape=musbt.shape = musr.shape =muss.shape = musw.shape = musb.shape = (T,T)
    Msbp.shape =Msbt.shape = Msr.shape =Mss.shape = Msw.shape = Msb.shape = (T,T)
    ssbp.shape = ssbt.shape = ssr.shape =sss.shape = ssw.shape = ssb.shape = (T,T)
    
    M = 0.0
    
    for k in range(1,K+1):
        a = datetime.now(); 
        if (thread):
            
            threads = []
            
            if (S == "Hilbert*Treblih"): 
                thread1 = myThread(1, "Thread-1", A,AS,T,"Hilbert")
                thread2 = myThread(2, "Thread-2", B,BS,T,"Treblih")
                
            else:
                thread1 = myThread(1, "Thread-1", A,AS,T,S)
                thread2 = myThread(2, "Thread-2", B,BS,T,S)

            threads.append(thread1)
            threads.append(thread2)
            for t in threads:
                t.start()
                
            for t in threads:
                t.join()
        else:
            if S == "[-1,1]": 
                # -1,1

                print S, "[-1,1]"
                for i in range(0,T):
                    AS[i] = A[i] = np.random.uniform(-1,1,T) 
                    BS[i] = B[i] = np.random.uniform(-1,1,T) 
                    
            elif S == "[0,1]":
                
                
                print S, "[0,1]"
                for i in range(0,T):
                    AS[i] = A[i] = np.random.uniform(0,1,T) 
                    BS[i] = B[i] = np.random.uniform(0,1,T) 
            elif S == "Hilbert" and k==1:
                print S, "Hilbert"
                
                for i in range(0,T):
                    for j in range(0,T):
                        AS[i][j] = A[i][j] = 1.0/(i+1+j+1-1)
                        BS[i][j] = B[i][j] = 1.0/(i+1+j+1-1)
            elif S == "Treblih" and k==1:
                print S, "Treblih"

                for i in range(0,T):
                    for j in range(0,T):
                        AS[i][j] = A[i][j] = 1.0/(-i-1-j-1+1 + T +T )
                        BS[i][j] = B[i][j] = 1.0/(-i-1-j-1+1 + T +T )
            elif S == "Hilbert*Treblih" and k==1:
                print S, "Hilbert*Treblih"

                for i in range(0,T):
                    for j in range(0,T):
                        AS[i][j] = A[i][j] = 1.0/(-i-1-j-1+1 + T +T )
                        BS[i][j] = B[i][j] = 1.0/(i+1+j+1-1)
            elif S == "I" and k==1:
                print S, "Int"

                for i in range(0,T):
                    for j in range(0,T):
                        AS[i][j] = A[i][j] = (-i-1-j-1+1 + T +T )
                        BS[i][j] = B[i][j] = (i+1+j+1-1)
                        
        b = datetime.now()
        print "build matrices", b-a
        
        a = datetime.now(); CD = fmm.d_mm_leaf_computationP(A,B);   b = datetime.now()
        print "Goto Double", b-a
        
        
        a = datetime.now();CS = fmm.s_mm_leaf_computationP(AS,BS);   b = datetime.now()
        print "Goto Float", b-a
        X = CD-CS
        print X.max()
        musr = (musr*(k-1)+  X)/k;  Msr = (Msr*(k-1)+np.multiply(X,X))/k ; ssr = Msr - np.multiply(musr,musr)
        
        
        a = datetime.now();CS = fmm.s_wmpipeP(AS,BS);   b = datetime.now()
        print "Winograd float",b-a
        X = CD-CS
        print X.max()
        musw = (musw*(k-1)+  X)/k; Msw = (Msw*(k-1)+np.multiply(X,X))/k; ssw = Msw - np.multiply(musw,musw)
        
        a = datetime.now();CS = fmm.s_BMOWR_PIPEP(AS,BS);   b = datetime.now()
        print "B-Winograd float", b-a
        X = CD-CS
        print X.max()
        musb = (musb*(k-1)+  X)/k; Msb = (Msb*(k-1)+np.multiply(X,X))/k ;   ssb = Msb - np.multiply(musb,musb)

        a = datetime.now();CS = fmm.s_wmRP(AS,BS);   b = datetime.now()
        print "Winograd-permutation float", b-a
        print CD.shape,CS.shape
        X = CD-CS
        print X.shape, X.max()
        musbt = (musbt*(k-1)+  X)/k; Msbt = (Msbt*(k-1)+np.multiply(X,X))/k; ssbt = Msbt - np.multiply(musbt,musbt)

        a = datetime.now();CS = fmm.s_BMOWRRP(AS,BS);   b = datetime.now()
        print "B-Winograd-premutation float", b-a
        print CD.shape,CS.shape
        
        X = CD-CS
        print X.shape, X.max()
        musbp = (musbp*(k-1)+  X)/k; Msbp = (Msbp*(k-1)+np.multiply(X,X))/k; ssbp = Msbp - np.multiply(musbp,musbp)

    
        a = datetime.now();CS = fmm.s_smpipeP(AS,BS);   b = datetime.now()
        print "Strassen float", b-a
        X = CD-CS
        print X.max()
        muss = (muss*(k-1)+  X)/k;   Mss = (Mss*(k-1)+np.multiply(X,X))/k ;   sss = Mss - np.multiply(muss,muss)

    


    for i in range(0,ssr.shape[0]):
        for j in range(0,ssr.shape[1]):
            ssr[i,j] = math.sqrt(ssr[i,j])
            ssw[i,j] = math.sqrt(ssw[i,j])
            ssb[i,j] = math.sqrt(ssb[i,j])            
            ssbt[i,j] = math.sqrt(ssbt[i,j])
            ssbp[i,j] = math.sqrt(ssbt[i,j])
            sss[i,j] = math.sqrt(sss[i,j])
            
            
        #heat([[0,ssr],[0,ssw],[0,ssb],[0,sss]])
            
    L = []
    L.append([ssr,'SGEMM',  ssr.max(),musr])
    L.append([ssw,'SWino',  ssw.max(),musw])    
    L.append([ssbt,'SWino-permutation',  ssbt.max(),musbt])    
    L.append([ssbp,'SWOpt-permutation',  ssbp.max(),musbp])    
    L.append([ssb,'SWOpt-PIPE',  ssb.max(),musb]) 
    L.append([sss,'SStra',  sss.max(),muss])
    
    
    
    return L



def Usage():
    print " temp -i 10 -s 5000"


def texTable(R,bottom,filename):
    
    F = open(filename,'w')
    
    hist = "hist_max"
    heat = "heat_max"

    header = """
\\begin{table}[hbt]
  \\footnotesize
  \\tbl{Range %s, Maximum Error, Maximum Heat, max/heat $\\sim$ 4 \\label{tab:%s}}{%s
    \\begin{tabular}{%s}
"""
    for sign in R:
        Methods = sorted(R[sign][heat].keys())

        MP = [] 
        M = [] 
        for m in Methods:
            if (m.find("Permute")>=0):
                MP.append(m)
            else:
                M.append(m)
                
        Sizes = sorted(R[sign][heat][Methods[0]].keys())
        
        columns = "r"
        top = "size"
        for m in M:
            columns += "l"
            top += " & " + m 
        top  +=  "\\\\ \\hline\n"
 
        h = header %(sign,sign,"%",columns)

        F.write(h + top+"\n")

        for s in Sizes:
            if (s < bottom):
                continue
            line = "%d"  % (s)  
            for m in M:
                val = "%1.2e/%1.2e/%1.2f" % ( R[sign][hist][m][s],
                                              R[sign][heat][m][s],
                                              R[sign][hist][m][s]/R[sign][heat][m][s])
                
                line += " & " + val
            F.write(line + "\\\\ \n")

                    

        top = "\\hline \\\\  size "
        for m in MP:
            
            top += " & " + m 
        top  +=  "\\\\ \n"

        F.write(top+"\n")
        for s in Sizes:
            if (s < bottom):
                continue
            line = "%d  "  % (s)  
            for m in MP:
                val = "%1.2e/%1.2e/%1.2f" % ( R[sign][hist][m][s],
                                              R[sign][heat][m][s],
                                              R[sign][hist][m][s]/R[sign][heat][m][s])
                
                line += " & " + val
            F.write(line + "\\\\ \n")
        F.write("\\hline \n")
        
        tail ="""\end{tabular}}
 \end{table}"""

        F.write(tail)
    F.close()

def readTable(filename,methods):
    import copy
    import re
    W = {}
    for m in methods:
        W[m]= {}
        
    
    R = {"[0,1]"  : {"heat_max": W,                "hist_max" : copy.deepcopy(W)}, 
         "[-1,1]" : {"heat_max": copy.deepcopy(W), "hist_max" : copy.deepcopy(W)} 
         } 

    F = open(filename)
    

    # [0,1]	##_heat_max	(21,21)	SSTRA-Permute	7.51545308113e-07	##_hist_max	(21,21)	SSTRA-Permute	2.86961641427e-06
    line = F.readline().strip()
    while (line):
        print line
        L = re.split("[\t ]##_",line)
        range = L[0]
        L.pop(0)
        
        for l in L:
            print "##",l
            if (l.find("heatM_max")>=0):
                print "skipping:", l
                continue
            
            m, size, name, value = l.split()
            print m,size,name,value
            n = eval(size)[0]
            H = R[range][m][name]
            H[n]=float(value)
            
            print n, H[n],R[range][m][name]
        line = F.readline().strip()
    
    F.close()
    return R

def computeN0(N,b):
    if N<=b:
        return N
    else: 
        return computeN0(N/2,b)
    

def plotMaxAll(R):
    S = ["[0,1]", "[-1,1]"]
    H = ["hist_max", "heat_max"] 
    X = [True, False]
    
    for s in S:
        for h in H: 
            for x in X:
                tail = "Xfactor.png"
                filename = h+s
                if (x):
                    tail = "log"+tail 
                    
                filename += tail
                plotMax(R,s,h,X=x,file=True,filename=filename)
                

    
def plotMax(R,range,heat,boundary=20,X=False,file=False,filename="multtmp.png"):
    import matplotlib.pyplot as plt        
    import math
    plt.rc('font',**{'size':32})
    plt.rc('legend',**{'fontsize':48})




    F = R[range][heat]
    Reference = R["[-1,1]"][heat]
    reference = R[range][heat]

#    lines = [ "b-o", 
#              "g--v",
#              "r-.^" ,	
#              "c:<" ,	
#              "m->" ,	
#              "y--1" ,	
#              "k-.2" ]	

    lines = [ "-", 
              "--",
              "-." ,	
              ":" ,	
              "-" ,	
              "--" ,	
              "-.", 
              ":"]	

    markers = [ 's',
                '*' ,
                'd' ,
                '1' ,
                'x' , 
                '+' , 
                'p' , 
                '>' ]
    colors  =  ['black',
             'black',
             'black',
             'black',
             'black',
             'black',
             'black',
             'black']
             
    
    print lines
    fig = plt.figure()
    ax = fig.add_subplot(111)
    j= 0

    
    for a in F.keys():
        
        items = sorted(F[a].items(), key=lambda item: item[0])
        x = [] 
        y = []
        k = 0
        #print items
        
        for i in items:
            if i[0]<= boundary :
                continue
            
            n  =  i[0]
            n0 = computeN0(n,boundary)
            l = math.log((0.0+n) /n0,2)
            x.append(n)
            
            if (a=="SGEMM"):
                ck = ck = i[1]/reference[a][n0]
            else:
                ck = i[1]/Reference[a][n0]

            
            ## ck = X^(n/n0) - >  log2 X  = n0/n log2 ck X = 2^(n0/n log2 ck)
            
            
            #
            if (X):
                ## X^l = ck
                w = 2** (math.log(ck,2)/(l))
            else:
                ## ck = X^(n/n0) - >  log2 X  = n0/n log2 ck X = 2^(n0/n log2 ck)
                w = 2**(math.log((ck+5*n/n0)/((n0+5)),2)/l)

            y.append(w)
            #t = i[1]
            
            
            
        #print x, y,  a
        #print lines
        #print j
        #print lines[j]
            
            #print a, items,x

        ax.plot(x, y,ls=lines[j],marker=markers[j],c=colors[j],linewidth=6,label=a,markersize=12)
        j = j+1

    ax.grid(True)

    ax.set_xlabel('N')
    if (X):
        ax.set_ylabel('(n/n0)^log X')
        ax.legend(loc='upper right')
    else:
        ax.set_ylabel("X^l")
        ax.legend(loc='lower right')
        
    plt.title(range+" "+heat,fontsize=32)
    #plt.yscale('log')

    if (not file):
        fig.show()
        return 
    F = plt.gcf()

# Now check everything with the defaults:
    DPI = F.get_dpi()
    print "DPI:", DPI
    DefaultSize = F.get_size_inches()
    F.set_size_inches(DefaultSize[0]*3, DefaultSize[1]*3)
    #fig.show();


    plt.savefig(filename,  format='png' )
    
    


def OneRun(K,T,S,methods, f = True):
    List = compareP(K,T,S,methods)
    #matplotlib.pyplot.rc('legend',**{'fontsize':12})

    post = "%dx%d%dTimes%sOrthogonal.png" %(T,T,K,S)
    heat(List,S,file=f,filename="HeatError"+post)
    heatM(List,S,file=f,filename="HeatMError"+post)
    histogram(List,S,file=f,filename="HistogramError"+post)
    plot(List,file=f,filename="TimeError"+post)
    del List


    

if __name__ == "__main__":

    import sys
    import os
    import getopt
    import string 

    Introduction = { 
        'GSGEMM' : fmm.s_mm_leaf_computationP,
        'SW' : fmm.s_wmP,
        'SWOPT' : fmm.s_BMOWRP,
        'SSTRA' : fmm.s_smulP,
        }
    
    Small = { 
        'GSGEMM'        : fmm.s_mm_leaf_computationP,
        'SW'            : fmm.s_wmP,
        'SWOPT'         : fmm.s_BMOWRP,
        'SSTRA'         : fmm.s_smulP,
        'SW-Permute'    : fmm.s_wmRP,
        'SW-4Permute'   : fmm.s_wmTRP,
        'SWOPT-Permute' : fmm.s_BMOWRRP,
        'SSTRA-Permute' : fmm.s_smulRP,
        }

    Ortho = { 
        'SW-4Permute'   : fmm.s_wmTRP,
        'SW-Permute' : fmm.s_wmRP,
        'SWOPT-Permute' : fmm.s_BMOWRRP,
        'SSTRA-Permute' : fmm.s_smulRP,
        }
    
    
    
    Big = { 
        'GSGEMM' : fmm.s_mm_leaf_computationP,
        'SW-Pipe' : fmm.s_wmpipeP,
        'SWOPT-Pipe' : fmm.s_BMOWR_PIPEP,
        'SSTRA-Pipe' : fmm.s_smpipeP,
        'SW-Permute' : fmm.s_wmRP,
        'SWOPT-Permute' : fmm.s_BMOWRRP,
        'SSTRA-Permute' : fmm.s_smulRP,
        }
    
    Goto = { 
        'GSGEMM' : fmm.s_mm_leaf_computationP,
        }

    Fast = { 
        'SW-Pipe'       : fmm.s_wmpipeP,
        'SW-Permute'    : fmm.s_wmRP,
        'SSTRA-Pipe' : fmm.s_smpipeP,
        'SSTRA-Permute' : fmm.s_smulRP,
        'SWOPT-Pipe' : fmm.s_BMOWR_PIPEP,
        'SWOPT-Permute' : fmm.s_BMOWRRP,
        }
    
    fast = { 
        'SW-Permute'    : fmm.s_wmRP,
        'SSTRA-Permute' : fmm.s_smulRP,
        'SWOPT-Permute' : fmm.s_BMOWRRP,
        'SW' : fmm.s_wmP,
        'SWOPT' : fmm.s_BMOWRP,
        'SSTRA' : fmm.s_smulP,
        }
    
    
    methods =  Small
    K = 10
    T = 2000
    S = "[-1,1]"
    Plotting = True
    onlyPlotting = False
    gotoonly = False
    try:
        opts, args = getopt.getopt(sys.argv[1:], "d:i:s:pr:m:", 
                                   ["help","iteration=","size=","plot","methods="])
    except getopt.error, msg:
        raise Usage(msg)

    
    for o, a in opts:
        if o == "-v":
            verbose = True
        elif o in ("-h", "--help"):
            Usage()
            sys.exit()
        elif o in ("-i", "--iteration"):
            K = long(a)
        elif o in ("-m", "--methods"):
            if (a=='S'):
                methods = Small;
            elif (a == "I"):
                methods = Introduction
            elif (a =="B") : 
                methods = Big
            elif (a =="f") :
                methods = fast
            elif (a =="F") : 
                methods = Fast
            elif (a =="G") :
                methods = Goto
            elif (a =="O") :
                methods = Ortho
            
        elif o in ("-s", "--size"):
            T = long(a)
        elif o == "-p":
            Plotting = False
        elif o == "-r":
            S = a
        elif o == "-d":
            import matplotlib
            matplotlib.use(a)
        else:
           print o, a 
           assert False, "unhandled option"
     

        #List = compare(K,T,S)



    OneRun(K,T,S,methods)
