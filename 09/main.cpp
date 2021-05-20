#include "ExternalSort.h"

void DefaultTest() {
	std::string input_name = "input.txt";
	std::ofstream input_file(input_name, std::ios::binary | std::ios::out);
	for (size_t i=0; i < 10000; i++) {
		auto *n = new uint64_t(std::rand() % 100);
		input_file.write(reinterpret_cast<char*>(n), sizeof(uint64_t));
		delete n;
	}
	input_file.close();

	std::string output_name = MergeSortThreaded(input_name);
	std::ifstream fcheck(output_name, std::ios::binary | std::ios::in);
	uint64_t n, pred_n;
	fcheck.read(reinterpret_cast<char*>(&pred_n), sizeof(uint64_t));
	while (!fcheck.eof()) {
		fcheck.read(reinterpret_cast<char*>(&n), sizeof(uint64_t));
		assert(pred_n <= n);
		pred_n = n;
	}
}

int main() {
	DefaultTest();
	std::cout << "Success!" << std::endl;
}