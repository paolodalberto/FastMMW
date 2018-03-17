
s_dcmulR <- function(a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;

    nc   = length(B[1,]);
    mc   = length(A[,1]) ;
    C = array(0.0, dim=c(mc,nc))
    c = 1.0
    n = 0
    output <- .C("s_dcmulB",
                 betac = as.single(c),
                 transc = as.integer(n),
                 mc =as.integer(mc),
                 nc =as.integer(nc),
                 Mc =as.integer(mc),
                 Nc =as.integer(nc),
                 datac = as.single(C),		
                 betaa = as.single(a),
                 transa = as.integer(n),
                 ma =as.integer(ma),
                 na =as.integer(na),
                 Ma =as.integer(ma),
                 Na =as.integer(na),
                 dataa = as.single(A),		
                 betab = as.single(b),
                 transb = as.integer(n),
                 mb =as.integer(mb),
                 nb =as.integer(nb),
                 Mb =as.integer(mb),
                 Nb =as.integer(nb),
                 datab = as.single(B)
                 )

    array(output$datac,dim=dim(C))
}

s_mulR <- function(a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;

    nc   = length(B[1,]);
    mc   = length(A[,1]) ;
    C = array(0.0, dim=c(mc,nc))
    c = 1.0
    n = 0
    output <- .C("s_mulB",
                 betac = as.single(c),
                 transc = as.integer(n),
                 mc =as.integer(mc),
                 nc =as.integer(nc),
                 Mc =as.integer(mc),
                 Nc =as.integer(nc),
                 datac = as.single(C),		
                 betaa = as.single(a),
                 transa = as.integer(n),
                 ma =as.integer(ma),
                 na =as.integer(na),
                 Ma =as.integer(ma),
                 Na =as.integer(na),
                 dataa = as.single(A),		
                 betab = as.single(b),
                 transb = as.integer(n),
                 mb =as.integer(mb),
                 nb =as.integer(nb),
                 Mb =as.integer(mb),
                 Nb =as.integer(nb),
                 datab = as.single(B)
                 )

    array(output$datac,dim=dim(C))
}

s_mulptR <- function(a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;

    nc   = length(B[1,]);
    mc   = length(A[,1]) ;
    C = array(0.0, dim=c(mc,nc))
    c = 1.0
    n = 0
    output <- .C("s_mulptB",
                 betac = as.single(c),
                 transc = as.integer(n),
                 mc =as.integer(mc),
                 nc =as.integer(nc),
                 Mc =as.integer(mc),
                 Nc =as.integer(nc),
                 datac = as.single(C),		
                 betaa = as.single(a),
                 transa = as.integer(n),
                 ma =as.integer(ma),
                 na =as.integer(na),
                 Ma =as.integer(ma),
                 Na =as.integer(na),
                 dataa = as.single(A),		
                 betab = as.single(b),
                 transb = as.integer(n),
                 mb =as.integer(mb),
                 nb =as.integer(nb),
                 Mb =as.integer(mb),
                 Nb =as.integer(nb),
                 datab = as.single(B)
                 )

    array(output$datac,dim=dim(C))
}

s_maddR <- function(c,C,a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;
    nc   = length(C[1,]);
    mc   = length(C[,1]) ;

    n = 0
  
   output <- .C("s_maddB",
     betac = as.single(c),
     transc = as.integer(n),
     mc =as.integer(mc),
     nc =as.integer(nc),
     Mc =as.integer(mc),
     Nc =as.integer(nc),
     datac = as.single(C),		
     betaa = as.single(a),
     transa = as.integer(n),
     ma =as.integer(ma),
     na =as.integer(na),
     Ma =as.integer(ma),
     Na =as.integer(na),
     dataa = as.single(A),		
     betab = as.single(b),
     transb = as.integer(n),
     mb =as.integer(mb),
     nb =as.integer(nb),
     Mb =as.integer(mb),
     Nb =as.integer(nb),
     datab = as.single(B)

     )

    array(output$datac,dim=dim(C))
}



s_saddmulR <- function(c,C,a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;
    nc   = length(C[1,]);
    mc   = length(C[,1]) ;

    n = 0
  
   output <- .C("s_saddmulB",
     betac = as.single(c),
     transc = as.integer(n),
     mc =as.integer(mc),
     nc =as.integer(nc),
     Mc =as.integer(mc),
     Nc =as.integer(nc),
     datac = as.single(C),		
     betaa = as.single(a),
     transa = as.integer(n),
     ma =as.integer(ma),
     na =as.integer(na),
     Ma =as.integer(ma),
     Na =as.integer(na),
     dataa = as.single(A),		
     betab = as.single(b),
     transb = as.integer(n),
     mb =as.integer(mb),
     nb =as.integer(nb),
     Mb =as.integer(mb),
     Nb =as.integer(nb),
     datab = as.single(B)

     )

    array(output$datac,dim=dim(C))
}



s_smulR <- function(a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;

    nc   = length(B[1,]);
    mc   = length(A[,1]) ;
    C = array(0.0, dim=c(mc,nc))
    c = 1.0
    n = 0
    output <- .C("s_smulB",
                 betac = as.single(c),
                 transc = as.integer(n),
                 mc =as.integer(mc),
                 nc =as.integer(nc),
                 Mc =as.integer(mc),
                 Nc =as.integer(nc),
                 datac = as.single(C),		
                 betaa = as.single(a),
                 transa = as.integer(n),
                 ma =as.integer(ma),
                 na =as.integer(na),
                 Ma =as.integer(ma),
                 Na =as.integer(na),
                 dataa = as.single(A),		
                 betab = as.single(b),
                 transb = as.integer(n),
                 mb =as.integer(mb),
                 nb =as.integer(nb),
                 Mb =as.integer(mb),
                 Nb =as.integer(nb),
                 datab = as.single(B)
                 )

    array(output$datac,dim=dim(C))
}

s_wmulR <- function(a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;

    nc   = length(B[1,]);
    mc   = length(A[,1]) ;
    C = array(0.0, dim=c(mc,nc))
    c = 1.0
    n = 0
    output <- .C("s_wmulB",
                 betac = as.single(c),
                 transc = as.integer(n),
                 mc =as.integer(mc),
                 nc =as.integer(nc),
                 Mc =as.integer(mc),
                 Nc =as.integer(nc),
                 datac = as.single(C),		
                 betaa = as.single(a),
                 transa = as.integer(n),
                 ma =as.integer(ma),
                 na =as.integer(na),
                 Ma =as.integer(ma),
                 Na =as.integer(na),
                 dataa = as.single(A),		
                 betab = as.single(b),
                 transb = as.integer(n),
                 mb =as.integer(mb),
                 nb =as.integer(nb),
                 Mb =as.integer(mb),
                 Nb =as.integer(nb),
                 datab = as.single(B)
                 )

    array(output$datac,dim=dim(C))
}

s_waddmulR <- function(c,C,a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;
    nc   = length(C[1,]);
    mc   = length(C[,1]) ;

    n = 0
  
   output <- .C("s_waddmulB",
     betac = as.single(c),
     transc = as.integer(n),
     mc =as.integer(mc),
     nc =as.integer(nc),
     Mc =as.integer(mc),
     Nc =as.integer(nc),
     datac = as.single(C),		
     betaa = as.single(a),
     transa = as.integer(n),
     ma =as.integer(ma),
     na =as.integer(na),
     Ma =as.integer(ma),
     Na =as.integer(na),
     dataa = as.single(A),		
     betab = as.single(b),
     transb = as.integer(n),
     mb =as.integer(mb),
     nb =as.integer(nb),
     Mb =as.integer(mb),
     Nb =as.integer(nb),
     datab = as.single(B)

     )

    array(output$datac,dim=dim(C))
}



s_wmR <- function(a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;

    nc   = length(B[1,]);
    mc   = length(A[,1]) ;
    C = array(0.0, dim=c(mc,nc))
    c = 1.0
    n = 0
    output <- .C("s_wmB",
                 betac = as.single(c),
                 transc = as.integer(n),
                 mc =as.integer(mc),
                 nc =as.integer(nc),
                 Mc =as.integer(mc),
                 Nc =as.integer(nc),
                 datac = as.single(C),		
                 betaa = as.single(a),
                 transa = as.integer(n),
                 ma =as.integer(ma),
                 na =as.integer(na),
                 Ma =as.integer(ma),
                 Na =as.integer(na),
                 dataa = as.single(A),		
                 betab = as.single(b),
                 transb = as.integer(n),
                 mb =as.integer(mb),
                 nb =as.integer(nb),
                 Mb =as.integer(mb),
                 Nb =as.integer(nb),
                 datab = as.single(B)
                 )

    array(output$datac,dim=dim(C))
}

s_wmaddR <- function(c,C,a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;
    nc   = length(C[1,]);
    mc   = length(C[,1]) ;

    n = 0
  
   output <- .C("s_wmaddB",
     betac = as.single(c),
     transc = as.integer(n),
     mc =as.integer(mc),
     nc =as.integer(nc),
     Mc =as.integer(mc),
     Nc =as.integer(nc),
     datac = as.single(C),		
     betaa = as.single(a),
     transa = as.integer(n),
     ma =as.integer(ma),
     na =as.integer(na),
     Ma =as.integer(ma),
     Na =as.integer(na),
     dataa = as.single(A),		
     betab = as.single(b),
     transb = as.integer(n),
     mb =as.integer(mb),
     nb =as.integer(nb),
     Mb =as.integer(mb),
     Nb =as.integer(nb),
     datab = as.single(B)

     )

    array(output$datac,dim=dim(C))
}



s_adaptive_smulR <- function(a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;

    nc   = length(B[1,]);
    mc   = length(A[,1]) ;
    C = array(0.0, dim=c(mc,nc))
    c = 1.0
    n = 0
    output <- .C("s_adaptive_smulB",
                 betac = as.single(c),
                 transc = as.integer(n),
                 mc =as.integer(mc),
                 nc =as.integer(nc),
                 Mc =as.integer(mc),
                 Nc =as.integer(nc),
                 datac = as.single(C),		
                 betaa = as.single(a),
                 transa = as.integer(n),
                 ma =as.integer(ma),
                 na =as.integer(na),
                 Ma =as.integer(ma),
                 Na =as.integer(na),
                 dataa = as.single(A),		
                 betab = as.single(b),
                 transb = as.integer(n),
                 mb =as.integer(mb),
                 nb =as.integer(nb),
                 Mb =as.integer(mb),
                 Nb =as.integer(nb),
                 datab = as.single(B)
                 )

    array(output$datac,dim=dim(C))
}

s_omulR <- function(a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;

    nc   = length(B[1,]);
    mc   = length(A[,1]) ;
    C = array(0.0, dim=c(mc,nc))
    c = 1.0
    n = 0
    output <- .C("s_omulB",
                 betac = as.single(c),
                 transc = as.integer(n),
                 mc =as.integer(mc),
                 nc =as.integer(nc),
                 Mc =as.integer(mc),
                 Nc =as.integer(nc),
                 datac = as.single(C),		
                 betaa = as.single(a),
                 transa = as.integer(n),
                 ma =as.integer(ma),
                 na =as.integer(na),
                 Ma =as.integer(ma),
                 Na =as.integer(na),
                 dataa = as.single(A),		
                 betab = as.single(b),
                 transb = as.integer(n),
                 mb =as.integer(mb),
                 nb =as.integer(nb),
                 Mb =as.integer(mb),
                 Nb =as.integer(nb),
                 datab = as.single(B)
                 )

    array(output$datac,dim=dim(C))
}

s_oaddmulR <- function(c,C,a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;
    nc   = length(C[1,]);
    mc   = length(C[,1]) ;

    n = 0
  
   output <- .C("s_oaddmulB",
     betac = as.single(c),
     transc = as.integer(n),
     mc =as.integer(mc),
     nc =as.integer(nc),
     Mc =as.integer(mc),
     Nc =as.integer(nc),
     datac = as.single(C),		
     betaa = as.single(a),
     transa = as.integer(n),
     ma =as.integer(ma),
     na =as.integer(na),
     Ma =as.integer(ma),
     Na =as.integer(na),
     dataa = as.single(A),		
     betab = as.single(b),
     transb = as.integer(n),
     mb =as.integer(mb),
     nb =as.integer(nb),
     Mb =as.integer(mb),
     Nb =as.integer(nb),
     datab = as.single(B)

     )

    array(output$datac,dim=dim(C))
}



s_owmulR <- function(a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;

    nc   = length(B[1,]);
    mc   = length(A[,1]) ;
    C = array(0.0, dim=c(mc,nc))
    c = 1.0
    n = 0
    output <- .C("s_owmulB",
                 betac = as.single(c),
                 transc = as.integer(n),
                 mc =as.integer(mc),
                 nc =as.integer(nc),
                 Mc =as.integer(mc),
                 Nc =as.integer(nc),
                 datac = as.single(C),		
                 betaa = as.single(a),
                 transa = as.integer(n),
                 ma =as.integer(ma),
                 na =as.integer(na),
                 Ma =as.integer(ma),
                 Na =as.integer(na),
                 dataa = as.single(A),		
                 betab = as.single(b),
                 transb = as.integer(n),
                 mb =as.integer(mb),
                 nb =as.integer(nb),
                 Mb =as.integer(mb),
                 Nb =as.integer(nb),
                 datab = as.single(B)
                 )

    array(output$datac,dim=dim(C))
}

s_owaddmulR <- function(c,C,a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;
    nc   = length(C[1,]);
    mc   = length(C[,1]) ;

    n = 0
  
   output <- .C("s_owaddmulB",
     betac = as.single(c),
     transc = as.integer(n),
     mc =as.integer(mc),
     nc =as.integer(nc),
     Mc =as.integer(mc),
     Nc =as.integer(nc),
     datac = as.single(C),		
     betaa = as.single(a),
     transa = as.integer(n),
     ma =as.integer(ma),
     na =as.integer(na),
     Ma =as.integer(ma),
     Na =as.integer(na),
     dataa = as.single(A),		
     betab = as.single(b),
     transb = as.integer(n),
     mb =as.integer(mb),
     nb =as.integer(nb),
     Mb =as.integer(mb),
     Nb =as.integer(nb),
     datab = as.single(B)

     )

    array(output$datac,dim=dim(C))
}



s_bmR <- function(a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;

    nc   = length(B[1,]);
    mc   = length(A[,1]) ;
    C = array(0.0, dim=c(mc,nc))
    c = 1.0
    n = 0
    output <- .C("s_bmB",
                 betac = as.single(c),
                 transc = as.integer(n),
                 mc =as.integer(mc),
                 nc =as.integer(nc),
                 Mc =as.integer(mc),
                 Nc =as.integer(nc),
                 datac = as.single(C),		
                 betaa = as.single(a),
                 transa = as.integer(n),
                 ma =as.integer(ma),
                 na =as.integer(na),
                 Ma =as.integer(ma),
                 Na =as.integer(na),
                 dataa = as.single(A),		
                 betab = as.single(b),
                 transb = as.integer(n),
                 mb =as.integer(mb),
                 nb =as.integer(nb),
                 Mb =as.integer(mb),
                 Nb =as.integer(nb),
                 datab = as.single(B)
                 )

    array(output$datac,dim=dim(C))
}

