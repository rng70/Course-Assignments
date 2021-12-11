#include <bits/stdc++.h>

using namespace std;

class State;

struct compare{
public:
    bool operator() (auto a, auto b){
        return a.first > b.first;
    }
};

class StarSearch{
public:
    void expand(auto state){
        state->expand1(state, 1, "Manhattan:");
//        cout << state.getManhattanCost() << endl;
        state->expand1(state, 2, "Hamming:");
        state->expand1(state, 3, "Linear Conflict:");
        cout << "Search complete" << endl;
    }

    void search(auto state){
        cout << "Here is a* search" << endl;
        expand(state);
    }
};

class State{
    int node;
    int depth;
    State* parent;
    vector<vector<int>> board;
    vector<vector<int>> goal;

    auto getIndex(auto grid, int key){

        for(int i=0;i<node;i++){
            for(auto j=0;j<node;j++){
                if(grid[i][j]==key){
                    return make_pair(i, j);
                }
            }
        }

        return make_pair(0, 0);
    }

    auto getLineGrid(){
        vector<int>lineGrid;

        for(int i=0;i<node;i++){
            for(int j=0;j<node;j++){
                lineGrid.push_back(board[i][j]);
            }
        }

        return lineGrid;
    }

    auto getInverseCount(){
        int inv_count = 0;
        vector<int>lineGrid = getLineGrid();

        for(int i=0;i<node*node-1; i++){
            for(int j=i+1;j<node*node; j++){
                if(lineGrid[i] && lineGrid[j] && (lineGrid[i] > lineGrid[j])){
                    inv_count++;
                }
            }
        }

        return inv_count;
    }

    auto emptyTilePosition(){
        for(auto i=node-1;i>=0;i--){
            for(auto j=node-1;j>=0;j--){
                if(!board[i][j]){
                    return node - i;
                }
            }
        }
        return 0;
    }

    auto generateGoalState(){
        int count = 1;
        for(auto i=0;i<node;i++){
            vector<int> a;
            for(auto j=0;j<node;j++){
                if(count == node*node)
                    a.push_back(0);
                else
                    a.push_back(count++);
            }
            this->goal.push_back(a);
        }
    }

    auto printGrid(auto grid, auto s){
        cout << s << endl;
        for(auto p: grid){
            for(auto i: p){
                cout << i << " ";
            }
            cout << endl;
        }
    }

    auto printGrid(auto grid){
        for(auto p: grid){
            for(auto i: p){
                cout << i << " ";
            }
            cout << endl;
        }
    }

public:
    State(auto node, auto depth, State* parent, auto board){
        this->node = node;
        this->depth = depth;
        this->board = board;
        this->parent = parent;
        generateGoalState();
//        printGrid(this->goal, "Final Grid");
    }

    auto getManhattanCost(){
        auto cost = 0;

        for(auto i=0;i<node;i++){
            for(auto j=0; j<node; j++){
                if(board[i][j]!=0){
                    auto index = getIndex(this->goal, board[i][j]);
                    cost += (abs(index.first - i) + abs(index.second - j));
                }
            }
        }

        return cost;
    }

    int getDepth(){
        return this->depth;
    }

    int getNode(){
        return this->node;
    }

    auto getParent(){
        return this->parent;
    }

    auto getBoard(){
        return this->board;
    }

    auto setBoard(auto _p){
        this->board = _p;
    }

    auto swap(auto s, int x1, int y1, int x2, int y2){
        State* b = new State(s->getNode(), s->getDepth()+1, s, s->getBoard());

        auto curBoard = b->getBoard();
        int _p = curBoard[x1][y1];
        curBoard[x1][y1] = curBoard[x2][y2];
        curBoard[x2][y2] = _p;

        b->setBoard(curBoard);
        return b;
    }

    auto getHammingCost(){
        int cost=0;

        for(int i=0;i<node;i++){
            for(auto j=0;j<node;j++){
                if(board[i][j] != goal[i][j])
                    cost++;
            }
        }

        return cost;
    }

    auto isThisRow(int i, int p){
        int maxVal = (i+1)*node;
        int minVal = i*node + 1;

        if(p>= minVal && p<=maxVal)
            return true;
        return false;
    }

