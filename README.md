# Proiect-2-SD
Fibonacci Heap

  Implementation of the Fibonacci Heap in C++ with all its associated operations.

  A Fibonacci Heap is a data structure used to implement a priority queue that provides a better amortized runtime complexity compared to other priority queue data structures such as binary heaps or binomial heaps. The Fibonacci Heap was first introduced by Michael L. Fredman and Robert E. Tarjan in 1984. It has the same functionality as a binary heap or a binomial heap but with better amortized performance for certain operations.

  The Fibonacci Heap is a collection of trees with a set of properties. It has a minimum-heap property that states that each node is greater or equal than its parent node, and each child node is greater or equal than it's parent node. Additionally, it has a specific structural property that is the key to its improved performance: it is a collection of trees that obey a Fibonacci sequence.
  
  <img width="661" alt="fibonacci-heap-structure" src="https://user-images.githubusercontent.com/105515716/235310682-39e739d8-5d03-4875-afbf-119cb1abd790.png">

 The Fibonacci Heap supports several operations, including:

-> Insertion: This operation inserts a new element into the heap in O(1) time complexity.

-> Find minimum: This operation returns the element with the minimum key in the heap in O(1) time complexity.

-> Merge: This operation merges two Fibonacci Heaps in O(1) time complexity.

-> Decrease key: This operation decreases the key of a node in the heap in O(1) amortized time complexity.

-> Delete: This operation removes a specific node from the heap in O(log n) amortized time complexity.

-> Extract minimum: This operation removes and returns the element with the minimum key in the heap in O(log n) amortized time complexity.

  The Fibonacci Heap has a better amortized performance compared to other priority queue data structures such as binary heaps or binomial heaps for certain operations such as decrease key and extract minimum. However, it has a higher constant factor in its running time, making it less efficient for small input sizes.
  
  ![image](https://user-images.githubusercontent.com/105515716/234973491-ef62f24d-c20f-43c1-814d-e44ed8494a78.png)
  
  For testing purposes, this implementation includes an interactive menu. Additionally, it has two Fibonacci Heaps (let's call them Fibonacci Heap A and Fibonacci Heap B) stored in memory, which look like this:
  
  Fibonacci Heap A :
  
  ![fibonacci-heap2 (1)](https://user-images.githubusercontent.com/105515716/235310825-12684ac3-aaad-48e6-90e5-d0f9b99234c9.png)


  Fibonacci Heap B : 
  
  ![Screenshot_1](https://user-images.githubusercontent.com/105515716/235310849-0e15a383-dcbe-49ba-a224-5857143235d3.jpg)


  Using the interactive menu, we can test all the operations on the Fibonacci Heap A, including a one time use only Merge operation that merges Fibonacci Heap A with Fibonacci Heap B. To be more precise, Fibonacci Heap A is the Fibonacci Heap we will be working on, and Fibonacci Heap B is just to test the Merge operation. It also lets you create your own Fibonacci Heap from scratch. You can use all the operations as well on your Fibonacci Heap, having again a one time use only Merge operation with Fibonacci Heap B.
