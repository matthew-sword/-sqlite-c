#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite3.h"

static int callback(void *NotUsed, int argc, char **argv, char **azColName);

//连接数据库 ,如果没有就创建一个
char* connect(sqlite3 *db);

//创建数据表
void create_table(sqlite3 *db,char* dbname);

//插入数据
void insert_data(sqlite3 *db,char* dbname);

//查找数据
void select_data(sqlite3 *db,char* dbname);

//更新数据
void update_data(sqlite3 *db,char* dbname);

//删除数据
void delete_data(sqlite3 *db,char* dbname);

//SQL命名行模式
void sql_command(sqlite3 *db,char* dbname);


int main(int argc, char *argv[])
{
    sqlite3 *db = NULL;
    char* dbname = NULL;
    printf("welcome to students manage system\n");
    printf("please select a option\n");
    printf(  "\n1.connect or create a database\n" \
             "2.create a table \n" \
             "3.insert data \n" \
             "4.search data \n" \
             "5.update data \n" \
             "6.delete data \n" \
             "7.sql_command mode \n" \
             "0.exit the program\n");

    int select_a = 1;

    while (select_a)
    {
        printf("\nyour option >>> ");
        scanf("%d",&select_a);
        getchar();

        switch (select_a)
        {
            case 1: {
                dbname = connect(db);
                break;
            }

            case 2: {
                create_table(db,dbname);
                break;
            }

            case 3: {
                insert_data(db,dbname);
                break;
            }

            case 4: {
                select_data(db,dbname);
                break;
            }

            case 5: {
                update_data(db,dbname);
                break;
            }

            case 6: {
                delete_data(db,dbname);
                break;
            }

            case 7: {
                sql_command(db,dbname);
                break;
            }

            case 0:{
                sqlite3_close(db);
                printf("program end successfully\n");
                break;
            }

            default: {
                printf("input error!\nplease put in again\n");
                break;
            }
        }
    }
    return 0;
}


static int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
    int i;
    for(i=0; i<argc; i++){
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

char* connect(sqlite3 *db)
{
    char *zErrMsg = 0;
    int rc;

//command line start
    char* dbname;
    dbname = (char*)malloc(sizeof(char) * 256);
    printf("database name(*.db) >>>");
    scanf("%s",dbname);
//command line end

    rc = sqlite3_open(dbname, &db);

    if( rc ){
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        exit(0);
    }else{
        fprintf(stderr, "Opened database successfully\n");
        return dbname;
    }

}

void create_table(sqlite3 *db,char* dbname)
{
    char *zErrMsg = 0;
    int  rc;
    char *sql;

    //command line start
    char tb_name[256];
    printf("\ncreate table name >>>");
    scanf("%s",tb_name);
    getchar();

    char property[2000];
    printf("put in the properties and data type(INT TEXT CHAR(50) REAL)\n");
    printf("example: property1 TYPE1, property2 TYPE2, property3 TYPE3\n");
    printf("\nproperties >>>");
    gets(property);
    //command line end

    //generate sql command
    sql = (char*)malloc(sizeof(char) * 2000);
    memset(sql,'\0',1);
    sql = strcat(sql,"CREATE TABLE ");
    sql = strcat(sql,tb_name);
    sql = strcat(sql,"(");
    sql = strcat(sql,property);
    sql = strcat(sql,");");
    //puts(sql);

    //open database
    rc = sqlite3_open(dbname, &db);
    if( rc ){
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        exit(0);
    }


    //Execute SQL statement
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }else{
        fprintf(stdout, "table created successfully\n");
    }

    free(sql);
    sqlite3_close(db);
}

void insert_data(sqlite3 *db,char* dbname)
{
    char *zErrMsg = 0;
    int  rc;
    char *sql;
    char insert[2000];
    sql = (char*)malloc(sizeof(char) * 2000);
    memset(sql,'\0',1);

    /* Open database */
    rc = sqlite3_open(dbname, &db);
    if( rc ){
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        exit(0);
    }

    char tb_name[256];
    printf("\ninsert table name >>>");
    scanf("%s",tb_name);
    getchar();

    while (1)
    {
        printf("put in the properties and the values\n");
        printf("example: (property1,property2,property3) VALUES (VALUE1,VALUE2,VALUE3)\n");
        printf("\ninsert data >>>");
        gets(insert);
        sql = strcat(sql,"INSERT INTO ");
        sql = strcat(sql,tb_name);
        sql = strcat(sql," ");
        sql = strcat(sql,insert);
        sql = strcat(sql,";");

        printf("\ncontinue to insert(Y/N)? >>>");
        if (getchar() == 'N' || getchar() == 'n')
            break;
    }

    //puts(sql);

    /* Execute SQL statement */
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }else{
        fprintf(stdout, "Records created successfully\n");
    }

    sqlite3_close(db);
}

