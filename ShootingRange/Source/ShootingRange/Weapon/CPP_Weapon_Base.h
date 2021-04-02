// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CPP_DebugFireLineTraceEnum.h"
//#include "ShootingRange/Player/Interface/CPP_Player_Interfaces.h"
#include "ShootingRange/Player/CPP_ManageInteractStateEnum.h"
#include "Components/BoxComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_Weapon_Base.generated.h"

UCLASS()
class SHOOTINGRANGE_API ACPP_Weapon_Base : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACPP_Weapon_Base();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

/* 武器の基本情報 */
protected:
	// マガジンサイズ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponInfo")
	int32 MagazineSize;

	// マガジンの数
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponInfo")
	int32 MagazineNum;

	// 最大弾数
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "WeaponInfo")
	int32 MaxAmmo;

	// 現在のマガジン内の弾数
	int32 CurrentAmmo;

	// 射程距離
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponInfo")
	float BulletDistance;

/* 射撃処理 */
protected:
	// 発砲音
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SoundEffects")
	USoundBase* FireSound;

	// デバッグラインの切り替え
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DebugSettings")
	EShowDebugLine ShowDebugLine;

	// デバッグラインの色
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DebugSettings")
	FLinearColor LineColor;

	// デバッグラインを描画する時間
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DebugSettings")
	float Duration;

	// デバッグラインの厚さ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DebugSettings")
	float Thickness;

	// デバッグラインの開始地点
	FVector StartLocation;

	// デバッグラインの終了地点
	FVector EndLocation;

	// 弾の着弾結果
	FHitResult FireHitResult;

	// 着弾エフェクト
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Particles")
	UParticleSystem* HitEffect;

	// 着弾音
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SoundEffects")
	USoundBase* HitSound;

public:
	// 銃のリロード
	UFUNCTION(BlueprintCallable, Category = "WeaponBase")
	virtual void Reload();

	// 射撃
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "WeaponBase")
	void Fire();
	virtual void Fire_Implementation();

/* メッシュ */
protected:
	// ルートコンポーネント
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* DefaultSceneRoot;

	// インタラクトイベント用のコリジョン
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UBoxComponent* InteractCollision;

	// 武器のメッシュ
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* WeaponMesh;

/* インタラクトイベント */
protected:
	// 武器を持っているか
	bool bIsAttached;

public:
	// アイテムのピックアップイベント（インタラクト）
	//UFUNCTION()
	//void Interact() override;

	// プレイヤーの一人称メッシュを取得
	UFUNCTION()
	USceneComponent* GetFirstPersonMesh() const;

	// インタラクト用のオーバーラップイベント
	// オーバーラップ開始
	UFUNCTION()
	void OnOverlapBeginInteract
	(
		UPrimitiveComponent*	OverlappedComponent,
		AActor*					OtherActor,
		UPrimitiveComponent*	OtherComp,
		int32					OtherBodyIndex,
		bool					bFromSweep,
		const FHitResult&		SweepResult
	);
	// オーバーラップ終了
	UFUNCTION()
	void OnOverlapEndInteract
	(
		UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex
	);

/* エディタ */
public:
	// 最大弾数計算
	UFUNCTION(BlueprintCallable, Category = "WeaponBaseWithEditor")
	void CalculateMaxAmmo();

	// エディタの変更を検知して更新
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
};