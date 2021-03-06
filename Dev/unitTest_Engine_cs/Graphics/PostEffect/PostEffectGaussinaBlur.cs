﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace unitTest_Engine_cs.Graphics.PostEffect
{
	class PostEffectGaussinaBlur : EngineTest
	{
		asd.PostEffectGaussianBlur pe;
		float intensity = 0.0f;

		public PostEffectGaussinaBlur()
			: base(10)
		{
		}

		protected override void OnStart()
		{
			var scene = new asd.Scene();
			var layer = new asd.Layer2D();
			var obj = new asd.TextureObject2D();
			scene.AddLayer(layer);
			layer.AddObject(obj);
			asd.Engine.ChangeScene(scene);

			var g = asd.Engine.Graphics;
			var texture = g.CreateTexture2D("Data/Texture/Sample1.png");
			obj.Texture = texture;
			obj.Scale = new asd.Vector2DF(1, 1);

			pe = new asd.PostEffectGaussianBlur();
			pe.Intensity = intensity;
			layer.AddPostEffect(pe);
		}

		protected override void OnUpdating()
		{
			pe.Intensity = intensity;
			intensity += 0.5f;
		}
	}
}
