// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "ShootingRangeGameModeBase.h"
#include "Engine.h"

void AShootingRangeGameModeBase::StartPlay()
{
	Super::StartPlay();

	check(GEngine != nullptr);

	// �L�[�� -1 �̏ꍇ�A�㏑�����ꂸ�ɏ�ɐV�������b�Z�[�W�Ƃ��ĕ\�������
	const int32 AlwaysAddKey = -1;

	// Viewport ��Ƀ��b�Z�[�W��\������
	// �L�[, �\������, �����F, �\������
	GEngine->AddOnScreenDebugMessage(AlwaysAddKey, 5.0f, FColor::Yellow, TEXT("Hello World, This is ShootingRangeGameMode!"));
}