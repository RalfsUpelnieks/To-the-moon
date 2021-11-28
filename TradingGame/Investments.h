#pragma once
#include <iostream>
#include <vector>
class Investments {
private:
	std::string name;
	std::vector<float> price;
	std::vector<int> vol;
	float minPrice;

public:

	void init(std::string name, float startPrice, float minPrice, float maxPrice);

	void newPrice();

	float randomPrice();

	std::vector<float> getPrice();
	std::vector<int> getVol();

	std::string getName();

};

