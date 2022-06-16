#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "DebugCamera.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

  public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

  private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	DebugText* debugText_ = nullptr;

	/// <summary>
	/// ゲームシーン用
	uint32_t textureHandle_ = 0;
	//3Dモデルの生成
	Model* model_ = nullptr;
	DebugCamera* debugCamera_ = nullptr;

	

	Vector3 box[8] = {
		{0.0f, 0.0f, 0.0f},//0
		{5.0f, 0.0f, 0.0f},//1
		{5.0f, 0.0f, 5.0f},//2
		{0.0f, 0.0f, 5.0f},//3

		{0.0f, 5.0f, 0.0f},//4
		{5.0f, 5.0f, 0.0f},//5
		{5.0f, 5.0f, 5.0f},///6
		{0.0f, 5.0f, 5.0f},//7
	};

	Vector3 startLine[8] = {
		//縦
		{-7.5f, 0.0f, -7.5f},//0
		{-2.5f, 0.0f, -7.5f},//1
		{2.5f, 0.0f, -7.5f},//2
		{7.5f, 0.0f, -7.5f},//3
		//横
		{-7.5f, 0.0f, -7.5f},//4
		{-7.5f, 0.0f, -2.5f},//5
		{-7.5f, 0.0f, 2.5f},///6
		{-7.5f, 0.0f, 7.5f},//7
	};

	Vector3 endLine[8] = {
		//縦
		{-7.5f, 0.0f, 7.5f},//0
		{-2.5f, 0.0f, 7.5f},//1
		{2.5f, 0.0f, 7.5f},//2
		{7.5f, 0.0f, 7.5f},//3
		//横
		{7.5f, 0.0f, -7.5f},//4
		{7.5f, 0.0f, -2.5f},//5
		{7.5f, 0.0f, 2.5f},///6
		{7.5f, 0.0f, 7.5f},//7
	};




	int boxEdgeList[12][2] =
	{
		{0,1},
		{1,2},
		{2,3},
		{3,0},
		{0,4},
		{1,5},
		{2,6},
		{3,7},
		{4,5},
		{5,6},
		{6,7},
		{7,4},
	};

	//色の設定
	Vector4 color = {
		0xFF, 0xFF, 0xFF, 0xFF
	};
	
	

	//ワールドトランスフォーム
	WorldTransform worldTransform_;
	//ビュープロダクション
	ViewProjection viewProjection_;

	/// </summary>
};
