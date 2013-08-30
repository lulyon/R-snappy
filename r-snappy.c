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
	size_t src_len = Rf_length(v);
	const char* src = CHAR(STRING_ELT(v, 0));
	size_t dst_max_size = snappy_max_compressed_length(src_len);
	char* dst = R_alloc(dst_max_size, sizeof(char));
	if (dst != NULL) {
		if (snappy_compress(src, src_len, dst,
					&dst_max_size) == SNAPPY_OK) {
			PROTECT(ans = NEW_CHARACTER(dst_max_size));
			memcpy(AS_CHARACTER(ans), dst, sizeof(char) * dst_max_size);
			UNPROTECT(1);
			return ans;
		}
		else {
			printf("Error: snappy_compress fails.\n");
			return ans;
		}
	}

	printf("Error: R_alloc fails.\n");
	return ans;
}

SEXP rsnappy_uncompress(SEXP v)
{
	SEXP ans = R_NilValue;
	size_t src_len = Rf_length(v);
	size_t dst_max_size = 0;
	const char* src = CHAR(STRING_ELT(v, 0));
	if (snappy_uncompressed_length(src, src_len, &dst_max_size)
			!= SNAPPY_OK) {
		printf("Error: snappy_uncompressed_length fails.\n");
		return ans;
	}
	char* dst = (char*)R_alloc(dst_max_size, sizeof(char));
	if (dst != NULL) {
		if (snappy_uncompress(src, src_len, dst,
					&dst_max_size) == SNAPPY_OK) {
			PROTECT(ans = NEW_CHARACTER(dst_max_size));
			memcpy(AS_CHARACTER(ans), dst, sizeof(char) * dst_max_size);
			UNPROTECT(1);
			return ans;
		}
		else {
			printf("Error: snappy_uncompress fails.\n");
			return ans;
		}
	}

	printf("Error: R_alloc fails.\n");
	return ans;
}



