// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ITrampa.h"
#include "TrampaReal.generated.h"


UCLASS()
class BOMBERMAN_012025_API ATrampaReal : public AActor, public IITrampa
{
	GENERATED_BODY()
	
private:
	bool PermitirActivacion;

public:	
	// Sets default values for this actor's properties
	ATrampaReal();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Funciones de la interfaz IITrampa
	virtual void Activar() override;
	virtual void SetPermitirActivacion(bool bPermitir) override;

};
