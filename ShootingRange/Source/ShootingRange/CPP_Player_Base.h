// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
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

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// 正面／後方への移動
	UFUNCTION()
	void MoveForward(float Value);

	// 左右への移動
	UFUNCTION()
	void MoveRight(float Value);
	
	// キーが押された時にジャンプフラグをセット
	UFUNCTION()
	void StartJump();
	
	// キーが離された時にジャンプフラグをクリア
	UFUNCTION()
	void StopJump();

	// 一人称カメラ
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* FPSCameraComponent;

	// 一人称メッシュ（腕）、自身にのみ見える
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* FPSMesh;
};
