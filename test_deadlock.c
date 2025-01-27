#include "types.h"
#include "user.h"
#include "stat.h"

#define GRAPH_DEBUG

void thread1(void* arg1, void* arg2) {
    printf(1, "Thread 1: Requesting Resource 0\n");
    if (requestresource(0) == -1) {
        printf(1, "Thread 1: Deadlock detected while requesting Resource 0\n");
        exit();
    }
    sleep(100);
    printf(1, "Thread 1: Requesting Resource 1\n");
    if (requestresource(1) == -1) {
        printf(1, "Thread 1: Deadlock detected while requesting Resource 1\n");
        exit();
    }
    // printf(1, "Thread 1: Releasing Resource 0\n");
    // releaseresource(0);
    // printf(1, "Thread 1: Releasing Resource 1\n");
    // releaseresource(1);
    exit();
}

void thread2(void* arg1, void* arg2) {
    printf(1, "Thread 2: Requesting Resource 1\n");
    if (requestresource(1) == -1) {
        printf(1, "Thread 2: Deadlock detected while requesting Resource 1\n");
        exit();
    }
    sleep(500);
    printf(1, "Thread 2: Requesting Resource 0\n");
    if (requestresource(0) == -1) {
        printf(1, "Thread 2: Deadlock detected while requesting Resource 0\n");
        exit();
    }
    printf(1, "Thread 2: Releasing Resource 1\n");
    releaseresource(1);
    printf(1, "Thread 2: Releasing Resource 0\n");
    releaseresource(0);
    exit();
}

int main() {
    void* stack1 = malloc(4096);
    void* stack2 = malloc(4096);

    if (stack1 == 0 || stack2 == 0) {
        printf(1, "Failed to allocate memory for thread stacks\n");
        exit();
    }

    thread_create(&thread1, 0, 0);
    thread_create(&thread2, 0, 0);

    join(1);
    join(2);

    free(stack1);
    free(stack2);

    exit();
}
