#!/usr/bin/env python 


from distutils.core import setup, Extension

python = "/usr/include/python2.7/"
numpy = "/usr/lib/python2.7/dist-packages/numpy/core/include/numpy/"

setup (name = "FastMMWP",
    version = "0.4",
    ext_modules = [
        Extension (
             "FastMMWP",
            [ "FastMMWP.c" ],
            library_dirs = ["../lib","../../GotoBLAS2/", "../../ATLAS/install2/lib"],
            libraries = ['dcfastmm','dfastmm','scfastmm','sfastmm',
                         'goto',
                         'pthread',
                         #'atlas','ptcblas','cblas'
                         ],
            include_dirs = [ "./","./include/",python,
                             numpy,
                           ],
            define_macros=[ ('OMP_NUM_THREADS','4'), ('APPLICATION','1'), ('GOTO_BLAS',1)],
            #define_macros=[ ('OMP_NUM_THREADS','4'), ('APPLICATION','1'), ('ATLAS',1)],
            extra_compile_args = ['-pthread', '-fopenmp', '-O2',   '-msse3', '-fPIC', '-march=opteron', '-mtune=opteron']
       )
    ]
)

