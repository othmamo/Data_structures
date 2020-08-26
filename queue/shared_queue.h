/* shared_queue.h : a producer/consumer queue */

# ifndef EPITA_IP_SHARED_QUEUE_H_
# define EPITA_IP_SHARED_QUEUE_H_

# include <semaphore.h>
# include <stdlib.h>


struct shared_queue {
  sem_t lock, size;
  struct queue *store;
};

/* new_shared_queue() allocate and initialize a new queue             */
struct shared_queue* new_shared_queue(void);

/* shared_queue_push(queue, val) add val to the queue                 *
 * notify waiting threads when done                                   */
void shared_queue_push(struct shared_queue *queue, int val);

/* shared_queue_pop(queue) pop a new value from the queue             *
 * blocks while the queue is empty                                    */
int shared_queue_pop(struct shared_queue *queue);

/* shared_queue_destroy(queue) destroy the queue                      *
 * free any remaining memory                                          */
void shared_queue_destroy(struct shared_queue *queue);

# endif /* EPITA_IP_SHARED_QUEUE_H_ */
