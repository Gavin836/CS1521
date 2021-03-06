// COMP1521 18s2 Assignment 1
// 9x9 versions of upper- and lower-case letters
// Put in a *.h file to keep csroll.c a bit cleaner

typedef char OneChar[CHRSIZE][CHRSIZE];

OneChar all_chars[52] =
{
  {
    {' ',' ',' ','#','#','#',' ',' ',' '},
    {' ',' ','#',' ',' ',' ','#',' ',' '},
    {' ','#',' ',' ',' ',' ',' ','#',' '},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#','#','#','#','#','#','#','#','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
  },
  {
    {'#','#','#','#','#','#','#','#',' '},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#','#','#','#','#','#','#','#',' '},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#','#','#','#','#','#','#','#',' '},
  },
  {
    {' ','#','#','#','#','#','#','#',' '},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ',' '},
    {'#',' ',' ',' ',' ',' ',' ',' ',' '},
    {'#',' ',' ',' ',' ',' ',' ',' ',' '},
    {'#',' ',' ',' ',' ',' ',' ',' ',' '},
    {'#',' ',' ',' ',' ',' ',' ',' ',' '},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {' ','#','#','#','#','#','#','#',' '},
  },
  {
    {'#','#','#','#','#','#','#','#',' '},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#','#','#','#','#','#','#','#',' '},
  },
  {
    {'#','#','#','#','#','#','#','#','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ',' '},
    {'#',' ',' ',' ',' ',' ',' ',' ',' '},
    {'#',' ',' ',' ',' ',' ',' ',' ',' '},
    {'#','#','#','#','#','#','#','#','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ',' '},
    {'#',' ',' ',' ',' ',' ',' ',' ',' '},
    {'#',' ',' ',' ',' ',' ',' ',' ',' '},
    {'#','#','#','#','#','#','#','#','#'},
  },
  {
    {'#','#','#','#','#','#','#','#','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ',' '},
    {'#',' ',' ',' ',' ',' ',' ',' ',' '},
    {'#',' ',' ',' ',' ',' ',' ',' ',' '},
    {'#','#','#','#','#','#','#','#','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ',' '},
    {'#',' ',' ',' ',' ',' ',' ',' ',' '},
    {'#',' ',' ',' ',' ',' ',' ',' ',' '},
    {'#',' ',' ',' ',' ',' ',' ',' ',' '},
  },
  {
    {'#','#','#','#','#','#','#','#','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ',' '},
    {'#',' ',' ',' ',' ',' ',' ',' ',' '},
    {'#',' ',' ',' ',' ',' ',' ',' ',' '},
    {'#',' ',' ',' ',' ',' ','#','#','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#','#','#','#','#','#','#','#',' '},
  },
  {
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#','#','#','#','#','#','#','#','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
  },
  {
    {' ',' ',' ',' ','#',' ',' ',' ',' '},
    {' ',' ',' ',' ','#',' ',' ',' ',' '},
    {' ',' ',' ',' ','#',' ',' ',' ',' '},
    {' ',' ',' ',' ','#',' ',' ',' ',' '},
    {' ',' ',' ',' ','#',' ',' ',' ',' '},
    {' ',' ',' ',' ','#',' ',' ',' ',' '},
    {' ',' ',' ',' ','#',' ',' ',' ',' '},
    {' ',' ',' ',' ','#',' ',' ',' ',' '},
    {' ',' ',' ',' ','#',' ',' ',' ',' '},
  },
  {
    {' ',' ',' ',' ',' ',' ',' ',' ','#'},
    {' ',' ',' ',' ',' ',' ',' ',' ','#'},
    {' ',' ',' ',' ',' ',' ',' ',' ','#'},
    {' ',' ',' ',' ',' ',' ',' ',' ','#'},
    {' ',' ',' ',' ',' ',' ',' ',' ','#'},
    {' ',' ',' ',' ',' ',' ',' ',' ','#'},
    {' ',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {' ','#','#','#','#','#','#','#',' '},
  },
  {
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ','#',' '},
    {'#',' ',' ',' ',' ',' ','#',' ',' '},
    {'#',' ',' ',' ',' ','#',' ',' ',' '},
    {'#','#','#','#','#',' ',' ',' ',' '},
    {'#',' ',' ',' ',' ','#',' ',' ',' '},
    {'#',' ',' ',' ',' ',' ','#',' ',' '},
    {'#',' ',' ',' ',' ',' ',' ','#',' '},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
  },
  {
    {'#',' ',' ',' ',' ',' ',' ',' ',' '},
    {'#',' ',' ',' ',' ',' ',' ',' ',' '},
    {'#',' ',' ',' ',' ',' ',' ',' ',' '},
    {'#',' ',' ',' ',' ',' ',' ',' ',' '},
    {'#',' ',' ',' ',' ',' ',' ',' ',' '},
    {'#',' ',' ',' ',' ',' ',' ',' ',' '},
    {'#',' ',' ',' ',' ',' ',' ',' ',' '},
    {'#',' ',' ',' ',' ',' ',' ',' ',' '},
    {'#','#','#','#','#','#','#','#','#'},
  },
  {
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#','#',' ',' ',' ',' ',' ','#','#'},
    {'#',' ','#',' ',' ',' ','#',' ','#'},
    {'#',' ',' ','#',' ','#',' ',' ','#'},
    {'#',' ',' ',' ','#',' ',' ',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
  },
  {
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#','#',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ','#',' ',' ',' ',' ',' ','#'},
    {'#',' ',' ','#',' ',' ',' ',' ','#'},
    {'#',' ',' ',' ','#',' ',' ',' ','#'},
    {'#',' ',' ',' ',' ','#',' ',' ','#'},
    {'#',' ',' ',' ',' ',' ','#',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ','#','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
  },
  {
    {' ','#','#','#','#','#','#','#',' '},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {' ','#','#','#','#','#','#','#',' '},
  },
  {
    {'#','#','#','#','#','#','#','#',' '},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#','#','#','#','#','#','#','#',' '},
    {'#',' ',' ',' ',' ',' ',' ',' ',' '},
    {'#',' ',' ',' ',' ',' ',' ',' ',' '},
    {'#',' ',' ',' ',' ',' ',' ',' ',' '},
    {'#',' ',' ',' ',' ',' ',' ',' ',' '},
  },
  {
    {' ','#','#','#','#','#','#','#',' '},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ',' ',' ',' ','#',' ',' ','#'},
    {'#',' ',' ',' ',' ',' ','#',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ','#',' '},
    {' ','#','#','#','#','#','#',' ','#'},
  },
  {
    {'#','#','#','#','#','#','#','#',' '},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#','#','#','#','#','#','#','#',' '},
    {'#',' ',' ',' ',' ','#',' ',' ',' '},
    {'#',' ',' ',' ',' ',' ','#',' ',' '},
    {'#',' ',' ',' ',' ',' ',' ','#',' '},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
  },
  {
    {' ','#','#','#','#','#','#','#','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ',' '},
    {'#',' ',' ',' ',' ',' ',' ',' ',' '},
    {'#',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ','#','#','#','#','#','#','#',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ','#'},
    {' ',' ',' ',' ',' ',' ',' ',' ','#'},
    {' ',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#','#','#','#','#','#','#','#',' '},
  },
  {
    {'#','#','#','#','#','#','#','#','#'},
    {' ',' ',' ',' ','#',' ',' ',' ',' '},
    {' ',' ',' ',' ','#',' ',' ',' ',' '},
    {' ',' ',' ',' ','#',' ',' ',' ',' '},
    {' ',' ',' ',' ','#',' ',' ',' ',' '},
    {' ',' ',' ',' ','#',' ',' ',' ',' '},
    {' ',' ',' ',' ','#',' ',' ',' ',' '},
    {' ',' ',' ',' ','#',' ',' ',' ',' '},
    {' ',' ',' ',' ','#',' ',' ',' ',' '},
  },
  {
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {' ','#','#','#','#','#','#','#',' '},
  },
  {
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {' ','#',' ',' ',' ',' ',' ','#',' '},
    {' ',' ','#',' ',' ',' ','#',' ',' '},
    {' ',' ',' ','#','#','#',' ',' ',' '},
  },
  {
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ',' ',' ','#',' ',' ',' ','#'},
    {' ','#',' ','#',' ','#',' ','#',' '},
    {' ',' ','#',' ',' ',' ','#',' ',' '},
  },
  {
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {' ','#',' ',' ',' ',' ',' ','#',' '},
    {' ',' ','#',' ',' ',' ','#',' ',' '},
    {' ',' ',' ','#',' ','#',' ',' ',' '},
    {' ',' ',' ',' ','#',' ',' ',' ',' '},
    {' ',' ',' ','#',' ','#',' ',' ',' '},
    {' ',' ','#',' ',' ',' ','#',' ',' '},
    {' ','#',' ',' ',' ',' ',' ','#',' '},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
  },
  {
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {' ','#',' ',' ',' ',' ',' ','#',' '},
    {' ',' ','#',' ',' ',' ','#',' ',' '},
    {' ',' ',' ','#',' ','#',' ',' ',' '},
    {' ',' ',' ',' ','#',' ',' ',' ',' '},
    {' ',' ',' ',' ','#',' ',' ',' ',' '},
    {' ',' ',' ',' ','#',' ',' ',' ',' '},
    {' ',' ',' ',' ','#',' ',' ',' ',' '},
    {' ',' ',' ',' ','#',' ',' ',' ',' '},
  },
  {
    {'#','#','#','#','#','#','#','#','#'},
    {' ',' ',' ',' ',' ',' ',' ','#',' '},
    {' ',' ',' ',' ',' ',' ','#',' ',' '},
    {' ',' ',' ',' ',' ','#',' ',' ',' '},
    {' ',' ',' ',' ','#',' ',' ',' ',' '},
    {' ',' ',' ','#',' ',' ',' ',' ',' '},
    {' ',' ','#',' ',' ',' ',' ',' ',' '},
    {' ','#',' ',' ',' ',' ',' ',' ',' '},
    {'#','#','#','#','#','#','#','#','#'},
  },
  {
    {' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {'#','#','#','#','#','#','#','#',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ','#'},
    {' ','#','#','#','#','#','#','#','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {' ','#','#','#','#','#','#','#','#'},
  },
  {
    {'#',' ',' ',' ',' ',' ',' ',' ',' '},
    {'#',' ',' ',' ',' ',' ',' ',' ',' '},
    {'#',' ',' ',' ',' ',' ',' ',' ',' '},
    {'#','#','#','#','#','#','#','#',' '},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#','#','#','#','#','#','#','#',' '},
  },
  {
    {' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ','#','#','#','#','#','#','#','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ',' '},
    {'#',' ',' ',' ',' ',' ',' ',' ',' '},
    {'#',' ',' ',' ',' ',' ',' ',' ',' '},
    {'#',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ','#','#','#','#','#','#','#','#'},
  },
  {
    {' ',' ',' ',' ',' ',' ',' ',' ','#'},
    {' ',' ',' ',' ',' ',' ',' ',' ','#'},
    {' ',' ',' ',' ',' ',' ',' ',' ','#'},
    {' ','#','#','#','#','#','#','#','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {' ','#','#','#','#','#','#','#','#'},
  },
  {
    {' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ','#','#','#','#','#','#','#',' '},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#','#','#','#','#','#','#','#',' '},
    {'#',' ',' ',' ',' ',' ',' ',' ',' '},
    {'#',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ','#','#','#','#','#','#','#','#'},
  },
  {
    {' ','#','#','#','#','#','#','#','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ',' '},
    {'#',' ',' ',' ',' ',' ',' ',' ',' '},
    {'#','#','#','#','#','#','#','#','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ',' '},
    {'#',' ',' ',' ',' ',' ',' ',' ',' '},
    {'#',' ',' ',' ',' ',' ',' ',' ',' '},
    {'#',' ',' ',' ',' ',' ',' ',' ',' '},
    {'#',' ',' ',' ',' ',' ',' ',' ',' '},
  },
  {
    {' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ','#','#','#','#','#','#','#','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {' ','#','#','#','#','#','#','#','#'},
    {' ',' ',' ',' ',' ',' ',' ',' ','#'},
    {' ',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#','#','#','#','#','#','#','#',' '},
  },  
  {
    {'#',' ',' ',' ',' ',' ',' ',' ',' '},
    {'#',' ',' ',' ',' ',' ',' ',' ',' '},
    {'#',' ',' ',' ',' ',' ',' ',' ',' '},
    {'#','#','#','#','#','#','#','#',' '},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
  },
  {
    {' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ','#',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ','#',' ',' ',' ',' '},
    {' ',' ',' ',' ','#',' ',' ',' ',' '},
    {' ',' ',' ',' ','#',' ',' ',' ',' '},
    {' ',' ',' ',' ','#',' ',' ',' ',' '},
    {' ',' ',' ',' ','#',' ',' ',' ',' '},
    {' ',' ',' ',' ','#',' ',' ',' ',' '},
  },
  {
    {' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ','#'},
    {' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ','#'},
    {' ',' ',' ',' ',' ',' ',' ',' ','#'},
    {' ',' ',' ',' ',' ',' ',' ',' ','#'},
    {' ',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {' ','#','#','#','#','#','#','#',' '},
  },  
  {
    {'#',' ',' ',' ',' ',' ',' ',' ',' '},
    {'#',' ',' ',' ',' ',' ',' ',' ',' '},
    {'#',' ',' ',' ',' ',' ',' ',' ',' '},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ','#',' '},
    {'#','#','#','#','#','#','#',' ',' '},
    {'#',' ',' ',' ',' ',' ','#',' ',' '},
    {'#',' ',' ',' ',' ',' ',' ','#',' '},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
  },
  {
    {'#',' ',' ',' ',' ',' ',' ',' ',' '},
    {'#',' ',' ',' ',' ',' ',' ',' ',' '},
    {'#',' ',' ',' ',' ',' ',' ',' ',' '},
    {'#',' ',' ',' ',' ',' ',' ',' ',' '},
    {'#',' ',' ',' ',' ',' ',' ',' ',' '},
    {'#',' ',' ',' ',' ',' ',' ',' ',' '},
    {'#',' ',' ',' ',' ',' ',' ',' ',' '},
    {'#',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ','#','#','#','#','#','#','#','#'},
  },
  {
    {' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ','#',' ',' ',' ',' ',' ','#',' '},
    {'#',' ','#',' ',' ',' ','#',' ','#'},
    {'#',' ',' ','#',' ','#',' ',' ','#'},
    {'#',' ',' ',' ','#',' ',' ',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
  },
  {
    {' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ','#','#','#','#','#',' ',' '},
    {'#','#',' ',' ',' ',' ',' ','#',' '},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
  },
  {
    {' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ','#','#','#','#','#','#','#',' '},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {' ','#','#','#','#','#','#','#',' '},
  },
  {
    {' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ','#','#','#','#','#','#','#',' '},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#','#','#','#','#','#','#','#',' '},
    {'#',' ',' ',' ',' ',' ',' ',' ',' '},
    {'#',' ',' ',' ',' ',' ',' ',' ',' '},
    {'#',' ',' ',' ',' ',' ',' ',' ',' '},
  },  
  {
    {' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ','#','#','#','#','#','#','#','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {' ','#','#','#','#','#','#','#','#'},
    {' ',' ',' ',' ',' ',' ',' ',' ','#'},
    {' ',' ',' ',' ',' ',' ',' ',' ','#'},
    {' ',' ',' ',' ',' ',' ',' ',' ','#'},
  },  
  {
    {' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ','#','#','#','#','#','#','#','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ',' '},
    {'#',' ',' ',' ',' ',' ',' ',' ',' '},
    {'#',' ',' ',' ',' ',' ',' ',' ',' '},
    {'#',' ',' ',' ',' ',' ',' ',' ',' '},
    {'#',' ',' ',' ',' ',' ',' ',' ',' '},
  },
  {
    {' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ','#','#','#','#','#','#','#','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ','#','#','#','#','#','#','#',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ','#'},
    {' ',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#','#','#','#','#','#','#','#',' '},
  },  
  {
    {' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ','#',' ',' ',' ',' '},
    {' ',' ',' ',' ','#',' ',' ',' ',' '},
    {'#','#','#','#','#','#','#','#','#'},
    {' ',' ',' ',' ','#',' ',' ',' ',' '},
    {' ',' ',' ',' ','#',' ',' ',' ',' '},
    {' ',' ',' ',' ','#',' ',' ',' ',' '},
    {' ',' ',' ',' ','#',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ','#',' ',' ',' '},
  },
  {
    {' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {' ','#','#','#','#','#','#','#',' '},
  },
  {
    {' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {' ','#',' ',' ',' ',' ',' ','#',' '},
    {' ',' ','#',' ',' ',' ','#',' ',' '},
    {' ',' ',' ','#',' ','#',' ',' ',' '},
    {' ',' ',' ',' ','#',' ',' ',' ',' '},
  },
  {
    {' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ',' ',' ','#',' ',' ',' ','#'},
    {' ','#',' ','#',' ','#',' ','#',' '},
    {' ',' ','#',' ',' ',' ','#',' ',' '},
  },
  {
    {' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {' ','#',' ',' ',' ',' ',' ','#',' '},
    {' ',' ','#','#','#','#','#',' ',' '},
    {' ',' ','#',' ',' ',' ','#',' ',' '},
    {' ','#',' ',' ',' ',' ',' ','#',' '},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
  },  
  {
    {' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ','#'},
    {' ','#','#','#','#','#','#','#','#'},
    {' ',' ',' ',' ',' ',' ',' ',' ','#'},
    {' ',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#','#','#','#','#','#','#','#',' '},
  },  
  {
    {' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {'#','#','#','#','#','#','#','#','#'},
    {' ',' ',' ',' ',' ',' ',' ','#',' '},
    {' ',' ',' ','#','#','#','#',' ',' '},
    {' ',' ','#',' ',' ',' ',' ',' ',' '},
    {' ','#',' ',' ',' ',' ',' ',' ',' '},
    {'#','#','#','#','#','#','#','#','#'},
  }
};
