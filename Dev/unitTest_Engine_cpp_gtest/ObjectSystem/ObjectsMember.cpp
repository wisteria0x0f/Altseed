﻿#include <gtest/gtest.h>
#include <Altseed.h>
#include <memory>
#include "../EngineTest.h"

using namespace std;
using namespace asd;

class ObjectSystem_ObjectsMember : public EngineTest
{
public:
	ObjectSystem_ObjectsMember(bool isOpenGLMode)
		: EngineTest(asd::ToAString("ObjectsMember"), isOpenGLMode, 30)
	{
	}

protected:
	void OnStart()
	{
		auto object = make_shared<TextureObject2D>();

		object->SetPosition(Vector2DF(10, 20));
		ASSERT_TRUE(object->GetPosition() == Vector2DF(10, 20));

		object->SetAngle(90);
		ASSERT_FLOAT_EQ(object->GetAngle(), 90);

		object->SetScale(Vector2DF(2, 3));
		ASSERT_TRUE(object->GetScale() == Vector2DF(2, 3));

		object->SetCenterPosition(Vector2DF(101, 102));
		ASSERT_TRUE(object->GetCenterPosition() == Vector2DF(101, 102));

		object->SetColor(Color(128, 127, 126, 125));
		ASSERT_EQ(object->GetColor().R, 128);
		ASSERT_EQ(object->GetColor().G, 127);
		ASSERT_EQ(object->GetColor().B, 126);
		ASSERT_EQ(object->GetColor().A, 125);

		object->SetDrawingPriority(1);
		ASSERT_EQ(object->GetDrawingPriority(), 1);

		object->SetTurnLR(false);
		ASSERT_EQ(object->GetTurnLR(), false);

		object->SetTurnUL(false);
		ASSERT_EQ(object->GetTurnUL(), false);

		auto g = asd::Engine::GetGraphics();
		object->SetTexture(g->CreateTexture2D(ToAString("Data/Texture/Cloud1.png").c_str()));
		ASSERT_NE(object->GetTexture(), nullptr);
	}
};

ENGINE_TEST(ObjectSystem, ObjectsMember)
