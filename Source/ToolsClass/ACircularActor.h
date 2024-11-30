// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ACircularActor.generated.h"

UCLASS()
class TOOLSCLASS_API AACircularActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AACircularActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void GenerateObjects();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	TArray<UStaticMesh*> StaticMeshes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	int32 NumObjects;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	float Radius;
};
