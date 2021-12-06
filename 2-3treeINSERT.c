A function to implement the insert operation in 2-3 Tree
void insert(node *candidate, t *key) { //Here key is the element to be inserted in the candidate
	if(candidate == nullptr) {
		root = new node(key);
		return;
	}
	if(candidate->isleaf()) {
		candidate->store(key);
	}else {
		if(*candidate->firstkey > *key) {
			insert(candidate->less, key); //Insert to left subtree.
		}else if(*candidate->firstkey <= *key && candidate->is2node()) {
			insert(candidate->btwn, key); //Insert to mid subtree.
		}else {
			if(*candidate->secondkey > *key) {
				insert(candidate->btwn, key); //Insert to mid subtree.
			}else {
				insert(candidate->great, key); //Insert to right subtree.
			}
		}
	}
	split(candidate); //This function is to balance the tree incase of an overflow.	
}
