// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ShootingRangeGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGRANGE_API AShootingRangeGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	virtual void StartPlay() override;
};
