// Fill out your copyright notice in the Description page of Project Settings.


#include "ACircularActor.h"
#include "Engine/StaticMeshActor.h"


// Sets default values
AACircularActor::AACircularActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AACircularActor::BeginPlay()
{
	Super::BeginPlay();
	GenerateObjects();
}

#pragma optimize("", off)
void AACircularActor::GenerateObjects()
{
	if (StaticMeshes.Num() <= 0) return;

	for (int index = 0; index < NumObjects; index++)
	{
		float Angle = index * (360.0f / NumObjects);
		FVector position = FVector(FMath::Cos(FMath::DegreesToRadians(Angle)) * Radius, FMath::Sin(FMath::DegreesToRadians(Angle)) * Radius, 0.0f);
		position = GetActorLocation() + position;

		int32 randomIndex = FMath::RandRange(0, StaticMeshes.Num() - 1);
		UStaticMesh* selectedMesh = StaticMeshes[randomIndex];

		if (selectedMesh) 
		{
			AStaticMeshActor* meshActor = GetWorld()->SpawnActor<AStaticMeshActor>(position, FRotator::ZeroRotator);

			if (meshActor) 
			{
				meshActor->GetStaticMeshComponent()->SetStaticMesh(selectedMesh);
			}
		}
	}
}
#pragma optimize("", on)

// Called every frame
void AACircularActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

