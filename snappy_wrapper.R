# R wrapper for snappy binding

dyn.load("snappy.so")
snappy_compress <- function(s) {
	.Call("rsnappy_compress", as.character(s))
}

snappy_uncompress <- function(s) {
	.Call("rsnappy_uncompress", as.character(s))
}

snappy_validate_compressed_buffer <- function(s) {
	.Call("rsnappy_validate_compressed_buffer", as.character(s))
}

