#include "PriorityQueue.h"

// Constructors
PriorityQueue::PriorityQueue(){
}

// Destructor
PriorityQueue::~PriorityQueue(){
}

void PriorityQueue::push(Ranking item){
	this->list.push_back(item);
	push_heap(this->list.begin(), this->list.end(), rank_comp());
}

// In case queue is empty, returns an empty Ranking
Ranking PriorityQueue::pop(){
	Ranking item;

	item.id = 0;
	item.rank = -1;

	if (!this->list.empty()){
		item = this->list.front();

		pop_heap(this->list.begin(), this->list.end(), rank_comp());

		this->list.pop_back();
	}

	return item;
}

int PriorityQueue::size(){
	return this->list.size();
}

bool PriorityQueue::empty(){
	return this->list.empty();
}

// In case i isn't in queue, returns empty Ranking
Ranking PriorityQueue::getFromVector(int i){
	Ranking item;

	item.id = 0;
	item.rank = -1;

	if (this->list.size() >= i){
		item = this->list[i];
	}

	return item;
}

// Returns first element in vector
Ranking PriorityQueue::popFromVector(){
	Ranking item;

	item.id = 0;
	item.rank = -1;

	if (!this->list.empty()){
		item = this->list.front();
		this->list.erase(this->list.cbegin());
	}

	return item;
}

// Remove all elements
void PriorityQueue::clear(){
	this->list.clear();
	this->list.shrink_to_fit();
}