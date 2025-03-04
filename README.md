# simple_avl
The simple avl  tree template. 
![avl-tree with segments info in nodes](https://github.com/khlruslan/simple_avl/blob/main/search_avl_example.png?raw=true)

The code from [libavl](https://adtinfo.org/) is used to implement avl.

AVL-tree template used for :
- insert numbers in avl-tree
- processing requests for the number of elements in a numerical segment. Information about the range of values and the number of child elements in each node of the tree is used to quickly process requests for counting the number of elements in a numerical segment. The complexity estimate is O(log N).

Requests:
- k number . Insert one key.
- q number1 number2 . Get number of elements in a numerical segment \[number1, number2\]


<p>For comparison, similar requests are processed via std::set. The complexity estimate is O(N). 
</p>
<p> Example:
</p>
<p>
 k 10 k 20 q 8 31 q 6 9 k 30 k 40 q 15 40
</p>
<p> Answer:
</p>
<p>
 2 0 3
</p>

Useful functions:
- iterator
- post/pre - increment/decrement for iterator
- lower_bound
- upper_bound
  