s_bmaddR <- function(c,C,a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;
    nc   = length(C[1,]);
    mc   = length(C[,1]) ;

    n = 0
  
   output <- .C("s_bmaddB",
     betac = as.single(c),
     transc = as.integer(n),
     mc =as.integer(mc),
     nc =as.integer(nc),
     Mc =as.integer(mc),
     Nc =as.integer(nc),
     datac = as.single(C),		
     betaa = as.single(a),
     transa = as.integer(n),
     ma =as.integer(ma),
     na =as.integer(na),
     Ma =as.integer(ma),
     Na =as.integer(na),
     dataa = as.single(A),		
     betab = as.single(b),
     transb = as.integer(n),
     mb =as.integer(mb),
     nb =as.integer(nb),
     Mb =as.integer(mb),
     Nb =as.integer(nb),
     datab = as.single(B)

     )

    array(output$datac,dim=dim(C))
}



s_ptaddmulR <- function(c,C,a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;
    nc   = length(C[1,]);
    mc   = length(C[,1]) ;

    n = 0
  
   output <- .C("s_ptaddmulB",
     betac = as.single(c),
     transc = as.integer(n),
     mc =as.integer(mc),
     nc =as.integer(nc),
     Mc =as.integer(mc),
     Nc =as.integer(nc),
     datac = as.single(C),		
     betaa = as.single(a),
     transa = as.integer(n),
     ma =as.integer(ma),
     na =as.integer(na),
     Ma =as.integer(ma),
     Na =as.integer(na),
     dataa = as.single(A),		
     betab = as.single(b),
     transb = as.integer(n),
     mb =as.integer(mb),
     nb =as.integer(nb),
     Mb =as.integer(mb),
     Nb =as.integer(nb),
     datab = as.single(B)

     )

    array(output$datac,dim=dim(C))
}



s_wmpipeR <- function(a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;

    nc   = length(B[1,]);
    mc   = length(A[,1]) ;
    C = array(0.0, dim=c(mc,nc))
    c = 1.0
    n = 0
    output <- .C("s_wmpipeB",
                 betac = as.single(c),
                 transc = as.integer(n),
                 mc =as.integer(mc),
                 nc =as.integer(nc),
                 Mc =as.integer(mc),
                 Nc =as.integer(nc),
                 datac = as.single(C),		
                 betaa = as.single(a),
                 transa = as.integer(n),
                 ma =as.integer(ma),
                 na =as.integer(na),
                 Ma =as.integer(ma),
                 Na =as.integer(na),
                 dataa = as.single(A),		
                 betab = as.single(b),
                 transb = as.integer(n),
                 mb =as.integer(mb),
                 nb =as.integer(nb),
                 Mb =as.integer(mb),
                 Nb =as.integer(nb),
                 datab = as.single(B)
                 )

    array(output$datac,dim=dim(C))
}

s_wmaddpipeR <- function(c,C,a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;
    nc   = length(C[1,]);
    mc   = length(C[,1]) ;

    n = 0
  
   output <- .C("s_wmaddpipeB",
     betac = as.single(c),
     transc = as.integer(n),
     mc =as.integer(mc),
     nc =as.integer(nc),
     Mc =as.integer(mc),
     Nc =as.integer(nc),
     datac = as.single(C),		
     betaa = as.single(a),
     transa = as.integer(n),
     ma =as.integer(ma),
     na =as.integer(na),
     Ma =as.integer(ma),
     Na =as.integer(na),
     dataa = as.single(A),		
     betab = as.single(b),
     transb = as.integer(n),
     mb =as.integer(mb),
     nb =as.integer(nb),
     Mb =as.integer(mb),
     Nb =as.integer(nb),
     datab = as.single(B)

     )

    array(output$datac,dim=dim(C))
}



s_bmpipeR <- function(a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;

    nc   = length(B[1,]);
    mc   = length(A[,1]) ;
    C = array(0.0, dim=c(mc,nc))
    c = 1.0
    n = 0
    output <- .C("s_bmpipeB",
                 betac = as.single(c),
                 transc = as.integer(n),
                 mc =as.integer(mc),
                 nc =as.integer(nc),
                 Mc =as.integer(mc),
                 Nc =as.integer(nc),
                 datac = as.single(C),		
                 betaa = as.single(a),
                 transa = as.integer(n),
                 ma =as.integer(ma),
                 na =as.integer(na),
                 Ma =as.integer(ma),
                 Na =as.integer(na),
                 dataa = as.single(A),		
                 betab = as.single(b),
                 transb = as.integer(n),
                 mb =as.integer(mb),
                 nb =as.integer(nb),
                 Mb =as.integer(mb),
                 Nb =as.integer(nb),
                 datab = as.single(B)
                 )

    array(output$datac,dim=dim(C))
}

s_bmaddpipeR <- function(c,C,a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;
    nc   = length(C[1,]);
    mc   = length(C[,1]) ;

    n = 0
  
   output <- .C("s_bmaddpipeB",
     betac = as.single(c),
     transc = as.integer(n),
     mc =as.integer(mc),
     nc =as.integer(nc),
     Mc =as.integer(mc),
     Nc =as.integer(nc),
     datac = as.single(C),		
     betaa = as.single(a),
     transa = as.integer(n),
     ma =as.integer(ma),
     na =as.integer(na),
     Ma =as.integer(ma),
     Na =as.integer(na),
     dataa = as.single(A),		
     betab = as.single(b),
     transb = as.integer(n),
     mb =as.integer(mb),
     nb =as.integer(nb),
     Mb =as.integer(mb),
     Nb =as.integer(nb),
     datab = as.single(B)

     )

    array(output$datac,dim=dim(C))
}



s_smpipeR <- function(a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;

    nc   = length(B[1,]);
    mc   = length(A[,1]) ;
    C = array(0.0, dim=c(mc,nc))
    c = 1.0
    n = 0
    output <- .C("s_smpipeB",
                 betac = as.single(c),
                 transc = as.integer(n),
                 mc =as.integer(mc),
                 nc =as.integer(nc),
                 Mc =as.integer(mc),
                 Nc =as.integer(nc),
                 datac = as.single(C),		
                 betaa = as.single(a),
                 transa = as.integer(n),
                 ma =as.integer(ma),
                 na =as.integer(na),
                 Ma =as.integer(ma),
                 Na =as.integer(na),
                 dataa = as.single(A),		
                 betab = as.single(b),
                 transb = as.integer(n),
                 mb =as.integer(mb),
                 nb =as.integer(nb),
                 Mb =as.integer(mb),
                 Nb =as.integer(nb),
                 datab = as.single(B)
                 )

    array(output$datac,dim=dim(C))
}

s_smaddpipeR <- function(c,C,a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;
    nc   = length(C[1,]);
    mc   = length(C[,1]) ;

    n = 0
  
   output <- .C("s_smaddpipeB",
     betac = as.single(c),
     transc = as.integer(n),
     mc =as.integer(mc),
     nc =as.integer(nc),
     Mc =as.integer(mc),
     Nc =as.integer(nc),
     datac = as.single(C),		
     betaa = as.single(a),
     transa = as.integer(n),
     ma =as.integer(ma),
     na =as.integer(na),
     Ma =as.integer(ma),
     Na =as.integer(na),
     dataa = as.single(A),		
     betab = as.single(b),
     transb = as.integer(n),
     mb =as.integer(mb),
     nb =as.integer(nb),
     Mb =as.integer(mb),
     Nb =as.integer(nb),
     datab = as.single(B)

     )

    array(output$datac,dim=dim(C))
}



s_RmulR <- function(a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;

    nc   = length(B[1,]);
    mc   = length(A[,1]) ;
    C = array(0.0, dim=c(mc,nc))
    c = 1.0
    n = 0
    output <- .C("s_RmulB",
                 betac = as.single(c),
                 transc = as.integer(n),
                 mc =as.integer(mc),
                 nc =as.integer(nc),
                 Mc =as.integer(mc),
                 Nc =as.integer(nc),
                 datac = as.single(C),		
                 betaa = as.single(a),
                 transa = as.integer(n),
                 ma =as.integer(ma),
                 na =as.integer(na),
                 Ma =as.integer(ma),
                 Na =as.integer(na),
                 dataa = as.single(A),		
                 betab = as.single(b),
                 transb = as.integer(n),
                 mb =as.integer(mb),
                 nb =as.integer(nb),
                 Mb =as.integer(mb),
                 Nb =as.integer(nb),
                 datab = as.single(B)
                 )

    array(output$datac,dim=dim(C))
}

s_adaptive_wmR <- function(a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;

    nc   = length(B[1,]);
    mc   = length(A[,1]) ;
    C = array(0.0, dim=c(mc,nc))
    c = 1.0
    n = 0
    output <- .C("s_adaptive_wmB",
                 betac = as.single(c),
                 transc = as.integer(n),
                 mc =as.integer(mc),
                 nc =as.integer(nc),
                 Mc =as.integer(mc),
                 Nc =as.integer(nc),
                 datac = as.single(C),		
                 betaa = as.single(a),
                 transa = as.integer(n),
                 ma =as.integer(ma),
                 na =as.integer(na),
                 Ma =as.integer(ma),
                 Na =as.integer(na),
                 dataa = as.single(A),		
                 betab = as.single(b),
                 transb = as.integer(n),
                 mb =as.integer(mb),
                 nb =as.integer(nb),
                 Mb =as.integer(mb),
                 Nb =as.integer(nb),
                 datab = as.single(B)
                 )

    array(output$datac,dim=dim(C))
}

s_BMADD_PIPER <- function(c,C,a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;
    nc   = length(C[1,]);
    mc   = length(C[,1]) ;

    n = 0
  
   output <- .C("s_BMADD_PIPEB",
     betac = as.single(c),
     transc = as.integer(n),
     mc =as.integer(mc),
     nc =as.integer(nc),
     Mc =as.integer(mc),
     Nc =as.integer(nc),
     datac = as.single(C),		
     betaa = as.single(a),
     transa = as.integer(n),
     ma =as.integer(ma),
     na =as.integer(na),
     Ma =as.integer(ma),
     Na =as.integer(na),
     dataa = as.single(A),		
     betab = as.single(b),
     transb = as.integer(n),
     mb =as.integer(mb),
     nb =as.integer(nb),
     Mb =as.integer(mb),
     Nb =as.integer(nb),
     datab = as.single(B)

     )

    array(output$datac,dim=dim(C))
}



s_BMADDR <- function(c,C,a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;
    nc   = length(C[1,]);
    mc   = length(C[,1]) ;

    n = 0
  
   output <- .C("s_BMADDB",
     betac = as.single(c),
     transc = as.integer(n),
     mc =as.integer(mc),
     nc =as.integer(nc),
     Mc =as.integer(mc),
     Nc =as.integer(nc),
     datac = as.single(C),		
     betaa = as.single(a),
     transa = as.integer(n),
     ma =as.integer(ma),
     na =as.integer(na),
     Ma =as.integer(ma),
     Na =as.integer(na),
     dataa = as.single(A),		
     betab = as.single(b),
     transb = as.integer(n),
     mb =as.integer(mb),
     nb =as.integer(nb),
     Mb =as.integer(mb),
     Nb =as.integer(nb),
     datab = as.single(B)

     )

    array(output$datac,dim=dim(C))
}



s_BMOWR_PIPER <- function(a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;

    nc   = length(B[1,]);
    mc   = length(A[,1]) ;
    C = array(0.0, dim=c(mc,nc))
    c = 1.0
    n = 0
    output <- .C("s_BMOWR_PIPEB",
                 betac = as.single(c),
                 transc = as.integer(n),
                 mc =as.integer(mc),
                 nc =as.integer(nc),
                 Mc =as.integer(mc),
                 Nc =as.integer(nc),
                 datac = as.single(C),		
                 betaa = as.single(a),
                 transa = as.integer(n),
                 ma =as.integer(ma),
                 na =as.integer(na),
                 Ma =as.integer(ma),
                 Na =as.integer(na),
                 dataa = as.single(A),		
                 betab = as.single(b),
                 transb = as.integer(n),
                 mb =as.integer(mb),
                 nb =as.integer(nb),
                 Mb =as.integer(mb),
                 Nb =as.integer(nb),
                 datab = as.single(B)
                 )

    array(output$datac,dim=dim(C))
}

s_BMOWRR <- function(a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;

    nc   = length(B[1,]);
    mc   = length(A[,1]) ;
    C = array(0.0, dim=c(mc,nc))
    c = 1.0
    n = 0
    output <- .C("s_BMOWRB",
                 betac = as.single(c),
                 transc = as.integer(n),
                 mc =as.integer(mc),
                 nc =as.integer(nc),
                 Mc =as.integer(mc),
                 Nc =as.integer(nc),
                 datac = as.single(C),		
                 betaa = as.single(a),
                 transa = as.integer(n),
                 ma =as.integer(ma),
                 na =as.integer(na),
                 Ma =as.integer(ma),
                 Na =as.integer(na),
                 dataa = as.single(A),		
                 betab = as.single(b),
                 transb = as.integer(n),
                 mb =as.integer(mb),
                 nb =as.integer(nb),
                 Mb =as.integer(mb),
                 Nb =as.integer(nb),
                 datab = as.single(B)
                 )

    array(output$datac,dim=dim(C))
}

d_dcmulR <- function(a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;

    nc   = length(B[1,]);
    mc   = length(A[,1]) ;
    C = array(0.0, dim=c(mc,nc))
    c = 1.0
    n = 0
    output <- .C("d_dcmulB",
                 betac = as.double(c),
                 transc = as.integer(n),
                 mc =as.integer(mc),
                 nc =as.integer(nc),
                 Mc =as.integer(mc),
                 Nc =as.integer(nc),
                 datac = as.double(C),		
                 betaa = as.double(a),
                 transa = as.integer(n),
                 ma =as.integer(ma),
                 na =as.integer(na),
                 Ma =as.integer(ma),
                 Na =as.integer(na),
                 dataa = as.double(A),		
                 betab = as.double(b),
                 transb = as.integer(n),
                 mb =as.integer(mb),
                 nb =as.integer(nb),
                 Mb =as.integer(mb),
                 Nb =as.integer(nb),
                 datab = as.double(B),DUP=FALSE
                 )

    array(output$datac,dim=dim(C))
}

d_mulR <- function(a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;

    nc   = length(B[1,]);
    mc   = length(A[,1]) ;
    C = array(0.0, dim=c(mc,nc))
    c = 1.0
    n = 0
    output <- .C("d_mulB",
                 betac = as.double(c),
                 transc = as.integer(n),
                 mc =as.integer(mc),
                 nc =as.integer(nc),
                 Mc =as.integer(mc),
                 Nc =as.integer(nc),
                 datac = as.double(C),		
                 betaa = as.double(a),
                 transa = as.integer(n),
                 ma =as.integer(ma),
                 na =as.integer(na),
                 Ma =as.integer(ma),
                 Na =as.integer(na),
                 dataa = as.double(A),		
                 betab = as.double(b),
                 transb = as.integer(n),
                 mb =as.integer(mb),
                 nb =as.integer(nb),
                 Mb =as.integer(mb),
                 Nb =as.integer(nb),
                 datab = as.double(B),DUP=FALSE
                 )

    array(output$datac,dim=dim(C))
}

