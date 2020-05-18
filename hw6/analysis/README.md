* Test Cases
	* I tested my program on input sizes of combination of n=1000,3000 and m=1,3,5.
* Results
	* n = 1000, m = 1
		* AVL: 0.0220149 seconds
		* Splay: 0.0481536 seconds
	* n = 1000, m = 3
		* AVL: 0.0499457 seconds
		* Splay: 0.106233 seconds
	* n = 1000, m = 5
		* AVL: 0.049349 seconds
		* Splay: 0.104923 seconds
	* n = 3000, m = 1
		* AVL: 0.0594974 seconds
		* Splay: 0.143461 seconds
	* n = 3000, m = 3
		* AVL: 0.159917 seconds
		* Splay: 0.371075 seconds
	* n = 3000, m = 5
		* AVL: 0.159633 seconds
		* Splay: 0.377216 seconds
	* although both length of the string and number of strings affect the time it takes for the operation, the length of string m seems to have a bigger effect.
* Explanation
	* I think the results turned out the way it did because I was using rand() function to generate random strings which disadvatanges the splay tree since it is dependent on the 90/10 rule. Had the data been less random, I believe the splay tree would have done better. Also, even though the splay tree did worse than the AVL tree, it only did so by a constant factor
* Comparison
	* Unsorted Array
		* Unsorted array may be very inefficient and slow because while insertion may be fast, if you need to update, you can only do so in linear time
	* Sorted List
		* Sorted lists are better than unsorted arrays with updating, but still take longer than AVL or splay trees because inserting itself needs nlogn time
	* BST
		* BST's are better than unsorted arrays, but still may perform worse than AVL or splay trees since they may take a long time especially if the height gets too big
	* HashTable
		* Given the hash function is adequate enough so that the number of collision is minimal, hash tables would be faster than AVL or splay trees