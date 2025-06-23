// Fill out your copyright notice in the Description page of Project Settings.


#include "TrampaReal.h"

// Sets default values
ATrampaReal::ATrampaReal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Inicializar propiedades de la trampa real
	PermitirActivacion = true;

}

// Called when the game starts or when spawned
void ATrampaReal::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATrampaReal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATrampaReal::Activar()
{
	if (PermitirActivacion)
	{
		UE_LOG(LogTemp, Warning, TEXT("¡Trampa real activada!"));
	}
}

void ATrampaReal::SetPermitirActivacion(bool bPermitir)
{
	PermitirActivacion = bPermitir;

}

