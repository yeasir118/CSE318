#include <bits/stdc++.h>
using namespace std;

class SearchNode {
int** board;
int** goal_board;
int k;
int blank_row, blank_col;
int moves_made;
SearchNode* prev;
public:
    // constructor
    SearchNode(int grid_size){
        this->k = grid_size;
        this->board = new int*[k];
        for(int i=0;i<k;i++){
            board[i] = new int[k];
        }

        for(int i=0;i<k;i++){
            for(int j=0;j<k;j++){
                cout<<"Board Position ("<<i<<" "<<j<<") (Enter 0 for empty cell): ";
                cin>>board[i][j];
                if(board[i][j] == 0){
                    blank_row = i;
                    blank_col = j;
                }
            }
        }

        goal_board = new int*[k];
        for(int i=0;i<k;i++){
            goal_board[i] = new int[k];
            for(int j=0;j<k;j++){
                goal_board[i][j] = i*k+j+1;
            }
        }
        goal_board[k-1][k-1] = 0;

        moves_made = 0;
        prev = NULL;
    }

    SearchNode(int** board, int k, int blank_row, int blank_col, int moves_made){
        this->board = new int*[k];
        for(int i=0;i<k;i++){
            this->board[i] = new int[k];
            for(int j=0;j<k;j++){
                this->board[i][j] = board[i][j];
            }
        }
        this->k = k;
        this->blank_row = blank_row;
        this->blank_col = blank_col;
        this->moves_made = moves_made;
        this->prev = NULL;

        goal_board = new int*[k];
        for(int i=0;i<k;i++){
            goal_board[i] = new int[k];
            for(int j=0;j<k;j++){
                goal_board[i][j] = i*k+j+1;
            }
        }
        goal_board[k-1][k-1] = 0;
    }

    SearchNode(const SearchNode& node){
        this->k = node.k;
        this->blank_row = node.blank_row;
        this->blank_col = node.blank_col;
        this->moves_made = node.moves_made;

        this->board = new int*[k];
        for(int i=0;i<k;i++){
            this->board[i] = new int[k];
            for(int j=0;j<k;j++){
                this->board[i][j] = node.board[i][j];
            }
        }
        this->prev = node.prev;

        this->goal_board = new int*[k];
        for(int i=0;i<k;i++){
            this->goal_board[i] = new int[k];
            for(int j=0;j<k;j++){
                this->goal_board[i][j] = node.goal_board[i][j];
            }
        }
    }

    // assignment operator
    SearchNode& operator=(const SearchNode& node){
        if(this != &node){
            for(int i=0;i<k;i++){
                delete[] board[i];
                delete[] goal_board[i];
            }
            delete[] board;
            delete[] goal_board;

            this->k = node.k;
            this->blank_row = node.blank_row;
            this->blank_col = node.blank_col;
            this->moves_made = node.moves_made;

            this->board = new int*[k];
            for(int i=0;i<k;i++){
                this->board[i] = new int[k];
                for(int j=0;j<k;j++){
                    this->board[i][j] = node.board[i][j];
                }
            }
            this->prev = node.prev;

            this->goal_board = new int*[k];
            for(int i=0;i<k;i++){
                this->goal_board[i] = new int[k];
                for(int j=0;j<k;j++){
                    this->goal_board[i][j] = node.goal_board[i][j];
                }
            }
        }
        return *this;
    }

    int** get_board(){
        return board;
    }

    int** get_goal_board(){
        return goal_board;
    }

    int get_k(){
        return k;
    }

    int get_blank_row(){
        return blank_row;
    }

    int get_blank_col(){
        return blank_col;
    }

    int get_moves_made(){
        return moves_made;
    }

    SearchNode* get_prev(){
        return prev;
    }

    void set_board(int** board){
        for(int i=0;i<k;i++){
            for(int j=0;j<k;j++){
                this->board[i][j] = board[i][j];
            }
        }
    }

    void set_goal_board(int** board){
        for(int i=0;i<k;i++){
            for(int j=0;j<k;j++){
                this->goal_board[i][j] = board[i][j];
            }
        }
    }

    void set_k(int k){
        this->k = k;
    }

    void set_blank_row(int blank_row){
        this->blank_row = blank_row;
    }

    void set_blank_col(int blank_col){
        this->blank_col = blank_col;
    }

