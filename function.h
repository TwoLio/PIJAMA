bool	initAllegro();
void	changeState(int &state, int newState);
int		showMessageBox(const char *text, int flag, const char *button = NULL);
ALLEGRO_BITMAP*	createBitmap(ALLEGRO_BITMAP *texture[], int n);
