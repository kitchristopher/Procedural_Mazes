#pragma once
#include<random>
#include <vector>
#include <exception>
#include <functional>

using namespace std;

namespace Utilties
{
	int Random_Int(int min, int max);

	template<class T>
	T Sample_Vector(vector<T>* vectorToSample)
	{
		if (vectorToSample == nullptr || vectorToSample->empty())
		{
			//			cout << "Invalid vector specified!" << endl;
			return nullptr;
		}

		return vectorToSample->at(Random_Int(0, vectorToSample->size() - 1));
	}

	template<class T>
	vector<T> Select_From_Vector(vector<T>* vectorToSelect, std::function<bool(T)> passFunc)
	{
		vector<T> result;

		for (auto it = vectorToSelect->begin(); it != vectorToSelect->end(); it++)
		{
			if (passFunc(*it) == true)
				result.push_back(*it);
		}

		return result;
	}

}