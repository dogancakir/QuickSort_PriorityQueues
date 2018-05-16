In this project, we sort the final notes of M applicants. And we select best N applicants for interview. When project is being done, there must be some operations to apply, INSERT, UPDATE and REMOVE. Before explanation of functions, there is a class called “heap”.This class holds the notes and ID of applicants. In main function there is a list of “heap” called “queue”. “queue” is sorted. There is one more “heap” list called “scores” in main. “scores” isn’t sorted, it is the first shape of heap.  
 
In INSERT function, new element is read from file and added to “scores” heap. 
 
In UPDATE function, size of heap is controlled as first step. If heap is not NULL, an element is chosen using random number and updated via adding 0-10 points to final score or substracting 0-10 points from final scores. 
 
In REMOVE function, the final score of chosen element updated as 0 and MAX_HEAPIFY operation for chosen element is applied and size of heap is decreased with 1. After MAX_HEAPIFY operation the smallest number is the last element of heap list, After decrase operation chosen element has been removed. 