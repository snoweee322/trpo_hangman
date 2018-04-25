int main()
{
	char c;
	while (1)
	{
    	puts(" 1. Start game");
    	puts(" 2. Leaderboard");
    	puts(" 3. Exit");
    	c = getch();
    	switch(c)
    	{
			case '1': game(); break;
			case '2': leaderboard(); break;
			case '3': return 0;
			default : puts("Wrong key");
		}
	}
	return 0;
}
