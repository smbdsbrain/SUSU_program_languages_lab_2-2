#define _CRT_SECURE_NO_WARNINGS
#include "cstdio"
#include "iostream"
#include "string"
#include "vector"
#include "sstream"
using namespace std;

int stack[10000];
int si = 0;

struct Stack {
	double *_array;
	int n, i;

	void make_bigger() {
		double *t = _array;
		//delete(t);
		_array = new double[2 * n];
		for (int i = 0; i < n; i++)
			_array[i] = t[i];
		n *= 2;
	}

	Stack() {
		n = 2;
		i = 0;
		_array = NULL;
	}
};

struct Command{
	char *name;
	void(*func)(Stack *);
};

void st_init(Stack *st) {
	st->_array = new double[st->n];
}

void st_pop(Stack *st) {
	st->i--;
}

void st_push(Stack *st, double x) {
	
	if (st->i + 1 == st->n)
	{
		st->make_bigger();
	}

	st->_array[st->i++] = x;
}

double st_top(Stack *st) {
	return st->_array[st->i - 1];
}

void st_replace(Stack *st, double x){
	st->_array[st->i - 1] = x;
}

void st_print(Stack *st) {
	for (int i = 0; i < st->i; i++) {
		cout << st->_array[i] << ' ';
	}
	cout << '\n';
}

void st_sin(Stack *st) {
	st_replace(st, sin(st_top(st)));
}

void st_cos(Stack *st) {
	st_replace(st, cos(st_top(st)));
}


void st_atan(Stack *st) {
	st_replace(st, atan(st_top(st)));
}


void st_tan(Stack *st) {
	st_replace(st, tan(st_top(st)));
}

void st_asin(Stack *st) {
	st_replace(st, asin(st_top(st)));
}

void st_acos(Stack *st) {
	st_replace(st, acos(st_top(st)));
}

void st_pi(Stack *st) {
	st_push(st, acos(-1));
}

void st_clear(Stack *st) {
	st->i = 0;
}

void st_exit(Stack *st) {
	exit(0);
}

void st_plus(Stack *st) {
	double r = st_top(st);
	st_pop(st);
	st_replace(st, st_top(st) + r);
}

void st_sub(Stack *st) {
	double r = st_top(st);
	st_pop(st);
	st_replace(st, st_top(st) - r);
}

void st_mult(Stack *st) {
	double r = st_top(st);
	st_pop(st);
	st_replace(st, st_top(st) * r);
}

void st_div(Stack *st) {
	double r = st_top(st);
	st_pop(st);
	st_replace(st, st_top(st) / r);
}


const int sz_cmds = 13;
Command cmds[sz_cmds];


int main()
{
#ifdef _DEBUG
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
#endif
	

	cmds[0].name = "sin";
	cmds[0].func = &st_sin;

	cmds[1].name = "cos";
	cmds[1].func = &st_cos;

	cmds[2].name = "tan";
	cmds[2].func = &st_tan;

	cmds[3].name = "atan";
	cmds[3].func = &st_atan;

	cmds[4].name = "asin";
	cmds[4].func = &st_asin;

	cmds[5].name = "acos";
	cmds[5].func = &st_acos;

	cmds[6].name = "pi";
	cmds[6].func = &st_pi;

	cmds[7].name = "quit";
	cmds[7].func = &st_exit;

	cmds[8].name = "print";
	cmds[8].func = &st_print;

	cmds[9].name = "clear";
	cmds[9].func = &st_clear;

	cmds[10].name = "+";
	cmds[10].func = &st_plus;

	cmds[11].name = "-";
	cmds[11].func = &st_sub;

	cmds[11].name = "*";
	cmds[11].func = &st_mult;

	cmds[12].name = "/";
	cmds[12].func = &st_div;


	Stack st;
	st_init(&st);
	string l_str;
	while (getline(cin, l_str)) {
		stringstream ss = stringstream(l_str);
		string t;
		while (ss >> t)
		{
			bool is_digest = true;
			for (int i = 0; i < sz_cmds; i++)
				if (cmds[i].name == t) {
					(cmds[i].func)(&st);
					is_digest = false;
				}
			if (is_digest)
			{
				stringstream ss_i = stringstream(t);
				double d;
				ss_i >> d;
				st_push(&st, d);
			}

			st_print(&st);
		}
	}

	return 0;
}