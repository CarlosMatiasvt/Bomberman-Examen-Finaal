// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IEstadoClima.h"
#include "Components/DirectionalLightComponent.h"
#include "GestorClima.generated.h"

UCLASS()
class BOMBERMAN_012025_API AGestorClima : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGestorClima();
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Luz")
	class UDirectionalLightComponent* LuzDireccional;

	// Cambiar estado recibe un UObject que implemente la interfaz IEstadoClima
	UFUNCTION()
	// Cambia el estado del clima
	void CambiarEstado(UObject* NuevoEstado);

	// Variable para saber si es día o noche
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Estado")
	bool EsDeDia;

private:
	UPROPERTY()
	UObject* EstadoActual;

};
