// Fill out your copyright notice in the Description page of Project Settings.


#include "TrampaProxy.h"

// Sets default values
ATrampaProxy::ATrampaProxy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Inicializar propiedades de la trampa real
	MallaTrampaProxy = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MallaTrampaProxy"));
	RootComponent = MallaTrampaProxy;

	// Asignar un material al bloque
	MallaTrampaProxy->SetupAttachment(RootComponent);
	MallaTrampaProxy->SetWorldScale3D(FVector(1.0f, 1.0f, 3.0f));

	static ConstructorHelpers::FObjectFinder<UStaticMesh>ObjetoMallaTrampaProxy(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));

	if (ObjetoMallaTrampaProxy.Succeeded())
	{
		MallaTrampaProxy->SetStaticMesh(ObjetoMallaTrampaProxy.Object);

		MallaTrampaProxy->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	}

}

// Called when the game starts or when spawned
void ATrampaProxy::BeginPlay()
{
	Super::BeginPlay();

	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	TrampaReal = GetWorld()->SpawnActor<ATrampaReal>(ATrampaReal::StaticClass(), GetActorLocation(), FRotator::ZeroRotator, Params);
	
}

// Called every frame
void ATrampaProxy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATrampaProxy::Activar()
{
	// Verifica si la trampa real está disponible y si se permite la activación
    if (PermitirActivacion && TrampaReal)
    {
        TrampaReal->Activar();
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, TEXT("TRAMPA PROXY BIEN HECHA"));

    }
    else
    {
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, TEXT("NO SE IMPLEMENTO LA TRAMPA PROXY"));
	}
}

void ATrampaProxy::SetPermitirActivacion(bool bPermitir)
{
    PermitirActivacion = bPermitir;
}

