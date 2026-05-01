#pragma once
#include <vector>

class Heap {
private:
	struct Node {
		int value;
		int priority;
	};

	std::vector<Node> heap;

	int parent(int index) const { return (index - 1) / 2; }
	int leftChild(int index) const { return 2 * index + 1; }
	int rightChild(int index) const { return 2 * index + 2; }

	void heapifyUp(int index);
	void heapifyDown(int index);

public:
	void insert(int value, int priority);
	void extract_max();
	void peek() const;
	void modify_priority(int value, int new_priority);
	void return_size() const;
};