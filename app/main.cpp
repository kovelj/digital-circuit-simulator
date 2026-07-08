#include "Simulator.h"

void run_tests() {
	std::vector<int> test_vector = {0,1,2,3,4,5};
	
	Simulator simulator;
	for (const auto test_number : test_vector) {
		simulator.loadCircuit("../test/test_" + std::to_string(test_number) + ".txt");
		simulator.simulate("../test/test_" + std::to_string(test_number) + "_output.txt");
	}
}

int main() 
{
	run_tests();
	return 0;
}