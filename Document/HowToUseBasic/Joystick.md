﻿## ジョイステックの入力状態の取得

AltseedでJoystickを扱うには、まずEngineクラスが持つJoystickContainerプロパティを取得します。これは接続されているジョイスティック一覧を保存するコンテナであり、このコンテナからGetJoystickAtメソッドで0からの番号を指定すると、Joystickクラスのインスタンスを取得できるため、そこから入力状態を取得します。

### ジョイステックにある全てのボタンの入力状態を取得

* include_basic_sample Joystick_Basic

### ジョイステックにある全てのアナログスティックの入力状態を取得

* include_basic_sample Joystick_Axis

## 一部のゲームパッドの入力状態の取得

* include_basic_sample Joystick_GamePad