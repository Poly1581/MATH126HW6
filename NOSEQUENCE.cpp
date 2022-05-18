#include <stack>
#include <vector>
#include <utility>
#include <iostream>
#include <algorithm>

using namespace std;
using pvi = pair<vector<int>,vector<int>>;

vector<int> LIS(const vector<int>& sequence) {
	vector<int> LISsequence(sequence.size(),1);
	for(int c = 0; c < sequence.size(); c++) {
		for(int p = 0; p < c; p++) {
			if(sequence.at(c) > sequence.at(p)) {
				LISsequence.at(c) = max(LISsequence.at(c), LISsequence.at(p)+1);
			}
		}
	}
	return LISsequence;
}

int maxLIS(const vector<int>& sequence) {
	vector<int> LISsequence = LIS(sequence);
	int maxL = 0;
	for(int i = 0; i < LISsequence.size(); i++) {
		maxL = max(maxL,LISsequence.at(i));
	}
	return maxL;
}

vector<int> LDS(const vector<int>& sequence) {
	vector<int> LDSsequence(sequence.size(),1);
	for(int c = 0; c < sequence.size(); c++) {
		for(int p = 0; p < c; p++) {
			if(sequence.at(c) < sequence.at(p)) {
				LDSsequence.at(c) = max(LDSsequence.at(c), LDSsequence.at(p)+1);
			}
		}
	}
	return LDSsequence;
}

int maxLDS(const vector<int>& sequence) {
	vector<int> LDSsequence = LDS(sequence);
	int maxD = 0;
	for(int i = 0; i < LDSsequence.size(); i++) {
		maxD = max(maxD,LDSsequence.at(i));
	}
	return maxD;
}

pvi remove(stack<pvi>& S) {
	pvi value = S.top();
	S.pop();
	return value;
}

int main() {
	vector<int> choices = {1,2,3,4,5,6,7,8,9};
	vector<int> curr;
	stack<pvi> S;
	pvi state(choices,curr);
	S.push(state);
	bool found = false;
	while(S.size() != 0 && !found) {
		state = remove(S);
		choices = state.first;
		curr = state.second;
		if(choices.size() == 0) {	//				LEAF NODE IN TREE
			found = (maxLIS(curr) < 4)&&(maxLDS(curr) < 4);
		} else {				//				INTERNAL NODE IN TREE
			for(int i = 0; i < choices.size(); i++) {
				vector<int> newcurr = curr;
				newcurr.push_back(choices.at(i));
				vector<int> newchoices = choices;
				newchoices.at(i) = newchoices.back();
				newchoices.resize(newchoices.size()-1);
				pvi newstate(newchoices,newcurr);
				S.push(newstate);
			}
		}
	}
	cout << "ARRANGEMENT FOUND" << endl;
	for(int i = 0; i < curr.size(); i++) {
		cout << curr.at(i) << " ";
	}
	cout << endl;
	cout << "LONGEST INCRESING SUBSEQUENCE:" << endl;
	vector<int> LISsequence = LIS(curr);
	for(int i = 0; i < LISsequence.size(); i++) {
		cout << LISsequence.at(i) << " ";
	}
	cout << endl;
	cout << "LONGEST DECREASING SUBSEQUENCE:" << endl;
	vector<int> LDSsequence = LDS(curr);
	for(int i = 0; i < LDSsequence.size(); i++) {
		cout << LDSsequence.at(i) << " ";
	}
	cout << endl;
}