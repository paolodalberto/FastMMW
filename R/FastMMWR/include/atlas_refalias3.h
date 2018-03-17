#ifndef ATLAS_REFALIAS3_H
#define ATLAS_REFALIAS3_H
/*
 * Real BLAS
 */
   #ifdef ATL_ANTOINE_THREADS
      #define ATL_ssyr2k  ATL_srefsyr2k
   #else
      #define ATL_ssyr2k  ATL_s@(rep2c)syr2k
   #endif
   #ifdef ATL_ANTOINE_THREADS
      #define ATL_ssyrk   ATL_srefsyrk
   #else
      #define ATL_ssyrk   ATL_s@(rep2c)syrk
   #endif
   #ifdef ATL_ANTOINE_THREADS
      #define ATL_ssymm   ATL_srefsymm
   #else
      #define ATL_ssymm   ATL_s@(rep2c)symm
   #endif
   #ifdef ATL_ANTOINE_THREADS
      #define ATL_strmm   ATL_sreftrmm
   #else
      #define ATL_strmm   ATL_s@(rep2c)trmm
   #endif
   #ifdef ATL_ANTOINE_THREADS
      #define ATL_strsm   ATL_sreftrsm
   #else
      #define ATL_strsm   ATL_s@(rep2c)trsm
   #endif
   #ifdef ATL_ANTOINE_THREADS
      #define ATL_sgemm   ATL_srefgemm
   #else
      #define ATL_sgemm   ATL_s@(rep2c)gemm
   #endif

   #ifdef ATL_ANTOINE_THREADS
      #define ATL_dsyr2k  ATL_drefsyr2k
   #else
      #define ATL_dsyr2k  ATL_d@(rep2c)syr2k
   #endif
   #ifdef ATL_ANTOINE_THREADS
      #define ATL_dsyrk   ATL_drefsyrk
   #else
      #define ATL_dsyrk   ATL_d@(rep2c)syrk
   #endif
   #ifdef ATL_ANTOINE_THREADS
      #define ATL_dsymm   ATL_drefsymm
   #else
      #define ATL_dsymm   ATL_d@(rep2c)symm
   #endif
   #ifdef ATL_ANTOINE_THREADS
      #define ATL_dtrmm   ATL_dreftrmm
   #else
      #define ATL_dtrmm   ATL_d@(rep2c)trmm
   #endif
   #ifdef ATL_ANTOINE_THREADS
      #define ATL_dtrsm   ATL_dreftrsm
   #else
      #define ATL_dtrsm   ATL_d@(rep2c)trsm
   #endif
   #ifdef ATL_ANTOINE_THREADS
      #define ATL_dgemm   ATL_drefgemm
   #else
      #define ATL_dgemm   ATL_d@(rep2c)gemm
   #endif

/*
 * Complex BLAS
 */
   #ifdef ATL_ANTOINE_THREADS
      #define ATL_ctrmm     ATL_creftrmm
   #else
      #define ATL_ctrmm     ATL_c@(rep2c)trmm
   #endif
   #ifdef ATL_ANTOINE_THREADS
      #define ATL_cher2k    ATL_crefher2k
   #else
      #define ATL_cher2k    ATL_c@(rep2c)her2k
   #endif
   #ifdef ATL_ANTOINE_THREADS
      #define ATL_csyr2k    ATL_crefsyr2k
   #else
      #define ATL_csyr2k    ATL_c@(rep2c)syr2k
   #endif
   #ifdef ATL_ANTOINE_THREADS
      #define ATL_cherk     ATL_crefherk
   #else
      #define ATL_cherk     ATL_c@(rep2c)herk
   #endif
   #ifdef ATL_ANTOINE_THREADS
      #define ATL_csyrk     ATL_crefsyrk
   #else
      #define ATL_csyrk     ATL_c@(rep2c)syrk
   #endif
   #ifdef ATL_ANTOINE_THREADS
      #define ATL_chemm     ATL_crefhemm
   #else
      #define ATL_chemm     ATL_c@(rep2c)hemm
   #endif
   #ifdef ATL_ANTOINE_THREADS
      #define ATL_csymm     ATL_crefsymm
   #else
      #define ATL_csymm     ATL_c@(rep2c)symm
   #endif
   #ifdef ATL_ANTOINE_THREADS
      #define ATL_cgemm     ATL_crefgemm
   #else
      #define ATL_cgemm     ATL_c@(rep2c)gemm
   #endif
   #ifdef ATL_ANTOINE_THREADS
      #define ATL_ctrsm     ATL_creftrsm
   #else
      #define ATL_ctrsm     ATL_c@(rep2c)trsm
   #endif

   #ifdef ATL_ANTOINE_THREADS
      #define ATL_ztrmm     ATL_zreftrmm
   #else
      #define ATL_ztrmm     ATL_z@(rep2c)trmm
   #endif
   #ifdef ATL_ANTOINE_THREADS
      #define ATL_zher2k    ATL_zrefher2k
   #else
      #define ATL_zher2k    ATL_z@(rep2c)her2k
   #endif
   #ifdef ATL_ANTOINE_THREADS
      #define ATL_zsyr2k    ATL_zrefsyr2k
   #else
      #define ATL_zsyr2k    ATL_z@(rep2c)syr2k
   #endif
   #ifdef ATL_ANTOINE_THREADS
      #define ATL_zherk     ATL_zrefherk
   #else
      #define ATL_zherk     ATL_z@(rep2c)herk
   #endif
   #ifdef ATL_ANTOINE_THREADS
      #define ATL_zsyrk     ATL_zrefsyrk
   #else
      #define ATL_zsyrk     ATL_z@(rep2c)syrk
   #endif
   #ifdef ATL_ANTOINE_THREADS
      #define ATL_zhemm     ATL_zrefhemm
   #else
      #define ATL_zhemm     ATL_z@(rep2c)hemm
   #endif
   #ifdef ATL_ANTOINE_THREADS
      #define ATL_zsymm     ATL_zrefsymm
   #else
      #define ATL_zsymm     ATL_z@(rep2c)symm
   #endif
   #ifdef ATL_ANTOINE_THREADS
      #define ATL_zgemm     ATL_zrefgemm
   #else
      #define ATL_zgemm     ATL_z@(rep2c)gemm
   #endif
   #ifdef ATL_ANTOINE_THREADS
      #define ATL_ztrsm     ATL_zreftrsm
   #else
      #define ATL_ztrsm     ATL_z@(rep2c)trsm
   #endif

#endif
