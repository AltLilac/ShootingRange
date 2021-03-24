// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_DebugFireLineTraceEnum.h"
#include "ShootingRange/Player/Interface/CPP_Interact.h"
#include "CPP_Weapon_Base.generated.h"

/*
	TODO:
	・ベースクラスでどこまで Attach と Interact を定義するか
	
	Interact
	・まず、オブジェクトのインタラクトイベントトリガー用に設定したコリジョンにプレイヤーがオーバーラップしたら
	インタラクト可能な旨を示す UI を表示
*/

UCLASS()
class SHOOTINGRANGE_API ACPP_Weapon_Base : public AActor, public ICPP_Interact
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACPP_Weapon_Base();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

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
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// 銃のリロード
	UFUNCTION(BlueprintCallable, Category = "WeaponBase")
	virtual void Reload();

	// 射撃
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "WeaponBase")
	void Fire();
	virtual void Fire_Implementation();

	// アイテムのピックアップイベント（インタラクト）
	UFUNCTION(BlueprintCallable, Category = "WeaponBase")
	void Interact_Implementation() override;

	/*--- エディタ上での更新を反映させる ---*/
	UFUNCTION(BlueprintCallable, Category = "WeaponBaseWithEditor")
	void CalculateMaxAmmo();

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	/* --------------------------------- */
};