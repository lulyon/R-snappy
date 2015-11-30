R-snappy
========

A R binding of google's [snappy](https://code.google.com/p/snappy/ "snappy") compressor.

How to Build
============
First of all, configure your system using:

        R-snappy$ ./sysconfig

Then, build R-snappy with make:

        R-snappy$ make

That'all, enjoy snappy in R.

How to Use
==========
Here is a sample usage in R shell:

        R version 2.14.1 (2011-12-22) Copyright (C) 2011 The R Foundation for Statistical Computing
        > source('snappy_wrapper.R')
        > compressed = snappy_compress("hello world!")
		> snappy_validate_compressed_buffer(compress)
		[1] TRUE
        > uncompressed = snappy_uncompress(compressed)
        > cat(uncompressed, "\n")
		hello world!
		>

Report Bugs
===========
Please report bugs to [lulyon AT 126 DOT com] or [lualu AT tencent DOT com] .

