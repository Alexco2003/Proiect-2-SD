# Proiect-2-SD
Fibonacci Heap

  Implementation of the Fibonacci Heap in C++ with all its associated operations. This implementation of the Fibonacci Heap can handle duplicates and negative integers within the limits of the integer data type. The minimum integer possible is -2147483648, but the minimum that can be inserted into the Fibonacci Heap is one greater than that, which is -2147483647 (This was done to ensure that the 'delete' operation works properly).

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

 Guide for the interactive menu : 
 
 ![Screenshot_6](https://user-images.githubusercontent.com/105515716/235469747-56f250b6-a446-474c-8990-037b921db85c.jpg)
 
 This is the main menu. Press '1' to work with Fibonacci Heap A, press '2' to create your own Fibonacci Heap, or press '3' to stop the program.
 
![Screenshot_5](https://user-images.githubusercontent.com/105515716/235469915-fe75f8b3-65d7-4ef8-9cb9-526194501448.jpg)

This is the second menu, which you can access by selecting option '1' or '2' from the main menu. Here, you can perform operations on the Fibonacci Heap and view your progress. To return to the main menu, press '10'.

Note that the 'mergeheap(infoarena).cpp' file serves as a test for the Fibonacci Heap data structure. It was designed to solve the problem presented in this link (mergeheap), using this implementation of the Fibonacci Heap : https://www.infoarena.ro/problema/mergeheap. If you're interested, you can check out the source code that obtained a perfect score of 100 points out of 100 here : https://www.infoarena.ro/job_detail/3125141. 

![image](https://user-images.githubusercontent.com/105515716/235594584-af75355d-fc35-4f41-a00e-de5964031582.png)

 
