// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_Weapon_Base.h"
#include "Engine/World.h"
#include "Components/AudioComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Engine.h"

// Sets default values
ACPP_Weapon_Base::ACPP_Weapon_Base()
	: MagazineSize	(0)
	, MagazineNum	(0)
	, MaxAmmo		(0)
	, CurrentAmmo	(MagazineSize)

	, BulletDistance(10000.0f)

	, FireSound	(nullptr)
	, HitEffect	(nullptr)
	, HitSound	(nullptr)

	, ShowDebugLine	(EShowDebugLine::Enabled)
	, Duration		(1.0)
	, Thickness		(1.0f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACPP_Weapon_Base::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPP_Weapon_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// 銃のリロード
void ACPP_Weapon_Base::Reload()
{
	// マガジン内の弾が減っていたら
	if (CurrentAmmo != MagazineSize)
	{
		int32 TempCurrentAmmo = CurrentAmmo;
		
		// マガジンの補給
		CurrentAmmo = MagazineSize > (CurrentAmmo + MaxAmmo) ? (CurrentAmmo + MaxAmmo) : MagazineSize;
		
		// 予備弾数を更新
		MaxAmmo = 0 >= (MaxAmmo - (MagazineSize - TempCurrentAmmo)) ? 0 : (MaxAmmo - (MagazineSize - TempCurrentAmmo));
	}
	else
	{
		return;
	}
}

// 射撃
void ACPP_Weapon_Base::Fire_Implementation()
{
	// マガジン内に弾が残っていたら
	if (CurrentAmmo > 0)
	{
		CurrentAmmo--;
	}
	else
	{
		return;
	}

	// 発砲音
	if (FireSound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), FireSound, GetActorLocation());
	}

	// デバッグラインの描画
	if (ShowDebugLine == EShowDebugLine::Enabled)
	{
		// 開始地点を取得
		StartLocation = GetActorLocation() + GetActorScale().Y;
		// 終了地点を取得
		EndLocation	= StartLocation + (GetActorLocation() * BulletDistance);
		// ライン色の指定
		LineColor = FLinearColor(255.0, 0.0, 0.0, 0.0);

		// ラインの描画
		UKismetSystemLibrary::DrawDebugLine(GetWorld(), StartLocation, EndLocation, LineColor, Duration, Thickness);
	}

	// ライントレース
	{
		FCollisionQueryParams CollisionQueryParams;
		
		// 自身を無視する（銃本体）
		CollisionQueryParams.AddIgnoredActor(this);

		// トレースするライン
		GetWorld()->LineTraceSingleByChannel(FireHitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility, CollisionQueryParams);

		// 着弾エフェクト
		if (FireHitResult.bBlockingHit && HitEffect && HitSound)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEffect, EndLocation);
			UGameplayStatics::SpawnSoundAtLocation(GetWorld(), HitSound, EndLocation);
		}
	}
}

// アイテムのピックアップイベント（インタラクト）
void ACPP_Weapon_Base::Interact_Implementation()
{
	ICPP_Interact::Interact_Implementation();

	check(GEngine != nullptr)

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, TEXT("Called WeaponBase interact interface!!"));
}

/*--- エディタ上での更新を反映させる ---*/
void ACPP_Weapon_Base::CalculateMaxAmmo()
{
	MaxAmmo = MagazineSize * MagazineNum;
}

#if WITH_EDITOR
void ACPP_Weapon_Base::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	CalculateMaxAmmo();
}
#endif // WITH_EDITOR
/* --------------------------------- */