#ifndef DATABASE_API
#define DATABASE_API

//add  head
#include "sqlite3.h"
#include "common.h"

/* MAKE_DB_QUERY is a sqlite3 query idiom that hides the clutter */
/* error_message_format: is the format to print errror message returned from salite3_exec so it must
   contain one and only one %s */
/* return_code_on_error: is the value to return in an event of error.  Normally provide -1 for
   this. If continued execution is desired give 0 instead. */
/* callback_func: is the callback function or NULL when not used */
/* callback_arg: is the pointer to the argument to the callback_func */
/* query_string_format: is the format to formulate a query string.  It is passed to sqlite3_mprintf
   so all printf format as well as sqlite specific ones are allowd.  All the following parameters
   after query_string_format are passed on to sqlite3_mprintf. */
#define MAKE_DB_QUERY(db, error_message_format, return_code_on_error, callback_func, callback_arg, query_string_format, ...) \
  {                                                                     \
    char *query_statement = NULL;                                       \
    char *error_message = NULL;                                         \
    query_statement = sqlite3_mprintf(query_string_format, ##__VA_ARGS__); \
    if(query_statement == NULL) return -1;                              \
    if(sqlite3_exec(db, query_statement, callback_func, callback_arg, &error_message)) { \
      if((return_code_on_error) != 0) {                                 \
        printf(error_message_format, error_message);               \
        sqlite3_free(error_message);                                    \
        sqlite3_free(query_statement);                                  \
        return (return_code_on_error);                                  \
      }                                                                 \
    }                                                                   \
    sqlite3_free(query_statement);                                      \
    sqlite3_free(error_message); /* just in case, passing NULL is no harm */ \
  }

/*
** CAPI3REF: Result Codes
** KEYWORDS: SQLITE_OK {error code} {error codes}
** KEYWORDS: {result code} {result codes}
**
** Many SQLite functions return an integer result code from the set shown
** here in order to indicates success or failure.
**
** New error codes may be added in future versions of SQLite.
**
** See also: [SQLITE_IOERR_READ | extended result codes]
*/
#define SQLITE_OK           0   /* Successful result */
/* beginning-of-error-codes */
#define SQLITE_ERROR        1   /* SQL error or missing database */
#define SQLITE_INTERNAL     2   /* Internal logic error in SQLite */
#define SQLITE_PERM         3   /* Access permission denied */
#define SQLITE_ABORT        4   /* Callback routine requested an abort */
#define SQLITE_BUSY         5   /* The database file is locked */
#define SQLITE_LOCKED       6   /* A table in the database is locked */
#define SQLITE_NOMEM        7   /* A malloc() failed */
#define SQLITE_READONLY     8   /* Attempt to write a readonly database */
#define SQLITE_INTERRUPT    9   /* Operation terminated by sqlite3_interrupt()*/
#define SQLITE_IOERR       10   /* Some kind of disk I/O error occurred */
#define SQLITE_CORRUPT     11   /* The database disk image is malformed */
#define SQLITE_NOTFOUND    12   /* NOT USED. Table or record not found */
#define SQLITE_FULL        13   /* Insertion failed because database is full */
#define SQLITE_CANTOPEN    14   /* Unable to open the database file */
#define SQLITE_PROTOCOL    15   /* NOT USED. Database lock protocol error */
#define SQLITE_EMPTY       16   /* Database is empty */
#define SQLITE_SCHEMA      17   /* The database schema changed */
#define SQLITE_TOOBIG      18   /* String or BLOB exceeds size limit */
#define SQLITE_CONSTRAINT  19   /* Abort due to constraint violation */
#define SQLITE_MISMATCH    20   /* Data type mismatch */
#define SQLITE_MISUSE      21   /* Library used incorrectly */
#define SQLITE_NOLFS       22   /* Uses OS features not supported on host */
#define SQLITE_AUTH        23   /* Authorization denied */
#define SQLITE_FORMAT      24   /* Auxiliary database format error */
#define SQLITE_RANGE       25   /* 2nd parameter to sqlite3_bind out of range */
#define SQLITE_NOTADB      26   /* File opened that is not a database file */
#define SQLITE_ROW         100  /* sqlite3_step() has another row ready */
#define SQLITE_DONE        101  /* sqlite3_step() has finished executing */

#define DB_NAME      "hand.db"
#define FEATURE_NAME_LEN 10

typedef struct {
  int found;
  char *str;
  int len;
} sqlite3_dat_get_cb_arg_t;

static sqlite3 *hand_db = NULL;

class HandGestureDBApi
{
public:
    explicit HandGestureDBApi(void);
    ~HandGestureDBApi();

    /*  sqlite3 init */
    int database_init(void);

    int database_insert_feature(const char *kname, SGestureFeature feature);

    /*  sqlite3 inquire prepare*/
    int  database_inquire_sql(const char* keyname);

    /*  sqlite3 inquire current row step*/
    SQLITE_API int database_inquire_step();

    /*  sqlite3 inquire current row info*/
    int database_inquire_info(SGestureFeature &feature);

    /*  sqlite3 inquire shut down*/
    int database_inquire_shutdown();

    /* sqlite3 shutdown */
    int database_shutdown(void);
private:
    sqlite3_stmt *m_pFaceStmt;
};

#endif // DATABASE_API

