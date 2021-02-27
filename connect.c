#include <mysql.h>
#include <stdio.h>
#include "dbError.h"
#include <string.h>

#define DB_HOST "127.0.0.1"
#define DB_USER "root"
#define DB_PASS "1111"
#define DB_NAME "rootdb"
#define CHOP(x) x[strlen(x) - 1] = ' '

int main(void)
{
    MYSQL       *connection=NULL, conn;
    MYSQL_RES   *sql_result;
    MYSQL_ROW   sql_row;
    int       query_stat; 

    char name[12];
    char address[80];
    char tel[12];
    char query[255];
    
    mysql_init(&conn);

    connection = mysql_real_connect(&conn, DB_HOST,
                                    DB_USER, DB_PASS,
                                    DB_NAME, 3306,
                                    (char *)NULL, 0);

    if (connection == NULL)
    {
        fprintf(stderr, "DB Connecting Error : %s", mysql_error(&conn));
        return 1;
    }

    query_stat = mysql_query(connection, "select * from test");
    if (query_stat != 0)
    {
        fprintf(stderr, "DB Query Error : %s", mysql_error(&conn));
        return 1;
    }
    
    sql_result = mysql_store_result(connection);
    
    printf("%+11s %-30s %-10s", "code", "name", "desc");
    while ( (sql_row = mysql_fetch_row(sql_result)) != NULL )
    {
        printf("%+11s %-30s %-10s", sql_row[0], sql_row[1], sql_row[2]);
    }

    mysql_free_result(sql_result);

    printf("code :");
    fgets(code, 50, stdin);
    CHOP(code);

    printf("name :");
    fgets(name, 50, stdin);
    CHOP(name);

    printf("desc :");
    fgets(desc, 500, stdin);
    CHOP(desc);

    sprintf(query, "insert into test values "
                   "('%s', '%s', '%s')",
                   code, name, desc);

    query_stat = mysql_query(connection, query);
    if (query_stat != 0)
    {
        fprintf(stderr, "DB Query Error : %s", mysql_error(&conn));
        return 1;
    }

    mysql_close(connection);
}