# simple_avl
The simple avl  tree template. 
![avl-tree with segments info in nodes](https://github.com/khlruslan/simple_avl/blob/main/search_avl_example.png?raw=true)

The code from [libavl](https://adtinfo.org/) is used to implement avl.

AVL-tree template used for :
- insert numbers in avl-tree
- processing requests for the number of elements in a numerical segment. Information about the range of values and the number of child elements in each node of the tree is used to quickly process requests for counting the number of elements in a numerical segment. The complexity estimate is O(log N).

For comparison, similar requests are processed via std::set. The complexity estimate is O(N). 
