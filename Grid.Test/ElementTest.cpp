#include "pch.h"
#include "CppUnitTest.h"
#include "Element.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GridTest
{
	TEST_CLASS(ElementTest)
	{
	public:
		TEST_METHOD(Test_ElementCreation2D)
		{
			const Element<double, 2> element({ 0, 1, 2, 3 });
			Assert::AreEqual(element.GetNodeIndex(0), static_cast<size_t>(0), L"Node index 0 should be 0");
			Assert::AreEqual(element.GetNodeIndex(1), static_cast<size_t>(1), L"Node index 1 should be 1");
			Assert::AreEqual(element.GetNodeIndex(2), static_cast<size_t>(2), L"Node index 2 should be 2");
			Assert::AreEqual(element.GetNodeIndex(3), static_cast<size_t>(3), L"Node index 3 should be 3");
		}

		TEST_METHOD(Test_ElementCreation3D)
		{
			const Element<double, 3> element({ 0, 1, 2, 3, 4, 5, 6, 7 });
			Assert::AreEqual(element.GetNodeIndex(0), static_cast<size_t>(0), L"Node index 0 should be 0");
			Assert::AreEqual(element.GetNodeIndex(7), static_cast<size_t>(7), L"Node index 7 should be 7");
		}
	};
}
