#ifndef __DB_H__
#define __DB_H__

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *buffer;
    size_t buffer_length;
    ssize_t input_length;
} InputBuffer;

typedef enum { EXECUTE_SUCCESS, EXECUTE_TABLE_FULL } ExecuteResult;

typedef enum {
    META_COMMAND_SUCCESS,
    META_COMMAND_UNRECOGNIZED_COMMAND
} MetaCommandResult;

typedef enum {
    PREPARE_SUCCESS,
    PREPARE_STRING_TOO_LONG,
    PREPARE_SYNTAX_ERROR,
    PREPARE_UNRECOGNIZED_STATEMENT
} PrepareResult;

typedef enum { STATEMENT_INSERT, STATEMENT_SELECT } StatementType;

#define COLUMN_USERNAME_SIZE 32
#define COLUMN_EMAIL_SIZE 255

typedef struct {
    uint32_t id;
    char username[COLUMN_USERNAME_SIZE];
    char email[COLUMN_EMAIL_SIZE];
} Row;

typedef struct {
    StatementType type;
    Row row_to_insert;  // only used by insert statement.
} Statement;

#define size_of_attribute(Struct, Attribute) sizeof(((Struct *) 0)->Attribute)

static const uint32_t ID_SIZE = size_of_attribute(Row, id);
static const uint32_t USERNAME_SIZE = size_of_attribute(Row, username);
static const uint32_t EMAIL_SIZE = size_of_attribute(Row, email);
static const uint32_t ID_OFFSET = 0;
static const uint32_t USERNAME_OFFSET = ID_OFFSET + ID_SIZE;
static const uint32_t EMAIL_OFFSET = USERNAME_OFFSET + USERNAME_SIZE;
static const uint32_t ROW_SIZE = ID_SIZE + USERNAME_SIZE + EMAIL_SIZE;

/* duplicate symbols in constant issues
 * https://github.com/gzrjzcx/project_templete/issues/8 */
static const uint32_t PAGE_SIZE = 4096;
#define TABLE_MAX_PAGES 100
static const uint32_t ROWS_PER_PAGE = PAGE_SIZE / ROW_SIZE;
static const uint32_t TABLE_MAX_ROWS = ROWS_PER_PAGE * TABLE_MAX_PAGES;

typedef struct {
    uint32_t num_rows;
    void *pages[TABLE_MAX_PAGES];
} Table;

void print_row(Row *row);
void print_row_byte(Row *row);
void serialize_row(Row *source, void *destination);
void deserialize_row(void *source, Row *destination);
void *row_slot(Table *table, uint32_t row_num);
Table *new_table();
void free_table(Table *table);

InputBuffer *new_input_buffer();

MetaCommandResult do_meta_command(InputBuffer *input_buffer, Table *table);

PrepareResult prepare_statement(InputBuffer *input_buffer,
                                Statement *statement);
PrepareResult prepare_insert(InputBuffer *input_buffer, Statement *statement);
PrepareResult prepare_select(InputBuffer *input_buffer, Statement *statement);

ExecuteResult execute_insert(Statement *statement, Table *table);
ExecuteResult execute_select(Statement *statement, Table *table);
ExecuteResult execute_statement(Statement *statement, Table *table);

void print_prompt();
void read_input(InputBuffer *input_buffer, FILE *f);
void close_input_buffer(InputBuffer *input_buffer);

#endif /*  __DB_H__ */
