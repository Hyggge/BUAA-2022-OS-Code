#include <env.h>
#include <pmap.h>
#include <printf.h>

/* Overview:
 *  Implement simple round-robin scheduling.
 *
 *
 * Hints:
 *  1. The variable which is for counting should be defined as 'static'.
 *  2. Use variable 'env_sched_list', which is a pointer array.
 *  3. CANNOT use `return` statement!
 */
/*** exercise 3.15 ***/

extern struct Env* curenv;
extern struct Env_list env_sched_list[];


void sched_yield(void)
{
//	printf("yield!!!\n");
    static int count = 0; // remaining time slices of current env
    static int point = 0; // current e:nv_sched_list index
    
    struct Env *e = curenv;

    if (count == 0 || e == NULL || e->env_status != ENV_RUNNABLE) {
       	if (e != NULL) {
			LIST_REMOVE(e, env_sched_link);
        	LIST_INSERT_TAIL(&env_sched_list[1-point], e, env_sched_link);
        }
        while(1) {
            if (LIST_EMPTY(&env_sched_list[point])) {
                point = 1 - point;
            }
            
            e = LIST_FIRST(&env_sched_list[point]);

            if (e->env_status == ENV_RUNNABLE) {
                break;
            } 
            else {
                LIST_REMOVE(e, env_sched_link);
                LIST_INSERT_TAIL(&env_sched_list[1-point], e, env_sched_link);
            }
        }
		count = e->env_pri;
    }
//	printf("%d going to run\n", e->env_id);
    count--;
    env_run(e);


    /*  hint:
     *  1. if (count==0), insert `e` into `env_sched_list[1-point]`
     *     using LIST_REMOVE and LIST_INSERT_TAIL.
     *  2. if (env_sched_list[point] is empty), point = 1 - point;
     *     then search through `env_sched_list[point]` for a runnable env `e`, 
     *     and set count = e->env_pri
     *  3. count--
     *  4. env_run()
     *
     *  functions or macros below may be used (not all):
     *  LIST_INSERT_TAIL, LIST_REMOVE, LIST_FIRST, LIST_EMPTY
     */
}

