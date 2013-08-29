/*
 * ========================================================================
 *
 *       Filename:  r-snappy.c
 *
 *    Description:  Google snappy R binding.
 *
 *        Created:  08/29/2013 16:30:59 PM
 *
 *         Author:  luliang (lulyon), lulyon@126.com
 *        Company:  ICT ( Institute Of Computing Technology, CAS )
 *
 * ========================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#include <R.h>
#include <Rinternals.h>

#include "snappy/snappy-c.h"

SEXP rsnappy_compress(SEXP v)
{
	SEXP ans = R_NilValue;
	size_t src_len = Rf_length(v);
	const char* src = CHARACTER(v);
	size_t dst_max_size = snappy_max_compressed_length(src_len);
	char* dstmem = (char*)R_alloc(dst_max_size, sizeof(char));
	if (dstmem != NULL) {
		if (snappy_compress(src, src_len, dstmem,
					&dst_max_size) == SNAPPY_OK) {
			PROTECT(ans = Rf_allocVector(STRSXP, dst_max_size));
			memcpy(CHARACTER(ans), dstmem, sizeof(char) * dst_max_size);
			UNPROTECT(1);
			return ans;
		}
		else {
			printf("Error: snappy_compress fail.\n");
			return ans;
		}
	}

	printf("Error: R_alloc fail.\n");
	return ans;
}

SEXP rsnappy_uncompress(SEXP v)
{
	SEXP ans = R_NilValue;
	size_t src_len = Rf_length(v);
	size_t dst_max_size = 0;
	const char* src = CHARACTER(v);
	if (snappy_uncompressed_length(src, src_len, &dst_max_size)
			!= SNAPPY_OK) {
		printf("Error: snappy_uncompressed_length fail.\n");
		return ans;
	}
	char* dstmem = (char*)R_alloc(dst_max_size, sizeof(char));
	if (dstmem != NULL) {
		if (snappy_uncompress(src, src_len, dstmem,
					&dst_max_size) == SNAPPY_OK) {
			PROTECT(ans = Rf_allocVector(STRSXP, dst_max_size));
			memcpy(CHARACTER(ans), dstmem, sizeof(char) * dst_max_size);
			UNPROTECT(1);
			return ans;
		}
		free(dstmem);
	}

	printf("Error: R_alloc fail.\n");
	return ans;
}



