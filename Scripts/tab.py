import sys
import os
import getopt
import string 
import subprocess
import re

class Usage(Exception):
    def __init__(self, msg):
        self.msg = msg

def main(argv=None):
    filename = ''
    names = []
    results = []
    if argv is None:
        argv = sys.argv
    try:
        try:
            opts, args = getopt.getopt(argv[1:], "h:f", ["help","filename="])
        except getopt.error, msg:
            raise Usage(msg)
        
        for o, a in opts:
            if o == "-v":
                verbose = True
            elif o in ("-h", "--help"):
                Usage()
                sys.exit()
            elif o in ("-o", "--output"):
                output = a
            elif o in ("-f", "--filename"):
                filename = a
            else:
                assert False, "unhandled option"

        if (filename != '' ):
            if string.find(filename,"*")>=0:
                files=os.listdir(".")
                
                for f in files:
                    if (re.match(filename,f)):
                        
                        name, result = readFile(f)
                        #print f,name
                        #print result
                        names.append(name)
                        results.append(result)
            else:
                name, result = readFile(filename)
                #print result 
                names.append(name)
                results.append(result)
                
        if (len(names)>0):
            printtabs(names,results)


    except Usage, err:
        print >>sys.stderr, err.msg
        print >>sys.stderr, "for help use --help"
        return 2


def printtabs(names, results):

    header = "size"
    for n in names:
        #print n
        header = header +"\t"+n
    print header

    i = 0
    for N in results[0]:
        line = N[0]
        
        for r in results:
            
            line = "%s\t%d" % (line,  r[i][1])
            
        print line
        i = i + 1
        

    

def readFile(filename):
    F = open(filename,'r')
    i = 0
    results = []

    size = F.readline()
    cold = F.readline()    
    hot = F.readline()
    
    name = ''
    
    while (size):
        #print size
        s = size.split(' ')
        N = long(s[-1])
        
        colds = cold.split(' ')
        
        if (name =='') :
            name = colds[1]
        C = float(colds[-1])*1000000
        
        hots = hot.split(' ')
        H=float(hots[-1])*1000000
        
        results.append([N,max(C,H)])
                


        size = F.readline()
        cold = F.readline()    
        hot = F.readline()
    
    
    F.close()
    return name,results


if __name__ == "__main__":
    sys.exit(main())
