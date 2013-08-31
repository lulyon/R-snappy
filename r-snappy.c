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
#include <Rdefines.h>

#include "snappy/snappy-c.h"

SEXP rsnappy_compress(SEXP v)
{
	SEXP ans = R_NilValue;
	PROTECT(v = AS_CHARACTER(v));
	const char* src = CHAR(STRING_ELT(v, 0));
	size_t src_len = strlen(src);
	size_t dst_max_size = snappy_max_compressed_length(src_len);
	char* dst = R_alloc(dst_max_size, sizeof(char));
	if (dst != NULL) {
		if (snappy_compress(src, src_len, dst,
					&dst_max_size) == SNAPPY_OK) {
			PROTECT(ans = NEW_CHARACTER(1));
			SET_STRING_ELT(ans, 0, mkCharLen(dst, dst_max_size));
			UNPROTECT(2);
			return ans;
		}
		else {
			printf("Error: snappy_compress fails.\n");
			UNPROTECT(1);
			return ans;
		}
	}

	printf("Error: R_alloc fails.\n");
	UNPROTECT(1);
	return ans;
}

SEXP rsnappy_uncompress(SEXP v)
{
	SEXP ans = R_NilValue;
	PROTECT(v = AS_CHARACTER(v));
	const char* src = CHAR(STRING_ELT(v, 0));
	size_t src_len = strlen(src);
	size_t dst_max_size = 0;
	if (snappy_uncompressed_length(src, src_len, &dst_max_size)
			!= SNAPPY_OK) {
		printf("Error: snappy_uncompressed_length fails.\n");
		return ans;
	}
	char* dst = R_alloc(dst_max_size, sizeof(char));
	if (dst != NULL) {
		if (snappy_uncompress(src, src_len, dst,
					&dst_max_size) == SNAPPY_OK) {
			PROTECT(ans = NEW_CHARACTER(1));
			SET_STRING_ELT(ans, 0, mkCharLen(dst, dst_max_size));
			UNPROTECT(2);
			return ans;
		}
		else {
			printf("Error: snappy_uncompress fails.\n");
			UNPROTECT(1);
			return ans;
		}
	}

	printf("Error: R_alloc fails.\n");
	UNPROTECT(1);
	return ans;
}



