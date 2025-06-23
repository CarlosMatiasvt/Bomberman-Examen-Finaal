// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "IEstadoClima.h"
#include "GestorClima.h"
#include "EstadoDia.generated.h"

/**
 * 
 */
UCLASS()
class BOMBERMAN_012025_API UEstadoDia : public UObject, public IIEstadoClima
{
	GENERATED_BODY()
public:
    virtual void AplicarEstado(AGestorClima* Gestor) override
    {
		// Cambia el estado del gestor a día
        if (Gestor && Gestor->LuzDireccional)
        {
			// Ajusta la intensidad de la luz direccional a un valor positivo para simular día
            Gestor->LuzDireccional->SetIntensity(10.0f);
            GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Yellow, TEXT("Ahora es de DÍA"));
        }
        Gestor->EsDeDia = true;
    }

};
