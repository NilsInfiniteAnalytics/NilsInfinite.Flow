#include "pch.h"
#include "CppUnitTest.h"
#include "CartesianGrid.h"

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

		static CartesianGrid<double, 2>* Grid2D;
		static CartesianGrid<double, 3>* Grid3D;

		TEST_CLASS_INITIALIZE(ClassInitialize)
		{
			Grid2D = new CartesianGrid(RESOLUTION_2D, DOMAIN_SIZE_2D);
			Grid3D = new CartesianGrid(RESOLUTION_3D, DOMAIN_SIZE_3D);
		}

		TEST_CLASS_CLEANUP(ClassCleanup)
		{
			delete Grid2D;
			delete Grid3D;
		}

		TEST_METHOD(Test_ValidNodeIndices2D_Success)
		{
			Assert::AreEqual(Grid2D->GetNodeIndex({ 0, 0 }), static_cast<size_t>(0), L"Index (0,0) should map to 0");
		}
	};

	CartesianGrid<double, 2>* GridTest::Grid2D = nullptr;
	CartesianGrid<double, 3>* GridTest::Grid3D = nullptr;
}