d_mulptR <- function(a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;

    nc   = length(B[1,]);
    mc   = length(A[,1]) ;
    C = array(0.0, dim=c(mc,nc))
    c = 1.0
    n = 0
    output <- .C("d_mulptB",
                 betac = as.double(c),
                 transc = as.integer(n),
                 mc =as.integer(mc),
                 nc =as.integer(nc),
                 Mc =as.integer(mc),
                 Nc =as.integer(nc),
                 datac = as.double(C),		
                 betaa = as.double(a),
                 transa = as.integer(n),
                 ma =as.integer(ma),
                 na =as.integer(na),
                 Ma =as.integer(ma),
                 Na =as.integer(na),
                 dataa = as.double(A),		
                 betab = as.double(b),
                 transb = as.integer(n),
                 mb =as.integer(mb),
                 nb =as.integer(nb),
                 Mb =as.integer(mb),
                 Nb =as.integer(nb),
                 datab = as.double(B),DUP=FALSE
                 )

    array(output$datac,dim=dim(C))
}

d_maddR <- function(c,C,a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;
    nc   = length(C[1,]);
    mc   = length(C[,1]) ;

    n = 0
  
   output <- .C("d_maddB",
     betac = as.double(c),
     transc = as.integer(n),
     mc =as.integer(mc),
     nc =as.integer(nc),
     Mc =as.integer(mc),
     Nc =as.integer(nc),
     datac = as.double(C),		
     betaa = as.double(a),
     transa = as.integer(n),
     ma =as.integer(ma),
     na =as.integer(na),
     Ma =as.integer(ma),
     Na =as.integer(na),
     dataa = as.double(A),		
     betab = as.double(b),
     transb = as.integer(n),
     mb =as.integer(mb),
     nb =as.integer(nb),
     Mb =as.integer(mb),
     Nb =as.integer(nb),
     datab = as.double(B),DUP=FALSE

     )

    array(output$datac,dim=dim(C))
}



d_saddmulR <- function(c,C,a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;
    nc   = length(C[1,]);
    mc   = length(C[,1]) ;

    n = 0
  
   output <- .C("d_saddmulB",
     betac = as.double(c),
     transc = as.integer(n),
     mc =as.integer(mc),
     nc =as.integer(nc),
     Mc =as.integer(mc),
     Nc =as.integer(nc),
     datac = as.double(C),		
     betaa = as.double(a),
     transa = as.integer(n),
     ma =as.integer(ma),
     na =as.integer(na),
     Ma =as.integer(ma),
     Na =as.integer(na),
     dataa = as.double(A),		
     betab = as.double(b),
     transb = as.integer(n),
     mb =as.integer(mb),
     nb =as.integer(nb),
     Mb =as.integer(mb),
     Nb =as.integer(nb),
     datab = as.double(B),DUP=FALSE

     )

    array(output$datac,dim=dim(C))
}



d_smulR <- function(a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;

    nc   = length(B[1,]);
    mc   = length(A[,1]) ;
    C = array(0.0, dim=c(mc,nc))
    c = 1.0
    n = 0
    output <- .C("d_smulB",
                 betac = as.double(c),
                 transc = as.integer(n),
                 mc =as.integer(mc),
                 nc =as.integer(nc),
                 Mc =as.integer(mc),
                 Nc =as.integer(nc),
                 datac = as.double(C),		
                 betaa = as.double(a),
                 transa = as.integer(n),
                 ma =as.integer(ma),
                 na =as.integer(na),
                 Ma =as.integer(ma),
                 Na =as.integer(na),
                 dataa = as.double(A),		
                 betab = as.double(b),
                 transb = as.integer(n),
                 mb =as.integer(mb),
                 nb =as.integer(nb),
                 Mb =as.integer(mb),
                 Nb =as.integer(nb),
                 datab = as.double(B),DUP=FALSE
                 )

    array(output$datac,dim=dim(C))
}

d_wmulR <- function(a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;

    nc   = length(B[1,]);
    mc   = length(A[,1]) ;
    C = array(0.0, dim=c(mc,nc))
    c = 1.0
    n = 0
    output <- .C("d_wmulB",
                 betac = as.double(c),
                 transc = as.integer(n),
                 mc =as.integer(mc),
                 nc =as.integer(nc),
                 Mc =as.integer(mc),
                 Nc =as.integer(nc),
                 datac = as.double(C),		
                 betaa = as.double(a),
                 transa = as.integer(n),
                 ma =as.integer(ma),
                 na =as.integer(na),
                 Ma =as.integer(ma),
                 Na =as.integer(na),
                 dataa = as.double(A),		
                 betab = as.double(b),
                 transb = as.integer(n),
                 mb =as.integer(mb),
                 nb =as.integer(nb),
                 Mb =as.integer(mb),
                 Nb =as.integer(nb),
                 datab = as.double(B),DUP=FALSE
                 )

    array(output$datac,dim=dim(C))
}

d_waddmulR <- function(c,C,a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;
    nc   = length(C[1,]);
    mc   = length(C[,1]) ;

    n = 0
  
   output <- .C("d_waddmulB",
     betac = as.double(c),
     transc = as.integer(n),
     mc =as.integer(mc),
     nc =as.integer(nc),
     Mc =as.integer(mc),
     Nc =as.integer(nc),
     datac = as.double(C),		
     betaa = as.double(a),
     transa = as.integer(n),
     ma =as.integer(ma),
     na =as.integer(na),
     Ma =as.integer(ma),
     Na =as.integer(na),
     dataa = as.double(A),		
     betab = as.double(b),
     transb = as.integer(n),
     mb =as.integer(mb),
     nb =as.integer(nb),
     Mb =as.integer(mb),
     Nb =as.integer(nb),
     datab = as.double(B),DUP=FALSE

     )

    array(output$datac,dim=dim(C))
}



d_wmR <- function(a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;

    nc   = length(B[1,]);
    mc   = length(A[,1]) ;
    C = array(0.0, dim=c(mc,nc))
    c = 1.0
    n = 0
    output <- .C("d_wmB",
                 betac = as.double(c),
                 transc = as.integer(n),
                 mc =as.integer(mc),
                 nc =as.integer(nc),
                 Mc =as.integer(mc),
                 Nc =as.integer(nc),
                 datac = as.double(C),		
                 betaa = as.double(a),
                 transa = as.integer(n),
                 ma =as.integer(ma),
                 na =as.integer(na),
                 Ma =as.integer(ma),
                 Na =as.integer(na),
                 dataa = as.double(A),		
                 betab = as.double(b),
                 transb = as.integer(n),
                 mb =as.integer(mb),
                 nb =as.integer(nb),
                 Mb =as.integer(mb),
                 Nb =as.integer(nb),
                 datab = as.double(B),DUP=FALSE
                 )

    array(output$datac,dim=dim(C))
}

d_wmaddR <- function(c,C,a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;
    nc   = length(C[1,]);
    mc   = length(C[,1]) ;

    n = 0
  
   output <- .C("d_wmaddB",
     betac = as.double(c),
     transc = as.integer(n),
     mc =as.integer(mc),
     nc =as.integer(nc),
     Mc =as.integer(mc),
     Nc =as.integer(nc),
     datac = as.double(C),		
     betaa = as.double(a),
     transa = as.integer(n),
     ma =as.integer(ma),
     na =as.integer(na),
     Ma =as.integer(ma),
     Na =as.integer(na),
     dataa = as.double(A),		
     betab = as.double(b),
     transb = as.integer(n),
     mb =as.integer(mb),
     nb =as.integer(nb),
     Mb =as.integer(mb),
     Nb =as.integer(nb),
     datab = as.double(B),DUP=FALSE

     )

    array(output$datac,dim=dim(C))
}



d_adaptive_smulR <- function(a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;

    nc   = length(B[1,]);
    mc   = length(A[,1]) ;
    C = array(0.0, dim=c(mc,nc))
    c = 1.0
    n = 0
    output <- .C("d_adaptive_smulB",
                 betac = as.double(c),
                 transc = as.integer(n),
                 mc =as.integer(mc),
                 nc =as.integer(nc),
                 Mc =as.integer(mc),
                 Nc =as.integer(nc),
                 datac = as.double(C),		
                 betaa = as.double(a),
                 transa = as.integer(n),
                 ma =as.integer(ma),
                 na =as.integer(na),
                 Ma =as.integer(ma),
                 Na =as.integer(na),
                 dataa = as.double(A),		
                 betab = as.double(b),
                 transb = as.integer(n),
                 mb =as.integer(mb),
                 nb =as.integer(nb),
                 Mb =as.integer(mb),
                 Nb =as.integer(nb),
                 datab = as.double(B),DUP=FALSE
                 )

    array(output$datac,dim=dim(C))
}

d_omulR <- function(a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;

    nc   = length(B[1,]);
    mc   = length(A[,1]) ;
    C = array(0.0, dim=c(mc,nc))
    c = 1.0
    n = 0
    output <- .C("d_omulB",
                 betac = as.double(c),
                 transc = as.integer(n),
                 mc =as.integer(mc),
                 nc =as.integer(nc),
                 Mc =as.integer(mc),
                 Nc =as.integer(nc),
                 datac = as.double(C),		
                 betaa = as.double(a),
                 transa = as.integer(n),
                 ma =as.integer(ma),
                 na =as.integer(na),
                 Ma =as.integer(ma),
                 Na =as.integer(na),
                 dataa = as.double(A),		
                 betab = as.double(b),
                 transb = as.integer(n),
                 mb =as.integer(mb),
                 nb =as.integer(nb),
                 Mb =as.integer(mb),
                 Nb =as.integer(nb),
                 datab = as.double(B),DUP=FALSE
                 )

    array(output$datac,dim=dim(C))
}

d_oaddmulR <- function(c,C,a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;
    nc   = length(C[1,]);
    mc   = length(C[,1]) ;

    n = 0
  
   output <- .C("d_oaddmulB",
     betac = as.double(c),
     transc = as.integer(n),
     mc =as.integer(mc),
     nc =as.integer(nc),
     Mc =as.integer(mc),
     Nc =as.integer(nc),
     datac = as.double(C),		
     betaa = as.double(a),
     transa = as.integer(n),
     ma =as.integer(ma),
     na =as.integer(na),
     Ma =as.integer(ma),
     Na =as.integer(na),
     dataa = as.double(A),		
     betab = as.double(b),
     transb = as.integer(n),
     mb =as.integer(mb),
     nb =as.integer(nb),
     Mb =as.integer(mb),
     Nb =as.integer(nb),
     datab = as.double(B),DUP=FALSE

     )

    array(output$datac,dim=dim(C))
}



d_owmulR <- function(a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;

    nc   = length(B[1,]);
    mc   = length(A[,1]) ;
    C = array(0.0, dim=c(mc,nc))
    c = 1.0
    n = 0
    output <- .C("d_owmulB",
                 betac = as.double(c),
                 transc = as.integer(n),
                 mc =as.integer(mc),
                 nc =as.integer(nc),
                 Mc =as.integer(mc),
                 Nc =as.integer(nc),
                 datac = as.double(C),		
                 betaa = as.double(a),
                 transa = as.integer(n),
                 ma =as.integer(ma),
                 na =as.integer(na),
                 Ma =as.integer(ma),
                 Na =as.integer(na),
                 dataa = as.double(A),		
                 betab = as.double(b),
                 transb = as.integer(n),
                 mb =as.integer(mb),
                 nb =as.integer(nb),
                 Mb =as.integer(mb),
                 Nb =as.integer(nb),
                 datab = as.double(B),DUP=FALSE
                 )

    array(output$datac,dim=dim(C))
}

d_owaddmulR <- function(c,C,a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;
    nc   = length(C[1,]);
    mc   = length(C[,1]) ;

    n = 0
  
   output <- .C("d_owaddmulB",
     betac = as.double(c),
     transc = as.integer(n),
     mc =as.integer(mc),
     nc =as.integer(nc),
     Mc =as.integer(mc),
     Nc =as.integer(nc),
     datac = as.double(C),		
     betaa = as.double(a),
     transa = as.integer(n),
     ma =as.integer(ma),
     na =as.integer(na),
     Ma =as.integer(ma),
     Na =as.integer(na),
     dataa = as.double(A),		
     betab = as.double(b),
     transb = as.integer(n),
     mb =as.integer(mb),
     nb =as.integer(nb),
     Mb =as.integer(mb),
     Nb =as.integer(nb),
     datab = as.double(B),DUP=FALSE

     )

    array(output$datac,dim=dim(C))
}



d_bmR <- function(a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;

    nc   = length(B[1,]);
    mc   = length(A[,1]) ;
    C = array(0.0, dim=c(mc,nc))
    c = 1.0
    n = 0
    output <- .C("d_bmB",
                 betac = as.double(c),
                 transc = as.integer(n),
                 mc =as.integer(mc),
                 nc =as.integer(nc),
                 Mc =as.integer(mc),
                 Nc =as.integer(nc),
                 datac = as.double(C),		
                 betaa = as.double(a),
                 transa = as.integer(n),
                 ma =as.integer(ma),
                 na =as.integer(na),
                 Ma =as.integer(ma),
                 Na =as.integer(na),
                 dataa = as.double(A),		
                 betab = as.double(b),
                 transb = as.integer(n),
                 mb =as.integer(mb),
                 nb =as.integer(nb),
                 Mb =as.integer(mb),
                 Nb =as.integer(nb),
                 datab = as.double(B),DUP=FALSE
                 )

    array(output$datac,dim=dim(C))
}

d_bmaddR <- function(c,C,a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;
    nc   = length(C[1,]);
    mc   = length(C[,1]) ;

    n = 0
  
   output <- .C("d_bmaddB",
     betac = as.double(c),
     transc = as.integer(n),
     mc =as.integer(mc),
     nc =as.integer(nc),
     Mc =as.integer(mc),
     Nc =as.integer(nc),
     datac = as.double(C),		
     betaa = as.double(a),
     transa = as.integer(n),
     ma =as.integer(ma),
     na =as.integer(na),
     Ma =as.integer(ma),
     Na =as.integer(na),
     dataa = as.double(A),		
     betab = as.double(b),
     transb = as.integer(n),
     mb =as.integer(mb),
     nb =as.integer(nb),
     Mb =as.integer(mb),
     Nb =as.integer(nb),
     datab = as.double(B),DUP=FALSE

     )

    array(output$datac,dim=dim(C))
}



d_ptaddmulR <- function(c,C,a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;
    nc   = length(C[1,]);
    mc   = length(C[,1]) ;

    n = 0
  
   output <- .C("d_ptaddmulB",
     betac = as.double(c),
     transc = as.integer(n),
     mc =as.integer(mc),
     nc =as.integer(nc),
     Mc =as.integer(mc),
     Nc =as.integer(nc),
     datac = as.double(C),		
     betaa = as.double(a),
     transa = as.integer(n),
     ma =as.integer(ma),
     na =as.integer(na),
     Ma =as.integer(ma),
     Na =as.integer(na),
     dataa = as.double(A),		
     betab = as.double(b),
     transb = as.integer(n),
     mb =as.integer(mb),
     nb =as.integer(nb),
     Mb =as.integer(mb),
     Nb =as.integer(nb),
     datab = as.double(B),DUP=FALSE

     )

    array(output$datac,dim=dim(C))
}



d_wmpipeR <- function(a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;

    nc   = length(B[1,]);
    mc   = length(A[,1]) ;
    C = array(0.0, dim=c(mc,nc))
    c = 1.0
    n = 0
    output <- .C("d_wmpipeB",
                 betac = as.double(c),
                 transc = as.integer(n),
                 mc =as.integer(mc),
                 nc =as.integer(nc),
                 Mc =as.integer(mc),
                 Nc =as.integer(nc),
                 datac = as.double(C),		
                 betaa = as.double(a),
                 transa = as.integer(n),
                 ma =as.integer(ma),
                 na =as.integer(na),
                 Ma =as.integer(ma),
                 Na =as.integer(na),
                 dataa = as.double(A),		
                 betab = as.double(b),
                 transb = as.integer(n),
                 mb =as.integer(mb),
                 nb =as.integer(nb),
                 Mb =as.integer(mb),
                 Nb =as.integer(nb),
                 datab = as.double(B),DUP=FALSE
                 )

    array(output$datac,dim=dim(C))
}

