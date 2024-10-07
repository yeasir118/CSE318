#include "bits/stdc++.h"
using namespace std;

// game board
int board[14] = {
    4, 4, 4, 4, 4, 4, 0,
    4, 4, 4, 4, 4, 4, 0
};

// default parameters
int depth = 5;
float w1 = 1, w2 = 1, w3 = 0.5;

// false: no free move
// true: free move
bool move(int board[], bool maxP, int pos){
    int stones = board[pos];
    board[pos] = 0;
    int index = (pos+1)%14;
    while(stones>0){
        if((maxP && index==13) || (!maxP && index==6)){
            index = (index+1)%14;
        }
        board[index]++;
        stones--;

        if(stones==0){
            if((maxP && index==6) || (!maxP && index==13)){
                return true;
            }

            if(board[index]==1){
                if(maxP && index>=0 && index<=5 && board[12-index]>0){
                    board[index] += board[12-index];
                    board[12-index] = 0;
                    board[6] += board[index];
                    board[index] = 0;
                }else if(!maxP && index>=7 && index<=12 && board[12-index]>0){
                    board[index] += board[12-index];
                    board[12-index] = 0;
                    board[13] += board[index];
                    board[index] = 0;
                }
            }
        }

        index = (index+1)%14;
    }
    return false;
}

// print board
void print(int board[]){
    cout<<endl;
    for(int i=0;i<3;i++){
        for(int j=0;j<8;j++){
            if(i==1){
                if(j==0 || j==7){
                    cout<<board[13-j]<<"  ";
                }else{
                    cout<<"-  ";
                }
            }else if(i==0 && (j>=1 && j<7)){
                cout<<board[13-j]<<"  ";
            }else if(i==2 && (j>=1 && j<7)){
                cout<<board[j-1]<<"  ";
            }else{
                cout<<"   ";
            }
        }
        cout<<endl;
    }
}

// terminal state
bool gameOver(int board[]){
    int sum1 = 0;
    int sum2 = 0;
    for(int i=0;i<6;i++){
        sum1 += board[i];
        sum2 += board[i+7];
    }
    if(sum1==0 || sum2==0){
        return true;
    }
    return false;
}

// minimax node
class MinimaxNode{
public:
    int bestValue;
    int bestMove;
    bool freeMove;
    MinimaxNode(){
        this->bestValue = 0;
        this->bestMove = -1;
        this->freeMove = false;
    }
    MinimaxNode(int bestValue, int bestMove, bool freeMove){
        this->bestValue = bestValue;
        this->bestMove = bestMove;
        this->freeMove = freeMove;
    }
    void print(){
        cout<<"bestValue: "<<bestValue<<" bestMove: "<<bestMove<<" freeMove: "<<freeMove<<endl;
    }
};

// heuristic1: max_storage - min_storage
float heuristic1(int board[], bool maxP){
    if(maxP){
        return board[6]-board[13];
    }
    return board[13]-board[6];
}

// heuristic2: w1*(max_storage - min_storage) + w2*(max_stones - min_stones)
float heuristic2(int board[], bool maxP, int w1, int w2){
    int sum1 = 0;
    int sum2 = 0;
    for(int i=0;i<6;i++){
        sum1 += board[i];
        sum2 += board[i+7];
    }
    if(maxP){
        return w1*(board[6]-board[13]) + w2*(sum1-sum2);
    }
    return w1*(board[13]-board[6]) + w2*(sum2-sum1);
}

// heuristic3: w1*(max_storage - min_storage) + w2*(max_stones - min_stones) + w3*(free_move)
float heuristic3(int board[], bool maxP, float w1, float w2, float w3){
    int sum1 = 0;
    int sum2 = 0;
    for(int i=0;i<6;i++){
        sum1 += board[i];
        sum2 += board[i+7];
    }
    if(maxP){
        return w1*(board[6]-board[13]) + w2*(sum1-sum2) + w3*(board[6]==0);
    }
    return w1*(board[13]-board[6]) + w2*(sum2-sum1) + w3*(board[13]==0);
}

MinimaxNode minimax(int board[], bool maxP, int depth){
    if(gameOver(board) || depth==0){
        // return MinimaxNode(heuristic1(board, maxP), -1, false);
        // return MinimaxNode(heuristic2(board, maxP, w1, w2), -1, false);
        return MinimaxNode(heuristic3(board, maxP, w1, w2, w3), -1, false);
    }

    if(maxP){
        int bestValue = INT_MIN;
        int bestMove = -1;
        bool freeMove = false;
        for(int i=0;i<6;i++){
            if(board[i]==0){
                continue;
            }
            int tempBoard[14];
            for(int i=0;i<14;i++){
                tempBoard[i] = board[i];
            }
            bool freeMove = move(tempBoard, maxP, i);
            MinimaxNode child = minimax(tempBoard, !maxP, depth-1);
            if(child.bestValue>=bestValue){
                bestValue = child.bestValue;
                bestMove = i;
                freeMove = child.freeMove;
            }
        }
        return MinimaxNode(bestValue, bestMove, freeMove);
    }else{
        int bestValue = INT_MAX;
        int bestMove = -1;
        bool freeMove = false;
        for(int i=7;i<13;i++){
            if(board[i]==0){
                continue;
            }
            int tempBoard[14];
            for(int i=0;i<14;i++){
                tempBoard[i] = board[i];
            }
            bool freeMove = move(tempBoard, maxP, i);
            MinimaxNode child = minimax(tempBoard, !maxP, depth-1);
            if(child.bestValue<=bestValue){
                bestValue = child.bestValue;
                bestMove = i;
                freeMove = child.freeMove;
            }
        }
        return MinimaxNode(bestValue, bestMove, freeMove);
    }
}

