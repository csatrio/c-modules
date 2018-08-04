#include "dynastruct.h"

int main(int argc, char* argv[]) {
    int tmp = 1;
    int field_size = 4;
    packer *p = create_packer(1024);
    dynastruct *ds = (dynastruct*)malloc(sizeof(dynastruct));
    ds->fields = create_fields(4);

    pack_field(p, ds->fields[0], tmp, "field_1", INTEGER_T);
    tmp = 2;
    pack_field(p, ds->fields[1], tmp, "field_2", INTEGER_T);
    tmp = 3;
    pack_field(p, ds->fields[2], tmp, "field_3", INTEGER_T);

    double t = 3.14;
    pack_field(p, ds->fields[3], t, "double_field", DOUBLE_T);
    printf("dynamic data struct size : %ld bytes \n", p->offset);
    ds->buf = p->buf;

    for(int i=0; i<4; i++){
        if(ds->fields[i].type == INTEGER_T){
            int *v = access_field(ds, i);
            printf("%d\n", *v);
        } else if(ds->fields[i].type == DOUBLE_T){
            double *v = access_field(ds, i);
            printf("%f\n", *v);
        }
    }
    free_packer(p);
    free_dynastruct(ds);
}
