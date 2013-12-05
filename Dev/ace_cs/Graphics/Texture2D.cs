﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ace
{
	public class Texture2D : IDestroy
	{
		internal swig.Texture2D SwigObject { get; set; }

		internal Texture2D(swig.Texture2D swig)
		{
#if DEBUG
			// 唯一の対応するクラスであることを保証
			if(GC.Texture2Ds.GetObject(swig.GetPtr()) != null) throw new Exception();
#endif
			SwigObject = swig;
		}

		~Texture2D()
		{
			Destroy();
		}

		public bool IsDestroyed
		{
 			get
			{
				return SwigObject == null;
			}
		}

		public void Destroy()
		{
			lock (this)
			{
				if (SwigObject == null) return;
				GC.Collector.AddObject(SwigObject);
				SwigObject = null;
			}
			System.GC.SuppressFinalize(this);
		}

		public Vector2DI Size
		{
			get { return SwigObject.GetSize(); }
		}

		public TextureFilterType Filter
		{
			get { return (TextureFilterType)SwigObject.GetFilter();}
			set { SwigObject.SetFilter((swig.eTextureFilterType)value); }
		}
	}
}