    auto getLinearConflictCost(){
        int cost = 0;

        for(int i=0;i<node;i++){
            for(int j=0;j<node-1;j++){
                for(int k=j+1;k<node;k++){
                    int x1 = board[i][j];
                    int x2 = board[i][k];
                    if(isThisRow(i, k) && isThisRow(i, k) && (x1>x2)){
                        cost++;
                    }
                }
            }
        }

        return cost;
    }

    auto getCost(auto p){
        if(p==1){
            return getManhattanCost()+getDepth();
        }else if(p==2){
            return getHammingCost()+getDepth();
        }else{
            return getManhattanCost()+2*getLinearConflictCost();
        }
    }

    void print(auto s, auto p){
        vector<vector<vector<int>>>listOfBoard;
        listOfBoard.push_back(p);

        while(s != 0){
            listOfBoard.push_back((*s).getBoard());
            s = (*s).getParent();
        }

        reverse(listOfBoard.begin(), listOfBoard.end());

        cout << " <-- -------------------------------- -->" << endl;
        for(auto x: listOfBoard){
            for(auto p: x){
                for(auto i: p){
                    cout << i << " ";
                }
                cout << endl;
            }
            cout << " <-- -------------------------------- -->" << endl;
        }
    }

    bool equals(auto a, auto b){
        for(int i=0;i<node;i++){
            for(int j=0;j<node;j++){
                if(a[i][j] != b[i][j]){
                    return false;
                }
            }
        }
        return true;
    }

