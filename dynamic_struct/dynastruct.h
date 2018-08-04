/* 
Module for creating dynamic data structures in C
Data will be packed into a char array, and acessed using offsets
Constantinus Satrio 2018-08-04
*/
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct packer{
    char* buf;
    size_t size;
    size_t offset;
}packer;

typedef struct field{
    const char* name;
    unsigned int type;
    size_t offset;
} field;

typedef struct dynastruct{
    char* buf;
    field* fields;
} dynastruct;

#define INTEGER_T 1
#define FLOAT_T 2
#define DOUBLE_T 3
#define LONG_T 4
#define CHARS_T 5
#define CHAR_T 6

#define pack(_packer, data){size_t siz = sizeof(data); memcpy(_packer->buf+(_packer->offset), &data, siz); _packer->offset += siz;}
#define pack_char(_packer, data){size_t siz = strlen(data); memcpy(_packer->buf+(_packer->offset), data, siz); _packer->offset += siz;}
#define get_copy(_packer, ptr){size_t siz = sizeof(ptr); memcpy(&ptr, _packer->buf + _packer->offset, siz); _packer->offset += siz;}
#define reset_packer(_packer){memset(_packer->buf, 0, _packer->offset); _packer->offset = 0;}
#define create_fields(_size)({field* _f; _f = (field*)malloc(_size*sizeof(field)); _f;})
#define pack_field(_packer, _f, data, _name, _type){_f.name = _name; _f.type = _type; _f.offset = _packer->offset;\
size_t siz = sizeof(data); memcpy(_packer->buf+(_packer->offset), &data, siz);\
 _packer->offset += siz;}
#define free_packer(_packer){free(_packer->buf); free(_packer);}
#define free_dynastruct(_d){free(_d->fields); free(_d);}

static inline void* access (char *buf, size_t offset){
    return (void*) buf[offset];
}

static inline char* access_char(char *buf, size_t offset){
    return buf + offset;
}

static inline const char* field_type_name(unsigned int _type){
    switch(_type){
        case INTEGER_T : return "INTEGER_T";
        case FLOAT_T : return "FLOAT_T";
        case DOUBLE_T : return "DOUBLE_T";
        case LONG_T : return "LONG_T";
        case CHAR_T : return "CHAR_T";
        case CHARS_T : return "CHARS_T";
        default : return "UNDEFINED";
    }
}

static inline void* access_field(dynastruct* ds, size_t idx){
    field f = ds->fields[idx];
    printf("acessing field %s of type %s\n", f.name, field_type_name(f.type));
    return (void*) ds->buf + f.offset;
}

static inline packer* create_packer(size_t size){
    packer* p = (packer*) malloc(sizeof(packer));
    p->buf = (char*)malloc(size);
    memset(p->buf, 0, size);
    p->size = size;
    return p;
}