#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

#define RESOURCE_ID 0
#define BUFFER_SIZE 128

void worker(void* arg1, void* arg2) {
  char write_buffer[BUFFER_SIZE] = "Hello, this is a test message.";
  char read_buffer[BUFFER_SIZE];

  if (requestresource(RESOURCE_ID) < 0) {
    printf(1, "Failed to request resource %d\n", RESOURCE_ID);
    exit();
  }

  if (writeresource(RESOURCE_ID, write_buffer, 0, strlen(write_buffer) + 1) < 0) {
    printf(1, "Failed to write to resource %d\n", RESOURCE_ID);
    exit();
  }

  if (readresource(RESOURCE_ID, 0, BUFFER_SIZE, read_buffer) < 0) {
    printf(1, "Failed to read from resource %d\n", RESOURCE_ID);
    exit();
  }

  printf(1, "Read from resource: %s\n", read_buffer);

  if (releaseresource(RESOURCE_ID) < 0) {
    printf(1, "Failed to release resource %d\n", RESOURCE_ID);
    exit();
  }

  // check reading from resource after releasing
  if (readresource(RESOURCE_ID, 0, BUFFER_SIZE, read_buffer) < 0) {
    printf(1, "Failed to read from resource %d\n", RESOURCE_ID);
    exit();
  }

  exit();
}

int main(int argc, char *argv[]) {
  thread_create(&worker, 0, 0);
  join(1);

  exit();
}
