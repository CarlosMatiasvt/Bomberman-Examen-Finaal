// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bomba.generated.h"

UCLASS()
class BOMBERMAN_012025_API ABomba : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABomba();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Tiempo antes de explotar (segundos)
	UPROPERTY(EditAnywhere, Category = "Bomba")
	float TiempoParaExplotar = 5.0f;
	void activar();
	// Efecto de explosión (opcional)
	void Explotar();

private:
	FTimerHandle TimerHandle_Explosion;
};
