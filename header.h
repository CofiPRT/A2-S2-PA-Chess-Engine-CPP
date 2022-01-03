#ifndef _HEADER_H
#define _HEADER_H

#define BOARD_SIZE 120

#define whitePawn -10
#define whiteKnight -30
#define whiteBishop -35
#define whiteRook -50
#define whiteQueen -90
#define whiteKing -100
#define blackPawn 10
#define blackKnight 30
#define blackBishop 35
#define blackRook 50
#define blackQueen 90
#define blackKing 100

extern bool force;
extern bool isWhite;
extern int board[BOARD_SIZE];

extern unsigned long long wPawnsBitb;
extern unsigned long long wKnightsBitb;
extern unsigned long long wBishopsBitb;
extern unsigned long long wRooksBitb;
extern unsigned long long wQueenBitb;
extern unsigned long long wKingBitb;
extern unsigned long long bPawnsBitb;
extern unsigned long long bKnightsBitb;
extern unsigned long long bBishopsBitb;
extern unsigned long long bRooksBitb;
extern unsigned long long bQueenBitb;
extern unsigned long long bKingBitb;

bool checkMove(char* input);
void setBoard();
int boardPos(const char* move);
int boardPos64(const char* move);
void processMove(char* input);
void removePiece(int current120, int current64);
bool isOnBoard(const char* move);

#endif