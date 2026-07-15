#include "filesystem"
#include "Simulator.h"

void run_tests() {
	std::vector<int> test_vector = {0,1,2,3,4,5};
	std::filesystem::path test_dir(TEST_DIR);

	Simulator simulator;
	for (auto test_number : test_vector) {
		auto input_path = test_dir / ("test_" + std::to_string(test_number) + ".txt");
		auto output_path = test_dir / ("test_" + std::to_string(test_number) + "_output.txt");

		simulator.loadCircuit(input_path);
		simulator.simulate(output_path);
	}
}

int main() {

	run_tests();
	return 0;
}