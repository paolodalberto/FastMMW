
#Q = read.csv("results.gpus.slot3.txt",sep=",")
#Q = read.csv("results.2.txt",sep=",")
#Q = read.csv("gpufixed.txt",sep=",")
#Q = read.csv("3x3.out",sep=",")
#Q = read.csv("result.3.txt",sep=",")
#Q = read.csv("result5x5.out",sep=",")
#Q = read.csv("result8x8.txt",sep=",")
#Q = read.csv("result8x8_0-2.txt",sep=",")
#Q = read.csv("result.clblast.txt",sep=",")
Q = read.csv("result.clblast.tuned.txt",sep=",")

Types = unique(Q$TYPE)

C = c("blue",     "red",     "green",    "yellow", "black",
      "darkblue", "darkred", "darkgreen","yellow3","gray",
      'azure',    'orange',  'green',    'yellow4', 'pink' )
L = c( 1         , 2,         3,         4,         5,
       6,          1,         2,         3,         4,
       5,         6,           1,         2,          3 )



for (T in Types) {

    if (FILE)  png(paste(T,".png",sep=""))

    
    
    Single = subset(Q, TYPE==T)
    algs = unique(Single$NAME)


    algs = algs[grepl("2x",algs)]
    algs = sort(algs)
    
    
    Algs =list()
    for (a in algs) {
        Algs[[a]] = subset(Single, NAME==a)
    }
    
    S = unique(Single$SIZE)
    
    range = S*0.0 + min(Single$HOT)
    range[1] = max(Single$HOT)
    #C = c("darkblue","blue","turquoise", "darkred", "red", "orange","black")

    
    plot(S,range, type='n', col='white', main=T, ylab="GFLOPS", xlab="Size")

    i = 1
    for (a in algs) {
        
        w = Algs[[a]]
        str(w)
        lines(w$SIZE, w$HOT, col=C[i],lty=L[i],lwd=2)
        i = i +1
    }
    legend("bottomright", legend=algs,col=C,lwd=3,lty=L)
    
    if (FILE) dev.off()
    else X11()
}

