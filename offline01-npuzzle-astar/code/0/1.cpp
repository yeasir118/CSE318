#include <bits/stdc++.h>
using namespace std;

int goal_board[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};

class SearchNode {
int** board;
int k;
int blank_row, blank_col;
int moves_made;
public:
    SearchNode(){
        cout<<"Enter puzzle size: "<<endl;
        cin>>k;

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
        for(int i=0;i<k;i++){
            delete[] board[i];
        }
        delete[] board;
    }
};

int main() {
    vector<SearchNode*> all_nodes;
    
    SearchNode* initialNode = new SearchNode();
    return 0;
}