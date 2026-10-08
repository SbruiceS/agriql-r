/**
 * AgriQL C ABI v1 — opaque handles, language kernel.
 * Author: Sbruice Singh / Agricultural Service of Product Farm (ASPF).
 *
 * Link: -lagriql_ffi  (cdylib / staticlib from crates/agriql-ffi)
 * The C++ scientific kernel also ships include/agriql/embed.h with the same
 * function names for the storage engine. Do not mix ABIs in one process.
 *
 * This header is the compatibility boundary. Rust structs are not exported.
 *
 * Preferred names (master prompt):
 *   agriql_engine_t, agriql_execute, agriql_result_t,
 *   agriql_last_error, agriql_free_result, agriql_close
 * Older aliases remain: agriql_db, agriql_exec, agriql_exec_text, agriql_errmsg.
 */
#ifndef AGRIQL_H
#define AGRIQL_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(_WIN32) && defined(AGRIQL_DLL)
#  ifdef AGRIQL_BUILD_DLL
#    define AGRIQL_API __declspec(dllexport)
#  else
#    define AGRIQL_API __declspec(dllimport)
#  endif
#else
#  define AGRIQL_API
#endif

typedef struct agriql_db agriql_db;
typedef agriql_db agriql_engine_t;
typedef struct agriql_result agriql_result;
typedef agriql_result agriql_result_t;
typedef struct agriql_error agriql_error;
typedef agriql_error agriql_error_t;

enum {
  AGRIQL_OK = 0,
  AGRIQL_ERROR = 1,
  AGRIQL_BUSY = 2,
  AGRIQL_NOMEM = 3,
  AGRIQL_MISUSE = 4
};

AGRIQL_API int agriql_open(const char* path, agriql_engine_t** out);
AGRIQL_API int agriql_close(agriql_engine_t* db);
AGRIQL_API const char* agriql_thread_error(void);

AGRIQL_API agriql_result_t* agriql_execute(agriql_engine_t* db, const char* sql);
AGRIQL_API const char* agriql_result_text(const agriql_result_t* r);
AGRIQL_API int agriql_result_status(const agriql_result_t* r);
AGRIQL_API void agriql_free_result(agriql_result_t* r);

AGRIQL_API agriql_error_t* agriql_last_error(agriql_engine_t* db);
AGRIQL_API const char* agriql_error_message(const agriql_error_t* e);
AGRIQL_API const char* agriql_last_text(agriql_engine_t* db);

AGRIQL_API int agriql_exec(agriql_db* db, const char* sql,
                           void* unused_cb, void* unused_ctx, char** errmsg);
AGRIQL_API int agriql_exec_text(agriql_db* db, const char* sql, char** out);
AGRIQL_API void agriql_free(char* p);
AGRIQL_API const char* agriql_version(void);
AGRIQL_API const char* agriql_grammar(void);
AGRIQL_API int agriql_c_abi(void);
AGRIQL_API const char* agriql_errmsg(agriql_db* db);

#ifdef __cplusplus
}
#endif

#endif /* AGRIQL_H */