d_wmaddpipeR <- function(c,C,a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;
    nc   = length(C[1,]);
    mc   = length(C[,1]) ;

    n = 0
  
   output <- .C("d_wmaddpipeB",
     betac = as.double(c),
     transc = as.integer(n),
     mc =as.integer(mc),
     nc =as.integer(nc),
     Mc =as.integer(mc),
     Nc =as.integer(nc),
     datac = as.double(C),		
     betaa = as.double(a),
     transa = as.integer(n),
     ma =as.integer(ma),
     na =as.integer(na),
     Ma =as.integer(ma),
     Na =as.integer(na),
     dataa = as.double(A),		
     betab = as.double(b),
     transb = as.integer(n),
     mb =as.integer(mb),
     nb =as.integer(nb),
     Mb =as.integer(mb),
     Nb =as.integer(nb),
     datab = as.double(B),DUP=FALSE

     )

    array(output$datac,dim=dim(C))
}



d_bmpipeR <- function(a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;

    nc   = length(B[1,]);
    mc   = length(A[,1]) ;
    C = array(0.0, dim=c(mc,nc))
    c = 1.0
    n = 0
    output <- .C("d_bmpipeB",
                 betac = as.double(c),
                 transc = as.integer(n),
                 mc =as.integer(mc),
                 nc =as.integer(nc),
                 Mc =as.integer(mc),
                 Nc =as.integer(nc),
                 datac = as.double(C),		
                 betaa = as.double(a),
                 transa = as.integer(n),
                 ma =as.integer(ma),
                 na =as.integer(na),
                 Ma =as.integer(ma),
                 Na =as.integer(na),
                 dataa = as.double(A),		
                 betab = as.double(b),
                 transb = as.integer(n),
                 mb =as.integer(mb),
                 nb =as.integer(nb),
                 Mb =as.integer(mb),
                 Nb =as.integer(nb),
                 datab = as.double(B),DUP=FALSE
                 )

    array(output$datac,dim=dim(C))
}

d_bmaddpipeR <- function(c,C,a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;
    nc   = length(C[1,]);
    mc   = length(C[,1]) ;

    n = 0
  
   output <- .C("d_bmaddpipeB",
     betac = as.double(c),
     transc = as.integer(n),
     mc =as.integer(mc),
     nc =as.integer(nc),
     Mc =as.integer(mc),
     Nc =as.integer(nc),
     datac = as.double(C),		
     betaa = as.double(a),
     transa = as.integer(n),
     ma =as.integer(ma),
     na =as.integer(na),
     Ma =as.integer(ma),
     Na =as.integer(na),
     dataa = as.double(A),		
     betab = as.double(b),
     transb = as.integer(n),
     mb =as.integer(mb),
     nb =as.integer(nb),
     Mb =as.integer(mb),
     Nb =as.integer(nb),
     datab = as.double(B),DUP=FALSE

     )

    array(output$datac,dim=dim(C))
}



d_smpipeR <- function(a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;

    nc   = length(B[1,]);
    mc   = length(A[,1]) ;
    C = array(0.0, dim=c(mc,nc))
    c = 1.0
    n = 0
    output <- .C("d_smpipeB",
                 betac = as.double(c),
                 transc = as.integer(n),
                 mc =as.integer(mc),
                 nc =as.integer(nc),
                 Mc =as.integer(mc),
                 Nc =as.integer(nc),
                 datac = as.double(C),		
                 betaa = as.double(a),
                 transa = as.integer(n),
                 ma =as.integer(ma),
                 na =as.integer(na),
                 Ma =as.integer(ma),
                 Na =as.integer(na),
                 dataa = as.double(A),		
                 betab = as.double(b),
                 transb = as.integer(n),
                 mb =as.integer(mb),
                 nb =as.integer(nb),
                 Mb =as.integer(mb),
                 Nb =as.integer(nb),
                 datab = as.double(B),DUP=FALSE
                 )

    array(output$datac,dim=dim(C))
}

d_smaddpipeR <- function(c,C,a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;
    nc   = length(C[1,]);
    mc   = length(C[,1]) ;

    n = 0
  
   output <- .C("d_smaddpipeB",
     betac = as.double(c),
     transc = as.integer(n),
     mc =as.integer(mc),
     nc =as.integer(nc),
     Mc =as.integer(mc),
     Nc =as.integer(nc),
     datac = as.double(C),		
     betaa = as.double(a),
     transa = as.integer(n),
     ma =as.integer(ma),
     na =as.integer(na),
     Ma =as.integer(ma),
     Na =as.integer(na),
     dataa = as.double(A),		
     betab = as.double(b),
     transb = as.integer(n),
     mb =as.integer(mb),
     nb =as.integer(nb),
     Mb =as.integer(mb),
     Nb =as.integer(nb),
     datab = as.double(B),DUP=FALSE

     )

    array(output$datac,dim=dim(C))
}



d_RmulR <- function(a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;

    nc   = length(B[1,]);
    mc   = length(A[,1]) ;
    C = array(0.0, dim=c(mc,nc))
    c = 1.0
    n = 0
    output <- .C("d_RmulB",
                 betac = as.double(c),
                 transc = as.integer(n),
                 mc =as.integer(mc),
                 nc =as.integer(nc),
                 Mc =as.integer(mc),
                 Nc =as.integer(nc),
                 datac = as.double(C),		
                 betaa = as.double(a),
                 transa = as.integer(n),
                 ma =as.integer(ma),
                 na =as.integer(na),
                 Ma =as.integer(ma),
                 Na =as.integer(na),
                 dataa = as.double(A),		
                 betab = as.double(b),
                 transb = as.integer(n),
                 mb =as.integer(mb),
                 nb =as.integer(nb),
                 Mb =as.integer(mb),
                 Nb =as.integer(nb),
                 datab = as.double(B),DUP=FALSE
                 )

    array(output$datac,dim=dim(C))
}

d_adaptive_wmR <- function(a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;

    nc   = length(B[1,]);
    mc   = length(A[,1]) ;
    C = array(0.0, dim=c(mc,nc))
    c = 1.0
    n = 0
    output <- .C("d_adaptive_wmB",
                 betac = as.double(c),
                 transc = as.integer(n),
                 mc =as.integer(mc),
                 nc =as.integer(nc),
                 Mc =as.integer(mc),
                 Nc =as.integer(nc),
                 datac = as.double(C),		
                 betaa = as.double(a),
                 transa = as.integer(n),
                 ma =as.integer(ma),
                 na =as.integer(na),
                 Ma =as.integer(ma),
                 Na =as.integer(na),
                 dataa = as.double(A),		
                 betab = as.double(b),
                 transb = as.integer(n),
                 mb =as.integer(mb),
                 nb =as.integer(nb),
                 Mb =as.integer(mb),
                 Nb =as.integer(nb),
                 datab = as.double(B),DUP=FALSE
                 )

    array(output$datac,dim=dim(C))
}

d_BMADD_PIPER <- function(c,C,a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;
    nc   = length(C[1,]);
    mc   = length(C[,1]) ;

    n = 0
  
   output <- .C("d_BMADD_PIPEB",
     betac = as.double(c),
     transc = as.integer(n),
     mc =as.integer(mc),
     nc =as.integer(nc),
     Mc =as.integer(mc),
     Nc =as.integer(nc),
     datac = as.double(C),		
     betaa = as.double(a),
     transa = as.integer(n),
     ma =as.integer(ma),
     na =as.integer(na),
     Ma =as.integer(ma),
     Na =as.integer(na),
     dataa = as.double(A),		
     betab = as.double(b),
     transb = as.integer(n),
     mb =as.integer(mb),
     nb =as.integer(nb),
     Mb =as.integer(mb),
     Nb =as.integer(nb),
     datab = as.double(B),DUP=FALSE

     )

    array(output$datac,dim=dim(C))
}



d_BMADDR <- function(c,C,a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;
    nc   = length(C[1,]);
    mc   = length(C[,1]) ;

    n = 0
  
   output <- .C("d_BMADDB",
     betac = as.double(c),
     transc = as.integer(n),
     mc =as.integer(mc),
     nc =as.integer(nc),
     Mc =as.integer(mc),
     Nc =as.integer(nc),
     datac = as.double(C),		
     betaa = as.double(a),
     transa = as.integer(n),
     ma =as.integer(ma),
     na =as.integer(na),
     Ma =as.integer(ma),
     Na =as.integer(na),
     dataa = as.double(A),		
     betab = as.double(b),
     transb = as.integer(n),
     mb =as.integer(mb),
     nb =as.integer(nb),
     Mb =as.integer(mb),
     Nb =as.integer(nb),
     datab = as.double(B),DUP=FALSE

     )

    array(output$datac,dim=dim(C))
}



d_BMOWR_PIPER <- function(a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;

    nc   = length(B[1,]);
    mc   = length(A[,1]) ;
    C = array(0.0, dim=c(mc,nc))
    c = 1.0
    n = 0
    output <- .C("d_BMOWR_PIPEB",
                 betac = as.double(c),
                 transc = as.integer(n),
                 mc =as.integer(mc),
                 nc =as.integer(nc),
                 Mc =as.integer(mc),
                 Nc =as.integer(nc),
                 datac = as.double(C),		
                 betaa = as.double(a),
                 transa = as.integer(n),
                 ma =as.integer(ma),
                 na =as.integer(na),
                 Ma =as.integer(ma),
                 Na =as.integer(na),
                 dataa = as.double(A),		
                 betab = as.double(b),
                 transb = as.integer(n),
                 mb =as.integer(mb),
                 nb =as.integer(nb),
                 Mb =as.integer(mb),
                 Nb =as.integer(nb),
                 datab = as.double(B),DUP=FALSE
                 )

    array(output$datac,dim=dim(C))
}

d_BMOWRR <- function(a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;

    nc   = length(B[1,]);
    mc   = length(A[,1]) ;
    C = array(0.0, dim=c(mc,nc))
    c = 1.0
    n = 0
    output <- .C("d_BMOWRB",
                 betac = as.double(c),
                 transc = as.integer(n),
                 mc =as.integer(mc),
                 nc =as.integer(nc),
                 Mc =as.integer(mc),
                 Nc =as.integer(nc),
                 datac = as.double(C),		
                 betaa = as.double(a),
                 transa = as.integer(n),
                 ma =as.integer(ma),
                 na =as.integer(na),
                 Ma =as.integer(ma),
                 Na =as.integer(na),
                 dataa = as.double(A),		
                 betab = as.double(b),
                 transb = as.integer(n),
                 mb =as.integer(mb),
                 nb =as.integer(nb),
                 Mb =as.integer(mb),
                 Nb =as.integer(nb),
                 datab = as.double(B),DUP=FALSE
                 )

    array(output$datac,dim=dim(C))
}

c_dcmulR <- function(a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;

    nc   = length(B[1,]);
    mc   = length(A[,1]) ;
    C = array(0.0, dim=c(mc,nc))
    c = 1.0
    n = 0
    output <- .C("c_dcmulB",
                 betac = as.complex(c),
                 transc = as.integer(n),
                 mc =as.integer(mc),
                 nc =as.integer(nc),
                 Mc =as.integer(mc),
                 Nc =as.integer(nc),
                 datac = as.complex(C),		
                 betaa = as.complex(a),
                 transa = as.integer(n),
                 ma =as.integer(ma),
                 na =as.integer(na),
                 Ma =as.integer(ma),
                 Na =as.integer(na),
                 dataa = as.complex(A),		
                 betab = as.complex(b),
                 transb = as.integer(n),
                 mb =as.integer(mb),
                 nb =as.integer(nb),
                 Mb =as.integer(mb),
                 Nb =as.integer(nb),
                 datab = as.complex(B)
                 )

    array(output$datac,dim=dim(C))
}

c_mulR <- function(a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;

    nc   = length(B[1,]);
    mc   = length(A[,1]) ;
    C = array(0.0, dim=c(mc,nc))
    c = 1.0
    n = 0
    output <- .C("c_mulB",
                 betac = as.complex(c),
                 transc = as.integer(n),
                 mc =as.integer(mc),
                 nc =as.integer(nc),
                 Mc =as.integer(mc),
                 Nc =as.integer(nc),
                 datac = as.complex(C),		
                 betaa = as.complex(a),
                 transa = as.integer(n),
                 ma =as.integer(ma),
                 na =as.integer(na),
                 Ma =as.integer(ma),
                 Na =as.integer(na),
                 dataa = as.complex(A),		
                 betab = as.complex(b),
                 transb = as.integer(n),
                 mb =as.integer(mb),
                 nb =as.integer(nb),
                 Mb =as.integer(mb),
                 Nb =as.integer(nb),
                 datab = as.complex(B)
                 )

    array(output$datac,dim=dim(C))
}

c_mulptR <- function(a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;

    nc   = length(B[1,]);
    mc   = length(A[,1]) ;
    C = array(0.0, dim=c(mc,nc))
    c = 1.0
    n = 0
    output <- .C("c_mulptB",
                 betac = as.complex(c),
                 transc = as.integer(n),
                 mc =as.integer(mc),
                 nc =as.integer(nc),
                 Mc =as.integer(mc),
                 Nc =as.integer(nc),
                 datac = as.complex(C),		
                 betaa = as.complex(a),
                 transa = as.integer(n),
                 ma =as.integer(ma),
                 na =as.integer(na),
                 Ma =as.integer(ma),
                 Na =as.integer(na),
                 dataa = as.complex(A),		
                 betab = as.complex(b),
                 transb = as.integer(n),
                 mb =as.integer(mb),
                 nb =as.integer(nb),
                 Mb =as.integer(mb),
                 Nb =as.integer(nb),
                 datab = as.complex(B)
                 )

    array(output$datac,dim=dim(C))
}

c_maddR <- function(c,C,a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;
    nc   = length(C[1,]);
    mc   = length(C[,1]) ;

    n = 0
  
   output <- .C("c_maddB",
     betac = as.complex(c),
     transc = as.integer(n),
     mc =as.integer(mc),
     nc =as.integer(nc),
     Mc =as.integer(mc),
     Nc =as.integer(nc),
     datac = as.complex(C),		
     betaa = as.complex(a),
     transa = as.integer(n),
     ma =as.integer(ma),
     na =as.integer(na),
     Ma =as.integer(ma),
     Na =as.integer(na),
     dataa = as.complex(A),		
     betab = as.complex(b),
     transb = as.integer(n),
     mb =as.integer(mb),
     nb =as.integer(nb),
     Mb =as.integer(mb),
     Nb =as.integer(nb),
     datab = as.complex(B)

     )

    array(output$datac,dim=dim(C))
}



c_saddmulR <- function(c,C,a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;
    nc   = length(C[1,]);
    mc   = length(C[,1]) ;

    n = 0
  
   output <- .C("c_saddmulB",
     betac = as.complex(c),
     transc = as.integer(n),
     mc =as.integer(mc),
     nc =as.integer(nc),
     Mc =as.integer(mc),
     Nc =as.integer(nc),
     datac = as.complex(C),		
     betaa = as.complex(a),
     transa = as.integer(n),
     ma =as.integer(ma),
     na =as.integer(na),
     Ma =as.integer(ma),
     Na =as.integer(na),
     dataa = as.complex(A),		
     betab = as.complex(b),
     transb = as.integer(n),
     mb =as.integer(mb),
     nb =as.integer(nb),
     Mb =as.integer(mb),
     Nb =as.integer(nb),
     datab = as.complex(B)

     )

    array(output$datac,dim=dim(C))
}



