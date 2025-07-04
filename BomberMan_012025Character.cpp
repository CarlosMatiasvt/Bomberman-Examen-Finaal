// Copyright Epic Games, Inc. All Rights Reserved.
#include "BomberMan_012025Character.h"
#include "InterfaceBomba.h"
#include "GestorClima.h"
#include "EstadoDia.h"
#include "Kismet/GameplayStatics.h"
#include "EstadoNoche.h"
#include "ClaseConcretaColocarBomba.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

//////////////////////////////////////////////////////////////////////////
// ABomberMan_012025Character

ABomberMan_012025Character::ABomberMan_012025Character()
{


	ClaseBomba = ABomba::StaticClass();  // Apunta directamente a la clase C++

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

void ABomberMan_012025Character::BeginPlay()
{
	// Buscar instancia de GestorClima en el mundo
	Super::BeginPlay();

	TArray<AActor*> Encontrados;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGestorClima::StaticClass(), Encontrados);

	if (Encontrados.Num() > 0)
	{
		GestorClima = Cast<AGestorClima>(Encontrados[0]);

		if (GestorClima)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, TEXT("GestorClima asignado correctamente"));
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("NO se encontr� el GestorClima en el nivel"));
	}
}



//////////////////////////////////////////////////////////////////////////
// Input

void ABomberMan_012025Character::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &ABomberMan_012025Character::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABomberMan_012025Character::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ABomberMan_012025Character::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ABomberMan_012025Character::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &ABomberMan_012025Character::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &ABomberMan_012025Character::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &ABomberMan_012025Character::OnResetVR);
	//ColocarBomba
	PlayerInputComponent->BindAction("ColocarBomba", IE_Pressed, this, &ABomberMan_012025Character::ColocarBomba);
	//cambiar estado de d�a/noche
	PlayerInputComponent->BindAction("CambiarClima", IE_Pressed, this, &ABomberMan_012025Character::AlternarClima);


}



void ABomberMan_012025Character::ColocarBomba()
{
	if (!ClaseBomba)
	{
		UE_LOG(LogTemp, Warning, TEXT("ClaseBomba no asignada"));
		return;
	}

	FVector Pos = GetActorLocation();
	Pos.Z -= 90.f; // Ajusta la posici�n a los pies

	// Crear el comando concreto y almacenarlo en la interfaz
	UClaseConcretaColocarBomba* Comando = NewObject<UClaseConcretaColocarBomba>();
	Comando->Inicializar(Pos, ClaseBomba, GetWorld());

	ComandoColocarBomba = Comando;

	// Ejecutar usando la interfaz
	if (ComandoColocarBomba)
	{
		ComandoColocarBomba->Ejecutar();
	}
}
//alterna el clima
void ABomberMan_012025Character::AlternarClima()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green,
		FString::Printf(TEXT("EsDeDia ahora es: %s"), GestorClima->EsDeDia ? TEXT("True") : TEXT("False")));
	if (GestorClima)
	{
		if (GestorClima->EsDeDia)
		{
			// Cambiar a estado de noche
			GestorClima->CambiarEstado(NewObject<UEstadoNoche>());
		}
		else
		{
			// Cambiar a estado de d�a
			GestorClima->CambiarEstado(NewObject<UEstadoDia>());
		}
	}
}



void ABomberMan_012025Character::OnResetVR()
{
	// If BomberMan_012025 is added to a project via 'Add Feature' in the Unreal Editor the dependency on HeadMountedDisplay in BomberMan_012025.Build.cs is not automatically propagated
	// and a linker error will result.
	// You will need to either:
	//		Add "HeadMountedDisplay" to [YourProject].Build.cs PublicDependencyModuleNames in order to build successfully (appropriate if supporting VR).
	// or:
	//		Comment or delete the call to ResetOrientationAndPosition below (appropriate if not supporting VR)
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void ABomberMan_012025Character::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void ABomberMan_012025Character::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void ABomberMan_012025Character::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ABomberMan_012025Character::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ABomberMan_012025Character::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ABomberMan_012025Character::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}
