#include "../libs/general/general.h"
#include "../libs/util/util.h"

int main(int argc, char*argv[]){
    int n = atoi(argv[1]);
    int m = atoi(argv[2]);

    int i, j , k;
    char *inputs[1] = {"pippo"};

    files_array files = get_files(inputs, 1, true);

    for(i = 0; i < n; i++){
        p_input *p=get_P_input(files.files, files.size, n);
        printf("P: %d\n", i);
        for( k= 0; k < p[i].path_size ; k++) {
            printf("Path : %s\n", p[i].paths[k]);
            range *r = get_ranges_from_size(p[i].paths[k], m);

            /*for (j = 0; j < m; j++) {
                printf("Q: %d | %d - %d\n", j, r[j].start, r[j].end);
            }*/
            printf("\n\n");
        }
        printf("\n\n");
    }
    return 0;
}