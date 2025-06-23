// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "IEstadoClima.h"
#include "GestorClima.h"
#include "EstadoNoche.generated.h"

/**
 * 
 */
UCLASS()
class BOMBERMAN_012025_API UEstadoNoche : public UObject, public IIEstadoClima
{
	GENERATED_BODY()

public:
    virtual void AplicarEstado(AGestorClima* Gestor) override
    {
        if (Gestor && Gestor->LuzDireccional)
        {
            Gestor->LuzDireccional->SetIntensity(0.0f);
            GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Yellow, TEXT("Ahora es de NOCHE"));
        }
        Gestor->EsDeDia = false;
    }
};
