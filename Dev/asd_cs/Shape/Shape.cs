﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace asd
{
    /// <summary>
    /// 当たり判定や図形描画に用いられる図形を扱う抽象クラス。
    /// </summary>
    public abstract class Shape : IDisposable, IReleasable
    {
        #region IDisposable Support
        bool disposed = false;

        ~Shape()
        {
            Dispose(false);
        }

        public void Dispose()
        {
            Dispose(true);
            System.GC.SuppressFinalize(this);
        }

        protected virtual void Dispose(bool disposing)
        {
            if (disposed)
            {
                return;
            }

            var core = CoreShape;

            if (core != null)
            {
                GC.Collector.AddObject(core);
                CoreShape = null;
            }

            disposed = false;
        }
        #endregion
        /// <summary>
        /// 図形のタイプを取得する。
        /// </summary>
        public abstract ShapeType ShapeType { get; }

        internal abstract swig.CoreShape CoreShape { get; set; }

        bool IReleasable.IsReleased
        {
            get { return disposed; }
        }

        void IReleasable.ForceToRelease()
        {
            Dispose();
        }

        /// <summary>
        /// 指定した図形と衝突しているか否かを調べる。
        /// </summary>
        /// <param name="shape">衝突を調べる図形</param>
        /// <returns>衝突したか否か</returns>
        public bool GetIsCollidedWith(Shape shape)
        {
            return CoreShape.GetIsCollidedWith(shape.CoreShape);
        }
    }
}
