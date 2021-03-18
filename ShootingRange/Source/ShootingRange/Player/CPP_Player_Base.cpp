// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_Player_Base.h"
#include "Engine.h"

// Sets default values
ACPP_Player_Base::ACPP_Player_Base()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ��l�̃J�����R���|�[�l���g���쐬
	FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	check(FPSCameraComponent != nullptr);

	// �J�����R���|�[�l���g���A�^�b�`
	FPSCameraComponent->SetupAttachment(CastChecked<USceneComponent, UCapsuleComponent>(GetCapsuleComponent()));

	// �J�������L�����N�^�[�̖ڂ̏�����ɔz�u
	FPSCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f + BaseEyeHeight));

	// �|�[���ŃJ�����̉�]���R���g���[���ł���悤�ɂ���
	FPSCameraComponent->bUsePawnControlRotation = true;

	// ��l�̃��b�V���i�r�j���쐬
	FPSMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));
	check(FPSMesh != nullptr);

	// ���g�ɂ��������Ȃ��悤�ɐݒ�
	FPSMesh->SetOnlyOwnerSee(true);

	// ��l�̃J�����ɃA�^�b�`
	FPSMesh->SetupAttachment(FPSCameraComponent);

	// ��l�̃L�����N�^�[���P��̃��b�V���Ɍ�����悤�A�r�̃��b�V���̉e���ꕔ������
	FPSMesh->bCastDynamicShadow = false;
	FPSMesh->CastShadow = false;

	// �S�g���b�V�������g���猩���Ȃ��悤�ɂ���
	GetMesh()->SetOwnerNoSee(true);
}

// Called when the game starts or when spawned
void ACPP_Player_Base::BeginPlay()
{
	Super::BeginPlay();

	const int32 AlwaysAddKey = -1;
	
	check(GEngine != nullptr);
	GEngine->AddOnScreenDebugMessage(AlwaysAddKey, 5.0f, FColor::Red, TEXT("We are using Player!"));
}

// Called every frame
void ACPP_Player_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACPP_Player_Base::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// �ړ��̃Z�b�g�A�b�v
	PlayerInputComponent->BindAxis("MoveForward/Backward", this, &ACPP_Player_Base::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight/Left", this, &ACPP_Player_Base::MoveRight);

	// ���_�ύX�̃Z�b�g�A�b�v
	PlayerInputComponent->BindAxis("Turn", this, &ACPP_Player_Base::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &ACPP_Player_Base::AddControllerPitchInput);

	// �W�����v�̃Z�b�g�A�b�v
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACPP_Player_Base::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACPP_Player_Base::StopJump);
}

// ���ʁ^����ւ̈ړ�
void ACPP_Player_Base::MoveForward(float Value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}

// ���E�ւ̈ړ�
void ACPP_Player_Base::MoveRight(float Value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}

// �L�[�������ꂽ���ɃW�����v�t���O���Z�b�g
void ACPP_Player_Base::StartJump()
{
	bPressedJump = true;
}

// �L�[�������ꂽ���ɃW�����v�t���O���N���A
void ACPP_Player_Base::StopJump()
{
	bPressedJump = false;
}