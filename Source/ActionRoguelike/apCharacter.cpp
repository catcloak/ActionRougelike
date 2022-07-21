// Fill out your copyright notice in the Description page of Project Settings.


#include "apCharacter.h"
#include  "Z:\xuhuan\UE_4.26\Engine\Source\Runtime\Engine\Classes\GameFramework\SpringArmComponent.h"
#include "Z:\xuhuan\UE_4.26\Engine\Source\Runtime\Engine\Classes\Camera\CameraComponent.h"
#include "Z:\xuhuan\UE_4.26\Engine\Source\Runtime\Engine\Classes\GameFramework\CharacterMovementComponent.h"

// Sets default values
AapCharacter::AapCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->bUsePawnControlRotation = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);

	GetCharacterMovement()->bOrientRotationToMovement = true;

	bUseControllerRotationYaw = false;
}

// Called when the game starts or when spawned
void AapCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AapCharacter::MoveForward(float Value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.00f;
	ControlRot.Roll = 0.00f;

	AddMovementInput(ControlRot.Vector(), Value);

}

void AapCharacter::MoveRight(float Value)
{

	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.00f;
	ControlRot.Roll = 0.00f;

	
	//X = forward
	//Y = RIGHT
	//Z = UPDOWN

	FVector RightVector = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);

	AddMovementInput(RightVector, Value);
}
void AapCharacter::PrimaryAttack()
{
	FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");

	FTransform SpawnTM = FTransform(GetControlRotation(), HandLocation);

	FActorSpawnParameters SpawnParms;
	SpawnParms.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	GetWorld()->SpawnActor<AActor>(Projectileclass, SpawnTM, SpawnParms);
}
// Called every frame
void AapCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AapCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AapCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AapCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &AapCharacter::PrimaryAttack);
}

