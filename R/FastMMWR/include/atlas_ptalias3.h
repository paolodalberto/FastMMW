#ifndef ATLAS_PTALIAS3_H
#define ATLAS_PTALIAS3_H
/*
 * Real BLAS
 */
   #ifdef ATL_ANTOINE_THREADS
      #define ATL_ssyr2k  ATL_sptsyr2k
   #else
      #define ATL_ssyr2k  ATL_stsyr2k
   #endif
   #ifdef ATL_ANTOINE_THREADS
      #define ATL_ssyrk   ATL_sptsyrk
   #else
      #define ATL_ssyrk   ATL_stsyrk
   #endif
   #ifdef ATL_ANTOINE_THREADS
      #define ATL_ssymm   ATL_sptsymm
   #else
      #define ATL_ssymm   ATL_stsymm
   #endif
   #ifdef ATL_ANTOINE_THREADS
      #define ATL_strmm   ATL_spttrmm
   #else
      #define ATL_strmm   ATL_sttrmm
   #endif
   #ifdef ATL_ANTOINE_THREADS
      #define ATL_strsm   ATL_spttrsm
   #else
      #define ATL_strsm   ATL_sttrsm
   #endif
   #ifdef ATL_ANTOINE_THREADS
      #define ATL_sgemm   ATL_sptgemm
   #else
      #define ATL_sgemm   ATL_stgemm
   #endif

   #ifdef ATL_ANTOINE_THREADS
      #define ATL_dsyr2k  ATL_dptsyr2k
   #else
      #define ATL_dsyr2k  ATL_dtsyr2k
   #endif
   #ifdef ATL_ANTOINE_THREADS
      #define ATL_dsyrk   ATL_dptsyrk
   #else
      #define ATL_dsyrk   ATL_dtsyrk
   #endif
   #ifdef ATL_ANTOINE_THREADS
      #define ATL_dsymm   ATL_dptsymm
   #else
      #define ATL_dsymm   ATL_dtsymm
   #endif
   #ifdef ATL_ANTOINE_THREADS
      #define ATL_dtrmm   ATL_dpttrmm
   #else
      #define ATL_dtrmm   ATL_dttrmm
   #endif
   #ifdef ATL_ANTOINE_THREADS
      #define ATL_dtrsm   ATL_dpttrsm
   #else
      #define ATL_dtrsm   ATL_dttrsm
   #endif
   #ifdef ATL_ANTOINE_THREADS
      #define ATL_dgemm   ATL_dptgemm
   #else
      #define ATL_dgemm   ATL_dtgemm
   #endif

/*
 * Complex BLAS
 */
   #ifdef ATL_ANTOINE_THREADS
      #define ATL_ctrmm     ATL_cpttrmm
   #else
      #define ATL_ctrmm     ATL_cttrmm
   #endif
   #ifdef ATL_ANTOINE_THREADS
      #define ATL_cher2k    ATL_cpther2k
   #else
      #define ATL_cher2k    ATL_cther2k
   #endif
   #ifdef ATL_ANTOINE_THREADS
      #define ATL_csyr2k    ATL_cptsyr2k
   #else
      #define ATL_csyr2k    ATL_ctsyr2k
   #endif
   #ifdef ATL_ANTOINE_THREADS
      #define ATL_cherk     ATL_cptherk
   #else
      #define ATL_cherk     ATL_ctherk
   #endif
   #ifdef ATL_ANTOINE_THREADS
      #define ATL_csyrk     ATL_cptsyrk
   #else
      #define ATL_csyrk     ATL_ctsyrk
   #endif
   #ifdef ATL_ANTOINE_THREADS
      #define ATL_chemm     ATL_cpthemm
   #else
      #define ATL_chemm     ATL_cthemm
   #endif
   #ifdef ATL_ANTOINE_THREADS
      #define ATL_csymm     ATL_cptsymm
   #else
      #define ATL_csymm     ATL_ctsymm
   #endif
   #ifdef ATL_ANTOINE_THREADS
      #define ATL_cgemm     ATL_cptgemm
   #else
      #define ATL_cgemm     ATL_ctgemm
   #endif
   #ifdef ATL_ANTOINE_THREADS
      #define ATL_ctrsm     ATL_cpttrsm
   #else
      #define ATL_ctrsm     ATL_cttrsm
   #endif

   #ifdef ATL_ANTOINE_THREADS
      #define ATL_ztrmm     ATL_zpttrmm
   #else
      #define ATL_ztrmm     ATL_zttrmm
   #endif
   #ifdef ATL_ANTOINE_THREADS
      #define ATL_zher2k    ATL_zpther2k
   #else
      #define ATL_zher2k    ATL_zther2k
   #endif
   #ifdef ATL_ANTOINE_THREADS
      #define ATL_zsyr2k    ATL_zptsyr2k
   #else
      #define ATL_zsyr2k    ATL_ztsyr2k
   #endif
   #ifdef ATL_ANTOINE_THREADS
      #define ATL_zherk     ATL_zptherk
   #else
      #define ATL_zherk     ATL_ztherk
   #endif
   #ifdef ATL_ANTOINE_THREADS
      #define ATL_zsyrk     ATL_zptsyrk
   #else
      #define ATL_zsyrk     ATL_ztsyrk
   #endif
   #ifdef ATL_ANTOINE_THREADS
      #define ATL_zhemm     ATL_zpthemm
   #else
      #define ATL_zhemm     ATL_zthemm
   #endif
   #ifdef ATL_ANTOINE_THREADS
      #define ATL_zsymm     ATL_zptsymm
   #else
      #define ATL_zsymm     ATL_ztsymm
   #endif
   #ifdef ATL_ANTOINE_THREADS
      #define ATL_zgemm     ATL_zptgemm
   #else
      #define ATL_zgemm     ATL_ztgemm
   #endif
   #ifdef ATL_ANTOINE_THREADS
      #define ATL_ztrsm     ATL_zpttrsm
   #else
      #define ATL_ztrsm     ATL_zttrsm
   #endif

#endif
