# R wrapper for snappy binding

dyn.load("snappy.so")
snappy_compress <- function(str) {
	result <- .Call("rsnappy_compress", as.character(str))
	return result
}

snappy_uncompress <- function(str) {
	result <- .Call("rsnappy_uncompress", as.character(str))
	return result
}


