#include <bits/stdc++.h>
using namespace std;

int goal_board[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};

class SearchNode {
int** board;
int k;
int blank_row, blank_col;
int moves_made;
SearchNode* prev;
public:
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
    }

    // copy constructor
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
    }

    // assignment operator
    SearchNode& operator=(const SearchNode& node){
        if(this != &node){
            // deallocate existing resources
            for(int i=0;i<k;i++){
                delete[] board[i];
            }
            delete[] board;

            // copy new resources
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
        }
        return *this;
    }

    int** get_board(){
        return board;
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

    bool is_goal(){
        int goal = 1;
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
        if(board == NULL){
            return;
        }
        for(int i=0;i<k;i++){
            delete[] board[i];
        }
        delete[] board;
        board = NULL;
    }
};

struct CompareHamming{
    bool operator()(SearchNode* node1, SearchNode* node2){
        return (node1->hamming_distance() + node1->get_moves_made()) > (node2->hamming_distance() + node2->get_moves_made());
    }
};

string board_to_string(int** board, int k){
    string board_string = "";
    for(int i=0;i<k;i++){
        for(int j=0;j<k;j++){
            board_string += to_string(board[i][j]) + ",";
        }
    }
    return board_string;
}

int count_inversion(int** board, int k){
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

int main() {

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
            return 0;
        }
    }else{
        if(inversion_count % 2 != 0){
            cout<<"Puzzle is unsolvable!"<<endl;
            delete initial_node;
            initial_node = NULL;
            return 0;
        }
    }

    priority_queue<SearchNode*, vector<SearchNode*>, CompareHamming> open_list;
    set<string> closed_list;
    vector<SearchNode*> all_nodes;

    open_list.push(initial_node);
    all_nodes.push_back(initial_node);

    int explored_nodes = 0, expanded_nodes = 0;

    while(!open_list.empty()){

        SearchNode* current_node = open_list.top();
        open_list.pop();
        explored_nodes++;

        if(current_node->is_goal()){
            cout<<"Goal State Reached!"<<endl;
            cout<<"Moves Made: "<<current_node->get_moves_made()<<endl;
            cout<<"Path: "<<endl;
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
    cout<<"Number of nodes deleted: "<<node_num<<endl;

    cout<<"Number of nodes explored: "<<explored_nodes<<endl;
    cout<<"Number of nodes expanded: "<<expanded_nodes<<endl;

    return 0;
}