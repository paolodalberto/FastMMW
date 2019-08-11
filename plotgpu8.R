
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
#Q = read.csv("result.clblast.txt",sep=",")
Q = read.csv("result.clblast.tuned.txt",sep=",")
Q = read.csv("results.2019-07029.csv",sep=",")
Types = unique(Q$TYPE)


##ALG = c('M7', 'M23', 'M49', 'M99', 'M343')
ALG = c('M7', 'M23', 'M49')


for (T in Types) {

    Single = subset(Q, TYPE==T)

    for (a in ALG) {
        if (FILE)  png(paste(T,a,".png",sep=""))
        SingleA = Single[grep(a,Single$NAME),]


        Algs = list()
        algs = unique(SingleA$NAME)
        S = unique(SingleA$SIZE)
        for (aq in algs) {
            Algs[[aq]] = subset(SingleA, NAME==aq)
        }

    
        range = S*0.0 + min(SingleA$HOT)
        range[1] = max(SingleA$HOT)
    
        C = c("darkblue","red", "orange","black","green","yellow","cyan")

        plot(S,range, type='n', col='white', main=paste(T,a), ylab="GFLOPS", xlab="Size")

        i = 1
        for (ab in algs) {
        
            w = Algs[[ab]]
            str(w)
            lines(w$SIZE, w$HOT, col=C[i])
            i = i +1
        }
        legend("topleft", legend=algs,col=C,lwd=3)
    
        if (FILE) dev.off()
        else X11()
    }
}

