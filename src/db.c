#include "db.h"
#include <stdio.h>
#include <string.h>

InputBuffer *new_input_buffer()
{
    InputBuffer *input_buffer = (InputBuffer *) malloc(sizeof(InputBuffer));
    input_buffer->buffer = NULL;
    input_buffer->buffer_length = 0;
    input_buffer->input_length = 0;

    return input_buffer;
}

void show_buffer(InputBuffer *b)
{
    printf("InputBuffer->buffer: [%s]\n", b->buffer);
    printf("InputBuffer->input_length: [%d]\n", b->input_length);
    printf("InputBuffer->buffer_length: [%d]\n", b->buffer_length);
}

MetaCommandResult do_meta_command(InputBuffer *input_buffer, Table *table)
{
    if (strcmp(input_buffer->buffer, ".exit") == 0) {
        close_input_buffer(input_buffer);
        free_table(table);
        exit(EXIT_SUCCESS);
    } else {
        return META_COMMAND_UNRECOGNIZED_COMMAND;
    }
}

PrepareResult prepare_statement(InputBuffer *input_buffer, Statement *statement)
{
    if (strncmp(input_buffer->buffer, "insert", 6) == 0) {
        return prepare_insert(input_buffer, statement);
    }
    if (strcmp(input_buffer->buffer, "select") == 0) {
        return prepare_select(input_buffer, statement);
    }
    return PREPARE_UNRECOGNIZED_STATEMENT;
}

PrepareResult prepare_insert(InputBuffer *input_buffer, Statement *statement)
{
    statement->type = STATEMENT_INSERT;

    char *keyword = strtok(input_buffer->buffer, " ");
    char *id_string = strtok(NULL, " ");
    char *username = strtok(NULL, " ");
    char *email = strtok(NULL, " ");

    if (id_string == NULL || username == NULL || email == NULL)
        return PREPARE_SYNTAX_ERROR;

    int id = atoi(id_string);
    if (strlen(email) > COLUMN_EMAIL_SIZE)
        return PREPARE_STRING_TOO_LONG;

    statement->row_to_insert.id = id;
    strcpy(statement->row_to_insert.username, username);
    strcpy(statement->row_to_insert.email, email);

    return PREPARE_SUCCESS;
}

PrepareResult prepare_select(InputBuffer *input_buffer, Statement *statement)
{
    statement->type = STATEMENT_SELECT;
    return PREPARE_SUCCESS;
}

ExecuteResult execute_insert(Statement *statement, Table *table)
{
    if (table->num_rows >= TABLE_MAX_ROWS) {
        return EXECUTE_TABLE_FULL;
    }

    Row *row_to_insert = &(statement->row_to_insert);

    serialize_row(row_to_insert, row_slot(table, table->num_rows));
    table->num_rows += 1;

    return EXECUTE_SUCCESS;
}

ExecuteResult execute_select(Statement *statement, Table *table)
{
    for (uint32_t i = 0; i < table->num_rows; i++) {
        Row *row = new_row();
        deserialize_row(row_slot(table, i), row);
        print_row(row);
        free(row);
    }
    return EXECUTE_SUCCESS;
}

ExecuteResult execute_statement(Statement *statement, Table *table)
{
    switch (statement->type) {
    case (STATEMENT_INSERT):
        return execute_insert(statement, table);
    case (STATEMENT_SELECT):
        return execute_select(statement, table);
    }
}

void print_prompt()
{
    printf("db > ");
}

void read_input(InputBuffer *input_buffer, FILE *f)
{
    ssize_t bytes_read =
        // Use getdelim to explicitly specify delimiter
        getdelim(&(input_buffer->buffer), &(input_buffer)->buffer_length, '\n',
                 f);

    if (bytes_read <= 0) {
        printf("Error reading input\n");
        exit(EXIT_FAILURE);
    }

    ssize_t actual_bytes_read = 0;
    if (input_buffer->buffer[bytes_read - 1] != '\n') {
        // no \n
        // e.g. [h e l l o \0]
        // bytes_read = 5
        // actual_bytes_read = 5
        actual_bytes_read = bytes_read;
    } else {
        // has \n
        // e.g. [h e l l o \n \0]
        // bytes_read = 6 (getdelim won't ignore \n)
        // actual_bytes_read = 6 - 1 = 5
        actual_bytes_read = bytes_read - 1;
    }

    input_buffer->input_length = actual_bytes_read;
    input_buffer->buffer[actual_bytes_read] = 0;
}

void close_input_buffer(InputBuffer *input_buffer)
{
    free(input_buffer->buffer);
    free(input_buffer);
}

Row *new_row()
{
    Row *row = calloc(1, sizeof(Row));
    return row;
}

void print_row(Row *row)
{
    printf("(%d, %s, %s)\n", row->id, row->username, row->email);
}

void print_table(Table *table)
{
    char *ptr = table->pages;
    for (int i = 0; i < table->num_rows; i++) {
        Row *row = new_row();
        deserialize_row(row_slot(table, i), row);
        print_row(row);
    }
}

void print_row_byte(Row *row)
{
    char *ptr = row;
    for (int i = 0; i < sizeof(Row) + 1; i += 4) {
        if (i > sizeof(Row))
            return;
        printf("Row[%d-%d]: |%c%c%c%c|\n", i, i + 3, ptr[i], ptr[i + 1],
               ptr[i + 2], ptr[i + 3]);
    }
}


void serialize_row(Row *source, void *destination)
{
    memcpy(destination + ID_OFFSET, &(source->id), ID_SIZE);
    memcpy(destination + USERNAME_OFFSET, &(source->username), USERNAME_SIZE);
    memcpy(destination + EMAIL_OFFSET, &(source->email), EMAIL_SIZE);
}

void deserialize_row(void *source, Row *destination)
{
    memcpy(&(destination->id), source + ID_OFFSET, ID_SIZE);
    memcpy(&(destination->username), source + USERNAME_OFFSET, USERNAME_SIZE);
    memcpy(&(destination->email), source + EMAIL_OFFSET, EMAIL_SIZE);
}


void *row_slot(Table *table, uint32_t row_num)
{
    uint32_t page_num = row_num / ROWS_PER_PAGE;
    void *page = table->pages[page_num];
    if (page == NULL) {
        // Allocate memory only when we try to access page.
        page = table->pages[page_num] = malloc(PAGE_SIZE);
    }
    uint32_t row_offset = row_num % ROWS_PER_PAGE;
    uint32_t byte_offset = row_offset * ROW_SIZE;

    return page + byte_offset;
}

Table *new_table()
{
    Table *table = (Table *) malloc(sizeof(Table));
    table->num_rows = 0;
    for (uint32_t i = 0; i < TABLE_MAX_PAGES; i++) {
        table->pages[i] = NULL;
    }
    return table;
}

void free_table(Table *table)
{
    for (uint32_t i = 0; i < table->pages[i]; i++) {
        free(table->pages[i]);
    }
    free(table);
}