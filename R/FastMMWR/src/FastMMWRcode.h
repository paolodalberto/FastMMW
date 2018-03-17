void s_dcmulB(float *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, float *datac, 
 float *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, float *dataa, 
 float *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, float *datab) {
 	S_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	S_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	S_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(s_dcmul(C,A,B));
 }void s_mulB(float *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, float *datac, 
 float *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, float *dataa, 
 float *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, float *datab) {
 	S_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	S_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	S_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(s_mul(C,A,B));
 }void s_mulptB(float *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, float *datac, 
 float *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, float *dataa, 
 float *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, float *datab) {
 	S_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	S_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	S_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(s_mulpt(C,A,B));
 }void s_maddB(float *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, float *datac, 
 float *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, float *dataa, 
 float *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, float *datab) {
 	S_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	S_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	S_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(s_madd(C,A,B));
 }void s_saddmulB(float *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, float *datac, 
 float *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, float *dataa, 
 float *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, float *datab) {
 	S_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	S_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	S_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(s_saddmul(C,A,B));
 }void s_smulB(float *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, float *datac, 
 float *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, float *dataa, 
 float *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, float *datab) {
 	S_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	S_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	S_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(s_smul(C,A,B));
 }void s_wmulB(float *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, float *datac, 
 float *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, float *dataa, 
 float *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, float *datab) {
 	S_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	S_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	S_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(s_wmul(C,A,B));
 }void s_waddmulB(float *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, float *datac, 
 float *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, float *dataa, 
 float *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, float *datab) {
 	S_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	S_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	S_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(s_waddmul(C,A,B));
 }void s_wmB(float *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, float *datac, 
 float *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, float *dataa, 
 float *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, float *datab) {
 	S_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	S_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	S_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(s_wm(C,A,B));
 }void s_wmaddB(float *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, float *datac, 
 float *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, float *dataa, 
 float *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, float *datab) {
 	S_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	S_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	S_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(s_wmadd(C,A,B));
 }void s_adaptive_smulB(float *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, float *datac, 
 float *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, float *dataa, 
 float *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, float *datab, int *a) {
 	S_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	S_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	S_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(s_adaptive_smul(C,A,B,*a));
 }void s_omulB(float *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, float *datac, 
 float *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, float *dataa, 
 float *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, float *datab) {
 	S_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	S_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	S_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(s_omul(C,A,B));
 }void s_oaddmulB(float *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, float *datac, 
 float *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, float *dataa, 
 float *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, float *datab) {
 	S_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	S_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	S_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(s_oaddmul(C,A,B));
 }void s_owmulB(float *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, float *datac, 
 float *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, float *dataa, 
 float *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, float *datab) {
 	S_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	S_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	S_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(s_owmul(C,A,B));
 }void s_owaddmulB(float *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, float *datac, 
 float *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, float *dataa, 
 float *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, float *datab) {
 	S_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	S_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	S_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(s_owaddmul(C,A,B));
 }void s_bmB(float *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, float *datac, 
 float *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, float *dataa, 
 float *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, float *datab) {
 	S_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	S_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	S_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(s_bm(C,A,B));
 }void s_bmaddB(float *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, float *datac, 
 float *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, float *dataa, 
 float *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, float *datab) {
 	S_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	S_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	S_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(s_bmadd(C,A,B));
 }void s_ptaddmulB(float *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, float *datac, 
 float *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, float *dataa, 
 float *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, float *datab) {
 	S_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	S_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	S_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(s_ptaddmul(C,A,B));
 }void s_wmpipeB(float *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, float *datac, 
 float *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, float *dataa, 
 float *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, float *datab) {
 	S_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	S_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	S_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(s_wmpipe(C,A,B,0));
 }void s_wmaddpipeB(float *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, float *datac, 
 float *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, float *dataa, 
 float *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, float *datab) {
 	S_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	S_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	S_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(s_wmaddpipe(C,A,B,0));
 }void s_bmpipeB(float *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, float *datac, 
 float *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, float *dataa, 
 float *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, float *datab) {
 	S_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	S_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	S_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(s_bmpipe(C,A,B,0));
 }void s_bmaddpipeB(float *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, float *datac, 
 float *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, float *dataa, 
 float *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, float *datab) {
 	S_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	S_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	S_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(s_bmaddpipe(C,A,B,0));
 }void s_smpipeB(float *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, float *datac, 
 float *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, float *dataa, 
 float *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, float *datab) {
 	S_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	S_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	S_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(s_smpipe(C,A,B,0));
 }void s_smaddpipeB(float *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, float *datac, 
 float *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, float *dataa, 
 float *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, float *datab) {
 	S_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	S_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	S_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(s_smaddpipe(C,A,B,0));
 }void s_RmulB(float *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, float *datac, 
 float *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, float *dataa, 
 float *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, float *datab) {
 	S_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	S_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	S_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(s_Rmul(C,A,B));
 }void s_adaptive_wmB(float *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, float *datac, 
 float *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, float *dataa, 
 float *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, float *datab, int *a) {
 	S_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	S_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	S_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(s_adaptive_wm(C,A,B,*a));
 }void s_BMADD_PIPEB(float *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, float *datac, 
 float *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, float *dataa, 
 float *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, float *datab) {
 	S_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	S_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	S_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(s_BMADD_PIPE(C,A,B,0));
 }void s_BMADDB(float *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, float *datac, 
 float *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, float *dataa, 
 float *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, float *datab) {
 	S_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	S_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	S_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(s_BMADD(C,A,B));
 }void s_BMOWR_PIPEB(float *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, float *datac, 
 float *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, float *dataa, 
 float *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, float *datab) {
 	S_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	S_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	S_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(s_BMOWR_PIPE(C,A,B,0));
 }void s_BMOWRB(float *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, float *datac, 
 float *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, float *dataa, 
 float *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, float *datab) {
 	S_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	S_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	S_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(s_BMOWR(C,A,B));
 }void d_dcmulB(double *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, double *datac, 
 double *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, double *dataa, 
 double *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, double *datab) {
 	D_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	D_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	D_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(d_dcmul(C,A,B));
 }void d_mulB(double *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, double *datac, 
 double *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, double *dataa, 
 double *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, double *datab) {
 	D_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	D_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	D_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(d_mul(C,A,B));
 }void d_mulptB(double *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, double *datac, 
 double *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, double *dataa, 
 double *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, double *datab) {
 	D_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	D_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	D_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(d_mulpt(C,A,B));
 }void d_maddB(double *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, double *datac, 
 double *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, double *dataa, 
 double *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, double *datab) {
 	D_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	D_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	D_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(d_madd(C,A,B));
 }void d_saddmulB(double *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, double *datac, 
 double *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, double *dataa, 
 double *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, double *datab) {
 	D_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	D_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	D_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(d_saddmul(C,A,B));
 }void d_smulB(double *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, double *datac, 
 double *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, double *dataa, 
 double *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, double *datab) {
 	D_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	D_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	D_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(d_smul(C,A,B));
 }void d_wmulB(double *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, double *datac, 
 double *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, double *dataa, 
 double *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, double *datab) {
 	D_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	D_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	D_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(d_wmul(C,A,B));
 }void d_waddmulB(double *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, double *datac, 
 double *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, double *dataa, 
 double *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, double *datab) {
 	D_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	D_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	D_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(d_waddmul(C,A,B));
 }void d_wmB(double *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, double *datac, 
 double *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, double *dataa, 
 double *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, double *datab) {
 	D_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	D_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	D_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(d_wm(C,A,B));
 }void d_wmaddB(double *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, double *datac, 
 double *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, double *dataa, 
 double *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, double *datab) {
 	D_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	D_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	D_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(d_wmadd(C,A,B));
 }void d_adaptive_smulB(double *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, double *datac, 
 double *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, double *dataa, 
 double *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, double *datab, int *a) {
 	D_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	D_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	D_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(d_adaptive_smul(C,A,B,*a));
 }void d_omulB(double *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, double *datac, 
 double *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, double *dataa, 
 double *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, double *datab) {
 	D_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	D_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	D_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(d_omul(C,A,B));
 }void d_oaddmulB(double *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, double *datac, 
 double *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, double *dataa, 
 double *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, double *datab) {
 	D_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	D_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	D_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(d_oaddmul(C,A,B));
 }void d_owmulB(double *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, double *datac, 
 double *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, double *dataa, 
 double *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, double *datab) {
 	D_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	D_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	D_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(d_owmul(C,A,B));
 }void d_owaddmulB(double *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, double *datac, 
 double *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, double *dataa, 
 double *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, double *datab) {
 	D_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	D_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	D_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(d_owaddmul(C,A,B));
 }void d_bmB(double *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, double *datac, 
 double *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, double *dataa, 
 double *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, double *datab) {
 	D_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	D_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	D_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(d_bm(C,A,B));
 }void d_bmaddB(double *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, double *datac, 
 double *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, double *dataa, 
 double *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, double *datab) {
 	D_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	D_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	D_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(d_bmadd(C,A,B));
 }void d_ptaddmulB(double *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, double *datac, 
 double *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, double *dataa, 
 double *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, double *datab) {
 	D_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	D_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	D_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(d_ptaddmul(C,A,B));
 }void d_wmpipeB(double *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, double *datac, 
 double *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, double *dataa, 
 double *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, double *datab) {
 	D_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	D_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	D_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(d_wmpipe(C,A,B,0));
 }void d_wmaddpipeB(double *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, double *datac, 
 double *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, double *dataa, 
 double *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, double *datab) {
 	D_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	D_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	D_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(d_wmaddpipe(C,A,B,0));
 }void d_bmpipeB(double *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, double *datac, 
 double *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, double *dataa, 
 double *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, double *datab) {
 	D_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	D_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	D_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(d_bmpipe(C,A,B,0));
 }void d_bmaddpipeB(double *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, double *datac, 
 double *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, double *dataa, 
 double *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, double *datab) {
 	D_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	D_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	D_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(d_bmaddpipe(C,A,B,0));
 }void d_smpipeB(double *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, double *datac, 
 double *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, double *dataa, 
 double *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, double *datab) {
 	D_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	D_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	D_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(d_smpipe(C,A,B,0));
 }void d_smaddpipeB(double *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, double *datac, 
 double *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, double *dataa, 
 double *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, double *datab) {
 	D_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	D_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	D_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(d_smaddpipe(C,A,B,0));
 }void d_RmulB(double *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, double *datac, 
 double *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, double *dataa, 
 double *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, double *datab) {
 	D_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	D_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	D_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(d_Rmul(C,A,B));
 }void d_adaptive_wmB(double *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, double *datac, 
 double *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, double *dataa, 
 double *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, double *datab, int *a) {
 	D_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	D_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	D_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(d_adaptive_wm(C,A,B,*a));
 }void d_BMADD_PIPEB(double *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, double *datac, 
 double *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, double *dataa, 
 double *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, double *datab) {
 	D_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	D_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	D_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(d_BMADD_PIPE(C,A,B,0));
 }void d_BMADDB(double *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, double *datac, 
 double *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, double *dataa, 
 double *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, double *datab) {
 	D_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	D_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	D_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(d_BMADD(C,A,B));
 }void d_BMOWR_PIPEB(double *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, double *datac, 
 double *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, double *dataa, 
 double *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, double *datab) {
 	D_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	D_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	D_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(d_BMOWR_PIPE(C,A,B,0));
 }void d_BMOWRB(double *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, double *datac, 
 double *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, double *dataa, 
 double *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, double *datab) {
 	D_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	D_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	D_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(d_BMOWR(C,A,B));
 }void c_dcmulB(float complex *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, float complex *datac, 
 float complex *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, float complex *dataa, 
 float complex *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, float complex *datab) {
 	C_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	C_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	C_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(c_dcmul(C,A,B));
 }void c_mulB(float complex *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, float complex *datac, 
 float complex *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, float complex *dataa, 
 float complex *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, float complex *datab) {
 	C_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	C_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	C_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(c_mul(C,A,B));
 }void c_mulptB(float complex *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, float complex *datac, 
 float complex *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, float complex *dataa, 
 float complex *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, float complex *datab) {
 	C_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	C_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	C_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(c_mulpt(C,A,B));
 }void c_maddB(float complex *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, float complex *datac, 
 float complex *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, float complex *dataa, 
 float complex *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, float complex *datab) {
 	C_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	C_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	C_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(c_madd(C,A,B));
 }void c_saddmulB(float complex *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, float complex *datac, 
 float complex *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, float complex *dataa, 
 float complex *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, float complex *datab) {
 	C_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	C_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	C_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(c_saddmul(C,A,B));
 }void c_smulB(float complex *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, float complex *datac, 
 float complex *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, float complex *dataa, 
 float complex *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, float complex *datab) {
 	C_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	C_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	C_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(c_smul(C,A,B));
 }void c_wmulB(float complex *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, float complex *datac, 
 float complex *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, float complex *dataa, 
 float complex *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, float complex *datab) {
 	C_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	C_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	C_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(c_wmul(C,A,B));
 }void c_waddmulB(float complex *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, float complex *datac, 
 float complex *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, float complex *dataa, 
 float complex *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, float complex *datab) {
 	C_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	C_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	C_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(c_waddmul(C,A,B));
 }void c_wmB(float complex *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, float complex *datac, 
 float complex *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, float complex *dataa, 
 float complex *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, float complex *datab) {
 	C_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	C_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	C_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(c_wm(C,A,B));
 }void c_wmaddB(float complex *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, float complex *datac, 
 float complex *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, float complex *dataa, 
 float complex *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, float complex *datab) {
 	C_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	C_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	C_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(c_wmadd(C,A,B));
 }void c_adaptive_smulB(float complex *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, float complex *datac, 
 float complex *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, float complex *dataa, 
 float complex *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, float complex *datab, int *a) {
 	C_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	C_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	C_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(c_adaptive_smul(C,A,B,*a));
 }void c_omulB(float complex *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, float complex *datac, 
 float complex *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, float complex *dataa, 
 float complex *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, float complex *datab) {
 	C_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	C_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	C_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(c_omul(C,A,B));
 }void c_oaddmulB(float complex *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, float complex *datac, 
 float complex *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, float complex *dataa, 
 float complex *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, float complex *datab) {
 	C_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	C_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	C_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(c_oaddmul(C,A,B));
 }void c_owmulB(float complex *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, float complex *datac, 
 float complex *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, float complex *dataa, 
 float complex *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, float complex *datab) {
 	C_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	C_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	C_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(c_owmul(C,A,B));
 }void c_owaddmulB(float complex *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, float complex *datac, 
 float complex *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, float complex *dataa, 
 float complex *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, float complex *datab) {
 	C_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	C_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	C_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(c_owaddmul(C,A,B));
 }void c_bmB(float complex *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, float complex *datac, 
 float complex *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, float complex *dataa, 
 float complex *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, float complex *datab) {
 	C_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	C_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	C_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(c_bm(C,A,B));
 }void c_bmaddB(float complex *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, float complex *datac, 
 float complex *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, float complex *dataa, 
 float complex *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, float complex *datab) {
 	C_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	C_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	C_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(c_bmadd(C,A,B));
 }void c_ptaddmulB(float complex *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, float complex *datac, 
 float complex *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, float complex *dataa, 
 float complex *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, float complex *datab) {
 	C_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	C_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	C_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(c_ptaddmul(C,A,B));
 }void c_wmpipeB(float complex *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, float complex *datac, 
 float complex *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, float complex *dataa, 
 float complex *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, float complex *datab) {
 	C_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	C_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	C_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(c_wmpipe(C,A,B,0));
 }void c_wmaddpipeB(float complex *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, float complex *datac, 
 float complex *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, float complex *dataa, 
 float complex *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, float complex *datab) {
 	C_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	C_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	C_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(c_wmaddpipe(C,A,B,0));
 }void c_bmpipeB(float complex *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, float complex *datac, 
 float complex *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, float complex *dataa, 
 float complex *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, float complex *datab) {
 	C_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	C_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	C_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(c_bmpipe(C,A,B,0));
 }void c_bmaddpipeB(float complex *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, float complex *datac, 
 float complex *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, float complex *dataa, 
 float complex *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, float complex *datab) {
 	C_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	C_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	C_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(c_bmaddpipe(C,A,B,0));
 }void c_smpipeB(float complex *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, float complex *datac, 
 float complex *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, float complex *dataa, 
 float complex *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, float complex *datab) {
 	C_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	C_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	C_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(c_smpipe(C,A,B,0));
 }void c_smaddpipeB(float complex *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, float complex *datac, 
 float complex *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, float complex *dataa, 
 float complex *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, float complex *datab) {
 	C_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	C_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	C_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(c_smaddpipe(C,A,B,0));
 }void c_RmulB(float complex *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, float complex *datac, 
 float complex *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, float complex *dataa, 
 float complex *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, float complex *datab) {
 	C_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	C_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	C_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(c_Rmul(C,A,B));
 }void c_adaptive_wmB(float complex *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, float complex *datac, 
 float complex *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, float complex *dataa, 
 float complex *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, float complex *datab, int *a) {
 	C_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	C_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	C_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(c_adaptive_wm(C,A,B,*a));
 }void c_BMADD_PIPEB(float complex *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, float complex *datac, 
 float complex *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, float complex *dataa, 
 float complex *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, float complex *datab) {
 	C_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	C_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	C_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(c_BMADD_PIPE(C,A,B,0));
 }void c_BMADDB(float complex *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, float complex *datac, 
 float complex *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, float complex *dataa, 
 float complex *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, float complex *datab) {
 	C_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	C_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	C_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(c_BMADD(C,A,B));
 }void c_BMOWR_PIPEB(float complex *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, float complex *datac, 
 float complex *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, float complex *dataa, 
 float complex *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, float complex *datab) {
 	C_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	C_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	C_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(c_BMOWR_PIPE(C,A,B,0));
 }void c_BMOWRB(float complex *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, float complex *datac, 
 float complex *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, float complex *dataa, 
 float complex *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, float complex *datab) {
 	C_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	C_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	C_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(c_BMOWR(C,A,B));
 }void z_dcmulB(double complex *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, double complex *datac, 
 double complex *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, double complex *dataa, 
 double complex *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, double complex *datab) {
 	Z_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	Z_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	Z_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(z_dcmul(C,A,B));
 }void z_mulB(double complex *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, double complex *datac, 
 double complex *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, double complex *dataa, 
 double complex *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, double complex *datab) {
 	Z_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	Z_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	Z_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(z_mul(C,A,B));
 }void z_mulptB(double complex *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, double complex *datac, 
 double complex *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, double complex *dataa, 
 double complex *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, double complex *datab) {
 	Z_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	Z_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	Z_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(z_mulpt(C,A,B));
 }void z_maddB(double complex *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, double complex *datac, 
 double complex *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, double complex *dataa, 
 double complex *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, double complex *datab) {
 	Z_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	Z_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	Z_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(z_madd(C,A,B));
 }void z_saddmulB(double complex *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, double complex *datac, 
 double complex *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, double complex *dataa, 
 double complex *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, double complex *datab) {
 	Z_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	Z_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	Z_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(z_saddmul(C,A,B));
 }void z_smulB(double complex *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, double complex *datac, 
 double complex *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, double complex *dataa, 
 double complex *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, double complex *datab) {
 	Z_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	Z_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	Z_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(z_smul(C,A,B));
 }void z_wmulB(double complex *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, double complex *datac, 
 double complex *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, double complex *dataa, 
 double complex *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, double complex *datab) {
 	Z_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	Z_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	Z_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(z_wmul(C,A,B));
 }void z_waddmulB(double complex *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, double complex *datac, 
 double complex *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, double complex *dataa, 
 double complex *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, double complex *datab) {
 	Z_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	Z_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	Z_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(z_waddmul(C,A,B));
 }void z_wmB(double complex *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, double complex *datac, 
 double complex *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, double complex *dataa, 
 double complex *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, double complex *datab) {
 	Z_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	Z_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	Z_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(z_wm(C,A,B));
 }void z_wmaddB(double complex *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, double complex *datac, 
 double complex *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, double complex *dataa, 
 double complex *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, double complex *datab) {
 	Z_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	Z_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	Z_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(z_wmadd(C,A,B));
 }void z_adaptive_smulB(double complex *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, double complex *datac, 
 double complex *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, double complex *dataa, 
 double complex *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, double complex *datab, int *a) {
 	Z_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	Z_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	Z_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(z_adaptive_smul(C,A,B,*a));
 }void z_omulB(double complex *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, double complex *datac, 
 double complex *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, double complex *dataa, 
 double complex *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, double complex *datab) {
 	Z_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	Z_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	Z_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(z_omul(C,A,B));
 }void z_oaddmulB(double complex *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, double complex *datac, 
 double complex *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, double complex *dataa, 
 double complex *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, double complex *datab) {
 	Z_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	Z_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	Z_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(z_oaddmul(C,A,B));
 }void z_owmulB(double complex *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, double complex *datac, 
 double complex *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, double complex *dataa, 
 double complex *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, double complex *datab) {
 	Z_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	Z_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	Z_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(z_owmul(C,A,B));
 }void z_owaddmulB(double complex *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, double complex *datac, 
 double complex *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, double complex *dataa, 
 double complex *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, double complex *datab) {
 	Z_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	Z_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	Z_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(z_owaddmul(C,A,B));
 }void z_bmB(double complex *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, double complex *datac, 
 double complex *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, double complex *dataa, 
 double complex *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, double complex *datab) {
 	Z_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	Z_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	Z_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(z_bm(C,A,B));
 }void z_bmaddB(double complex *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, double complex *datac, 
 double complex *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, double complex *dataa, 
 double complex *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, double complex *datab) {
 	Z_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	Z_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	Z_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(z_bmadd(C,A,B));
 }void z_ptaddmulB(double complex *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, double complex *datac, 
 double complex *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, double complex *dataa, 
 double complex *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, double complex *datab) {
 	Z_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	Z_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	Z_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(z_ptaddmul(C,A,B));
 }void z_wmpipeB(double complex *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, double complex *datac, 
 double complex *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, double complex *dataa, 
 double complex *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, double complex *datab) {
 	Z_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	Z_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	Z_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(z_wmpipe(C,A,B,0));
 }void z_wmaddpipeB(double complex *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, double complex *datac, 
 double complex *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, double complex *dataa, 
 double complex *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, double complex *datab) {
 	Z_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	Z_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	Z_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(z_wmaddpipe(C,A,B,0));
 }void z_bmpipeB(double complex *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, double complex *datac, 
 double complex *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, double complex *dataa, 
 double complex *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, double complex *datab) {
 	Z_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	Z_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	Z_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(z_bmpipe(C,A,B,0));
 }void z_bmaddpipeB(double complex *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, double complex *datac, 
 double complex *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, double complex *dataa, 
 double complex *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, double complex *datab) {
 	Z_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	Z_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	Z_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(z_bmaddpipe(C,A,B,0));
 }void z_smpipeB(double complex *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, double complex *datac, 
 double complex *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, double complex *dataa, 
 double complex *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, double complex *datab) {
 	Z_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	Z_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	Z_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(z_smpipe(C,A,B,0));
 }void z_smaddpipeB(double complex *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, double complex *datac, 
 double complex *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, double complex *dataa, 
 double complex *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, double complex *datab) {
 	Z_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	Z_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	Z_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(z_smaddpipe(C,A,B,0));
 }void z_RmulB(double complex *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, double complex *datac, 
 double complex *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, double complex *dataa, 
 double complex *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, double complex *datab) {
 	Z_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	Z_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	Z_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(z_Rmul(C,A,B));
 }void z_adaptive_wmB(double complex *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, double complex *datac, 
 double complex *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, double complex *dataa, 
 double complex *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, double complex *datab, int *a) {
 	Z_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	Z_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	Z_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(z_adaptive_wm(C,A,B,*a));
 }void z_BMADD_PIPEB(double complex *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, double complex *datac, 
 double complex *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, double complex *dataa, 
 double complex *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, double complex *datab) {
 	Z_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	Z_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	Z_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(z_BMADD_PIPE(C,A,B,0));
 }void z_BMADDB(double complex *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, double complex *datac, 
 double complex *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, double complex *dataa, 
 double complex *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, double complex *datab) {
 	Z_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	Z_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	Z_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(z_BMADD(C,A,B));
 }void z_BMOWR_PIPEB(double complex *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, double complex *datac, 
 double complex *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, double complex *dataa, 
 double complex *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, double complex *datab) {
 	Z_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	Z_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	Z_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(z_BMOWR_PIPE(C,A,B,0));
 }void z_BMOWRB(double complex *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, double complex *datac, 
 double complex *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, double complex *dataa, 
 double complex *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, double complex *datab) {
 	Z_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	Z_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	Z_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(z_BMOWR(C,A,B));
 }void s_mm_leaf_computation_maddB(float *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, float *datac, 
 float *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, float *dataa, 
 float *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, float *datab) {
 	S_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	S_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	S_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(mm_leaf_computation_madd_s(C,A,B));
 }void s_mm_leaf_computationB(float *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, float *datac, 
 float *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, float *dataa, 
 float *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, float *datab) {
 	S_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	S_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	S_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(mm_leaf_computation_s(C,A,B));
 }void d_mm_leaf_computation_maddB(double *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, double *datac, 
 double *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, double *dataa, 
 double *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, double *datab) {
 	D_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	D_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	D_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(mm_leaf_computation_madd_d(C,A,B));
 }void d_mm_leaf_computationB(double *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, double *datac, 
 double *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, double *dataa, 
 double *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, double *datab) {
 	D_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	D_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	D_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(mm_leaf_computation_d(C,A,B));
 }void c_mm_leaf_computation_maddB(float complex *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, float complex *datac, 
 float complex *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, float complex *dataa, 
 float complex *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, float complex *datab) {
 	C_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	C_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	C_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(mm_leaf_computation_madd_c(C,A,B));
 }void c_mm_leaf_computationB(float complex *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, float complex *datac, 
 float complex *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, float complex *dataa, 
 float complex *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, float complex *datab) {
 	C_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	C_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	C_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(mm_leaf_computation_c(C,A,B));
 }void z_mm_leaf_computation_maddB(double complex *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, double complex *datac, 
 double complex *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, double complex *dataa, 
 double complex *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, double complex *datab) {
 	Z_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	Z_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	Z_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(mm_leaf_computation_madd_z(C,A,B));
 }void z_mm_leaf_computationB(double complex *betac, int *transc, int *mc, int *nc, int *Mc, int *Nc, double complex *datac, 
 double complex *betaa, int *transa, int *ma, int *na, int *Ma, int *Na, double complex *dataa, 
 double complex *betab, int *transb, int *mb, int *nb, int *Mb, int *Nb, double complex *datab) {
 	Z_Matrix C = {  datac, *mc, *nc, *Mc, *Nc, flags[*transc], *betac}; 
 	Z_Matrix A = {  dataa, *ma, *na, *Ma, *Na, flags[*transa], *betaa};  
 	Z_Matrix B = {  datab, *mb, *nb, *Mb, *Nb, flags[*transb], *betab};
 	TEXECUTE(mm_leaf_computation_z(C,A,B));
 }