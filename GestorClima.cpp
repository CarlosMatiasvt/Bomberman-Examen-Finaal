// Fill out your copyright notice in the Description page of Project Settings.


#include "GestorClima.h"
#include "EstadoDia.h"
#include "EstadoNoche.h"
#include "Kismet/GameplayStatics.h"              // Para UGameplayStatics
#include "Engine/DirectionalLight.h"             // Para ADirectionalLight
#include "Components/DirectionalLightComponent.h" // Para UDirectionalLightComponent
#include "Engine/World.h"                        // Para GetWorld()
#include "Engine/Engine.h"                       // Para GEngine->AddOnScreenDebugMessage

// Sets default values
AGestorClima::AGestorClima()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	EsDeDia = true;
	EstadoActual = nullptr;

}

void AGestorClima::BeginPlay()
{
    Super::BeginPlay();
	// Inicializar el estado actual a día
    TArray<AActor*> FoundLights;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADirectionalLight::StaticClass(), FoundLights);
    if (FoundLights.Num() > 0)
    {
        ADirectionalLight* DirLightActor = Cast<ADirectionalLight>(FoundLights[0]);
        if (DirLightActor)
        {
            LuzDireccional = Cast<UDirectionalLightComponent>(DirLightActor->GetLightComponent());
        }
    }
}

void AGestorClima::CambiarEstado(UObject* NuevoEstado)
{
    EstadoActual = NuevoEstado;

    if (EstadoActual)
    {
		// Verificar si el objeto implementa la interfaz IIEstadoClima
        IIEstadoClima* Estado = Cast<IIEstadoClima>(EstadoActual);
        if (Estado)
        {
			// Aplicar el estado al gestor de clima
            Estado->AplicarEstado(this);
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("El objeto no implementa IEstadoClima"));
        }
    }

}




