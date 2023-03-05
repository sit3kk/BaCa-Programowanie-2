//Konrad Sitek
#include <string>
#include <cstdarg>
#include <iostream>


void reverseString(std::string& str, short i);
void swapChar(char&, char&);
std::string Sum(int, const std::string*);
std::string Sum(int, ...);
void Sum(std::string*, int, const std::string*);
void Sum(std::string*, int, ...);
void Sum(std::string&, int, ...);
std::string Mult(int, const std::string*);
std::string Mult(int, ...);
void Mult(std::string*, int, const std::string*);
void Mult(std::string*, int, ...);
void Mult(std::string&, int, const std::string*);
void Mult(std::string&, int, ...);
std::string Operation(std::string(*)(int, const std::string*), int, const std::string*);
std::string Operation(std::string(*)(int, const std::string*), int, ...);
void Operation(std::string*, std::string(*)(int, const std::string*), int, ...);
void Operation(std::string*, std::string(*)(int, const std::string*), int, const std::string*);
void Operation(std::string&, void(*)(std::string*, int, const std::string*), int, const std::string*);
void Operation(std::string&, void(*)(std::string*, int, const std::string*), int, ...);


std::string trim(std::string str, bool negative, short i)
{
	if (i == str.length()-1 && str[str.length()-1] == '0') return "0";

	if (str.length() == 1) return str;
	
	if (str[i] == '0' || str[i] == ' ' || str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-') negative = true;

		return trim(str, negative, i + 1);
	}

	if (negative) return '-' + str.substr(i, str.length());
	return str.substr(i, str.length());

}

void swapString(std::string& a, std::string& b)
{
	std::string tmp;
	tmp = a;
	a = b;
	b = tmp;


}

void swapChar(char& a, char& b)
{
	char tmp;
	tmp = a;
	a = b;
	b = tmp;

}

void reverseString(std::string& str, short i = 0)
{
	short n = str.length();

	if (i == n / 2) return;

	swapChar(str[i], str[n - i - 1]);
	reverseString(str, i + 1);

}

void calculateCarry(int& carry,std::string& result,std::string str1,std::string str2,int i, int size)
{
	if (i >= size) return;




	int sum = ((str1[i] - '0') + (str2[i] - '0') + carry);
	result.push_back(sum % 10 + '0');
	carry = sum / 10;

	return calculateCarry(carry, result, str1, str2, i + 1, size);


}

void addRemDig(int& carry, std::string& result, std::string str1, std::string str2, int i, int size)
{
	if (i >= size) return;



	int sum = ((str2[i] - '0') + carry);
	result.push_back(sum % 10 + '0');
	carry = sum / 10;


	return addRemDig(carry, result, str1, str2, i + 1, size);
}

std::string sumStrings(std::string str1, std::string str2)
{
	if (str1.length() > str2.length()) swapString(str1, str2);

	

	std::string result = "";


	int size1 = str1.length();
	int size2 = str2.length();


	reverseString(str1, 0);
	reverseString(str2, 0);


	int carry = 0;

	calculateCarry(carry, result, str1, str2, 0, size1);
	addRemDig(carry, result, str1, str2, size1, size2);


	if (carry) result.push_back(carry + '0');


	reverseString(result);


	return result;

}

bool smaller(std::string str1, std::string str2, int i)
{
	if (str1.length() < str2.length()) return true;
	else if (str2.length() < str1.length()) return false;
	else
	{
		if (str1[i] < str2[i]) return true;
		else if (str2[i] < str1[i]) return false;
		else
		{
			return smaller(str1, str2, i + 1);
		}
	}

}

void traverse(int& carry, std::string& result, std::string str1, std::string str2, int i, int diff)
{

	if (i == -1) return;

	int sub = ((str1[i + diff] - '0') - (str2[i] - '0') - carry);

	if (sub < 0)
	{
		sub = sub + 10;
		carry = 1;
	}
	else carry = 0;

	result.push_back(sub + '0');

	return traverse(carry, result, str1, str2, i - 1, diff);

}

void subtract(int& carry, std::string& result, std::string str1, std::string str2, int i, int diff)
{

	if (i == -1) return;

	if (str1[i] == '0' && carry)
	{
		result.push_back('9');
		return subtract(carry, result, str1, str2, i + -1, diff);
	}

	int sub = ((str1[i] - '0') - carry);
	if (i > 0 || sub > 0) result.push_back(sub + '0');
	carry = 0;



	return subtract(carry, result, str1, str2, i - 1, diff);

}

