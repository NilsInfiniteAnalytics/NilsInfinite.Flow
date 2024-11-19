#pragma once
#include <vector>
#include <array>
#include <cmath>
#include <stdexcept>

template <typename T, size_t Dimensions>
class CartesianGrid
{
	static_assert(Dimensions == 2 || Dimensions == 3, "Only 2D or 3D grids are supported");

public:
	CartesianGrid(std::array<size_t, Dimensions> resolution, std::array<T, Dimensions> domainSize)
		: Resolution(resolution), DomainSize(domainSize)
	{
		ComputeGridSpacing();
		InitializeData();
	}

	size_t GetNodeIndex(const std::array<size_t, Dimensions>& indices) const
	{
		size_t index = 0;
		size_t multiplier = 1;
		for (size_t i = 0; i < Dimensions; i++)
		{
			if (indices[i] >= Resolution[i])
			{
				throw std::out_of_range("Index out of range");
			}
			index += indices[i] * multiplier;
			multiplier *= Resolution[i];
		}
		return index;
	}

	T& operator()(const std::array<size_t, Dimensions>& indices)
	{
		return Data[GetNodeIndex(indices)];
	}

	T& operator()(const std::array<size_t, Dimensions>& indices) const
	{
		return Data[GetNodeIndex(indices)];
	}

private:
	std::array<size_t, Dimensions> Resolution;
	std::array<T, Dimensions> DomainSize;
	std::array<T, Dimensions> GridSpacing;
	std::vector<T> Data;

	void ComputeGridSpacing()
	{
		for (size_t i = 0; i < Dimensions; i++)
		{
			GridSpacing[i] = DomainSize[i] / static_cast<T>(Resolution[i] - 1);
		}
	}

	void InitializeData()
	{
		size_t totalNodes = 1;
		for (size_t i = 0; i < Dimensions; i++)
		{
			totalNodes *= Resolution[i];
		}
		Data.resize(totalNodes, T{});
	}
};

