// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_Player_Base.h"
#include "Kismet/GameplayStatics.h"
#include "Engine.h"

/*
	TODO:

	・PlayerBase の BeginInteract が現状、全部のオブジェクトに対して一斉にインタラクトが行われるので
	条件に応じて個別にインタラクトを実行した方がいい

	・他にもインターフェースから実装していった方がいいアクションがあるので、
	新しくプレイヤーインターフェースのクラスを作って、射撃、リロード、インタラクトなどを作る
*/

extern EManageInteractState ManageInteractState;

// Sets default values
ACPP_Player_Base::ACPP_Player_Base()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 一人称カメラのセットアップ
	FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	check(FPSCameraComponent != nullptr);

	// 一人称カメラをアタッチ
	FPSCameraComponent->SetupAttachment(CastChecked<USceneComponent, UCapsuleComponent>(GetCapsuleComponent()));

	// 一人称カメラの相対座標
	FPSCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f + BaseEyeHeight));

	// 自身が回転を制御
	FPSCameraComponent->bUsePawnControlRotation = true;

	// 一人称メッシュのセットアップ
	FPSMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));
	check(FPSMesh != nullptr);

	// 一人称メッシュを自身にのみ見えるようにする
	FPSMesh->SetOnlyOwnerSee(true);

	// 一人称メッシュを一人称カメラにアタッチ
	FPSMesh->SetupAttachment(FPSCameraComponent);

	// 一部影を無効化
	FPSMesh->bCastDynamicShadow = false;
	FPSMesh->CastShadow = false;

	// 全体メッシュを自身から見えないようにする
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

	// プレイヤーアクションのセットアップ
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACPP_Player_Base::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACPP_Player_Base::StopJump);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &ACPP_Player_Base::BeginInteract);
}

void ACPP_Player_Base::MoveForward(float Value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}

void ACPP_Player_Base::MoveRight(float Value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}

void ACPP_Player_Base::StartJump()
{
	bPressedJump = true;
}

void ACPP_Player_Base::StopJump()
{
	bPressedJump = false;
}

void ACPP_Player_Base::BeginInteract()
{
	// 武器のインタラクトイベント用コリジョンにオーバーラップしていたら
	if (ManageInteractState == EManageInteractState::Weapon)
	{
		check(GEngine != nullptr)
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, TEXT("PlayerBase_Interact"));

		TArray<AActor*> OutActors;

		// インターフェース取得
		UGameplayStatics::GetAllActorsWithInterface(this->GetWorld(), UCPP_Interact::StaticClass(), OutActors);

		// インターフェースを持っている対象全ての実行を行う
		for (AActor* Actor : OutActors)
		{
			ICPP_Interact::Execute_Interact(Actor);
		}
	}
}