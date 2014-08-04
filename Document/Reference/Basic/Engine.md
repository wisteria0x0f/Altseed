﻿## エンジン (Engine)

### 概要

AmusementCreatorsEngine(以下ACE)の機能を提供します。初期化、終了処理及び、殆どの機能を使用するためのプロパティを持っています。ACEを使用するためには必ずエンジンを使用する必要があります。

エンジンでACEの初期化を行えます。その時、様々なオプションを指定できます。例えば、フルスクリーンかどうかなどです。シーンの変更や終了処理もエンジンで行います。


### 主なメソッド

| 名称 | 説明 |
|---|---|
| Initialize | ACEを初期化します。使用開始時に必ず実行します。 |
| DoEvents | ACEのフレーム開始処理を実行します。毎フレームの開始時に必ず実行します。falseを返した場合、ACEを終了させる必要があります。 |
| Update | ACEの毎フレームの更新処理を実行します。毎フレーム、かならず実行します。 |
| Terminate | ACEの終了処理を実行します。ACEを終了時に必ず実行します。 |
| ChangeScene | 更新するシーンを変更します。 |
| ChangeSceneWithTransition | トランジションを適用し、更新するシーンを変更します。 |
| Close | ACEのウインドウを閉じます。 |
| TakeScreenshot | スクリーンショットを撮影し、画像として保存します。 |




### 主なプロパティ

#### フレームレート系

| 名称 | 説明 |
|---|---|
| CurrentFPS | 現在のFPS |
| TargetFPS | 目標のFPS。このFPSに近づくように内部の更新が実行されます。 |
| DeltaTime |  |
| TimeSpan |  |
| FramerateMode | フレームレート制御方法 |

### 主なイベント

なし

### 使用方法

全てのサンプルで使用されているので、そちらを参照してください。