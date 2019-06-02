#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>
#include <math.h>

#define MAXNUM	1001

using namespace std;

class Number { // includes Integer range

public:

	int arr[MAXNUM];
	int how_many_digit;

	int start_idx; // idx which starts number

	bool is_minus;

	Number(int num) {

		int idx = MAXNUM - 1;
		int temp_num = num < 0 ? -num : num;
		how_many_digit = 0;

		while (temp_num) {

			arr[idx--] = temp_num % 10;
			temp_num /= 10;

			how_many_digit++;
		}

		start_idx = idx + 1;

		for (; idx >= 0; idx--)
			arr[idx] = 0;

		if (num == 0)
			how_many_digit = 1;

		is_minus = num < 0 ? true : false;
	}

	Number(const Number& Num,bool minus_flag) {

		how_many_digit = Num.how_many_digit;
		start_idx = Num.start_idx;

		if (Num.is_minus == true)
			is_minus = (minus_flag == true ? false : true);
		else
			is_minus = (minus_flag == true ? true : false);

		for (int i = 0; i < MAXNUM; i++) {
			arr[i] = 0;

			if (i == Num.start_idx) {
				for (int j = i; j < MAXNUM; j++)
					arr[j] = Num.arr[j];
				break;
			}
		}

	}

	void print_number() {

		if (is_minus == true)
			printf("-");

		for(int i=start_idx;i<MAXNUM;i++)
				printf("%d", arr[i]);
		printf("\n");
	}

	int get_number() { // if number is not out of range in int

		int value = 0, cnt = 0;

		for (int j = MAXNUM - 1; j > MAXNUM - 11; j--) {

			value += (pow(10, cnt) * arr[j]);
			cnt++;
		}

		return (is_minus == true ? -value : value);
	}

	bool operator>(Number Num) {

		if (is_minus == true && Num.is_minus == false)
			return false;
		else if (is_minus == false && Num.is_minus == true)
			return true;
		else {

			if (how_many_digit > Num.how_many_digit)
				return (is_minus == false ? true : false);
			else if (how_many_digit < Num.how_many_digit)
				return (is_minus == false ? false : true);
			else {

				for (int i = start_idx; i < MAXNUM - 1; i++)
					if (arr[i] > Num.arr[i])
						return true;
					else if (arr[i] < Num.arr[i])
						return false;

				// if they are same
			}

		}

	}

	Number& operator+(Number Num) {

		if (is_minus != Num.is_minus)
			return this->operator-(Num);
		else {
		
			int carry = 0, value, rem;
			Number result(0);

			result.is_minus = is_minus;

			for (int i = MAXNUM - 1; i >= 0; i--) {

				rem = (arr[i] + Num.arr[i] + carry) % 10;
				value = arr[i] + Num.arr[i] + carry;

				result.arr[i] = rem;

				carry = (value >= 10 ? 1 : 0);
			}

			if (result.arr[start_idx - 1] != 0) {
				result.how_many_digit = how_many_digit + 1;
				result.start_idx = start_idx - 1;
			}
			else {
				result.how_many_digit = how_many_digit;
				result.start_idx = start_idx;
			}

			return result;
		}

	}

	Number& operator*(Number Num) {

		int times = Num.get_number();
		times = (Num.is_minus == true ? -times : times);

		Number result(0);

		result.is_minus = (this->is_minus != Num.is_minus ? true : false);

		for (int i = 0; i < times; i++)
			result = result.operator+(*this);

		return result;
	}

	Number& operator-(Number Num) {

		if (is_minus == false && Num.is_minus == true)
			return this->operator+(Num);





	}

	void operator/(Number Num) {





	}

};


int main(void)
{
	int N, M;
	//scanf("%d %d", &N, &M);

	//for (int k = 1; k <= M; k++) {
	//}

	Number num1(-1477), num2(-2580);

	//Number result = (num1.operator+(num2),false);
	//result.print_number();

	//if (num2.operator>(num1))
	//	printf("num1 is bigger");

	Number result(num2, true);
	result.print_number();

	Number result2 = num1.operator*(num2);
	result2.print_number();

	return 0;
}