c_smulR <- function(a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;

    nc   = length(B[1,]);
    mc   = length(A[,1]) ;
    C = array(0.0, dim=c(mc,nc))
    c = 1.0
    n = 0
    output <- .C("c_smulB",
                 betac = as.complex(c),
                 transc = as.integer(n),
                 mc =as.integer(mc),
                 nc =as.integer(nc),
                 Mc =as.integer(mc),
                 Nc =as.integer(nc),
                 datac = as.complex(C),		
                 betaa = as.complex(a),
                 transa = as.integer(n),
                 ma =as.integer(ma),
                 na =as.integer(na),
                 Ma =as.integer(ma),
                 Na =as.integer(na),
                 dataa = as.complex(A),		
                 betab = as.complex(b),
                 transb = as.integer(n),
                 mb =as.integer(mb),
                 nb =as.integer(nb),
                 Mb =as.integer(mb),
                 Nb =as.integer(nb),
                 datab = as.complex(B)
                 )

    array(output$datac,dim=dim(C))
}

c_wmulR <- function(a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;

    nc   = length(B[1,]);
    mc   = length(A[,1]) ;
    C = array(0.0, dim=c(mc,nc))
    c = 1.0
    n = 0
    output <- .C("c_wmulB",
                 betac = as.complex(c),
                 transc = as.integer(n),
                 mc =as.integer(mc),
                 nc =as.integer(nc),
                 Mc =as.integer(mc),
                 Nc =as.integer(nc),
                 datac = as.complex(C),		
                 betaa = as.complex(a),
                 transa = as.integer(n),
                 ma =as.integer(ma),
                 na =as.integer(na),
                 Ma =as.integer(ma),
                 Na =as.integer(na),
                 dataa = as.complex(A),		
                 betab = as.complex(b),
                 transb = as.integer(n),
                 mb =as.integer(mb),
                 nb =as.integer(nb),
                 Mb =as.integer(mb),
                 Nb =as.integer(nb),
                 datab = as.complex(B)
                 )

    array(output$datac,dim=dim(C))
}

c_waddmulR <- function(c,C,a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;
    nc   = length(C[1,]);
    mc   = length(C[,1]) ;

    n = 0
  
   output <- .C("c_waddmulB",
     betac = as.complex(c),
     transc = as.integer(n),
     mc =as.integer(mc),
     nc =as.integer(nc),
     Mc =as.integer(mc),
     Nc =as.integer(nc),
     datac = as.complex(C),		
     betaa = as.complex(a),
     transa = as.integer(n),
     ma =as.integer(ma),
     na =as.integer(na),
     Ma =as.integer(ma),
     Na =as.integer(na),
     dataa = as.complex(A),		
     betab = as.complex(b),
     transb = as.integer(n),
     mb =as.integer(mb),
     nb =as.integer(nb),
     Mb =as.integer(mb),
     Nb =as.integer(nb),
     datab = as.complex(B)

     )

    array(output$datac,dim=dim(C))
}



c_wmR <- function(a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;

    nc   = length(B[1,]);
    mc   = length(A[,1]) ;
    C = array(0.0, dim=c(mc,nc))
    c = 1.0
    n = 0
    output <- .C("c_wmB",
                 betac = as.complex(c),
                 transc = as.integer(n),
                 mc =as.integer(mc),
                 nc =as.integer(nc),
                 Mc =as.integer(mc),
                 Nc =as.integer(nc),
                 datac = as.complex(C),		
                 betaa = as.complex(a),
                 transa = as.integer(n),
                 ma =as.integer(ma),
                 na =as.integer(na),
                 Ma =as.integer(ma),
                 Na =as.integer(na),
                 dataa = as.complex(A),		
                 betab = as.complex(b),
                 transb = as.integer(n),
                 mb =as.integer(mb),
                 nb =as.integer(nb),
                 Mb =as.integer(mb),
                 Nb =as.integer(nb),
                 datab = as.complex(B)
                 )

    array(output$datac,dim=dim(C))
}

c_wmaddR <- function(c,C,a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;
    nc   = length(C[1,]);
    mc   = length(C[,1]) ;

    n = 0
  
   output <- .C("c_wmaddB",
     betac = as.complex(c),
     transc = as.integer(n),
     mc =as.integer(mc),
     nc =as.integer(nc),
     Mc =as.integer(mc),
     Nc =as.integer(nc),
     datac = as.complex(C),		
     betaa = as.complex(a),
     transa = as.integer(n),
     ma =as.integer(ma),
     na =as.integer(na),
     Ma =as.integer(ma),
     Na =as.integer(na),
     dataa = as.complex(A),		
     betab = as.complex(b),
     transb = as.integer(n),
     mb =as.integer(mb),
     nb =as.integer(nb),
     Mb =as.integer(mb),
     Nb =as.integer(nb),
     datab = as.complex(B)

     )

    array(output$datac,dim=dim(C))
}



c_adaptive_smulR <- function(a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;

    nc   = length(B[1,]);
    mc   = length(A[,1]) ;
    C = array(0.0, dim=c(mc,nc))
    c = 1.0
    n = 0
    output <- .C("c_adaptive_smulB",
                 betac = as.complex(c),
                 transc = as.integer(n),
                 mc =as.integer(mc),
                 nc =as.integer(nc),
                 Mc =as.integer(mc),
                 Nc =as.integer(nc),
                 datac = as.complex(C),		
                 betaa = as.complex(a),
                 transa = as.integer(n),
                 ma =as.integer(ma),
                 na =as.integer(na),
                 Ma =as.integer(ma),
                 Na =as.integer(na),
                 dataa = as.complex(A),		
                 betab = as.complex(b),
                 transb = as.integer(n),
                 mb =as.integer(mb),
                 nb =as.integer(nb),
                 Mb =as.integer(mb),
                 Nb =as.integer(nb),
                 datab = as.complex(B)
                 )

    array(output$datac,dim=dim(C))
}

c_omulR <- function(a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;

    nc   = length(B[1,]);
    mc   = length(A[,1]) ;
    C = array(0.0, dim=c(mc,nc))
    c = 1.0
    n = 0
    output <- .C("c_omulB",
                 betac = as.complex(c),
                 transc = as.integer(n),
                 mc =as.integer(mc),
                 nc =as.integer(nc),
                 Mc =as.integer(mc),
                 Nc =as.integer(nc),
                 datac = as.complex(C),		
                 betaa = as.complex(a),
                 transa = as.integer(n),
                 ma =as.integer(ma),
                 na =as.integer(na),
                 Ma =as.integer(ma),
                 Na =as.integer(na),
                 dataa = as.complex(A),		
                 betab = as.complex(b),
                 transb = as.integer(n),
                 mb =as.integer(mb),
                 nb =as.integer(nb),
                 Mb =as.integer(mb),
                 Nb =as.integer(nb),
                 datab = as.complex(B)
                 )

    array(output$datac,dim=dim(C))
}

c_oaddmulR <- function(c,C,a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;
    nc   = length(C[1,]);
    mc   = length(C[,1]) ;

    n = 0
  
   output <- .C("c_oaddmulB",
     betac = as.complex(c),
     transc = as.integer(n),
     mc =as.integer(mc),
     nc =as.integer(nc),
     Mc =as.integer(mc),
     Nc =as.integer(nc),
     datac = as.complex(C),		
     betaa = as.complex(a),
     transa = as.integer(n),
     ma =as.integer(ma),
     na =as.integer(na),
     Ma =as.integer(ma),
     Na =as.integer(na),
     dataa = as.complex(A),		
     betab = as.complex(b),
     transb = as.integer(n),
     mb =as.integer(mb),
     nb =as.integer(nb),
     Mb =as.integer(mb),
     Nb =as.integer(nb),
     datab = as.complex(B)

     )

    array(output$datac,dim=dim(C))
}



c_owmulR <- function(a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;

    nc   = length(B[1,]);
    mc   = length(A[,1]) ;
    C = array(0.0, dim=c(mc,nc))
    c = 1.0
    n = 0
    output <- .C("c_owmulB",
                 betac = as.complex(c),
                 transc = as.integer(n),
                 mc =as.integer(mc),
                 nc =as.integer(nc),
                 Mc =as.integer(mc),
                 Nc =as.integer(nc),
                 datac = as.complex(C),		
                 betaa = as.complex(a),
                 transa = as.integer(n),
                 ma =as.integer(ma),
                 na =as.integer(na),
                 Ma =as.integer(ma),
                 Na =as.integer(na),
                 dataa = as.complex(A),		
                 betab = as.complex(b),
                 transb = as.integer(n),
                 mb =as.integer(mb),
                 nb =as.integer(nb),
                 Mb =as.integer(mb),
                 Nb =as.integer(nb),
                 datab = as.complex(B)
                 )

    array(output$datac,dim=dim(C))
}

c_owaddmulR <- function(c,C,a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;
    nc   = length(C[1,]);
    mc   = length(C[,1]) ;

    n = 0
  
   output <- .C("c_owaddmulB",
     betac = as.complex(c),
     transc = as.integer(n),
     mc =as.integer(mc),
     nc =as.integer(nc),
     Mc =as.integer(mc),
     Nc =as.integer(nc),
     datac = as.complex(C),		
     betaa = as.complex(a),
     transa = as.integer(n),
     ma =as.integer(ma),
     na =as.integer(na),
     Ma =as.integer(ma),
     Na =as.integer(na),
     dataa = as.complex(A),		
     betab = as.complex(b),
     transb = as.integer(n),
     mb =as.integer(mb),
     nb =as.integer(nb),
     Mb =as.integer(mb),
     Nb =as.integer(nb),
     datab = as.complex(B)

     )

    array(output$datac,dim=dim(C))
}



c_bmR <- function(a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;

    nc   = length(B[1,]);
    mc   = length(A[,1]) ;
    C = array(0.0, dim=c(mc,nc))
    c = 1.0
    n = 0
    output <- .C("c_bmB",
                 betac = as.complex(c),
                 transc = as.integer(n),
                 mc =as.integer(mc),
                 nc =as.integer(nc),
                 Mc =as.integer(mc),
                 Nc =as.integer(nc),
                 datac = as.complex(C),		
                 betaa = as.complex(a),
                 transa = as.integer(n),
                 ma =as.integer(ma),
                 na =as.integer(na),
                 Ma =as.integer(ma),
                 Na =as.integer(na),
                 dataa = as.complex(A),		
                 betab = as.complex(b),
                 transb = as.integer(n),
                 mb =as.integer(mb),
                 nb =as.integer(nb),
                 Mb =as.integer(mb),
                 Nb =as.integer(nb),
                 datab = as.complex(B)
                 )

    array(output$datac,dim=dim(C))
}

c_bmaddR <- function(c,C,a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;
    nc   = length(C[1,]);
    mc   = length(C[,1]) ;

    n = 0
  
   output <- .C("c_bmaddB",
     betac = as.complex(c),
     transc = as.integer(n),
     mc =as.integer(mc),
     nc =as.integer(nc),
     Mc =as.integer(mc),
     Nc =as.integer(nc),
     datac = as.complex(C),		
     betaa = as.complex(a),
     transa = as.integer(n),
     ma =as.integer(ma),
     na =as.integer(na),
     Ma =as.integer(ma),
     Na =as.integer(na),
     dataa = as.complex(A),		
     betab = as.complex(b),
     transb = as.integer(n),
     mb =as.integer(mb),
     nb =as.integer(nb),
     Mb =as.integer(mb),
     Nb =as.integer(nb),
     datab = as.complex(B)

     )

    array(output$datac,dim=dim(C))
}



c_ptaddmulR <- function(c,C,a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;
    nc   = length(C[1,]);
    mc   = length(C[,1]) ;

    n = 0
  
   output <- .C("c_ptaddmulB",
     betac = as.complex(c),
     transc = as.integer(n),
     mc =as.integer(mc),
     nc =as.integer(nc),
     Mc =as.integer(mc),
     Nc =as.integer(nc),
     datac = as.complex(C),		
     betaa = as.complex(a),
     transa = as.integer(n),
     ma =as.integer(ma),
     na =as.integer(na),
     Ma =as.integer(ma),
     Na =as.integer(na),
     dataa = as.complex(A),		
     betab = as.complex(b),
     transb = as.integer(n),
     mb =as.integer(mb),
     nb =as.integer(nb),
     Mb =as.integer(mb),
     Nb =as.integer(nb),
     datab = as.complex(B)

     )

    array(output$datac,dim=dim(C))
}



c_wmpipeR <- function(a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;

    nc   = length(B[1,]);
    mc   = length(A[,1]) ;
    C = array(0.0, dim=c(mc,nc))
    c = 1.0
    n = 0
    output <- .C("c_wmpipeB",
                 betac = as.complex(c),
                 transc = as.integer(n),
                 mc =as.integer(mc),
                 nc =as.integer(nc),
                 Mc =as.integer(mc),
                 Nc =as.integer(nc),
                 datac = as.complex(C),		
                 betaa = as.complex(a),
                 transa = as.integer(n),
                 ma =as.integer(ma),
                 na =as.integer(na),
                 Ma =as.integer(ma),
                 Na =as.integer(na),
                 dataa = as.complex(A),		
                 betab = as.complex(b),
                 transb = as.integer(n),
                 mb =as.integer(mb),
                 nb =as.integer(nb),
                 Mb =as.integer(mb),
                 Nb =as.integer(nb),
                 datab = as.complex(B)
                 )

    array(output$datac,dim=dim(C))
}

c_wmaddpipeR <- function(c,C,a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;
    nc   = length(C[1,]);
    mc   = length(C[,1]) ;

    n = 0
  
   output <- .C("c_wmaddpipeB",
     betac = as.complex(c),
     transc = as.integer(n),
     mc =as.integer(mc),
     nc =as.integer(nc),
     Mc =as.integer(mc),
     Nc =as.integer(nc),
     datac = as.complex(C),		
     betaa = as.complex(a),
     transa = as.integer(n),
     ma =as.integer(ma),
     na =as.integer(na),
     Ma =as.integer(ma),
     Na =as.integer(na),
     dataa = as.complex(A),		
     betab = as.complex(b),
     transb = as.integer(n),
     mb =as.integer(mb),
     nb =as.integer(nb),
     Mb =as.integer(mb),
     Nb =as.integer(nb),
     datab = as.complex(B)

     )

    array(output$datac,dim=dim(C))
}



c_bmpipeR <- function(a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;

    nc   = length(B[1,]);
    mc   = length(A[,1]) ;
    C = array(0.0, dim=c(mc,nc))
    c = 1.0
    n = 0
    output <- .C("c_bmpipeB",
                 betac = as.complex(c),
                 transc = as.integer(n),
                 mc =as.integer(mc),
                 nc =as.integer(nc),
                 Mc =as.integer(mc),
                 Nc =as.integer(nc),
                 datac = as.complex(C),		
                 betaa = as.complex(a),
                 transa = as.integer(n),
                 ma =as.integer(ma),
                 na =as.integer(na),
                 Ma =as.integer(ma),
                 Na =as.integer(na),
                 dataa = as.complex(A),		
                 betab = as.complex(b),
                 transb = as.integer(n),
                 mb =as.integer(mb),
                 nb =as.integer(nb),
                 Mb =as.integer(mb),
                 Nb =as.integer(nb),
                 datab = as.complex(B)
                 )

    array(output$datac,dim=dim(C))
}

