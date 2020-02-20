
#ifndef UTILITY_H_
#define UTILITY_H_

#define NUM_OF_VALID_CHARS 66

inline unsigned char index(char ch)
{
	if (ch >= 'A' && ch <= 'Z')
		return ch - 'A';
	if (ch >= 'a' && ch <= 'z')
		return ch - 'a' + 26;
	if (ch >= '0' && ch <= '9')
		return ch - '0' + 52;
	switch (ch)
	{
		case ('.') : return 62;
		case (',') : return 63;
		case ('\'') : return 64;
		case ('`') : return 65;
	}
}

#endif
