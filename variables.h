

//ALLEGRO_FONT *font = al_load_ttf_font("Fonts/Capture_it.ttf",25,3 ); //Load Main font

//ALLEGRO_BITMAP *chessboard = al_load_bitmap("Images/chess_board3.png"); ///Load chess board from file

ALLEGRO_BITMAP *chessboard = al_load_bitmap("Images/Chess_board_4.bmp");

//ALLEGRO_BITMAP *chessboard = al_load_bitmap("Images/Chess_board2.bmp");



/*
ALLEGRO_BITMAP *white_pawn = al_load_bitmap("Images/white_pawn.bmp");
al_convert_mask_to_alpha (white_pawn, al_map_rgb(255,0,255)); //this converts the color 255,0,255 to transparent


ALLEGRO_BITMAP *black_pawn = al_load_bitmap("Images/pawn_black.bmp");
al_convert_mask_to_alpha (black_pawn, al_map_rgb(255,0,255)); //this converts the color 255,0,255 to transparent

ALLEGRO_BITMAP *white_rook = al_load_bitmap("Images/white_rook.bmp");
al_convert_mask_to_alpha (white_rook, al_map_rgb(255,0,255)); //this converts the color 255,0,255 to transparent

ALLEGRO_BITMAP *black_rook = al_load_bitmap("Images/black_rook.bmp");
al_convert_mask_to_alpha (black_rook, al_map_rgb(255,0,255)); //this converts the color 255,0,255 to transparent

ALLEGRO_BITMAP *white_knight = al_load_bitmap("Images/white_knight.bmp");
al_convert_mask_to_alpha (white_knight, al_map_rgb(255,0,255)); //this converts the color 255,0,255 to transparent

ALLEGRO_BITMAP *black_knight = al_load_bitmap("Images/black_knight.bmp");
al_convert_mask_to_alpha (black_knight, al_map_rgb(255,0,255)); //this converts the color 255,0,255 to transparent

ALLEGRO_BITMAP *white_bishop = al_load_bitmap("Images/white_bishop.bmp");
al_convert_mask_to_alpha (white_bishop, al_map_rgb(255,0,255)); //this converts the color 255,0,255 to transparent

ALLEGRO_BITMAP *black_bishop = al_load_bitmap("Images/black_bishop.bmp");
al_convert_mask_to_alpha (black_bishop, al_map_rgb(255,0,255)); //this converts the color 255,0,255 to transparent

ALLEGRO_BITMAP *white_queen = al_load_bitmap("Images/white_queen.bmp");
al_convert_mask_to_alpha (white_queen, al_map_rgb(255,0,255)); //this converts the color 255,0,255 to transparent

ALLEGRO_BITMAP *white_king = al_load_bitmap("Images/white_king.bmp");
al_convert_mask_to_alpha (white_king, al_map_rgb(255,0,255)); //this converts the color 255,0,255 to transparent

ALLEGRO_BITMAP *black_queen = al_load_bitmap("Images/black_queen.bmp");
al_convert_mask_to_alpha (black_queen, al_map_rgb(255,0,255)); //this converts the color 255,0,255 to transparent

ALLEGRO_BITMAP *black_king = al_load_bitmap("Images/black_king.bmp");
al_convert_mask_to_alpha (black_king, al_map_rgb(255,0,255)); //this converts the color 255,0,255 to transparent

ALLEGRO_BITMAP *transparent = al_load_bitmap("Images/transparent.bmp");
al_convert_mask_to_alpha (transparent, al_map_rgb(255,0,255)); //this converts the color 255,0,255 to transparent

ALLEGRO_BITMAP *transparent2 = al_load_bitmap("Images/transparent2.bmp");
al_convert_mask_to_alpha (transparent2, al_map_rgb(255,0,255)); //this converts the color 255,0,255 to transparent
*/

///New chess pieces:


ALLEGRO_BITMAP *white_pawn = al_load_bitmap("Images2/white_pawn.png");
al_convert_mask_to_alpha (white_pawn, al_map_rgb(255,0,255)); //this converts the color 255,0,255 to transparent


ALLEGRO_BITMAP *black_pawn = al_load_bitmap("Images2/black_pawn.png");
al_convert_mask_to_alpha (black_pawn, al_map_rgb(255,0,255)); //this converts the color 255,0,255 to transparent

ALLEGRO_BITMAP *white_rook = al_load_bitmap("Images2/white_rook.png");
al_convert_mask_to_alpha (white_rook, al_map_rgb(255,0,255)); //this converts the color 255,0,255 to transparent

ALLEGRO_BITMAP *black_rook = al_load_bitmap("Images2/black_rook.png");
al_convert_mask_to_alpha (black_rook, al_map_rgb(255,0,255)); //this converts the color 255,0,255 to transparent

