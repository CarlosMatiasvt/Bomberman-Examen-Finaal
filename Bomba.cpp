// Fill out your copyright notice in the Description page of Project Settings.


#include "Bomba.h"

// Sets default values
ABomba::ABomba()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Añade un mesh para que se vea (puedes cambiar esto por uno propio en el editor)
	UStaticMeshComponent* BombaMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BombaMesh"));
	RootComponent = BombaMesh;
	// Asignar un material al bloque
	BombaMesh->SetupAttachment(RootComponent);
	BombaMesh->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));

	static ConstructorHelpers::FObjectFinder<UStaticMesh>ObjetoBombaMesh(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));
	if (ObjetoBombaMesh.Succeeded())
	{
		BombaMesh->SetStaticMesh(ObjetoBombaMesh.Object);

		BombaMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	}
}

// Called when the game starts or when spawned
void ABomba::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABomba::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABomba::activar()
{
	// Empieza el temporizador de explosión
	GetWorld()->GetTimerManager().SetTimer(
		TimerHandle_Explosion,
		this,
		&ABomba::Explotar,
		TiempoParaExplotar,
		false
	);
}

void ABomba::Explotar()
{
	// Puedes poner aquí efectos visuales o de daño
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, TEXT("LA BOMBA EXPLOTO"));

	Destroy(); // Destruye la bomba después de explotar
}

