#include <iostream>
#include <string>
#include <vector>
#include <chrono>

template <class T>
std::string findChars(std::string& str1, std::string& str2, std::vector<T>& matrix) {

	size_t str1S = str1.length();
	size_t str2S = str2.length();

	if (str1S * str2S == 0)
		return "";

	std::string tmp = str1.substr(0, str1S - 1);
	std::string tmp2 = str2.substr(0, str2S - 1);

	if (str1[str1S - 1] == str2[str2S - 1]) {
		return findChars(tmp, tmp2, matrix) + str1[str1S - 1];
	}

	return(
		(matrix[str2S][str1S - 1] > matrix[str2S - 1][str1S])
		? findChars(tmp, str2, matrix)
		: findChars(str1, tmp2, matrix)
		);
}


std::string calculateLCS(std::string& str1, std::string& str2) {

	std::vector<std::vector<size_t>> myVector;
	myVector.reserve(str2.length() + 1);
	std::vector<size_t> myRow(str1.length() + 1, 0);

	for (size_t i = 0; i <= str2.length(); i++) {
		myVector.emplace_back(myRow);
		myVector[i].reserve(str1.length() + 1);
	}

	for (size_t i = 1; i < myVector.size(); i++) {
		for (size_t j = 1; j < myVector[i].size(); j++) {
			myVector[i][j] = (str1[j - 1] == str2[i - 1])
				? myVector[i - 1][j - 1] + 1
				: (myVector[i][j - 1] > myVector[i - 1][j])
				? myVector[i][j - 1]
				: myVector[i - 1][j];
		}
	}

	return findChars(str1, str2, myVector);
}

int main() {

	std::string a, b;
	std::cout << "1st Sentence/Word : "; std::cin >> a;
	std::cout << "2nd Sentence/Word : "; std::cin >> b;

	auto start = std::chrono::high_resolution_clock::now();

	std::cout << "LCS: " << calculateLCS(a, b) << std::endl;

	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> duration = end - start;
	std::cout << "Elapsed time : " << duration.count() << " s\n";
}