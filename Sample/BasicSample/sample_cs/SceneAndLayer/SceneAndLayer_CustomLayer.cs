﻿
// このサンプルで使用するカスタマイズしたレイヤー。
class SceneAndLayer_SampleLayer : asd.Layer2D
{
	// フレーム数を数えるカウンタ。
	private int count;

	// コンストラクタ
	public SceneAndLayer_SampleLayer()
	{
		// カウンタを初期化
		count = 0;
	}

	// 毎フレーム実行される関数をオーバーライド。
	protected override void OnUpdated()
	{
		// フレーム数を数える
		count++;

		// 60フレームごとに
		if(count % 60 == 0)
		{
			// オブジェクトを生成
			var obj = new asd.TextureObject2D();

			// オブジェクトのテクスチャを設定
			obj.Texture = asd.Engine.Graphics.CreateTexture2D("Data/Texture/Picture1.png");

			// オブジェクトの位置を設定
			var p = count / 60 * 20;
			obj.Position = new asd.Vector2DF(p, p);

			// オブジェクトをこのレイヤーに追加
			AddObject(obj);
		}
	}
}

class SceneAndLayer_CustomLayer : ISample
{
	public string Description
	{
		get { return "Layer2Dクラスを継承して、ふるまいをカスタマイズするサンプル。"; }
	}
	public string Title
	{
		get { return "レイヤーのカスタマイズ"; }
	}
	public string ClassName
	{
		get { return "SceneAndLayer_CustomLayer"; }
	}	

	// Layer2Dを継承することでカスタマイズしたレイヤーを作り、一定時間ごとにオブジェクトを追加するサンプル。
	public void Run()
	{
		// Altseedを初期化する。
		asd.Engine.Initialize("SceneAndLayer_CustomLayer", 640, 480, new asd.EngineOption());

		// シーンクラスのインスタンスを生成する。
		var scene = new asd.Scene();

		// 描画するシーンを指定する。
		asd.Engine.ChangeScene(scene);

		// レイヤークラスのインスタンスを生成する。
		var layer = new SceneAndLayer_SampleLayer();

		// 描画するレイヤーをシーンに追加する。
		scene.AddLayer(layer);

		// Altseedのウインドウが閉じられていないか確認する。
		while(asd.Engine.DoEvents())
		{
			// Altseedを更新する。
			asd.Engine.Update();
			Recorder.CaptureScreen("SceneAndLayer_CustomLayer", 0, 100, 0.5f, 0.5f);
			Recorder.TakeScreenShot("SceneAndLayer_CustomLayer", 150);
		}

		// Altseedを終了する。
		asd.Engine.Terminate();
	}
}