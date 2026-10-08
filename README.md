# agriql

R client for the AgriQL engine. This package is not a database. `aqdb_query` calls `agriql_execute` in `libagriql_ffi`.

The only published package is `agriql`. Separate packages for Arrow, geospatial, fusion, and models are not published.

## Install

`libagriql_ffi` must already be on the library path. Build it from [AgriQL](https://github.com/SbruiceS/AgriQL):

```bash
git clone https://github.com/SbruiceS/AgriQL.git
cd AgriQL
cargo build -p agriql-ffi --release
sudo cp target/release/libagriql_ffi.so /usr/local/lib
sudo ldconfig
```

Then, in R:

```r
install.packages("remotes")
remotes::install_github("SbruiceS/agriql-r")
```

If the library is not in a default directory:

```bash
AGRIQL_LIBDIR=/path/to/lib R CMD INSTALL .
```

## Use

```r
library(agriql)

db <- aqdb_connect("farm.aqdb")
text <- aqdb_query(db, "SHOW SCHEMAS;")
aqdb_frame(text)
```

`aqdb_connect(":memory:")` opens an in-memory engine. A path ending in `.aqdb` opens that file. The package does not parse the file itself.
