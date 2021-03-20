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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MagazineSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MagazineNum;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 MaxAmmo;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 CurrentAmmo;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void Reload();

	UFUNCTION()
	virtual void Fire();

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
