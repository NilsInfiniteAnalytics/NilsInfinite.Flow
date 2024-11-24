#pragma once
#include <vector>
#include <stdexcept>
#include <optional>

template <typename T, size_t Dimensions>
class Element
{
	static_assert(Dimensions == 2 || Dimensions == 3, "Only 2D or 3D elements are supported");

public:
	explicit Element(const std::initializer_list<size_t> nodeIndices, const bool isActive = true)
		: NodeIndices(nodeIndices), IsActive(isActive)
	{
		if (NodeIndices.size() != (Dimensions == 2 ? 4 : 8))
		{
			throw std::invalid_argument("Incorrect number of node indices for the element");
		}
	}

	[[nodiscard]] size_t GetNodeIndex(const size_t localIndex) const
	{
		if (localIndex >= NodeIndices.size())
		{
			throw std::out_of_range("Index out of range");
		}
		return NodeIndices[localIndex];
	}

	void SetNeighbor(size_t direction, size_t neighborIndex)
	{
		if (direction >= Neighbors.size())
			throw std::out_of_range("Invalid neighbor direction");
		Neighbors[direction] = neighborIndex;
	}

	[[nodiscard]] std::optional<size_t> GetNeighbor(size_t direction) const
	{
		if (direction >= Neighbors.size())
			throw std::out_of_range("Invalid neighbor direction");
		return Neighbors[direction];
	}

	[[nodiscard]] bool IsElementActive() const
	{
		return IsActive;
	}

	void SetElementActive(const bool isActive)
	{
		IsActive = isActive;
	}

	void SetVolume(T volume)
	{
		Volume = volume;
	}

	T GetVolume() const
	{
		return Volume;
	}

private:
	std::vector<size_t> NodeIndices;
	bool IsActive;
	T Volume{};
	std::array<std::optional<size_t>, Dimensions * 2> Neighbors;
};