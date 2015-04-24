void newTetrimino()
{
  tetr_x = 2;
  tetr_y = -1;
  curr_tetr += (random() % 7);
  if(curr_tetr >= 7)
  {
    curr_tetr -= 7;
  }
  for(byte y = 0; y < 4; y++)
  {
    for(byte x = 0; x < 4; x++)
    {
      current_tetrimino[y][x] = tetrimino[curr_tetr][y][x];
    }
  }
}
