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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MagazineSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MagazineNum;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 MaxAmmo;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 CurrentAmmo;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void Reload();

	UFUNCTION()
	virtual void Fire();

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
