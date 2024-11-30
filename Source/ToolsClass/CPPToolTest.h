// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPPToolTest.generated.h"

UCLASS()
class TOOLSCLASS_API ACPPToolTest : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = true))
	UStaticMeshComponent* Body;

	UPROPERTY(EditInstanceOnly, BluePrintReadOnly, meta = (AllowPrivateAccess = true))
	TArray<UStaticMeshComponent*> ComponentList;

	UPROPERTY(EditInstanceOnly, BluePrintReadOnly, meta=(AllowPrivateAccess = true)) 
	float DistanceBetweenElements;

	UPROPERTY(EditInstanceOnly, BluePrintReadOnly, meta = (AllowPrivateAccess = true))
	int NumberOfElements;

	UPROPERTY(EditInstanceOnly, BluePrintReadOnly, meta = (AllowPrivateAccess = true))
	UStaticMesh* Visualizer;

	
public:	
	// Sets default values for this actor's properties
	ACPPToolTest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnConstruction(const FTransform& _transform) override;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	virtual void RegenerateComponents();
	virtual void AlignComponents();
	virtual void SetStaticMesh();
#endif


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