c_bmaddpipeR <- function(c,C,a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;
    nc   = length(C[1,]);
    mc   = length(C[,1]) ;

    n = 0
  
   output <- .C("c_bmaddpipeB",
     betac = as.complex(c),
     transc = as.integer(n),
     mc =as.integer(mc),
     nc =as.integer(nc),
     Mc =as.integer(mc),
     Nc =as.integer(nc),
     datac = as.complex(C),		
     betaa = as.complex(a),
     transa = as.integer(n),
     ma =as.integer(ma),
     na =as.integer(na),
     Ma =as.integer(ma),
     Na =as.integer(na),
     dataa = as.complex(A),		
     betab = as.complex(b),
     transb = as.integer(n),
     mb =as.integer(mb),
     nb =as.integer(nb),
     Mb =as.integer(mb),
     Nb =as.integer(nb),
     datab = as.complex(B)

     )

    array(output$datac,dim=dim(C))
}



c_smpipeR <- function(a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;

    nc   = length(B[1,]);
    mc   = length(A[,1]) ;
    C = array(0.0, dim=c(mc,nc))
    c = 1.0
    n = 0
    output <- .C("c_smpipeB",
                 betac = as.complex(c),
                 transc = as.integer(n),
                 mc =as.integer(mc),
                 nc =as.integer(nc),
                 Mc =as.integer(mc),
                 Nc =as.integer(nc),
                 datac = as.complex(C),		
                 betaa = as.complex(a),
                 transa = as.integer(n),
                 ma =as.integer(ma),
                 na =as.integer(na),
                 Ma =as.integer(ma),
                 Na =as.integer(na),
                 dataa = as.complex(A),		
                 betab = as.complex(b),
                 transb = as.integer(n),
                 mb =as.integer(mb),
                 nb =as.integer(nb),
                 Mb =as.integer(mb),
                 Nb =as.integer(nb),
                 datab = as.complex(B)
                 )

    array(output$datac,dim=dim(C))
}

c_smaddpipeR <- function(c,C,a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;
    nc   = length(C[1,]);
    mc   = length(C[,1]) ;

    n = 0
  
   output <- .C("c_smaddpipeB",
     betac = as.complex(c),
     transc = as.integer(n),
     mc =as.integer(mc),
     nc =as.integer(nc),
     Mc =as.integer(mc),
     Nc =as.integer(nc),
     datac = as.complex(C),		
     betaa = as.complex(a),
     transa = as.integer(n),
     ma =as.integer(ma),
     na =as.integer(na),
     Ma =as.integer(ma),
     Na =as.integer(na),
     dataa = as.complex(A),		
     betab = as.complex(b),
     transb = as.integer(n),
     mb =as.integer(mb),
     nb =as.integer(nb),
     Mb =as.integer(mb),
     Nb =as.integer(nb),
     datab = as.complex(B)

     )

    array(output$datac,dim=dim(C))
}



c_RmulR <- function(a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;

    nc   = length(B[1,]);
    mc   = length(A[,1]) ;
    C = array(0.0, dim=c(mc,nc))
    c = 1.0
    n = 0
    output <- .C("c_RmulB",
                 betac = as.complex(c),
                 transc = as.integer(n),
                 mc =as.integer(mc),
                 nc =as.integer(nc),
                 Mc =as.integer(mc),
                 Nc =as.integer(nc),
                 datac = as.complex(C),		
                 betaa = as.complex(a),
                 transa = as.integer(n),
                 ma =as.integer(ma),
                 na =as.integer(na),
                 Ma =as.integer(ma),
                 Na =as.integer(na),
                 dataa = as.complex(A),		
                 betab = as.complex(b),
                 transb = as.integer(n),
                 mb =as.integer(mb),
                 nb =as.integer(nb),
                 Mb =as.integer(mb),
                 Nb =as.integer(nb),
                 datab = as.complex(B)
                 )

    array(output$datac,dim=dim(C))
}

c_adaptive_wmR <- function(a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;

    nc   = length(B[1,]);
    mc   = length(A[,1]) ;
    C = array(0.0, dim=c(mc,nc))
    c = 1.0
    n = 0
    output <- .C("c_adaptive_wmB",
                 betac = as.complex(c),
                 transc = as.integer(n),
                 mc =as.integer(mc),
                 nc =as.integer(nc),
                 Mc =as.integer(mc),
                 Nc =as.integer(nc),
                 datac = as.complex(C),		
                 betaa = as.complex(a),
                 transa = as.integer(n),
                 ma =as.integer(ma),
                 na =as.integer(na),
                 Ma =as.integer(ma),
                 Na =as.integer(na),
                 dataa = as.complex(A),		
                 betab = as.complex(b),
                 transb = as.integer(n),
                 mb =as.integer(mb),
                 nb =as.integer(nb),
                 Mb =as.integer(mb),
                 Nb =as.integer(nb),
                 datab = as.complex(B)
                 )

    array(output$datac,dim=dim(C))
}

c_BMADD_PIPER <- function(c,C,a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;
    nc   = length(C[1,]);
    mc   = length(C[,1]) ;

    n = 0
  
   output <- .C("c_BMADD_PIPEB",
     betac = as.complex(c),
     transc = as.integer(n),
     mc =as.integer(mc),
     nc =as.integer(nc),
     Mc =as.integer(mc),
     Nc =as.integer(nc),
     datac = as.complex(C),		
     betaa = as.complex(a),
     transa = as.integer(n),
     ma =as.integer(ma),
     na =as.integer(na),
     Ma =as.integer(ma),
     Na =as.integer(na),
     dataa = as.complex(A),		
     betab = as.complex(b),
     transb = as.integer(n),
     mb =as.integer(mb),
     nb =as.integer(nb),
     Mb =as.integer(mb),
     Nb =as.integer(nb),
     datab = as.complex(B)

     )

    array(output$datac,dim=dim(C))
}



c_BMADDR <- function(c,C,a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;
    nc   = length(C[1,]);
    mc   = length(C[,1]) ;

    n = 0
  
   output <- .C("c_BMADDB",
     betac = as.complex(c),
     transc = as.integer(n),
     mc =as.integer(mc),
     nc =as.integer(nc),
     Mc =as.integer(mc),
     Nc =as.integer(nc),
     datac = as.complex(C),		
     betaa = as.complex(a),
     transa = as.integer(n),
     ma =as.integer(ma),
     na =as.integer(na),
     Ma =as.integer(ma),
     Na =as.integer(na),
     dataa = as.complex(A),		
     betab = as.complex(b),
     transb = as.integer(n),
     mb =as.integer(mb),
     nb =as.integer(nb),
     Mb =as.integer(mb),
     Nb =as.integer(nb),
     datab = as.complex(B)

     )

    array(output$datac,dim=dim(C))
}



c_BMOWR_PIPER <- function(a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;

    nc   = length(B[1,]);
    mc   = length(A[,1]) ;
    C = array(0.0, dim=c(mc,nc))
    c = 1.0
    n = 0
    output <- .C("c_BMOWR_PIPEB",
                 betac = as.complex(c),
                 transc = as.integer(n),
                 mc =as.integer(mc),
                 nc =as.integer(nc),
                 Mc =as.integer(mc),
                 Nc =as.integer(nc),
                 datac = as.complex(C),		
                 betaa = as.complex(a),
                 transa = as.integer(n),
                 ma =as.integer(ma),
                 na =as.integer(na),
                 Ma =as.integer(ma),
                 Na =as.integer(na),
                 dataa = as.complex(A),		
                 betab = as.complex(b),
                 transb = as.integer(n),
                 mb =as.integer(mb),
                 nb =as.integer(nb),
                 Mb =as.integer(mb),
                 Nb =as.integer(nb),
                 datab = as.complex(B)
                 )

    array(output$datac,dim=dim(C))
}

c_BMOWRR <- function(a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;

    nc   = length(B[1,]);
    mc   = length(A[,1]) ;
    C = array(0.0, dim=c(mc,nc))
    c = 1.0
    n = 0
    output <- .C("c_BMOWRB",
                 betac = as.complex(c),
                 transc = as.integer(n),
                 mc =as.integer(mc),
                 nc =as.integer(nc),
                 Mc =as.integer(mc),
                 Nc =as.integer(nc),
                 datac = as.complex(C),		
                 betaa = as.complex(a),
                 transa = as.integer(n),
                 ma =as.integer(ma),
                 na =as.integer(na),
                 Ma =as.integer(ma),
                 Na =as.integer(na),
                 dataa = as.complex(A),		
                 betab = as.complex(b),
                 transb = as.integer(n),
                 mb =as.integer(mb),
                 nb =as.integer(nb),
                 Mb =as.integer(mb),
                 Nb =as.integer(nb),
                 datab = as.complex(B)
                 )

    array(output$datac,dim=dim(C))
}

z_dcmulR <- function(a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;

    nc   = length(B[1,]);
    mc   = length(A[,1]) ;
    C = array(0.0, dim=c(mc,nc))
    c = 1.0
    n = 0
    output <- .C("z_dcmulB",
                 betac = as.complex(c),
                 transc = as.integer(n),
                 mc =as.integer(mc),
                 nc =as.integer(nc),
                 Mc =as.integer(mc),
                 Nc =as.integer(nc),
                 datac = as.complex(C),		
                 betaa = as.complex(a),
                 transa = as.integer(n),
                 ma =as.integer(ma),
                 na =as.integer(na),
                 Ma =as.integer(ma),
                 Na =as.integer(na),
                 dataa = as.complex(A),		
                 betab = as.complex(b),
                 transb = as.integer(n),
                 mb =as.integer(mb),
                 nb =as.integer(nb),
                 Mb =as.integer(mb),
                 Nb =as.integer(nb),
                 datab = as.complex(B),DUP=FALSE
                 )

    array(output$datac,dim=dim(C))
}

z_mulR <- function(a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;

    nc   = length(B[1,]);
    mc   = length(A[,1]) ;
    C = array(0.0, dim=c(mc,nc))
    c = 1.0
    n = 0
    output <- .C("z_mulB",
                 betac = as.complex(c),
                 transc = as.integer(n),
                 mc =as.integer(mc),
                 nc =as.integer(nc),
                 Mc =as.integer(mc),
                 Nc =as.integer(nc),
                 datac = as.complex(C),		
                 betaa = as.complex(a),
                 transa = as.integer(n),
                 ma =as.integer(ma),
                 na =as.integer(na),
                 Ma =as.integer(ma),
                 Na =as.integer(na),
                 dataa = as.complex(A),		
                 betab = as.complex(b),
                 transb = as.integer(n),
                 mb =as.integer(mb),
                 nb =as.integer(nb),
                 Mb =as.integer(mb),
                 Nb =as.integer(nb),
                 datab = as.complex(B),DUP=FALSE
                 )

    array(output$datac,dim=dim(C))
}

z_mulptR <- function(a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;

    nc   = length(B[1,]);
    mc   = length(A[,1]) ;
    C = array(0.0, dim=c(mc,nc))
    c = 1.0
    n = 0
    output <- .C("z_mulptB",
                 betac = as.complex(c),
                 transc = as.integer(n),
                 mc =as.integer(mc),
                 nc =as.integer(nc),
                 Mc =as.integer(mc),
                 Nc =as.integer(nc),
                 datac = as.complex(C),		
                 betaa = as.complex(a),
                 transa = as.integer(n),
                 ma =as.integer(ma),
                 na =as.integer(na),
                 Ma =as.integer(ma),
                 Na =as.integer(na),
                 dataa = as.complex(A),		
                 betab = as.complex(b),
                 transb = as.integer(n),
                 mb =as.integer(mb),
                 nb =as.integer(nb),
                 Mb =as.integer(mb),
                 Nb =as.integer(nb),
                 datab = as.complex(B),DUP=FALSE
                 )

    array(output$datac,dim=dim(C))
}

z_maddR <- function(c,C,a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;
    nc   = length(C[1,]);
    mc   = length(C[,1]) ;

    n = 0
  
   output <- .C("z_maddB",
     betac = as.complex(c),
     transc = as.integer(n),
     mc =as.integer(mc),
     nc =as.integer(nc),
     Mc =as.integer(mc),
     Nc =as.integer(nc),
     datac = as.complex(C),		
     betaa = as.complex(a),
     transa = as.integer(n),
     ma =as.integer(ma),
     na =as.integer(na),
     Ma =as.integer(ma),
     Na =as.integer(na),
     dataa = as.complex(A),		
     betab = as.complex(b),
     transb = as.integer(n),
     mb =as.integer(mb),
     nb =as.integer(nb),
     Mb =as.integer(mb),
     Nb =as.integer(nb),
     datab = as.complex(B),DUP=FALSE

     )

    array(output$datac,dim=dim(C))
}



z_saddmulR <- function(c,C,a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;
    nc   = length(C[1,]);
    mc   = length(C[,1]) ;

    n = 0
  
   output <- .C("z_saddmulB",
     betac = as.complex(c),
     transc = as.integer(n),
     mc =as.integer(mc),
     nc =as.integer(nc),
     Mc =as.integer(mc),
     Nc =as.integer(nc),
     datac = as.complex(C),		
     betaa = as.complex(a),
     transa = as.integer(n),
     ma =as.integer(ma),
     na =as.integer(na),
     Ma =as.integer(ma),
     Na =as.integer(na),
     dataa = as.complex(A),		
     betab = as.complex(b),
     transb = as.integer(n),
     mb =as.integer(mb),
     nb =as.integer(nb),
     Mb =as.integer(mb),
     Nb =as.integer(nb),
     datab = as.complex(B),DUP=FALSE

     )

    array(output$datac,dim=dim(C))
}



z_smulR <- function(a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;

    nc   = length(B[1,]);
    mc   = length(A[,1]) ;
    C = array(0.0, dim=c(mc,nc))
    c = 1.0
    n = 0
    output <- .C("z_smulB",
                 betac = as.complex(c),
                 transc = as.integer(n),
                 mc =as.integer(mc),
                 nc =as.integer(nc),
                 Mc =as.integer(mc),
                 Nc =as.integer(nc),
                 datac = as.complex(C),		
                 betaa = as.complex(a),
                 transa = as.integer(n),
                 ma =as.integer(ma),
                 na =as.integer(na),
                 Ma =as.integer(ma),
                 Na =as.integer(na),
                 dataa = as.complex(A),		
                 betab = as.complex(b),
                 transb = as.integer(n),
                 mb =as.integer(mb),
                 nb =as.integer(nb),
                 Mb =as.integer(mb),
                 Nb =as.integer(nb),
                 datab = as.complex(B),DUP=FALSE
                 )

    array(output$datac,dim=dim(C))
}

z_wmulR <- function(a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;

    nc   = length(B[1,]);
    mc   = length(A[,1]) ;
    C = array(0.0, dim=c(mc,nc))
    c = 1.0
    n = 0
    output <- .C("z_wmulB",
                 betac = as.complex(c),
                 transc = as.integer(n),
                 mc =as.integer(mc),
                 nc =as.integer(nc),
                 Mc =as.integer(mc),
                 Nc =as.integer(nc),
                 datac = as.complex(C),		
                 betaa = as.complex(a),
                 transa = as.integer(n),
                 ma =as.integer(ma),
                 na =as.integer(na),
                 Ma =as.integer(ma),
                 Na =as.integer(na),
                 dataa = as.complex(A),		
                 betab = as.complex(b),
                 transb = as.integer(n),
                 mb =as.integer(mb),
                 nb =as.integer(nb),
                 Mb =as.integer(mb),
                 Nb =as.integer(nb),
                 datab = as.complex(B),DUP=FALSE
                 )

    array(output$datac,dim=dim(C))
}

