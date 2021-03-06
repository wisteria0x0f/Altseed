﻿#pragma once

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#include <asd.common.Base.h>
#include "../asd.Core.Base.h"
#include "../asd.ReferenceObject.h"
#include "../common/Math/asd.Vector2DI.h"

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
namespace asd {
	//----------------------------------------------------------------------------------
	//
	//----------------------------------------------------------------------------------
#if !SWIG
	typedef void(ASD_STDCALL *CoreFuncPtr)(Core*);
#endif

	class CoreOption
	{
	public:
		bool IsFullScreen;
		GraphicsDeviceType GraphicsDevice;
		bool IsReloadingEnabled;
		bool IsWindowResizable = false;
		WindowPositionType WindowPosition;
		ColorSpaceType ColorSpace;
	};

	class Core
		: public ReferenceObject
	{
	private:

	public:

#if !SWIG
		/**
			@brief	インスタンスが破棄された際に呼ばれる関数ポインタを設定する。
			@param	func	破棄された際に呼ばれる関数
		*/
		virtual void SetRemovedFunctionPpointer(CoreFuncPtr func) = 0;
#endif

		/**
		@brief	初期化を行う。
		@param	title	タイトル
		@param	width	横幅
		@param	height	縦幅
		@param	isFullScreen	フルスクリーンで起動するかどうか?
		@param	isOpenGLMode	OpenGLで起動するかどうか?
		@return	成否
		*/
		virtual bool Initialize(const achar* title, int32_t width, int32_t height, CoreOption option) = 0;

		/**
		@brief	初期化を行う。
		@param	handle1	ハンドル
		@param	handle2	ハンドル
		@param	width	横幅
		@param	height	縦幅
		@param	isOpenGLMode	OpenGLで起動するかどうか?
		@return	成否
		*/
		virtual bool InitializeByExternalWindow(void* handle1, void* handle2, int32_t width, int32_t height, CoreOption option) = 0;

		/**
			@brief	タイトルを設定する。
			@param	title	タイトル
		*/
		virtual void SetTitle(const achar* title) = 0;

		/**
		@brief	イベントを実行し、進行可否を判断する。
		@return	進行可能か?
		*/
		virtual bool DoEvents() = 0;

		/**
		@brief	更新処理を行う。
		*/
		virtual void Update() = 0;

		/**
		@brief	終了処理を行う。
		*/
		virtual void Terminate() = 0;

		/**
		@brief	更新されたリソースのリロードを行う。
		*/
		virtual void Reload() = 0;

		/**
			@brief	描画機能の準備をする。
		*/
		virtual void BeginDrawing() = 0;

		/**
			@brief	描画機能の使用を完了する。
		*/
		virtual void EndDrawing() = 0;

		/**
			@brief	シーンをウインドウに描画する。
		*/
		virtual void DrawSceneToWindow(CoreScene* scene) = 0;

		/**
			@brief	画面遷移しつつシーンをウインドウに描画する。
		*/
		virtual void DrawSceneToWindowWithTransition(CoreScene* nextScene, CoreScene* previousScene, CoreTransition* transition) = 0;

		/**
			@brief	現在のコアの内部情報を描画する。
		*/
		virtual void Draw() = 0;

		/**
			@brief	現在のシーンを変更します。
		*/
		virtual void ChangeScene(CoreScene* scene) = 0;

		/**
			@brief	ウインドウを閉じる。
		*/
		virtual void Close() = 0;

		/**
			@brief	マウスカーソルを作成する。
			@param	path	画像のパス
			@param	hot		カーソルの相対座標
			@return	カーソル
		*/
		virtual Cursor* CreateCursor(const achar* path, Vector2DI hot) = 0;

		/**
			@brief	マウスカーソルを設定する。
			@param	cursor	カーソル
		*/
		virtual void SetCursor(Cursor* cursor) = 0;

		/**
		@brief	クリップボードの内容を取得する。
		@return	クリップボード
		*/
		virtual const achar* GetClipboardString() = 0;

		/**
		@brief	クリップボードの内容を設定する。
		@param	s	文字列
		*/
		virtual void SetClipboardString(const achar* s) = 0;

		/**
			@brief	フルスクリーンモードかどうか設定する。
			@param	isFullscreenMode	フルスクリーンモードか
		*/
		virtual void SetIsFullscreenMode(bool isFullscreenMode) = 0;

		/**
			@brief	スクリーンショットをpngとして保存する。
			@param	path	出力先
		*/
		virtual void TakeScreenshot(const achar* path) = 0;

		/**
			@brief	スクリーンショットをgifアニメーションとして録画する。
			@param	path	出力先
			@param	frame	録画フレーム数
			@param	frequency_rate	録画頻度(例えば、1だと1フレームに1回保存、0.5だと2フレームに2回保存)
			@param	scale	ウインドウサイズに対する画像サイズの拡大率(ウインドウサイズが320の場合、0.5を指定すると160の画像が出力される)
			@note
			実行してから一定時間の間、録画を続ける。
			録画が終了するまでにアプリケーションが終了された場合、終了した時点までの録画結果が出力される。
		*/
		virtual void CaptureScreenAsGifAnimation(const achar* path, int32_t frame, float frequency_rate, float scale) = 0;

		/**
			@brief	1フレームで経過した時間を実時間(秒)で取得する。
			@return	経過時間時間(秒)
		*/
		virtual float GetDeltaTime() const = 0;

		/**
		@brief	1フレームで経過した時間を外部から設定する。
		@param	deltaTime	経過時間(秒)
		@note
		基本的に開発者は使用する必要はない。
		何らかの理由で無理やり経過時間を指定する場合に使用する。
		*/
		virtual void SetDeltaTime(float deltaTime) = 0;

		/**
			@brief	現在のFPSを取得する。
			@return FPS
		*/
		virtual float GetCurrentFPS() = 0;

		/**
			@brief	目標FPSを取得する。
			@return	FPS
		*/
		virtual int32_t GetTargetFPS() = 0;

		/**
			@brief	目標FPSを設定する。
			@param	fps	FPS
		*/
		virtual void SetTargetFPS(int32_t fps) = 0;

		/**
		@brief	時間を指定可能なオブジェクトの実時間あたりの進行速度を取得する。
		@return	進行速度
		*/
		virtual float GetTimeSpan() const = 0;

		/**
		@brief	時間を指定可能なオブジェクトの実時間あたりの進行速度を設定する。
		@param	timeSpan	進行速度
		*/
		virtual void SetTimeSpan(float timeSpan) = 0;

		/**
		@brief	フレームレートの制御方法を取得する。
		@return	制御方法
		*/
		virtual FramerateMode GetFramerateMode() const = 0;

		/**
		@brief	フレームレートの制御方法を設定する。
		@param	framerateMode	制御方法
		*/
		virtual void SetFramerateMode(FramerateMode framerateMode) = 0;

		/**
			@brief	Windowsの場合、ウインドウのハンドルを返す。
			@return	ウインドウハンドル
		*/
		virtual void* GetWindowHandle() const = 0;

		/**
		@brief キーボードの入力を扱うKeyboardクラスを取得する。
		*/
		virtual Keyboard* GetKeyboard() = 0;

		/**
		@brief マウスの入力を扱うMouseクラスを取得する。
		*/
		virtual Mouse* GetMouse() = 0;

		/**
		@brief 接続されているジョイスティックの入力を扱うJoystickContainerクラスを取得する。
		*/
		virtual JoystickContainer* GetJoystickContainer() = 0;

		/**
		@brief 通常のファイルとパックファイルに対する読み込みをサポートするFileクラスを取得する。
		*/
		virtual File* GetFile() = 0;

		/**
			@brief	ログ出力を扱うLogクラスを取得する。
		*/
		virtual Log* GetLogger() = 0;

		/**
			@brief	プロファイリング機能を提供するProfilerクラスを取得する。
		*/
		virtual Profiler* GetProfiler() = 0;

		virtual LayerProfiler* GetLayerProfiler() = 0;

		/**
			@brief	描画を扱うグラフィックスクラスを取得する。
		*/
		virtual Graphics* GetGraphics() = 0;

		virtual Sound* GetSound() = 0;

		virtual ObjectSystemFactory* GetObjectSystemFactory() = 0;

		virtual AnimationSystem* GetAnimationSyatem() = 0;

		/**
		@brief	ウィンドウサイズを取得する。
		*/
		virtual Vector2DI GetWindowSize() = 0;

		virtual void SetWindowSize(Vector2DI size) = 0;

		virtual bool GetProfilerVisibility() const = 0;

		virtual void SetProfilerVisibility(bool visible) = 0;

		virtual void OpenTool() = 0;

		virtual void CloseTool() = 0;

		virtual Tool* GetTool() = 0;
	};
	//----------------------------------------------------------------------------------
	//
	//----------------------------------------------------------------------------------
};
