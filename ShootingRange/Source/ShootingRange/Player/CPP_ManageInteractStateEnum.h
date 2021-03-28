// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedEnum.h"
#include "CPP_ManageInteractStateEnum.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGRANGE_API UCPP_ManageInteractStateEnum : public UUserDefinedEnum
{
	GENERATED_BODY()
	
};

UENUM(BlueprintType)
enum class EManageInteractState : uint8
{
	InCollision,
	OutOfCollision
};