void select_data(sqlite3 *db,char* dbname)
{
    char *zErrMsg = 0;
    int rc;
    char *sql;
    const char* data = "Callback function called";

    /* Open database */
    rc = sqlite3_open(dbname, &db);
    if( rc ){
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        exit(0);
    }

    //command line start
    char tb_name[256];
    printf("\nselect table name >>>");
    scanf("%s",tb_name);
    getchar();
    //command line end

    //generate sql command
    sql = (char*)malloc(sizeof(char) * 2000);
    memset(sql,'\0',1);
    sql = strcat(sql,"SELECT * from ");
    sql = strcat(sql,tb_name);

    //puts(sql);

    //Execute SQL statement
    rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    sqlite3_close(db);

}

void update_data(sqlite3 *db,char* dbname)
{
    char *zErrMsg = 0;
    int rc;
    char *sql;
    const char* data = "Callback function called";

    //command line start
    char tb_name[256];
    printf("\nupdate table name >>>");
    scanf("%s",tb_name);
    getchar();
    //command line end

    //generate sql command
    char up_data[2000];
    char position[200];
    sql = (char*)malloc(sizeof(char) * 2000);
    memset(sql,'\0',1);

    printf("put in the properties and updated_data \n");
    printf("example: property1=value1,property2=value2\n");
    printf("\nupdated_data >>>");
    gets(up_data);
    printf("\nwhere (property_x=value_x) >>>");
    gets(position);


    sql = strcat(sql,"UPDATE ");
    sql = strcat(sql,tb_name);
    sql = strcat(sql," SET ");
    sql = strcat(sql,up_data);
    sql = strcat(sql," WHERE ");
    sql = strcat(sql,position);
    sql = strcat(sql,";");

    //puts(sql);

    // Open database
    rc = sqlite3_open(dbname, &db);
    if( rc ){
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        exit(0);
    }

    //Execute SQL statement
    rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }else{
        fprintf(stdout, "Records created successfully\n");
    }

    sqlite3_close(db);
}

void delete_data(sqlite3 *db,char* dbname)
{
    char *zErrMsg = 0;
    int rc;
    char *sql;
    const char* data = "Callback function called";

    //command line start
    char tb_name[256];
    printf("\ndelete table name >>>");
    scanf("%s",tb_name);
    getchar();
    //command line end

    //generate sql command
    char position[200];
    sql = (char*)malloc(sizeof(char) * 2000);
    memset(sql,'\0',1);

    printf("put in the primary key \n");
    printf("example: delete from where >>>property_key=value_key\n");
    printf("\ndelete from where >>>");
    gets(position);

    sql = strcat(sql,"DELETE from ");
    sql = strcat(sql,tb_name);
    sql = strcat(sql," WHERE ");
    sql = strcat(sql,position);
    sql = strcat(sql,";");
    sql = strcat(sql,"SELECT * from ");
    sql = strcat(sql,tb_name);

    //puts(sql);

    //Open database
    rc = sqlite3_open(dbname, &db);
    if( rc ){
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        exit(0);
    }

    // Execute SQL statement
    rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }else{
        fprintf(stdout, "Operation done successfully\n");
    }
    sqlite3_close(db);

}

void sql_command(sqlite3 *db,char* dbname)
{
    char *zErrMsg = 0;
    int rc;
    char *sql;

    sql = (char*)malloc(sizeof(char) * 2000);
    memset(sql,'\0',1);
    printf("\nput in the sql command >>>");
    gets(sql);

    /* Open database */
    rc = sqlite3_open(dbname, &db);
    if( rc ){
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        exit(0);
    }

    /* Execute SQL statement */
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }else{
        fprintf(stdout, "Command executed successfully\n");
    }
    sqlite3_close(db);
}