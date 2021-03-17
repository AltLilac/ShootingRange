// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_Player_Base.h"
#include "Engine.h"

// Sets default values
ACPP_Player_Base::ACPP_Player_Base()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 一人称カメラコンポーネントを作成
	FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	check(FPSCameraComponent != nullptr);

	// カメラコンポーネントをアタッチ
	FPSCameraComponent->SetupAttachment(CastChecked<USceneComponent, UCapsuleComponent>(GetCapsuleComponent()));

	// カメラをキャラクターの目の少し上に配置
	FPSCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f + BaseEyeHeight));

	// ポーンでカメラの回転をコントロールできるようにする
	FPSCameraComponent->bUsePawnControlRotation = true;

	// 一人称メッシュ（腕）を作成
	FPSMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));
	check(FPSMesh != nullptr);

	// 自身にしか見えないように設定
	FPSMesh->SetOnlyOwnerSee(true);

	// 一人称カメラにアタッチ
	FPSMesh->SetupAttachment(FPSCameraComponent);

	// 一人称キャラクターが単一のメッシュに見えるよう、腕のメッシュの影を一部無効化
	FPSMesh->bCastDynamicShadow = false;
	FPSMesh->CastShadow = false;

	// 全身メッシュを自身から見えないようにする
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

	// 移動のセットアップ
	PlayerInputComponent->BindAxis("MoveForward/Backward", this, &ACPP_Player_Base::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight/Left", this, &ACPP_Player_Base::MoveRight);

	// 視点変更のセットアップ
	PlayerInputComponent->BindAxis("Turn", this, &ACPP_Player_Base::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &ACPP_Player_Base::AddControllerPitchInput);

	// ジャンプのセットアップ
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACPP_Player_Base::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACPP_Player_Base::StopJump);
}

// 正面／後方への移動
void ACPP_Player_Base::MoveForward(float Value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}

// 左右への移動
void ACPP_Player_Base::MoveRight(float Value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}

// キーが押された時にジャンプフラグをセット
void ACPP_Player_Base::StartJump()
{
	bPressedJump = true;
}

// キーが離された時にジャンプフラグをクリア
void ACPP_Player_Base::StopJump()
{
	bPressedJump = false;
}