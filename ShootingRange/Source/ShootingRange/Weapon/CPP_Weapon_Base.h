// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

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

	// 弾倉のサイズ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponInfo")
	int32 MagazineSize;

	// 弾倉の数
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponInfo")
	int32 MagazineNum;

	// 最大弾数
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "WeaponInfo")
	int32 MaxAmmo;

	// 現在の弾倉内の弾数
	int32 CurrentAmmo;

	// 射程距離
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponInfo")
	float BulletDistance;

	// 発砲音
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SoundEffects")
	UAudioComponent* FireSound;

	// デバッグライン
	UENUM(BlueprintType)
	enum class EShowDebugLine : uint8
	{
		Enabled,
		Disabled
	};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DebugSettings")
	EShowDebugLine ShowDebugLine;

	// デバッグラインの色
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DebugSettings")
	FLinearColor LineColor;

	// デバッグラインの継続時間
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DebugSettings")
	float Duration;

	// デバッグラインの厚さ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DebugSettings")
	float Thickness;

	// デバッグラインの開始座標
	FVector StartLocation;

	// デバッグラインの終了座標
	FVector EndLocation;

	// ヒットしたオブジェクト
	FHitResult FireHitResult;

	// ヒットパーティクル
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Particles")
	UParticleSystemComponent* HitEffect;

	// ヒット音
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SoundEffects")
	UAudioComponent* HitSound;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "WeaponBase")
	virtual void Reload();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "WeaponBase")
	void Fire();
	virtual void Fire_Implementation();

	UFUNCTION(BlueprintCallable, Category = "WeaponBase")
	void CalculateMaxAmmo();
	
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

	// インターフェースを C++ ベースクラスである程度定義すべきか？
	/*
		# Interact
			* インタラクト可能なアイテムやオブジェクトに設定したコリジョンにプレイヤーがオーバーラップしたら
			  プレイヤークラスに通知を行い、インタラクト可能な旨を示す UI を表示する
			  (E キーで○○を取得)

			## どのようにしてプレイヤークラスに通知を送るか

		# Attach
			* インタラクト可能な旨を示す UI が表示されている状態で
			  プレイヤークラスから、インタラクトキー(E)の入力を受け取ったらこの関数を呼び出す

			* 入力を受け取ったら、プレイヤーの手の中央に武器をセットする
	*/
};