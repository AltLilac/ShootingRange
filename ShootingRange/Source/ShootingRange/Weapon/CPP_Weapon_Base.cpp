// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_Weapon_Base.h"

// Sets default values
ACPP_Weapon_Base::ACPP_Weapon_Base()
	: MagazineSize(0)
	, MagazineNum(0)
	, MaxAmmo(0)
	, CurrentAmmo(0)
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

void ACPP_Weapon_Base::Reload()
{

}

void ACPP_Weapon_Base::Fire()
{

}