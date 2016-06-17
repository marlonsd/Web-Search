#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <algorithm>
#include <deque>

using namespace std;

struct Ranking{
	unsigned int id;
	double rank;
};

struct rank_comp {
	bool operator()(Ranking A, Ranking B) {
		return (A.rank > B.rank);
	}
};

class PriorityQueue{

private:
	vector<Ranking> list;

public:
	PriorityQueue();
	~PriorityQueue();
	
	void push(Ranking url);
	Ranking pop();

	int size();
	bool empty();
	
	Ranking getFromVector(int i);
	Ranking popFromVector();
	void clear();

};

#endif