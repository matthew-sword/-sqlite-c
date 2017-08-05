#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite3.h" 

static int callback(void *NotUsed, int argc, char **argv, char **azColName);

//连接数据库 ,如果没有就创建一个 
void connect(sqlite3 *db);   

//创建数据表
void creat_table(sqlite3 *db);

//插入学生数据
void insert_students_data(sqlite3 *db);

//插入成绩数据
void insert_transcript_data(sqlite3 *db);

//查找数据
void select_data(sqlite3 *db);

//更新数据
void update_data(sqlite3 *db);

//删除数据
void delete_data(sqlite3 *db); 


int main(int argc, char *argv[]) 
{	
   sqlite3 *db;
   
   connect(db);
  
   creat_table(db);

   insert_students_data(db);
   
   insert_transcript_data(db);
   
   select_data(db);
   
   update_data(db);
   	
   delete_data(db); 
   
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

void connect(sqlite3 *db)
{
   char *zErrMsg = 0;
   int rc;

   rc = sqlite3_open("SMS.db", &db);

   if( rc ){
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      exit(0);
   }else{
      fprintf(stderr, "Opened database successfully\n");
   }
   
   sqlite3_close(db);
} 

void creat_table(sqlite3 *db)
{
   char *zErrMsg = 0;
   int  rc;
   char *sql;

   /* Open database */
   rc = sqlite3_open("SMS.db", &db);
   if( rc ){
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      exit(0);
   }else{
      fprintf(stdout, "Opened database successfully\n");
   }

   /* Create SQL statement of students information*/
   sql = "CREATE TABLE STUDENTS("  \
         "ID INT PRIMARY KEY     NOT NULL," \
         "NAME           TEXT    NOT NULL," \
         "SEX        CHAR(10)," \
         "AGE            INT     NOT NULL," \
         "NATION        CHAR(50)," \
         "ORIGIN        CHAR(50) );";

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   if( rc != SQLITE_OK ){
   fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
      fprintf(stdout, "Students information table created successfully\n");
   }
   
   
   /* Create SQL statement of courses scores*/
   sql = "CREATE TABLE TRANSCRIPT("  \
         "ID INT PRIMARY KEY     NOT NULL," \
         "CALCULUS      REAL ," \
         "LINEAR_ALGEBRA      REAL ," \
         "DATA_STRUCTURE      REAL ," \
         "CIRCUITRY      REAL ," \
         "C_LANGUAGE        REAL );";

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   if( rc != SQLITE_OK ){
   fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
      fprintf(stdout, "transcript table created successfully\n");
   }
   
   printf("\nstatement:\n");
   printf("\nstudents information:\n");
   printf("id  name  sex  age  nation  origin\n");
   printf("\ntranscipt:\n");
   printf("id  calculus  linear_algebra  data_structure  circuitry  c_language\n");

   sqlite3_close(db);
}

void insert_students_data(sqlite3 *db)
{
	char *zErrMsg = 0;
    int  rc;
    char *sql;
            
       /* Open database */
   rc = sqlite3_open("SMS.db", &db);
   if( rc ){
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      exit(0);
   }else{
      fprintf(stderr, "Opened database successfully\n");
   }
   
   /* Create SQL statement */
   
   
   sql = "INSERT INTO STUDENTS (ID,NAME,SEX,AGE,NATION,ORIGIN) "  \
         "VALUES (1, '李雷', '男', 19,'汉', '北京' ); " \
		 "INSERT INTO STUDENTS (ID,NAME,SEX,AGE,NATION,ORIGIN) "  \
         "VALUES (2, '韩梅梅', '男', 19,'汉', '上海' ); " \
         "INSERT INTO STUDENTS (ID,NAME,SEX,AGE,NATION,ORIGIN) "  \
         "VALUES (3, '李华', '男', 19,'汉', '天津' ); " \
         "INSERT INTO STUDENTS (ID,NAME,SEX,AGE,NATION,ORIGIN) "  \
         "VALUES (4, '麦克雷', '男', 19,'汉', '重庆' ); ";
		 
		 
		 

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

void insert_transcript_data(sqlite3 *db)
{
	char *zErrMsg = 0;
    int  rc;
    char *sql;
            
       /* Open database */
   rc = sqlite3_open("SMS.db", &db);
   if( rc ){
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      exit(0);
   }else{
      fprintf(stderr, "Opened database successfully\n");
   }
   
   /* Create SQL statement */
   
   
   sql = "INSERT INTO TRANSCRIPT (ID,CALCULUS,LINEAR_ALGEBRA,DATA_STRUCTURE,CIRCUITRY,C_LANGUAGE) "  \
         "VALUES (1, 99.3,88.2, 98.5, 67.6,85.6 ); " \
		 "INSERT INTO TRANSCRIPT (ID,CALCULUS,LINEAR_ALGEBRA,DATA_STRUCTURE,CIRCUITRY,C_LANGUAGE) "  \
         "VALUES (2, 99.3,88.2, 98.5, 67.6,85.6 ); " \
		 "INSERT INTO TRANSCRIPT (ID,CALCULUS,LINEAR_ALGEBRA,DATA_STRUCTURE,CIRCUITRY,C_LANGUAGE) "  \
         "VALUES (3, 99.3,88.2, 98.5, 67.6,85.6 ); " \
		 "INSERT INTO TRANSCRIPT (ID,CALCULUS,LINEAR_ALGEBRA,DATA_STRUCTURE,CIRCUITRY,C_LANGUAGE) "  \
         "VALUES (4, 99.3,88.2, 98.5, 67.6,85.6 ); " ;
		 
		 
		 

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

void select_data(sqlite3 *db)
{
   char *zErrMsg = 0;
   int rc;
   char *sql;
   const char* data = "Callback function called";

   /* Open database */
   rc = sqlite3_open("SMS.db", &db);
   if( rc ){
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      exit(0);
   }else{
      fprintf(stderr, "Opened database successfully\n");
   }

   /* Create SQL statement */
   sql = "SELECT * from STUDENTS";

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
      fprintf(stdout, "Operation done successfully\n");
   }
   sqlite3_close(db);
}

void update_data(sqlite3 *db)
{
   char *zErrMsg = 0;
   int rc;
   char *sql;
   const char* data = "Callback function called";

   /* Open database */
   rc = sqlite3_open("SMS.db", &db);
   if( rc ){
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      exit(0);
   }else{
      fprintf(stderr, "Opened database successfully\n");
   }

   /* Create merged SQL statement */
   sql = "UPDATE STUDENTS set SEX = '女' where ID=2; " \
         "SELECT * from STUDENTS";

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
      fprintf(stdout, "Operation done successfully\n");
   }
   sqlite3_close(db);
}

void delete_data(sqlite3 *db)
{
   char *zErrMsg = 0;
   int rc;
   char *sql;
   const char* data = "Callback function called";

   /* Open database */
   rc = sqlite3_open("SMS.db", &db);
   if( rc ){
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      exit(0);
   }else{
      fprintf(stderr, "Opened database successfully\n");
   }

   /* Create merged SQL statement */
   sql = "DELETE from STUDENTS where ID=1; " \
         "SELECT * from STUDENTS";

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
      fprintf(stdout, "Operation done successfully\n");
   }
   sqlite3_close(db);
}
