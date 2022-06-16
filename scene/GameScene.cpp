#include "GameScene.h"
#include "TextureManager.h"
#include "AxisIndicator.h"
#include "PrimitiveDrawer.h"
#include "afin.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene()
{
	delete model_;
	delete debugCamera_;
}

void GameScene::Initialize()
{

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();

	textureHandle_ = TextureManager::Load("mario.jpg");
	model_ = Model::Create();

	//ワールドトランスフォーム
	worldTransform_.Initialize();
	//ビュープロダクション
	viewProjection_.Initialize();

	//デバックカメラの生成
	debugCamera_ = new DebugCamera(WinApp::kWindowWidth, WinApp::kWindowHeight);
	//軸方向表示の表示を有効化する
	AxisIndicator::GetInstance()->SetVisible(TRUE);
	//軸方向表示が参照するビュープロダクションを指定する（アドレス渡し）
	AxisIndicator::GetInstance()->SetTargetViewProjection(&debugCamera_->GetViewProjection());

	//ライン描画が参照するビュープロダクションを指定する(アドレス渡し）
	PrimitiveDrawer::GetInstance()->SetViewProjection(&debugCamera_->GetViewProjection());




	worldTransform_.scale_ = { 2.0f, 2.0f, 2.0f };



	//worldTransform_.matWorld_ = {
	//	1.0f, 0.0f, 0.0f, 0.0f,
	//	1.0f, 1.0f, 0.0f, 0.0f,
	//	1.0f, 0.0f, 1.0f, 0.0f,
	//	1.0f, 0.0f, 0.0f, 1.0f
	//};
	//worldTransform_.matWorld_ *= matScale;



	Matrix4 matScale = genScaleMatrix(worldTransform_.scale_); // (1)
	setMatWolrd(worldTransform_, matScale);
	//行列の転送
	worldTransform_.TransferMatrix();

}

void GameScene::Update()
{
	debugCamera_->Update();
}

void GameScene::Draw()
{

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	model_->Draw(worldTransform_, debugCamera_->GetViewProjection(), textureHandle_);
	for (int i = 0; i < 8; i++)
	{
		//PrimitiveDrawer::GetInstance()->DrawLine3d(line[i], line[i+1 % 8], color);
		PrimitiveDrawer::GetInstance()->DrawLine3d(startLine[i], endLine[i], color);

	}
	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// デバッグテキストの描画
	debugText_->DrawAll(commandList);
	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}


