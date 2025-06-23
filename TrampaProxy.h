// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ITrampa.h"
#include "TrampaReal.h"
#include "TrampaProxy.generated.h"

UCLASS()
class BOMBERMAN_012025_API ATrampaProxy : public AActor, public IITrampa
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATrampaProxy();
	// Referencia a la trampa real
	ATrampaReal* TrampaReal;
	// Componente de malla para la trampa proxy
	UStaticMeshComponent* MallaTrampaProxy;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Propiedad para controlar si se permite la activación de la trampa
	bool PermitirActivacion;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Funciones de la interfaz IITrampa
	virtual void Activar() override;
	virtual void SetPermitirActivacion(bool bPermitir) override;

};
