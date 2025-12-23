#pragma once

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Drawing;

#include <cmath>
#include <algorithm>

namespace CppCLRWinFormsProject {

	public ref class ClassData {
	public:
		int Id;
		String^ Name;
		Color ClassColor;
		List<Point>^ Points;

		ClassData(int id, String^ name, Color color) {
			Id = id;
			Name = name;
			ClassColor = color;
			Points = gcnew List<Point>();
		}
	};

	public ref class PointData {
	public:
		int ClassId;
		int PointIndex;
		float X;
		float Y;

		PointData(int classId, int pointIndex, float x, float y) {
			ClassId = classId;
			PointIndex = pointIndex;
			X = x;
			Y = y;
		}
	};

} 