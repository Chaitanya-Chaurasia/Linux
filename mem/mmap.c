#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>
 
 #define LIMIT_MAP 5
 
 void child_process_worker(void *map){
     
     printf("Verifying shared memory starts from <%p>", map);
     for (int i = 0; i < 5; i++){
         *((char *)(map + i * sizeof(int))) = rand() % (901);
     }
     return;
 }
 
 int main(int argc, char *argv[]){
     
     printf("Starting parent process .... \n");
     
     long page_size = sysconf(_SC_PAGESIZE);  // GENERALLY 4096
     
     void *shared_array = mmap(0, page_size, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, 0, 0);
     
     printf("Shared array memory created, starting from addr: <%p>\n", shared_array);
    
    // ways to access memory content, and modify it.
     *(int *)shared_array = 10;
     printf("val at addr: %d \n", *(int *)shared_array);
     *(int *)(shared_array + sizeof(int)) = 20;
     printf("val at addr: %d \n", *(int *)(shared_array + sizeof(int)));


    pid_t child = fork();
    
    if (child == 0){
        printf("Executing child process ... \n");
        child_process_worker(shared_array);
        printf("Executed child process ... \n");
    } else {
        printf("Back to parent process ... \n");
        waitpid(child, NULL, 0);
        int temp_arr[5] = {1, 2, 3, 4, 5};
        printf("initial array: \t");
        for (int i = 0; i < 5; i++){
         printf("%d \t", temp_arr[i]);
        }
        
        for (int i = 0; i < 5; i++){
         temp_arr[i] = *((char *)(shared_array + i * sizeof(int)));
        }
        printf("updated array: \t");
        for (int i = 0; i < 5; i++){
         printf("%d \t", temp_arr[i]);
        }
    }
     
    return 0;
}
 
