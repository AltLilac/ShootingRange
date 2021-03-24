// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_Interact.h"
#include "Engine.h"

// Add default functionality here for any ICPP_Interact functions that are not pure virtual.
void ICPP_Interact::Interact_Implementation()
{
	check(GEngine != nullptr)

	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Cyan, TEXT("Called default interact interface!!"));
}