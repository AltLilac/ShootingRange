// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CPP_Attach.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCPP_Attach : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SHOOTINGRANGE_API ICPP_Attach
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	// アタッチイベント
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void AttachItemToHand();
	virtual void AttachItemToHand_Implementetion();
};
