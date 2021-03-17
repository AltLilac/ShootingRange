// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "ShootingRangeGameModeBase.h"
#include "Engine.h"

void AShootingRangeGameModeBase::StartPlay()
{
	Super::StartPlay();

	check(GEngine != nullptr);

	// キーが -1 の場合、上書きされずに常に新しいメッセージとして表示される
	const int32 AlwaysAddKey = -1;

	// Viewport 上にメッセージを表示する
	// キー, 表示時間, 文字色, 表示文字
	GEngine->AddOnScreenDebugMessage(AlwaysAddKey, 5.0f, FColor::Yellow, TEXT("Hello World, This is ShootingRangeGameMode!"));
}