    void set_moves_made(int moves_made){
        this->moves_made = moves_made;
    }

    void set_prev(SearchNode* prev){
        this->prev = prev;
    }

    void printBoard(){
        cout<<endl<<"Board: "<<endl;
        for(int i=0;i<k;i++){
            cout<<"\t";
            for(int j=0;j<k;j++){
                cout<<board[i][j]<<" ";
            }
        cout<<endl;
        }
    }

    void printGoalBoard(){
        cout<<endl<<"Goal Board: "<<endl;
        for(int i=0;i<k;i++){
            cout<<"\t";
            for(int j=0;j<k;j++){
                cout<<goal_board[i][j]<<" ";
            }
        cout<<endl;
        }
    }

    // function to calculate hamming distance. used in comparator of priority queue
    int hamming_distance(){
        int hamming_distance = 0;
        for(int i=0;i<k;i++){
            for(int j=0;j<k;j++){
                if((board[i][j] != 0) && (board[i][j] != i*k+j+1)){
                    hamming_distance++;
                }
            }
        }
        return hamming_distance;
    }

    // function to calculate manhattan distance. used in comparator of priority queue
    int manhattan_distance(){
        int manhattan_distance = 0;
        for(int i=0;i<k;i++){
            for(int j=0;j<k;j++){
                if(board[i][j] != 0){
                    int digit_row = (board[i][j]-1)/k;
                    int digit_col = (board[i][j]-1)%k;
                    manhattan_distance += abs(digit_row-i) + abs(digit_col-j);
                }
            }
        }
        return manhattan_distance;
    }

    // moves for generating neighbors
    SearchNode* move_left(){
        if(blank_col > 0){
            SearchNode* neighbor_node = new SearchNode(*this);
            swap(neighbor_node->board[blank_row][blank_col], neighbor_node->board[blank_row][blank_col-1]);
            neighbor_node->blank_col--;
            neighbor_node->moves_made++;
            return neighbor_node;
        }
        return NULL;
    }

    SearchNode* move_up(){
        if(blank_row > 0){
            SearchNode* neighbor_node = new SearchNode(*this);
            swap(neighbor_node->board[blank_row][blank_col], neighbor_node->board[blank_row-1][blank_col]);
            neighbor_node->blank_row--;
            neighbor_node->moves_made++;
            return neighbor_node;
        }
        return NULL;
    }

    SearchNode* move_right(){
        if(blank_col < k-1){
            SearchNode* neighbor_node = new SearchNode(*this);
            swap(neighbor_node->board[blank_row][blank_col], neighbor_node->board[blank_row][blank_col+1]);
            neighbor_node->blank_col++;
            neighbor_node->moves_made++;
            return neighbor_node;
        }
        return NULL;
    }

    SearchNode* move_down(){
        if(blank_row < k-1){
            SearchNode* neighbor_node = new SearchNode(*this);
            swap(neighbor_node->board[blank_row][blank_col], neighbor_node->board[blank_row+1][blank_col]);
            neighbor_node->blank_row++;
            neighbor_node->moves_made++;
            return neighbor_node;
        }
        return NULL;
    }

    // checking if goal state
    bool is_goal(){
        for(int i=0;i<k;i++){
            for(int j=0;j<k;j++){
                if(board[i][j] != goal_board[i][j]){
                    return false;
                }
            }
        }
        return true;
    }

    ~SearchNode(){
        for(int i=0;i<k;i++){
            delete[] board[i];
            delete[] goal_board[i];
        }
        delete[] board;
        delete[] goal_board;
        board = NULL;
        goal_board = NULL;
    }
};

// function pointer using typedef to choose heuristics from hamming and manhattan
typedef int (SearchNode::*HeuristicFunction)();

// priority_queue takes in class or struct as comparator and not function
// known as functor
struct CompareHeuristic {
    // function pointer(variable of the CompareHeuristic struct)
    HeuristicFunction heuristic;
    // constructor
    CompareHeuristic(HeuristicFunction h) {
        this->heuristic = h;
    }

    // required by priority_queue to overload "()" operator
    bool operator()(SearchNode* node1, SearchNode* node2) {
        return ((node1->*heuristic)() + node1->get_moves_made()) > ((node2->*heuristic)() + node2->get_moves_made());
    }
};

