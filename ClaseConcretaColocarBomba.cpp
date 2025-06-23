// Fill out your copyright notice in the Description page of Project Settings.


#include "ClaseConcretaColocarBomba.h"


void UClaseConcretaColocarBomba::Ejecutar()
{
    if (!Mundo || !*BombaClase)
    {
        if (GEngine)
            GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("NO SE COLOCO BOMBA (Mundo o ClaseBomba es nullptr)"));
        return;
    }

    FActorSpawnParameters Parametros;
    Parametros.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

    ABomba* NuevaBomba = Mundo->SpawnActor<ABomba>(BombaClase, Ubicacion, FRotator::ZeroRotator, Parametros);

    if (NuevaBomba)
    {
        NuevaBomba->activar(); // <-- Aquí inicias el temporizador para que explote y se destruya
        GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, TEXT("¡Bomba colocada con éxito!"));
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("NO SE PUDO SPAWNEAR LA BOMBA"));
    }
}