std::string subString(std::string str1, std::string str2)
{

	if (str1 == str2) return "0";


	if (smaller(str1, str2, 0)) swap(str1, str2);



	std::string result = "";



	int diff = str1.length() - str2.length();
	int carry = 0;


	traverse(carry, result, str1, str2, str2.length() - 1, diff);
	subtract(carry, result, str1, str2, str1.length() - str2.length() - 1, diff);


	

	reverseString(result);
	if (result[0] == '0') return result.substr(1, result.size() - 1);
	return result;

}

std::string mainSum(std::string str1, std::string str2)
{

	str1 = trim(str1,false, 0);
	str2 = trim(str2,false, 0);


	if (str1 == "0") return str2;
	else if (str2 == "0") return str1;
	else if (str1[0] == '-' && str2[0] == '-')
	{
		std::string tmp1 = str1.substr(1, str1.length() - 1);
		std::string tmp2 = str2.substr(1, str2.length() - 1);


		return '-' + sumStrings(tmp1, tmp2);
		
	}
	else if (str1[0] == '-' && str2[0] != '-')
	{
		std::string tmp1 = str1.substr(1, str1.length() - 1);

		if (str2 == tmp1) return "0";
		else if (smaller(tmp1, str2, 0))
		{
			std::string output = subString(str2, tmp1);

			if (output[0] == '0') return output.substr(1, output.length() - 1);
			return output ;
		}
		else if (smaller(str2, tmp1, 0))
		{
			
			std::string output = subString(tmp1, str2);;

			if (output[0] == '0') return '-' + output.substr(1, output.length() - 1);
			return '-'+output;
			

		}
		
	}
	else if (str1[0] != '-' && str2[0] == '-')
	{
		std::string tmp2 = str2.substr(1, str2.length() - 1);


		if (str1 == tmp2) return "0";
		else if (smaller(tmp2, str1, 0))
		{
			std::string output = subString(str1, tmp2);

			if (output[0] == '0') return output.substr(1, output.length() - 1);
			return output;

		}
		else if (smaller(str1, tmp2, 0))
		{
			std::string output = subString(tmp2, str1);

			if (output[0] == '0') return '-' + output.substr(1, output.length() - 1);
			return '-' + output;


		}

	}
	else
	{
		return sumStrings(str1, str2);
	}

}

void loop2(std::string& product, std::string str1, std::string str2, int i, int j)
{
	if (j == -1) return;

	int n = (str1[i] - '0') * (str2[j] - '0') + product[i + j + 1];
	product[i + j + 1] = n % 10;
	product[i + j] += n / 10;


	loop2(product, str1, str2, i, j - 1);
}

void loop1(std::string& product, std::string str1, std::string str2, int i)
{
	if (i == -1) return;
	
	loop2(product, str1, str2, i, str2.length() - 1);

	return loop1(product, str1, str2, i - 1);
}

void loop3(std::string& product, int i)
{
	if (i == product.size()) return;

	product[i] += '0';

	loop3(product, i + 1);
}

std::string multiply(std::string str1, std::string str2)
{



	if (str1 == "0" || str2 == "0") return "0";
	

	std::string product(str1.length() + str2.length(), 0);


	loop1(product,str1,str2,str1.length()-1);

	loop3(product, 0);


	if (product[0] == '0') return product.substr(1);

	return product;

}

std::string mainMultiply(std::string str1, std::string str2)
{

	str1 = trim(str1, false, 0);
	str2 = trim(str2, false, 0);

	if (str1.length() == 0) return str2;
	if (str2.length() == 0) return str1;


	if (str1 == "0" || str2 == "0" || (str1[0] == '-' && str1[1] == '0') || (str2[0] == '-' && str2[1] == '0')) return "0";



	if (str1[0] == '-' && str2[0] == '-') return multiply(str1.substr(1, str1.length() - 1), str2.substr(1, str2.length() - 1));
	else if (str1[0] == '-' && str2[0] != '-') return '-' + multiply(str1.substr(1, str1.length() - 1), str2);
	else if (str1[0] != '-' && str2[0] == '-') return '-' + multiply(str1, str2.substr(1, str2.length() - 1));
	else if (str1[0] != '-' && str2[0] != '-') return multiply(str1, str2);
}


