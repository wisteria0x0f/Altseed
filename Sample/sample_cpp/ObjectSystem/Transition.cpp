
#include <Base.h>

class Scene1 : public ace::Scene
{
	std::shared_ptr<ace::TextureObject2D> obj;
protected:
	virtual void OnUpdated() override;
public:
	Scene1();
};

class Scene2 : public ace::Scene
{
	std::shared_ptr<ace::TextureObject2D> obj;
protected:
	virtual void OnUpdated() override;
public:
	Scene2();
};

Scene1::Scene1()
{
	auto layer = std::make_shared<ace::Layer2D>();

	AddLayer(layer);

	obj = std::make_shared<ace::TextureObject2D>();
	obj->SetTexture(ace::Engine::GetGraphics()->CreateTexture2D(ace::ToAString("Data/Texture/Sample1.png").c_str()));
	obj->SetCenterPosition(ace::Vector2DF(256, 256));
	obj->SetPosition(ace::Vector2DF(320, 240));

	layer->AddObject(obj);
}

void Scene1::OnUpdated()
{
	auto v = obj->GetAngle();
	v += 2.0;
	obj->SetAngle(v);

	//マウスが左クリックされた時にScene2へ遷移する。
	if (ace::Engine::GetMouse()->GetLeftButton()->GetButtonState() == ace::MouseButtonState::Push)
	{
		auto scene2 = std::make_shared<Scene2>();
		ace::Engine::ChangeScene(scene2);
	}
}

Scene2::Scene2()
{
	auto layer = std::make_shared<ace::Layer2D>();

	AddLayer(layer);

	obj = std::make_shared<ace::TextureObject2D>();
	obj->SetTexture(ace::Engine::GetGraphics()->CreateTexture2D(ace::ToAString("Data/Texture/Block1.png").c_str()));
	obj->SetPosition(ace::Vector2DF(100, 100));

	layer->AddObject(obj);
}

void Scene2::OnUpdated()
{
	auto v = obj->GetAngle();
	v -= 2.0;
	obj->SetAngle(v);

	//マウスが左クリックされた時にフェード付きでScene1へ遷移する。
	if (ace::Engine::GetMouse()->GetLeftButton()->GetButtonState() == ace::MouseButtonState::Push)
	{
		auto& scene1 = std::make_shared<Scene1>();
		ace::Engine::ChangeSceneWithTransition(scene1, std::make_shared<ace::TransitionFade>(1.0f, 1.0f));
	}
}

void Transition()
{
	//aceを初期化する。
	ace::Engine::Initialize(ace::ToAString("Transition").c_str(), 640, 480, ace::EngineOption());

	auto scene = std::make_shared<Scene1>();
	ace::Engine::ChangeScene(scene);

	// aceが進行可能かチェックする。
	while (ace::Engine::DoEvents())
	{
		//aceを更新する。
		ace::Engine::Update();
	}

	//aceを終了する。
	ace::Engine::Terminate();
}
