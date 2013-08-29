# R wrapper for snappy binding

dyn.load("snappy.so")
snappy_compress <- function(s) {
	result <- .Call("rsnappy_compress", as.character(s))
	return result
}

snappy_uncompress <- function(s) {
	result <- .Call("rsnappy_uncompress", as.character(s))
	return result
}


