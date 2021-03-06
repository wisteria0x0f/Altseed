﻿## マウス (Mouse)

### 概要

マウスからの入力を扱うクラスです。

[エンジン](../Basic/Engine.md)のMouseプロパティから現在のフレームのマウスの入力状態を持った当クラスのインスタンスを取得できます。

マウスが持つ左ボタン、右ボタンならびに中央ボタンの押し状態と、中央ボタンのホイールの回転状態を調べることが出来ます。
（2016.06.09に追加したGetButtonInputStateにてマウス上のすべてのボタンの押し状態を調べられるようになりました。）

#### ボタンの押し状態

押し状態は前のフレームと現在のフレームでそのボタンを押したかによって決まり、以下の4通りとなります。(○・・・押している、✕・・・押していない)

|状態|前のフレーム|現在のフレーム|
|---|---|---|
|Free|✕|✕|
|Release|○|✕|
|Push|✕|○|
|Hold|○|○|

### 主なメソッド

| 名称 | 説明 |
|---|---|
|GetButtonInputState|指定したボタンの入力状態を取得（押し状態）|

### 主なプロパティ


| 名称 | 説明 |
|---|---|
|LeftButton|マウスの左ボタンの入力状態を持つクラスを取得(ボタンの押し状態)|
|MiddleButton|マウスの中央ボタンの入力状態を持つクラスを取得(ボタンの押し状態とホイールの回転状態)|
|RightButton|マウスの右ボタンの入力状態を持つクラスを取得(ボタンの押し状態)|
|Wheel|ホイールの回転度合い|
|Position|マウスポインタの位置を取得|

### 主なイベント

なし

### 使用方法

Mouseクラスのサンプルです。

* include_basic_sample Mouse

