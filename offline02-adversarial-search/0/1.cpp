#include "bits/stdc++.h"
using namespace std;

int board[14] = {
    4, 4, 4, 4, 4, 4, 0,
    4, 4, 4, 4, 4, 4, 0
};

// heuristic1: max_stones - min_stones
int heuristic1(int board[], bool maxP){
    int sum1 = 0;
    int sum2 = 0;
    for(int i=0;i<6;i++){
        sum1 += board[i];
        sum2 += board[i+7];
    }
    if(maxP){
        return sum1-sum2;
    }
    return sum2-sum1;
}

// false: no free move
// true: free move
bool move(bool maxP, int pos){
    if(maxP){
        if(pos>=0 && pos<=5 && board[pos]==0){
            return false;
        }
        int temp_board[14];
        for(int i=0;i<14;i++){
            temp_board[i] = board[i];
        }
        int num_stones = temp_board[pos];
        temp_board[pos] = 0;
        int index = (pos+1)%14;
        while(num_stones>0){
            if(index==13){
                index = (index+1)%14;
                continue;
            }

            temp_board[index]++;
            num_stones--;

            if(num_stones==0){
                if(index==6){
                    return true;
                }

                if(temp_board[index]==1 && index>=0 && index<=5 && temp_board[12-index]>0){
                        temp_board[index] += temp_board[12-index];
                        temp_board[12-index] = 0;
                        temp_board[6] += temp_board[index];
                        temp_board[index] = 0;
                }
            }

            index = (index+1)%14;
        }   
    }else{
        if(pos>=7 && pos<=12 && board[pos]==0){
            return false;
        }
        int temp_board[14];
        for(int i=0;i<14;i++){
            temp_board[i] = board[i];
        }
        int num_stones = temp_board[pos];
        temp_board[pos] = 0;
        int index = (pos+1)%14;
        while(num_stones>0){
            if(index==6){
                index = (index+1)%14;
                continue;
            }

            temp_board[index]++;
            num_stones--;

            if(num_stones==0){
                if(index==13){
                    return true;
                }

                if(temp_board[index]==1 && index>=7 && index<=12 && temp_board[12-index]>0){
                        temp_board[index] += temp_board[12-index];
                        temp_board[12-index] = 0;
                        temp_board[13] += temp_board[index];
                        temp_board[index] = 0;
                }
            }

            index = (index+1)%14;
        }   
    }
}

// -1: min wins
// 0: draw
// 1: max wins
// 2: not terminal
int terminal_test(int board[], bool maxP){
    int sum1 = 0;
    int sum2 = 0;
    for(int i=0;i<6;i++){
        sum1 += board[i];
        sum2 += board[i+7];
    }
    if(sum1==0 || sum2==0){
        if(board[6]>board[13]){
            board[6] += sum1;
            return 1;
        }else if(board[6]<board[13]){
            board[13] += sum2;
            return -1;
        }else{
            return 0;
        }
    }
    return 2;
}

class MiniMaxReturnNode{
public:
    int heuristic_value;
    int action;
    bool free_move;
    MiniMaxReturnNode(int heuristic_value, int action, bool free_move){
        this->heuristic_value = heuristic_value;
        this->action = action;
        this->free_move = free_move;
    }
    void print(){
        cout<<"Heuristic value: "<<heuristic_value<<endl;
        cout<<"Action: "<<action<<endl;
        cout<<"Free move: "<<free_move<<endl;
    }
};

MiniMaxReturnNode MiniMax(int board[], bool maxP, int depth){
    if(depth==0){
        return MiniMaxReturnNode(heuristic1(board, maxP), -1, false);
    }
    if(maxP){
        int max_val = INT_MIN;
        int action = -1;
        bool free_move = false;
        for(int i=0;i<6;i++){
            if(board[i]==0){
                continue;
            }
            int temp_board[14];
            for(int j=0;j<14;j++){
                temp_board[j] = board[j];
            }
            bool free_move = move(maxP, i);
            MiniMaxReturnNode temp = MiniMax(temp_board, !maxP, depth-1);
            if(temp.heuristic_value>max_val){
                max_val = temp.heuristic_value;
                action = i;
                free_move = temp.free_move;
            }
        }
        return MiniMaxReturnNode(max_val, action, free_move);
    }else{
        int min_val = INT_MAX;
        int action = -1;
        bool free_move = false;
        for(int i=7;i<13;i++){
            if(board[i]==0){
                continue;
            }
            int temp_board[14];
            for(int j=0;j<14;j++){
                temp_board[j] = board[j];
            }
            bool free_move = move(maxP, i);
            MiniMaxReturnNode temp = MiniMax(temp_board, !maxP, depth-1);
            if(temp.heuristic_value<min_val){
                min_val = temp.heuristic_value;
                action = i;
                free_move = temp.free_move;
            }
        }
        return MiniMaxReturnNode(min_val, action, free_move);
    }
}

int main(){
    bool mP = true;
    while(true){
        int depth = 5;
        int teminal = terminal_test(board, true);
        if(teminal==1){
            cout<<"Max wins"<<endl;
            break;
        }else if(teminal==-1){
            cout<<"Min wins"<<endl;
            break;
        }else if(teminal==0){
            cout<<"Draw"<<endl;
            break;
        }
        if(mP){
            MiniMaxReturnNode temp = MiniMax(board, mP, depth);
            temp.print();
            if(temp.free_move){
                cout<<"Free move"<<endl;
                continue;
            }
            
            
        }
    }
    return 0;
}