#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

struct Args {
    int* num;
    int mod;
    int curPnum;
    int pnum;
    int k;
};

pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;

void gaussian(void* _arg) {
    struct Args* arg = _arg;
    for (int i = arg->curPnum; i <= arg->k; i += arg->pnum) {
        pthread_mutex_lock(&mut);
        *arg->num = (*(arg->num) * i) % arg->mod;
        pthread_mutex_unlock(&mut);
    }
}

int main(int argc, char **argv) {
    int pnum = 1, mod = 1, k = 1;

    static struct option options[] = {
            {"k", required_argument, 0, 0},
            {"pnum", required_argument, 0, 0},
            {"mod", required_argument, 0, 0},
            {0, 0, 0, 0}
    };

    while (1) {
        int option_index = 0;
        int c = getopt_long(argc, argv, "k", options, &option_index);

        if(c == -1) {
            break;
        }

        switch(c) {
            case 0: {
                switch(option_index) {
                    case 0: {
                        k = atoi(optarg);
                        if (k < 0) {
                            printf("K must be a positive number or 0. Now K is %d\n", k);
                            return 1;
                        }
                    }
                    case 1: {
                        pnum = atoi(optarg);
                        if (pnum < 1) {
                            printf("pnum must be a positive number. Now pnum is %d\n", pnum);
                            return 2;
                        }
                        break;
                    }
                    case 2: {
                        mod = atoi(optarg);
                        if (mod < 0) {
                            printf("Mod must be a positive number. Now mod is %d\n", mod);
                            return 3;
                        }
                        break;
                    }
                }
                break;
            }
            default: {
                printf("getopt returned character code 0%o?\n", c);
            }
        }
    }

    int curPnum = 0;
    pthread_t* thArray = (pthread_t*)malloc(sizeof(pthread_t) * curPnum);

    struct Args* arg = malloc(pnum * sizeof(struct Args));

    int num = 1;
    for (curPnum = 0; curPnum < pnum; curPnum++) {
        arg[curPnum].num = &num;
        arg[curPnum].mod = mod;
        arg[curPnum].pnum = pnum;
        arg[curPnum].k = k;
        arg[curPnum].curPnum = curPnum + 1;
        if (pthread_create(thArray + curPnum, NULL, (void*)gaussian, (void*)(&(arg[curPnum]))) != 0) {
            perror("pthread_create");
            exit(1);
        }
    }

    curPnum--;

    for (; curPnum >= 0; curPnum--) {
        if (pthread_join(thArray[curPnum], NULL) != 0) {
            perror("pthread_join");
            exit(1);
        }
    }

    printf ("Answer: %d\n", num);
    free(thArray);

    return 0;
}