// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ITrampa.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UITrampa : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BOMBERMAN_012025_API IITrampa
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	// Funciones de la interfaz
	virtual void Activar() = 0;
	virtual void SetPermitirActivacion(bool bPermitir) = 0;
};