    int expand1(auto state, int key, string str){
        priority_queue<pair<int, State*>, vector<pair<int, State*> >, compare> subState;
        set<vector<vector<int>>>closeList;
        subState.push(make_pair(state->getCost(key), state));

        int expand=1, explored=1;

        while(!subState.empty()){
            expand++;
            pair<int, State*> p = subState.top();
            auto childState = subState.top().second;
            subState.pop();

//            cout << "Current Cost: " << childState.getManhattanCost() << endl;
//            cout << "Current Depth: " << childState.getDepth() << endl;
//            print(childState);
//            cout << " ----------------------- " << endl;

            if(equals(childState->getBoard(), childState->goal)){
                cout << str << endl;
                cout << "Explored: " << explored << endl;
                cout << "Expanded: " << expand << endl;
                cout << "Solution depth: " << childState->getDepth() << endl;
                print(childState->getParent(), childState->getBoard());
                break;
            }

            auto emptyTile = getIndex(childState->getBoard(), 0);
            if(closeList.find(childState->getBoard())!=closeList.end()){
//                cout << "Already is in close list" << endl;
            }else{
                closeList.insert(childState->getBoard());
                if(emptyTile.first>0){
//                cout << "Here ----------------------------------------------> Tanin" << endl;
                    auto child = swap(childState, emptyTile.first, emptyTile.second, emptyTile.first-1, emptyTile.second);
//                cout << child.getCost(1) << endl;
                    subState.push(make_pair(child->getCost(key), child));
                    explored++;
//                print(child);
                }
                if(emptyTile.first<(node-1)){
//                cout << "Here ---------------------------------------------->" << endl;
                    auto child = swap(childState, emptyTile.first, emptyTile.second, emptyTile.first+1, emptyTile.second);
                    subState.push(make_pair(child->getCost(key), child));
                    explored++;
//                cout << child.getCost(1) << endl;
//                print(child);
                }
                if(emptyTile.second<(node-1)){
//                cout << "Here ----------------------------------------------> Arafat" << endl;
                    auto child = swap(childState, emptyTile.first, emptyTile.second, emptyTile.first, emptyTile.second+1);
                    subState.push(make_pair(child->getCost(key), child));
                    explored++;
//                cout << child.getCost(1) << endl;
//                print(child);
                }
                if(emptyTile.second>0){
//                cout << "Here ----------------------------------------------> Al" << endl;
                    auto child = swap(childState, emptyTile.first, emptyTile.second, emptyTile.first, emptyTile.second-1);
                    subState.push(make_pair(child->getCost(key), child));
                    explored++;
//                cout << child.getCost(1) << endl;
//                print(child);
                }
            }

//            return subState.top().second;
        }
        return 0;
    }

//    int expand(auto state, int key){
//        priority_queue<pair<int, State>, vector<pair<int, State> >, compare> subState;
//
//        subState.push(make_pair(state.getCost(1), state));
//
//        int expand=1, explored=1;
//
//        while(!subState.empty()){
//            expand++;
//            pair<int, State> p = subState.top();
//            auto childState = subState.top().second;
//            subState.pop();
//
//            cout << "Current Cost: " << childState.getManhattanCost() << endl;
//            cout << "Current Depth: " << childState.getDepth() << endl;
////            print(childState);
//            cout << " ----------------------- " << endl;
//
//            if(equals(childState.getBoard(), childState.goal)){
//                cout << "Manhattan:" << endl;
//                cout << "Explored: " << explored << endl;
//                cout << "Expanded: " << expand << endl;
//                print(childState);
//                return 0;
//            }
//
//            auto emptyTile = getIndex(childState.getBoard(), 0);
//            if(emptyTile.first>0){
////                cout << "Here ----------------------------------------------> Tanin" << endl;
//                auto child = swap(childState, emptyTile.first, emptyTile.second, emptyTile.first-1, emptyTile.second);
////                cout << child.getCost(1) << endl;
//                subState.push(make_pair(child.getCost(key), child));
//                explored++;
////                print(child);
//            }
//            if(emptyTile.first<(node-1)){
////                cout << "Here ---------------------------------------------->" << endl;
//                auto child = swap(childState, emptyTile.first, emptyTile.second, emptyTile.first+1, emptyTile.second);
//                subState.push(make_pair(child.getCost(key), child));
//                explored++;
////                cout << child.getCost(1) << endl;
////                print(child);
//            }
//            if(emptyTile.second<(node-1)){
////                cout << "Here ----------------------------------------------> Arafat" << endl;
//                auto child = swap(childState, emptyTile.first, emptyTile.second, emptyTile.first, emptyTile.second+1);
//                subState.push(make_pair(child.getCost(key), child));
//                explored++;
////                cout << child.getCost(1) << endl;
////                print(child);
//            }
//            if(emptyTile.second>0){
////                cout << "Here ----------------------------------------------> Al" << endl;
//                auto child = swap(childState, emptyTile.first, emptyTile.second, emptyTile.first, emptyTile.second-1);
//                subState.push(make_pair(child.getCost(key), child));
//                explored++;
////                cout << child.getCost(1) << endl;
////                print(child);
//            }
//
////            return subState.top().second;
//        }
//        return 0;
//    }

    auto isTheBoardSolvable(){
        auto invCount = getInverseCount();

        if(node & 1){
            return !(invCount & 1);
        }else{
            auto pos = emptyTilePosition();
            if(pos & 1)
                return !(invCount & 1);
            else
                return !(!(invCount & 1));
        }
    }
};

void solve(auto board, int k){
    auto state = new State(k, 0, nullptr, board);

    if(state->isTheBoardSolvable()){
        cout << "Solvable" << endl;
        StarSearch starSearch;
        starSearch.search(state);
    }else{
        cout << "Not solvable" << endl;
    }
}

auto convertToBoard(auto arr, int n){
    auto counter = 0;
    vector<vector<int>>board;

    for(int i=0;i<n;i++){
        vector<int>a;

        for(int j=0;j<n;j++){
            a.push_back(arr[counter++]);
        }

        board.push_back(a);
    }

    return board;
}

auto stringToInteger(const string& val){
    int n;

    stringstream strToInt(val);
    strToInt >> n;

    return n;
}

void input(){
    int k, t;
    string s;

    cout << "Enter Grid" << endl;

    cin >> k;
    t = k;
    k *= k;
    vector<int>arr;
    while(k--){
        cin >> s;
        if(s=="*" || s=="0"){
            s="0";
        }
        arr.push_back(stringToInteger(s));
    }

    solve(convertToBoard(arr, t), t);
}

int main() {
//    freopen("output.txt", "a", stdout);
    input();
    return 0;
}
