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
		// Cambia el estado del gestor a noche
        if (Gestor && Gestor->LuzDireccional)
        {
			// Ajusta la intensidad de la luz direccional a 0 para simular noche
            Gestor->LuzDireccional->SetIntensity(0.0f);
            GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Yellow, TEXT("Ahora es de NOCHE"));
        }
        Gestor->EsDeDia = false;
    }
};
