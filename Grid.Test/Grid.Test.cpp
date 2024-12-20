#include "pch.h"
#include "CppUnitTest.h"
#include "Element.h"
#include "CartesianGrid.h"
#include "Mesh.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GridTest
{
	TEST_CLASS(GridTest)
	{
	public:
		static constexpr std::array<size_t, 2> RESOLUTION_2D = { 10, 10 };
		static constexpr std::array<size_t, 3> RESOLUTION_3D = { 10, 10,10 };
		static constexpr std::array<double, 2> DOMAIN_SIZE_2D = { 1.0, 1.0 };
		static constexpr std::array<double, 3> DOMAIN_SIZE_3D = { 1.0, 1.0, 1.0 };
		static constexpr double TOLERANCE = 1e-4;
		static constexpr double ABSOLUTE_TOLERANCE = 1e-12;

		TEST_METHOD_INITIALIZE(TestInitialize)
		{
			Grid2D = std::make_unique<CartesianGrid<double, 2>>(RESOLUTION_2D, DOMAIN_SIZE_2D);
			Grid3D = std::make_unique<CartesianGrid<double, 3>>(RESOLUTION_3D, DOMAIN_SIZE_3D);
		}

		TEST_METHOD_CLEANUP(TestCleanup)
		{
			Grid2D.reset();
			Grid3D.reset();
		}

		TEST_METHOD(Test_ValidNodeIndices2D_Success)
		{
			constexpr size_t numberOf2dNodes = RESOLUTION_2D[0] * RESOLUTION_2D[1];
			Assert::AreEqual(Grid2D->GetNodeIndex({ 0, 0 }), static_cast<size_t>(0), L"Index (0,0) should map to 0");
		}

		TEST_METHOD(Test_DataInitialization2D)
		{
			for (size_t i = 0; i < RESOLUTION_2D[0]; ++i)
			{
				for (size_t j = 0; j < RESOLUTION_2D[1]; ++j)
				{
					Assert::AreEqual((*Grid2D)({ i, j }), 0.0, TOLERANCE, L"Grid data should be initialized to zero.");
				}
			}
		}

		TEST_METHOD(Test_ValidNodeIndices3D_Success)
		{
			constexpr size_t numberOf3dNodes = RESOLUTION_3D[0] * RESOLUTION_3D[1] * RESOLUTION_3D[2];
			Assert::AreEqual(Grid3D->GetNodeIndex({ 0, 0, 0 }), static_cast<size_t>(0), L"Index (0,0,0) should map to 0");
		}

	private:
		std::unique_ptr<CartesianGrid<double, 2>> Grid2D;
		std::unique_ptr<CartesianGrid<double, 3>> Grid3D;
	};
}
