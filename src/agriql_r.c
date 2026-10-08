#include <R.h>
#include <Rinternals.h>
#include <string.h>
#include "agriql.h"

SEXP agriql_r_query(SEXP path, SEXP sql) {
    agriql_engine_t *db = NULL;
    const char *file = CHAR(STRING_ELT(path, 0));
    const char *open_path = strcmp(file, ":memory:") == 0 ? NULL : file;
    if (agriql_open(open_path, &db) != AGRIQL_OK) {
        error("%s", agriql_thread_error());
    }
    agriql_result_t *result = agriql_execute(db, CHAR(STRING_ELT(sql, 0)));
    if (result == NULL || agriql_result_status(result) != AGRIQL_OK) {
        const char *message = result != NULL ? agriql_result_text(result) : agriql_thread_error();
        if (result != NULL) {
            agriql_free_result(result);
        }
        agriql_close(db);
        error("%s", message != NULL ? message : "AGRIQL-2701");
    }
    SEXP out = PROTECT(mkString(agriql_result_text(result)));
    agriql_free_result(result);
    agriql_close(db);
    UNPROTECT(1);
    return out;
}
