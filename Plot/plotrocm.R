
#Q = read.csv("results.gpus.slot3.txt",sep=",")
#Q = read.csv("results.2.txt",sep=",")
#Q = read.csv("gpufixed.txt",sep=",")
#Q = read.csv("3x3.out",sep=",")
#Q = read.csv("result.3.txt",sep=",")
#Q = read.csv("result5x5.out",sep=",")
#Q = read.csv("result8x8.txt",sep=",")
#Q = read.csv("result8x8_0-2.txt",sep=",")
#Q = read.csv("TRPNG/result8x8_all.txt",sep=",")
#Q = read.csv("result8x8_0-4_all_epyc_MI25.txt",sep=",")
Q = read.csv("result.legacyrocm.txt",sep=",")

Types = unique(Q$TYPE)


##ALG = c('M7', 'M23', 'M49', 'M99', 'M343')

ALLALG =c('M7', 'M23')
ALG = c('M7', 'M23')
C = c("plum","purple",  "red","darkred","blue", "darkblue","gray", "black")
##gpu = c("vega","fijis","elles","fiji-elle")
##c("Vega", "-vega-","2xfiji-", "-Elles"))
##GPUS = list(c("Vega", "vega-", "Ellesmeres", "2xf"))

GPUS = list(c("vega-2xfiji","2xfiji-"))

for (gpu in GPUS) { 

for (T in Types) {

    ##if (T=='Single') ALG = c('M7')
    ##else ALG = c('M7', 'M23')      
    
    Single = subset(Q, TYPE==T & (grepl(ALG[1],NAME)|grepl(ALG[2],NAME)))
    ##Single = subset(Single, TYPE==T & (grepl(gpu[1],NAME)|grepl(gpu[2],NAME)|grepl(gpu[3],NAME)|grepl(gpu[4],NAME)))
    Single = subset(Single, TYPE==T & (grepl(gpu[1],NAME)|grepl(gpu[2],NAME)))


    if (FILE)  png(paste(T,paste(gpu[1],"-vs-",gpu[2],sep=""),".png",sep=""))
    


    Algs = list()
    algs = unique(Single$NAME)
    print(algs)

    
    
    S = unique(Single$SIZE)
    for (aq in algs) {
        
        Algs[[aq]] = subset(Single, grepl(aq,NAME))
    }

    
    range = S*0.0 + min(Single$HOT)
    range[1] = max(Single$HOT)
    

    
    plot(S,range, type='n', col='white', main=T, ylab="GFLOPS", xlab="Size")
    
    i = 1
    for (ab in algs) {
        print(c(ab,C[i]))
        w = Algs[[ab]]
        
        print(w$NAME)
        lines(w$SIZE, w$HOT, col=C[i],lwd=3)
        i = i +1
    }
    legend("topleft", legend=algs,col=C,lwd=3)
    
    if (FILE) dev.off()
    else X11()

}
}
