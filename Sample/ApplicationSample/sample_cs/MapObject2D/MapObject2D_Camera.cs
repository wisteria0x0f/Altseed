﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

/// <summary>
/// カメラ付きでマップを表示するサンプル。
/// </summary>
class MapObject2D_Camera : ISample
{
	public string Description
	{
		get { return "マップチップを並べて描画し、さらにカメラでスクロールするサンプルです。"; }
	}

	public string Title
	{
		get { return "マップチップとスクロール"; }
	}

	public string ClassName
	{
		get { return "MapObject2D_Camera"; }
	}

	public void Run()
    {
        // Altseedを初期化する
        asd.Engine.Initialize("MapObject2D_Camera", 640, 480, new asd.EngineOption());

        //カメラを設定する。
        var camera = new asd.CameraObject2D();

        camera.Src = new asd.RectI(0, 0, 640, 480);
        camera.Dst = new asd.RectI(0, 0, 640, 480);

        {
            //マップオブジェクトを生成する。
            var mapObject = new asd.MapObject2D();

            var texture = asd.Engine.Graphics.CreateTexture2D("Data/Texture/Chip1.png");

            //マップオブジェクトに50*50=2500個のチップを登録する。
            for (int i = 0; i < 50; ++i)
            {
                for (int j = 0; j < 50; ++j)
                {
                    //チップを生成する。
                    var chip = new asd.Chip2D();

                    //チップにテクスチャを設定する。
                    chip.Texture = texture;

                    //チップの描画先を指定する。
                    chip.Position = new asd.Vector2DF(i * 40 - 1000, j * 40 - 1000);

                    //マップオブジェクトにチップを追加する。
                    mapObject.AddChip(chip);
                }
            }

            //レイヤーにマップオブジェクトを追加する。
            asd.Engine.AddObject2D(mapObject);

            //レイヤーにカメラオブジェクトを追加する。
            asd.Engine.AddObject2D(camera);
        }

        // Altseedのウインドウが閉じられていないか確認する。
        while (asd.Engine.DoEvents())
        {
            //カメラを移動させる
            var pos = camera.Src;
            pos.X += 1;
            pos.Y += 1;
            pos.X %= 1000;
            pos.Y %= 1000;
            camera.Src = pos;

            // Altseedを更新する。
            asd.Engine.Update();
            Recorder.CaptureScreen("MapObject2D_Camera", 0, 8, 0.2f, 0.5f);
			Recorder.TakeScreenShot("MapObject2D_Camera", 20);
        }

        // Altseedの終了処理をする。
        asd.Engine.Terminate();
    }
}
