// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "InterfaceBomba.h"
#include "Bomba.h"
#include "ClaseConcretaColocarBomba.generated.h"

/**
 * 
 */
UCLASS()
class BOMBERMAN_012025_API UClaseConcretaColocarBomba : public UObject, public IInterfaceBomba
{
	GENERATED_BODY()
	
private:
    FVector Ubicacion;
    TSubclassOf<ABomba> BombaClase;
    UWorld* Mundo;

public:
    void Inicializar(FVector InUbicacion, TSubclassOf<ABomba> InBombaClase, UWorld* InMundo)
    {
        Ubicacion = InUbicacion;
        BombaClase = InBombaClase;
        Mundo = InMundo;
    }

    virtual void Ejecutar() override;
};
