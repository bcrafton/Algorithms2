Brian Crafton and Oliver Scott HW 2b

--------------------------
SORT TIMES
--------------------------
quick sort time: 0.27
heap sort time: 0.461
merge sort time: 1.092
insertion sort time: 515.288
--------------------------
SEARCH TIMES
--------------------------
input15: 0.2
input30: 0.8
input50: 2.252
input250: 56.999
--------------------------
SEARCH TIMES w/ Hashtable
--------------------------
input15: 0.142
input30: 0.563
input50: 1.586
input250: 39.423

Relative to the performance of the other searching algorithms, heap sort is the most thoeretically ideal candidate for this assignment. 
This is because it shares the average performance of O(nlogn) as merge sort and quicksort. It doesn't require any additional space,
making it preferable to merge sort, and does not have a 'worst-case' scenario like quick sort, making it the more dependable alternative.

Mergesort has O(nlogn) efficiency but it requires extra space.
Quicksort has average O(nlogn) efficiency but it has a worse case scenario of O(n^2)
Insertion sort has an effieciency of O(n^2) but it can perform better than the other algorithms at smaller values of n