ALLEGRO_BITMAP *white_knight = al_load_bitmap("Images2/white_knight.png");
al_convert_mask_to_alpha (white_knight, al_map_rgb(255,0,255)); //this converts the color 255,0,255 to transparent

ALLEGRO_BITMAP *black_knight = al_load_bitmap("Images2/black_knight.png");
al_convert_mask_to_alpha (black_knight, al_map_rgb(255,0,255)); //this converts the color 255,0,255 to transparent

ALLEGRO_BITMAP *white_bishop = al_load_bitmap("Images2/white_bishop.png");
al_convert_mask_to_alpha (white_bishop, al_map_rgb(255,0,255)); //this converts the color 255,0,255 to transparent

ALLEGRO_BITMAP *black_bishop = al_load_bitmap("Images2/black_bishop.png");
al_convert_mask_to_alpha (black_bishop, al_map_rgb(255,0,255)); //this converts the color 255,0,255 to transparent

ALLEGRO_BITMAP *white_queen = al_load_bitmap("Images2/white_queen.png");
al_convert_mask_to_alpha (white_queen, al_map_rgb(255,0,255)); //this converts the color 255,0,255 to transparent

ALLEGRO_BITMAP *white_king = al_load_bitmap("Images2/white_king.png");
al_convert_mask_to_alpha (white_king, al_map_rgb(255,0,255)); //this converts the color 255,0,255 to transparent

ALLEGRO_BITMAP *black_queen = al_load_bitmap("Images2/black_queen.png");
al_convert_mask_to_alpha (black_queen, al_map_rgb(255,0,255)); //this converts the color 255,0,255 to transparent

ALLEGRO_BITMAP *black_king = al_load_bitmap("Images2/black_king.png");
al_convert_mask_to_alpha (black_king, al_map_rgb(255,0,255)); //this converts the color 255,0,255 to transparent

ALLEGRO_BITMAP *transparent = al_load_bitmap("Images/transparent.bmp");
al_convert_mask_to_alpha (transparent, al_map_rgb(255,0,255)); //this converts the color 255,0,255 to transparent

ALLEGRO_BITMAP *transparent2 = al_load_bitmap("Images/transparent2.bmp");
al_convert_mask_to_alpha (transparent2, al_map_rgb(255,0,255)); //this converts the color 255,0,255 to transparent


///BUTTONS----------------------------------------------------------------------------------------------------------
ALLEGRO_BITMAP *reset = al_load_bitmap("Buttons/reset.png");
//al_convert_mask_to_alpha (black_king, al_map_rgb(255,0,255)); //this converts the color 255,0,255 to transparent

ALLEGRO_BITMAP *b1 = al_load_bitmap("Buttons/b1.png");
ALLEGRO_BITMAP *b2 = al_load_bitmap("Buttons/b2.png");
ALLEGRO_BITMAP *b3 = al_load_bitmap("Buttons/b3.png");
ALLEGRO_BITMAP *b4 = al_load_bitmap("Buttons/b4.png");
ALLEGRO_BITMAP *b5 = al_load_bitmap("Buttons/b5.png");
ALLEGRO_BITMAP *b6 = al_load_bitmap("Buttons/b6.png");
ALLEGRO_BITMAP *b7 = al_load_bitmap("Buttons/b7.png");
ALLEGRO_BITMAP *undo = al_load_bitmap("Buttons/undo.png");
ALLEGRO_BITMAP *exit = al_load_bitmap("Buttons/exit.png");
ALLEGRO_BITMAP *editor = al_load_bitmap("Buttons/editor.png");

ALLEGRO_BITMAP *play = al_load_bitmap("Buttons/play.png");

ALLEGRO_BITMAP *standardboard = al_load_bitmap("Buttons/standardboard.png");

/*
ALLEGRO_BITMAP *iamwhites = al_load_bitmap("Buttons/iamwhites.png");
ALLEGRO_BITMAP *iamblacks = al_load_bitmap("Buttons/iamblacks.png");
ALLEGRO_BITMAP *whitestart = al_load_bitmap("Buttons/whitestart.png");
ALLEGRO_BITMAP *blackstart = al_load_bitmap("Buttons/blackstart.png");
*/

ALLEGRO_BITMAP *whiteb = al_load_bitmap("Buttons/white.png");
ALLEGRO_BITMAP *blackb = al_load_bitmap("Buttons/black.png");

ALLEGRO_BITMAP *no_cpu = al_load_bitmap("Buttons/no_cpu.png");

ALLEGRO_BITMAP *about = al_load_bitmap("Buttons/about.png");

ALLEGRO_BITMAP *piece_on_hold;

