#include <cmath>
#include <cstdint>
#include <iostream>
#include <vector>
#include <algorithm>

uint32_t multiplication_table[10][10];

int main() {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			multiplication_table[i][j] = i * j;
		}
	}

	std::string x, y;
	std::cin >> x >> y;
	bool is_negative = true;
	if (x[0] == '-' && y[0] == '-') {
		is_negative = false;
		x = x.substr(1, x.size());
		y = y.substr(1, y.size());
	} else if (x[0] == '-') {
		x = x.substr(1, x.size());
	} else if (y[0] == '-') {
		y = y.substr(1, y.size());
	} else {
		is_negative = false;
	}
	if (x.size() < y.size()) {
		std::swap(x, y);
	}
	std::cout << x << " x " << y << "\n";


	// Build partial sums
	// Both partial sums building and adding is done in reverse, it's just easier
	std::vector<std::string> partial_sums {};
	partial_sums.resize(y.size());
	for (int64_t multiplier_index = y.size() - 1;
	     multiplier_index >= 0;
	     multiplier_index--) {
		int32_t carry = 0;
		int32_t current_num = 0;
		int64_t adjusted_index = y.size() - 1 - multiplier_index;
		for (int64_t multiplicand_index = x.size() - 1;
		     multiplicand_index >= 0;
		     multiplicand_index--) {
			current_num = multiplication_table[x[multiplicand_index] - '0'][y[multiplier_index] - '0'];
			if (carry > 0) current_num += carry;
			if (current_num > 9) {
				partial_sums[adjusted_index].push_back(current_num % 10 + '0');
				if (multiplicand_index == 0) {
					partial_sums[adjusted_index].push_back(current_num / 10 + '0');
					break;
				} else {
					carry = current_num / 10;
				}
			} else {
				partial_sums[adjusted_index].push_back(current_num + '0');
				carry = 0;
			}
		}
		std::reverse(partial_sums[adjusted_index].begin(),
			     partial_sums[adjusted_index].end());
	}

	// Sum them up
	auto number_of_partial_sums = partial_sums.size();
	std::string final_sum;
	final_sum.resize(x.size() + y.size());
	final_sum[0] = '\0';
	int64_t current_num = 0;
	int64_t final_sum_index = 0;
	for (int64_t i = 0; i < number_of_partial_sums; i++) {
		final_sum_index = i;
		int64_t carry = 0;
		for (int64_t j = partial_sums[i].size() - 1; j >= 0; j--) {
			current_num = final_sum[final_sum_index] + (partial_sums[i][j] - '0') + carry;
			if (current_num > 9) {
				final_sum[final_sum_index] = current_num % 10;
				if (j == 0) {
					final_sum[final_sum_index + 1] = current_num / 10; 
					break;
				}
				carry = current_num / 10;
			} else {
				final_sum[final_sum_index] = current_num;
				carry = 0;
			}
			final_sum_index++;
		}
	}
	std::reverse(final_sum.begin(), final_sum.begin() + final_sum_index);
	for (int64_t i = 0; i < final_sum_index; i++) final_sum[i] += '0';
	std::cout << (is_negative ? "-" : "") << std::string {final_sum.begin(), final_sum.begin() + final_sum_index} << "\n";
}