// alpha-beta pruning
MinimaxNode minimax_alpha_beta(int board[], bool maxP, int depth, int alpha, int beta){
    if(gameOver(board) || depth==0){
        // return MinimaxNode(heuristic1(board, maxP), -1, false);
        // return MinimaxNode(heuristic2(board, maxP, w1, w2), -1, false);
        return MinimaxNode(heuristic3(board, maxP, w1, w2, w3), -1, false);
    }

    if(maxP){
        int bestValue = INT_MIN;
        int bestMove = -1;
        bool freeMove = false;
        for(int i=0;i<6;i++){
            if(board[i]==0){
                continue;
            }
            int tempBoard[14];
            for(int i=0;i<14;i++){
                tempBoard[i] = board[i];
            }
            bool freeMove = move(tempBoard, maxP, i);
            MinimaxNode child = minimax_alpha_beta(tempBoard, !maxP, depth-1, alpha, beta);
            if(child.bestValue>=bestValue){
                bestValue = child.bestValue;
                bestMove = i;
                freeMove = child.freeMove;
            }
            alpha = max(alpha, bestValue);
            if(beta<=alpha){
                break;
            }
        }
        return MinimaxNode(bestValue, bestMove, freeMove);
    }else{
        int bestValue = INT_MAX;
        int bestMove = -1;
        bool freeMove = false;
        for(int i=7;i<13;i++){
            if(board[i]==0){
                continue;
            }
            int tempBoard[14];
            for(int i=0;i<14;i++){
                tempBoard[i] = board[i];
            }
            bool freeMove = move(tempBoard, maxP, i);
            MinimaxNode child = minimax_alpha_beta(tempBoard, !maxP, depth-1, alpha, beta);
            if(child.bestValue<=bestValue){
                bestValue = child.bestValue;
                bestMove = i;
                freeMove = child.freeMove;
            }
            beta = min(beta, bestValue);
            if(beta<=alpha){
                break;
            }
        }
        return MinimaxNode(bestValue, bestMove, freeMove);
    }
}

// max player score
int maxPlayerScore(int board[]){
    int sum = 0;
    for(int i=0;i<7;i++){
        sum += board[i];
    }
    return sum;
}

int main(){

    // game starts with max player
    bool maxP = true;

    cout<<"human vs computer: 1\tcomputer vs computer: 2\n";
    int human_vs_computer;
    do{
        cin>>human_vs_computer;
    }while(human_vs_computer!=1 && human_vs_computer!=2);
    cout<<"user provided parameters: 1\tdefault parameters: 2\n";
    int choice;
    do{
        cin>>choice;
    }while(choice!=1 && choice!=2);
    if(choice==1){
        cout<<"depth: ";
        cin>>depth;
        cout<<"heuristics: 1  2  3"<<endl;
        do{
            cin>>choice;
        }while(choice!=1 && choice!=2 && choice!=3);
        if(choice==2 || choice==3){
            cout<<"w1: ";
            cin>>w1;
            cout<<"w2: ";
            cin>>w2;
            if(choice==3){
                cout<<"w3: ";
                cin>>w3;
            }
        }
    }
    cout<<"alpha-beta pruning: 1\tminimax: 2\n";
    do{
        cin>>choice;
    }while(choice!=1 && choice!=2);

    int alpha = INT_MIN;
    int beta = INT_MAX;

    while(true){
        
        print(board);

        if(gameOver(board)){
            int max_score = maxPlayerScore(board);
            if(max_score>24){
                cout<<"max player wins\n";
            }else if(max_score<24){
                cout<<"min player wins\n";
            }else{
                cout<<"draw\n";
            }
            cout<<"max player score: "<<max_score<<endl;
            cout<<"min player score: "<<48-max_score<<endl;
            break;
        }

        if(human_vs_computer==1){
            if(maxP){
                cout<<"max player: (0-5)\n";
                int pos;
                do{
                    cin>>pos;
                }while(pos<0 || pos>5 || board[pos]==0);
                bool freeMove = move(board, maxP, pos);
                if(!freeMove){
                    maxP = !maxP;
                }
            }else{
                MinimaxNode node;
                if(choice==1) node = minimax_alpha_beta(board, maxP, depth, alpha, beta);
                else node = minimax(board, maxP, depth);
                cout<<"\tmin player: ";
                cout<<"bestValue: "<<node.bestValue<<" bestMove: "<<node.bestMove;
                if(node.bestMove==-1){
                    maxP = !maxP;
                    continue;
                }
                bool freeMove = move(board, maxP, node.bestMove);
                cout<<" freeMove: "<<freeMove<<endl;
                if(!freeMove){
                    maxP = !maxP;
                }
            }
        }else{
            MinimaxNode node;
            if(choice==1) node = minimax_alpha_beta(board, maxP, depth, alpha, beta);
            else node = minimax(board, maxP, depth);
            if(maxP) cout<<"\tmax player: ";
            else cout<<"\tmin player: ";
            cout<<"bestValue: "<<node.bestValue<<" bestMove: "<<node.bestMove;
            if(node.bestMove==-1){
                maxP = !maxP;
                continue;
            }
            bool freeMove = move(board, maxP, node.bestMove);
            cout<<" freeMove: "<<freeMove<<endl;
            if(!freeMove){
                maxP = !maxP;
            }
        }
    }

    return 0;
}