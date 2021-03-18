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

	// ���ʁ^����ւ̈ړ�
	UFUNCTION()
	void MoveForward(float Value);

	// ���E�ւ̈ړ�
	UFUNCTION()
	void MoveRight(float Value);
	
	// �L�[�������ꂽ���ɃW�����v�t���O���Z�b�g
	UFUNCTION()
	void StartJump();
	
	// �L�[�������ꂽ���ɃW�����v�t���O���N���A
	UFUNCTION()
	void StopJump();

	// ��l�̃J����
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* FPSCameraComponent;

	// ��l�̃��b�V���i�r�j�A���g�ɂ̂݌�����
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* FPSMesh;
};
