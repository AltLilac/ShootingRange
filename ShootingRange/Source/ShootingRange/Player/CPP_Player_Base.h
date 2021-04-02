// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ShootingRange/Player/CPP_ManageInteractStateEnum.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CPP_Player_Base.generated.h"

UCLASS()
class SHOOTINGRANGE_API ACPP_Player_Base : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACPP_Player_Base();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// 一人称カメラ
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* FPSCameraComponent;

	// 一人称メッシュ
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* FPSMesh;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// X 方向の移動
	UFUNCTION()
	void MoveForward(float Value);

	// Y 方向の移動
	UFUNCTION()
	void MoveRight(float Value);
	
	// ジャンプの開始
	UFUNCTION()
	void StartJump();
	
	// ジャンプの終了
	UFUNCTION()
	void StopJump();

	// インタラクトの開始
	UFUNCTION()
	void BeginInteract();
};
