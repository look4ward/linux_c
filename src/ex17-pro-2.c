//向数据库添加更多操作，比如find。

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

struct Address {
    int id;
    int set;
    char *name;
    char *email;
};

struct Database {
    int MAX_DATA;
    int MAX_ROWS;
    struct Address *rows;
};

struct Connection {
    FILE *file;
    struct Database *db;
};

void die(const char *message, struct Connection *conn)
{
    if(errno) {
        perror(message);
    } else {
        printf("ERROR: %s\n", message);
    }

    if(conn) {
        if(conn->db) {
            if(conn->db->rows) {
                int i;
                for(i = 0; i < conn->db->MAX_ROWS; i++) {
                    free(conn->db->rows[i].name);
                    free(conn->db->rows[i].email);
                }
                free(conn->db->rows);
            }
            free(conn->db);
        }
        if(conn->file) fclose(conn->file);
        free(conn);
    }
    exit(1);
}

void Address_print(struct Address *addr)
{
    printf("%d %s %s\n",
            addr->id, addr->name, addr->email);
}

void Database_load(struct Connection *conn)
{
    for(int i = 0; i < conn->db->MAX_ROWS; i++){
        int rc = fread(&(conn->db->rows[i].id), sizeof(int), 1, conn->file);//把文件里的id读出到内存上的db
        if(rc != 1) die("Failed to load database.",conn);
        rc = fread(&(conn->db->rows[i].set), sizeof(int), 1, conn->file);//把文件里的set读出到内存上的db
        if(rc != 1) die("Failed to load database.",conn);
        rc = fread(conn->db->rows[i].name, sizeof(char) * conn->db->MAX_DATA, 1, conn->file);//把文件里的name读出到内存上的db
        if(rc != 1) die("Failed to load database.",conn);
        rc = fread(conn->db->rows[i].email, sizeof(char) * conn->db->MAX_DATA, 1, conn->file);//把文件里的email读出到内存上的db
        if(rc != 1) die("Failed to load database.",conn);
    }
}

struct Connection *Database_open(const char *filename, char mode, char *argv1, char *argv2)
{
    int i;

    struct Connection *conn = malloc(sizeof(struct Connection));
    if(!conn) die("Memory error", NULL);

    conn->db = malloc(sizeof(struct Database));
    if(!conn->db) die("Memory error", conn);

    conn->db->MAX_DATA = atoi(argv1);
    conn->db->MAX_ROWS = atoi(argv2);

    conn->db->rows = malloc(sizeof(struct Address) * conn->db->MAX_ROWS);
    if(!conn->db->rows) die("Memory error", conn);

    for(i = 0; i < conn->db->MAX_ROWS; i++) {
        conn->db->rows[i].name = malloc(conn->db->MAX_DATA);
        conn->db->rows[i].email = malloc(conn->db->MAX_DATA);
        if(!conn->db->rows[i].name || !conn->db->rows[i].email)
            die("Memory error", conn);
        memset(conn->db->rows[i].name, 0, conn->db->MAX_DATA);
        memset(conn->db->rows[i].email, 0, conn->db->MAX_DATA);
    }

    if(mode == 'c') {
        conn->file = fopen(filename, "w");
    } else {
        conn->file = fopen(filename, "r+");

        if(conn->file) {
            Database_load(conn);
        }
    }

    if(!conn->file) die("Failed to open the file", conn);

    return conn;
}

void Database_close(struct Connection *conn)
{
    if(conn) {
        if(conn->file) fclose(conn->file);
        if(conn->db) {
            if(conn->db->rows) {
                int i;
                for(i = 0; i < conn->db->MAX_ROWS; i++) {
                    free(conn->db->rows[i].name);
                    free(conn->db->rows[i].email);
                }
                free(conn->db->rows);
            }
            free(conn->db);
        }
        free(conn);
    }
}

