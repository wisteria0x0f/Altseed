﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

/// <summary>
/// 文字列を回転させて表示するサンプル。
/// </summary>
class TextObject2D_Rotate : ISample
{
    public void Run()
    {
        // Altseedを初期化する。
        asd.Engine.Initialize("TextObject2D_Rotate", 640, 480, new asd.EngineOption());

        {
            // 動的フォントの取得と文字列描画オブジェクトの設定を行う。
            var edgeFont = asd.Engine.Graphics.CreateDynamicFont(string.Empty, 40, new asd.Color(255, 128, 128, 255), 1, new asd.Color(255, 255, 255, 255));
            var edgeObj = new asd.TextObject2D();
            edgeObj.Font = edgeFont;
            edgeObj.Position = new asd.Vector2DF(100, 100);

            // 30度回転させて描画する。
            edgeObj.Angle = 30;
            edgeObj.Text = "文字列の回転描画";
            asd.Engine.AddObject2D(edgeObj);
        }

        // Altseedのウインドウが閉じられていないか確認する。
        while (asd.Engine.DoEvents())
        {
            // Altseedを更新する。
            asd.Engine.Update();
            Recorder.TakeScreenShot("TextObject2D_Rotate", 30);
        }

        // Altseedの終了処理をする。
        asd.Engine.Terminate();
    }
}