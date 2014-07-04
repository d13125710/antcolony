#pragma once
class AntWalkedWay
{
	std::vector<int> antway_vecctor;
    double distance;
public:
	AntWalkedWay(std::vector<int> &way_vector, double distance)
	{
		antway_vecctor = way_vector;
        this->distance = distance;
	}

	double getDistance()
	{
		return  this->distance;
	}
	std::vector<int>& getWay()
	{
		return this->antway_vecctor;
	}

	~AntWalkedWay(void)
	{
	}
};

