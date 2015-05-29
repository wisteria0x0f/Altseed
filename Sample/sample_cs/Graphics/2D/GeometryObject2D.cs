﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace sample_cs.Graphics._2D
{
    /// <summary>
    /// 図形を表示する。
    /// </summary>
    class GeometryObject2D : ISample
    {
        public void Run()
        {
            // aceを初期化する
            ace.Engine.Initialize("GeometryObject2D", 640, 480, new ace.EngineOption());

            // シーンを生成する
            var scene = new ace.Scene();

            var layer = new ace.Layer2D();
            var texture = ace.Engine.Graphics.CreateTexture2D("Data/Texture/Sample1.png");

            //図形描画クラスのコンストラクタを呼び出す
            var geometryObj1 = new ace.GeometryObject2D();
            var geometryObj2 = new ace.GeometryObject2D();
            var geometryObj3 = new ace.GeometryObject2D();

            //図形描画クラスをレイヤーに追加する。
            layer.AddObject(geometryObj1);
            layer.AddObject(geometryObj2);
            layer.AddObject(geometryObj3);

            //レイヤーをシーンに追加する。
            scene.AddLayer(layer);

            //シーンを変更する。
            ace.Engine.ChangeScene(scene);

            //弧を図形描画クラス1にて描画する。
            {
                //弧の外径、内径、頂点数、中心位置、開始頂点番号、終了頂点番号を指定。
                var arc = new ace.ArcShape();
                arc.OuterDiameter= 100;
                arc.InnerDiameter = 10;
                arc.NumberOfCorners = 96;
                arc.Position = new ace.Vector2DF(300, 100);
                arc.StartingCorner = 90;
                arc.EndingCorner = 5;

                //弧を描画する図形として設定し、合成するテクスチャも設定。
                geometryObj1.Shape = arc;
                geometryObj1.Texture = texture;
                geometryObj1.Position = new ace.Vector2DF(0, 0);
            }

            //矩形を図形描画クラス2にて描画する。
            {
                //矩形の描画範囲、UV範囲を指定。
                var rect = new ace.RectangleShape();
                rect.DrawingArea = new ace.RectF(10, 210, 300, 200);
                rect.UV = new ace.RectF(0, 0, 0.5f, 0.5f);

                //矩形を描画する図形として設定し、合成するテクスチャも設定。
                geometryObj2.Shape = rect;
                geometryObj2.Texture = texture;
                geometryObj2.Position = new ace.Vector2DF(0, 0);
            }

            //多角形を図形描画クラス3にて描画する。
            {

                var polygon = new ace.PolygonShape();
                //多角形を構成する頂点を追加していく。（星形になるようにする。）
                for (int i = 0; i < 10; ++i)
                {
                    ace.Vector2DF vec = new ace.Vector2DF(1, 0);
                    vec.Degree = i * 36;
                    vec.Length = (i % 2 == 0) ? 100 : 55;
                    polygon.AddVertex(vec + new ace.Vector2DF(500, 250));

                }

                //多角形を描画する図形として設定し、合成するテクスチャも設定。
                geometryObj3.Shape = polygon;
                geometryObj3.Texture = texture;
                geometryObj3.Position = new ace.Vector2DF(0, 0);
            }

            // aceが進行可能かチェックする。
            while (ace.Engine.DoEvents())
            {
                // aceを更新する。
                ace.Engine.Update();
            }

            // aceを終了する。
            ace.Engine.Terminate();
        }

    }
}