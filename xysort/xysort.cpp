#include <bits/stdc++.h>
#include <cstdlib>


using namespace std;
#define vi vector<int>

void xysort(vi &a, vi &b){
	int s= 0,ts=s;
	int cur_i = 0, tci, ttci;
	vi p;
	int x = 0;

	vi ind(a.size(), 0);
	while(ind[a.size()-1] != int(b.size()-1)){
		tci = ts;
		ttci =(cur_i+1) % a.size();
		if(x++ < 5)
			cout << " Fucking tci " << tci << " ttci " << ttci << endl; 


		if(tci == ttci){
			if(x++ < 10)
				cout << "Continued "<< endl;
			continue;
		}
		if(ind[ts]==int(b.size()))
			ts++;

		
		if(x++ < 5)
			// cout << "++ " << tci << " " << ttci << " " << ind[tci] << " " << ind[ttci] << " ++" << endl;
		while((b[ind[tci]] + a[tci]) <= (b[ind[ttci]] + a[ttci])){
			
		cout << "a["<<tci<<"] = "<< a[tci] << " ind["<<tci<<"] = " << ind[tci] << " is compared with "<<"b["<<ttci<<"] = " << b[ttci] << " ind["<<ttci<<"] = " << ind[ttci] << endl; 
			cout << "Pushed " << b[ind[tci]] + a[tci] << endl; //" " << b[ind[ttci]] + a[ttci] << endl;
			p.push_back(b[ind[tci]] + a[tci]);
			ind[tci]++;

			// cout << tci << " " << ttci << " " << ind[tci] << " " << ind[ttci] << endl;
			if(ind[tci]==int(b.size())){
				// cout << " fuck "<< endl;
				cout << "a[" << tci << "] checking finished as ind[" <<tci << "] = " << ind[tci] << endl; 
				ts = ++s;
				x = 0;
				break;
			}
		}
		cur_i++;
	}

	for(auto i:p){
		cout << i << " ";
	}
	cout << endl;
}

int main(){
	cout << "Enter number of elements of first set:";
	int n;
	cin >> n;
	vi a(n);
	cout << "Enter the numbers" << endl;

	for(auto &i:a){
		cin >> i;
	}

	cout << "Enter number of elements of second set:";
	int m;
	cin >> m;

	vi b(m);
	cout << "Enter the numbers" << endl;

	for(auto &i:b){
		cin >> i;
	}

	// this is straight forward implementation

	vi t1 = a;
	vi t2 = b;
	vi t3;
	for(auto i:a){
		for(auto j:b){
			t3.push_back(i+j);
		}
	}

	sort(t3.begin(),t3.end());

	cout << "In O(nmlog(nm)) :" << endl;
	for(auto i:t3){
		cout << i << " ";
	}
	cout << endl;

	// this is O(n^2) implementation
	sort(a.begin(), a.end());
	sort(b.begin(), b.end());

	cout << "A set :" << endl;
	for(auto i:a){
		cout << i << " ";
	}
	cout << endl << "B set :" << endl;
	for(auto i:b){
		cout << i << " ";
	}
	cout << endl;
	xysort(a, b);
	return EXIT_SUCCESS;
}