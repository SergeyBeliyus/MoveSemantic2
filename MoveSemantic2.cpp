#include <iostream>
#include <string>

class big_integer {
public:
	std::string _number;
	size_t _size;

	big_integer(std::string s): _number(s), _size(_number.length()) {}

	~big_integer(){}

	big_integer(const big_integer& other) {
		_number = other._number;
		_size = other._size;
	}

	int customCharToInt(char c) {
		// Add your custom conversion logic here
		switch (c) {
		case '1':
			return 1;
		case '2':
			return 2;
		case '3':
			return 3;
		case '4':
			return 4;
		case '5':
			return 5;
		case '6':
			return 6;
		case '7':
			return 7;
		case '8':
			return 8;
		case '9':
			return 9;
		default:
			return 0; // Default conversion
		}
	}

	big_integer& operator=(big_integer&& other) {
		std::swap(_number, other._number);
		std::swap(_size, other._size);
		return *this;
	}

	big_integer& operator+(big_integer other)  {

		size_t size;
		int add = 0;

		if (_size >= other._size) {
			size = other._size;
		}
		else {
			size = _size;
			std::string temp = _number;
			_number = other._number;
			other._number = temp;
			_size = other._size;
			other._size = size;
		}

		size_t i = 0;
		while (i != size){
			int tmp = customCharToInt(_number.at(_size - 1 - i)) + customCharToInt(other._number.at(other._size - 1 - i)) + add;
			if (tmp < 10) {
				_number.replace(_size - 1 - i, 1, std::to_string(tmp));
				add = 0;
			}
			else {
				_number.replace(_size - 1 - i, 1, std::to_string(tmp % 10));
				add = 1;
				if (i == 0) {
					size++;
					_number = std::to_string(add) + _number;
				}
			}
			i++;
		}
		return *this;
	}

	big_integer& operator*(int digit) {

		int size = static_cast<int>(_size - 1);
		int add = 0;

		while (size >= 0) {
			int tmp = customCharToInt(_number.at(size)) * digit + add;
			if (tmp < 10) {
				_number.replace(size, 1, std::to_string(tmp));
				add = 0;
			}
			else {
				_number.replace(size, 1, std::to_string(tmp % 10));
				add = tmp / 10;
				if (size == 0) {
					_size++;
					_number = std::to_string(add) + _number;
				}
			}
			size--;
		}

		return *this;
	}

	friend std::ostream& operator << (std::ostream& out, const big_integer& number) {
		return out << number._number;
	}
};


int main(int argc, char* argv[]) {
	auto number1 = big_integer("114575");
	auto number2 = big_integer("78524");
//	auto result1 = number1 + number2;
	auto result1 = number1 * 9;
	std::cout << result1; // 193099
}