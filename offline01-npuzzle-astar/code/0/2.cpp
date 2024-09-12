#include <bits/stdc++.h>
using namespace std;

class SearchNode {
public:
    vector<vector<int>> board;
    int n, moves, hamming, manhattan;
    int blank_row, blank_col;
    SearchNode* prev;

    // Constructor to initialize the board and calculate heuristics
    SearchNode(vector<vector<int>>& b, int moves_made, SearchNode* previous) : 
        board(b), moves(moves_made), prev(previous) {
        n = b.size();
        hamming = calculateHamming();
        manhattan = calculateManhattan();
        findBlankTile();
    }

    // Find the blank tile position (-1)
    void findBlankTile() {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (board[i][j] == -1) {
                    blank_row = i;
                    blank_col = j;
                    return;
                }
            }
        }
    }

    // Calculate Hamming distance
    int calculateHamming() {
        int dist = 0;
        int target = 1;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (board[i][j] != target && board[i][j] != -1) {
                    dist++;
                }
                target++;
            }
        }
        return dist;
    }

    // Calculate Manhattan distance
    int calculateManhattan() {
        int dist = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (board[i][j] != -1) {
                    int target_row = (board[i][j] - 1) / n;
                    int target_col = (board[i][j] - 1) % n;
                    dist += abs(i - target_row) + abs(j - target_col);
                }
            }
        }
        return dist;
    }

    // Priority function: f(n) = g(n) + h(n)
    int priority(bool useHamming) const {
        if (useHamming)
            return moves + hamming;
        else
            return moves + manhattan;
    }

    // Compare two search nodes based on their priority
    bool operator<(const SearchNode& other) const {
        return this->priority(false) > other.priority(false);
    }

    // Generate the neighboring nodes by moving the blank tile
    vector<SearchNode*> neighbors() {
        vector<SearchNode*> neighbors;
        vector<pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}}; // right, down, left, up

        for (auto [dx, dy] : directions) {
            int new_row = blank_row + dx;
            int new_col = blank_col + dy;

            if (new_row >= 0 && new_row < n && new_col >= 0 && new_col < n) {
                vector<vector<int>> new_board = board;
                swap(new_board[blank_row][blank_col], new_board[new_row][new_col]);

                SearchNode* neighbor = new SearchNode(new_board, moves + 1, this);
                neighbors.push_back(neighbor);
            }
        }
        return neighbors;
    }

    // Check if the current board is the goal board
    bool isGoal() const {
        int target = 1;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i == n - 1 && j == n - 1)
                    return board[i][j] == -1;
                if (board[i][j] != target)
                    return false;
                target++;
            }
        }
        return true;
    }

    // Print the board
    void print() {
        for (const auto& row : board) {
            for (int tile : row) {
                if (tile == -1)
                    cout << "  ";
                else
                    cout << tile << " ";
            }
            cout << endl;
        }
        cout << "Moves made: " << moves << endl;
    }
};

// Custom comparator for the priority queue
struct Compare {
    bool operator()(SearchNode* a, SearchNode* b) {
        return a->priority(false) > b->priority(false);  // Use manhattan distance for now
    }
};

void AStarSearch(vector<vector<int>>& initial_board) {
    priority_queue<SearchNode*, vector<SearchNode*>, Compare> open_list;
    set<vector<vector<int>>> closed_list;
    vector<SearchNode*> all_nodes;  // To keep track of all nodes created for memory cleanup

    // Initial search node
    SearchNode* initial_node = new SearchNode(initial_board, 0, nullptr);
    open_list.push(initial_node);
    all_nodes.push_back(initial_node);

    while (!open_list.empty()) {
        SearchNode* current = open_list.top();
        open_list.pop();

        // If we reached the goal
        if (current->isGoal()) {
            cout << "Solution found!" << endl;
            current->print();
            
            // Clean up all dynamically allocated nodes
            for (SearchNode* node : all_nodes) {
                delete node;
            }
            return;
        }

        // Insert current node into closed list
        closed_list.insert(current->board);

        // Explore neighbors
        for (SearchNode* neighbor : current->neighbors()) {
            if (closed_list.find(neighbor->board) == closed_list.end()) {
                open_list.push(neighbor);
                all_nodes.push_back(neighbor);  // Keep track of allocated nodes
            } else {
                // We won't use this neighbor, so free its memory
                delete neighbor;
            }
        }
    }

    cout << "No solution found." << endl;

    // Clean up all dynamically allocated nodes
    for (SearchNode* node : all_nodes) {
        delete node;
    }
}


int main() {
    vector<vector<int>> initial_board = {
        {1, 2, 3},
        {-1, 4, 5},
        {7, 8, 6}  // -1 represents the blank tile
    };

    AStarSearch(initial_board);

    return 0;
}
