//Konrad Sitek

int length(char* m, int n);
void Insert(char* n, int* m);
void Emplace(char* n, int* m);
void Erase(char* n, int* m);
void Print(int n, char* m);








bool Emptiness(int n)
{
	return n == 0;
	
}

bool Nonempty(int n)
{
	return n != 0;
}


bool Equality(int n, int m)
{
	return n == m;
}

bool Inclusion(int n, int m)
{
	return (n | m) == m;

}

bool Disjoint(int n, int m)
{
	return (n & m) == 0;
	
}

bool Conjunctive(int n, int m)
{
	return (n & m) != 0;
	
}


int length(char* n, int m)
{
	if (*(n + m) == '\0') return m;
	length(n, m + 1);
}

void clear(char* n, int i)
{
	if (*(n + i) != '\0')
	{
		*(n + i) = '\0';
		clear(n, i + 1);

	}
}


void Emplace(char* n, int* m)
{
	*m = 0;
	Insert(n, m);

}



void Insert(char* n, int* m)
{
	static int i = 0;

	if (i < length(n, 0))
	{
		if (*(n + i) != ' ')
		{

			int x = 1;
			if (*(n + i) == '1') x <<= 16;
			if (*(n + i + 1) == '1') x <<= 8;
			if (*(n + i + 2) == '1') x <<= 4;
			if (*(n + i + 3) == '1') x <<= 2;
			if (*(n + i + 4) == '1') x <<= 1;
			i += 4;


			*m = *m | x;
		}

		i++;
		Insert(n, m);
	}
	else i = 0;
	
	
}


void Erase(char* n, int* m)
{

	static int i = 0;

	if (i < length(n, 0))
	{
		if (*(n + i) != ' ')
		{

			int x = 1;
			if (*(n + i) == '1') x <<= 16;
			if (*(n + i + 1) == '1') x <<= 8;
			if (*(n + i + 2) == '1') x <<= 4;
			if (*(n + i + 3) == '1') x <<= 2;
			if (*(n + i + 4) == '1') x <<= 1;
			i += 4;


			*m = ((*m) & (~x));
		}

		i++;
		Erase(n, m);
	}
	else i = 0;
	
	
}



void Print(int n, char* m)
{
	static int i = 31;

	if (i == -1) *(m + length(m, 0) - 1) = '\0';

	if (n == 0)
	{
		i = 31;
		*m = 'e';
		*(m + 1) = 'm';
		*(m + 2) = 'p';
		*(m + 3) = 't';
		*(m + 4) = 'y';
		*(m + 5) = '\0';

	}
	else 
	{
		if (i >= 0)
		{
			if (i == 31) clear(m, 0);

			if (n & (1 << i))
			{
				int x = length(m, 0);
				*(m + x) = ((i / 16) + '0');
				*(m + x + 1) = (((i / 8) % 2) + '0');
				*(m + x + 2) = (((i / 4) % 4 % 2) + '0');
				*(m + x + 3) = (((i / 2) % 8 % 2) + '0');
				*(m + x + 4) = ((i % 2) + '0');
				*(m + x + 5) = ' ';
				*(m + x + 6) = '\0';
			}
			i--;
			Print(n, m);
		}
		else i = 31;
		
	}
	
		
}

bool Member(char* n , int m)
{
	static int i = 0;
	if (i < length(n, 0))
	{
		if (*(n + i) != ' ')
		{
			int x = 1;
			if (*(n + i) == '1') x <<= 16;
			if (*(n + i + 1) == '1') x <<= 8;
			if (*(n + i + 2) == '1') x <<= 4;
			if (*(n + i + 3) == '1') x <<= 2;
			if (*(n + i + 4) == '1') x <<= 1;
			i = 0;
			return (x & m);
		}
		i++;
		return Member(n, m);
	}
	else return false;
	
	
}

void Union(int n, int m, int* l)
{
	*l = (n | m);
}

void Intersection(int n, int m, int* l)
{
	*l = (n & m);
}


void Symmetric(int n, int m, int* l)
{
	*l = (n ^ m);
}

void Difference(int n, int m, int* l)
{
	*l = ((~m) & n);
}

void Complement(int n, int* m)
{
	*m = (~n);
}


int helper(int n, int i)
{
	if (i < 32)
	{
		if (n&(1 << i)) return (helper(n, i + 1) + 1);

		return helper(n, i + 1);
	}
	return 0;
}

int Cardinality(int n)
{
	if (n == 0) return 0;
	return helper(n, 0);
}

bool LessThen(int n, int m)
{
	if (Cardinality(n) == Cardinality(m)) return n < m;
	return Cardinality(n) < Cardinality(m);
}

bool LessEqual(int n, int m)
{
	if (Cardinality(n) == Cardinality(m)) return n <= m;
	return Cardinality(n) < Cardinality(m);
}

bool GreatEqual(int n, int m)
{

	return !LessThen(n, m);
}

bool GreatThen(int n, int m)
{
	return !LessEqual(n, m);
}

