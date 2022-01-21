// Fill out your copyright notice in the Description page of Project Settings.


#include "Mario.h"

#include "Coin.h"
#include "KillZone.h"
#include "MyHUD.h"
#include "SMyCompoundWidget.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMario::AMario()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("Arm");
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->TargetArmLength = 300.f;
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);

	SprintSpeedMultiplier = 2.0f;
	Coins = 0;
}

// Called when the game starts or when spawned
void AMario::BeginPlay()
{
	Super::BeginPlay();

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AMario::OnCollide);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &AMario::OnStopCollision);

	RespawnLocation = GetActorLocation();
}

// Called every frame
void AMario::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMario::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Forward", this, &AMario::MoveForward);
	PlayerInputComponent->BindAxis("Side", this, &AMario::MoveSide);
	PlayerInputComponent->BindAxis("Turn", this, &AMario::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &AMario::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMario::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AMario::StopJumping);
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AMario::Sprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AMario::StopSprint);
	PlayerInputComponent->BindAction("Hurt", IE_Pressed, this, &AMario::UpdateHealth);
}

void AMario::MoveForward(float Direction)
{
	AddMovementInput(GetActorForwardVector(), Direction);
}


inline void AMario::MoveSide(float Direction)
{
	AddMovementInput(GetActorRightVector(), Direction);
}

void AMario::Sprint()
{
	GetCharacterMovement()->MaxWalkSpeed *= SprintSpeedMultiplier;
}

void AMario::StopSprint()
{
	GetCharacterMovement()->MaxWalkSpeed /= SprintSpeedMultiplier;
}


void AMario::OnCollide(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                       int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ACoin* Coin = Cast<ACoin>(OtherActor))
	{
		Coins++;
		UE_LOG(LogTemp, Warning, TEXT("Coins: %d"), Coins);
		Coin->Destroy();
	}

	if (AKillZone* KillZone = Cast<AKillZone>(OtherActor))
	{
		Coins = 0;
		UE_LOG(LogTemp, Warning, TEXT("Died"));
		SetActorLocation(RespawnLocation);
	}
}

void AMario::UpdateHealth()
{
	AMyHUD* GameHUD = Cast<AMyHUD>(UGameplayStatics::GetPlayerController(this->GetOwner(), 0)->GetHUD());
	Progress -= 0.005;

	if (IsValid(GameHUD))
	{
		GameHUD->InGameWidget->SetHealthBar(Progress);
	}
}


void AMario::OnStopCollision(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
                             class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("Collision stopped with: %s"), *OtherActor->GetFullName());
}
