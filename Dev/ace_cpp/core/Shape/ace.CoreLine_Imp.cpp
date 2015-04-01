﻿#include "ace.CoreLine_Imp.h"
#include "ace.CoreTriangle_Imp.h"

namespace ace
{
	CoreLine_Imp::CoreLine_Imp()
		:staringPosition(Vector2DF(0, 0))
		, endingPosition(Vector2DF(0, 0))
		, thickness(0)
	{

	}

	Vector2DF CoreLine_Imp::GetStartingPosition() const
	{
		return staringPosition;
	}

	void CoreLine_Imp::SetStartingPosition(Vector2DF startingPosition)
	{
		isNeededUpdating = true;
		isNeededCalcBoundingCircle = true;
		this->staringPosition = startingPosition;
	}

	Vector2DF CoreLine_Imp::GetEndingPosition() const
	{
		return endingPosition;
	}

	void CoreLine_Imp::SetEndingPosition(Vector2DF endingPosition)
	{
		isNeededUpdating = true;
		isNeededCalcBoundingCircle = true;
		this->endingPosition = endingPosition;
	}

	float CoreLine_Imp::GetThickness() const
	{
		return thickness;
	}

	void CoreLine_Imp::SetThickness(float thickness)
	{
		isNeededCalcBoundingCircle = true;
		isNeededUpdating = true;
		this->thickness = thickness;
	}

	ShapeType CoreLine_Imp::GetShapeType() const
	{
		return ShapeType::Line;
	}

#if !SWIG
	void CoreLine_Imp::DivideToTriangles()
	{
		Vector2DF vector = endingPosition - staringPosition;

		if (vector.GetSquaredLength() == 0) return;

		auto binorm = vector;
		{
			auto deg = binorm.GetDegree();
			deg += 90;
			binorm.SetDegree(deg);
			binorm.Normalize();
		}

		auto halfThickness = thickness / 2;

		std::array<Vector2DF, 4> vertexes = { staringPosition + binorm*halfThickness, endingPosition + binorm*halfThickness, endingPosition - binorm*halfThickness, staringPosition - binorm*halfThickness };
		std::array<Vector2DF, 4> uvs = { Vector2DF(0, 0), Vector2DF(0, 0), Vector2DF(0, 0), Vector2DF(0, 0) };

		auto triangle1 = new CoreTriangle_Imp();
		auto triangle2 = new CoreTriangle_Imp();

		for (int j = 0; j < 3; ++j)
		{
			triangle1->SetPointByIndex(vertexes[j], j);
			triangle1->SetUVByIndex(uvs[j], j);

			triangle2->SetPointByIndex(vertexes[(j + 2) % 4], j);
			triangle2->SetUVByIndex(uvs[(j + 2) % 4], j);
		}

		triangles.push_back(triangle1);
		triangles.push_back(triangle2);
	}

	void CoreLine_Imp::CalculateBoundingCircle()
	{
		Vector2DF vector = endingPosition - staringPosition;

		if (vector.GetSquaredLength() == 0) return;

		auto binorm = vector;
		{
			auto deg = binorm.GetDegree();
			deg += 90;
			binorm.SetDegree(deg);
			binorm.Normalize();
		}

		auto halfThickness = thickness / 2;

		std::array<Vector2DF, 4> vertexes = { staringPosition + binorm*halfThickness, endingPosition + binorm*halfThickness, endingPosition - binorm*halfThickness, staringPosition - binorm*halfThickness };

		Vector2DF center = (vertexes[0] + vertexes[1] + vertexes[2] + vertexes[3]) / 4.0f;
		float radius = (vertexes[0] - center).GetLength();

		boundingCircle = culling2d::Circle(culling2d::Vector2DF(center.X, center.Y), radius);

	}
#endif

};