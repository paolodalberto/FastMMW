
#Q = read.csv("results.gpus.slot3.txt",sep=",")
#Q = read.csv("results.2.txt",sep=",")
#Q = read.csv("gpufixed.txt",sep=",")
#Q = read.csv("3x3.out",sep=",")
#Q = read.csv("result.3.txt",sep=",")
#Q = read.csv("result5x5.out",sep=",")
#Q = read.csv("result8x8.txt",sep=",")
#Q = read.csv("result8x8_0-2.txt",sep=",")
#Q = read.csv("result.clblast.txt",sep=",")
#Q = read.csv("result.clblast.tuned.txt",sep=",")
#Q = read.csv("results.2019-07029.csv",sep=",")
Q = read.csv("roc.results.2.txt",sep=",")
#Q = read.csv("roc.results.viionly_2.txt",sep=",")
Types = unique(Q$TYPE)

C = c("blue",     "red",     "green",    "yellow", "black",
      "darkblue", "darkred", "darkgreen","yellow3","gray",
      'orange',    'brown',  'green',    'yellow4', 'pink' )
L = c( 1         , 2,         3,         4,         5,
       6,          1,         2,         3,         4,
       5,         6,           1,         2,          3 )



for (T in Types) {

    if (FILE)  png(paste(T,".png",sep=""))

    
    
    Single = subset(Q, TYPE==T)
    algs = unique(Single$NAME)

    
    #algs = algs[grepl("2x",algs)]
    algs = sort(algs)
    
    print(algs)
    print(Single)
    Algs =list()
    for (a in algs) {
        Algs[[a]] = subset(Single, NAME==a)
    }
    
    S = unique(Single$SIZE)
    print(c(min(Single$HOT),min(Single$COLD)))
    range = S*0.0 + min(min(Single$HOT),min(Single$COLD))
    range[1] = max(max(Single$COLD),max(Single$HOT))
    #C = c("darkblue","blue","turquoise", "darkred", "red", "orange","black")
    print(T)
    print(range)
    print(S)
    
    plot(S,range, type='n', col='white', main=T, ylab="GFLOPS", xlab="Size")

    i = 1
    for (a in algs) {
        w = Algs[[a]]	  
        str(w)
        if (length(w$SIZE)<=1) {	
          lines(w$SIZE, w$HOT, col=C[i],lty=L[i],lwd=2,type="p")
	}
	else {
	  lines(w$SIZE, w$HOT, col=C[i],lty=L[i],lwd=2)
	}
        i = i +1
    }
    legend("bottomright", legend=algs,col=C,lwd=3,lty=L)
    
    if (FILE) dev.off()
    else X11()
}