z_waddmulR <- function(c,C,a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;
    nc   = length(C[1,]);
    mc   = length(C[,1]) ;

    n = 0
  
   output <- .C("z_waddmulB",
     betac = as.complex(c),
     transc = as.integer(n),
     mc =as.integer(mc),
     nc =as.integer(nc),
     Mc =as.integer(mc),
     Nc =as.integer(nc),
     datac = as.complex(C),		
     betaa = as.complex(a),
     transa = as.integer(n),
     ma =as.integer(ma),
     na =as.integer(na),
     Ma =as.integer(ma),
     Na =as.integer(na),
     dataa = as.complex(A),		
     betab = as.complex(b),
     transb = as.integer(n),
     mb =as.integer(mb),
     nb =as.integer(nb),
     Mb =as.integer(mb),
     Nb =as.integer(nb),
     datab = as.complex(B),DUP=FALSE

     )

    array(output$datac,dim=dim(C))
}



z_wmR <- function(a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;

    nc   = length(B[1,]);
    mc   = length(A[,1]) ;
    C = array(0.0, dim=c(mc,nc))
    c = 1.0
    n = 0
    output <- .C("z_wmB",
                 betac = as.complex(c),
                 transc = as.integer(n),
                 mc =as.integer(mc),
                 nc =as.integer(nc),
                 Mc =as.integer(mc),
                 Nc =as.integer(nc),
                 datac = as.complex(C),		
                 betaa = as.complex(a),
                 transa = as.integer(n),
                 ma =as.integer(ma),
                 na =as.integer(na),
                 Ma =as.integer(ma),
                 Na =as.integer(na),
                 dataa = as.complex(A),		
                 betab = as.complex(b),
                 transb = as.integer(n),
                 mb =as.integer(mb),
                 nb =as.integer(nb),
                 Mb =as.integer(mb),
                 Nb =as.integer(nb),
                 datab = as.complex(B),DUP=FALSE
                 )

    array(output$datac,dim=dim(C))
}

z_wmaddR <- function(c,C,a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;
    nc   = length(C[1,]);
    mc   = length(C[,1]) ;

    n = 0
  
   output <- .C("z_wmaddB",
     betac = as.complex(c),
     transc = as.integer(n),
     mc =as.integer(mc),
     nc =as.integer(nc),
     Mc =as.integer(mc),
     Nc =as.integer(nc),
     datac = as.complex(C),		
     betaa = as.complex(a),
     transa = as.integer(n),
     ma =as.integer(ma),
     na =as.integer(na),
     Ma =as.integer(ma),
     Na =as.integer(na),
     dataa = as.complex(A),		
     betab = as.complex(b),
     transb = as.integer(n),
     mb =as.integer(mb),
     nb =as.integer(nb),
     Mb =as.integer(mb),
     Nb =as.integer(nb),
     datab = as.complex(B),DUP=FALSE

     )

    array(output$datac,dim=dim(C))
}



z_adaptive_smulR <- function(a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;

    nc   = length(B[1,]);
    mc   = length(A[,1]) ;
    C = array(0.0, dim=c(mc,nc))
    c = 1.0
    n = 0
    output <- .C("z_adaptive_smulB",
                 betac = as.complex(c),
                 transc = as.integer(n),
                 mc =as.integer(mc),
                 nc =as.integer(nc),
                 Mc =as.integer(mc),
                 Nc =as.integer(nc),
                 datac = as.complex(C),		
                 betaa = as.complex(a),
                 transa = as.integer(n),
                 ma =as.integer(ma),
                 na =as.integer(na),
                 Ma =as.integer(ma),
                 Na =as.integer(na),
                 dataa = as.complex(A),		
                 betab = as.complex(b),
                 transb = as.integer(n),
                 mb =as.integer(mb),
                 nb =as.integer(nb),
                 Mb =as.integer(mb),
                 Nb =as.integer(nb),
                 datab = as.complex(B),DUP=FALSE
                 )

    array(output$datac,dim=dim(C))
}

z_omulR <- function(a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;

    nc   = length(B[1,]);
    mc   = length(A[,1]) ;
    C = array(0.0, dim=c(mc,nc))
    c = 1.0
    n = 0
    output <- .C("z_omulB",
                 betac = as.complex(c),
                 transc = as.integer(n),
                 mc =as.integer(mc),
                 nc =as.integer(nc),
                 Mc =as.integer(mc),
                 Nc =as.integer(nc),
                 datac = as.complex(C),		
                 betaa = as.complex(a),
                 transa = as.integer(n),
                 ma =as.integer(ma),
                 na =as.integer(na),
                 Ma =as.integer(ma),
                 Na =as.integer(na),
                 dataa = as.complex(A),		
                 betab = as.complex(b),
                 transb = as.integer(n),
                 mb =as.integer(mb),
                 nb =as.integer(nb),
                 Mb =as.integer(mb),
                 Nb =as.integer(nb),
                 datab = as.complex(B),DUP=FALSE
                 )

    array(output$datac,dim=dim(C))
}

z_oaddmulR <- function(c,C,a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;
    nc   = length(C[1,]);
    mc   = length(C[,1]) ;

    n = 0
  
   output <- .C("z_oaddmulB",
     betac = as.complex(c),
     transc = as.integer(n),
     mc =as.integer(mc),
     nc =as.integer(nc),
     Mc =as.integer(mc),
     Nc =as.integer(nc),
     datac = as.complex(C),		
     betaa = as.complex(a),
     transa = as.integer(n),
     ma =as.integer(ma),
     na =as.integer(na),
     Ma =as.integer(ma),
     Na =as.integer(na),
     dataa = as.complex(A),		
     betab = as.complex(b),
     transb = as.integer(n),
     mb =as.integer(mb),
     nb =as.integer(nb),
     Mb =as.integer(mb),
     Nb =as.integer(nb),
     datab = as.complex(B),DUP=FALSE

     )

    array(output$datac,dim=dim(C))
}



z_owmulR <- function(a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;

    nc   = length(B[1,]);
    mc   = length(A[,1]) ;
    C = array(0.0, dim=c(mc,nc))
    c = 1.0
    n = 0
    output <- .C("z_owmulB",
                 betac = as.complex(c),
                 transc = as.integer(n),
                 mc =as.integer(mc),
                 nc =as.integer(nc),
                 Mc =as.integer(mc),
                 Nc =as.integer(nc),
                 datac = as.complex(C),		
                 betaa = as.complex(a),
                 transa = as.integer(n),
                 ma =as.integer(ma),
                 na =as.integer(na),
                 Ma =as.integer(ma),
                 Na =as.integer(na),
                 dataa = as.complex(A),		
                 betab = as.complex(b),
                 transb = as.integer(n),
                 mb =as.integer(mb),
                 nb =as.integer(nb),
                 Mb =as.integer(mb),
                 Nb =as.integer(nb),
                 datab = as.complex(B),DUP=FALSE
                 )

    array(output$datac,dim=dim(C))
}

z_owaddmulR <- function(c,C,a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;
    nc   = length(C[1,]);
    mc   = length(C[,1]) ;

    n = 0
  
   output <- .C("z_owaddmulB",
     betac = as.complex(c),
     transc = as.integer(n),
     mc =as.integer(mc),
     nc =as.integer(nc),
     Mc =as.integer(mc),
     Nc =as.integer(nc),
     datac = as.complex(C),		
     betaa = as.complex(a),
     transa = as.integer(n),
     ma =as.integer(ma),
     na =as.integer(na),
     Ma =as.integer(ma),
     Na =as.integer(na),
     dataa = as.complex(A),		
     betab = as.complex(b),
     transb = as.integer(n),
     mb =as.integer(mb),
     nb =as.integer(nb),
     Mb =as.integer(mb),
     Nb =as.integer(nb),
     datab = as.complex(B),DUP=FALSE

     )

    array(output$datac,dim=dim(C))
}



z_bmR <- function(a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;

    nc   = length(B[1,]);
    mc   = length(A[,1]) ;
    C = array(0.0, dim=c(mc,nc))
    c = 1.0
    n = 0
    output <- .C("z_bmB",
                 betac = as.complex(c),
                 transc = as.integer(n),
                 mc =as.integer(mc),
                 nc =as.integer(nc),
                 Mc =as.integer(mc),
                 Nc =as.integer(nc),
                 datac = as.complex(C),		
                 betaa = as.complex(a),
                 transa = as.integer(n),
                 ma =as.integer(ma),
                 na =as.integer(na),
                 Ma =as.integer(ma),
                 Na =as.integer(na),
                 dataa = as.complex(A),		
                 betab = as.complex(b),
                 transb = as.integer(n),
                 mb =as.integer(mb),
                 nb =as.integer(nb),
                 Mb =as.integer(mb),
                 Nb =as.integer(nb),
                 datab = as.complex(B),DUP=FALSE
                 )

    array(output$datac,dim=dim(C))
}

z_bmaddR <- function(c,C,a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;
    nc   = length(C[1,]);
    mc   = length(C[,1]) ;

    n = 0
  
   output <- .C("z_bmaddB",
     betac = as.complex(c),
     transc = as.integer(n),
     mc =as.integer(mc),
     nc =as.integer(nc),
     Mc =as.integer(mc),
     Nc =as.integer(nc),
     datac = as.complex(C),		
     betaa = as.complex(a),
     transa = as.integer(n),
     ma =as.integer(ma),
     na =as.integer(na),
     Ma =as.integer(ma),
     Na =as.integer(na),
     dataa = as.complex(A),		
     betab = as.complex(b),
     transb = as.integer(n),
     mb =as.integer(mb),
     nb =as.integer(nb),
     Mb =as.integer(mb),
     Nb =as.integer(nb),
     datab = as.complex(B),DUP=FALSE

     )

    array(output$datac,dim=dim(C))
}



z_ptaddmulR <- function(c,C,a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;
    nc   = length(C[1,]);
    mc   = length(C[,1]) ;

    n = 0
  
   output <- .C("z_ptaddmulB",
     betac = as.complex(c),
     transc = as.integer(n),
     mc =as.integer(mc),
     nc =as.integer(nc),
     Mc =as.integer(mc),
     Nc =as.integer(nc),
     datac = as.complex(C),		
     betaa = as.complex(a),
     transa = as.integer(n),
     ma =as.integer(ma),
     na =as.integer(na),
     Ma =as.integer(ma),
     Na =as.integer(na),
     dataa = as.complex(A),		
     betab = as.complex(b),
     transb = as.integer(n),
     mb =as.integer(mb),
     nb =as.integer(nb),
     Mb =as.integer(mb),
     Nb =as.integer(nb),
     datab = as.complex(B),DUP=FALSE

     )

    array(output$datac,dim=dim(C))
}



z_wmpipeR <- function(a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;

    nc   = length(B[1,]);
    mc   = length(A[,1]) ;
    C = array(0.0, dim=c(mc,nc))
    c = 1.0
    n = 0
    output <- .C("z_wmpipeB",
                 betac = as.complex(c),
                 transc = as.integer(n),
                 mc =as.integer(mc),
                 nc =as.integer(nc),
                 Mc =as.integer(mc),
                 Nc =as.integer(nc),
                 datac = as.complex(C),		
                 betaa = as.complex(a),
                 transa = as.integer(n),
                 ma =as.integer(ma),
                 na =as.integer(na),
                 Ma =as.integer(ma),
                 Na =as.integer(na),
                 dataa = as.complex(A),		
                 betab = as.complex(b),
                 transb = as.integer(n),
                 mb =as.integer(mb),
                 nb =as.integer(nb),
                 Mb =as.integer(mb),
                 Nb =as.integer(nb),
                 datab = as.complex(B),DUP=FALSE
                 )

    array(output$datac,dim=dim(C))
}

z_wmaddpipeR <- function(c,C,a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;
    nc   = length(C[1,]);
    mc   = length(C[,1]) ;

    n = 0
  
   output <- .C("z_wmaddpipeB",
     betac = as.complex(c),
     transc = as.integer(n),
     mc =as.integer(mc),
     nc =as.integer(nc),
     Mc =as.integer(mc),
     Nc =as.integer(nc),
     datac = as.complex(C),		
     betaa = as.complex(a),
     transa = as.integer(n),
     ma =as.integer(ma),
     na =as.integer(na),
     Ma =as.integer(ma),
     Na =as.integer(na),
     dataa = as.complex(A),		
     betab = as.complex(b),
     transb = as.integer(n),
     mb =as.integer(mb),
     nb =as.integer(nb),
     Mb =as.integer(mb),
     Nb =as.integer(nb),
     datab = as.complex(B),DUP=FALSE

     )

    array(output$datac,dim=dim(C))
}



z_bmpipeR <- function(a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;

    nc   = length(B[1,]);
    mc   = length(A[,1]) ;
    C = array(0.0, dim=c(mc,nc))
    c = 1.0
    n = 0
    output <- .C("z_bmpipeB",
                 betac = as.complex(c),
                 transc = as.integer(n),
                 mc =as.integer(mc),
                 nc =as.integer(nc),
                 Mc =as.integer(mc),
                 Nc =as.integer(nc),
                 datac = as.complex(C),		
                 betaa = as.complex(a),
                 transa = as.integer(n),
                 ma =as.integer(ma),
                 na =as.integer(na),
                 Ma =as.integer(ma),
                 Na =as.integer(na),
                 dataa = as.complex(A),		
                 betab = as.complex(b),
                 transb = as.integer(n),
                 mb =as.integer(mb),
                 nb =as.integer(nb),
                 Mb =as.integer(mb),
                 Nb =as.integer(nb),
                 datab = as.complex(B),DUP=FALSE
                 )

    array(output$datac,dim=dim(C))
}

z_bmaddpipeR <- function(c,C,a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;
    nc   = length(C[1,]);
    mc   = length(C[,1]) ;

    n = 0
  
   output <- .C("z_bmaddpipeB",
     betac = as.complex(c),
     transc = as.integer(n),
     mc =as.integer(mc),
     nc =as.integer(nc),
     Mc =as.integer(mc),
     Nc =as.integer(nc),
     datac = as.complex(C),		
     betaa = as.complex(a),
     transa = as.integer(n),
     ma =as.integer(ma),
     na =as.integer(na),
     Ma =as.integer(ma),
     Na =as.integer(na),
     dataa = as.complex(A),		
     betab = as.complex(b),
     transb = as.integer(n),
     mb =as.integer(mb),
     nb =as.integer(nb),
     Mb =as.integer(mb),
     Nb =as.integer(nb),
     datab = as.complex(B),DUP=FALSE

     )

    array(output$datac,dim=dim(C))
}



z_smpipeR <- function(a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;

    nc   = length(B[1,]);
    mc   = length(A[,1]) ;
    C = array(0.0, dim=c(mc,nc))
    c = 1.0
    n = 0
    output <- .C("z_smpipeB",
                 betac = as.complex(c),
                 transc = as.integer(n),
                 mc =as.integer(mc),
                 nc =as.integer(nc),
                 Mc =as.integer(mc),
                 Nc =as.integer(nc),
                 datac = as.complex(C),		
                 betaa = as.complex(a),
                 transa = as.integer(n),
                 ma =as.integer(ma),
                 na =as.integer(na),
                 Ma =as.integer(ma),
                 Na =as.integer(na),
                 dataa = as.complex(A),		
                 betab = as.complex(b),
                 transb = as.integer(n),
                 mb =as.integer(mb),
                 nb =as.integer(nb),
                 Mb =as.integer(mb),
                 Nb =as.integer(nb),
                 datab = as.complex(B),DUP=FALSE
                 )

    array(output$datac,dim=dim(C))
}