////////////////////Sum/////////////////////


std::string helperSum1(int i, int n, const std::string* arr)
{
	
	if (i == n) return "0";
	else return mainSum(*(arr + i), helperSum1(i + 1, n, arr));
	
	
}

std::string helperSum2(int i, int n, std::va_list args)
{
	if (i == n) return "0";
	else
	{
		std::string tmp = va_arg(args, char*);
		return mainSum(tmp, helperSum2(i+1,n,args));
	}
}

std::string Sum(int n, const std::string* arr)
{
	
	return helperSum1(0,n,arr);

}

std::string Sum(int n, ...)
{
	va_list args;

	va_start(args, n);

	std::string result = helperSum2(0, n, args);

	va_end(args);

	return result;

}

void Sum(std::string* result, int n, const std::string* arr)
{
	*result = Sum(n, arr);
}

void Sum(std::string* result, int n, ...)
{
	std::va_list args;
	va_start(args, n);
	*result = helperSum2(0, n, args);
	va_end(args);
}

void Sum(std::string& result, int n, ...)
{
	std::va_list args;
	va_start(args, n);
	result = helperSum2(0, n, args);
	va_end(args);
}

void Sum(std::string& result, int n, const std::string* arr)
{
	result = helperSum1(0, n, arr);
}


/////////////////Multi///////////////////


std::string helperMult1(int i, int n, const std::string* arr)
{
	if (i == n) return "1";
	else return mainMultiply(*(arr + i), helperMult1(i + 1, n, arr));

}

std::string helperMulti2(int i, int n, std::va_list args)
{
	if (i == n) return "1";
	else
	{
		std::string tmp = va_arg(args, char*);
		return mainMultiply(tmp, helperMulti2(i + 1, n, args));
	}
}

std::string Mult(int n, const std::string* arr)
{

	return helperMult1(0, n, arr);

}

std::string Mult(int n, ...)
{
	std::va_list args;
	va_start(args, n);
	std::string result = helperMulti2(0, n, args);
	va_end(args);
	return result;
}

void Mult(std::string* result, int n, const std::string* arr)
{
	*result = helperMult1(0, n, arr);

}

void Mult(std::string* result, int n, ...)
{
	std::va_list args;
	va_start(args, n);
	*result = helperMulti2(0, n, args);
	va_end(args);
	
}

void Mult(std::string& result, int n, const std::string* arr)
{
	result = helperMult1(0,n,arr);
}

void Mult(std::string& result, int n, ...)
{
	std::va_list args;
	va_start(args, n);
	result = helperMulti2(0, n, args);
	va_end(args);
}


/////////////////Operation/////////////////////

void helperOperation(int i, int n, std::string* arr, std::va_list args)
{
	if (i != n)
	{
		*(arr + i) = static_cast<std::string>(va_arg(args, char*));
		helperOperation(i + 1, n, arr, args);
	}
	
}


std::string Operation(std::string(* f)(int, const std::string*),int n, const std::string* arr)
{
	return f(n, arr);
}

std::string Operation(std::string (*f)(int, const std::string*), int n, ...)
{
	std::va_list args;
	va_start(args, n);
	std::string* arr = new std::string[n];
	helperOperation(0, n, arr, args);
	va_end(args);
	std::string result = f(n, arr);
	delete[] arr;
	return result;
}


void Operation(std::string* result, std::string(* f)(int, const std::string*), int n, ...)
{

	std::va_list args;
	va_start(args, n);
	std::string* arr = new std::string[n];
	helperOperation(0, n, arr, args);
	va_end(args);
	*result = f(n, arr);
	delete[] arr;
	
	
}

void Operation(std::string* result, std::string(* f)(int, const std::string*), int n, const std::string* arr)
{
	*result = f(n, arr);
}

void Operation(std::string& result, void(* f)(std::string*,int,const std::string*), int n , const std::string* arr)
{
	f(&result, n, arr);
}

void Operation(std::string& result, void(* f)(std::string*, int , const std::string*), int n, ...)
{

	std::va_list args; 
	va_start(args, n);
	std::string* arr = new std::string[n];
	helperOperation(0, n, arr, args);
	va_end(args);
	f(&result, n, arr);
	delete[] arr;

}
