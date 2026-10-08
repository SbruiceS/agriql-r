aqdb_connect <- function(path = ":memory:") {
  structure(list(path = path), class = "agriql")
}

aqdb_query <- function(db, sql) {
  if (!inherits(db, "agriql")) {
    stop("db is not an agriql connection")
  }
  .Call(agriql_r_query, as.character(db$path), as.character(sql))
}

aqdb_frame <- function(text) {
  lines <- strsplit(text, "\n", fixed = TRUE)[[1]]
  lines <- lines[nzchar(lines)]
  if (length(lines) < 2 || !grepl("\t", lines[[1]], fixed = TRUE)) {
    return(data.frame(text = lines, stringsAsFactors = FALSE))
  }
  header <- strsplit(lines[[1]], "\t", fixed = TRUE)[[1]]
  rows <- strsplit(lines[-1], "\t", fixed = TRUE)
  frame <- as.data.frame(do.call(rbind, rows), stringsAsFactors = FALSE)
  names(frame) <- header
  frame
}
