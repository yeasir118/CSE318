#include "bits/stdc++.h"
using namespace std;

// an one dimentional array of integers
int board[14] = {
    4, 4, 4, 4, 4, 4, 0,
    4, 4, 4, 4, 4, 4, 0
};

void printBoard(){
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

// -1: min player wins
// 0: draw
// 1: max player wins
// 2: game not over
int terminalTest(){
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

// 0: swap player
// 1: same player
int action(bool maxPlayer){
    
    if(maxPlayer){
        cout<<"max player: (0-5)\n";    
    }else{
        cout<<"min player: (0-5)\n";
    }
    int pos;
    do{
        cin>>pos;
    }while(pos<0 || pos>5 || (board[pos]==0 && maxPlayer) || (board[pos+7]==0 && !maxPlayer));

    if(!maxPlayer){
        pos += 7;
    }

    int num_stones = board[pos];
    board[pos] = 0;
    int index = (pos+1)%14;
    while(num_stones>0){
        if((maxPlayer && index==13) || (!maxPlayer && index==6)){
            index = (index+1)%14;
        }
        cout<<"index: "<<index<<" num_stones: "<<num_stones<<endl;
        board[index]++;
        num_stones--;
        index = (index+1)%14;
    }
    index = (index+13)%14;
    if(maxPlayer && index==6){
        return 1;
    }
    if(!maxPlayer && index==13){
        return 1;
    }
    if(board[index]==1){
        if(maxPlayer && index>=0 && index<=5 && board[12-index]>0){
            board[index] += board[12-index];
            board[12-index] = 0;
            board[6] += board[index];
            board[index] = 0;
        }else if(!maxPlayer && index>=7 && index<=12 && board[12-index]>0){
            board[index] += board[12-index];
            board[12-index] = 0;
            board[13] += board[index];
            board[index] = 0;
        }
    }
    return 0;
}

// heuristic1: max_stones - min_stones
int heuristic1(){
    int sum1 = 0;
    int sum2 = 0;
    for(int i=0;i<6;i++){
        sum1 += board[i];
        sum2 += board[i+7];
    }
    return sum1-sum2;
}



int main()
{   
    printBoard();
    bool mP = true;
    while(1){
        int val = action(mP);
        if(!val){
            mP = !mP;
        }
        printBoard();
        int term = terminalTest();
        if(term==1){
            cout<<"max player wins\n";
            break;
        }else if(term==-1){
            cout<<"min player wins\n";
            break;
        }else if(term==0){
            cout<<"draw\n";
            break;
        }
    }
    return 0;
}