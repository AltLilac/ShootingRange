// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedEnum.h"
#include "CPP_DebugFireLineTraceEnum.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGRANGE_API UCPP_DebugFireLineTraceEnum : public UUserDefinedEnum
{
	GENERATED_BODY()
	
};

UENUM(BlueprintType)
enum class EShowDebugLine : uint8
{
	Enable,
	Disable
};
