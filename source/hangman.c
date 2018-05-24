#include <stdio.h>

void hangman(int n) //виселица
{
	switch (n)
	{
		case 9: printf("  ____   |@|\n |   |   |@|\n |   o   |@|\n |  /|\\  |@|\n_|_ / \\  |@|  "); break;
		case 8: printf("  ____   |@|\n |   |   |@|\n |   o   |@|\n |  /|\\  |@|\n_|_ /    |@|  "); break;
		case 7: printf("  ____   |@|\n |   |   |@|\n |   o   |@|\n |  /|\\  |@|\n_|_      |@|  "); break;
		case 6: printf("  ____   |@|\n |   |   |@|\n |   o   |@|\n |  /|   |@|\n_|_      |@|  "); break;
		case 5: printf("  ____   |@|\n |   |   |@|\n |   o   |@|\n |   |   |@|\n_|_      |@|  "); break;
		case 4: printf("  ____   |@|\n |   |   |@|\n |   o   |@|\n |       |@|\n_|_      |@|  "); break;
		case 3: printf("  ____   |@|\n |       |@|\n |       |@|\n |       |@|\n_|_      |@|  "); break;
		case 2: printf("         |@|\n |       |@|\n |       |@|\n |       |@|\n_|_      |@|  "); break;
		case 1: printf("         |@|\n         |@|\n         |@|\n         |@|\n___      |@|  "); break;
		case 0: printf("         |@|\n         |@|\n         |@|\n         |@|\n         |@|  "); break;
	}
}
