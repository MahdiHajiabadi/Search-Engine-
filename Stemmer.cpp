#include<iostream>
#include<string>
#include<fstream>
using namespace std;
int main()
{
	ifstream fin("diffs.txt");
	char * stemming(char *);
	char word[100]="seeing";
	char *a=stemming(word);
	cout<<word;
	char steam[100];
	///cin>>word;
	int n = 0, k = 0;
	ofstream fout("errors.txt");
	while (fin >> word)
	{
		fin >> steam;
		string t = word;
		char *a=stemming(word);
		//cout<<word<<endl;
		string s = word;
		if (s == steam )
			k++;
		else
			fout << t << " : " << s << " , " << steam << "\n";
		n++;
	}
	fout.close();
	cout << k << " / " << n << " = " << k / (double)n * 100 << endl;
}
char *stemming(char *word)
{
	int status=0;
	int m(char * ,int);
	int step1=0,step2=0;
	bool IsCVC(char *,int);
	int i,index=0,length;
	for(i=0;word[i]!=0;i++);
	length=i;
	////////////////////////////////Step 1:Gets rid of plurals

	if (word[i-1]=='s')
	{
		if(word[i-2] =='e'&& word[i-3] =='s'&& word[i-4] =='s' && length>5)
		{
			i-=2;
		}
		else if (length>3 && word[i-2]=='e' && word[i-3]=='i')
		{
			i-=2;
		}
		else if( word[i-2]!='s')
		{
			i--;
			step2=1;
		}
	}
	if (length>4 && word[i-1]=='d' && word[i-2]=='e' && word[i-3]=='e')
	{
		int k=m(word,i-3);
		if (k>0)
		{
			i--;
		}
	}
	if (word[i-1]=='d' && word[i-2]=='e' && length>2)
	{
		if (word[i-3]!='e')
		{
			
		//int k=m(word,i-2);
		int k=0;
		for (int j=0;j<i-2;j++)
		{

			if (word[j]=='a'||word[j]=='e'||word[j]=='i'||word[j]=='o'||word[j]=='u')
			{ 
				k++;
				break;
			}
		}
		if (k==0)
			for (int j=0;j<i-2;j++)
			{
				if (word[j]=='y')
				{ 
					k++;
					break;
				}

			}
			if (k>0)
			{
				i=i-2;
				step1=1;
				if (step2)
					step2=0;
			}
		}
	}
	if (!step1 && word[i-1]=='g' && word[i-2]=='n'&& word[i-3]=='i' && i>4)
	{
		int k=0;
		for (int j=0;j<i-3;j++)
		{

			if (word[j]=='a'||word[j]=='e'||word[j]=='i'||word[j]=='o'||word[j]=='u')
			{ 
				k++;
				break;
			}
		}
		if (k==0)
			for (int j=0;j<i-2;j++)
			{
				if (word[j]=='y')
				{ 
					k++;
					break;
				}

			}
		if (k>0)
		{
			i=i-3;
			step1=1;
			if (step2)
				step2=0;

		}
	}
	if (word[i-1]=='t'&& word[i-2]=='a' && step1 &&  length>4)
	{
		i++;
		word[i-1]='e';
	}
	else if (word[i-1]=='l'&& word[i-2]=='b' && step1 && length>3)
	{
		i++;
		word[i-1]='e';
	}
	else if (word[i-1]=='z'&& word[i-2]=='i' && step1 &&  length>3)
	{
		i++;
		word[i-1]='e';
	}
	if (step1)
	{
		int k=m(word,i);
		bool cond=IsCVC(word,i);
		if (k==1 && cond )
		{
			i++;
			word[i-1]='e';
		}
	}
	if (word[i-1]==word[i-2] && step1 && !step2 &&  length>4 )
	{
		if (word[i-1]!='o' &&  word[i-1]!='e')
		{
		i--;
		status=1;
		if (word[i-1]=='l'||word[i-1]=='s'||word[i-1]=='z' )
			i++;
		}
	}
	//////////////Step 2. Another vowel in stem
	if (word[i-1]=='y')
	{
		int k=0;
		for(int j=0;j<i;j++)
			if (word[j]=='a'||word[j]=='e'||word[j]=='i'||word[j]=='o'||word[j]=='u' )
			{	k++;
		break;
		}
		if (k==0)
			for (int j=0;j<i-2;j++)
			{
				if (word[j]=='y')
				{ 
					k++;
					break;
				}
			}

		if (k!=0)
			word[i-1]='i';
	}
	/*int k=m(word,i);
	bool con=IsCVC(word,i);
	if (k==1 && con)
	word[i-1]='e';*/

	///////////////////Step 3 Maps double suffixes to single ones
	//int k=m(word,i);
	if (i>=2)
		switch (word[i-2])
	{ 

		case 'a':
			if(word[i-1]=='l'&& word[i-2]=='a'&&word[i-3]=='n' && word[i-4]=='o'&&word[i-5]=='i'&&word[i-6]=='t'&&word[i-7]=='a')
			{
				int k=m(word,i-7);
				if (k>0)
				{
					word[i-5]='e';
					i-=4;
				}
			}
			if (i>=6)
				if( word[i-1]=='l'&& word[i-2]=='a'&&word[i-3]=='n' && word[i-4]=='o'&&word[i-5]=='i'&&word[i-6]=='t')
				{
					int k=m(word,i-6);
					if (k>0)
						i-=2;
				}
				break;
		case 'c':
			if (i>=4)
				if( word[i-1]=='i'&& word[i-2]=='c'&& word[i-3]=='n' && word[i-4]=='e')
				{
					int k=m(word,i-4);
					if (k>0)
					{
						word[i-1]='e'; 
					}
				}
				if (i>=4)
					if( word[i-1]=='i'&& word[i-2]=='c'&& word[i-3]=='n' && word[i-4]=='a')
					{
						int k=m(word,i-4);
						if(k>0)
						{
							word[i-1]='e'; 
						}
					}
					break;
		case 'e':
			if (i>=4)
				if(word[i-1]=='r'&& word[i-2]=='e'&&word[i-3]=='z' && word[i-4]=='i')
				{
					int k=m(word,i-4);
					if(k>0)
					{
						i--;
					}
				}
				break;
		case 'l':
			if (i>=3)
				if( word[i-1]=='i'&& word[i-2]=='l'&& word[i-3]=='b' && word[i-4]=='a')
				{
					int k=m(word,i-4);
					if (k>0)
						word[i-1]='e'; 
				}
				if (i>=4)
					if( word[i-1]=='i'&& word[i-2]=='l'&&word[i-3]=='l'&& word[i-4]=='a')
					{
						int k=m(word,i-4);
						if(k>0)
							i-=2;
					}
					if (i>=5)
						if( word[i-1]=='i'&& word[i-2]=='l'&&word[i-3]=='t'&& word[i-4]=='n'&& word[i-5]=='e' && length>4)
						{
							int k=m(word,i-5);
							if (k>0)
								i-=2;
						}
						if (i>=3)
							if(word[i-1]=='i'&& word[i-2]=='l'&& word[i-3]=='e' && length>4)
							{
								int k=m(word,i-3);
								if (k>0)
									i-=2;
							}
							if (i>=5)
								if(word[i-1]=='i'&& word[i-2]=='l'&&word[i-3]=='s'&& word[i-4]=='u'&& word[i-5]=='o')
								{
									int k=m(word,i-5);
									if (k>0)
										i-=2;
								}
								break;
		case 'o':
			if (i>=7)
				if( word[i-1]=='n'&& word[i-2]=='o'&&word[i-3]=='i'&& word[i-4]=='t'&& word[i-5]=='a'&& word[i-6]=='z'&& word[i-7]=='i')
				{
					int k=m(word,i-7);
					if (k>0)
					{
						word[i-5]='e';
						i-=4;
					}
				}
				if (i>=5)
					if( word[i-1]=='n'&& word[i-2]=='o'&&word[i-3]=='i'&& word[i-4]=='t'&& word[i-5]=='a')
					{
						int k=m(word,i-5);
						if (k>0)
						{
							word[i-3]='e';
							i-=2;
						}
					}
					/*	if(k>0 && word[i-1]=='n'&& word[i-2]=='o'&&word[i-3]=='i'&& word[i-4]=='t'&& word[i-5]=='c')
					{
					i-=3;
					}*/
					if( word[i-1]=='n'&& word[i-2]=='o'&&word[i-3]=='i'&& word[i-4]=='t'&& word[i-5]=='p')
					{
						int k=m(word,i-5);
						if (k>0)
							i-=3;
					}
					if( word[i-1]=='n'&& word[i-2]=='o'&&word[i-3]=='i'&& word[i-4]=='t'&& word[i-5]=='r')
					{
						int k=m(word,i-5);
						if (k>0)
							i-=3;
					}
					if(word[i-1]=='n'&& word[i-2]=='o'&&word[i-3]=='i'&& word[i-4]=='t'&& word[i-5]=='i')
					{
						int k=m(word,i-5);
						if (k>0)
							i-=3;
					}
					if (i>=4)
						if(word[i-1]=='r'&& word[i-2]=='o'&&word[i-3]=='t'&& word[i-4]=='a')
						{
							int k=m(word,i-4);
							if (k>0)
							{
								word[i-2]='e';
								i-=1;
							}
						}
						break;
		case 's':
			if (i>=5)
				if(word[i-1]=='m'&& word[i-2]=='s'&&word[i-3]=='i'&& word[i-4]=='l'&& word[i-5]=='a')
				{
					int k=m(word,i-5);
					if(k>0)
						i-=3;
				}
				if (i>=7)
					if(word[i-1]=='s'&& word[i-2]=='s'&&word[i-3]=='e'&& word[i-4]=='n'&& word[i-5]=='e'&& word[i-6]=='v'&& word[i-7]=='i')
					{
						int k=m(word,i-7);
						if (k>0)
							i-=4;
					}
					if (i>=7)
						if(word[i-1]=='s'&& word[i-2]=='s'&&word[i-3]=='e'&& word[i-4]=='n'&& word[i-5]=='l'&& word[i-6]=='u'&& word[i-7]=='f')
						{
							int k=m(word,i-7);
							if(k>0)
								i-=4;
						}
						if (i>=7)
							if(word[i-1]=='s'&& word[i-2]=='s'&&word[i-3]=='e'&& word[i-4]=='n'&& word[i-5]=='s'&& word[i-6]=='u'&& word[i-7]=='o')
							{
								int k=m(word,i-7);
								if (k>0)
									i-=4;
							}
							break;
		case 't':
			if (i>=5)
				if(word[i-1]=='i'&& word[i-2]=='t'&&word[i-3]=='i'&& word[i-4]=='l'&& word[i-5]=='a')
				{
					int k=m(word,i-7);
					if (k>0)
						i-=3;
				}
				if (i>=5)
					if(word[i-1]=='i'&& word[i-2]=='t'&&word[i-3]=='i'&& word[i-4]=='v'&& word[i-5]=='i')
					{
						int k=m(word,i-5);
						if (k>0)
						{
							word[i-3]='e';
							i-=2;
						}
					}
					if (i>=6)
						if(word[i-1]=='i'&& word[i-2]=='t'&&word[i-3]=='i'&& word[i-4]=='l'&& word[i-5]=='i' && word[i-6]=='b')
						{
							int k=m(word,i-6);
							if (k>0)
							{
								word[i-5]='l';
								word[i-4]='e';
								i-=3;
							}
						}
						break;

		default:
			break;
	}
	////////////////////////////////////////////Step 4: Deals with suffixes
	switch (word[i-1])
	{
		int k;
	case 'e':
		if(word[i-1]=='e'&& word[i-2]=='t'&&word[i-3]=='a'&& word[i-4]=='c'&& word[i-5]=='i')
		{
			k=m(word,i-5);
			if (k>0)
				i-=3;
		}
		if (i>=5)
			if(word[i-1]=='e'&& word[i-2]=='v'&&word[i-3]=='i'&& word[i-4]=='t'&& word[i-5]=='a')
			{
				k=m(word,i-5);
				if (k>0)
					i-=5;
			}
			if (i>=5)
				if(word[i-1]=='e'&& word[i-2]=='z'&&word[i-3]=='i'&& word[i-4]=='l'&& word[i-5]=='a')
				{
					k=m(word,i-5);
					if (k>0)
						i-=3;
				}
				break;
	case 'i':
		if (i>=5)
			if(word[i-1]=='i'&& word[i-2]=='t'&&word[i-3]=='i'&& word[i-4]=='c'&& word[i-5]=='i')
			{
				k=m(word,i-5);
				if (k>0)
					i-=3;
			}
	case 'l':
		if (i>=4)
			if(word[i-1]=='l'&& word[i-2]=='a'&&word[i-3]=='c'&& word[i-4]=='i')
			{
				k=m(word,i-4);
				if (k>0)
					i-=2;
			}
			if(word[i-1]=='l'&& word[i-2]=='u'&&word[i-3]=='f')
			{
				k=m(word,i-3);
				if (k>0)
					i-=3;
			}
			break;
	case 's':
		/*if (i>=5)
			if(word[i-1]=='s'&& word[i-2]=='s'&&word[i-3]=='e'&& word[i-4]=='n'&& word[i-5]=='e')
			{
				k=m(word,i-5);
				if (k>0)
					i-=5;
			}*/
		if (i>=4)
			if(word[i-1]=='s'&& word[i-2]=='s'&&word[i-3]=='e'&& word[i-4]=='n')
			{
				k=m(word,i-4);
				if (k>0)
					i-=4;
			}
			break;
	}
	/////////////////Step 5: Takes off-ant,-ence,etc
	if (i>=2)
		switch (word[i-2])
	{
		case 'a':
			if (i>=2)
				if (word[i-1]=='l' && word[i-2]=='a')
				{
					index=i-2;
					break;
				}
				break;

		case 'c':
			if (i>=4)
				if (word[i-1]=='e' && word[i-2]=='c' && word[i-3]=='n' && word[i-4]=='a')
				{
					index=i-4;
					break;
				}
				if (i>=4)
					if (word[i-1]=='e' && word[i-2]=='c' && word[i-3]=='n' && word[i-4]=='e')
					{
						index=i-4;
						break;
					}
					break;

		case 'e':
			if (i>=2)
				if (word[i-1]=='r' && word[i-2]=='e')
				{
					index=i-2;
					break;
				}
				break;

		case 'i':
			if (i>=2)
				if (word[i-1]=='c' && word[i-2]=='i')
				{
					index=i-2;
					break;
				}
				break;

		case 'l':
			if (i>=4)
				if (word[i-1]=='e' && word[i-2]=='l' && word[i-3]=='b' && word[i-4]=='a')
				{
					index=i-4;
					break;
				}
				if (i>=4)
					if (word[i-1]=='e' && word[i-2]=='l' && word[i-3]=='b' && word[i-4]=='i')
					{
						index=i-4;
						break;
					}
					break;

					/*	if (word[i-1]=='i')
					{
					index=i-2;
					break;
					}*/
		case 'n':
			if (word[i-1]=='t' && word[i-2]=='n' && word[i-3]=='a')
			{
				index=i-3;
				break;
			}
			if (word[i-1]=='t' && word[i-2]=='n' && word[i-3]=='e' && word[i-4]=='m' && word[i-5]=='e')
			{
				index=i-5;
				break;
			}
			if (word[i-1]=='t' && word[i-2]=='n' && word[i-3]=='e' && word[i-4]=='m')
			{
				index=i-4;
				break;
			}
			if (word[i-1]=='t' && word[i-2]=='n' && word[i-3]=='e' )
			{
				index=i-3;
				break;
			}
			break;

		case 'o':
			if (word[i-1]=='u' && word[i-2]=='o')
			{
				index=i-2;
				break;
			}
			if (word[i-1]=='n' && word[i-2]=='o' && word[i-3]=='i' && word[i-4]=='s' )
			{
				index=i-3;
				break;
			}
			if (word[i-1]=='n' && word[i-2]=='o' && word[i-3]=='i' && word[i-4]=='t' )
			{
				index=i-3;
				break;
			}
			if (word[i-1]=='u' && word[i-2]=='o')
			{
				index=i-2;
				break;
			}
			break;

		case 's': 
			if (word[i-1]=='m' && word[i-2]=='s' && word[i-3]=='i')
			{
				index=i-3;
			}
			break;
		case 't':
			if (word[i-1]=='e'&& word[i-2]=='t'&& word[i-3]=='a')
			{
				index=i-3;
				break;
			}
			if (word[i-1]=='i'&& word[i-2]=='t'&& word[i-3]=='i')
			{
				index=i-3;
			}
			break;

		case 'u':
			if (word[i-1]=='s' && word[i-2]=='u' && word[i-3]=='o')
			{
				index=i-3;
			}
			break;

		case 'v':
			if (i>=3)
				if (word[i-1]=='e' && word[i-2]=='v' && word[i-3]=='i')
				{
					index=i-3;
				}
				break;

				/////////////////////////////////////Adding New Rules


		case 'z': 
			if (word[i-1]=='e' && word[i-2]=='z' && word[i-3]=='i')
			{
				index=i-3;
			}
			break;


	}
	if (index!=0)
	{
		int k=m(word,index);
		int temp=0;
		if (k>1)
		{
			int temp=index;
			for (index;index<i;index++)
				word[index]='\0';
			i=temp;
		}		
	}
	//////////////////////////////Step 6: Removing a final-e
	if (word[i-1]=='e' && !status)
	{
		int k=m(word,i);
		if (k>1)
		{
			i--;
		}
		bool con=IsCVC(word,i-1);
		if(k==1 && !con)
		{
			i--;
		}
	}
	if (word[i-1]=='l' && word[i-2]==word[i-1])
	{
		int k=0;
		for (int j=0;j<i-1;j++)
		{

			if (word[j]=='a'||word[j]=='e'||word[j]=='i'||word[j]=='o'||word[j]=='u')
				if (word[j+1]!='a' && word[j+1]!='e'&& word[j+1]!='i' && word[j+1]!='o' && word[j+1]!='u')
				{ 
					k++;
				}
		}
		if (k>1)
		{
			i--;
		}
	}
	for (int j=i;j<length;j++)
		word[j]='\0';

	return word;
}
bool IsCVC(char *word,int pos)
{
	int k=0;
	bool CVC=false;
	if (pos>=3)
	{
		if (word[pos-1]!='a'&& word[pos-1]!='e'&& word[pos-1]!='i'&&word[pos-1]!='o'&&word[pos-1]!='u'&& word[pos-1]!='w' &&word[pos-1]!='x' &&word[pos-1]!='y' )
			if (word[pos-2]=='a'||word[pos-2]=='e'||word[pos-2]=='i'||word[pos-2]=='o'||word[pos-2]=='u')
				if (word[pos-3]!='a'&& word[pos-3]!='e'&& word[pos-3]!='i'&&word[pos-3]!='o'&&word[pos-3]!='u' )
					CVC=true;
		return CVC;		
	}
	else 
		return false;
}

int m(char *word,int pos)
{
	if (pos>=2)
	{

		int k=0;
		for (int j=0;j<pos-1;j++)
		{

			if (word[j]=='a'||word[j]=='e'||word[j]=='i'||word[j]=='o'||word[j]=='u'||word[j]=='y')
				if (word[j+1]!='a' && word[j+1]!='e'&& word[j+1]!='i' && word[j+1]!='o' && word[j+1]!='u')
				{ 
					k++;
				}
		}
		return k;
	}
	else 
		return 0;
}