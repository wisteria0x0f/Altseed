﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace test_cs
{
    class MouseSample1:ISample
    {
        [STAThread]
        public void Run()
        {
            var initialized = ace.Engine.Initialize("Mouse1", 640, 480, false);

            while (ace.Engine.DoEvents())
            {
                ace.Engine.Update();

                ace.Mouse mouse = ace.Engine.Mouse;

                switch (mouse.MiddleButton.ButtonState)
                {
                    case ace.MouseButtonState.Free:
                        Console.WriteLine("Middle Free");
                        break;
                    case ace.MouseButtonState.Hold:
                        Console.WriteLine("Middle Hold");
                        break;
                    case ace.MouseButtonState.Pull:
                        Console.WriteLine("Middle Pull");
                        break;
                    case ace.MouseButtonState.Push:
                        Console.WriteLine("Middle Push");
                        break;
                }
            }

            ace.Engine.Terminate();
        }
    }
}