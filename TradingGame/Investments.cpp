#include "Investments.h"


void Investments::init(std::string name, float startPrice, float minPrice, float maxPrice) {
	this->name = name;
	this->minPrice = minPrice;
	price.push_back(startPrice);
	vol.push_back(20000 + static_cast <int> (rand()) / (static_cast <int> (RAND_MAX / (40000 - 20000))));
	for (int i = 0; i < 62; i++) {
		price.push_back(randomPrice());

		vol.push_back(20000 + static_cast <int> (rand()) / (static_cast <int> (RAND_MAX / (40000 - 20000))));
	}
}

void Investments::newPrice() {
	price.erase(price.begin());
	price.push_back(randomPrice());

	vol.erase(vol.begin());
	vol.push_back(20000 + static_cast <int> (rand()) / (static_cast <int> (RAND_MAX / (40000 - 20000))));
}

float Investments::randomPrice() {
	float volatility = 2 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (10 - 2)));
	//float volatility = 2;

	float rnd = 0.01f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1.f - 0.01f)));

	float change_percent = 2 * volatility * rnd;
	if (change_percent > volatility)
		change_percent -= (2 * volatility);

	float change_amount = price.back() * change_percent / 100;
	float new_price = price.back() + change_amount;

	if (new_price < minPrice) {
		new_price += std::abs(change_amount) * 2;
	}

	return new_price;
}

std::vector<float> Investments::getPrice() {
	return this->price;
}

std::vector<int> Investments::getVol() {
	return this->vol;
}

std::string Investments::getName()
{
	return this->name;
}


