int checkWin(int a[20][20], int i, int j, int player, int _player)
{
    //Xét hàng ngang
    if(a[i][j+1] == player && a[i][j+2] == player && a[i][j+3] == player && a[i][j+4] == player && a[i][j+5] != _player && a[i][j-1] != _player) return 1;
    if(a[i][j-1] == player && a[i][j+1] == player && a[i][j+2] == player && a[i][j+3] == player && a[i][j+4] != _player && a[i][j-2] != _player) return 1;
    if(a[i][j-1] == player && a[i][j-2] == player && a[i][j-3] == player && a[i][j-4] == player && a[i][j+1] != _player && a[i][j-5] != _player) return 1;
    if(a[i][j+1] == player && a[i][j-1] == player && a[i][j-2] == player && a[i][j-3] == player && a[i][j+2] != _player && a[i][j-4] != _player) return 1;
    if(a[i][j+1] == player && a[i][j+2] == player && a[i][j-1] == player && a[i][j-2] == player && a[i][j+3] != _player && a[i][j-3] != _player) return 1;

    //Xét hàng dọc
    if(a[i+1][j] == player && a[i+2][j] == player && a[i+3][j] == player && a[i+4][j] == player && a[i+5][j] != _player && a[i-1][j] != _player) return 1;
    if(a[i-1][j] == player && a[i+1][j] == player && a[i+2][j] == player && a[i+3][j] == player && a[i+4][j] != _player && a[i-2][j] != _player) return 1;
    if(a[i-1][j] == player && a[i-2][j] == player && a[i-3][j] == player && a[i-4][j] == player && a[i+1][j] != _player && a[i-5][j] != _player) return 1;
    if(a[i+1][j] == player && a[i-1][j] == player && a[i-2][j] == player && a[i-3][j] == player && a[i+2][j] != _player && a[i-4][j] != _player) return 1;
    if(a[i+1][j] == player && a[i+2][j] == player && a[i-1][j] == player && a[i-2][j] == player && a[i+3][j] != _player && a[i-3][j] != _player) return 1;

    //Xét hàng chéo sang trái
    if(a[i+1][j+1] == player && a[i+2][j+2] == player && a[i+3][j+3] == player && a[i+4][j+4] == player && a[i-1][j-1] != _player && a[i+5][j+5] != _player) return 1;
    if(a[i-1][j-1] == player && a[i+1][j+1] == player && a[i+2][j+2] == player && a[i+3][j+3] == player && a[i-2][j-2] != _player && a[i+4][j+4] != _player) return 1;
    if(a[i-2][j-2] == player && a[i-1][j-1] == player && a[i+1][j+1] == player && a[i+2][j+2] == player && a[i-3][j-3] != _player && a[i+3][j+3] != _player) return 1;
    if(a[i-1][j-1] == player && a[i-2][j-2] == player && a[i-3][j-3] == player && a[i+1][j+1] == player && a[i-4][j-4] != _player && a[i+2][j+2] != _player) return 1;
    if(a[i-1][j-1] == player && a[i-2][j-2] == player && a[i-3][j-3] == player && a[i-4][j-4] == player && a[i+1][j+1] != _player && a[i-5][j-5] != _player) return 1;

    //Xét hàng chéo sang phải
    if(a[i-1][j+1] == player && a[i-2][j+2] == player && a[i-3][j+3] == player && a[i-4][j+4] == player && a[i+1][j-1] != _player && a[i-5][j+5] != _player) return 1;
    if(a[i+1][j-1] == player && a[i-1][j+1] == player && a[i-2][j+2] == player && a[i-3][j+3] == player && a[i+2][j-2] != _player && a[i-4][j+4] != _player) return 1;
    if(a[i+1][j-1] == player && a[i-1][j+1] == player && a[i+2][j-2] == player && a[i-2][j+2] == player && a[i-3][j+3] != _player && a[i+3][j-3] != _player) return 1;
    if(a[i+1][j-1] == player && a[i-1][j+1] == player && a[i+3][j-3] == player && a[i+2][j-2] == player && a[i+4][j-4] != _player && a[i-2][j+2] != _player) return 1;
    if(a[i+1][j-1] == player && a[i+2][j-2] == player && a[i+3][j-3] == player && a[i+4][j-4] == player && a[i-1][j+1] != _player && a[i+5][j-5] != _player) return 1;
    else return -1;
}
//**************************************************************