// function for generating string version of game state(board)
// easier to work with when storing in set(closed list)
string board_to_string(int** board, int k){
    string board_string = "";
    for(int i=0;i<k;i++){
        for(int j=0;j<k;j++){
            board_string += to_string(board[i][j]) + ",";
        }
    }
    return board_string;
}

// function to count inversion
int count_inversion(int** board, int k){
    // preparing 1D array because calculating inversion is easier this way
    int one_d_arr[k*k];
    for(int i=0;i<k;i++){
        for(int j=0;j<k;j++){
            one_d_arr[i*k+j] = board[i][j];
        }
    }

    int inversion_count = 0;
    for(int i=0;i<k*k-1;i++){
        for(int j=i+1;j<k*k;j++){
            if(one_d_arr[i] != 0 && one_d_arr[j] != 0 && one_d_arr[i] > one_d_arr[j]){
                inversion_count++;
            }
        }
    }
    return inversion_count;
}

// function implementing the algorithm
void AStarSearch(SearchNode* initial_node, HeuristicFunction heuristic, bool hamming){
    CompareHeuristic compare(heuristic);
    priority_queue<SearchNode*, vector<SearchNode*>, CompareHeuristic> open_list(compare);

    set<string> closed_list;
    vector<SearchNode*> all_nodes;  // stores all the nodes used in the algorithm. makes it easier to delete them at the end

    open_list.push(initial_node);
    all_nodes.push_back(initial_node);

    int explored_nodes = 0, expanded_nodes = 0;

    while(!open_list.empty()){

        SearchNode* current_node = open_list.top();
        open_list.pop();
        explored_nodes++;

        if(current_node->is_goal()){
            if(hamming) cout<<endl<<"\tHamming Distance Heuristics"<<endl;
            else cout<<endl<<"\tManhattan Distance Heuristics"<<endl;
            cout<<"Goal State Reached!"<<endl;
            cout<<"Moves Made: "<<current_node->get_moves_made()<<endl;
            cout<<"Path: "<<endl<<endl;
            while(current_node != NULL){
                current_node->printBoard();
                current_node = current_node->get_prev();
            }
            break;
        }

        closed_list.insert(board_to_string(current_node->get_board(), current_node->get_k()));

        int blank_row = current_node->get_blank_row();
        int blank_col = current_node->get_blank_col();

        vector<SearchNode*> neighbors = {
            current_node->move_left(),
            current_node->move_up(),
            current_node->move_right(),
            current_node->move_down()
        };

        for(auto neighbor_node: neighbors){
            if(neighbor_node != NULL){
                if(closed_list.find(board_to_string(neighbor_node->get_board(), neighbor_node->get_k())) == closed_list.end()){
                    neighbor_node->set_prev(current_node);
                    open_list.push(neighbor_node);
                    all_nodes.push_back(neighbor_node);
                    expanded_nodes++;
                }else{
                    delete neighbor_node;
                    neighbor_node = NULL;
                }
            }
        }
    }

    // delete node
    int node_num = 0;
    for(auto node : all_nodes){
        delete node;
        node = NULL;
        node_num++;
    }
    // cout<<"Number of nodes deleted: "<<node_num<<endl;

    cout<<"Number of nodes explored: "<<explored_nodes<<endl;
    cout<<"Number of nodes expanded: "<<expanded_nodes<<endl;
}

void AStarSearchAlgorithm(){
    int grid_size;
    cout<<"Enter puzzle size: "<<endl;
    cin>>grid_size;
    SearchNode* initial_node = new SearchNode(grid_size);

    int inversion_count = count_inversion(initial_node->get_board(), initial_node->get_k());
    if(grid_size %2 ==0){
        if((inversion_count + initial_node->get_blank_row()) % 2 == 0){
            cout<<"Puzzle is unsolvable!"<<endl;
            delete initial_node;
            initial_node = NULL;
            return;
        }
    }else{
        if(inversion_count % 2 != 0){
            cout<<"Puzzle is unsolvable!"<<endl;
            delete initial_node;
            initial_node = NULL;
            return;
        }
    }


    AStarSearch(new SearchNode(*initial_node), &SearchNode::hamming_distance, true);
    AStarSearch(new SearchNode(*initial_node), &SearchNode::manhattan_distance, false);    

    delete initial_node;
    initial_node = NULL;    
}

int main() {

    AStarSearchAlgorithm();
    return 0;
}