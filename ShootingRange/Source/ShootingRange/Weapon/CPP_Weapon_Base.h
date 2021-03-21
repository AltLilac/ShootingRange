// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_Weapon_Base.generated.h"

UCLASS()
class SHOOTINGRANGE_API ACPP_Weapon_Base : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPP_Weapon_Base();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// �e�q�̃T�C�Y
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponInfo")
	int32 MagazineSize;

	// �e�q�̐�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponInfo")
	int32 MagazineNum;

	// �ő�e��
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "WeaponInfo")
	int32 MaxAmmo;

	// ���݂̒e�q���̒e��
	int32 CurrentAmmo;

	// �˒�����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponInfo")
	float BulletDistance;

	// ���C��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SoundEffects")
	UAudioComponent* FireSound;

	// �f�o�b�O���C��
	UENUM(BlueprintType)
	enum class EShowDebugLine : uint8
	{
		Enabled,
		Disabled
	};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DebugSettings")
	EShowDebugLine ShowDebugLine;

	// �f�o�b�O���C���̐F
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DebugSettings")
	FLinearColor LineColor;

	// �f�o�b�O���C���̌p������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DebugSettings")
	float Duration;

	// �f�o�b�O���C���̌���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DebugSettings")
	float Thickness;

	// �f�o�b�O���C���̊J�n���W
	FVector StartLocation;

	// �f�o�b�O���C���̏I�����W
	FVector EndLocation;

	// �q�b�g�����I�u�W�F�N�g
	FHitResult FireHitResult;

	// �q�b�g�p�[�e�B�N��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Particles")
	UParticleSystemComponent* HitEffect;

	// �q�b�g��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SoundEffects")
	UAudioComponent* HitSound;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "WeaponBase")
	virtual void Reload();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "WeaponBase")
	void Fire();
	virtual void Fire_Implementation();

	UFUNCTION(BlueprintCallable, Category = "WeaponBase")
	void CalculateMaxAmmo();
	
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

	// �C���^�[�t�F�[�X�� C++ �x�[�X�N���X�ł�����x��`���ׂ����H
	/*
		# Interact
			* �C���^���N�g�\�ȃA�C�e����I�u�W�F�N�g�ɐݒ肵���R���W�����Ƀv���C���[���I�[�o�[���b�v������
			  �v���C���[�N���X�ɒʒm���s���A�C���^���N�g�\�Ȏ|������ UI ��\������
			  (E �L�[�Ł������擾)

			## �ǂ̂悤�ɂ��ăv���C���[�N���X�ɒʒm�𑗂邩

		# Attach
			* �C���^���N�g�\�Ȏ|������ UI ���\������Ă����Ԃ�
			  �v���C���[�N���X����A�C���^���N�g�L�[(E)�̓��͂��󂯎�����炱�̊֐����Ăяo��

			* ���͂��󂯎������A�v���C���[�̎�̒����ɕ�����Z�b�g����
	*/
};