z_smaddpipeR <- function(c,C,a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;
    nc   = length(C[1,]);
    mc   = length(C[,1]) ;

    n = 0
  
   output <- .C("z_smaddpipeB",
     betac = as.complex(c),
     transc = as.integer(n),
     mc =as.integer(mc),
     nc =as.integer(nc),
     Mc =as.integer(mc),
     Nc =as.integer(nc),
     datac = as.complex(C),		
     betaa = as.complex(a),
     transa = as.integer(n),
     ma =as.integer(ma),
     na =as.integer(na),
     Ma =as.integer(ma),
     Na =as.integer(na),
     dataa = as.complex(A),		
     betab = as.complex(b),
     transb = as.integer(n),
     mb =as.integer(mb),
     nb =as.integer(nb),
     Mb =as.integer(mb),
     Nb =as.integer(nb),
     datab = as.complex(B),DUP=FALSE

     )

    array(output$datac,dim=dim(C))
}



z_RmulR <- function(a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;

    nc   = length(B[1,]);
    mc   = length(A[,1]) ;
    C = array(0.0, dim=c(mc,nc))
    c = 1.0
    n = 0
    output <- .C("z_RmulB",
                 betac = as.complex(c),
                 transc = as.integer(n),
                 mc =as.integer(mc),
                 nc =as.integer(nc),
                 Mc =as.integer(mc),
                 Nc =as.integer(nc),
                 datac = as.complex(C),		
                 betaa = as.complex(a),
                 transa = as.integer(n),
                 ma =as.integer(ma),
                 na =as.integer(na),
                 Ma =as.integer(ma),
                 Na =as.integer(na),
                 dataa = as.complex(A),		
                 betab = as.complex(b),
                 transb = as.integer(n),
                 mb =as.integer(mb),
                 nb =as.integer(nb),
                 Mb =as.integer(mb),
                 Nb =as.integer(nb),
                 datab = as.complex(B),DUP=FALSE
                 )

    array(output$datac,dim=dim(C))
}

z_adaptive_wmR <- function(a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;

    nc   = length(B[1,]);
    mc   = length(A[,1]) ;
    C = array(0.0, dim=c(mc,nc))
    c = 1.0
    n = 0
    output <- .C("z_adaptive_wmB",
                 betac = as.complex(c),
                 transc = as.integer(n),
                 mc =as.integer(mc),
                 nc =as.integer(nc),
                 Mc =as.integer(mc),
                 Nc =as.integer(nc),
                 datac = as.complex(C),		
                 betaa = as.complex(a),
                 transa = as.integer(n),
                 ma =as.integer(ma),
                 na =as.integer(na),
                 Ma =as.integer(ma),
                 Na =as.integer(na),
                 dataa = as.complex(A),		
                 betab = as.complex(b),
                 transb = as.integer(n),
                 mb =as.integer(mb),
                 nb =as.integer(nb),
                 Mb =as.integer(mb),
                 Nb =as.integer(nb),
                 datab = as.complex(B),DUP=FALSE
                 )

    array(output$datac,dim=dim(C))
}

z_BMADD_PIPER <- function(c,C,a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;
    nc   = length(C[1,]);
    mc   = length(C[,1]) ;

    n = 0
  
   output <- .C("z_BMADD_PIPEB",
     betac = as.complex(c),
     transc = as.integer(n),
     mc =as.integer(mc),
     nc =as.integer(nc),
     Mc =as.integer(mc),
     Nc =as.integer(nc),
     datac = as.complex(C),		
     betaa = as.complex(a),
     transa = as.integer(n),
     ma =as.integer(ma),
     na =as.integer(na),
     Ma =as.integer(ma),
     Na =as.integer(na),
     dataa = as.complex(A),		
     betab = as.complex(b),
     transb = as.integer(n),
     mb =as.integer(mb),
     nb =as.integer(nb),
     Mb =as.integer(mb),
     Nb =as.integer(nb),
     datab = as.complex(B),DUP=FALSE

     )

    array(output$datac,dim=dim(C))
}



z_BMADDR <- function(c,C,a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;
    nc   = length(C[1,]);
    mc   = length(C[,1]) ;

    n = 0
  
   output <- .C("z_BMADDB",
     betac = as.complex(c),
     transc = as.integer(n),
     mc =as.integer(mc),
     nc =as.integer(nc),
     Mc =as.integer(mc),
     Nc =as.integer(nc),
     datac = as.complex(C),		
     betaa = as.complex(a),
     transa = as.integer(n),
     ma =as.integer(ma),
     na =as.integer(na),
     Ma =as.integer(ma),
     Na =as.integer(na),
     dataa = as.complex(A),		
     betab = as.complex(b),
     transb = as.integer(n),
     mb =as.integer(mb),
     nb =as.integer(nb),
     Mb =as.integer(mb),
     Nb =as.integer(nb),
     datab = as.complex(B),DUP=FALSE

     )

    array(output$datac,dim=dim(C))
}



z_BMOWR_PIPER <- function(a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;

    nc   = length(B[1,]);
    mc   = length(A[,1]) ;
    C = array(0.0, dim=c(mc,nc))
    c = 1.0
    n = 0
    output <- .C("z_BMOWR_PIPEB",
                 betac = as.complex(c),
                 transc = as.integer(n),
                 mc =as.integer(mc),
                 nc =as.integer(nc),
                 Mc =as.integer(mc),
                 Nc =as.integer(nc),
                 datac = as.complex(C),		
                 betaa = as.complex(a),
                 transa = as.integer(n),
                 ma =as.integer(ma),
                 na =as.integer(na),
                 Ma =as.integer(ma),
                 Na =as.integer(na),
                 dataa = as.complex(A),		
                 betab = as.complex(b),
                 transb = as.integer(n),
                 mb =as.integer(mb),
                 nb =as.integer(nb),
                 Mb =as.integer(mb),
                 Nb =as.integer(nb),
                 datab = as.complex(B),DUP=FALSE
                 )

    array(output$datac,dim=dim(C))
}

z_BMOWRR <- function(a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;

    nc   = length(B[1,]);
    mc   = length(A[,1]) ;
    C = array(0.0, dim=c(mc,nc))
    c = 1.0
    n = 0
    output <- .C("z_BMOWRB",
                 betac = as.complex(c),
                 transc = as.integer(n),
                 mc =as.integer(mc),
                 nc =as.integer(nc),
                 Mc =as.integer(mc),
                 Nc =as.integer(nc),
                 datac = as.complex(C),		
                 betaa = as.complex(a),
                 transa = as.integer(n),
                 ma =as.integer(ma),
                 na =as.integer(na),
                 Ma =as.integer(ma),
                 Na =as.integer(na),
                 dataa = as.complex(A),		
                 betab = as.complex(b),
                 transb = as.integer(n),
                 mb =as.integer(mb),
                 nb =as.integer(nb),
                 Mb =as.integer(mb),
                 Nb =as.integer(nb),
                 datab = as.complex(B),DUP=FALSE
                 )

    array(output$datac,dim=dim(C))
}

s_mm_leaf_computation_maddR <- function(c,C,a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;
    nc   = length(C[1,]);
    mc   = length(C[,1]) ;

    n = 0
  
   output <- .C("s_mm_leaf_computation_maddB",
     betac = as.single(c),
     transc = as.integer(n),
     mc =as.integer(mc),
     nc =as.integer(nc),
     Mc =as.integer(mc),
     Nc =as.integer(nc),
     datac = as.single(C),		
     betaa = as.single(a),
     transa = as.integer(n),
     ma =as.integer(ma),
     na =as.integer(na),
     Ma =as.integer(ma),
     Na =as.integer(na),
     dataa = as.single(A),		
     betab = as.single(b),
     transb = as.integer(n),
     mb =as.integer(mb),
     nb =as.integer(nb),
     Mb =as.integer(mb),
     Nb =as.integer(nb),
     datab = as.single(B)

     )

    array(output$datac,dim=dim(C))
}



s_mm_leaf_computationR <- function(a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;

    nc   = length(B[1,]);
    mc   = length(A[,1]) ;
    C = array(0.0, dim=c(mc,nc))
    c = 1.0
    n = 0
    output <- .C("s_mm_leaf_computationB",
                 betac = as.single(c),
                 transc = as.integer(n),
                 mc =as.integer(mc),
                 nc =as.integer(nc),
                 Mc =as.integer(mc),
                 Nc =as.integer(nc),
                 datac = as.single(C),		
                 betaa = as.single(a),
                 transa = as.integer(n),
                 ma =as.integer(ma),
                 na =as.integer(na),
                 Ma =as.integer(ma),
                 Na =as.integer(na),
                 dataa = as.single(A),		
                 betab = as.single(b),
                 transb = as.integer(n),
                 mb =as.integer(mb),
                 nb =as.integer(nb),
                 Mb =as.integer(mb),
                 Nb =as.integer(nb),
                 datab = as.single(B)
                 )

    array(output$datac,dim=dim(C))
}

d_mm_leaf_computation_maddR <- function(c,C,a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;
    nc   = length(C[1,]);
    mc   = length(C[,1]) ;

    n = 0
  
   output <- .C("d_mm_leaf_computation_maddB",
     betac = as.double(c),
     transc = as.integer(n),
     mc =as.integer(mc),
     nc =as.integer(nc),
     Mc =as.integer(mc),
     Nc =as.integer(nc),
     datac = as.double(C),		
     betaa = as.double(a),
     transa = as.integer(n),
     ma =as.integer(ma),
     na =as.integer(na),
     Ma =as.integer(ma),
     Na =as.integer(na),
     dataa = as.double(A),		
     betab = as.double(b),
     transb = as.integer(n),
     mb =as.integer(mb),
     nb =as.integer(nb),
     Mb =as.integer(mb),
     Nb =as.integer(nb),
     datab = as.double(B),DUP=FALSE

     )

    array(output$datac,dim=dim(C))
}



d_mm_leaf_computationR <- function(a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;

    nc   = length(B[1,]);
    mc   = length(A[,1]) ;
    C = array(0.0, dim=c(mc,nc))
    c = 1.0
    n = 0
    output <- .C("d_mm_leaf_computationB",
                 betac = as.double(c),
                 transc = as.integer(n),
                 mc =as.integer(mc),
                 nc =as.integer(nc),
                 Mc =as.integer(mc),
                 Nc =as.integer(nc),
                 datac = as.double(C),		
                 betaa = as.double(a),
                 transa = as.integer(n),
                 ma =as.integer(ma),
                 na =as.integer(na),
                 Ma =as.integer(ma),
                 Na =as.integer(na),
                 dataa = as.double(A),		
                 betab = as.double(b),
                 transb = as.integer(n),
                 mb =as.integer(mb),
                 nb =as.integer(nb),
                 Mb =as.integer(mb),
                 Nb =as.integer(nb),
                 datab = as.double(B),DUP=FALSE
                 )

    array(output$datac,dim=dim(C))
}

c_mm_leaf_computation_maddR <- function(c,C,a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;
    nc   = length(C[1,]);
    mc   = length(C[,1]) ;

    n = 0
  
   output <- .C("c_mm_leaf_computation_maddB",
     betac = as.complex(c),
     transc = as.integer(n),
     mc =as.integer(mc),
     nc =as.integer(nc),
     Mc =as.integer(mc),
     Nc =as.integer(nc),
     datac = as.complex(C),		
     betaa = as.complex(a),
     transa = as.integer(n),
     ma =as.integer(ma),
     na =as.integer(na),
     Ma =as.integer(ma),
     Na =as.integer(na),
     dataa = as.complex(A),		
     betab = as.complex(b),
     transb = as.integer(n),
     mb =as.integer(mb),
     nb =as.integer(nb),
     Mb =as.integer(mb),
     Nb =as.integer(nb),
     datab = as.complex(B)

     )

    array(output$datac,dim=dim(C))
}



c_mm_leaf_computationR <- function(a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;

    nc   = length(B[1,]);
    mc   = length(A[,1]) ;
    C = array(0.0, dim=c(mc,nc))
    c = 1.0
    n = 0
    output <- .C("c_mm_leaf_computationB",
                 betac = as.complex(c),
                 transc = as.integer(n),
                 mc =as.integer(mc),
                 nc =as.integer(nc),
                 Mc =as.integer(mc),
                 Nc =as.integer(nc),
                 datac = as.complex(C),		
                 betaa = as.complex(a),
                 transa = as.integer(n),
                 ma =as.integer(ma),
                 na =as.integer(na),
                 Ma =as.integer(ma),
                 Na =as.integer(na),
                 dataa = as.complex(A),		
                 betab = as.complex(b),
                 transb = as.integer(n),
                 mb =as.integer(mb),
                 nb =as.integer(nb),
                 Mb =as.integer(mb),
                 Nb =as.integer(nb),
                 datab = as.complex(B)
                 )

    array(output$datac,dim=dim(C))
}

z_mm_leaf_computation_maddR <- function(c,C,a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;
    nc   = length(C[1,]);
    mc   = length(C[,1]) ;

    n = 0
  
   output <- .C("z_mm_leaf_computation_maddB",
     betac = as.complex(c),
     transc = as.integer(n),
     mc =as.integer(mc),
     nc =as.integer(nc),
     Mc =as.integer(mc),
     Nc =as.integer(nc),
     datac = as.complex(C),		
     betaa = as.complex(a),
     transa = as.integer(n),
     ma =as.integer(ma),
     na =as.integer(na),
     Ma =as.integer(ma),
     Na =as.integer(na),
     dataa = as.complex(A),		
     betab = as.complex(b),
     transb = as.integer(n),
     mb =as.integer(mb),
     nb =as.integer(nb),
     Mb =as.integer(mb),
     Nb =as.integer(nb),
     datab = as.complex(B),DUP=FALSE

     )

    array(output$datac,dim=dim(C))
}



z_mm_leaf_computationR <- function(a,A,b,B) { 

    na   = length(A[1,]);
    ma   = length(A[,1]) ;
    nb   = length(B[1,]);
    mb   = length(B[,1]) ;

    nc   = length(B[1,]);
    mc   = length(A[,1]) ;
    C = array(0.0, dim=c(mc,nc))
    c = 1.0
    n = 0
    output <- .C("z_mm_leaf_computationB",
                 betac = as.complex(c),
                 transc = as.integer(n),
                 mc =as.integer(mc),
                 nc =as.integer(nc),
                 Mc =as.integer(mc),
                 Nc =as.integer(nc),
                 datac = as.complex(C),		
                 betaa = as.complex(a),
                 transa = as.integer(n),
                 ma =as.integer(ma),
                 na =as.integer(na),
                 Ma =as.integer(ma),
                 Na =as.integer(na),
                 dataa = as.complex(A),		
                 betab = as.complex(b),
                 transb = as.integer(n),
                 mb =as.integer(mb),
                 nb =as.integer(nb),
                 Mb =as.integer(mb),
                 Nb =as.integer(nb),
                 datab = as.complex(B),DUP=FALSE
                 )

    array(output$datac,dim=dim(C))
}
