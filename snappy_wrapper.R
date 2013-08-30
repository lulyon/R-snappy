# R wrapper for snappy binding

dyn.load("snappy.so")
snappy_compress <- function(s) {
	vec = .Call("rsnappy_compress", as.character(s))
	vec[1]
}

snappy_uncompress <- function(s) {
	vec = .Call("rsnappy_uncompress", as.character(s))
	vec[1]
}


