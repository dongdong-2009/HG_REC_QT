#include "database_api.h"

HandGestureDBApi::HandGestureDBApi(void)
{
    m_pFaceStmt = mpNULL;
}

HandGestureDBApi::~HandGestureDBApi()
{

}

int HandGestureDBApi::database_init(void)
{
    PRT_INFO("\n");
    if(sqlite3_open(DB_NAME, &hand_db) != SQLITE_OK)
    {
        // check whether we need to have it in persistent memory or not
        PRT_INFO("Can't open database hand_db: %s\n", sqlite3_errmsg(hand_db));
        sqlite3_close(hand_db);
        return -1;
    }

    MAKE_DB_QUERY(hand_db,
                "Error in Creating the handfeature table(Err): %s\n", -1, NULL, NULL,
                "CREATE TABLE IF NOT EXISTS handfeature"
                "(keyName varchar, "
                "angleName blob,anglechaName blob,countName blob);");
    return 0;
}

int HandGestureDBApi::database_insert_feature(const char *kname, SGestureFeature feature)
{
    mpINT iRes = -1;
    if(!hand_db) {
      PRT_INFO("Database has not been initialized\n");
      return iRes;
    }
    if(!kname) {
      PRT_INFO("kname cannot be NULL\n");
      return iRes;
    }

    sqlite3_stmt *stmt = mpNULL;
    char *query_statement = mpNULL;
    do{
            //delete record data if exist.
            MAKE_DB_QUERY(hand_db,
                 "Deletion ERROR: %s\n", 0, NULL, NULL,
                 "DELETE FROM handfeature WHERE keyName = %Q", kname);

            query_statement = sqlite3_mprintf("insert into handfeature(keyName,angleName, anglechaName,countName) values(%Q,?,?,?);",kname);
            if (query_statement == mpNULL)
            {
                 PRT_INFO("query_statement cannot be NULL\n");
                 break;
            }
            if (sqlite3_prepare(hand_db, query_statement, strlen(query_statement), &stmt, NULL) != SQLITE_OK)
            {
                PRT_INFO("ERROR:query preparation failed - %s\n", sqlite3_errmsg(hand_db));
                break;
            }

            if (sqlite3_bind_blob(stmt, 1, (float*)feature.angle, sizeof(feature.angle), NULL) != SQLITE_OK)
            {
                PRT_INFO("ERROR:query bind blod failed - %s\n", sqlite3_errmsg(hand_db));
                break;
            }
            if (sqlite3_bind_blob(stmt, 2, (float*)feature.anglecha, sizeof(feature.anglecha), NULL) != SQLITE_OK)
            {
                PRT_INFO("ERROR:query bind blod failed - %s\n", sqlite3_errmsg(hand_db));
                break;
            }
            if (sqlite3_bind_blob(stmt, 3, (float*)feature.count, sizeof(feature.count), NULL) != SQLITE_OK)
            {
                PRT_INFO("ERROR:query bind blod failed - %s\n", sqlite3_errmsg(hand_db));
                break;
            }

            if(!iRes){
                sqlite3_step(stmt);//exec insert command
                PRT_INFO("insert sucess!\n");
            }
            iRes = 0;
    }while(mpFALSE);

    if(query_statement != mpNULL)
    {
        sqlite3_free(query_statement);
        query_statement = mpNULL;
    }
    if(stmt != mpNULL)
    {
        sqlite3_finalize(stmt);
        stmt = mpNULL;
    }
    return iRes;
}

int HandGestureDBApi:: database_inquire_sql(const char* keyname)
{
    if(!hand_db) {
        PRT_INFO("hand_db cannot be NULL\n");
        return -1;
    }
    if(!keyname)
    {
        PRT_INFO("keyname cannot be NULL\n");
        return -1;
    }

    char *query_statement = NULL;
    query_statement = sqlite3_mprintf("SELECT * FROM handfeature WHERE keyName = %Q;",keyname);
    if (query_statement == NULL) return -1;
    if (sqlite3_prepare(hand_db, query_statement, strlen(query_statement), &m_pFaceStmt, NULL) != SQLITE_OK)
    {
        PRT_INFO("sql error:%s\n", sqlite3_errmsg(hand_db));
        PRT_INFO("ERROR:query preparation failed - %s\n", sqlite3_errmsg(hand_db));
        sqlite3_free(query_statement);
        query_statement = NULL;
        return -1;
    }
    sqlite3_free(query_statement);
    query_statement = NULL;
    sqlite3_step(m_pFaceStmt);//exec select
    return 0;
}

SQLITE_API int HandGestureDBApi::database_inquire_step()
{
    if(!hand_db)
    {
        PRT_INFO("face_db cannot be NULL\n");
        return -1;
    }
    if(!m_pFaceStmt)
    {
        PRT_INFO("m_pFaceStmt cannot be NULL\n");
        return -1;
    }
    return sqlite3_step(m_pFaceStmt);
}

int HandGestureDBApi::database_inquire_info(SGestureFeature &feature)
{
    if(!hand_db) {
        PRT_INFO("face_db cannot be NULL\n");
        return -1;
    }
    if(!m_pFaceStmt)
    {
         PRT_INFO("m_pFaceStmt cannot be NULL\n");
         return -1;
    }
    char* kname = (char *)sqlite3_column_text(m_pFaceStmt, 0);
    if(kname){
        feature.GestureName = kname;
    }

    const float* pFileContent1 = (const float*)sqlite3_column_blob(m_pFaceStmt,1);
    if (pFileContent1) {
        int anglebytes=sqlite3_column_bytes(m_pFaceStmt,1);
        memcpy(feature.angle,pFileContent1,anglebytes);
        //for(int i=0;i<bytes;i++)//print blob data
        // {
        //   printf("%f ",face_info->fdata_first[i]);
        // }
        // printf("\n");
   }
    const float* pFileContent2 = (const float*)sqlite3_column_blob(m_pFaceStmt,2);
    if (pFileContent2){
        int anglechabytes=sqlite3_column_bytes(m_pFaceStmt,2);
        memcpy(feature.anglecha,pFileContent2,anglechabytes);
    }

    const float* pFileContent3 = (const float*)sqlite3_column_blob(m_pFaceStmt,3);
    if (pFileContent3){
        int countbytes=sqlite3_column_bytes(m_pFaceStmt,3);
        memcpy(feature.count,pFileContent3,countbytes);
    }
    database_inquire_shutdown();
   return 0;
}

int HandGestureDBApi::database_inquire_shutdown()
{
    if(m_pFaceStmt == mpNULL)
    {
        PRT_INFO("m_pFaceStmt cannot be NULL\n");
        return -1;
    }
    sqlite3_finalize(m_pFaceStmt);
    m_pFaceStmt =mpNULL;
    return 0;
}

int HandGestureDBApi::database_shutdown(void)
{
  if(!hand_db) {
     PRT_INFO("face_db cannot be NULL\n");
     return -1;
  }
  sqlite3_close(hand_db);
  hand_db = NULL;
  return 0;
}
