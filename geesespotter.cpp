#include "geesespotter_lib.h"
#include "geesespotter.h"
#include <iostream>



void computeNeighbors(char * board, std::size_t xdim, std::size_t ydim){
for(int i=0;i<xdim*ydim;i++){
    if((board[i]&0b1001)!=0b1001){
        board[i]&=0b11110000;
    }
}
for(int y=0;y<ydim;y++){
    for(int x=0;x<xdim;x++){
        int adj1,adj2,adj3,adj4,adj6,adj7,adj8,adj9{};
        adj1=xdim*(y-1)+x-1;
        adj2=xdim*(y-1)+x;
        adj3=xdim*(y-1)+x+1;
        adj4=xdim*y+x-1;
        adj6=xdim*y+x+1;
        adj7=xdim*(y+1)+x-1;
        adj8=xdim*(y+1)+x;
        adj9=xdim*(y+1)+x+1; 
        if((board[xdim*y+x]&0b1001)==0b1001){
            if(x-1>=0&&y-1>=0&&((board[adj1]&0b1001)!=0b1001)){
                board[adj1]++;
            }
            if(y-1>=0&&((board[adj2]&0b1001)!=0b1001)){
                board[adj2]++;
            }
            if(x+1<=xdim-1&&y-1>=0&&((board[adj3]&0b1001)!=0b1001)){
                board[adj3]++;
            }
            if(x-1>=0&&((board[adj4]&0b1001)!=0b1001)){
                board[adj4]++;
            }
            if(x+1<=xdim-1&&((board[adj6]&0b1001)!=0b1001)){
                board[adj6]++;
            }
            if(x-1>=0&&y+1<=ydim-1&&((board[adj7]&0b1001)!=0b1001)){
                board[adj7]++;
            }
            if(y+1<=ydim-1&&((board[adj8]&0b1001)!=0b1001)){
                board[adj8]++;
            }
            if(x+1<=xdim-1&&y+1<=ydim-1&&((board[adj9]&0b1001)!=0b1001)){
                board[adj9]++;
            }
        }
    }
}
}



int reveal(char * board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc){
    char field=board[xdim*yloc+xloc];
    if(field&0x10){
        return 1;
    }
    else if((field&0x20)==0){
        return 2;
    }
    else{
        field&=0b00001111;
        board[xdim*yloc+xloc]=field;
        if(field==9){
            return 9;
        }
        else if(field==0){
            int y=yloc;
            int x=xloc;
            int adj1,adj2,adj3,adj4,adj6,adj7,adj8,adj9{};
            adj1=xdim*(y-1)+x-1;
            adj2=xdim*(y-1)+x;
            adj3=xdim*(y-1)+x+1;
            adj4=xdim*y+x-1;
            adj6=xdim*y+x+1;
            adj7=xdim*(y+1)+x-1;
            adj8=xdim*(y+1)+x;
            adj9=xdim*(y+1)+x+1; 
        
           if(x-1>=0&&y-1>=0&&((board[adj1]&markedBit())==0)){
                board[adj1]&=(~hiddenBit());
            }
            if(y-1>=0&&((board[adj2]&0x10)==0)){
                board[adj2]&=(~hiddenBit());
            }
            if(x+1<=xdim-1&&y-1>=0&&((board[adj3]&markedBit())==0)){
                board[adj3]&=(~hiddenBit());
            }
            if(x-1>=0&&((board[adj4]&markedBit())==0)){
                board[adj4]&=(~hiddenBit());
            }
            if(x+1<=xdim-1&&((board[adj6]&markedBit())==0)){
                board[adj6]&=(~hiddenBit());
            }
            if(x-1>=0&&y+1<=ydim-1&&((board[adj7]&markedBit())==0)){
                board[adj7]&=(~hiddenBit());
            }
            if(y+1<=ydim-1&&((board[adj8]&markedBit())==0)){
                board[adj8]&=(~hiddenBit());
            }
            if(x+1<=xdim-1&&y+1<=ydim-1&&((board[adj9]&markedBit())==0)){
                board[adj9]&=(~hiddenBit());
            }
            return 0;
        }
        else{
            return 0;
        }
    }
}

bool isGameWon(char * board, std::size_t xdim, std::size_t ydim){
    bool flag=true;
    for(int i=0;i<xdim*ydim;i++){
         if((board[i]&0b1001)!=0b1001) {
            if(board[i]>>4!=0){
                flag=false;
             }
        }
    }
return flag;
}




char * createBoard(std::size_t xdim, std::size_t ydim){
    char *board{new char[xdim*ydim]{}};
    return board;
}

void hideBoard(char * board, std::size_t xdim, std::size_t ydim){
    for(int i=0; i<xdim*ydim;i++)
    {
        board[i]|=hiddenBit();
    }
}

void cleanBoard(char * board){
        delete[] board;
        board=nullptr;
    }   

void printBoard(char * board, std::size_t xdim, std::size_t ydim){
    for(int y=0;y<ydim;y++){
        for(int x=0;x<xdim;x++){
            char field=board[xdim*y+x];
            if((field&markedBit()) == markedBit()){
                std::cout<<'M';
            }
            else if((field&hiddenBit()) == hiddenBit()){
                std::cout<<'*';
            }
            else{
                std::cout<<(board[xdim*y+x]&valueMask());
            }
        }
        std::cout<<std::endl;
    }
}
int mark(char * board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc){
    char markField=board[xdim*yloc+xloc];
    if((markField&0x20)==0){
        return 2;
    }
    else{
        markField^=0x10;
        board[xdim*yloc+xloc]=markField;
        return 0;
    }
}

