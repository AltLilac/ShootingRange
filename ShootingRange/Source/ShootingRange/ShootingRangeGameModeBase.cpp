// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "ShootingRangeGameModeBase.h"
#include "Engine.h"

void AShootingRangeGameModeBase::StartPlay()
{
	Super::StartPlay();

	check(GEngine != nullptr);

	const int32 AlwaysAddKey = -1;

	// このゲームモードがロードされたら、下記テキストをエディタ上に出力
	GEngine->AddOnScreenDebugMessage(AlwaysAddKey, 5.0f, FColor::Yellow, TEXT("Hello World, This is ShootingRangeGameMode!"));
}