#pragma once
#include "CartesianGrid.h"
#include "Element.h"

template <typename T, size_t Dimensions>
class Mesh
{
	static_assert(Dimensions == 2 || Dimensions == 3, "Only 2D or 3D meshes are supported");

public:
	explicit Mesh(CartesianGrid<T, Dimensions>& grid)
		: Grid(grid)
	{
		GenerateElements();
	}

	const std::vector<Element<T, Dimensions>>& GetElements() const
	{
		return Elements;
	}

private:
	CartesianGrid<T, Dimensions>& Grid;
	std::vector<Element<T, Dimensions>> Elements;

	void GenerateElements()
	{
		const auto& resolution = Grid.Resolution;
		for (size_t i = 0; i < resolution[0] - 1; ++i)
		{
			for (size_t j = 0; j < resolution[1] - 1; ++j)
			{
				if constexpr (Dimensions == 2)
				{
					Elements.emplace_back(std::initializer_list<size_t>{
						Grid.GetNodeIndex({ i, j }),
							Grid.GetNodeIndex({ i + 1, j }),
							Grid.GetNodeIndex({ i, j + 1 }),
							Grid.GetNodeIndex({ i + 1, j + 1 })
					});
				}
				else if constexpr (Dimensions == 3)
				{
					for (size_t k = 0; k < resolution[2] - 1; ++k)
					{
						Elements.emplace_back(std::initializer_list<size_t>{
							Grid.GetNodeIndex({ i, j, k }),
								Grid.GetNodeIndex({ i + 1, j, k }),
								Grid.GetNodeIndex({ i, j + 1, k }),
								Grid.GetNodeIndex({ i + 1, j + 1, k }),
								Grid.GetNodeIndex({ i, j, k + 1 }),
								Grid.GetNodeIndex({ i + 1, j, k + 1 }),
								Grid.GetNodeIndex({ i, j + 1, k + 1 }),
								Grid.GetNodeIndex({ i + 1, j + 1, k + 1 })
						});
					}
				}

			}
		}
	}

};