void Database_write(struct Connection *conn)
{
    rewind(conn->file);
    for(int i = 0; i < conn->db->MAX_ROWS; i++){
        int rc = fwrite(&(conn->db->rows[i].id), sizeof(int), 1, conn->file);
        if(rc != 1) die("Failed to write database.", conn);
        rc = fwrite(&(conn->db->rows[i].set), sizeof(int), 1, conn->file);
        if(rc != 1) die("Failed to write database.", conn);
        rc = fwrite(conn->db->rows[i].name, sizeof(char) * conn->db->MAX_DATA, 1, conn->file);
        if(rc != 1) die("Failed to write database.", conn);
        rc = fwrite(conn->db->rows[i].email, sizeof(char) * conn->db->MAX_DATA, 1, conn->file);
        if(rc != 1) die("Failed to write database.", conn);
    }

    int rc = fflush(conn->file);
    if(rc == -1) die("Cannot flush database.", conn);
}

void Database_create(struct Connection *conn)
{
    int i;

    for(i = 0; i < conn->db->MAX_ROWS; i++) {
        conn->db->rows[i].id = i;
        conn->db->rows[i].set = 0;
    }
}

void Database_set(struct Connection *conn, int id, const char *name, const char *email)
{
    int MAX_DATA = conn->db->MAX_DATA;

    if(conn->db->rows[id].set) die("Already set, delete it first", conn);

    conn->db->rows[id].set = 1;

    char *res = strncpy(conn->db->rows[id].name, name, MAX_DATA);
    if(!res) die("Name copy failed", conn);
    conn->db->rows[id].name[MAX_DATA - 1] = '\0';

    res = strncpy(conn->db->rows[id].email, email, MAX_DATA);
    if(!res) die("Email copy failed", conn);
    conn->db->rows[id].email[MAX_DATA - 1] = '\0';
}

void Database_get(struct Connection *conn, int id)
{
    struct Address *addr = &conn->db->rows[id];

    if(addr->set) {
        Address_print(addr);
    } else {
        die("ID is not set", conn);
    }
}

void Database_find(struct Connection *conn, char *substr){
    for(int i = 0;i < conn->db->MAX_ROWS; i++){
        if(conn->db->rows[i].set){
            if(strstr(conn->db->rows[i].name, substr)){
                Address_print(&conn->db->rows[i]);
            } 
            else if(strstr(conn->db->rows[i].email, substr)){
                Address_print(&conn->db->rows[i]);
            } 
        }
    }
}

void Database_delete(struct Connection *conn, int id)
{
    conn->db->rows[id].id = id;
    conn->db->rows[id].set= 0;
    memset(conn->db->rows[id].name, 0, conn->db->MAX_DATA);
    memset(conn->db->rows[id].email, 0, conn->db->MAX_DATA);
}

void Database_list(struct Connection *conn)
{
    int i = 0;
    int MAX_ROWS = conn->db->MAX_ROWS;

    for(i = 0; i < MAX_ROWS; i++) {
        struct Address *cur = &conn->db->rows[i];

        if(cur->set) {
            Address_print(cur);
        }
    }
}

int main(int argc, char *argv[])
{
    if(argc < 5) {
        printf("USAGE: %s <MAX_DATA> <MAX_ROWS> <dbfile> <action> [params]\n", argv[0]);
//                     [0]   [1]        [2]        [3]     [4]       [5]   
        return 1;
    }
    char *filename = argv[3];
    char action = argv[4][0];
    struct Connection *conn = Database_open(filename, action, argv[1], argv[2]);
    int id = 0;

    if(argc > 5) id = atoi(argv[5]);
    if(id >= conn->db->MAX_ROWS) die("There's not that many records.", conn);

    switch(action) {
        case 'c':
            Database_create(conn);
            Database_write(conn);
            break;

        case 'g':
            if(argc != 6) die("Need an id to get", conn);

            Database_get(conn, id);
            break;
        
        case 'f':
            if(argc != 6) die("Need string to find", conn);

            Database_find(conn, argv[5]);
            break;

        case 's':
            if(argc != 8) die("Need id, name, email to set", conn);

            Database_set(conn, id, argv[6], argv[7]);
            Database_write(conn);
            break;

        case 'd':
            if(argc != 6) die("Need id to delete", conn);

            Database_delete(conn, id);
            Database_write(conn);
            break;

        case 'l':
            Database_list(conn);
            break;
        default:
            die("Invalid action, only: c=create, g=get, s=set, d=del, l=list", conn);
    }

    Database_close(conn);

    return 0;
}
