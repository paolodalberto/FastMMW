
#Q = read.csv("results.gpus.slot3.txt",sep=",")
Q = read.csv("results.2.txt",sep=",")
Q = read.csv("gpuredo.txt",sep=",")

Types = unique(Q$TYPE)



for (T in Types) {

    if (FILE)  png(paste(T,".png",sep=""))

    Single = subset(Q, TYPE==T)
    algs = unique(Single$NAME)


    Algs =list()
    for (a in algs) {
        Algs[[a]] = subset(Single, NAME==a)
    }
    
    S = unique(Single$SIZE)
    
    range = S*0.0 + min(Single$HOT)
    range[1] = max(Single$HOT)
    C = c("darkblue","darkgreen", "darkred", "blue","green","red", "turquoise", "yellow", "orange")


    plot(S,range, type='n', col='white', main=T, ylab="GFLOPS", xlab="Size")

    i = 1
    for (a in algs) {
        
        w = Algs[[a]]
        str(w)
        lines(w$SIZE, w$HOT, col=C[i])
        i = i +1
    }
    legend("bottomleft", legend=algs,col=C,lwd=3)
    
    if (FILE) dev.off()
    else X11()
}

