#ifndef __DIN_PHIL__
#define __DIN_PHIL__

#include <stdbool.h>

typedef struct phil_ {

	int phil_id;
	pthread_t thread_handle;
	int eat_count;
} phil_t;

typedef struct spoon_ {

	int spoon_id;
	bool is_used;	/* bool to indicate if the spoon is being used or not */
	phil_t *phil;	/* If used, then which philosopher is using it */
	pthread_mutex_t mutex; /* For Mutual Exclusion */
	pthread_cond_t cv;	/* For thread Co-ordination competing for this Resource */
} spoon_t;

#endif /* __DIN_PHIL__  */
